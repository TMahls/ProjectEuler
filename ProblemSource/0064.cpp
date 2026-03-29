#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <cmath>

std::string problem64() {
// For N <= 10,000, create the continued fraction expansion for sqrt(N)
// ex: sqrt(23) = 4+1/(1+1/(3+1/(1+1/(8+1/...)))). We notate as [4;(1,3,1,8)]
// The part in () repeats and has a period of 4
// How many of those continued fractions have an odd period?

/*
Ok so this process can be distilled to a programatic action.
Just takes some pen and paper work.

a_prev + (sqrt(N) - c) / b

Flip fraction to b*(sqrt(N) + c) / (N - c^2)
Need to reformat to a_next + (sqrt(N) - c_next) / b_next
a_next = (b*(a0+c)) / (N-c^2) [integer division]
b_next = (N - c^2) / b;
c_next = (a_next * (i - c^2) ) / b_prev - c;

One might wonder if the pattern always holds that a0 is not
repeated but a1 onward is. To confirm, I printed the first 50 terms for all
the expansions. Seems like it does! So we can stop iterating when a,b,c match
the a,b,c for the first term.
*/

	int N = 10000;
	int ans = 0;

	int a0,a,b,b_prev,c;
	int aMatch,bMatch,cMatch;
	bool rational;
	bool periodFound;
	int periodCount;

	for (int i = 1; i <= N; i++) {
		rational = false;
		periodFound = false;
		periodCount = 0;
		a0 = std::floor(std::sqrt(i));
		a = a0;
		b = 1;
		c = a0;
		//std::cout << i << ": [" << a0 << ", ";
		while ( !periodFound && !rational ) {
			//std::cout << "a: " << a << " b: " << b << " c: " << c << std::endl;
			if (i == c*c) { // Rational fraction
				rational = true;
				a = 0;
				periodCount = -1; // Gives period count of 0
			} else {
				a = (b*(a0+c)) / (i - c*c);
				b_prev = b;
				b = (i - c*c) / b;
				c = (a*(i-c*c))/b_prev - c;
				if (periodCount == 1) {
					aMatch = a;
					bMatch = b;
					cMatch = c;
				} else {
					periodFound = (a == aMatch) && \
							(b == bMatch) && \
							(c == cMatch);
				}
			}
			periodCount++;
			//std::cout << a << ", ";
		}

		if (periodCount > 0) {
			periodCount -= 2;
			ans += (periodCount % 2); // Tally odd periods
		}

		//std::cout << std::endl << "Period count: " << periodCount << std::endl;
	}

	return std::to_string(ans);
}
