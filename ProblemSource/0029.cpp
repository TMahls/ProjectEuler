#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <cmath>

std::string problem29() {
// How many distinct a^b terms for a,b = 2 thru 100

/*
An easier way to think about this is-- if we brute force it, we'll have a 99 x 99
grid of very large numbers. That's 9801 terms, we just need to figure out which
are duplicates.

As a first pass, if a is a perfect square or cube, one half of its entries will be dupes.
Since a^b = (sqrt(a))^(2b)
If cube: a^b = (a^(1/3))^(3b)

At most we'll have a 6th power, since 2^6 = 64 (anything to the 7th power will be larger
than our upper bound)

Once we identify which numbers are powers, we'll assume those will be the only a values with
dupes.
Ex 64 = 8^2 = 4^3 = 2^6. All of these may remove dupes, since 4 and 8 have different powers.

A square root will remove dupe the following terms:
n    1  2 [3] 4 [5]
n^2  1  2

3 will dupe the first term, 5 will dupe the 2nd term, etc.
Therefore, the number of terms duped is floor((N-1)/2) where
N is the number of terms we have (this holds true when we start at 2.

A cube root will remove these
n    1  2  3  4 [5] 6  7 [8]
n^2  1 [2] 3  4 [5]
n^3  1  2  3

This means a third root will dupe terms.
This pattern gets tricky to define when we add in 4th, 5th, and 6th roots.

Overall, let's say N is a 4th power. We know that the third, second, and first power
will be in our table. We also know:
N^b = (N^3/4)^(4/3*b) = (N^2/4)^(4/2*b) = (N^1/4)^(4/1*b)
So we just need to figure out which of those exponents are integers, and in our table.
*/
	int N = 100;

	/*
	// Display powers -- helps see the patterns described above
	for (int a = 2; a <= N; a++) {
		for (int b = 2; b <= N; b++)
			std::cout << a << "^" << b << "=" << std::pow(a,b) << "  ";
		std::cout << std::endl;
	}
	*/

	int largestPower;
	int i;
	int maxRootCheck = std::floor(log(N) / log(2));
	float testVal;

	int totalUniqueTerms = 0;
	int nTerms;

	for (int a = 2; a <= N; a++) {
		// Determine if a is a power
		largestPower = 0;
		i = maxRootCheck;
		while ((i <= maxRootCheck) && (largestPower == 0)) {
			testVal = std::pow(a, 1.0/i);
			if (std::floor(testVal) == testVal)
				largestPower = i;
			i--;
		}

		nTerms = N - 1; // Number of vals in our power table

		if (largestPower > 1) { // Find out which values are duped
			//std::cout << a << " is a power, exp " << largestPower << std::endl;
			for (int b = 2; b <= N; b++) { // For each b
				bool valRemoved = 0;
				i = largestPower;
				while ( (i-- > 1) && !valRemoved ) {
					testVal = (float)b * largestPower / i;
					if ( (std::floor(testVal) == testVal) && (testVal <= N)) {
						nTerms--;
						valRemoved = 1;
						//std::cout << "Removing b = " << b << std::endl;
					}
				}
			}
			//std::cout << (N - 1 - nTerms) << " terms will be duped.\n";
		}

		totalUniqueTerms += nTerms;
	}

	return std::to_string(totalUniqueTerms);
}
