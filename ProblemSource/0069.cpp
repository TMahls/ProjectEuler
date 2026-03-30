#include "eulerUtils.h"
#include <iostream>
#include <string>

std::string problem69() {
// Totient function phi(n) = numer of relative primes n has from 1 to n
// For n < 1e6, find n value that maximizes n / phi(n)

/*
So for this problem, we want large numbers with few relative primes.
That is, numbers with a lot of factors.
Let's see if we can just return the number with the most factors without
even calculating relative primes.

Welp, that didn't work AND it was slow! 720720 was not the answer.

We should probably come up with an efficient way to calculate this.
Off to the wikipedia page for the Euler totient function.

What about the most prime factors? Well that did work (510510), but
still too slow. Let's look at the PDF writeup for this one

Ok so basically from the formula for totient we can see that:
n/phi(n) = Multiply (p / (p - 1) ) for all prime factors of N

Smaller 'p' values will give us larger ratios, since (n+1)/n > (n+2)/(n+1)
Ex: 3/2 > 5/4
So, we want to just multiply the smallest prime numbers until we get to our boundary.
Ex: It's guaranteed that 2*3*5 = 30 will have the largest ratio until N = 2*3*5*7 = 210
*/

	int N = 1e6;

	// Naive/slow approach
	/*
	int ans = 0;
	double currRatio, largestRatio;
	largestRatio = 0;
	for (int i = 2; i <= N; i++) {
		currRatio = countPrimeFactors(i);
		if (currRatio > largestRatio) {
			largestRatio = currRatio;
			ans = i;
		}

	}
	*/

	// Fast approach - just multiply smallest primes
	int ans = 2;
	int currPrime = 3;
	while (ans <= N) {
		if (isPrime(currPrime))
			ans *= currPrime;
		currPrime += 2;
	}
	ans /= (currPrime - 2);

	return std::to_string(ans);
}
