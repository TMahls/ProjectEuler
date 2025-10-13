#include "eulerUtils.h"
#include <iostream>
#include <string>

std::string problem20() {
// Digit sum of 100!

	int N = 100;

	BigInt bigFact(N);
	for (int i = N; i > 1; i--)
		bigFact *= BigInt(i);

	std::cout << N << "! = " << bigFact << std::endl;

	std::string bigFactStr = toString(bigFact);
	int digitSum = 0;
	for (unsigned int i = 0; i < bigFactStr.length(); i++)
		digitSum += char2num(bigFactStr[i]);

	return std::to_string(digitSum);
}
