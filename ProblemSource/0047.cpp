#include "eulerUtils.h"
#include <iostream>
#include <string>

std::string problem47() {
// First four consecutive numbers with four distinct
// prime factors each.

	char nDistinct = 4;

	int testNum = 2;
	char consecCount = 0;

	while (consecCount < nDistinct) {
		if (countPrimeFactors(testNum) == nDistinct) {
			//std::cout << testNum << " has " << (int)nDistinct << " pfactors!\n";
			consecCount++;
		} else {
			//std::cout << testNum << " fails. Resetting consec count\n";
			consecCount = 0;
		}
		testNum++;
	}

	return std::to_string(testNum  - nDistinct);
}
