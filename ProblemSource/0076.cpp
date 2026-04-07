#include "eulerUtils.h"
#include <iostream>
#include <string>

long long recursiveNumSums(int, int, long long **);

std::string problem76() {
// How many different ways can 100 be written
// as a sum of at least 2 positive ints?

/*

I think we'll use a recursive method here where we
count the number of ways to write a number X with
a maximum number Y

The function works well with 2 arguments but takes too
long due to the number of recursive calls with the same
arguments. Making a simple 2D array with previous answers
to numSums(N, maxNum) speeds things up tremendously


*/

	const int N = 100;
	long long ans;

	// Single answer:
	// Create lookup table for speed
	long long **lookupDb; // Double pointer to easily pass 2D array
	lookupDb = new long long *[N];
	for (int i = 0; i < N; i++) {
		lookupDb[i] = new long long[N];
		for (int j = 0; j < N; j++) // Clear entries
			lookupDb[i][j] = 0;
	}

	ans = recursiveNumSums(N,N-1,lookupDb);

	// Clean up your memory!
	for (int i = 0; i < N; i++) {
		delete[] lookupDb[i];
	}
	delete[] lookupDb;

	// Multiple answers:
	/*
	for (int i = 1; i <= N; i++) {
		// Create lookup table for speed
		long long **lookupDb; // Double pointer to easily pass 2D array
		lookupDb = new long long *[i];
		for (int j = 0; j < i; j++) {
			lookupDb[j] = new long long[i];
			for (int k = 0; k < i; k++) // Clear entries
				lookupDb[j][k] = 0;
		}

		ans = recursiveNumSums(i,i-1,lookupDb);

		// Clean up your memory!
		for (int j = 0; j < i; j++) {
			delete[] lookupDb[j];
		}
		delete[] lookupDb;

		std::cout << "i: " << i << " Sums: " << ans << std::endl;
	}
	*/
	return std::to_string(ans);
}

long long recursiveNumSums(int N, int maxNum, long long ** ansDb) {
	long long ans = 0;

	//std::cout << "N: " << N << " max num: " << maxNum << std::endl;

	if (maxNum == 0) { // This allows N=1 to give a valid answer of 0
		ans = 0;
	} else if ( (N == 1) || (maxNum == 1)) { // Base case - only one way to sum
		ans = 1;
	} else {
		if (maxNum >= N) // Can use single number to sum to 'N'
			ans = 1;
		// Break N into i + (N-i) and recurse on 'i'
		for (int i = maxNum; i > 0; i--) {
			if ( (N - i) > 0 ) {
				// Add ans to our database
				if (ansDb[N-i][i] == 0)
					ansDb[N-i][i] = recursiveNumSums(N-i,i,ansDb);
				ans += ansDb[N-i][i];
			}
		}
	}
	//std::cout << "(" << N << "," << maxNum << ") Ans: " << ans << std::endl;
	return ans;
}
