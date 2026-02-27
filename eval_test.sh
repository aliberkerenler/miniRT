#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
BOLD='\033[1m'
NC='\033[0m'

PASS=0
FAIL=0
WARN=0
TOTAL=0

ok()   { PASS=$((PASS+1)); TOTAL=$((TOTAL+1)); printf "  ${GREEN}[OK]${NC}   %s\n" "$1"; }
ko()   { FAIL=$((FAIL+1)); TOTAL=$((TOTAL+1)); printf "  ${RED}[KO]${NC}   %s\n" "$1"; }
warn() { WARN=$((WARN+1)); TOTAL=$((TOTAL+1)); printf "  ${YELLOW}[!!]${NC}   %s\n" "$1"; }
section() { echo ""; printf "${BOLD}${CYAN}━━━ %s ━━━${NC}\n" "$1"; }

# --- Test a scene renders without crash (timeout 5s) ---
test_render() {
	local scene="$1"
	local desc="$2"
	timeout 5 ./miniRT "$scene" &
	local pid=$!
	sleep 2
	if kill -0 "$pid" 2>/dev/null; then
		kill "$pid" 2>/dev/null
		wait "$pid" 2>/dev/null
		ok "$desc"
		return 0
	else
		wait "$pid" 2>/dev/null
		local exit_code=$?
		if [ "$exit_code" -eq 139 ] || [ "$exit_code" -eq 134 ] || [ "$exit_code" -eq 136 ]; then
			ko "$desc (CRASH - exit code $exit_code)"
			return 1
		else
			ko "$desc (exit code $exit_code)"
			return 1
		fi
	fi
}

# --- Test error scene exits with error message ---
test_error() {
	local scene="$1"
	local expected_msg="$2"
	local desc="$3"
	local output
	output=$(timeout 3 ./miniRT "$scene" 2>&1)
	local exit_code=$?
	if echo "$output" | grep -q "Error"; then
		if [ -n "$expected_msg" ] && echo "$output" | grep -qi "$expected_msg"; then
			ok "$desc"
		elif [ -n "$expected_msg" ]; then
			warn "$desc (got: $(echo "$output" | tail -1))"
		else
			ok "$desc"
		fi
	else
		ko "$desc (no error message)"
	fi
}

# --- Valgrind leak check ---
test_valgrind() {
	local scene="$1"
	local desc="$2"
	local output
	output=$(valgrind --leak-check=full --errors-for-leak-kinds=all \
		timeout 3 ./miniRT "$scene" 2>&1)
	local leaks=$(echo "$output" | grep "definitely lost:" | awk '{gsub(/,/,"",$4); print $4}')
	local indirect=$(echo "$output" | grep "indirectly lost:" | awk '{gsub(/,/,"",$4); print $4}')
	leaks=${leaks:-0}
	indirect=${indirect:-0}
	if [ "$leaks" = "0" ] && [ "$indirect" = "0" ]; then
		ok "$desc (no leaks)"
	else
		ko "$desc (definitely: $leaks, indirectly: $indirect)"
	fi
}

echo ""
printf "${BOLD}╔══════════════════════════════════════════════╗${NC}\n"
printf "${BOLD}║      miniRT Comprehensive Evaluation        ║${NC}\n"
printf "${BOLD}╚══════════════════════════════════════════════╝${NC}\n"

# ==========================================================
section "1. EXECUTABLE NAME & COMPILATION"
# ==========================================================

make fclean > /dev/null 2>&1

# Check no re-link
make > /dev/null 2>&1
if [ -f "./miniRT" ]; then
	ok "make produces miniRT executable"
else
	ko "make does not produce miniRT"
fi

# Check no re-link on second make
output=$(make 2>&1)
if echo "$output" | grep -q "Nothing to be done\|is up to date\|make\[1\]"; then
	relink_count=$(echo "$output" | grep -c "^cc ")
	if [ "$relink_count" -eq 0 ]; then
		ok "No re-link on second make"
	else
		ko "Re-link detected on second make ($relink_count cc calls)"
	fi
else
	ok "No re-link on second make"
fi

# ==========================================================
section "2. CONFIGURATION FILE VALIDATION"
# ==========================================================

