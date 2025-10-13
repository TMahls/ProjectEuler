#include "eulerUtils.h"
#include <iostream>
#include <string>

std::string problem26() {
// Longest recurring cycle in 1/n for n < 1000

	int N = 1e3;

	/*
	Some obersvations based on vibes:
	Only need to check primes -- it seems the length
	of a pattern is the same as the longest prime factor pattern.

	Additionally, it seems for the primes, the first non-zero number is
	what ends up repeating (no nonsense like 1/6 = 0.1(6)

	We essentially do long division here and count the number of
	times we have to do it before getting to our original factor.

	Another observation: The longest possible cycle length is n-1.
	Larger numbers get longer cycles.
	So we can actually start our search backwards, and give up once
	we have an unbeatable cycle length.
	*/

	int cycleLength;
	int longestCycle = 0;
	int longestCycleDenom = 2;
	int factor;
	int firstFactor;
	bool evenDivide; // Do we have a non-repeating fraction
	int i = N;
	while ( (i-- > 0) && (longestCycle <= (i-1)) ) {
		if ( isPrime(i) ) {
			evenDivide = false;
			//std::cout << "i = " << i << std::endl;

			factor = 10;
			cycleLength = 0;

			while (i > factor)
				factor *= 10;
			firstFactor = factor;

			do {
				factor %= i;
				if (factor == 0) {
					cycleLength = 0;
					evenDivide = true;
				}

				while ((i > factor) && !evenDivide) {
					factor *= 10;
					cycleLength++;
				}

				//std::cout << factor << std::endl;
			} while ((factor != firstFactor) && !evenDivide);

			//std::cout << "Cycle length: " << cycleLength << std::endl;

			if ( cycleLength > longestCycle ) {
				/*
				std::cout << i << " defeats " << longestCycleDenom << \
					" with cycle of " << cycleLength << std::endl;
				*/
				longestCycle = cycleLength;
				longestCycleDenom = i;
			}
		}
	}

	return std::to_string(longestCycleDenom);
}
