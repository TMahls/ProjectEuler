#include "eulerUtils.h"
#include <iostream>
#include <string>

std::string problem72() {
// For ordered, fully reduced fractions n/d where d <= 1e6,
// Find the number of fractions in the set

/*

For each denominator from 2 to N, there are a certain number
of members:
2 -> 1/2 [1]
3 -> 1/3, 2/3 [2]
4 -> 1/4, 3/4 [2]
5 -> 1/5, 2/5, 3/5, 4/5 [4]

Fully simplified means the numbers are relatively prime,
so the number of fractions for denominator n is the totient phi(n)
So if we can find out sum of phi(n) for n = 2 to 1e6, we're good.

The naive solution works but is too slow. After trying to calculate
all phi(n) values quickly, I had to turn to the PDF.

We are using a seive-like approach, where we start with phi(n) = n
and multiply by (1 - 1/p) for every prime that is a factor of n
*/

	const int N = 1e6;
	unsigned long long ans = 0;

	// Naive solution
	/*
	for (int i = 2; i <= N; i++) {
		int totient = phi(i);
		ans += totient;
		//std::cout << "i: " << i << " phi(i): " << totient << std::endl;
	}
	*/

	// Init phi table
	// Use malloc because this array is too large for stack
	int * phiTable = (int *) malloc( (N-1) * sizeof(int) );
	for (int i = 0; i < (N - 1); i++)
		phiTable[i] = i+2;

	// Construct phi table
	for (int i = 2; i <= N; i++) {
		if (phiTable[i - 2] == i) { // Prime Number i
			for (int j = i; j <= N; j+=i)
				phiTable[j-2] = phiTable[j-2] - phiTable[j-2]/i; // Multiply by 1-1/i
		}
	}

	// Sum phi table
	for (int i = 2; i <= N; i++)
		ans += phiTable[i - 2];

	free(phiTable);
	phiTable = NULL;

	return std::to_string(ans);
}
