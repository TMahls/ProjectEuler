#include "eulerUtils.h"
#include <iostream>
#include <string>

std::string problem15() {
	// How many paths thru a 20 x 20 grid, when you can only move right or down

	/*
	 With no backtracking (can't move left or up), we will move exactly 20 times down and 20 times right.

	 Imagine our series of moves as a string "RDRRDDDDRRR..." of length 2 * N (grid size)

	 The question is how many different combinations of that are there?

	 nCr = n! / (r! * (n - r)!)

	 We use this since for our series of 40 moves, there are 20 "spots" we're picking for D
	 The remaining spots are filled by R
	 For the 2 x 2, there are (4 * 3) possible ways to place them, but since order
	 does not matter we divide by a further 2! to remove redundant combos.
	*/

	int gridSize = 20;
	BigInt ans;
	ans = nCr(gridSize * 2, gridSize);
	return toString(ans);
}
