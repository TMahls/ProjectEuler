#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <algorithm>

std::string problem55() {
// How many Lychrel numbers below 10,000?
// Lychrel number - a number that does not eventually become
// a palindrome thru reversing the digits and adding to itself.
// Given -- max 50 iterations.

	BigInt lychrel;
	std::string currStr;
	short iterationCount;
	short ans = 0;
	for (int i = 1; i < 10000; i++) {
		//std::cout << "Test " << i << std::endl;
		lychrel = i;
		iterationCount = 0;
		do {
			currStr = toString(lychrel);
			std::reverse(currStr.begin(), currStr.end());

			lychrel += BigInt(currStr);
			iterationCount++;
			//std::cout << lychrel << " , ";
		} while ( !isPalindrome(toString(lychrel)) && \
			(iterationCount < 50) );

		//std::cout << std::endl;

		if (iterationCount >= 50) {
			//std::cout << i << " didn't converge!\n";
			ans++;
		}

	}


	return std::to_string(ans);
}
