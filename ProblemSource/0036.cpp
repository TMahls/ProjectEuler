#include "eulerUtils.h"
#include <iostream>
#include <string>

std::string problem36() {
// Sum of all [2,10] palindromes below 1 million
// [2,10] meaning they are palindromes in base 2 and base 10

	/* Test cases for base conversion functions
	std::cout << "Test: " << convertToBase("123.45",10,2) << std::endl;
	std::cout << "Test: " << convertToBase("-123.45",10,2) << std::endl;
	std::cout << "Test: " << convertToBase("-123.45",10,16) << std::endl;
	std::cout << "Test: " << convertToBase("-123.45",10,64) << std::endl;
	std::cout << "Test: " << convertToBase("-123.45",10,10) << std::endl;
	*/

	int ans = 0;
	std::string j;
	std::string iStr;
	for (int i = 1; i < 1e6; i++) {
		iStr = std::to_string(i);
		if ( isPalindrome(iStr) ) {
			j = convertBase10Int(i,2);
			//j = i;
			if ( isPalindrome(j) ) {
				//std::cout << i << " is a palindrome in b10 and b2.\n";
				ans += i;
			}
		}
	}

	return std::to_string(ans);
}
