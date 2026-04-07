#include "eulerUtils.h"
#include <iostream>
#include <string>

std::string problem78() {
// Let p(n) be the number of ways n coins can be
// separated into piles. p(5) = 7. Find smallest
// n such that p(n) is divisible by 1e6

/*
This seems the same to me as problem 76, but we go in
a loop and find the first example that is a multiple of 1e6
I need to make some improvements to the 76 algorithm.

I could just look up the p(n) sequence on OEIS

A000041 - The partition numbers. Gives the following formula
a(n) = 1/n * Sum{k = 0 .. n-1} sigma(n-k) * a(k)
Where sigma(x) is the sum of divisors of x (incl. 1 and x).
Therefore, a(5) = 1/5 * (sigma(5)*a(0) + sigma(4)*a(1) + sigma(3)*a(2) +
sigma(2)*a(3) + sigma(1)*a(4) ) = (6*1 + 7*1 + 4*2 + 3*3 + 1*5)/5

So we need to calculate sigma(x) quickly.

Well, even brute forcing up to n = 8000 we don't find our answer. Need to be
smarter about this.

This one was tricky for me! But 2 insights allow for it to be solved
quickly.

1 - Euler's Pentagonal Number Theorem
 Euler (of course) figured out something neat about the partition numbers.
p(n) = p(n-1) + p(n-2) - p(n-5) - p(n-7) + p(n-12)

The paremters are pentagonal numbers of the form:
(3k^2+k)/2 and (3k^2-k)/2

And the sign is alternating every 2 terms.

To read more about this see the following paper:
Addition and Counting: The Arithmetic of Partitions - Scott Ahlgren and Ken Ono

This let me brute force up to 50,000 but it was slow and I still didn't find
the answer.

2 - Storing + calculating (pn % N) instead of pn

OK SO-- this is the first one where we make use of mod() to make
calculations easier. We don't calculate these super huge numbers directly.
We just keep track of pn % N since that's what we care about and it won't
change from adding.
This way you can just use int instead of BigInt, tremendously faster.
*/

	int N = 1e6;

	// Generate pentagonal number db
	std::vector<int> pentaDb;
	int pentaNum = 0;
	int idx = 1;
	while (pentaNum <= N){
		pentaNum = (3*idx*idx - idx)/2;
		pentaDb.push_back(pentaNum);
		pentaNum = (3*idx*idx + idx)/2;
		pentaDb.push_back(pentaNum);
		idx++;
	}
	/*
	std::cout << "Penta nums: [";
	for (int i : pentaDb)
		std::cout << i << ",";
	std::cout << "]\n";
	*/

	std::vector<int> ansDb = {1,1};
	int pn;
	int i = 2;
	bool plus;
	bool found = false;
	while (!found) {
		pn = 0;
		idx = 0;
		plus = true;
		while ( (i - pentaDb[idx]) >= 0 ) {
			//std::cout << "p(i - " << pentaDb[idx] << ")\n";
			//std::cout << " = " << ansDb[i-pentaDb[idx]] << std::endl;
			if (plus)
				pn +=  ansDb[i - pentaDb[idx]];
			else
				pn =  N + pn - ansDb[i - pentaDb[idx]];

			pn %= N; // Only keep first couple digits
			idx++;
			if ( (idx % 2) == 0 )
				plus ^= true;
		}

		//std::cout << "i: " << i << " p(i): " << pn << std::endl;
		ansDb.push_back(pn);

		found = ( pn == 0 );

		i++;
	}

	return std::to_string(i - 1);
}
