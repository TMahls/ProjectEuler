#include "eulerUtils.h"
#include <iostream>
#include <string>

std::string problem73() {
// For ordered, fully reduced fractions n/d where d <= 12,000,
// find the number of fractions between 1/3 and 1/2

/*
The last 2 problems we have not actually generated a fraction list,
but maybe this one we will.

For each denominator d, we're looking for integers that are between d/3 and d/2,
that do not have any common factors (relatively prime) with d.

First approach:
-Build prime database
-For each d from 4 to 12,000
	-For each num between d/3 and d/2
		-For each prime in database
			If num%prime = 0 and den%prime = 0, skip
		Tally

Welp, that was too slow. Checking ~12 million pairs of numbers for being
relatively prime takes a long while.

Here's the approach that worked:
Build prime table from 1 to 6000 (largest numerator we'd need)
For each d from 4 to 12,000
	Calculate nFracs = total number of nums between d/3 and d/2
	Use bool array to represent whether those fracs are simplified - init to all true

	For all primes that are factors of d
		Eliminate simplifiable fractions using prime seive

	Subtract bool array false values from nFracs

	Add the number of simplified fractions for that d to our ans

*/

	const int N = 12000;
	const int upperDen = 2;
	const int lowerDen = 3;
	int ans = 0;

	std::vector<int> primeDb = getAllPrimes(N / upperDen);
	bool place[N/upperDen - N/lowerDen];

	int lowerNum, upperNum;
	int nFracs;
	unsigned int i;
	int startingSpot;
	for (int den = (lowerDen+1); den <= N; den++) {
		// Get total number of fractions
		if ( (den%upperDen) == 0 )
			upperNum = den/upperDen - 1;
		else
			upperNum = den/upperDen;
		lowerNum = den/lowerDen + 1;
		nFracs = upperNum - lowerNum + 1;

		//std::cout << lowerNum << " - " << upperNum << "/" << den << std::endl;
		//std::cout << "Count: " << nFracs << std::endl;

		// To eliminate unsimplified fractions, use denominator prime factor seive
		if (nFracs > 0) {
			// Init place[] to true
			for (int i = lowerNum; i <= upperNum; i++)
				place[i - lowerNum] = true;
			i = 0;
			while ( (i < primeDb.size()) && (primeDb[i] <= upperNum) ) {
				if ( (den % primeDb[i]) == 0 ) {
					// For each prime factor of our den <= upperNum
					startingSpot = lowerNum + ( (primeDb[i] - \
						(lowerNum%primeDb[i])) % primeDb[i] );
					// Remove entries where the numerator is also divisible by it
					for (int j = startingSpot; j <= upperNum; j += primeDb[i])
						place[j - lowerNum] = false;
				}
				i++;
			}

			// Adjust nFracs value
			//std::cout << "Place: [";
			for (int i = lowerNum; i <= upperNum; i++) {
				//std::cout << place[i-lowerNum] << ", ";
				if ( !place[i - lowerNum] )
					nFracs--;
			}
			//std::cout << "]\n";
			//std::cout << "Count after reduction: " << nFracs << std::endl;
		}

		ans += nFracs;
	}

	return std::to_string(ans);
}
