#!/bin/bash

RED="\033[0;31m"
GREEN="\033[0;32m"
BLUE="\033[0;34m"
NC="\033[0m"

PROGRAM="../bin/c_test"

run_order_test() {
	local name="$1"
	shift

	echo -ne " ${BLUE}[ORDER TEST]${NC} $name ... "

	local output=$($PROGRAM "$@" 2>/dev/null)
	local exit_code=$?

	if [[ $exit_code -ne 0 ]]; then
		echo -e "${RED}Test failed${NC}"
		return
	fi

	local numbers=($(echo "$output" | grep "Number:" | awk '{print $2}'))

	if [[ ${#numbers[@]} -eq 0 ]]; then
		echo -e "${RED}FAIL (no output)${NC}"
		return
	fi

	for i in $(seq 0 $((${#numbers[@]} - 2))); do
		if [[ ${numbers[$i]} -gt ${numbers[$i+1]} ]]; then
			echo -e "${RED}FAIL (not sorted)${NC}"
			return
		fi
	done

	local found_positive=false
	for num in "${numbers[@]}"; do
		if [[ $num -ge 0 ]]; then
			found_positive=true
		elif [[ $found_positive == true ]]; then
			echo -e "${RED}FAIL (negative after positive)${NC}"
			return
		fi
	done
	
	echo -e "${GREEN}PASS${NC}"
}

run_order_test "Small test" "11" "11"
run_order_test "100 numbers on 100 threads" "100" "100"
run_order_test "50 numbers on 50 threads" "50" "50"
run_order_test "2 numbers on 2 threads" "2" "2"
