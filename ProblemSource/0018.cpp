#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <cmath>

int triangleArrayLength(std::string, int);
void str2Array(std::string, long long *, int);
void dynamicRowSum(long long *, int);

std::string problem18() {
	// Maximum sum thru triangle

	std::string realTriangle = "75"
	" 95 64"
	" 17 47 82"
	" 18 35 87 10"
	" 20 04 82 47 65"
	" 19 01 23 75 03 34"
	" 88 02 77 73 07 63 67"
	" 99 65 04 28 06 16 70 92"
	" 41 41 26 56 83 40 80 70 33"
	" 41 48 72 33 47 32 37 16 94 29"
	" 53 71 44 65 25 43 91 52 97 51 14"
	" 70 11 33 28 77 73 17 78 39 68 17 57"
	" 91 71 52 38 17 14 91 43 58 50 27 29 48"
	" 63 66 04 68 89 53 67 30 73 16 69 87 40 31"
	" 04 62 98 27 23 09 70 98 73 93 38 53 60 04 23";

	std::string demoTriangle = "3"
	" 7 4"
	" 2 4 6"
	" 8 5 9 3";

	int realArrayLength = triangleArrayLength(realTriangle, 2);
	int demoArrayLength = triangleArrayLength(demoTriangle, 1);

	long long * realArray = new long long[realArrayLength]();
	long long * demoArray = new long long[demoArrayLength]();

	str2Array(realTriangle, realArray, 2);
	str2Array(demoTriangle, demoArray, 1);

	/*
	std::cout << "Real array: [";
	for (int i = 0; i < realArrayLength; i++)
		std::cout << realArray[i] << ", ";
	std::cout << "]" << std::endl;

	std::cout << "Dummy array: [";
	for (int i = 0; i < demoArrayLength; i++)
		std::cout << demoArray[i] << ", ";
	std::cout << "]" << std::endl;
	*/

	for (int row = (inverseTriangleNum(realArrayLength) - 2); row >= 0; row--)
		dynamicRowSum(realArray, row);

	int ans = realArray[0];

	delete[] realArray;
	delete[] demoArray;

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
