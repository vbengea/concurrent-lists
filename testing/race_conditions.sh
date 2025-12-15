#!/bin/bash

RED="\033[0;31m"
GREEN="\033[0;32m"
BLUE="\033[0;34m"
NC="\033[0m"

PROGRAM="../bin/c_test"

run_test() {
	local name="$1"
	shift

	echo -ne " ${BLUE}[RACE CONDITION TEST]${NC} $name ... "

	valgrind --tool=helgrind --error-exitcode=1 \
			--quiet \
			$PROGRAM "$@" > /dev/null 2>&1

	local exit_code=$?

	if [[ $exit_code -eq 0 ]]; then
		echo -e "${GREEN}No race conditions${NC}"
	else
		echo -e "${RED}Race condition detected${NC}"
	fi
}

run_test "Small input" "2" "10"
run_test "Multiple threads" "4" "50"
run_test "Many threads" "50" "100"
run_test "Max threads" "999" "100"