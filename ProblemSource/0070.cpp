#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <cmath>

std::string problem70() {
// Totient function phi(n) = numer of relative primes n has from 1 to n
// For n < 1e7, find n value that minimizes n / phi(n) where phi(n) is a permutation of n

/*
Okay, a tougher version of 69!
We are searching 1 thru 9,999,999 - so 1 to 7 digits

To minimize n / phi(n) we want something that has many relative primes, so
essentially prime numbers?

For prime numbers phi(n) = n-1. But we can't have a permutation where the perm(x) = x-1...?

From the example given we know that ratios as small as 1.1 are feasible. We also know that
larger digit numbers can get smaller ratios. Therefore our number will be:
-Large
-Not prime
-Have 2 prime factors -- by observation with naive method
-The prime factors will be large -- Larger prime factors means larger phi(n) and smaller ratio.
-The prime factors will be close to sqrt(N) -- this is only true for large N. For N = 1e4, the answer is 3*997
So let's get all primes around sqrt(N) and start multiplying them by other primes in the list

Fun fact -- when a number just has two prime factors [i, j], by the formula phi(n) = (i-1)(j-1)
So that makes calculating easy!

*/

	int N = 1e7;

	// Naive approach - for N <= 1e5
	/*
	int ans = 0;
	double smallestRatio = N;
	for (int n = 2; n <= N; n++) {
		// Calcualte phi(n)
		int nPrimeFactors = countPrimeFactors(n);
		long long totient = n;
		if (nPrimeFactors > 0) {
			long long * primeFactors = new long long[nPrimeFactors];
			getPrimeFactors(n, primeFactors);

			long long den = 1;
			//std::cout << "n: " << n << std::endl;
			for (int i = 0; i < nPrimeFactors; i++) {
				totient *= primeFactors[i] - 1;
				den *= primeFactors[i];
				//std::cout << "Multiply by " << primeFactors[i] - 1 << " / " << primeFactors[i] << std::endl;
				//std::cout << "Totient: " << totient << " Den: " << den << std::endl;
			}
			totient /= den;


			if (isPerm(std::to_string(totient), std::to_string(n))) {
				std::cout << "n: " << n << " phi(n): " << totient << std::endl;
				std::cout << "Ratio: " << (double)(n)/totient << std::endl;
				if ((double)(n)/totient < smallestRatio) {
					std::cout << "New smallest ratio!" << std::endl;
					ans = n;
					smallestRatio = (double)(n)/totient;

					std::cout << "Prime factors: [";
					for (int i = 0; i < nPrimeFactors; i++)
						std::cout << primeFactors[i] << ", ";
					std::cout << std::endl;
				}
			}
			delete[] primeFactors;
		} else {
			totient = n - 1;
		}
		//std::cout << "Final Totient: " << totient <<  std::endl;
	}
	*/

	// We know our answer prime factors are around sqrt(N) to maximize fraction size
	// As N gets larger you can narrow this search factor from 5 to 2 for speed
	std::vector<int> primeDb = getAllPrimes(std::sqrt(N) * 5);
	int eraseIdx = 0;
	int idx = 0;
	while (eraseIdx == 0) {
		if (primeDb.at(idx) > (std::sqrt(N) / 5))
			eraseIdx = idx;
		idx++;
	}
	primeDb.erase(primeDb.begin(), primeDb.begin() + eraseIdx);

	unsigned int i = 0;
	unsigned int j;
	int ans = 0;
	int n, totient;
	double smallestRatio = N;
	while (i < primeDb.size()) {
		j = 0;
		while (j <= i) {
			n = primeDb[i] * primeDb[j];
			if ( n < N ) {
				// Calcualte phi(n)
				totient = (primeDb[i] - 1) * (primeDb[j] - 1);

				// Check if its a perm
				if (isPerm(std::to_string(totient), std::to_string(n))) {
					//std::cout << "n: " << n << " phi(n): " << totient << std::endl;
					//std::cout << "Ratio: " << (double)(n)/totient << std::endl;
					if ((double)(n)/totient < smallestRatio) {
						//std::cout << "New smallest ratio!" << std::endl;
						ans = n;
						smallestRatio = (double)(n)/totient;
					}
				}

			}
			j++;
		}
		i++;
	}

	return std::to_string(ans);
}
