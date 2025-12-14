#!/bin/bash

RED="\033[0;31m"
GREEN="\033[0;32m"
BLUE="\033[0;34m"
NC="\033[0m"

PROGRAM="../bin/c_test"

run_test() {
	local name="$1"
	shift

	echo -ne " ${BLUE}[LEAK TEST]${NC} $name ... "

	valgrind --leak-check=full --error-exitcode=1 \
			--quiet \
			$PROGRAM "$@" > /dev/null 2>&1

	local exit_code=$?

	if [[ $exit_code -eq 0 ]]; then
		echo -e "${GREEN}No Leaks${NC}"
	else
		echo -e "${RED}Memory Leak detected${NC}"
	fi
}

run_test "Small input" "2" "1"
run_test "100 numbers per thread with 10 threads" "10" "100"
run_test "10 numbers per thread with 10 threads" "10" "10"
run_test "42 numbers per thread with 42 threads" "42" "42"
run_test "1 number per thread with 42 threads" "42" "1"
run_test "42 numbers per thread with 1 thread" "1" "42"