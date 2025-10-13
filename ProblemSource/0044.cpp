#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <cmath>

#define N 5000

std::string problem44() {
// Pentagonal numbers Pn = n(3n-1)/2
// Find 2 pentagonal numbers, Pj and Pk such that
// Their sum and difference are pentagonal. What is the
// minimal difference between them?


/*
I tried to think of a clever way to do this, but
it turns out math is faster than using binary search to
see if the sum and diff are in the large pentagonal
number database.
*/

	int pentanumData[N] = {};
	for (int i = 0; i < N; i++)
		pentanumData[i] = (i + 1)*(3*(i + 1) - 1)/2;

	int diff = 0;
	int sum = 0;
	double calc;
	int minDiff = N*(3*N-1)/2;
	for(int j = 1; j < N; j++) {
		for (int k = 0; k < j; k++) {
			diff = pentanumData[j] - pentanumData[k];
			calc = (1 + sqrt(1 + 24*diff))/ 6;
			if ( std::floor(calc) == calc) {
				sum = pentanumData[j] + pentanumData[k];
				calc = (1 + sqrt(1 + 24 * sum)) / 6;
				if (std::floor(calc) == calc) {
					std::cout << "Both! " << j+1 << ", " << k+1 << std::endl;
					if (diff < minDiff)
						minDiff = diff;
				}
			}
		}
	}

	return std::to_string(minDiff);
}
