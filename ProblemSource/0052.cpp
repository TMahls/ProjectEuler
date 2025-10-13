#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <cmath>

std::string problem52() {
// Smallest number such that x, 2x, 3x, 4x, 5x, 6x
// are all permutations of each other

	char maxMultiple = 6;
	char currMultiple;
	bool found = false;
	bool failed;
	int searchNum = 11;

	while (!found) {
		//std::cout << "Searching: " << searchNum << std::endl;
		if (numDigits(maxMultiple * searchNum) > numDigits(searchNum))
			searchNum = std::pow(10, numDigits(searchNum) + 1);

		failed = false;
		currMultiple = maxMultiple;
		while ((currMultiple > 0) && !failed) {
			if ( !isPerm(std::to_string(searchNum * currMultiple), \
				std::to_string(searchNum)) )
				failed = true;
			currMultiple--;
		}

		if (!failed)
			found = true;

		searchNum++;
	}

	return std::to_string(--searchNum);
}
