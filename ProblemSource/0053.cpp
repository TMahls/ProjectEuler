#include "eulerUtils.h"
#include <iostream>
#include <string>

std::string problem53() {
// How many nCr values for n = 1-100 are larger than 1e6?

/*
We'll take advantage of the symmetry - nCr = nC(n-r)
Additionally, all r values after the first one million found
will be for that n (up to (n-r)). Also, we can start our search at r = 2.

This is not super efficient, there's probably a way to do this without big
ints. But it's just barely fast enough (250-300ms) on my machine.
*/

	BigInt test;
	BigInt nFact;
	int ans = 0;
	for (int n = 23; n <= 100; n++) {
		nFact = bigFactorial(n);
		int r = 1;
		bool found = false;
		while (r <= (n/2) && !found) {
			//std::cout << "Testing " << n << "C" << r << std::endl;
			test = bigFactorial(r);
			test *= bigFactorial(n - r);
			test = nFact / test;
			if ( test > BigInt(1e6) ) {
				//std::cout << "Big boi!\n";
				found = true;
				ans += (n - 2*r + 1);
			}
			r++;
		}
	}

	return std::to_string(ans);
}
