#!/bin/bash

RED="\033[0;31m"
GREEN="\033[0;32m"
BLUE="\033[0;34m"
NC="\033[0m"

PROGRAM="../bin/c_test"

run_test() {
	local name="$1"
	shift

	echo -ne " ${BLUE}[INVALID INPUTTEST]${NC} $name ... "

	$PROGRAM "$@" > /dev/null 2>&1
	local exit_code=$?

	if [[ $exit_code -eq 1 || $exit_code -eq 2 || $exit_code -eq 3 ]]; then
		echo -e "${GREEN}Test passed${NC}"
	else
		echo -e "${RED}Test failed${NC}"
	fi
}

run_test "Invalid input" "0" "11"
run_test "Invalid input" "11" "0"
run_test "Invalid input" "-" "1"
run_test "Invalid input" "1" "-"
run_test "Invalid input" "-0" "10"
run_test "Invalid input" "22" "-0"
run_test "Invalid input" "-43745754754745" "+345643634634634"
run_test "Invalid input" "4eferg3745754754745" "+345643634634634"
run_test "Invalid input" "-43745754754745" "34564rgregre3634634634"
run_test "Invalid input" "45545475443745754754745" "34565464565465465465464565443634634634"
run_test "Invalid input" "+11" "+0"
run_test "Invalid input" "ABC" "234"
run_test "Invalid input" "11" "ABC"
run_test "Invalid input" "sdgggds" "45"
run_test "Invalid input" "?" "42"
run_test "Invalid input" "^" ","
run_test "Invalid input" "42" "42" "42"
