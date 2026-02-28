#!/bin/bash

# Renk kodları
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
MAGENTA='\033[0;35m'
BOLD='\033[1m'
NC='\033[0m'

AUTO=0
STRICT_VALGRIND=0
if [ "$1" == "--auto" ]; then
    AUTO=1
    echo -e "${MAGENTA}${BOLD}⚡ OTOMATİK MOD AKTİF (Sadece çökme/sızıntı testi, pencereler hızlı kapanacak) ⚡${NC}"
fi
if [ "$2" == "--valgrind" ] || [ "$1" == "--valgrind" ]; then
    STRICT_VALGRIND=1
    echo -e "${MAGENTA}${BOLD}🕵️ SIKI VALGRIND MODU AKTİF (Her sahnede tam hafıza kontrolü) 🕵️${NC}"
fi

PASS=0
FAIL=0
WARN=0
TOTAL=0

ok()   { PASS=$((PASS+1)); TOTAL=$((TOTAL+1)); printf "  ${GREEN}[OK]${NC}   %s\n" "$1"; }
ko()   { FAIL=$((FAIL+1)); TOTAL=$((TOTAL+1)); printf "  ${RED}[KO]${NC}   %s\n" "$1"; }
warn() { WARN=$((WARN+1)); TOTAL=$((TOTAL+1)); printf "  ${YELLOW}[UYARI]${NC} %s\n" "$1"; }
section() { echo ""; printf "${BOLD}${CYAN}━━━ %s ━━━${NC}\n" "$1"; }

TMP_DIR="/tmp/minirt_hard_tests"
mkdir -p "$TMP_DIR"

test_render() {
	local scene="$1"
	local short_desc="$2"
	local view_seconds=15
    if [ $AUTO -eq 1 ]; then
        view_seconds=1
    fi

	printf "  ${YELLOW} ▷ Test:${NC} ${short_desc}\n"
    
    local cmd="./miniRT $scene"
    if [ $STRICT_VALGRIND -eq 1 ]; then
        cmd="valgrind --leak-check=full --errors-for-leak-kinds=all ./miniRT $scene"
    fi

	$cmd > /dev/null 2>&1 &
	local pid=$!
	sleep 1

	if ! kill -0 "$pid" 2>/dev/null; then
		wait "$pid" 2>/dev/null
		local exit_code=$?
		if [ "$exit_code" -eq 139 ]; then
            ko "SEGFAULT (Çökme) tespit edildi!"
		else
            ko "Beklenmedik çıkış (Kod: $exit_code)"
        fi
		return 1
	fi

    if [ $AUTO -eq 0 ]; then
	    printf "    ${GREEN}Pencere açık (${view_seconds}s):${NC} "
	    local i=$view_seconds
	    while [ $i -gt 0 ]; do
		    printf "${BOLD}%2d${NC}" $i
		    sleep 1
		    printf "\b\b"
		    i=$((i - 1))
		    if ! kill -0 "$pid" 2>/dev/null; then
			    printf " \n"
			    warn "Pencere erken kapandı."
			    return 0
		    fi
	    done
	    printf " 0\n"
    fi

	kill -9 "$pid" 2>/dev/null
	wait "$pid" 2>/dev/null
	ok "Render başarılı (Çökme yok)"
	return 0
}

tetest_error() {
	local scene="$1"
	local desc="$2"
	local output
	output=$(timeout 2 ./miniRT "$scene" 2>&1)
	if echo "$output" | grep -qi "Error"; then
        ok "$desc"
	else
        ko "$desc (Hata mesajı eksik veya program çöktü)"
    fi
}

create_invalid() {
    echo -e "$2" > "$TMP_DIR/$1.rt"
    tetest_error "$TMP_DIR/$1.rt" "$3"
}

create_valid() {
    echo -e "$2" > "$TMP_DIR/$1.rt"
    test_render "$TMP_DIR/$1.rt" "$3"
}

echo ""
printf "${BOLD}╔══════════════════════════════════════════════╗${NC}\n"
printf "${BOLD}║    MINIRT HARDCORE EVALUATION SCRIPT v2.0    ║${NC}\n"
printf "${BOLD}╚══════════════════════════════════════════════╝${NC}\n"
echo "Kullanım: ./advanced_eval.sh [--auto] [--valgrind]"

section "1. NORM VE DERLEME (SIKI KONTROL)"
make fclean > /dev/null 2>&1
make > /dev/null 2>&1
if [ -f "./miniRT" ]; then
    ok "Derleme başarılı"
else
    ko "Derleme hatası"
    exit 1
fi

if ! command -v norminette &> /dev/null; then
	warn "Norminette yüklü değil"
else
	if norminette src/ include/ | grep -q "Error"; then
        ko "Norm hatası var!"
    else
        ok "Norminette kusursuz"
    fi
fi

section "2. PARSER STRESS TESTLERİ (Hata Fırlatmalı)"
create_invalid "no_perm" "A 0.2 255,255,255\nC 0,0,0 0,0,1 70" "Okuma izni olmayan dosya"
chmod 000 "$TMP_DIR/no_perm.rt"
tetest_error "$TMP_DIR/no_perm.rt" "Okuma izni olmayan dosya"

