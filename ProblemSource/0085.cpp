#include "eulerUtils.h"
#include <cmath>
#include <iostream>
#include <string>

std::string problem85() {
// A 3x2 grid contains 18 rectangles.
// What's the area of the grid with the closest to 2 million
// rectangles?

/*
Seems we need to make a recursive 'numRecs(X,Y)' function
and test it with a couple different values.
JK it's not actually recursive, it's very simple.

The example:
C(2,3) = 6 (1,1) + 4 (1,2) + 2 (1,3) + 3 (2,1) + 2 (2,2) + 1(2,3)
	or (3 * 2) + (2 * 2) + (1 * 2) + (3 * 1) + (2 * 1) + (1 * 1)

So C(x,y) = sum i = 1 to x (sum j = 1 to y (i * j) ))

Fastest way to calculate that for a bunch of X/Y combos is build a database.
The grid size is a tuned parameter (bad), initially I tried 1000 x 1000 since
the largest element will be 1e6, close enough to our goal N. But it turns out
you just need 100 since that will get you something only 2 off.

Init grid is just times tables:
[1 2 3 4
[2 4 6 8
[3 6 9 12
[4 8 12 16

Which is a triangle symmetric matrix so we only need fill out:
[1]2 3  4
[2 4]6  8
[3 6 9] 12
[4 8 12 16]

But we can actually sum this grid to get rectangle counts
[1] 3  6   10
[3  9] 18  30
[6  18 36] 60
[10 30 60 100]

If we calculate this before-hand, we just check to see
which element is closest to 2 mill.

Stop searching a row if our delta to goal gets larger than
our smallest delta yet. This saves a ton of time.
*/

	int goalN = 2e6;

	// Build db
	const int arraySize = 1000;

	// Use vector because this is too large for stack
	std::vector<std::vector<int>> ansDb;
	std::vector<int> testRow;
	for (int i = 0; i < arraySize; i++)
		testRow.push_back(0);
	for (int i = 0; i < arraySize; i++)
		ansDb.push_back(testRow);
	//int ansDb[arraySize][arraySize];

	int first, inc;
	ansDb[0][0] = 1;
	for (int i = 2; i <= arraySize; i++) {
		first = ansDb[i-2][0] + i;
		ansDb[i-1][0] = first;
		inc = 3*first;
		for (int j = 2; j <= i; j++) {
			ansDb[i-1][j-1] = inc;
			if (inc < (2*goalN)) // Only fill out values less than our goal
			// Otherwise you quickly get int overflow with this
				inc += ((j+1) * first);
		}
	}

	/*
	for (int i = 0; i < arraySize; i++) {
		std::cout << "[";
		for (int j = 0; j <= i; j++) {
			std::cout << ansDb[i][j] << ", ";
		}
		std::cout << "]\n";
	}
	*/

	int x = 1;
	int y,n;
	int closestN = 0;
	int closestArea;
	// Keep incrementing X until no X by Y have less than
	// our goal number.
	while (x < arraySize) {
		y = 1;
		n = 1;
		while ( ((n - goalN) < std::abs(goalN - closestN)) && (y <= x) ) {
			// Calculate recs for that X and Y
			n = ansDb[x-1][y-1];
			//std::cout << "[x, y] = [" << x << ", " << y << "] N = " << n << std::endl;
			if (std::abs(goalN - n) < std::abs(goalN - closestN)) {
				/*
				std::cout << "New closest! x: " << x << " y: " << \
					y << " recs: " << n << " area: " << x*y << std::endl;
				*/
				closestN = n;
				closestArea = x * y;
			}
			y++;
		}
		x++;
	}

	return std::to_string(closestArea);
}
