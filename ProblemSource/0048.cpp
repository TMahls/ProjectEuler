#include "eulerUtils.h"
#include <iostream>
#include <string>

std::string problem48() {
// Get the last 10 digits of the series:
// 1^1 + 2^2 + 3^3 + ...

/*
We can do repeated multiplication and only take
the last ten digits. Observation from brute force
with BigInt tells me that any multiple of 10 will
have enough 0's at the end that it won't affect the
answer.
*/
	short i = 11;
	long long testNum;
	long long sum = 10405071317;
	long long tenPow = 1e10;
	while (i < 1000) {
		// Skip multiples of 10
		if ( (i % 10) == 0)
			i++;

		//BigInt bigi(i);
		//std::cout << "i: " << bigi << " i^i: " << pow(bigi,bigi) << std::endl;

		// Repeated multiplication
		testNum = 1;
		for (int j = 0; j < i; j++) {
			testNum *= i;
			testNum %= tenPow; // Only want last 10 digits
		}
		//std::cout << "Last 10 digits: " << testNum << std::endl;
		sum += testNum;
		sum %= tenPow; // Add to sum, keep last 10 digits only
		i++;
	}

	return std::to_string(sum);
}
