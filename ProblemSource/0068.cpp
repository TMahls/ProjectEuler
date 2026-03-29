#include "eulerUtils.h"
#include <iostream>
#include <string>

void recursiveCreateNGonArray(bool *, char *, const int);

std::string problem68() {
// Arranging the numbers 1-10 on a special shape (see site)
// such that each of the 5 lines have the same sum.
// When listing all solutions for this, starting from lowest external
// node value and going clockwise you can make a 16 or 17 digit number.
// What's the maximum 16-digit string for the ring?

/*
Convoluted setup, but basically we need to get all solutions, turn them
into strings, and decide which one is largest.

Each of the N lines has 3 members: [a1,a2,a3]
Going clockwise, the next lines will have [b1,a3,b3], [c1, b3, c3]
And finally the last line_3 must match a2.
That rule, using every number once, and each line of 3 having the same sum means
we can probably just build these up.

We want to find maximal solutions, so our first node should be N+1.

The 16 vs. 17 string differentiation means that 10 must be an outer node.

Ideally my method will start with the largest value first, decrease, and just
print out the first solution it finds.

I'd also like to make the N in N-gon variable so I can test it out on the example.

Index convention: We take outer node and connected middle as [0,1]
then the next pair of outer + middle as [2,3]

Lines in 3-gon are [0 1 3], [2 3 5], [4 5 1]
Likewise, 5-gon are [0 1 3], [2 3 5], [4 5 7], [6 7 9], [8 9 1]
Even numbers are our independent nodes.
We will place numbers in this order.
*/

	const int N = 5; // N-gon

	bool numsPlaced[2*N]; // What numbers we've placed so far
	char ansArray[2*N]; // Our final answer

	// Populate arrays
	for (unsigned int i = 0; i < (sizeof(ansArray)/sizeof(char)); i++) {
		numsPlaced[i] = false;
		ansArray[i] = 0;
	}

	// The magic
	recursiveCreateNGonArray(numsPlaced, ansArray, N);

	// Create string from ans array
	/*
	std::cout << "Original ans: [";
	for (int i = 0; i < (2*N); i++)
		std::cout << (int)ansArray[i] << ", ";
	std::cout << "]\n";
	*/

	std::string ans = "";
	for (int i = 0; i < (2*N); i+=2) {
		ans += std::to_string((int)ansArray[i]);
		ans += std::to_string((int)ansArray[i+1]);
		ans += std::to_string((int)ansArray[(i+3)%(2*N)]);
	}

	return ans;
}

void recursiveCreateNGonArray(bool * numsPlaced, char * ansArray, const int N) {
	/*
	std::cout << "Nums Placed: [";
	for (int i = 0; i < 2*N; i++)
		std::cout << numsPlaced[i] << ", ";
	std::cout << "]\nAns Array: [";
	for (int i = 0; i < 2*N; i++)
		std::cout << (int)ansArray[i] << ", ";
	std::cout << "]\n";
	*/

	// Find our current ring idx number
	int currRingIdx = 0;
	while (ansArray[currRingIdx] != 0)
		currRingIdx++;

	// Test placing highest numbers first
	int testNum = 2*N;
	bool solnFound = false;
	int lineSum;
	bool allowedToPlace;
	while (!solnFound && (testNum > 0)) {
		// Check if N has been already placed
		allowedToPlace = !numsPlaced[testNum - 1];

		// This is not an official rule but will guide us towards our desired soln
		// We want our independent nodes to start at N + 1 and increase.
		if (allowedToPlace && ((currRingIdx % 2) == 0)) {
			if (currRingIdx == 0)
				allowedToPlace = (testNum == (N+1));
			else
				allowedToPlace = (testNum > (N+1));
		}

		// If we are at a middle node, check sum with previous line
		// > 4 check because the first 2 middle nodes are 'free'
		if (allowedToPlace && ((currRingIdx % 2) != 0) && (currRingIdx > 4)) {
			lineSum = ansArray[0] + ansArray[1] + ansArray[3];
			allowedToPlace = ((testNum + ansArray[currRingIdx - 2] + \
				ansArray[currRingIdx - 3]) == lineSum);

			// Special case if we are placing the last number:
			// Check sum with current line
			if (allowedToPlace && (currRingIdx == (2*N-1))) {
				allowedToPlace = ((testNum + ansArray[1] + \
					ansArray[currRingIdx - 1]) == lineSum);
			}
		}

		if (allowedToPlace) {
			//std::cout << "Placing " << testNum << std::endl;

			// Add num to ansArray and numsPlaced
			numsPlaced[testNum - 1] = true;
			ansArray[currRingIdx] = testNum;

			// Recurse
			recursiveCreateNGonArray(numsPlaced, ansArray, N);

			// Check for soln found
			solnFound = (ansArray[2*N-1] != 0);

			// Undo array change if we didn't get a solution
			if (!solnFound) {
				numsPlaced[testNum - 1] = false;
				ansArray[currRingIdx] = 0;
			}
		}
		testNum--;
	}
}
