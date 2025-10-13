#include "eulerUtils.h"
#include <iostream>
#include <string>

std::string problem37() {
// Sum of all 11 truncatable (left and right) primes

/*
As an initial thought, these can only end in 3 or 7.
2 or 5 won't be prime as 2 or 3 digit numbers. 1 isn't prime 

Turns out a brute force search finds all 11 fast enough.
I wonder how they know there's no larger ones? :)

*/

	int primeCount = 0;
	int searchNum = 23;
	unsigned int i;
	bool works;
	int ans = 0;
	std::string searchNumStr;
	std::string substr1; // left truncate
	std::string substr2; // right truncate
	while (primeCount < 11) {
		if (isPrime(searchNum)) {
			searchNumStr = std::to_string(searchNum);

			i = 0;
			works = true;
			while (works && (i < searchNumStr.length())) {
				substr1 = searchNumStr.substr(i, searchNumStr.length());
				substr2 = searchNumStr.substr(0, searchNumStr.length() - i);

				works = isPrime(std::stoi(substr1)) && isPrime(std::stoi(substr2));
				i++;
			}

			if (works) {
				//std::cout << searchNum << " is truncatable!\n";
				primeCount++;
				ans += searchNum;
			}

		}

		if ( (searchNum % 10) == 3 )
			searchNum += 4;
		else
			searchNum += 6;

	}

	return std::to_string(ans);
}
