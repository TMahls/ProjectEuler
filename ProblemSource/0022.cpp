#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::string problem22() {
	// Names scores - Get sum of all name scores in file
	// Score = (alphabet letter score) * positionInSortedList

	// Get names from file
	std::string fileName = "./ProblemSource/0022_names.txt";
	std::vector<std::string> nameVec = file2StringArray(fileName,",");

	// Trim " from names
	std::string currString;
	for (unsigned int i = 0; i < nameVec.size(); i++) {
		currString = nameVec.at(i);
		nameVec.at(i) = currString.substr(1, currString.length() - 2);
	}

	// Sort name list
	std::sort(nameVec.begin(), nameVec.end());

	// Iterate thru name list to get score
	int scoreSum = 0;
	int alphabetScore;
	for (unsigned int i = 0; i < nameVec.size(); i++) {
		currString = nameVec.at(i);

		// Calculate alphabet score, assuming all capital letters
		alphabetScore = 0;
		for (unsigned int i = 0; i < currString.length(); i++)
			alphabetScore += currString[i] - 64;

		/*
		std::cout << "Name: " << currString << " Alphabet score: " << \
			alphabetScore << " Position score: " << i+1 << std::endl;
		*/
		scoreSum += (i + 1) * alphabetScore;
	}

	return std::to_string(scoreSum);
}

