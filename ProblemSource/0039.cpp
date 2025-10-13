#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <cmath>

#define N 1000

std::string problem39() {
// Find right triangle perimeter <= 1000 with most integer solutions

	// How many times we've seen a particular perim
	short perimCount[N+1] = {};

	float a;
	for (short c = 2; c < N; c++) {
		for (short b = 1; b < c; b++) {
			a = std::sqrt(c * c - b * b);
			if ( (a == std::floor(a)) && ((a + b + c) <= N ) )
				perimCount[(short)a + b + c]++;
		}
	}

	// Go thru perimCount
	int maxSolns = 0;
	short maxSolnsPerim = 0;
	for (short i = 0; i <= N; i++) {
		if ( perimCount[i] > maxSolns ) {
			maxSolns = perimCount[i];
			maxSolnsPerim = i;
		}
	}

	return std::to_string(maxSolnsPerim);
}
