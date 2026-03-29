#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <cmath>

std::vector<int> getAllTerms(int);

std::string problem66() {
// For each D in x^2 - Dy^2 = 1, there is a minimum
// integer solution for x. For D <= 1000, which D has
// the largest minimum x value.
// Assume that if D is square there are no positive int solutions.

/*
Problem 100 (which I did before this one) also invovled a Pell Equation.
Pell's equation is a subset of Diophantine equations of the form:
x^2 - ny^2 - 1. So exactly this problem.

The Wikipedia page on Pell's equation relates this to root approximations
and continued fractions, which we just did in Problems 64 and 65!
We are trying to find the 'fundamental' solution which minimizes x.

Let's say we have a fraction approximation a/b of sqrt(D). [We can generate these from 64/65]
The fundamental solution is given as:

(x_min, y) = (a_r-1, b_r-1) if r is even
	   = (a_2r-1, b_2r-1) if r is odd

Where r is the period length. Examples
sqrt(7) = [2;(1,1,1,4)] -> Use [2, 1, 1, 1] for fraction
sqrt(13) = [3;(1,1,1,1,6)] -> Use [3, 1, 1, 1, 1, 6, 1, 1, 1, 1] for fraction

I don't entirely undertand why this works. But it's simple to implement based on what we've
already done!

This seems like a good paper for more context:
https://www.ams.org/notices/200202/fea-lenstra.pdf

*/
	int N = 1000;

	int ans = 0;
	BigInt biggestNum("0");

	for (int D = 2; D <= N; D++) {
		// Get repeating terms and get to right length
		std::vector<int> allTerms = getAllTerms(D);
		int periodLength = allTerms.size() - 1;
		if ((periodLength % 2) == 0) { // Even period
			allTerms.erase(allTerms.begin() + periodLength);
		} else { // Odd period
			for (int i = 1; i < periodLength; i++)
				allTerms.push_back(allTerms.at(i));
		}

		// If square, skip
		if (periodLength != 0) {

			// Print terms
			/*
			std::cout << "D: " << D << " Terms: [";
			for (int i : allTerms)
				std::cout << i << ", ";
			std::cout << std::endl;
			*/

			// Calculate fraction from terms array
			BigInt fracNum(1);
			BigInt prevNum;
			BigInt fracDem(allTerms.at(allTerms.size() - 1));

			int currTerm;

			int i = allTerms.size() - 2;
			while ( (i >= 0) ) {
				currTerm = allTerms.at(i);

				if (i == 0) {
					fracNum = currTerm * fracDem + fracNum;
				} else {
					prevNum = fracNum;
					fracNum = fracDem;
					fracDem = currTerm*fracDem + prevNum;
				}
				i--;
			}

			if (fracNum > biggestNum) {
				biggestNum = fracNum;
				ans = D;
			}

			/*
			std::cout << "D: " << D << " x: " << fracNum << \
				 " y: " << fracDem << std::endl;
			*/
		}
	}

	return std::to_string(ans);
}

std::vector<int> getAllTerms(int n) {
// Get terms of regular continued fraction for sqrt(n)
// The first term is floor(sqrt(N)), and the rest are the repeating part

	int a0,a,b,b_prev,c;
	int aMatch,bMatch,cMatch; // Our first terms that we are looking for
	bool rational;
	bool periodFound;
	int periodCount;

	std::vector<int> ans;

	rational = false;
	periodFound = false;
	periodCount = 0;
	a0 = std::floor(std::sqrt(n));
	a = a0;
	b = 1;
	c = a0;
	ans.push_back(a0);
	while ( !periodFound && !rational ) {
		if (n == c*c) { // Rational fraction
			rational = true;
			a = 0;
			periodCount = -1; // Gives period count of 0
		} else {
			a = (b*(a0+c)) / (n - c*c);
			b_prev = b;
			b = (n - c*c) / b;
			c = (a*(n-c*c))/b_prev - c;
			if (periodCount == 0) {
				aMatch = a;
				bMatch = b;
				cMatch = c;
			} else {
				periodFound = (a == aMatch) && \
						(b == bMatch) && \
						(c == cMatch);
			}
			if (!periodFound)
				ans.push_back(a);
		}
		periodCount++;
	}

	return ans;
}
