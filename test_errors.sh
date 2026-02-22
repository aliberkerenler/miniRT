#!/bin/bash

# miniRT Error Handling Test Script
# Bu script tüm hata senaryolarını test eder

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

PASS=0
FAIL=0

echo "========================================"
echo "   miniRT Error Handling Tests"
echo "========================================"
echo ""

test_error() {
    local file=$1
    local description=$2
    
    printf "%-45s" "Testing: $description"
    
    ./miniRT "$file" 2>&1 > /dev/null
    exit_code=$?
    
    if [ $exit_code -ne 0 ]; then
        echo -e " ${GREEN}[PASS]${NC} (exit: $exit_code)"
        ((PASS++))
    else
        echo -e " ${RED}[FAIL]${NC} (exit: $exit_code - should fail)"
        ((FAIL++))
    fi
}

# Uzantı hatası
test_error "scenes/error_invalid_extension.txt" ".txt extension (not .rt)"

# Var olmayan dosya
test_error "scenes/nonexistent_file.rt" "Non-existent file"

# Boş dosya
test_error "scenes/error_empty_file.rt" "Empty file"

# Eksik elemanlar
test_error "scenes/error_missing_ambient.rt" "Missing Ambient (A)"
test_error "scenes/error_missing_camera.rt" "Missing Camera (C)"
test_error "scenes/error_missing_light.rt" "Missing Light (L)"

# Tekrarlanan elemanlar
test_error "scenes/error_duplicate_ambient.rt" "Duplicate Ambient"
test_error "scenes/error_duplicate_camera.rt" "Duplicate Camera"
test_error "scenes/error_duplicate_light.rt" "Duplicate Light"

# Geçersiz format
test_error "scenes/error_invalid_ambient_format.rt" "Invalid Ambient format"
test_error "scenes/error_invalid_camera_format.rt" "Invalid Camera format"
test_error "scenes/error_invalid_light_format.rt" "Invalid Light format"
test_error "scenes/error_invalid_sphere_format.rt" "Invalid Sphere format"
test_error "scenes/error_invalid_plane_format.rt" "Invalid Plane format"
test_error "scenes/error_invalid_cylinder_format.rt" "Invalid Cylinder format"

# Geçersiz değerler
test_error "scenes/error_invalid_ambient_ratio.rt" "Ambient ratio > 1.0"
test_error "scenes/error_negative_ambient_ratio.rt" "Ambient ratio < 0"
test_error "scenes/error_invalid_light_brightness.rt" "Light brightness > 1.0"
test_error "scenes/error_negative_light_brightness.rt" "Light brightness < 0"
test_error "scenes/error_invalid_fov.rt" "FOV > 180"
test_error "scenes/error_negative_fov.rt" "FOV < 0"

# Renk hataları
test_error "scenes/error_invalid_color.rt" "Color value > 255"
test_error "scenes/error_negative_color.rt" "Color value < 0"
test_error "scenes/error_incomplete_color.rt" "Incomplete color (2 values)"

# Vektör hatası
test_error "scenes/error_incomplete_vector.rt" "Incomplete vector (2 values)"

# Bilinmeyen eleman
test_error "scenes/error_unknown_element.rt" "Unknown element (cube)"

# Negatif/sıfır boyutlar
test_error "scenes/error_negative_sphere_diameter.rt" "Negative sphere diameter"
test_error "scenes/error_zero_sphere_diameter.rt" "Zero sphere diameter"
test_error "scenes/error_negative_cylinder_diameter.rt" "Negative cylinder diameter"
test_error "scenes/error_negative_cylinder_height.rt" "Negative cylinder height"
test_error "scenes/error_zero_cylinder_diameter.rt" "Zero cylinder diameter"
test_error "scenes/error_zero_cylinder_height.rt" "Zero cylinder height"

echo ""
echo "========================================"
echo "   Results"
echo "========================================"
echo -e "Passed: ${GREEN}$PASS${NC}"
echo -e "Failed: ${RED}$FAIL${NC}"
echo "Total:  $((PASS + FAIL))"
echo ""

if [ $FAIL -eq 0 ]; then
    echo -e "${GREEN}All error handling tests passed!${NC}"
    exit 0
else
    echo -e "${RED}Some tests failed!${NC}"
    exit 1
fi
