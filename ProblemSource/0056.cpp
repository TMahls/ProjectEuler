#include "eulerUtils.h"
#include <iostream>
#include <string>

std::string problem56() {
// For a,b < 100, what is the max
// digit sum of a^b?

/*
Well, powers of 10 are gonna have a lot of 0's,
so I assume they're a no-go. Also, more digits is
better, more 9's is better...

We'll do the naive approach first, but only look at the
biggest 100 values (a, b > 90). EZ peasy -- turns out it's 99 ^ 95

*/
	int biggestDigitSum = 0;
	BigInt test;
	BigInt bigB;
	int testSum;
	for (int a = 91; a < 100; a++) {
		for (int b = 91; b < 100; b++) {
			test = a;
			bigB = b;
			test = pow(test, bigB);
			testSum = digitSum(toString(test));
			if (testSum > biggestDigitSum) {
				//std::cout << a << "^" << b << " has " << testSum << " digit sum\n";
				biggestDigitSum = testSum;
			}
		}
	}

	return std::to_string(biggestDigitSum);
}
