#include <iostream>
#include <string>
#include <cmath>

std::string problem28() {
// Find sum of diagonals in a number spiral starting from 1 in center.
// 1001 x 1001 sprial

/*
Example spiral

21 22 23 24 25
20 07 08 09 10
19 06 01 02 11
18 05 04 03 12
17 16 15 14 13

diagonalSum = 21 + 25 + 7 + 9 + 1 + 5 + 3 + 17 + 13 = 101

In high school I solved this by actually constructing the array.
I'd like to avoid creating an 1Mb+ array this time.

We can see that the end of our spiral is a square number on the top-right.
In a 5x5 example, the last number is 5^2.
We can calculate the last number in our big 1001 x 1001 spiral the same way.

Additionally, we can look at the spacing between diagonal spaces.
It goes [1, +2, +2, +2, +2 [spiral end], +4, +4, +4, +4 [spiral end],
+6, +6, +6, +6 [spiral end], etc.

Therefore, we can sum this up easily in a loop without making any arrays.
*/

	int spiralNum = 1;
	int addFactor = 2;
	int sum = 1;
	int N = 1001;

	while (spiralNum < std::pow(N,2)) {
		for (int i = 0; i < 4; i++) {
			spiralNum += addFactor;
			sum += spiralNum;
		}
		addFactor += 2;
	}

	return std::to_string(sum);
}
