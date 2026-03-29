#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <cmath>

int getTermValue(int);

std::string problem65() {
// Similar to last problem, e has a continued fraction of:
// [2;1,2,1,1,4,1,1,6,1,...]
// Calculate the digit sum of the numerator for the 100th continued fraction

/*
I had a 'simplify fraction' method on hand but turns out you don't need to
use it at all. You just need some big int storage to continue multiplying
up the chain. This method starts at the very lowest terms and works its way
up, same way you'd do this on pen and paper.
*/

	int N = 100;

	int currTerm;

	BigInt fracNum(1);
	BigInt prevNum;
	BigInt fracDem(getTermValue(N-1));

	for (int i = (N-2); i >= 0; i--) {
		currTerm = getTermValue(i);
		//std::cout << "i: " << i << " term: " << currTerm << std::endl;

		if (i == 0) {
			fracNum = currTerm * fracDem + fracNum;
		} else {
			prevNum = fracNum;
			fracNum = fracDem;
			fracDem = currTerm*fracDem + prevNum;
		}
		//std::cout << "Num: " << fracNum << " Dem: " << fracDem << std::endl;
	}

	return std::to_string(digitSum(toString(fracNum)));
}

int getTermValue(int idx) {
// Return 2,1,2,1,1,4,1,1,6,1,... pattern
	if (idx == 0)
		return 2;
	else if ( (idx % 3) == 2)
		return (2*(idx+1)/3);
	else
		return 1;
}
