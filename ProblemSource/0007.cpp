#include "eulerUtils.h"
#include <iostream>
#include <string>

std::string problem7() {
// 10,001st prime number
	int primeCount = 1;
	long long searchNum = 3;
	while (primeCount != 10001) {
		if (isPrime(searchNum))
			primeCount++;
		searchNum = searchNum + 2;
	}

	return std::to_string(searchNum - 2);
}
