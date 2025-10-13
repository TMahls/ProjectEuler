#!/bin/bash

cd ~/Documents/Coding\ Projects/ProjectEuler

# Take an input of the problem number
PROBLEM_NUMBER="$1"

# Define usage function
usage() {
	echo "Usage: ./runProblem.sh [Problem Number] [-n|--noLibCompile] [-v|--verifyAns]"
	echo "  Problem Number -- usually just an integer, but you can specify a bonus problem with bonus_[name]"
	echo "  -n|--noLibCompile: Euler utils lib will not be re-compiled"
	echo "  -v|--verifyAns: Answer will be checked against answer key"
	exit 1
}

SKIP_LIB=0
VERIFY=0

while [[ $# -gt 1 ]]; do
	case "$2" in
		-n | --noLibCompile)
			SKIP_LIB=1
			shift
			;;
		-v | --verifyAns)
			VERIFY=1
			shift
			;;
		-h | --help)
			usage
			;;
		*)
			echo "Unknown option: $2"
			usage
			;;
	esac
done

# Determine number of leading 0's in problemX.cpp
if [[ "$PROBLEM_NUMBER" =~ ^bonus ]]; then
	LEADING_ZEROS=""
else
	if [ $PROBLEM_NUMBER -ge 1000 ]; then
		LEADING_ZEROS=""
	elif [ $PROBLEM_NUMBER -ge 100 ]; then
		LEADING_ZEROS="0"
	elif [ $PROBLEM_NUMBER -ge 10 ]; then
		LEADING_ZEROS="00"
	else
		LEADING_ZEROS="000"
	fi
fi

# Search for problemX.cpp
if [ ! -f "./ProblemSource/$LEADING_ZEROS$PROBLEM_NUMBER.cpp" ]; then
	echo "File \"ProblemSource/$LEADING_ZEROS$PROBLEM_NUMBER.cpp\" does not exist."
	usage
else
	# If it exists, build it with g++ (use timer wrapper main)
	echo "Found Problem $PROBLEM_NUMBER file, compiling library..."

	WarningFlags="-std=c++14 -Wall -Wextra -Werror -pedantic-errors"

	# Library compilation is optional
	if [ $SKIP_LIB -eq 0 ]; then
		cd libEulerUtils
		g++ $WarningFlags -c eulerUtils.cpp -o eulerUtils.o
		STATUS=$?
		g++ $WarningFlags -c BigInt.cpp -o BigInt.o
		ar rcs libeulerUtils.a eulerUtils.o BigInt.o
		cd ..
	else
		echo "-- Skipping library compilation from provided flag --"
		STATUS=0
	fi

	if [ $STATUS -eq 0 ]; then
		echo "Library compile complete. Compiling problem..."

		GPPFlags="-D PROBLEM_NUM=$PROBLEM_NUMBER"
		if [ $VERIFY -eq 1 ]; then # Add verify macro
			GPPFlags="$GPPFlags -D VERIFY_ANSWER=1"
		fi

		LibFlags="-I ./libEulerUtils -L ./libEulerUtils -l eulerUtils"
		g++ $WarningFlags $GPPFlags ./ProblemSource/$LEADING_ZEROS$PROBLEM_NUMBER.cpp \
			mainWrapper.cpp $LibFlags -o mainWrapper.out

		STATUS=$?
		if [ $STATUS -eq 0 ]; then
			# Execute the file
			echo "Executing problem file..."
			./mainWrapper.out
		fi
	fi
fi
