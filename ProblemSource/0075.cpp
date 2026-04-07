#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <cmath>

std::string problem75() {
// Integer right triangles
// For perimeter <= 1.5e6, how many have exactly 1 soln?
// E.g. 120 has 3 solns (30,40,50) (20,48,52) (24,45,51)

/*
Shoutout to the Problem 9 PDF on showing an efficient way
to find pythagorean triplets. All primitive triplets can be
represented as:

a = m^2 + n^2;  b = 2*m*n;   c = m^2 + n^2
m > n > 0

We can generate pythag triples just by
incrementing m and n.

Since P = a + b + c =  2*m*(m+n)
We can calculate that our max m value to search is sqrt(N/2).
For this problem that's 866 which is super do-able!

Now to pick n values -- we know that the pythag triad is primitive
iff exactly one of m,n is even and gcd(m,n) = 1.

For this first rule, an efficient way to do this is set n_0 as 1 if m
is even, 2 if m is odd, and increment n by 2. That is how mEven and XOR
comes into play here instead of using mod2

For the second rule, repeatedly calling gcd will slow us down-- so instead
we get the list of prime factors for m and simply check those against 'n',
quitting out if n divides evenly.
We don't care what the gcd is, we just want to make sure they
don't share any prime factors.

This guarantees we generate m,n pairs that give primitive triads that have
a perim less than or equal to our goal. Next we just multiply those primitive
triads by some natural number 'd' to get all triads!

For this one we keep track of all perimiters we've found in a database array.
I've made other optimizations to use addition in loop conditions, and storing the
perim as a P/2 array-- this halves our memory usage since we know all P is even.

*/

	const int N = 1.5e6;
	int mMax = std::sqrt(N/2);
	int ans = 0;

	// Init perim database
	unsigned char perimDiv2Arr[N/2];
	for (int i = 0; i < (N/2); i++)
		perimDiv2Arr[i] = 0;

	bool mEven = true;
	int n;
	std::vector<long long> mPrimeFactors;
	int perimDiv2;
	bool mnPrimitive;
	unsigned int i;
	int perimDiv2Mult;
	for (int m = 2; m <= mMax; m++) {
		n = 2;
		if (mEven)
			n = 1;

		// Get unique prime factors of 'm'
		mPrimeFactors.clear();
		getPrimeFactorsVec(m, mPrimeFactors);

		perimDiv2 = m*(m+n);
		while ( (n < m) && (perimDiv2 <= (N/2)) ) {
			// Quick check to see if gcd(m,n) = 1
			mnPrimitive = true;
			i = 0;
			while (mnPrimitive && (i < mPrimeFactors.size())) {
				mnPrimitive = ((n % mPrimeFactors[i]) != 0);
				i++;
			}

			if (mnPrimitive) {
				//std::cout << "m: " << m << " n: " << n << std::endl;
				// Multiply and add to perim database until too big
				perimDiv2Mult = perimDiv2;
				while (perimDiv2Mult <= (N/2)) {
					//std::cout << "P/2: " << perimDiv2Mult << std::endl;
					perimDiv2Arr[perimDiv2Mult - 1]++;
					perimDiv2Mult += perimDiv2;
				}
			}

			perimDiv2 += (m + m);
			n += 2;
		}

		mEven ^= true;
	}

	// Tally answer as number of array entries that equal 1
	//std::cout << "Arr: [";
	for (int i = 0; i < (N/2); i++) {
		//std::cout << (int)perimDiv2Arr[i] << ", ";
		if (perimDiv2Arr[i] == 1)
			ans++;
	}
	//std::cout << "]\n";

	return std::to_string(ans);
}
