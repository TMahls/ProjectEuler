#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <cmath>

std::string problem0() {
// Sum of odd square numbers
// Nowadays to register a new PE account, you have to solve
// a simple problem. The number below is randomized.
	int sqNumberCount = 156e3;
	unsigned long long squareSum = 0;
	for (int i = 1; i <= sqNumberCount; i += 2)
		squareSum += std::pow(i,2);

	return std::to_string(squareSum);
}
