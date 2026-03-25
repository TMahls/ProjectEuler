#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>
#include <cmath>

void rangeCheckAndAdd(std::vector<int> *, int);
std::vector<int> getCyclicSet(std::vector<int>, std::vector<int>);

std::string problem61() {
// Cyclic figurate numbers
// Find the only set of 6 cyclic 4-digit numbers where
// each polygonal type (triangle, square, pentagonal,
// hexagonal, heptagonal, octoganal) is represented by
// a different number in the set. Cyclic means last 2
// digits of previous number are same as first 2 digits of next
// (incl. last number to first)

/*
The cycle can be in any order, but we need to see which representatives are crossed off.
We'll use a recursive method for that where we feed a database of all figurate numbers
between 1000 and 9999. We generate this by using n of range 19 to 140.
This is calculated cuz 19 is the smallest number such that Octagonal n(3n-2) is 4 digit
And 140 is the largest number such that the Triangle number n(n+1)/2 is 4 digit. Used
quadratic formula to solve for these.
*/

	// Create database of relevant 4-digit numbers
	std::vector<int> numsDb;
	int testNum;
	for (int n = 19; n <= 140; n++) {
		// This can be smartified with a loop but whatever
		testNum = (n * (n + 1))/2; // Triangle
		rangeCheckAndAdd(&numsDb, testNum);
		testNum = n * n; // Square
		rangeCheckAndAdd(&numsDb, testNum);
		testNum = (n * (3*n - 1))/2; // Pentagonal
		rangeCheckAndAdd(&numsDb, testNum);
		testNum = n * (2*n - 1); // Hexagonal
		rangeCheckAndAdd(&numsDb, testNum);
		testNum = (n * (5*n - 3))/2; // Heptagonal
		rangeCheckAndAdd(&numsDb, testNum);
		testNum = n * (3*n - 2); // Octagonal
		rangeCheckAndAdd(&numsDb, testNum);
	}
	// Preserve unique elements
	std::sort(numsDb.begin(), numsDb.end());
	std::vector<int>::iterator last = std::unique(numsDb.begin(), numsDb.end());
	numsDb.erase(last, numsDb.end());

	/*
	std::cout << "Figurate nums: " << std::endl;
	for (unsigned int i = 0; i < numsDb.size(); i++)
		std::cout << numsDb.at(i) << " , ";
	std::cout << std::endl;
	*/

	std::vector<int> startVec;
	std::vector<int> ans = getCyclicSet(numsDb, startVec);

	std::cout << "Nums: ";
	for (int i : ans)
		std::cout << i << ", ";
	std::cout <<  std::endl;

	return std::to_string(std::accumulate(ans.begin(), ans.end(), 0));
}

void rangeCheckAndAdd(std::vector<int> * vecPtr, int testNum) {
	if ((1000 <= testNum) && (testNum <= 9999))
		vecPtr->push_back(testNum);
}

std::vector<int> getCyclicSet(std::vector<int> numDb, std::vector<int> currSet) {
// numDb - Array of all 4-digit triangle thru octagonal numbers
// currSet - Our current set of cyclic numbers
	std::vector<int> ans = {};

	if (currSet.size() == 6) {
		/*
		std::cout << "Checking Curr set: ";
		for (int i : currSet)
			std::cout << i << " , ";
		std::cout << std::endl;
		*/

		// Check to see if our cyclic set has all figurate nums represented
		bool figurate[6];
		for (int i = 0; i < 6; i++)
			figurate[i] = false;

		double testVal[6];
		int j;
		bool found;
		double a,b,c;
		for (int i : currSet) {
			// This can be smartified with a loop but whatever man
			c = -i;
			a = 0.5; b = 0.5; // Triangle num
			testVal[0] = (-b + std::sqrt(b*b - 4*a*c))/(2*a);
			a = 1; b = 0; // Square num
			testVal[1] = (-b + std::sqrt(b*b - 4*a*c))/(2*a);
			a = 1.5; b = -0.5; // Pentagonal num
			testVal[2] = (-b + std::sqrt(b*b - 4*a*c))/(2*a);
			a = 2; b = -1; // Hexagonal num
			testVal[3] = (-b + std::sqrt(b*b - 4*a*c))/(2*a);
			a = 2.5; b = -1.5; // Heptagonal num
			testVal[4] = (-b + std::sqrt(b*b - 4*a*c))/(2*a);
			a = 3; b = -2; // Octagonal num
			testVal[5] = (-b + std::sqrt(b*b - 4*a*c))/(2*a);

			// A number might be in multiple figurates. Ex all
			// hexagonal nums are triangle nums. Therefore, we search
			// backwards, looking for higher order numbers first.
			// This is not a perfect search but it works for this problem.
			j = 5;
			found = false;
			while (!found && (j >= 0)) {
				if (std::abs(testVal[j] - (int)testVal[j]) < 1e-8) {
					found = true;
					figurate[j] = true;
				}
				j--;
			}
		}

		/*
		std::cout << "Figurate: ";
		for (bool i : figurate)
			std::cout << i << " , ";
		std::cout << std::endl;
		*/

		bool works = true;
		unsigned int i = 0;
		while (works && (i < currSet.size())) {
			if (!figurate[i])
				works = false;
			i++;
		}

		if (works) {
			//std::cout << "OMGOMGOMGOMG\n";
			return currSet; // Success!
		} else {
			return ans; // Fail -- does not represent all figurate nums
		}
	} else { // Recurse by adding different cyclic numbers
		int prevNum = 0;
		if (currSet.size() > 0)
			prevNum = currSet.at(currSet.size() - 1);
		unsigned int i = 0;
		unsigned int j;
		int currNum;
		bool cyclic;
		bool unique;
		std::vector<int> testSet;
		while ( (ans.size() == 0) && (i < numDb.size()) ) {
			unique = true;
			testSet = currSet;
			//std::cout << "testing num " << numDb.at(i) << std::endl;
			currNum = numDb.at(i);

			// Cyclic check
			cyclic = (currSet.size() == 0) || ((currNum / 100) == (prevNum % 100));
			if (currSet.size() == 5) // Wrap to first num
				cyclic = (cyclic && ( (currNum % 100) == (currSet.at(0) / 100) ) );

			// Unique number check
			j = 0;
			while (unique && (j < currSet.size())) {
				if (currNum == currSet.at(j))
					unique = false;
				j++;
			}
			if (cyclic && unique) {
				testSet.push_back(numDb.at(i));
				/*
				std::cout << " Adding a num! Curr set:\n";
				for (int j : currSet)
					std::cout << j << " , ";
				std::cout << std::endl;
				*/
				ans = getCyclicSet(numDb, testSet);
			}
			i++;
		}
	}
	return ans;
}
