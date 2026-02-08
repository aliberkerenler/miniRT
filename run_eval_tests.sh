#!/bin/bash

# Renk kodları
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

echo "=== MANDATORY PART OTO TEST BAŞLIYOR ==="

# 1. Compilation Test
echo -n "Checking compilation (make)... "
make re > /dev/null 2>&1
if [ $? -eq 0 ] && [ -f "./miniRT" ]; then
    echo -e "${GREEN}OK${NC}"
else
    echo -e "${RED}FAIL${NC}"
    exit 1
fi

# 2. Executable Name Test
echo -n "Checking executable name... "
if [ -f "miniRT" ]; then
    echo -e "${GREEN}OK${NC}"
else
    echo -e "${RED}FAIL${NC}"
    exit 1
fi

# 3. Norminette Check (Örnek, src ve include için)
echo "Checking Norminette (Mandatory)..."
if command -v norminette &> /dev/null; then
    norminette src/ include/ libft/ | grep "Error" > norm_errors.log
    if [ -s norm_errors.log ]; then
        echo -e "${RED}NORM ERRORS FOUND! Check norm_errors.log${NC}"
        # cat norm_errors.log # İsterseniz açabilirsiniz
    else
         echo -e "${GREEN}OK (No errors found)${NC}"
    fi
    rm -f norm_errors.log
else
    echo "Norminette not installed, skipping."
fi

# 4. Error Handling Tests
echo "Checking Error Handling..."
./miniRT > /dev/null 2>&1
if [ $? -ne 0 ]; then echo -e "  No args: ${GREEN}OK${NC}"; else echo -e "  No args: ${RED}FAIL${NC}"; fi

./miniRT not_exist.rt > /dev/null 2>&1
if [ $? -ne 0 ]; then echo -e "  Missing file: ${GREEN}OK${NC}"; else echo -e "  Missing file: ${RED}FAIL${NC}"; fi

./miniRT scenes/wrong_extension.txt > /dev/null 2>&1
if [ $? -ne 0 ]; then echo -e "  Wrong extension: ${GREEN}OK${NC}"; else echo -e "  Wrong extension: ${RED}FAIL${NC}"; fi

# 5. Visual Tests (Manuel kontrol gerektirir ama crash olmamalı)
echo "Running Visual Scenes (Press Ctrl+C to stop if stuck, or wait for auto-kill)..."

run_test() {
    SCENE=$1
    DESC=$2
    echo -n "  Testing $DESC ($SCENE)... "
    # Arka planda çalıştır, 1 saniye bekle, sonra kapat
    ./miniRT $SCENE > /dev/null 2>&1 &
    PID=$!
    sleep 0.5
    if ps -p $PID > /dev/null; then
        echo -e "${GREEN}Running (OK)${NC}"
        kill $PID
    else
        echo -e "${RED}CRASHED!${NC}"
    fi
}

run_test "scenes/test_shadow.rt" "Shadows"
run_test "scenes/test_multi_object.rt" "Multi-Objects"
run_test "scenes/test_translation.rt" "Translation"
run_test "scenes/test_rotation.rt" "Rotation"
run_test "scenes/test_brightness.rt" "Brightness"
run_test "scenes/cylinder_view3_top.rt" "Cylinder Caps"

echo "=== TEST COMPLETE ==="
echo "If all Visual Tests said 'Running (OK)', it means no Segfaults occurred."
echo "Please manually verify the images for correctness as per the Subject."
