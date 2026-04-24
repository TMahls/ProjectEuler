#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <cmath>

std::string problem86() {
// Cuboid (rectangular prism) route
// For a cuboid A x B x C, you can calculate
// the shortest route to get to opposite corners.
// When using integer side lengths, sometimes that's
// an int. Let f(M) be the # of cuboids with int sides
// up to M x M x M where that's true.
// Given: f(99) = 1975, f(100) = 2060
// Find first x where f(x) > 1e6

/*
Seems like we should generate cuboids
with int sides + shortest lengths here.

For a by b by c cuboid, we are trying to get from S to E:

  ---------E
 |         |
 |         c
 |         |
 /----------
/	  b
S---a-----

Our tuning parameter is (m). Our path is the following

--m--------
|  /      |
b /       |
|/        |
S----a-----
-----------E
|        / |
c       /  |
-----(a-m)---

Length: sqrt(b^2 + m^2) + sqrt((a-m)^2 + c^2)
Find 'm' such that the minimum of this is an integer.

This is a distinct cuboid -- so we will generate
them in order: a <= b <= c

*/

	int N = 10;
	int counter = 0;
	double m, D;
	int intCubeCounter = 0;
	for (int c = 1; c <= N; c++) {
		for (int b = 1; b <= c; b++) {
			for (int a = 1; a <= b; a++) {
				m = (double)(b*c)/(a+b);
				//std::cout << "m = " << m;
				D = std::sqrt(a*a+std::pow(c-m,2)) + std::sqrt(b*b+m*m);
				//std::cout << "-> " << a << ", " << b << ", " << c << ", " << D << std::endl;

				if ( (D - std::floor(D)) <= 1e-8 ) {
					std::cout << "Found " << a << ", " << b << ", " << c << ", " << D << std::endl;
					intCubeCounter++;
				}
				counter++;
			}
		}
	}

	std::cout << "N: " << N << " Distinct cuboids: " << counter << std::endl;
	std::cout << "Int cuboids: " << intCubeCounter << std::endl;

	return std::to_string(counter);
}
