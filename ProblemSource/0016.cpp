#include "eulerUtils.h"
#include <iostream>
#include <string>

std::string problem16() {
	// What is the digit sum of 2^1000 ?

	BigInt base(2);
	BigInt exponent(1000);

	BigInt largePower;
	largePower = pow(base, exponent);

	std::string digitString = toString(largePower);

	std::cout << base << " ^ " << exponent << "  = " << digitString << std::endl;

	int ans = 0;
	for (unsigned int i = 0; i < digitString.length(); i++)
		ans += char2num(digitString[i]);

	return std::to_string(ans);
}
