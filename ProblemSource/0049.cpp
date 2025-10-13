#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <algorithm>

std::string problem49() {
// 1487, 4817, 8147 are all prime,
// arithmetically increasing, and permutations of each other.
// There's one other 4-digit sequence with this property. Return
// the 12-digit concatenation of this sequence.

	std::string ans;
	int searchNum = 1001;
	unsigned int nTerms = 3;
	bool found = false;

	std::vector<int> perms;
	std::string testStr;

	int diff;
	while (!found && (searchNum < 10000)) {
		if (isPrime(searchNum)) {
			// Get all prime permutations
			perms = {searchNum};
			testStr = std::to_string(searchNum);
			while(!isReverseSorted(testStr)) {
				testStr = getNextPerm(testStr);
				if (isPrime(std::stoi(testStr)))
					perms.push_back(std::stoi(testStr));
			}

			// Sort
			std::sort(perms.begin(), perms.end());

			// Potential candidate
			if ( (perms.size() >= nTerms) && (!isPerm(std::to_string(searchNum),"1487")) ) {
				/*
				std::cout << "Prime perms: ";
				for (int i : perms)
					std::cout << i << " , ";
				std::cout << std::endl;
				*/

				/*
				This next part is a little messy. From our set of prime permutations, we
				want to try out different starting points and different jumps, each will give
				us a diff. We do this because our prime permutations array could look like this:
				a, b, c, d, e, f, g

				And the answer could be [a,b,c], or [a,c,e], or [c,e,g], or [a,d,g], or [d,e,f], etc.
				We need to try all of these. It's probably quite slow but thankfully by the time we
				get here we're only looking at a handful of candidate perm arrays.

				We add that diff to the second number to get our third number. If the third
				number is a prime permutation, we did it!
				*/

				for (unsigned int startIdx = 0; startIdx < (perms.size()-1); startIdx++) {
					for (unsigned int idxJump = 1; idxJump < (perms.size()-startIdx); idxJump++) {
						diff = perms[startIdx+idxJump] - perms[startIdx];
						testStr = std::to_string(perms[startIdx] + 2 * diff);
						if ( isPerm(testStr, std::to_string(perms[startIdx])) && \
							isPrime(std::stoi(testStr)) ) {
							ans += std::to_string(perms[startIdx]);
							ans += std::to_string(perms[startIdx] + diff);
							ans += testStr;
							found = true;
						}
					}
				}
			}
		}

		searchNum += 2;
		if ( (searchNum % 10) == 5)
			searchNum += 2;
	}



	return ans;
}
