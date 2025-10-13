#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

int triangleArrayLength(std::string, int);
void str2Array(std::string, long long *, int);
void dynamicRowSum(long long *, int);

std::string problem67() {
	// Maximum sum thru triangle II
	// The more difficult version of problem 18
	// Exact same code, this just needs to read from a file to create the initial string

	// Get triangle string from file
	std::string fileName = "./ProblemSource/0067_triangle.txt";

	std::string triangleStr = file2String(fileName," ");
	//std::string triangleStr = "03 07 04 02 04 06 08 05 09 03";

	int arrayLength = triangleArrayLength(triangleStr, 2);

	long long * triArray = new long long[arrayLength]();

	str2Array(triangleStr, triArray, 2);

	for (int row = (inverseTriangleNum(arrayLength) - 2); row >= 0; row--)
		dynamicRowSum(triArray, row);

	int ans = triArray[0];

	delete[] triArray;

	return std::to_string(ans);
}


int triangleArrayLength(std::string in, int digitsPerNum) {
// Calculate the length of the triangle array required
// Given the input string, and number of digits in the numbers

// We assume the following string format: "[X] [X]... [X] [X]"
// Where [X] are the numbers (of length digitsPerNum, with one space
// between all of them (no leading or trailing spaces.

	return (in.length() + 1) / (digitsPerNum + 1);
}


void str2Array(std::string in, long long * triArray, int digitsPerNum) {
// Convert a string of the above form into a 1-D numerical array
	int arrayIdx = 0;
	short currSpace;
	short factor;
	for (unsigned int i = 0; i < in.length(); i++) {
		currSpace = (i + 1) % (digitsPerNum + 1);
		if (currSpace) {
			factor = std::pow(10, digitsPerNum - currSpace);
			triArray[arrayIdx] += factor * char2num(in[i]);
		} else { // Start next number
			arrayIdx++;
		}
	}
}

void dynamicRowSum(long long * triArray, int currRow) {
// Replace currRow with currRow + max(rowBelow)
// Replace rowBelow with 0's
// Rows are 0-indexed, starting at the top.

	int rowStartIdx = triangleNum(currRow);
	int rowEndIdx = triangleNum(currRow + 1) - 1;

	// For each number in our current row
	int option1;
	int option2;

	for (int i = rowStartIdx; i <= rowEndIdx; i++) {
		// Get the 2 numbers in the row below
		option1 = triArray[rowEndIdx + 1 + (i - rowStartIdx)];
		option2 = triArray[rowEndIdx + 1 + (i - rowStartIdx) + 1];

		// Add the max to our current number
		if (option1 > option2)
			triArray[i] += option1;
		else
			triArray[i] += option2;

		// Replace the row with 0's (just option1, we still need option2)
		triArray[rowEndIdx + 1 + (i - rowStartIdx)] = 0;
	}
	// Zero the last element of the row below
	triArray[triangleNum(currRow + 2) - 1] = 0;
}
