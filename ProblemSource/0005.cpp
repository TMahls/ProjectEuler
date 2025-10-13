#include "eulerUtils.h"
#include <iostream>
#include <string>

std::string problem5() {
	// Get the smallest number divisible by 1 thru 20
	int currNum = 380; // 20 * 19, smallest it could possibly be
	bool isDivisible = false;

	/*
	We are only checking multiples of 20, which will all be divisible by 1,2,4,5,10
	18 covers 9, 6, 3 so we can remove those
	16 covers 8
	15 covers 5
	14 covers 7
	Note -- for numbers larger than 20 you could create this array programatically
	*/

	int numsToCheck[9] = {19, 18, 17, 16, 15, 14, 13, 12, 11};
	int i;

	while (!isDivisible) {
		isDivisible = true;
		i = 0;
		while (i < 9 && isDivisible) {
			if (currNum % numsToCheck[i])
				isDivisible = false;
			i++;
		}
		currNum += 20;
	}

	return std::to_string(currNum - 20);
}
