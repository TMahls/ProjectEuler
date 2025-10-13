#include <iostream>
#include <string>

std::string problem2() {
// Find sum of all even fib numbers below 4 million
	int sum = 2;
	int currNum = 0;
	int prevNums[2] = {1,2};

	while (currNum < 4e6) {
		currNum = prevNums[0] + prevNums[1];

		sum += !(currNum % 2) * currNum;

		prevNums[0] = prevNums[1];
		prevNums[1] = currNum;
	}

	return std::to_string(sum);
}
