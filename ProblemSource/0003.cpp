#include "eulerUtils.h"
#include <iostream>
#include <string>

std::string problem3() {
	// Get the largest prime factor of this number:
	long long N = 600851475143;

	int NPrimeFactors = countPrimeFactors(N);
	long long * allPrimeFactors = new long long[NPrimeFactors];

	getPrimeFactors(N, allPrimeFactors);
	long long ans = allPrimeFactors[NPrimeFactors - 1];

	delete[] allPrimeFactors;
	return std::to_string(ans);
}