# .rt extension check
test_error "scenes/eval_sphere" "" "Reject file without .rt extension" 2>/dev/null
echo "noformat" > /tmp/test_minirt.txt
test_error "/tmp/test_minirt.txt" "" "Reject .txt file"
rm -f /tmp/test_minirt.txt

# Error scenes
test_error "scenes/error_empty_file.rt" "Missing" "Reject empty file"
test_error "scenes/error_duplicate_ambient.rt" "Duplicate" "Reject duplicate ambient"
test_error "scenes/error_missing_camera.rt" "Missing" "Reject missing camera"
test_error "scenes/error_unknown_element.rt" "Unknown" "Reject unknown element"
test_error "scenes/error_negative_fov.rt" "FOV" "Reject negative FOV"
test_error "scenes/error_negative_color.rt" "Color" "Reject negative color"
test_error "scenes/error_alpha_in_color.rt" "Color" "Reject non-integer color"
test_error "scenes/error_orientation_out_of_range.rt" "Orientation" "Reject orientation out of range"
test_error "scenes/error_negative_sphere_diameter.rt" "diameter" "Reject negative sphere diameter"
test_error "scenes/error_zero_sphere_diameter.rt" "diameter" "Reject zero sphere diameter"
test_error "scenes/error_negative_cylinder_height.rt" "" "Reject negative cylinder height"
test_error "scenes/error_zero_cylinder_height.rt" "" "Reject zero cylinder height"
test_error "scenes/error_extra_token.rt" "" "Reject extra tokens"
test_error "scenes/error_double_comma.rt" "" "Reject double comma in values"
test_error "scenes/error_leading_comma.rt" "" "Reject leading comma"
test_error "scenes/error_trailing_comma.rt" "" "Reject trailing comma"
test_error "scenes/error_incomplete_color.rt" "" "Reject incomplete color"

# Non-existent file
test_error "scenes/nonexistent.rt" "" "Reject non-existent file"

# No arguments
output=$(timeout 2 ./miniRT 2>&1)
if echo "$output" | grep -q "Error"; then
	ok "Error on no arguments"
else
	ko "No error on missing arguments"
fi

# Too many arguments
output=$(timeout 2 ./miniRT scenes/eval_sphere.rt extra 2>&1)
if echo "$output" | grep -q "Error"; then
	ok "Error on too many arguments"
else
	ko "No error on too many arguments"
fi

# ==========================================================
section "3. BASIC SHAPES (render without crash)"
# ==========================================================

test_render "scenes/eval_sphere.rt" "Sphere at {0,0,0}"
test_render "scenes/eval_plane.rt" "Plane with z=0"
test_render "scenes/eval_cylinder.rt" "Cylinder along y-axis"

# ==========================================================
section "4. TRANSLATIONS & ROTATIONS"
# ==========================================================

test_render "scenes/eval_translation.rt" "Two spheres with translation"
test_render "scenes/eval_rotation.rt" "Cylinder with rotation"

# ==========================================================
section "5. MULTI-OBJECTS"
# ==========================================================

test_render "scenes/eval_multi_intersect.rt" "Intersecting objects"
test_render "scenes/eval_multi_objects.rt" "Multiple same-type objects (2sp+2cy+pl)"

# ==========================================================
section "6. CAMERA POSITION & DIRECTION"
# ==========================================================

test_render "scenes/eval_cam_x.rt" "Camera along X axis"
test_render "scenes/eval_cam_y.rt" "Camera along Y axis"
test_render "scenes/eval_cam_z.rt" "Camera along Z axis"
test_render "scenes/eval_cam_random.rt" "Camera at random position"

# ==========================================================
section "7. BRIGHTNESS 1/2 (Diffuse lighting)"
# ==========================================================

test_render "scenes/eval_brightness1.rt" "Sphere lit sideways"
test_render "scenes/eval_brightness2.rt" "Translated sphere lit sideways"

# ==========================================================
section "8. BRIGHTNESS 2/2 (Shadows)"
# ==========================================================

test_render "scenes/eval_shadow.rt" "Sphere shadow on plane"
test_render "scenes/eval_shadow_complex.rt" "Complex scene with shadows"

