#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

PASS=0
FAIL=0
TOTAL=0

echo "========================================="
echo "  miniRT Valgrind Memory Leak Test"
echo "========================================="
echo ""

for scene in scenes/*.rt; do
	TOTAL=$((TOTAL + 1))
	name=$(basename "$scene")
	output=$(valgrind --leak-check=full --errors-for-leak-kinds=all \
		timeout 3 ./miniRT "$scene" 2>&1)

	leaks=$(echo "$output" | grep "definitely lost:" | awk '{gsub(/,/,"",$4); print $4}')
	indirect=$(echo "$output" | grep "indirectly lost:" | awk '{gsub(/,/,"",$4); print $4}')
	errors=$(echo "$output" | grep "ERROR SUMMARY:" | awk '{gsub(/,/,"",$4); print $4}')
	leaks=${leaks:-0}
	indirect=${indirect:-0}
	errors=${errors:-0}

	if [ "$leaks" = "0" ] && [ "$indirect" = "0" ]; then
		printf "${GREEN}[OK]${NC}  %-45s leaks: %s  errors: %s\n" "$name" "$leaks" "$errors"
		PASS=$((PASS + 1))
	else
		printf "${RED}[KO]${NC}  %-45s leaks: %s  indirect: %s  errors: %s\n" "$name" "$leaks" "$indirect" "$errors"
		FAIL=$((FAIL + 1))
	fi
done

echo ""
echo "========================================="
printf "Total: %d  ${GREEN}Pass: %d${NC}  ${RED}Fail: %d${NC}\n" "$TOTAL" "$PASS" "$FAIL"
echo "========================================="

if [ "$FAIL" -gt 0 ]; then
	exit 1
fi
exit 0
