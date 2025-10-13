#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <set>

std::string problem32() {
// Sum of all products that can be written as:
// ab * cde = fghij
// The numbers can have any number of digits, but 1-9
// must all be represented once.

/*
Actually, it looks like my high school self
solved this fairly elegantly! We'll copy him.

He realized that the product must be between 1,000 and 10,000
Why? If the product has 3 digits or less, the multiplicands must have 6 digits total.
No matter how you split that up, you can't make a 3-digit number from that.

With 10,000, if the product has 5 digits you must have 4 digits in
the multiplicands. That's not enough digits to create a 5-digit number.


*/

	std::set<int> pandigitalSet;
	int factor2;
	std::string allNums;
	// Check all possible product numbers
	for (int i = 1000; i < 10000; i++) {
		// First get a factor of that number
		for (int factor = 2; factor <= std::sqrt(i); factor++) {
			// Calculate the second factor
			if ( (i % factor) == 0 ) {
				factor2 = i / factor;
				// Turn them all into a string
				allNums = std::to_string(i) + std::to_string(factor) + \
					std::to_string(factor2);
				// Determine if pandigital
				if (isPandigital(allNums))
					pandigitalSet.insert(i);
			}
		}
	}

	int productSum = 0;
	for (int i : pandigitalSet) {
		//std::cout << i << " has a pandigital product\n";
		productSum += i;
	}

	return std::to_string(productSum);
}
