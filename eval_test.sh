#!/bin/bash

# Renk kodları
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
BOLD='\033[1m'
NC='\033[0m' # No Color

# Sayaçlar
PASS=0
FAIL=0
WARN=0
TOTAL=0

# Helper fonksiyonlar
ok()   { PASS=$((PASS+1)); TOTAL=$((TOTAL+1)); printf "  ${GREEN}[OK]${NC}   %s\n" "$1"; }
ko()   { FAIL=$((FAIL+1)); TOTAL=$((TOTAL+1)); printf "  ${RED}[KO]${NC}   %s\n" "$1"; }
warn() { WARN=$((WARN+1)); TOTAL=$((TOTAL+1)); printf "  ${YELLOW}[UYARI]${NC} %s\n" "$1"; }
section() { echo ""; printf "${BOLD}${CYAN}━━━ %s ━━━${NC}\n" "$1"; }

# --- Bir sahnenin çökmeden render edilip edilmediğini test et ---
test_render() {
	local scene="$1"
	local short_desc="$2"
	local long_desc="$3"
	local view_seconds=15

	# Detaylı açıklamayı testten ÖNCE yazdır
	printf "  ${YELLOW} ▷ Test:${NC} ${short_desc}\n"
	printf "    ${CYAN}Beklenen Görüntü:${NC} ${long_desc}\n"

	# Programı arka planda başlat (timeout YOK, pencere açık kalsın)
	./miniRT "$scene" &
	local pid=$!

	# Pencerenin açılması için 2 saniye bekle
	sleep 2

	# Program hala çalışıyor mu kontrol et
	if ! kill -0 "$pid" 2>/dev/null; then
		wait "$pid" 2>/dev/null
		local exit_code=$?
		if [ "$exit_code" -eq 139 ] || [ "$exit_code" -eq 134 ] || [ "$exit_code" -eq 136 ]; then
			ko "Render işlemi ÇÖKTÜ (çıkış kodu $exit_code)"
		else
			ko "Render işlemi beklenmedik şekilde sonlandı (çıkış kodu $exit_code)"
		fi
		return 1
	fi

	# Pencere açık, geri sayım göster
	printf "    ${GREEN}Pencere açık - inceleme için ${view_seconds} saniye:${NC} "
	local i=$view_seconds
	while [ $i -gt 0 ]; do
		printf "${BOLD}%2d${NC}" $i
		sleep 1
		printf "\b\b"
		i=$((i - 1))
		# Her saniye programın hala çalışıp çalışmadığını kontrol et
		if ! kill -0 "$pid" 2>/dev/null; then
			printf "   \n"
			warn "Pencere bekleme sırasında kapandı (ESC ile mi kapatıldı?)"
			return 0
		fi
	done
	printf " 0\n"

	# 15 saniye doldu, programı sonlandır
	kill "$pid" 2>/dev/null
	wait "$pid" 2>/dev/null
	ok "Render işlemi başarıyla tamamlandı."
	return 0
}

# --- Hatalı bir sahnenin "Error" mesajı ile sonlandığını test et ---
test_error() {
	local scene="$1"
	local desc="$2"
	local output
	# Programı 3 saniye zaman aşımı ile çalıştır ve çıktısını yakala
	output=$(timeout 15 ./miniRT "$scene" 2>&1)
	# Çıktıda "Error" kelimesinin olup olmadığını kontrol et
	if echo "$output" | grep -q "Error"; then
		ok "$desc"
	else
		ko "$desc (Hata mesajı alınamadı)"
	fi
}

