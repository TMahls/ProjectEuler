#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <cmath>

std::string problem34() {
// Sum of all numbers that are equal to sum(digit!)

	// Build digit factorial table
	int factorial[10] = {1,1,2,3,4,5,6,7,8,9};
	for (int i = 3; i < 10; i++)
		factorial[i] *= factorial[i-1];

	/*
	std::cout << "factorials = [";
	for (int i = 0; i < 10; i++)
		std::cout << factorial[i] << ", ";
	std::cout << "]\n";
	*/

/*
10 is the lower search bound because we state anything
less isn't a sum.
7 * 9! is the upper bound because that's the max sum we can make
with 7 digits. Anything larger and we cannot express it.
9 * 8! < 8 digits, thus it's impossible for an 8 digit number to work.

We adapt 'extractDigit' for this.
*/

	// Brute force to explore:
	int ans = 0;
	short nDigits = 1;
	int tenPower = 10;
	int currNum;
	int digitSum;
	int nextDigit;

	for(int i = 10; i <= (7 * factorial[9]); i++) {
		// Doing this is faster than calling 'numDigits' every time
		if ( !(i%tenPower) ) {
			tenPower *= 10;
			nDigits++;
		}

		currNum = i;
		digitSum = 0;

		for (int digit = nDigits; digit > 0; digit--) {
			nextDigit = currNum / std::pow(10,digit-1);
			digitSum += factorial[nextDigit];
			currNum %= (int)(std::pow(10,digit-1));
		}

		//std::cout << "i: " << i << " digit factorial sum: " << digitSum << std::endl;
		if (i == digitSum) {
			//std::cout << i << " works.\n";
			ans += i;
		}
	}

	return std::to_string(ans);
}
