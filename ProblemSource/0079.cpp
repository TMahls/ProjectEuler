#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

std::string problem79() {
// Passcode derivation -- given file of 50 successful login attempts,
// where each one has 3 random (in order) characters of the passcode,
// construct the shortest possible password

/*
I solved this one on pen and paper after printing out the sorted list,
but I need to think of a way to do this algorithmically.

Overall I like the idea of, for each digit, storing which digits
come after it and before it. If there's a digit that no digits come before,
place that first. This probably can't deal with repeat digits but oh well.

We just go through that search the 'numsBefore' array and place chars
that have 0 chars before it, then 1, then 2, and so on until we've
placed every unique digit we've seen

*/

	// Get passwords from file
	std::string fileName = "./ProblemSource/0079_keylog.txt";
	std::vector<std::string> passVec = file2StringArray(fileName,"\n");

	// Sort name list
	std::sort(passVec.begin(), passVec.end());

	// Get minimum and maximum char
	//std::cout << "Pass strings:\n";
	char minChar = 127;
	char maxChar = 0;
	for (std::string i : passVec) {
		for (char j : i) {
			if (j > maxChar)
				maxChar = j;
			if (j < minChar)
				minChar = j;
		}
		//std::cout << i << std::endl;
	}

	// Init char precedence vector of sets
	std::set<char> passCharsSet;
	std::vector<std::set<char>> numsBefore;
	std::vector<std::set<char>> numsAfter;

	std::set<char> blank;
	for (char i = 0; i <= (maxChar-minChar); i++) {
		numsBefore.push_back(blank);
		numsAfter.push_back(blank);
	}

	// Get char precedence relationships
	char currChar, compChar;
	for (std::string i : passVec) {
		for (unsigned int j = 0; j < i.length(); j++) {
			currChar = i[j] - minChar;
			//std::cout << "Curr num: " << (int)currChar << std::endl;
			for (unsigned int k = 0; k < i.length(); k++) {
				compChar = i[k] - minChar;
				//std::cout << "Comp num: " << (int)compChar << std::endl;
				passCharsSet.insert(compChar);
				if (k < j)
					numsBefore[currChar].insert(compChar);
				else if (k > j)
					numsAfter[currChar].insert(compChar);
			}
		}
	}
	/*
	std::cout << "numsBefore: " << std::endl;
	for (std::set<char> i : numsBefore) {
		for (char j : i)
			std::cout << (int)j << ", ";
		std::cout << std::endl;
	}
	std::cout << "numsAfter: " << std::endl;
	for (std::set<char> i : numsAfter) {
		for (char j : i)
			std::cout << (int)j << ", ";
		std::cout << std::endl;
	}
	std::cout << "passCharsSet: " << std::endl;
	for (char i : passCharsSet)
		std::cout << (int)i << ", ";
	std::cout << std::endl;
	*/
	// Construct password
	std::string pass;
	bool placedAllChars = false;
	bool charInSet;
	unsigned char precedenceNum = 0;
	std::set<char>::iterator setIt = passCharsSet.begin();
	unsigned char currSetVal;
	while (!placedAllChars) {
		//std::cout << "Searching precedence " << (int)precedenceNum << std::endl;
		// Add all chars with curr precedence number
		for (unsigned char i = 0; i < numsBefore.size(); i++) {
			setIt = passCharsSet.find(i);
			charInSet = (setIt != passCharsSet.end());
			//std::cout << "Is " << (int)i << " in set? " << charInSet << std::endl;
			if (charInSet &&  (numsBefore[i].size() == precedenceNum)) {
				pass += minChar + i;
				//std::cout << "Pass: " << pass << std::endl;
			}
		}

		// Check if we've placed all chars in set
		placedAllChars = true;
		setIt = passCharsSet.begin();
		while ( placedAllChars && (setIt != passCharsSet.end()) ) {
			currSetVal = *setIt + 48;
			//std::cout << "Searching for " << (int)currSetVal << " in " << pass <<std::endl;
			placedAllChars = ( pass.find(currSetVal) != std::string::npos );
			//std::cout << "Found? " << placedAllChars << std::endl;
			setIt = std::next(setIt);
		}

		precedenceNum++;
	}

	return pass;
}