# --- Valgrind ile hafıza kaçağı kontrolü ---
test_valgrind() {
	local scene="$1"
	local desc="$2"
	# Valgrind'in kurulu olup olmadığını kontrol et
	if ! command -v valgrind &> /dev/null; then
		warn "Valgrind testi atlandı ('valgrind' komutu bulunamadı)"
		return
	fi
	local output
	output=$(valgrind --leak-check=full --errors-for-leak-kinds=all \
		timeout 5 ./miniRT "$scene" 2>&1)
	# "definitely lost" ve "indirectly lost" sızıntılarını kontrol et
	local leaks=$(echo "$output" | grep "definitely lost:" | awk '{gsub(/,/,"",$4); print $4}')
	local indirect=$(echo "$output" | grep "indirectly lost:" | awk '{gsub(/,/,"",$4); print $4}')
	leaks=${leaks:-0}
	indirect=${indirect:-0}
	if [ "$leaks" = "0" ] && [ "$indirect" = "0" ]; then
		ok "$desc (Sızıntı yok)"
	else
		ko "$desc (definitely: $leaks, indirectly: $indirect)"
	fi
}

echo ""
printf "${BOLD}╔══════════════════════════════════════════════╗${NC}\n"
printf "${BOLD}║      miniRT Kapsamlı Değerlendirme Testi     ║${NC}\n"
printf "${BOLD}╚══════════════════════════════════════════════╝${NC}\n"

# ==========================================================
section "1. DERLEME VE EXECUTABLE KONTROLÜ"
# ==========================================================

make fclean > /dev/null 2>&1
make > /dev/null 2>&1
if [ -f "./miniRT" ]; then
	ok "'make' komutu 'miniRT' dosyasını oluşturdu"
else
	ko "'make' komutu 'miniRT' dosyasını oluşturmadı"
	exit 1
fi

# İkinci 'make' komutunda yeniden linkleme olup olmadığını kontrol et
output=$(make 2>&1)
if echo "$output" | grep -q "Nothing to be done\|is up to date\|için yapılacak bir şey yok"; then
	ok "İkinci 'make' komutunda gereksiz derleme yapılmadı"
else
	ko "İkinci 'make' komutunda yeniden derleme tespit edildi"
fi

# ==========================================================
section "2. YAPILANDIRMA DOSYASI DOĞRULAMASI"
# ==========================================================

test_error "scenes/error_empty_file.rt" "Boş dosya reddedildi"
test_error "scenes/error_duplicate_ambient.rt" "Tekrarlanan Ambient (A) reddedildi"
test_error "scenes/error_missing_camera.rt" "Eksik Kamera (C) reddedildi"
test_error "scenes/error_unknown_element.rt" "Bilinmeyen eleman türü reddedildi"
test_error "scenes/error_negative_fov.rt" "Negatif FOV reddedildi"
test_error "scenes/error_negative_color.rt" "Negatif renk değeri reddedildi"
test_error "scenes/error_orientation_out_of_range.rt" "Aralık dışı oryantasyon vektörü reddedildi"
test_error "scenes/error_negative_sphere_diameter.rt" "Negatif küre çapı reddedildi"
test_error "scenes/nonexistent.rt" "Var olmayan dosya reddedildi"
test_error "./miniRT" "Argümansız çalıştırma reddedildi"
test_error "./miniRT scenes/chess.rt extra_arg" "Fazla argüman ile çalıştırma reddedildi"

# ==========================================================
section "3. TEMEL ŞEKİLLER (çökme olmadan render)"
# ==========================================================

test_render "eval_scenes/01_basic_sphere.rt" "Temel Küre" "Ekranın ortasında, sol üstten aydınlatılmış tek bir KIRMIZI KÜRE."
test_render "eval_scenes/02_basic_plane.rt" "Temel Düzlem" "Tüm ekranı kaplayan, sonsuz bir YEŞİL DÜZLEM."
test_render "eval_scenes/03_basic_cylinder.rt" "Temel Silindir" "Ekranın ortasında dikey olarak duran MAVİ bir SİLİNDİR."

# ==========================================================
section "4. ÖTELEME VE DÖNDÜRME"
# ==========================================================

test_render "eval_scenes/04_trans_spheres.rt" "Ötelenmiş Küreler" "Biri yakın (yeşil), diğeri uzak (kırmızı) iki küre dikey olarak hizalı."
test_render "eval_scenes/05_rot_cylinder.rt" "Döndürülmüş Silindir" "Ortada yatay olarak duran PEMBE bir SİLİNDİR."

# ==========================================================
section "5. ÇOKLU OBJELER"
# ==========================================================

