#!/bin/bash

# CD to the directory of this script
cd "$(dirname "$(readlink -f "$0")")"

# 2 Inputs - Lower bound, upper bound
LOWER_BOUND="$1"
UPPER_BOUND="$2"

if [ -z "$LOWER_BOUND" ]; then
	LOWER_BOUND=0
fi

if [ -z "$UPPER_BOUND" ]; then
	UPPER_BOUND=1000
fi


# Run all problems to see if they compile.
# This can help detect breakages in tne euler utils lib

# Re-compiles the lib for the first problem only.
COMPILED_LIB=0

for ((i=$LOWER_BOUND; i<=$UPPER_BOUND; i++)); do

	# Determine number of leading 0's in problemX.cpp
	if [ $i -ge 1000 ]; then
		LEADING_ZEROS=""
	elif [ $i -ge 100 ]; then
		LEADING_ZEROS="0"
	elif [ $i -ge 10 ]; then
		LEADING_ZEROS="00"
	else
		LEADING_ZEROS="000"
	fi

	if [ -f "./ProblemSource/$LEADING_ZEROS$i.cpp" ]; then
		if [ $COMPILED_LIB -eq 1 ]; then
			./runProblem.sh $i --noLibCompile --verifyAns
		else
			COMPILED_LIB=1
			./runProblem.sh $i --verifyAns
		fi
		echo # new line
	fi

done
