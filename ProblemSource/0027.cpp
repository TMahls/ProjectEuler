#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <cmath>

std::string problem27() {
// n^2 + an + b can generate lots of primes
// For ex, n^2 - 79n + 1601 generates 80 primes (n = 0 to 79)
// Find best a and b where abs(a,b) <= 1000

	int N = 1000;
	int bestA = 1;
	int bestB = 41;
	int mostConsecPrimes = 40;
	int n;
	for (int a = -N; a <= N; a++) {
		for (int b = -N; b <= N; b++) {
			n = 0;
			while (isPrime(std::pow(n,2) + a*n + b))
				n++;

			if ( (n-1) > mostConsecPrimes ) {
				mostConsecPrimes = n - 1;
				bestA = a;
				bestB = b;
				//std::cout << " a = " << a << ", b = " << b << " generated " << n-1 << " primes\n";
			}
		}
	}

	return std::to_string(bestA * bestB);
}
