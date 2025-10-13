#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <vector>

std::vector<std::vector<short>> getAllOddPerms(std::vector<short>);

std::string problem41() {
// Largest n-digit pandigital prime

/*
Two overall options -- build pandigital database and
check 'isPrime()', or build prime database and check
'isPandigital()'.

Let's build a pandigital database. Quicker to generate
permutations.
Then we need to strike any that end in 2,4,5,6,8
This is done in 'getAllOddPerms'. It turns out even generating
the 9! database takes about half a second-- too slow!
So we can't get the whole set then prune-- we have to generate
a reduced set to begin with.

We can also start at 9 digits and work our way down,
stopping the program when we find one.
*/
	long long ans;

	char nDigits = 9;
	bool found = false;
	std::vector<std::vector<short>> pandigitals;
	std::vector<short> digitsVec = {1,2,3,4,5,6,7,8,9,0};

	while (!found && (nDigits > 3)) {
		// Get digit permutations
		digitsVec.pop_back();
		pandigitals = getAllOddPerms(digitsVec);

		/*
		std::cout << "Perms that end in 1,3,7,9: \n";
		for (std::vector<short> x : pandigitals) {
			for (short y : x)
				std::cout << y << " , ";
			std::cout << std::endl;
		}
		*/

		// Check for primes
		int i = pandigitals.size() - 1;
		int testNum;
		int tenPow;
		while ( (i >= 0) && !found) {
			if (!pandigitals[i].empty()) {
				testNum = 0;
				tenPow = 1;
				for (int j = nDigits - 1; j >= 0; j--) {
					testNum += tenPow * pandigitals[i][j];
					tenPow *= 10;
				}

				if ( isPrime(testNum) ) {
					//std::cout << testNum << " is prime\n";
					ans = testNum;
					found = true;
				}
			}
			i--;
		}

		nDigits--;
	}

	return std::to_string(ans);
}

std::vector<std::vector<short>> getAllOddPerms(std::vector<short> n) {
// Adapted from 'getAllPerms' in the utils lib.
// Only looks at subperms that don't contain entirely even or 5
// This is done in the base case.

	std::vector<std::vector<short>> ans;
	std::vector<short> nMod;
	short N = n.size();

	// Base case -- for 2 nums, return swapped
	if (N == 2) {
		if ( ((n[1] % 2) == 1) && (n[1] != 5))
			ans.push_back(n);

		if ( ((n[0] % 2) == 1) && (n[0] != 5)) {
			nMod = {n[1], n[0]};
			ans.push_back(nMod);
		}
		return ans;
	}

	std::vector<std::vector<short>> subArr;
	for (unsigned short i = 0; i < N; i++) {
		// Create nMod by erasing 'i'
		// (erase is really slow)
		nMod.clear();
		for (short j : n)
			if (j != n[i])
				nMod.push_back(j);

		subArr = getAllOddPerms(nMod);

		for (std::vector<short> j : subArr) {
			nMod = {n[i]};
			for (short k : j)
				nMod.push_back(k);
			ans.push_back(nMod);
		}

	}

	return ans;
}
