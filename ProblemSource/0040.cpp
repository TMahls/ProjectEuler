#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <cmath>

int champernowne(int);

std::string problem40() {
/*
Champernowne's Constant - find
d_1 * d_10 * d_100 * ... * d_1e6

Where d_n is the nth digit of this irrational
decimal fraction created by concatenating positive
integers:

0.12345691011121314...

Making a string many millions of characters
long would be wasteful, so let's make a general function
champernowne(n)

Heh, looks like in high school I did create the massive
string. It was probably quite slow and memory intensive

I thought originally it'd be a recusrive approach, but
after working out in a spreadsheet I think I've got it.

See the explanation in the 'champernowne' function header
*/

	int ans = 1;

	//for (int i = 1; i < 300; i++)
	//	std::cout << i << " : " << champernowne(i) << std::endl;

	int tenPow = 1;
	for (int i = 0; i <= 6; i++) {
		ans *= champernowne(tenPow);
		tenPow *= 10;
	}

	return std::to_string(ans);
}

int champernowne(int n) {
// Return the nth digit of Champernowne's Constant

/*
Explanation:
In the first while loop we acquire 3 important values:
The 'digit section' of the constant that d_n is in, and
the upper and lower bound n for that digit section.

nDigits = 1 is the first digit section, 1-9
nDigits = 2 is the 2-digit numbers, 10-99
etc.

With these 3 values, we can now simplify the problem
to just solving within a digit section (notice we use n - lowerBound
to normalize).

The digitNum is what digit we are within the digit section.
0 = largest digit (100s in nDigits = 3)
1 = second largest (10s in nDigits = 3)
2 = third largest (1s in nDigits = 3)
etc.

This determines the switching frequency, which is how
often we expect this number to change. For the example
above, this will be
digitNum = 0 -> 100
digitNum = 1 -> 10
digitNum = 2 -> 1

Finally, using the switching frequency and nDigits
we can get the expected digit at that position. The
use of integer (floor) division is important here.

This took some trial and error with a spreadsheet to get
right, I did not derive this fully on pen and paper lol (though I tried)
*/

	int nDigits = 1;
	int lowerBound = 1;
	int upperBound = 9;
	int tenPow = 1;
	while (upperBound < n) {
		lowerBound += nDigits * 9 * tenPow;
		tenPow *= 10;
		nDigits++;
		upperBound += nDigits * 9 * tenPow;
	//	std::cout << "Lower: " << lowerBound << " Upper: " << upperBound << std::endl;
	}

	//std::cout << "n: " << n << " digits: " << nDigits << std::endl;


	int digitNum = (n - lowerBound) % nDigits;

	int switchFrequency = std::pow(10, nDigits - 1 - digitNum);

	//std::cout << "Switch freq: " << switchFrequency << std::endl;

	int ans = ((n - lowerBound) / (nDigits * switchFrequency)) % 10;
	if (digitNum == 0) // First digit in new set starts at 1 [10, 100, 1000, etc.]
		ans++;

	return ans;
}
