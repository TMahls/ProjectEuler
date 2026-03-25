#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <cmath>

std::vector<int> getPrimeSet(std::vector<int>, std::vector<int>, char, char);

std::string problem60() {
// Find set of 5 primes with the lowest sum with this property:
// Can concatenate any 2 primes in the set to get another prime
// Ex w/ 4: 3, 7, 109, 673

/*
I solved this one in MATLAB while at work, and it was
pretty darn slow (30+ seconds, yikes!) but the concept was
there.
*/
	int N = 5;
	int primeLimit = 1e4; // Abritrarily chosen
	std::vector<int> primeDb = getAllPrimes(primeLimit);

	/*
	std::cout << "primeDb: [";
	for (int i : primeDb)
		std::cout << i << ", ";
	std::cout << std::endl;
	std::cout << "Size: " << primeDb.size() << std::endl;
	*/

	std::vector<int> ans = getPrimeSet(primeDb, {}, 0, N);

	std::cout << "Primes: ";
	for (int i : ans)
		std::cout << i << ", ";
	std::cout <<  std::endl;

	return std::to_string(std::accumulate(ans.begin(), ans.end(), 0));
}

// Recursive method that builds a set of primes with this property, and stops once
// we reach our 'target recursion depth', or number of primes.
std::vector<int> getPrimeSet(std::vector<int> primeDb, std::vector<int> currPrimeIdx, char currDepth, char targetDepth) {

	// Make ans the primes referenced by currPrimeIdx
	std::vector<int> ans;
	for (int i : currPrimeIdx)
		ans.push_back(primeDb.at(i));

	// Test to see if it works
	bool works = true;
	unsigned char i = 0;
	unsigned char iNDigits;
	unsigned char j = 0;
	unsigned char jNDigits;
	if (ans.size() > 0) { // During our first attempt where currPrimeIdx is {} this will be false
		j = ans.size() - 1;
		jNDigits = std::log(ans.at(j))/std::log(10) + 1;
	}
	int concatPrime;
	// We actually only have to check how everything concats with our last prime
	// since we will only get here if the rest of the set already works amongst themselves.
	// This means we don't have to check prime concats we've already checked.
	while ( works && (i < j) ) {
		//std::cout << "iVal: " << ans.at(i) << " jVal: " << ans.at(j) << std::endl;

		concatPrime = ans.at(i) * std::pow(10, jNDigits) + ans.at(j);
		//std::cout << "Testing concat prime: " << concatPrime << std::endl;
		works = isPrime(concatPrime);

		if (works) {
			iNDigits = std::log(ans.at(i))/std::log(10) + 1;
			concatPrime = ans.at(j) * std::pow(10, iNDigits) + ans.at(i);
			//std::cout << "Testing concat prime: " << concatPrime << std::endl;
			works = isPrime(concatPrime);
		}

		i++;
	}

	/*
	if (works && (currDepth > 1)) {
		std::cout << "This set works:\n";
		std::cout << "currPrimeIdx: [";
		for (int i : currPrimeIdx)
			std::cout << i << ", ";
		std::cout << std::endl << "Primes: [";
		for (int i : ans)
			std::cout << i << ", ";
		std::cout << std::endl;
	}
	*/

	if ( (currDepth == targetDepth) && works) {
		// On success - return ans
		return ans;
	} else if (!works){
		// Curr set does not work
		ans = {};
		return ans; // Return blank array in case of failure
	} else {
		// Current set works now but we need to add more primes
		// Recursive case - test all next primes
		int startIdx;
		if (currPrimeIdx.size() < 1)
			startIdx = 1; // Start at the second prime since we know 3 doesn't work
		else
			startIdx = currPrimeIdx.at(currPrimeIdx.size() - 1) + 1;

		//std::cout << "Start idx: " << startIdx << std::endl;
		std::vector<int> testPrimeSet = currPrimeIdx;
		for (unsigned int testPrimeIdx = startIdx; testPrimeIdx < primeDb.size(); testPrimeIdx++) {
			testPrimeSet.push_back(testPrimeIdx);
			// Recursion call with new IDX set
			ans = getPrimeSet(primeDb, testPrimeSet, currDepth + 1, targetDepth);
			testPrimeSet = currPrimeIdx;
			if (ans.size() != 0) // Success
				return ans;
		}
	}

	ans = {};
	return ans; // Return blank array in case of failure
}
