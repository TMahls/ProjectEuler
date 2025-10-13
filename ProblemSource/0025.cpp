#include "eulerUtils.h"
#include <iostream>
#include <string>
std::string problem25() {
// Index of first fibonacci number with 1000 digits

	unsigned int N = 1000;
	int idx = 2;
	BigInt lastnum(1);
	BigInt num(1);
	BigInt nextnum;
	std::string numStr;
	do {
		nextnum = num + lastnum;
		lastnum = num;
		num = nextnum;
		numStr = toString(num);
		idx++;
		//std::cout << "idx: " << idx << " F(idx): " << num << std::endl;
	} while ( numStr.length() != N );

	return std::to_string(idx);
}
