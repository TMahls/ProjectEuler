#include "eulerUtils.h"
#include <iostream>
#include <string>

int lettersCount(int n);

std::string problem17() {
	// If you write out 1 thru 1000, how many letters?

	int N = 1000;

	int ans = 0;
	for (int i = 1; i <= N; i++)
		//std::cout << i << " has " << lettersCount(i) << " letters.\n";
		ans += lettersCount(i);

	return std::to_string(ans);
}

int lettersCount(int n) {
	// Recursion is useful here. This is quite expandable too!
	// Currently works up to one million.
	int count = 0;

	if (n < 20) {
		// Explicitly write number of letters in one thru nineteen (0 for zero)
		short digitLetters[] = {0,3,3,5,4,4,3,5,5,4,3,6,6,8,8,7,7,9,8,8};
		count = digitLetters[n];
	} else if (n < 100) {
		short tensPlace = n / 10;
		// Explcitly write number of letters in twenty thru ninety
		short digitLetters[] = {6,6,5,5,5,7,6,6};
		short tensLetters = digitLetters[tensPlace - 2];
		count = tensLetters + lettersCount(n % 10);
	} else if (n < 1000) {
		short hundredsPlace = n / 100;
		short hundredsLetters = lettersCount(hundredsPlace);

		if (n % 100) // 'Hundred and' has 10 letters
			count = hundredsLetters + 10 + lettersCount(n % 100);
		else // 'hundred' has 7
			count = hundredsLetters + 7;
	} else {
		short thousandsPlace = n / 1000;
		short thousandsLetters = lettersCount(thousandsPlace);

		// Thousand is 8 letters
		count = thousandsLetters + 8 + lettersCount(n % 1000);
	}

	return count;
}
