#include "eulerUtils.h"
#include <iostream>
#include <vector>
#include <string>

std::string problem24() {
// Millionth lexicographic permutation of "0123456789"

	int N = 1e6;
	std::string myString = "0123456789";

	/*
	This is the brute force solution that goes thru each permutation one at a time.
	This is too slow-- perhaps there's a way to get perm(n) assuming an ordred pair of digits.
	*/

	/*
	for (int i = 1; i < N; i++) {
		//std::cout << myString << std::endl;
		myString = getNextPerm(myString);
	}
	*/

	/*
	We need to decrement N to switch from the 0-index permutations
	to the 1-index the problem expects. That is, calling getNthPerm
	with N = 0 will give you an unchanged digits array, but in the
	context of the problem that's the first permutation.
	*/

	N--;
	myString = getNthPerm(myString,N);

	return myString;
}