mkdir -p "$TMP_DIR/dir_test.rt"
tetest_error "$TMP_DIR/dir_test.rt" "Dosya yerine klasör verilmesi"

create_invalid "double_dot" "A 0.2 255,255,255" "Uzantı kontrolü (double_dot.rt.txt)"
mv "$TMP_DIR/double_dot.rt" "$TMP_DIR/double_dot.rt.txt"
tetest_error "$TMP_DIR/double_dot.rt.txt" "Yanlış uzantılı dosya (.rt.txt)"

create_valid "tabs_and_spaces" "A \t 0.2 \t 255,255,255\nC\t 0,0,0 \t0,1,0 \t 70\nL \t0,0,0\t0.5\t255,255,255" "Tab ve boşluk karışımı (GEREKLİ elementleri var, format esnekse pass verebilir)"
tetest_error "eval_scenes/nonexistent_file_eval.rt" "Olmayan dosya testi"

create_invalid "color_overflow" "A 0.2 256,0,0\nC 0,0,0 0,1,0 70" "Renk taşması (256)"
create_invalid "color_negative" "A 0.2 -1,0,0\nC 0,0,0 0,1,0 70" "Renk negatif (-1)"
create_invalid "vector_overflow" "A 0.2 255,255,255\nC 0,0,0 0,2,0 70" "Yönektör taşması (0,2,0)"
create_invalid "fov_overflow" "A 0.2 255,255,255\nC 0,0,0 0,1,0 181" "FOV taşması (181)"
create_invalid "missing_commas" "A 0.2 255 255 255\nC 0,0,0 0,1,0 70" "Eksik virgül (255 255 255)"
create_invalid "char_in_number" "A 0.2 255,25a,255\nC 0,0,0 0,1,0 70" "Sayı içinde harf"

section "3. ZORLU RENDER (MATEMATİK UÇ NOKTALARI)"
create_valid "cam_inside_sphere" "A 0.2 255,255,255\nC 0,0,0 0,1,0 70\nL 0,50,0 0.8 255,255,255\nsp 0,0,0 50 255,0,0" "Kamera kürenin İÇİNDE (Çökmemeli, ortam ışığı -koyu kırmızı- veya yüzey görünmeli)"
create_valid "light_inside_sphere" "A 0.2 255,255,255\nC 0,-100,0 0,1,0 70\nL 0,0,0 0.8 255,255,255\nsp 0,0,0 50 255,0,0" "Işık kürenin İÇİNDE (Çökmemeli, ışın sınırını aştığı için parlak kırmızı görünebilir)"

create_valid "huge_numbers" "A 0.2 255,255,255\nC 0,0,-10000 0,0,1 70\nL 0,10000,-5000 0.8 255,255,255\nsp 0,0,10000 5000 255,0,0" "Çok büyük koordinatlar ve çaplar (Taşma/Çökme testi)"

create_valid "tiny_numbers" "A 0.2 255,255,255\nC 0,-0.01,0 0,1,0 70\nL -0.1,-0.1,0.1 0.8 255,255,255\nsp 0,0,0 0.005 255,0,0" "Çok küçük koordinatlar (Hassasiyet/Float testi)"

create_valid "parallel_cylinder" "A 0.2 255,255,255\nC 0,-50,0 0,1,0 70\nL -50,-50,50 0.8 255,255,255\ncy 0,0,0 0,1,0 10 50 0,0,255" "Kamera silindirin tam eksenine paralel bakıyor (Kapakları görmeli)"

create_valid "many_objects" "A 0.2 255,255,255\nC 0,-40,10 0,1,0 70\nL 0,-20,20 0.8 255,255,255\npl 0,0,0 0,0,1 200,200,200\ncy 0,25,10 0,0,1 10 20 0,255,255\nsp 0,10,10 8 255,0,0\ncy -15,10,5 0,1,0 6 20 255,0,255\nsp 15,10,5 6 0,255,0" "Farklı türde çoklu obje render testi (Kırmızı küre silindire gölge düşürmeli)"
echo ""
printf "${BOLD}╔══════════════════════════════════════════════╗${NC}\n"
printf "${BOLD}║              DEĞERLENDİRME ÖZETİ             ║${NC}\n"
printf "${BOLD}╠══════════════════════════════════════════════╣${NC}\n"
printf "║  ${GREEN}Başarılı: %-5d${NC} ${RED}Başarısız: %-5d${NC} ${YELLOW}Uyarı: %-5d${NC}  ║\n" "$PASS" "$FAIL" "$WARN"
printf "║  Toplam Test: %-33d║\n" "$TOTAL"
printf "${BOLD}╚══════════════════════════════════════════════╝${NC}\n"

rm -rf "$TMP_DIR"

if [ "$FAIL" -gt 0 ]; then
	echo -e "${RED}❌ Bazı Hardcore testler başarısız oldu. Logları incele.${NC}"
	exit 1
fi
echo -e "${GREEN}✅ TEBRİKLER! Tüm Hardcore testleri başarıyla geçtin!${NC}"
exit 0
