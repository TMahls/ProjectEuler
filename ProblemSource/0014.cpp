#include "eulerUtils.h"
#include <iostream>
#include <string>

std::string problem14() {
	// Longest Collatz sequence with starting num < 1 million
	int n = 1e6;

	int longestSeqStartingNum = 1;
	int longestSeq = 1;
	int currSeqLength;

	// PDF Tip - We start at n/2 because for k = 1 thru n/2,
	// 2*k is represented in our set. Which has a collatz length
	// of collatz(k) + 1.
	for (int i = n/2; i < n; i++){
		currSeqLength = collatzSequenceLength(i);
		if (currSeqLength > longestSeq) {
			longestSeq = currSeqLength;
			longestSeqStartingNum = i;
		}
	}

	return std::to_string(longestSeqStartingNum);
}


