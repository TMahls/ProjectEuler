#include "eulerUtils.h"
#include <iostream>
#include <string>

std::string problem12() {
	// First triangle number with over 500 factors
	int n = 1;
	int factorTarget = 500;

	long long currTriangleNum = 1;
	do {
		n++;
		currTriangleNum += n;
	} while ( countFactors(currTriangleNum) <= factorTarget );

	return std::to_string(currTriangleNum);
}


