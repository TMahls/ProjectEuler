#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <cmath>

std::string problem9() {
// Find the pythagorean triplet (a^2 + b^2 = c^2) where a+b+c=1000, return abc

	float a;
	for (int c = 2; c < 1000; c++) {
		for (int b = 1; b < c; b++) {
			a = std::sqrt(std::pow(c,2) - std::pow(b,2));
			if ( (a == std::floor(a)) && ((a + b + c) == 1000) ) {
				std::cout << "a: " << a << " b: " << b << " c: " << c << std::endl;
				return std::to_string((int)(a) * b * c);
			}
		}
	}

	return "";
}
