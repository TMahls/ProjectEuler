#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

std::string problem51() {
// Find first prime where you can replace any digits
// with the same value, and 8 of the 10 possible replacements are prime
// Ex: 56**3 has seven primes: 56003, 56113, 56333, 56443, 56663, 56773, 56993

/*
We won't be replacing the last digit, but every other one can be replaced.
Therefore the number of possible digit replacements is 2^(NDigits - 1)
Here we'll represent the digit replacement pattern as a number, and use its
binary representation to determine whether we replace a digit or not.
*/
	int N = 8;
	int failCount;
	bool found = false;
	int searchNum = 56007;
	int replaceLimit;
	bool replacingFirstDigit;
	std::string primeStr;
	std::string testStr;
	std::string ans;
	while (!found) {
		if ( isPrime(searchNum) ) {
			//std::cout << "Test prime: " << searchNum << std::endl;
			// Digit replacements
			primeStr = std::to_string(searchNum);
			replaceLimit = std::pow(2, primeStr.length() - 1);

			// For each replace pattern 'i'
			int i = 1;
			while ( (i < replaceLimit) && !found) {
				failCount = 0; // How many non-primes found
				replacingFirstDigit = (i >> 0) & 1;

				// For each digit replacement 0-9
				int replaceDigit = 0;
				while ( (replaceDigit < 10) && (failCount <= (10-N)) ) {
					testStr = primeStr;
					// For each digit
					for (unsigned int j = 0; j < primeStr.length(); j++)
						if ( (i >> j) & 1 )
							testStr[j] = num2char(replaceDigit);

					// If searchNum is the answer, we want to keep the one
					// where we replace with 0's or 1's as that'll be the smallest
					if ( (!replacingFirstDigit && (replaceDigit == 0)) || \
						(replacingFirstDigit && (replaceDigit == 1)) )
						ans = testStr;

					// Replacing the first digit with 0 is auto-fail.
					if ( replacingFirstDigit && (replaceDigit == 0) )
						failCount++;
					else if (!isPrime(std::stoi(testStr)))
						failCount++;

					//std::cout << "Digit replacement: " << testStr << std::endl;
					replaceDigit++;
				}

				if (failCount <= (10 - N))
					found = true;
				i++;
			}

		}

		if (!found) {
			searchNum += 2;
			if ( (searchNum % 10) == 5 )
				searchNum += 2;
		}
	}

	return ans;
}
