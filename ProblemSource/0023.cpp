#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <vector>

#define N 28123

std::string problem23() {
// Sum all integers that can't be written as the sum of two abundant numbers

/*
Interesting pre-amble. We can prove that all integers larger than 28123
can be expressed as the sum of 2 abundant numbers, but we know for a fact
that the actual largest number that CANT be expressed this way is smaller.

First let's collect a list of abundant numbers up to that limit.

Then, we create a big bool array where each index represents a number.
We iterate all the possible sums of our 2 abundant numbers, and if we find the sum
mark that entry on our bool array.

This is definitely a brute force solution and takes a couple hundred milliseconds.
*/
	int ans = triangleNum(23); // Smallest number that can be written is 24

	std::vector<int> abundantVec;
	for (int i = 1; i < N; i++) {
		if ((getFactorSum(i) - i) > i) {
			//std::cout << i << " is abundant!\n";
			abundantVec.push_back(i);
		}
	}

	bool sumsFound[N - 23] = {}; // Big bool array, takes up 28kbytes.

	for (unsigned int num1Idx = 0; num1Idx < abundantVec.size(); num1Idx++) {
		for (unsigned int num2Idx = num1Idx; num2Idx < abundantVec.size(); num2Idx++) {
			if ( (abundantVec.at(num1Idx) + abundantVec.at(num2Idx)) <= N )
				sumsFound[abundantVec.at(num1Idx) + abundantVec.at(num2Idx) - 24] = 1;
		}
	}

	for (int i = 0; i < (N - 23); i++) {
		if ( !sumsFound[i]) {
			//std::cout << i + 24 << " could not be expressed\n";
			ans += i + 24;
		}
	}

	return std::to_string(ans);
}
