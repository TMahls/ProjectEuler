#include "eulerUtils.h"
#include <iostream>
#include <string>

long long recursiveNumPrimeSums(int, int, long long **, std::vector<int>);

std::string problem77() {
// What's the first value that can be written as the sum
// of primes in over 5000 ways?

/*
Similar to the last problem but instead
of summing with natrual numbers we are summing with primes.
For speed we'll make a prime database of numbers we can add with

*/

	const int targetNum = 5000;
	const int N = 100; // How large our prime DB and answer DB is
	// This is a bit of a 'tuned value' that you scale up
	long long ans = 0;

	// Prime db
	std::vector<int> primeDb = getAllPrimes(N);

	// Create lookup table for speed
	long long **lookupDb; // Double pointer to easily pass 2D array
	lookupDb = new long long *[N];
	for (int i = 0; i < N; i++) {
		lookupDb[i] = new long long[N];
		for (int j = 0; j < N; j++) // Clear entries
			lookupDb[i][j] = 0;
	}

	int i = 4;
	int iIdx = 0;
	while (ans <= targetNum) {
		while (primeDb[iIdx] < i)
			iIdx++;
		if (iIdx > 0)
			iIdx--;
		ans = recursiveNumPrimeSums(i,iIdx,lookupDb,primeDb);
		//std::cout << "i: " << i << " ans: " << ans << std::endl;
		i++;
	}
	ans = i - 1;

	// Clean up your memory!
	for (int i = 0; i < N; i++) {
		delete[] lookupDb[i];
	}
	delete[] lookupDb;

	return std::to_string(ans);
}

long long recursiveNumPrimeSums(int N, int maxNumIdx, long long ** ansDb, std::vector<int> primeDb) {
	long long ans = 0;
	int testNum;
	//std::cout << "N: " << N << " Max prime: " << primeDb[maxNumIdx] << std::endl;

	if ( N < primeDb[0] ) { // Base case - Can't add up to 1
		ans = 0;
	} else if ( ((N == 2) && (maxNumIdx >= 0)) || \
		((N == 3) && (maxNumIdx >= 1)) ) { // Base case - one way to add to 2 and 3
		ans = 1;
	} else { // Recursive case
		// Break N into i + (N-i) and recurse on 'i'
		for (int i = maxNumIdx; i >= 0; i--) {
			testNum = N - primeDb[i];
			if ( testNum > 0 ) {
				// Add ans to our database
				if (ansDb[testNum][primeDb[i]] == 0)
					ansDb[testNum][primeDb[i]] = recursiveNumPrimeSums(testNum,i,ansDb,primeDb);
				ans += ansDb[testNum][primeDb[i]];
			} else if ( testNum == 0 ) { // Even addition
				if (ansDb[testNum][primeDb[i]] == 0)
					ansDb[testNum][primeDb[i]] = 1;
				ans++;
			}
		}
	}
	//std::cout << "(" << N << "," << primeDb[maxNumIdx] << ") Ans: " << ans << std::endl;
	return ans;
}
