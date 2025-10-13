#include "eulerUtils.h"
#include <iostream>
#include <string>

bool isCircularPrime(int);

std::string problem35() {
// How many circular primes below one million?
// Circular prime -- all digit rotations are prime

	int tally = 13; // We are given that there are 13 below 100
	for (int i = 101; i < 1e6; i++) {
		if (isPrime(i) && isCircularPrime(i)) {
			//std::cout << i << " is circular prime\n";
			tally++;
		}
	}

	return std::to_string(tally);
}

bool isCircularPrime(int n) {
// Given a prime n, determine if all digit rotations
// are also prime.

	int nDigits = numDigits(n);
	std::string nStr = std::to_string(n);
	int nTest;
	// For each rotation
	for (int i = 1; i < nDigits; i++) {
		nStr = nStr.substr(1) + nStr[0];
		nTest = std::stoi(nStr);
		if (!isPrime(nTest))
			return 0;
	}

	return 1;
}
