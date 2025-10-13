#include "eulerUtils.h"
#include <iostream>
#include <string>

std::string problem4() {
	// Get the largest palindromic number made from product of two 3-digit numbers
	int biggestPalindrome = 0;
	std::string testStr;
	for (int a = 100; a <= 999 ; a++) {
		for (int b = a; b <= 999 ; b++) {
			testStr = std::to_string(a * b);
			if (isPalindrome(testStr) && ((a*b) > biggestPalindrome)) {
				biggestPalindrome = a * b;
			}
		}
	}

	return std::to_string(biggestPalindrome);
}
