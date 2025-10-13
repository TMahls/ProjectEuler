#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>

std::string problem46() {
// Goldmach 2nd conjecture - every odd composite is the sum of a prime
// and twice a square. This is false-- find the smmalest counter-example

/*

O = P + 2N^2

Let's get a list of 2N^2, a list of primes,
and start adding them against each other.

*/

	int N = 10000; // Max number to test for

	std::vector<int> squareDB;
	int n;
	int i = 0;
	while (n < N) {
		n += 4*i++ + 2;
		squareDB.push_back(n);
	}

	std::vector<int> primeDB = {3, 5, 7};
	int primeCheck = 11; // Don't need 2 for this problem.
	while (primeCheck < N) {
		if (isPrime(primeCheck))
			primeDB.push_back(primeCheck);

		primeCheck += 2;
		if ((primeCheck % 10) == 5)
			primeCheck += 2;

	}

	/*
	std::cout << "Primes: ";
	for (int i : primeDB)
		std::cout << i << std::endl;

	std::cout << "Double squares: ";
	for (int i : squareDB)
		std::cout << i << std::endl;
	*/

	// Create set by adding these together
	std::set<int> sumSet;
	for (unsigned int i = 0; i < squareDB.size(); i++)
		for (unsigned int j = 0; j < primeDB.size(); j++)
			sumSet.insert(squareDB[i] + primeDB[j]);

	// Check the set for non-prime odds under N
	int counterExample = 0;
	i = 3;
	bool found = false;
	while ( (i < N) && !found) {
		if (!isPrime(i) && (sumSet.count(i) == 0)) {
			found = true;
			counterExample = i;
		}
		i += 2;
	}
	return std::to_string(counterExample);
}
