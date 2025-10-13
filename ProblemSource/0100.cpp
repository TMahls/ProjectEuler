#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <cmath>

#define DEMO 0

std::string problem100() {
	// In a game with red discs and blue discs in a box, you can have exactly a 50%
	// probability of taking 2 blue discs. Ex: B = 15, R = 6
	// Find the first integer number of blue discs when total discs > 1e12

	/*
	N = total discs = R (red discs) + B (blue discs)
	We are given (B / N) * ((B-1)/(N-1)) = 1/2
	You can use the quadratic formula to solve for B in terms of N
	or N in terms of B
	We must find integer solutions for B and N.
	For this we can start with a brute force approach.
	We use B = (1 + sqrt(1 + 2N(N-1))/2 and iterate N
	*/

	if (DEMO) {
		long long N = 1e6; // Long long necessary for accurate calculation!
		long long n = 3; // Min 2 blue discs 1 red disc
		double b;
		while (n++ < N) {
			b = (1 + std::sqrt(1 + 2*n*(n-1)))/2;
			if (std::floor(b) == b)
				std::cout << "N = " << n << "\tB = " << b << std::endl;
		}
	}

	/*
	From this we quickly get several N and B pairs:
	|   N   |   B   |
	|-------|-------|
	| 4     | 3     |
	| 21    | 15    |
	| 120   | 85	|
	| 697   | 493	|
	| 4060  | 2871	|
	| 23661 | 16731	|
	| 137904| 97513	|
	| 803761| 568345|

	Since iterating in the 1e12 scale is not feasible, we should instead
	find an equation to keep generating this table.

	One cheap (albeit common) way is by searching up this sequence on Sloane's
	Online Encyclopedia of Integer Sequences (OEIS). We find here both N (A046090)
	and B (A011900), as well as the parametric equation for it.

	That solves the problem, but I am not satisfied until I can derive the equation
	given by OEIS myself.

	Going back to our B = (1 + sqrt(1 + 2N(N-1))/2 equation, we can see that the main
	block of integer solutions is that square root. That is, we need to find N such
	that 1 + 2N(N-1) is a perfect square. It must also be an odd perfect square since we
	will add one and divide by 2. However, it is guaranteed to be odd by the '2N' term.

	This brings up the idea of diophantine pairs, where 2N and N-1 are the pair.
	Apparently this is also a Pell equation.

	1 + 2N(N-1) -> N^2 + (N-1)^2
	Therefore, we also need to find pythagorean triads of the form X, X+1, Z
	This was solved in the 1968 paper 'Pythagorean Triads of the form X, X+1, Z
	Described by Recurrence Sequences' (Forget and Larkin, Lockheed Missiles and Space Co)

	We will skip their derivation but use it.
	Essentially N = X + 1 = 2 * q_n * q_n+1 - (n % 2) + 1 [Eq 10 from paper]
	Where q_n = 2*q_n-1 + q_n-2, where q0 = 0 and q1 = 1

	*/

	// Equation from Forget and Larkin
	BigInt q_nm2; // q_0 = 0
	BigInt q_nm1(1); // q_1 = 1
	BigInt q_n(2); // q_2 = 2

	BigInt totalBalls;
	int n = 2;
	while (totalBalls < BigInt(1e12)) {
		q_nm2 = q_nm1;
		q_nm1 = q_n;
		q_n = 2 * q_nm1 + q_nm2;
		totalBalls = 2 * q_n * q_nm1 - (totalBalls % 2) + 1;
		n++;
	}

	BigInt intermediate;
	BigInt blueBalls;
	intermediate = 1 + 2*totalBalls*(totalBalls-1);
	blueBalls = (1 + sqrt(intermediate))/2;
	return toString(blueBalls);
}


