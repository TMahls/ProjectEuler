#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <vector>
#include <numeric>

std::string problem21() {
// Sum of all amicable numbers under 1e4
// Amicable numbers: d(a) = b; d(b) = a
// d(n) = Sum of divisors < n

	int N = 1e4;
	int ans = 0;

	// Note: Getting the factors vector and summing it is not
	// the most efficient way. There's a PDF for this one, but a faster
	// factor sum function can be made assuming we don't care about the
	// factors themselves.

	std::vector<long long> iFactors;
	int iFactorSum;

	std::vector<long long> jFactors = {};

	for (int i = 2; i <= N; i++) {
		//std::cout << "i = " << i << std::endl;
		iFactors.clear();
		getFactorsVec(i, iFactors);
		iFactorSum = std::accumulate(iFactors.begin(), iFactors.end(), 0) - i;
		//std::cout << "Factor sum: " << iFactorSum << std::endl;
		if (iFactorSum > i) {
			jFactors.clear();
			getFactorsVec(iFactorSum, jFactors);
			if ( (std::accumulate(jFactors.begin(), jFactors.end(), 0) - iFactorSum) == \
				i ) {
				//std::cout << i << " and " << iFactorSum << " are amicable!\n";
				ans += i + iFactorSum;
			}
		}

	}


	return std::to_string(ans);
}
