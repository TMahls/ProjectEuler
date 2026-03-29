#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <cmath>

std::string problem62() {
// Find smallest cube such that 5 of its digit permutations are cube
// Ex: 345^3 = 41063625 is the smallest one where 3 perms are cube

	char N = 5; // How many matching permutations  we're looking for

	const int nCubes = 10000; // How many cubes to search
	char digitMap[nCubes][10] = {0}; // Format: 0123456789

	// Build database of cube digit counts
	unsigned long long cubeVal;
	std::string cubeString;
	for (int i = 1; i <= nCubes; i++) {
		cubeVal = std::pow(i,3);
		cubeString = std::to_string(cubeVal);
		for (char j : cubeString) {
			digitMap[i-1][(int)(j-48)]++;
		}
		/*
		std::cout << std::endl;
		std::cout << i << "^3 = " << cubeVal << " = [";
		for (int j = 0; j < 10; j++)
			std::cout << (int)digitMap[i-1][j] << ", ";
		std::cout << std::endl;
		*/
	}

	// Check for one that appears n times
	bool found = false;
	int i = 0;
	bool sameDigitNum;
	char iDigitNum;
	char jDigitNum;
	char appearCount;
	int j;
	bool matches;
	char k;
	while ((i < (nCubes - N)) && !found) {
		appearCount = 1;
		j = i + 1;

		// Count number of digits in i
		iDigitNum = 0;
		for (int n = 0; n < 10; n++)
			iDigitNum += digitMap[i][n];

		sameDigitNum = true;
		// Stop checking if our digit number count is off
		while (sameDigitNum && (appearCount < N) && (j < nCubes)) {
			// Count number of digits in j
			jDigitNum = 0;
			for (int n = 0; n < 10; n++)
				jDigitNum += digitMap[j][n];
			sameDigitNum = (iDigitNum == jDigitNum);

			matches = true;
			k = 0;
			while (matches && (k < 10)) {
				matches = (digitMap[i][(int)k] == digitMap[j][(int)k]);
				k++;
			}
			if (matches) {
				appearCount++;
			}
			j++;
		}
		found = (appearCount == N);
		i++;
	}

	unsigned long long ans = 0;
	if (found)
		ans = std::pow(i, 3);
	return std::to_string(ans);
}
