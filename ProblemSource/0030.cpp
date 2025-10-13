#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <cmath>

std::string problem30() {
// Find sum of all nums that can be written as sum of fifth powers of digits
// That is, abcd = a^5 + b^5 + c^5 + d^5

/*
Let's think of an upper and lower bound to numbers that can work like this
to see if brute force checking is feasible.

Since 1^5 = 5 and 0^5 = 0 don't count, the lower bound is 2^5 = 32. No
number smaller than that can be expressed-- since the only numbers below
32 that contain only 1's or 0's (10,11) don't work.

What about upper bound? Well, the most we can get per digit is 9^5 = 59049
A number with all 9's will have a power sum of nDigits * 9^5
We find that for nDigits = 6, the power sum is also 6 digits.
So it's maybe feasible for a 6 digit number to satisfy this condition.
But for nDigits = 7, the power sum is only 6 digits. So it's impossible
for a 7-digit number to satisfy this condition.

Since we only need to check up to 1 million, let's brute force it.

Note: I originally used numDigits and extactDigit from the euler utils
lib with no strings, but then I found that those methods are a little
wasteful for this application (repeatedly calculating the number of digits),
so I found that just using to_string and doing math on each digit was
about twice as fast.

I'll be honest, this is where MATLAB or Python would come in handy.
We could brute force plot the power digit sum vs. N, along with y = x,
to get a good idea of our upper and lower bounds.
*/

	int N = 5;
	int upperBound = 1e6;
	int ans = 0;

	int powerSum;
	unsigned int currDigit;
	for (int i = 32; i < upperBound; i++) {
		std::string iStr = std::to_string(i);

		powerSum = 0;
		currDigit = 0;
		while ( (currDigit < iStr.length()) && (powerSum <= i)) {
			powerSum += std::pow( char2num(iStr[currDigit]), N);
			currDigit++;
		}
		//std::cout << i << " power sum: " << powerSum << std::endl;
		if (powerSum == i) {
			ans += i;
			//std::cout << "Holy shit, a match, i = " << i << std::endl;
		}
	}

	return std::to_string(ans);
}
