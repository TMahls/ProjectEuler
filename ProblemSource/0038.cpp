#include "eulerUtils.h"
#include <iostream>
#include <string>

std::string problem38() {
// Largest 9-digit 1-9 pandigital number made from special multiplication
// X (1 thru n) where we concat X, 2X, 3X, ... nX.

/*
Our answer must be 9 digits (no more no less) and pandigital - no repeats.

Since we can't go over 9 digits, this gives us an upper bound for search
nums. The given example of 9 is also important -- 918,273,645 is pretty
close to the max (987,654,321), so we need to come up with something better
than that. That is our lower bound.

Since the number starts with 1*X, our search num must start with 9. Initially
you can search:
90 - 99
900 - 999
etc.

But the lower bound can be refined using our 9 example, and the upper bound by
not allowing repeats:
91 - 98
918 - 987
9182 - 9876
etc.

Now thinking about 'n', multiplying 91-98 will give us the following pattern:
1X = ab
2X = cde
3X = fgh
4X = ijk
etc.

You can't get 9 digits cleanly from that, so we don't need to search 2 digit nums.
How about 3?
1X = abc
2X = defg
3X = hijk

Can't get 9 from that either - so 918 - 987 is out. What about 4?
1X = abcd
2X = defgh

Perfect. Since n must be greater than one, any starting num over 5 digits will
give us too many digits when we multiply by 2. So now we only need to search:
9182 - 9876
n = 2

Furthermore, since our number starts with 9, 2X cannot have 9 in it. Therefore
anything over 19000 / 2 = 9500 is out. The largest number below 9500 with no 9's
or repeating digits is 9487.

With only 305 numbers to search, this is now quickly done.

*/
	std::string largestFound;
	std::string testStr;
	for (int i = 9182; i <= 9487; i++) {
		testStr = std::to_string(i) + std::to_string(2*i);
		// Since we are only testing one order of magnitude, we know
		// the largest i will give the largest value
		if (isPandigital(testStr)) {
			//std::cout << "New largest: " << i << std::endl;
			largestFound = testStr;
		}
	}

	return largestFound;
}
