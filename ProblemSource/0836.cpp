#include "eulerUtils.h"
#include <iostream>
#include <string>

std::string problem836() {
// Find f(20230401,57)

/*
A silly problem - with lots of terrifying-sounding
nonsense terms it eventually tells us to give our answer
as the concatenation of the first letters of each bolded word.
*/

	std::vector<std::string> boldedWords = {"affine","plane","radically",\
		"integral","local","field","open","oriented","line","section",\
		"jacobian","orthogonal","kernel","embedding"};
	std::string ans;
	for (std::string word : boldedWords)
		ans += word[0];

	return ans;
}
