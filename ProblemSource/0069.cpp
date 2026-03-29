#include "eulerUtils.h"
#include <iostream>
#include <string>

std::string problem69() {
// Totient function phi(n) = numer of relative primes n has from 1-n
// For n < 1e6, find n value that maximizes n / phi(n)

/*
So for this problem, we want large numbers with few relative primes.
That is, numbers with a lot of factors.
Let's see if we can just return the number with the most factors without
even calculating relative primes.

Welp, that didn't work AND it was slow! 720720 was not the answer.

*/

	int N = 1e6;
	int ans = 0;
	int mostFactors = 0;
	for (int i = 2; i <= N; i++) {
		if (countFactors(i) > mostFactors) {
			mostFactors = countFactors(i);
			ans = i;
		}
	}

	return std::to_string(ans);
}
