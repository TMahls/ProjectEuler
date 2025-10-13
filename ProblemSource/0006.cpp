#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <cmath>

std::string problem6() {
	// Difference between (1+...+100)^2 and 1^2+...+100^2
	long long sumTerm = 0;
	for (char i = 1; i <= 100; i++) {
		sumTerm += std::pow(i,2);
	}
	long long productTerm = std::pow(triangleNum(100), 2);
	return std::to_string(productTerm - sumTerm);
}
