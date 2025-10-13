#include "eulerUtils.h"
#include <iostream>
#include <string>

std::string problem33() {
// Find simplified denominator of product of the 4 fractions with this property:
// 2 digits in numerator and denominator, less than 1
// Can be 'naively' simplified, such as 49/98 = 4/8

/*
Fractions will be of the following form:
ax/ay = x/y
xa/ya = x/y -> a != 0
ax/ya = x/y
xa/ay = x/y

These equations can be cross-multiplied:
(10a+x)y = (10a+y)x
(10x+a)y = (10a+y)x
(10a+x)y = (10y+a)x
(10x+a)y = (10a+y)x

Turns out that given the constraints, only
the 4th category works. But I guess we were throrough...
*/

	long long numerator = 1;
	long long denominator = 1;
	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			for (int a = 0; a < 10; a++) {
				// ax / ay
				if ( (y > x) && (a != 0) ) {
					if ( (y*(10*a+x)) == (x*(10*a+y)) ) {
						//std::cout << a << x << "/" << a << y << " works 1\n";
						numerator *= (10*a+x);
						denominator *= (10*a+y);
					}
				}

				// xa / ya
				if ( (y > x) && (x != 0) && (y != 0) && (a != 0) ) {
					if ( (y*(10*x+a)) == (x*(10*y+a)) ) {
						//std::cout << x << a << "/" << y << a << " works 2\n";
						numerator *= (10*x+a);
						denominator *= (10*y+a);
					}
				}

				// ax/ya
				if ( ((10*y+a) > (10*a+x)) && (a != 0) && (y != 0) ) {
					if ( (y*(10*a+x)) == (x*(10*y+a)) ) {
						//std::cout << a << x << "/" << y << a << " works 3\n";
						numerator *= (10*a+x);
						denominator *= (10*y+a);
					}
				}

				// xa/ay
				if ( ((10*x+a) < (10*a+y)) && (x != 0) && (a != 0) ) {
					if ( (y*(10*x+a)) == (x*(10*a+y)) ) {
						//std::cout << x << a << "/" << a << y << " works 4\n";
						numerator *= (10*x+a);
						denominator *= (10*a+y);
					}
				}
			}
		}
	}

	//std::cout << numerator << "/" << denominator << " simplifies to ";
	simplifyFraction(&numerator, &denominator);
	//std::cout << numerator << "/" << denominator << std::endl;
	return std::to_string(denominator);
}
