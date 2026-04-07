#include "eulerUtils.h"
#include <iostream>
#include <string>

std::string problem71() {
// For ordered, fully reduced fractions n/d where d <= 1e6,
// find the numerator of the fraction just smaller than 3/7

/*
I feel like this one can be done on pen and paper
3/7 = 300,000 / 700,000
Can 299,999 / 700,000 work?
Ah unfortunately they share a factor of 7, so it'd be
42857 / 100000
Still worth a try! Nope, not right.

600,000 / 1,400,000 -> 599,999 / 1,400,000

3,000,000 / 7,000,000 -> 2,999,999 / 7,000,000

Procedure: Start by multiplying a and b by N
Subtract 1 from new a and simplify the fraction.
Does the simplified fraction have a denom less than N?
If so, use that! If not, decrease N by 1.
*/

	int N = 1e6;

	int mult = N;
	bool found = false;

	int num = 3*mult - 1;
	int den = 7*mult;
	long long numSimple, denSimple;

	while (!found && (mult > 1)) {
		//std::cout << "Mult: " << mult;

		//std::cout << " = " << num << "/" << den;
		numSimple = num;
		denSimple = den;
		simplifyFraction(&numSimple, &denSimple);
		//std::cout << " Simplified: " << numSimple << "/" << denSimple;
		if (denSimple <= N) {
			//std::cout << " WORKS!";
			found = true;
		}
		//std::cout << std::endl;
		num -= 3;
		den -= 7;
		mult--;
	}

	return std::to_string(numSimple);
}
