#include "eulerUtils.h"
#include <iostream>
#include <string>

std::string problem58() {
/*
In problem 28  we summed the diagonals of a similar spiral.
When making a spiral like the following:

17 16 15 14 13
18  5  4  3 12
19  6  1  2 11
20  7  8  9 10
21 22 23 24 25

At what side length does the portion of primes on the diagonal
fall below 10%?
*/

/*
As the problem says, the bottom right
diagonal will always be odd squares - no primes there.
We just need an equation to generate the other 3 numbers and
check if they're prime, and keep track of how many primes relative
to the total.
*/
	float total = 1; // Start with the middle
	int primes = 0;
	int test = 1;
	int sideLength = 1;

	// That first condition is just so we don't get divide by zero on the first iteration
	while ((sideLength < 3) || ( (primes/total) >= 0.1) ) { // While we're above 10 percent
		test += sideLength + 1;

		for (int i = 0; i < 3; i++) {
			if (isPrime(test))
				primes++;
			test += (sideLength + 1);
		}

		total += 4;
		sideLength += 2;
		//std::cout << "Total diags: " << total << " primes: " << primes << " ratio: " << primes/total <<  std::endl;
	}

	return std::to_string(sideLength);
}
