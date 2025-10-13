#include "eulerUtils.h"
#include <iostream>
#include <string>

std::vector<std::vector<short>> getSpecialPerms(std::vector<short> remainingDigits, std::vector<short> currVec);

std::string problem43() {
// Find the sum of all 0-9 pandigital nums with this property:

/*
Digit concatenation:

d2d3d4 divisible by 2
d3d4d5 divisible by 3
d4d5d6 divisible by 5
d5d6d7 divisible by 7
d6d7d8 divisible by 11
d7d8d9 divisible by 13
d8d9d10 divisible by 17

Ex: 1406357289
*/

/*
The last 3 digits have to be divisible by 17, so limits us to
017
etc.

Additionally d6 must be a 5 or 0, so those 2 rules alone eliminate
many of the 10! = 3.63e6 pandigital numbers. d4 must be even

But I suppose we'll start with brute force.

Brute force took 6 seconds, WOOF!

So now, similar to problem 41, we can't prune the full set of pandigital
nums. We have to generate a reduced set.

We do this in 'getSpecialPerms' by checking our current vector as we recurse,
and only proceeding if our number obeys all the rules

*/

	long long ans = 0;
	std::vector<short> remainingDigits = {0,1,2,3,4,5,6,7,8,9};
	std::vector<short> currVec;

	std::vector<std::vector<short>> allPerms = getSpecialPerms(remainingDigits, currVec);

	long long tenPow;
	long long val;
	for (std::vector<short> i : allPerms) {
		tenPow = 1;
		val = 0;
		for (int j = i.size() - 1; j >= 0; j--) {
			val += tenPow * i[j];
			tenPow *= 10;
		}
		ans += val;
		//std::cout << "Adding " << val << std::endl;
	}

	return std::to_string(ans);
}

std::vector<std::vector<short>> getSpecialPerms(std::vector<short> remainingDigits, std::vector<short> currVec) {
// Return a vector of all permutations of N that might fit special properties
	/*
	std::cout << "Remaining digits: ";
	for (short i : remainingDigits)
		std::cout << i << " , ";
	std::cout << "\n Curr vec: ";
	for (short i : currVec)
		std::cout << i << " , ";
	std::cout << std::endl;
	*/
	std::vector<std::vector<short>> ans;
	short N = remainingDigits.size();
	short currDigit = 10 - N + 1;

	bool proceed;
	std::vector<short> remainingDigitsMod;
	std::vector<short> currVecMod; // Previous with our new num tacked on
	std::vector<std::vector<short>> subArr;
	short primes[] = {2,3,5,7,11,13,17};
	short latest3;
	for (unsigned short i = 0; i < N; i++) {
		//std::cout << "Adding " << remainingDigits[i] << std::endl;
		// Check digit rules
		proceed = true;
		if (currDigit >= 4) {
			latest3 = 100 * currVec[currVec.size() - 2] + 10 * currVec[currVec.size() - 1] + \
				remainingDigits[i];
			if ( (latest3 % primes[currDigit - 4]) != 0)
				proceed = false;
		}

		if (proceed) {
			if (remainingDigits.size() == 1) { // Base case
				ans.push_back(remainingDigits);
			} else {
				// Create nMod by erasing 'i'
				// (erase is really slow)
				remainingDigitsMod.clear();
				for (short j : remainingDigits)
					if (j != remainingDigits[i])
						remainingDigitsMod.push_back(j);
				currVecMod = currVec;
				currVecMod.push_back(remainingDigits[i]);

				subArr = getSpecialPerms(remainingDigitsMod, currVecMod);

				for (std::vector<short> j : subArr) {
					remainingDigitsMod = {remainingDigits[i]};
					for (short k : j)
						remainingDigitsMod.push_back(k);
					ans.push_back(remainingDigitsMod);
				}
			}
		}
	}

	return ans;
}