test_render "eval_scenes/06_multi_intersect.rt" "Kesişen Objeler" "Büyük bir kırmızı küre ve içinden dikey geçen yeşil bir silindir."
test_render "eval_scenes/07_multi_same.rt" "Aynı Türden Çoklu Objeler" "Altta gri düzlem, üstünde 2 küre (kırmızı, yeşil) ve 2 silindir (mavi, sarı)."

# ==========================================================
section "6. KAMERA POZİSYONU VE YÖNÜ"
# ==========================================================

test_render "eval_scenes/08_cam_x.rt" "Kamera X Ekseninde" "Kırmızı küreye yan taraftan bakış. Altında düzlem görünür."
test_render "eval_scenes/09_cam_y.rt" "Kamera Y Ekseninde" "Kırmızı küreye tam karşıdan bakış (Y derinlik ekseni). Altında düzlem görünür."
test_render "eval_scenes/10_cam_z.rt" "Kamera Z Ekseninde" "Kırmızı küreye tam tepeden bakış (Z yukarı ekseni). Küre daire gibi görünür."
test_render "eval_scenes/11_cam_rand.rt" "Rastgele Kamera Pozisyonu" "Kırmızı küreye sağ üst çaprazdan bakış."

# ==========================================================
section "7. AYDINLATMA (IŞIK)"
# ==========================================================

test_render "eval_scenes/12_light_side.rt" "Yandan Aydınlatılmış Küre" "Kırmızı kürenin sol tarafı parlak, sağ tarafı gölgede."
test_render "eval_scenes/13_light_trans.rt" "Ötelenmiş ve Yandan Aydınlatılmış Küre" "Yukarı ötelenmiş kırmızı kürenin yine sol tarafı parlak."

# ==========================================================
section "8. GÖLGELER"
# ==========================================================

test_render "eval_scenes/14_shadow_basic.rt" "Düzlem Üzerinde Basit Gölge" "Kırmızı kürenin, altındaki gri düzlem üzerine düşen yuvarlak gölgesi."
test_render "eval_scenes/15_shadow_complex.rt" "Karmaşık Sahnede Gölgeler" "Birden fazla objenin (küreler, silindir) birbirleri ve zemin üzerine düşen gölgeleri."

# ==========================================================
section "9. HAFIZA KAÇAĞI KONTROLÜ (Valgrind)"
# ==========================================================

test_valgrind "eval_scenes/01_basic_sphere.rt" "Basit sahne"
test_valgrind "eval_scenes/07_multi_same.rt" "Karmaşık sahne"
test_valgrind "scenes/error_unknown_element.rt" "Hatalı sahne"

# ==========================================================
section "10. NORMINETTE"
# ==========================================================

if ! command -v norminette &> /dev/null; then
	warn "Norminette testi atlandı ('norminette' komutu bulunamadı)"
else
	norm_output=$(norminette src/ include/ 2>&1)
	norm_errors=$(echo "$norm_output" | grep -c "Error")
	if [ "$norm_errors" -eq 0 ]; then
		ok "Norminette: Tüm dosyalarda hata bulunamadı"
	else
		ko "Norminette: $norm_errors hata bulundu"
		echo "$norm_output" | grep "Error" | head -5
	fi
fi

# ==========================================================
# ÖZET
# ==========================================================
echo ""
printf "${BOLD}╔══════════════════════════════════════════════╗${NC}\n"
printf "${BOLD}║              DEĞERLENDİRME ÖZETİ             ║${NC}\n"
printf "${BOLD}╠══════════════════════════════════════════════╣${NC}\n"
printf "║  ${GREEN}Başarılı: %-5d${NC} ${RED}Başarısız: %-5d${NC} ${YELLOW}Uyarı: %-5d${NC}  ║\n" "$PASS" "$FAIL" "$WARN"
printf "║  Toplam Test: %-33d║\n" "$TOTAL"
printf "${BOLD}╚══════════════════════════════════════════════╝${NC}\n"

if [ "$FAIL" -gt 0 ]; then
	exit 1
fi
exit 0
