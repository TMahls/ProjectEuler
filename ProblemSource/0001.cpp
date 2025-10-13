#include <iostream>
#include <string>

std::string problem1() {
// Find sum of all multiples of 3 or 5 below 1000
	int sum = 0;
	int N = 1000;

	for(int i = 3; i < N; i++) {
		if( ((i%3) == 0) || ((i%5) == 0))
			sum += i;
	}

	return std::to_string(sum);
}
