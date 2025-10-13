#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <vector>

std::string problem50() {
// Longest consecutive prime sum below 1 million

	int N = 1e6;

	// Build prime database
	std::vector<int> primes = {2,3,5,7};
	int searchNum = 11;
	while (searchNum < N) {
		if (isPrime(searchNum))
			primes.push_back(searchNum);
		searchNum += 2;
		if ( (searchNum % 10) == 5 )
			searchNum += 2;
	}

	unsigned int longestStreak = 0;
	int ans = 0;
	int sum;
	unsigned int n;
	unsigned int startIdx = 0;
	// In the primes database we start a consecutive sum
	// at each potential start IDX
	while (startIdx < primes.size()) {
		sum = 0;
		n = 0;
		// We keep summing until the sum goes over our limit
		while ( (sum < N) && (n < (primes.size() - startIdx)) ) {
			sum += primes[startIdx + n];
			n++;

			// Keep track of the longest consecutive streak where
			// 'sum' is a prime
			if ( (n > longestStreak) && isPrime(sum)) {
				//std::cout << "Added to " << sum << " with " << n << " consec terms\n";
				longestStreak = n;
				ans = sum;
			}

		}

		startIdx++;
	}

	return std::to_string(ans);
}