# ==========================================================
section "9. WINDOW MANAGEMENT"
# ==========================================================

# ESC key test
timeout 5 ./miniRT scenes/eval_sphere.rt &
pid=$!
sleep 2
if kill -0 "$pid" 2>/dev/null; then
	# Send ESC key via xdotool if available
	if command -v xdotool &>/dev/null; then
		xdotool key Escape 2>/dev/null
		sleep 1
		if ! kill -0 "$pid" 2>/dev/null; then
			ok "ESC key closes program"
		else
			kill "$pid" 2>/dev/null; wait "$pid" 2>/dev/null
			warn "ESC key test (xdotool may not have focused window)"
		fi
	else
		kill "$pid" 2>/dev/null; wait "$pid" 2>/dev/null
		warn "ESC key test skipped (xdotool not installed)"
	fi
else
	ko "Program crashed before ESC test"
fi

# ==========================================================
section "10. MEMORY LEAKS (Valgrind)"
# ==========================================================

test_valgrind "scenes/eval_sphere.rt" "Sphere scene"
test_valgrind "scenes/eval_cylinder.rt" "Cylinder scene"
test_valgrind "scenes/eval_multi_objects.rt" "Multi-objects scene"
test_valgrind "scenes/error_duplicate_ambient.rt" "Error scene (duplicate)"
test_valgrind "scenes/error_unknown_element.rt" "Error scene (unknown elem)"
test_valgrind "scenes/error_empty_file.rt" "Error scene (empty file)"

# ==========================================================
section "11. NORMINETTE"
# ==========================================================

norm_output=$(norminette src/ include/ 2>&1)
norm_errors=$(echo "$norm_output" | grep -c "Error")
if [ "$norm_errors" -eq 0 ]; then
	ok "Norminette: all files pass"
else
	ko "Norminette: $norm_errors error(s) found"
	echo "$norm_output" | grep "Error" | head -5
fi

# ==========================================================
section "12. SEGFAULT / CRASH TEST"
# ==========================================================

# Test with various malformed inputs
echo "" > /tmp/minirt_crash1.rt
test_error "/tmp/minirt_crash1.rt" "" "Empty content (whitespace only)"

echo "A 0.2 255,255,255" > /tmp/minirt_crash2.rt
test_error "/tmp/minirt_crash2.rt" "" "Only ambient (missing C, L)"

printf "A 0.2 255,255,255\nC 0,0,20 0,0,-1 70\nL 0,10,0 0.7 255,255,255\nsp 0,0,0 999999 255,0,0\n" > /tmp/minirt_crash3.rt
timeout 5 ./miniRT /tmp/minirt_crash3.rt &
pid=$!
sleep 2
if kill -0 "$pid" 2>/dev/null; then
	kill "$pid" 2>/dev/null; wait "$pid" 2>/dev/null
	ok "Huge sphere diameter: no crash"
else
	wait "$pid" 2>/dev/null
	ec=$?
	if [ "$ec" -eq 139 ] || [ "$ec" -eq 134 ]; then
		ko "Huge sphere diameter: CRASH (exit $ec)"
	else
		ok "Huge sphere diameter: handled (exit $ec)"
	fi
fi

rm -f /tmp/minirt_crash1.rt /tmp/minirt_crash2.rt /tmp/minirt_crash3.rt

# ==========================================================
# SUMMARY
# ==========================================================
echo ""
printf "${BOLD}╔══════════════════════════════════════════════╗${NC}\n"
printf "${BOLD}║               EVALUATION SUMMARY             ║${NC}\n"
printf "${BOLD}╠══════════════════════════════════════════════╣${NC}\n"
printf "║  ${GREEN}Pass: %-5d${NC}  ${RED}Fail: %-5d${NC}  ${YELLOW}Warn: %-5d${NC}       ║\n" "$PASS" "$FAIL" "$WARN"
printf "║  Total: %-38d║\n" "$TOTAL"
printf "${BOLD}╚══════════════════════════════════════════════╝${NC}\n"

if [ "$FAIL" -gt 0 ]; then
	exit 1
fi
exit 0
