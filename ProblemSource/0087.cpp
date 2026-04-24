#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <cmath>
#include <set>
#include <algorithm>

std::string problem87() {
// How many numbers below 50e6 can be expressed as:
// p1^2 + p2^3 + p3^4, where pn is a prime

/*
Well, for the square number we can have primes up to:
sqrt(N - 2^3 - 2^4)

For the cube we have primes up to:
(N - 2^2 - 2^4) ^ 1/3

For the 4th root we have primes up to:
(N - 2^2 - 2^3) ^ 1/4

There are only about 900 primes between 2 and sqrt(50e6),
so this is ok to brute force once we get a primeDb.

Further calculation reduction by using the prime2/3/4 and
calc/precalc variables mean we can loop through all our
combos pretty fast.

But it turns out, there are duplicates! Numbers that can
be expressed multiple ways.

First two examples:
145 = 2^2 + 5^3 + 2^4 = 11^2 + 2^3 + 2^4
210 = 2^2 + 5^3 + 3^4 = 11^2 + 2^3 + 3^4

We can avoid this with a set, but that's pretty slow since
we are inserting around a million numbers into the set.

Turns out a faster way (surprisingly) is to just add all
our numbers to a vector, sort, the vector, then count the unique
elements. Huh. Our vector does take up ~4Mb but that's OK.
*/

	const int N = 50e6;
	int ans = 0;

	// Create databases
	std::vector<int> primeDb = getAllPrimes(std::sqrt(N-24));
	std::set<int> foundNums;

	std::vector<int> prime2, prime3, prime4;
	unsigned int i = 0;
	int calc = 0;
	while (i < primeDb.size()) {
		calc = primeDb[i] * primeDb[i];
		prime2.push_back(calc);
		i++;
	}

	i = 0;
	calc = 0;
	while (calc < (N - 20)) {
		calc = primeDb[i] * prime2[i];
		prime3.push_back(calc);
		i++;
	}

	i = 0;
	calc = 0;
	while (calc < (N - 12)) {
		calc = primeDb[i] * prime3[i];
		prime4.push_back(calc);
		i++;
	}

	//std::cout << "Last prime: " << primeDb[primeDb.size()-1] << std::endl;
	std::vector<int> numsFound;

	// Combine prime powers and add to vector
	i = 0;
	unsigned int j,k,preCalc;
	while (i < prime2.size()) {
		j = 0;
		preCalc = prime2[i] + prime3[j];
		//std::cout << "a = " << primeDb[i] << std::endl;
		while ( preCalc <= (N - 16) ) {
			k = 0;
			calc = preCalc + prime4[k];
			//std::cout << "\tb = " << primeDb[j] << std::endl;
			while ( calc < N ) {
				//std::cout << "\t\tc = " << primeDb[k] << " p = " << calc << std::endl;
				numsFound.push_back(calc);
				k++;
				calc = preCalc + prime4[k];
			}
			j++;
			preCalc = prime2[i] + prime3[j];
		}
		i++;
	}

	// Count unique elements
	std::sort(numsFound.begin(), numsFound.end());
	ans = 1;
	for (unsigned int i = 1; i < numsFound.size(); i++)
		if (numsFound[i-1] != numsFound[i])
			ans++;

	return std::to_string(ans);
}
