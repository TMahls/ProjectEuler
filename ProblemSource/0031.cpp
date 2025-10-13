#include "eulerUtils.h"
#include <iostream>
#include <string>

int recursiveGetUniqueSums(short[], short, short, short);

std::string problem31() {
// How many unique ways can £2 be made with coins

/*
Seems like a straightforward recursion problem.
Just be careful to only return unique sums, by searching
decreasing coin sums only.

NOTE - The solution below is pretty bad! Read the PDF
for a better one. The recursion can be made simpler, or
you can use memoization to reduce repeated calculations.

You can even do some dynamic progrmaming to make this expandable
for up to £100

But for now, this runs in a couple ms and I am satisfied.
*/

	short target = 200;
	short coins[] = {1,2,5,10,20,50,100,200};
	int ans = recursiveGetUniqueSums(coins, 7, target, 0);

	return std::to_string(ans);
}

int recursiveGetUniqueSums(short coins[], short currCoinIdx, short target, short recursionDepth) {
	// How many unique ways can we sum up to target with number set?
	// The recursion depth variable is just useful for debugging.
	// We start with large coins here and strictly decrease (or use same coin)

	int numPossibilities = 0;

	// For each coin we can add
	int i = currCoinIdx + 1;
	while (i-- > 0) {
		if (coins[i] < target) {
			int a = recursiveGetUniqueSums(coins, i, target - coins[i], recursionDepth+1);
			numPossibilities += a;
			if (recursionDepth == 0) {
				//std::cout << a << " ways to get to " << target - coins[i] << " with idx " << i << " or less\n"; 
			}
		} else if (coins[i] == target) {
			numPossibilities++;
		}
	}

	return numPossibilities;
}
