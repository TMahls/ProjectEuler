#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <set>
#include <numeric>
#include <algorithm>

#define maxK 12000

std::vector<std::vector<int>> recursiveFactorSet(std::vector<long long>, int, int);

std::string problem88() {
// Find sum of all min product sum numbers for k = 2 thru 12000
// k is number of terms, "product sum number" is a number N such that
// N = a1 + a2 + ... + ak = a1 * a2 * ... * ak

/*
To make N as low as possible, you want as many 1's as possible.

For the minimal product sum number N(k), we can set an upper and lower bound
Lower bound - all 1's. 1 + 1 ... + 1, would mean N(k) = k. Of course this won't work
because 1 * 1 ... * 1 = 1

Upper bound - let's say I want all 1's and only the last 2 numbers to be non-1.

1 + 1 + ... + 1 + a + b = 1 * 1 * ... 1 * a * b - such that there are k terms total

Solve for a and b -- turns out we accomplish this with a = 2, b = k
Giving us a guaranteed way to get N(k) = 2k
For the example k = 3, 4, and 6 we see this employed

We can also get an upper limit to how many non-1 terms are in N(k).
Since N(k) <= 2k, and the lowest non-1 term we can have is 2, the most terms would be:
1 * ... * 1 * 2 * ...* 2. That would at most be log2(2k). For k <= 12000, we need at most 14
non-1 terms. So we can see that truly 1's dominate these sets.

The primary change of thinking here is -- instead of "given k, what set of numbers do I make"
think "given this set of numbers, how many 1's do I need to append to make it a prod-sum number.
What k value does that give?"

Instead of solving N(k) for each k linearly, we will search through a space
and add to a "best N(k)" database.

Now the real question becomes, what do these non-1 numbers look like?
They are always factors of N(k), since N(k) = 1 * 1 * ... * a1 * ... * an
However, they can be any size or permutation of factors. Let's consider factors for 8 (not incl. 1):

2 * 2 * 2
2 * 4

We see that these give optimal values for k  = 4 and k = 5, so we need an algorithm that can come up
with both of these. Meaning it's not enough to get all factors of a number, we also have to recursively
break them apart. Hence, our function 'recursiveFactorSet'-- which we set an upper bound on as previously.

Generating the factor breakdown set efficiently is the tricky bit. My first attempt led to a solution time
of around 30s in MATLAB, 11s in C++-- way too slow.

Eventually, finding a method that generated strictly increasing factor sets meant that
we did not have to process duplicates, allowing this to run in less than a second.

*/

	// We start by building a database of all factors for 2 thru 2k
	// Using a fixed-size array of variable sized vectors
	std::vector<long long> factorList[2*maxK - 1];

	for (int i = 0; i < (2 * maxK - 1); i++)
		getFactorsVec(i + 2, factorList[i]);

	int kDatabase[maxK - 1] = {};
	std::vector<std::vector<int>> factorBreakdown;
	std::vector<int> factorPerm;
	int factorSum, factorProduct, onesToAppend, k;
	for (int i = 0; i < (2*maxK - 1); i++) { // For each number 2 - 2k
		// Get the factor breakdown
		factorBreakdown = recursiveFactorSet(factorList[i], i+2, 1);

	/*
		std::cout << "Factor perms for " << i+2 << std::endl;
		for (std::vector<int> j : factorBreakdown) {
			std::cout << "[";
			for (int i : j)
				std::cout << i << ", ";
			std::cout << "]\n";
		}
	*/

		// Iterate through the list of factor expressions to get k values
		// Only get the 2nd of the list onward -- first is just N.
		factorProduct = i + 2;

		if ( (i + 2) <= maxK)
			kDatabase[i] = 2 * (i + 2); // Start with worst-case value

		for (unsigned int j = 1; j < factorBreakdown.size(); j++) {
			factorPerm = factorBreakdown.at(j);
			factorSum = std::accumulate(factorPerm.begin(), factorPerm.end(), 0);
			onesToAppend = factorProduct - factorSum;
			k = onesToAppend + factorPerm.size();
			if ((k <= maxK) && (factorProduct < kDatabase[k-2]))
				kDatabase[k - 2] = factorProduct;
		}
	}

	/*
	std::cout << "K database: [";
	for (int i = 0; i < (maxK - 1); i++)
		std::cout << kDatabase[i] << ", ";
	std::cout << "]\n";
	*/

	// Calculate sum of unique numbers
	int n = sizeof(kDatabase) / sizeof(kDatabase[0]);
	std::set<int> uniqueVals(kDatabase, kDatabase + n);
	int ans = std::accumulate(uniqueVals.begin(), uniqueVals.end(), 0);

	return std::to_string(ans);
}

std::vector<std::vector<int>> recursiveFactorSet(std::vector<long long> rootFactors, int currNum, \
int currFactorIdx) {
	// Given a number's factors, return all unique breakdowns of the factorization.
	// Ex - 24 = [1 2 3 4 6 8 12 24]
	// [24], [2 12], [2 2 6], [2 2 2 3], [2 3 4]
	// [3 8], [4 6]

	std::vector<std::vector<int>> factorBreakdown = {};

	factorBreakdown = {{currNum}};

	int newNum;
	std::vector<std::vector<int>> subFactors;

	// Iterate thru root factors. We start at 'currFactorIdx' to ensure our factors increase only
	// Our limit is one past the middle factor (ensure we cover square roots)
	for (unsigned int i = currFactorIdx; i <= std::floor(rootFactors.size()/2); i++) {
		newNum = currNum / rootFactors.at(i); // The number we find sub-factors of

		// Proceed if our curr target number is divisible by this root factor
		// Proceed only if new target >= our current factor (increasing list only)
		if ( !(currNum % rootFactors.at(i)) && (newNum >= rootFactors[i]) ) {
			subFactors = recursiveFactorSet(rootFactors, newNum, i);

			// Append i factor to the start of these subfactors
			for (std::vector<int> j : subFactors) {
				j.insert(j.begin(), rootFactors.at(i));
				factorBreakdown.push_back(j); // Add to factor breakdown
			}
		}
	}

	return factorBreakdown;
}
