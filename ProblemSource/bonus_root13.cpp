#include "eulerUtils.h"
#include <iostream>
#include <string>

std::string problembonus_root13() {
// Bonus Problem sqrt(13):
// Sum of first 1000 decimal digits of sqrt(13)
// I unlocked this after completing problem 51, for some reason

/*
Thanks to the wikipedia page for Square Root Algorithms
for the following digit-by-digit calculation example.
Not super creative, we use BigInt and do one digit at a time.

This method seems to work for finding any integer square roots,
with no floating point calculations.

It's a bit slow but just fast enough to squeak under my time requirement.
*/

	int root = 13;
	int nDigits = 1000;
	short ans = 0;

	int nDigit = 0;
	int x;
	BigInt p("0");
	BigInt c(root);
	BigInt y;
	char currDigit;

	std::cout << "sqrt(" << root << ") = ";
	while (nDigit <= nDigits) {
		x = 0;
		while ((x*(20*p + x)) <= c)
			x++;
		x--;

		y = x*(20*p + x);
		if (nDigit == 0)
			p = x;
		else
			p = 10*p + x;
		c = (c-y) * 100;

		currDigit = x;
		//std::cout << "x: " << x << " p (root) " << p << " c (val) " << c << std::endl;
		std::cout << (int)currDigit;
		if (nDigit == 0)
			std::cout << ".";
		else
			ans += currDigit;

		nDigit++;
	}
	std::cout << std::endl;

	return std::to_string(ans);
}
