#include "eulerUtils.h"
#include <iostream>
#include <string>

std::string problem74() {
// Digit factorial sum: 1! + 4! + 5! = 145
// You can repeat this process to form chains. There are 3 loops:
// 169 -> 363601 -> 1454 -> 169
// 871 -> 45361 -> 871
// 872 -> 45362 -> 872
// Every number will eventually get stuck in a loop.
// The longest chain starting from < 1e6 is 60 terms.
// How many chains for starting number below 1e6 have exactly 60 terms?

/*
Kind of like the Collatz conjecture, but I guess this one is solved in
that we know every number ends up in a loop. Let's build a database
of chain lengths that we can lookup for speed.
*/

	const int N = 1e6;
	int ans = 0;

	// Create chain lookup table
	char chainLength[N];
	for (int i = 0; i < N; i++)
		chainLength[i] = 0;

	std::vector<unsigned int> termsVec;
	unsigned int currTerm, factorialSum, j;
	char currDigit;
	char termCount;
	bool chainOver, foundRepeat;
	for (int i = 1; i < N; i++) {
		currTerm = i;
		termCount = 0;
		chainOver = false;
		termsVec = {};
		while (!chainOver) {
			termsVec.push_back(currTerm);

			//std::cout << "Term: " << currTerm << std::endl;
			if ((currTerm < N) && chainLength[currTerm - 1] != 0) {
				// Easy - we have a lookup
				//std::cout << "Found lookup!\n";
				chainOver = true;
				termCount += chainLength[currTerm - 1] - 1;
			} else { // Calculate next term
				factorialSum = 0;
				while (currTerm > 0) {
					currDigit = currTerm % 10;
					factorialSum += factorial(currDigit);
					currTerm = (currTerm - currDigit) / 10;
				}

				currTerm = factorialSum;

				// Check for repeat term to know if we're done
				foundRepeat = false;
				j = 0;
				while (!foundRepeat && (j < termsVec.size())) {
					foundRepeat = (termsVec[j] == currTerm);
					j++;
				}
				if (foundRepeat) {
					chainOver = true;
				}

			}
			termCount++;
		}

		// Add to our database and increment answer if chain length is 60
		chainLength[i - 1] = termCount;
		if (termCount == 60) {
			//std::cout << "i: " << i << " terms: " << (int)termCount << std::endl;
			ans++;
		}
	}

	return std::to_string(ans);
}
