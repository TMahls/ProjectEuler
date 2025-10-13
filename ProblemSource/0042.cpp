#include "eulerUtils.h"
#include <iostream>
#include <string>

#define N 32

std::string problem42() {
// How many words in the file have an alphabetical score
// that is a triangle number?

/*
Let's just build a database of triangle numbers to check against.
Largest we'd need is probably 20 Z's in a row, so 20 * 26 = 520
520 * 2 = 1040, sqrt(1040) = 32.25ish
That'd be the first 32 triangle numbers.
*/


	int ans = 0;
	int triNumDatabase[N];

	for (int i = 0; i < N; i++) {
		triNumDatabase[i] = triangleNum(i);
	}

	// Get words from file
	std::string fileName = "./ProblemSource/0042_words.txt";
	std::vector<std::string> wordsVec = file2StringArray(fileName,",");

	std::string currString;
	int wordScore;

	bool found;
	int n;
	for (unsigned int i = 0; i < wordsVec.size(); i++) {
		currString = wordsVec.at(i);
		wordScore = 0;

		// Trim ""
		for (unsigned int j = 1; j < (currString.length() - 1); j++)
			wordScore += currString[j] - 64; // Assume all caps

		//std::cout << currString << " score: " << wordScore << std::endl;

		// Most values are gonna be small so it's fastest to start
		// at the beginnign of the array
		found = false;
		n = 0;
		while (!found && (triNumDatabase[n] <= wordScore)) {
			if (wordScore == triNumDatabase[n])
				found = true;
			n++;

		}

		if (found) {
			//std::cout << wordScore << " is a triangle num\n";
			ans++;
		}
	}


	return std::to_string(ans);
}
