#include "eulerUtils.h"
#include <iostream>
#include <string>

std::string problem10() {
	// Sum of all primes below 2 million
	long long primeSum = 5; // Include 2,3
	// We increment by 6 since we eliminate multiples of 2 and 3
	for (int i = 5; i < 2e6; i += 6) {
		if (isPrime(i))
			primeSum += i;
		if (isPrime(i + 2))
			primeSum += (i + 2);
	}

	return std::to_string(primeSum);
}
