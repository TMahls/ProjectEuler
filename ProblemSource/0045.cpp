#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <cmath>

std::string problem45() {
// Find the second number that is triangle, pentagonal, and hexagonal
// T_n = n(n+1)/2
// P_n = n(3n-1)/2
// H_n = n(2n-1)
// The first is 40755

/*

Let's iterate thru hexagonal numbers
The diff between H_n and H_n+1 = 4n + 1

All hexagonal numbers are triangle numbers
I can't prove it but it just seems true, lol

*/
	bool found = false;
	int n = 143; // We are given 40755 = H_143
	long long Hn = 40755;
	double calc;
	while (!found) {
		Hn += (4*n + 1); // Next hexagonal number
		calc = (1+std::sqrt(1 + 24*Hn))/6; // Pentagonal check
		if ( std::floor(calc) == calc )
			found = true;
		n++;
	}

	return std::to_string(Hn);
}
