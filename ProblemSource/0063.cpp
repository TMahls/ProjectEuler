#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <cmath>

std::string problem63() {
// How many n-digit integers are also an nth power?
// Ex: 7^5 = 16807, 5 digits

/*
Let's say we're looking at N-digit numbers.
Having N digits means you're between 10^(N-1) and 10^N
There are only so many x values such that x^N is N digits:

1e(N-1) <= x^N < 1eN
(1e(N-1))^(1/N) <= x < 1e(N)^(1/N)
10^(N-1/N) <= x < 10

This upper bound makes sense since powers of 10 always have
one more digit than the exponent:
10^2 -> 3 digits
10^3 -> 4 digits
So larger numbers will all be that way.

Since x has to be an integer, the minute
our lower bound is larger than 9 we can stop looking.
*/
	int ans = 0;
	double lowerBound = 0;
	int N = 1;
	while (lowerBound <= 9) {
		lowerBound = std::pow(10, (double)(N-1)/N);
		for (int i = std::ceil(lowerBound); i < 10; i++) {
			//std::cout << i << "^" << N << " = " << std::pow(i,N) << " - Works.\n";
			ans++;
		}
		N++;
	}

	return std::to_string(ans);
}
