#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <cmath>

std::string problem80() {
// For n = 1 to 100, sum first 100 digits for all
// irrational sqrt(n)

/*
This one is quite similar to bonus problem root(13) so
I will be copying my method from there.

Unlike problem 13 we are counting all digits, including before
decimal point.

Note this might not work for N > 100, since the digit count might change
when the int part of our square root becomes larger than 10
*/

	int N = 100;
	int nDigits = 100;
	int ans = 0;

	for (int root = 2; root <= N; root++) {
		int intRoot = std::sqrt(root);
		if ( std::abs(std::sqrt(root) - intRoot) > 1e-6 ) {
			int nDigit = 1; // Include first digit in sum
			int x;
			BigInt p("0");
			BigInt c(root);
			BigInt y;
			char currDigit;

			//std::cout << "sqrt(" << root << ") = ";
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
				//std::cout << (int)currDigit;
				//if (nDigit == 1)
					//std::cout << ".";
				ans += currDigit;

				nDigit++;
			}
			//std::cout << std::endl << "Sum: " << ans << std::endl;
		}
	}

	return std::to_string(ans);
}
