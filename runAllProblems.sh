#!/bin/bash

cd ~/Documents/Coding\ Projects/ProjectEuler

# Run all problems to see if they compile.
# This can help detect breakages in tne euler utils lib

# Re-compiles the lib for the first problem only.
COMPILED_LIB=0

for i in {1..1000}; do

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
