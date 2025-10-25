#include "eulerUtils.h"
#include <iostream>
#include <string>

std::string problem57() {
// sqrt(2) = 1 + (1 / (2 + 1 / (2 + 1 / (2 + ... ))))
// Each iteration gives you a different fraction. In the first
// 1000 expansions, how many fractions contain a numerator with more
// digits than the denominator?

/*

We're given the first 8 expansions:
3/2, 7/5, 17/12, 41/29, 99/70, 239/169, 577/408, 1393/985
That is the first one which satiesfies our criteria.

Let's come up with a formula for the numerator and denominator.
Then we can just generate the next terms and see.

This is easier shown on pen and paper, but basically the equation is of the form:
1 + 1 / (2 + a/b), where a and b come from our last term.
a/b = 1/2, then 2/5, then 5/12, then 12/29, etc.
So a_n+1 = b_n
   b_n+1 = 2*b_n + a_n

And by some more simple math, our term is:
(3b + a) / (2b + a)
Now, are these always simplified fracs? Idk. Let's say they are lol

In that case we just need to see when (3b + a) has more digits than (2b + a)

Another one where BigInt is necessary -- these fractions get out of hand quick.

*/

	short ans = 0;
	BigInt a(1);
	BigInt b(2);
	BigInt temp;
	BigInt temp2;
	for (int i = 3; i < 1000; i++) {
		temp = b;
		b = 2*b + a;
		a = temp;
		//std::cout << i << "th term: " << (3*b+a) << "/" << (2*b+a) << std::endl;
		temp = 3*b + a;
		temp2 = temp - b;
		if (toString(temp).length() > toString(temp2).length()) {
			//std::cout << "thas more digits\n";
			//std::cout << i << std::endl;
			ans++;
		}
	}

	return std::to_string(ans);
}
