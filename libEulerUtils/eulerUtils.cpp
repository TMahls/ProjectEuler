 #include "eulerUtils.h"
#include <cstdio>
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm> // For std::sort

/*
--- Euler Utils ---

This file is a collection of useful
utility functions, specifically for
use in Project Euler problems.

See the header for a more convenient list.
-------------------
*/

void giveUp() {
	printf("Fuck this problem! I give up...\n\n\t(Now go grab a beer)\n");
}

std::string file2String(std::string fileName, const char * lineDelim) {
// Return one string of the file, with the lineDelim added between file lines
	std::ifstream inputFile(fileName);

	if (!inputFile.is_open()) {
		std::cerr << "ERROR: Could not open the input file " << fileName << std::endl;
		return "";
	}

	std::string line;
	std::string fileStr;
	while (std::getline(inputFile, line)) {
		fileStr += line;
		fileStr += lineDelim;
	}

	inputFile.close();
	return fileStr;
}

std::vector<std::string> file2StringArray(std::string fileName, const char * delim) {
// Return a vector of strings, where the delim character bounds the elements
	std::ifstream inputFile(fileName);

	std::vector<std::string> fileVector;

	if (!inputFile.is_open()) {
		std::cerr << "ERROR: Could not open the input file " << fileName << std::endl;
		return fileVector;
	}

	std::string line;
	while (std::getline(inputFile, line, *delim)) {
		fileVector.push_back(line);
	}

	inputFile.close();
	return fileVector;
}

void getPrimeFactors(long long N, long long * primeFactorsArr) {
// Return a sorted array of all prime factors of a number
	int NFactors = countFactors(N);
	long long * allFactors = new long long[NFactors];
	getFactors(N, allFactors, NFactors);

	int primeIdx = 0;
	for (int factorIdx = 0; factorIdx < NFactors; factorIdx++){
		if (isPrime(allFactors[factorIdx])) {
			primeFactorsArr[primeIdx] = allFactors[factorIdx];
			primeIdx++;
		}
	}
}

void getFactors(long long N, long long * factorsArr, int NFactors) {
// Return a sorted array of all factors of a number
	int upperBound = std::floor(std::sqrt(N));
	int idx = 0;
	for (int i = 1; i <= upperBound; i++) {
		if ( (N % i) == 0 ) {
			factorsArr[idx] = i;
			factorsArr[NFactors - idx - 1] = N / i;
			idx++;
		}
	}
}

void getFactorsVec(long long N, std::vector<long long> & factorsVec) {
// Same as above, but uses a vector instead of an array
	int upperBound = std::floor(std::sqrt(N));
	for (int i = 1; i <= upperBound; i++) {
		if ( (N % i) == 0 ) {
			factorsVec.push_back(i);
			if ( i != (N / i))
				factorsVec.push_back(N / i);
		}
	}
	std::sort(factorsVec.begin(), factorsVec.end());
}

int getFactorSum(long long N) {
// Return the sum of all factors (including 1 and N)
	if (N == 0) {
		return 0;
	} else if (N == 1) {
		return 1;
	}

	int upperBound = std::floor(std::sqrt(N));
	int factorSum = N + 1;

	for (int i = 2; i <= upperBound; i++) {
		if ( (N % i) == 0 ) {
			factorSum += i;
			if (i != (N / i))
				factorSum += (N / i);
		}
	}
	return factorSum;
}

int countFactors(long long N) {
// Return how many factors a number has
	if (N == 0) {
		return 0;
	} else if (N == 1) {
		return 1;
	}

	int upperBound = std::floor(std::sqrt(N));
	int factorsCount = 2;

	for (int i = 2; i <= upperBound; i++) {
		if ( (N % i) == 0 ) {
			factorsCount++; // One for i
			if (i != (N / i))
				factorsCount++; // One for N/i
		}
	}
	return factorsCount;
}

int countPrimeFactors(long long N) {
// Return how many prime factors a number has
	if (N == 0)
		return 0;
	else if (N == 1)
		return 1;

	long long upperBound = std::floor(std::sqrt(N));
	int primeFactorsCount = 0;

	for (int i = 2; i <= upperBound; i++) {
		if (!(N % i)) {
			primeFactorsCount += isPrime(i);
			if (i != (N / i))
				primeFactorsCount += isPrime(N / i);
		}
	}
	return primeFactorsCount;
}

bool isPrime(long long N) {
// Determine whether a number is prime
	if (N <= 1)
		return false;
	else if (N < 4)
		return true; // 2 and 3 are prime
	else if (!(N % 2))
		return false;
	else if (!(N % 3))
		return false;
	else if (N < 9) // All non-prime under 9 eliminated by above
		return true;
	else {
		// At this point we've eliminated all multiples of 2 and 3
		// Therefore the factors we need to check are: 5, 7, 11, 13, 17, 19, etc...

		long long upperBound = std::floor(std::sqrt(N));
		int testFactor = 5;
		while (testFactor <= upperBound) {
			if ( !(N % testFactor) || !(N % (testFactor + 2)) )
				return false;
			testFactor += 6;
		}
	}
	return true;
}

bool isPandigital(std::string N) {
// Determine whether an input string is 1-9 pandigital
	if ( N.length() == 9 ) {
		bool representedDigits[9] = {};

		for (int idx = 0; idx < 9; idx++)
			representedDigits[char2num(N[idx])-1] = 1;

		for (int idx = 0; idx < 9; idx++)
			if (representedDigits[idx] != 1)
				return false;
		return true;
	} else {
		return false;
	}
}

bool isPalindrome(std::string N) {
// Determine whether an input string is a palindrome
	for (int i = 0; i <= std::floor(N.length() / 2); i++) {
		if (N[i] != N[N.length()-1-i]) {
			return false;
		}
	}
	return true;
}

int numDigits(long long N) {
// Return how many digits are in an integer
	return std::floor(std::log(N) / std::log(10)) + 1;
}

char extractDigit(long long N, short n) {
// Return the nth digit from N.
// 1st digit is the ones place, 2nd is tens, etc.
	long long currNum = N - N%(int)(std::pow(10,n-1));
	for (short i = numDigits(N); i > n; i--) {
		currNum %= (int)(std::pow(10,i-1));
	}
	return currNum / std::pow(10,n-1);
}

std::string convertBase10Int(long long N, int base) {
// A quicker method than 'convertToBase'
// Less general-- this converts base 10 integers to a [2-16] base

	std::string baseChars = "0123456789ABCDEF";
	std::string out;
	int power = 0;
	int powerCalc;
	int nextDigit;
	while (N > 0) {
		powerCalc = std::pow(base, power);
		nextDigit = (N % (base * powerCalc)) / powerCalc;
		out.push_back(baseChars[nextDigit]);
		N -= nextDigit * powerCalc;
		power++;
	}
	return out;
}

std::string convertToBase(std::string in, int inBase, int outBase) {
// Convert a string from one base to another
/*
Supported bases: 2 - 16 and 64
A base of 0 for the in base or the out base is considered text.
Meaning 8-bit characters will be converted to binary, and then those
chunks will be converted to the target base (or vice versa)
Deals with negative signs and decimal places
*/
	std::string out;
	if (isValidBasePair(inBase, outBase)) {
		// Define character sets
		std::string normalBaseChars = "0123456789ABCDEF";
		std::string base64Chars = \
		 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

		if ( inBase > 0 ) {
			// Convert to numeric value first
			BigInt intPart;
			BigInt fracPart;

			bool negSign = (in[0] == '-');

			// Find IDX of decimal if we have one
			int decimalIdx = in.length();

			for (unsigned int i = 0; i < in.length(); i++)
				if (in[i] == '.')
					decimalIdx = i;

			// Get the integer and fractional numeric value
			std::string baseChars = (inBase == 64) ? base64Chars : normalBaseChars;

			int endIdx = negSign ? 1 : 0;
			int power = 0;
			bool found;
			unsigned int digitVal;
			for (int i = (decimalIdx - 1); i >= endIdx; i--) {
				found = 0;
				digitVal = 0;
				while ( (digitVal < normalBaseChars.length()) && !found) {
					found = (baseChars[digitVal] == in[i]);
					digitVal++;
				}
				intPart += --digitVal * std::pow(inBase, power);
				power++;
			}

			power = 0;
			for(int i = (in.length() - 1); i > decimalIdx; i--) {
				found = 0;
				digitVal = 0;
				while ( (digitVal < normalBaseChars.length()) && !found) {
					found = (baseChars[digitVal] == in[i]);
					digitVal++;
				}

				fracPart += --digitVal * std::pow(inBase, power);
				power++;
			}

			if (outBase > 0) { // Numeric value to numeric value
				if (negSign)
					out.push_back('-');


				baseChars = (outBase == 64) ? base64Chars : normalBaseChars;

				out += int2BaseStr(intPart, outBase, baseChars);
				if (fracPart > BigInt("0")) {

					out.push_back('.');

					// Fractions -- tricky because different bases will have different
					// numbers of decimals required-- even infinite-- to express the same value
					// We'll add some hard-coded amount of precision
					std::string fracStr;
					BigInt fractionNum(inBase);
					BigInt lengthNum(16 - length(fracPart)); // How much precision we need
					fracPart *= pow(fractionNum, lengthNum); // Adding trailing 0's
					lengthNum = length(fracPart);
					fractionNum = pow(fractionNum, lengthNum);

					BigInt divideNum;
					divideNum = fractionNum / outBase;
					BigInt i;
					while (divideNum > BigInt("0")) {
						i = fracPart / divideNum;
						if (i >= outBase) // This happens sometimes due to int divide above
							i = outBase - 1;
						fracStr.push_back(baseChars[std::stoi(toString(i))]);
						fracPart -= i * divideNum;
						divideNum /= outBase;
					}

					out += fracStr;
				}
			} else { // Numeric value to text
				// Convert in string to bit string
				std::string bits;
				char currDigitValue;

				// For each digit in input string
				for (unsigned int i = 0; i < in.length(); i++) {
					// Get the numeric value of that digit
					unsigned int j = 0;
					bool found = false;
					while ( (j < baseChars.length()) && !found ) {
						found = (baseChars[j] == in[i]);
						j++;
					}
					if (!found) // Use ASCII value
						currDigitValue = in[i];
					else
						currDigitValue = j - 1;

					// Add value bits to bit string
					unsigned int bitsRequired = std::ceil(std::log(inBase) / std::log(2)); // Number of bits

					char bit;
					for (unsigned int j = 0; j < bitsRequired; j++) {
						bit = (currDigitValue & (1 << (bitsRequired-1))) ? 1 : 0;
						bits.push_back(num2char(bit));
						currDigitValue <<= 1;
					}
				}


				// Bit string -> ASCII text
				unsigned char currChar;
				for (unsigned int i = 0; i < (bits.length() - 7); i += 8) {
					currChar = 0;
					for (int j = 0; j < 8; j++) {
						currChar += std::pow(2, 7 - j) * char2num(bits[i+j]);
					}
					out.push_back(currChar);
				}
			}
		} else { // Get numeric value of each character for text input
		/*
		Some explanation -- see the wikipedia page for Base64. The way text
		is converted is by taking the text, converting to a long vector of
		bits (8 per char, ASCII), and using every 6 bits from that to get a
		Base64 digit (since 6 bits is what you need, 2^6 = 64). In this way
		the first 3 letters of the string (24 bits) gives the first 4 digits
		in base 64. We can do this in other bases, the number that varies is
		how many 'bits' we take from the original stream to make a digit
		*/
			if (outBase != 0) {
				std::string bits;
				char bit;
				char currChar;
				for (unsigned int i = 0; i < in.length(); i++) {
					currChar = in[i];
					for (int j = 0; j < 8; j++) {
						bit = (currChar & (1 << 7)) ? 1 : 0; // 7th  bit
						bits.push_back(num2char(bit));
						currChar <<= 1;
					}
				}

				unsigned int bitsRequired = std::ceil(std::log(outBase) / std::log(2)); // Number of bits

				// Add trailing zeros to strings that don't divide 'bitsRequired' evenly
				for (unsigned int i = 0; i < (bits.length()%bitsRequired); i++)
					bits.push_back('0');

				// Read bitsRequired bits at a time from bit array
				std::string baseChars = (outBase == 64) ? base64Chars : normalBaseChars;
				int power = 0;
				while (bits.length() >= bitsRequired) {
					currChar = 0;
					power = 0;

					// Numeric value from binary string
					for (int i = bitsRequired - 1; i >= 0; i--) {
						currChar += std::pow(2,power) * char2num(bits[i]);
						power++;
					}
					bits = bits.substr(bitsRequired);

					// Add to out string
					out.push_back(baseChars[currChar]);
				}
			} else {
				out = in;
			}
		}
	} else {
		std::cerr << "ERROR: Unsupported base supplied to convertToBase()\n";
	}

	return out;

}

bool isValidBasePair(int inBase, int outBase) {
// Input validation for 'convertToBase'

	bool inBaseValid = (inBase >= 0) && ( (inBase <= 16) || (inBase == 64) );
	bool outBaseValid = (outBase >= 0) && ( (outBase <= 16) || (outBase == 64) );
	return (inBaseValid && outBaseValid);
}

std::string int2BaseStr(BigInt in, int base, std::string baseChars) {
// Construct number string from integer
// Ex: (BigInt("10"),2) returns "1010"
	std::string outStr;
	int power = 0;
	BigInt nextDigit;
	int digitPower;

	while (in > BigInt("0")) {
		digitPower = std::pow(base, power);
		nextDigit = (in % BigInt(base * digitPower)) / digitPower;
		outStr.push_back(baseChars[std::stoi(toString(nextDigit))]);
		in -= nextDigit * digitPower;
		power++;
	}
	std::reverse(outStr.begin(), outStr.end());
	return outStr;
}

long long triangleNum(int N){
// Return the Nth triangle number
	long long ans = (N * (N + 1))/2;
	return ans;
}

int inverseTriangleNum(long long N){
// If input is the nth triangle number, returns n. Else, returns 0
	int term = std::sqrt(8 * N + 1) - 1;
	if (!(term % 2))
		return term / 2;
	return 0;
}

char char2num(char n){
// Return numerical value of ASCII char ('1' = 1)
	return n - 48;
}

char num2char(char n){
// Return the ASCII character for a digit (1 = '1')
	return n + 48;
}

long long sgn(long long val) {
// The sign of a number. Thanks stack overflow!
// https://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c
	return (0 < val) - (val < 0);
}

void simplifyFraction(long long * num, long long * den) {
	long long factor = gcf(*num, *den);
	*num /= factor;
	*den /= factor;
}

long long gcf(long long a, long long b) {

	std::vector<long long> aFactorVec;
	std::vector<long long> bFactorVec;

	getFactorsVec(a, aFactorVec);
	getFactorsVec(b, bFactorVec);

	int commonFactorIdx = 0; // idx in b vector
	unsigned int aIdx = 0;
	unsigned int bIdx = 0;
	while ( (aIdx < aFactorVec.size()) && (aFactorVec[aIdx] <= b) ) {
		bIdx = commonFactorIdx;
		while ( (bIdx < bFactorVec.size()) && (bFactorVec[bIdx] <= a) ) {
			if (aFactorVec[aIdx] == bFactorVec[bIdx])
				commonFactorIdx = bIdx;
			bIdx++;
		}
		aIdx++;
	}

	//std::cout << "GCF of " << a << " and " << b << " is " << bFactorVec[commonFactorIdx] << std::endl;
	return bFactorVec[commonFactorIdx];
}

std::string getNextPerm(std::string in) {
// Return the next lexicographic permutation of an input string
// Works on strings with repeated digits such as "12112"
// Recursively calls itself on the substring [1,end]

	std::string out;
	if (in.length() <= 1) {
		return out;
	}

	bool reverseOrder = true;
	unsigned int i = 0;
	while (i++ < in.length() && reverseOrder)
		reverseOrder = (in[i] <= in[i-1]);

	if (reverseOrder) {
		return out; // Base case - no next perm for reverse
	} else {
		out = getNextPerm(in.substr(1,in.length()));
		if (out.length() == 0) { // Special case -- need to increment first digit
			out = in;
			std::string inSorted = in;
			std::sort(inSorted.begin(), inSorted.end());
			bool found = false;
			unsigned int idx = 0;
			while (idx < inSorted.length() && !found) {
				found = (inSorted[idx] == in[0]);
				idx++;
			}
			idx--;

			// Increment until we have the next number
			while (inSorted[idx] == in[0])
				idx++;

			out[0] = inSorted[idx];

			// Then re-arrange remaining digits
			unsigned int sortedIdx = 0;
			for (unsigned int i = 1; i < out.length(); i++) {
				if (sortedIdx == idx) // Skip the digit we used for the first entry
					sortedIdx++;
				out[i] = inSorted[sortedIdx];
				sortedIdx++;
			}
			return out;
		} else {
			return (in[0] + out); // Normal recursive case
		}
	}
}

std::string getNthPerm(std::string in, long long N) {
/*
This only works on ordered strings with unique digits (no repeats)
But can be faster than 'getNextPerm'. Created for Problem 24

This works by placing digits one at a time, knowing how many
permutations will start with a particular digit.

*/
	// Create vector from input string
	std::vector<short> digits;
	int factorialN[9]; // Factorial data

	for (unsigned int i = 0; i < in.length(); i++) {
		digits.push_back(char2num(in[i]));
		factorialN[i] = factorial(i + 1);
	}

	// Create output string one character at a time
	std::string out = "";
	short digitIdx;
	for (int i = digits.size(); i > 0; i--) {
		digitIdx = N / factorialN[i - 2];
		out += std::to_string(digits.at(digitIdx)); // Concat to our string

		// Erase curr digit
		digits.erase(digits.begin() + digitIdx);

		N %= factorialN[i - 2];
	}

	return out;
}

std::vector<std::vector<short>> getAllPerms(std::vector<short> n) {
// Return a vector of all permutations of n
// Assumes n is sorted
	std::vector<std::vector<short>> ans;
	std::vector<short> nMod;
	short N = n.size();

	// Base case -- for 2 nums, return swapped
	if (N == 2) {
		ans.push_back(n);
		nMod = {n[1], n[0]};
		ans.push_back(nMod);
		return ans;
	}

	std::vector<std::vector<short>> subArr;
	for (unsigned short i = 0; i < N; i++) {
		// Create nMod by erasing 'i'
		// (erase is really slow)
		nMod.clear();
		for (short j : n)
			if (j != n[i])
				nMod.push_back(j);

		subArr = getAllPerms(nMod);

		for (std::vector<short> j : subArr) {
			nMod = {n[i]};
			for (short k : j)
				nMod.push_back(k);
			ans.push_back(nMod);
		}
	}

	return ans;
}

bool isPerm(std::string a, std::string b) {
// Determines if b is a permutation of a
	std::sort(a.begin(), a.end());
	std::sort(b.begin(), b.end());
	return (a == b);
}

bool isReverseSorted(std::string in) {
// Determines if the input string is reverse sorted
	bool reverseOrder = true;
	unsigned int i = 0;
	while (i++ < in.length() && reverseOrder)
		reverseOrder = (in[i] <= in[i-1]);
	return reverseOrder;
}

BigInt bigFactorial(int n) {
	BigInt value(n);
	while (--n > 1) {
		value *= n;
	}
	return value;
}

BigInt nPr(int n, int r) {
	BigInt ans;
	ans = bigFactorial(n) / bigFactorial(n - r);
	return ans;
}

BigInt nCr(int n, int r) {
	BigInt ans;
	ans = nPr(n,r) / bigFactorial(r);
	return ans;
}

long long factorial(int n) {
	if (n <= 1)
		return 1;
	else
		return (n * factorial(n-1));
}

int collatzSequenceLength(long long startingNum){
// Return the length of the collatz sequence starting at startingNum
// We consider 1 to be the last number
	int sequenceLength = 1;
	while (startingNum != 1) {
		if (!(startingNum % 2))
			startingNum /= 2;
		else
			startingNum = 3 * startingNum + 1;
		sequenceLength++;
	}

	return sequenceLength;
}

bool isLeapYear(int year) {
// A leap yer occurs on any year divisible by 4
// But not on a century
// Unless the century is divisible by 400
	bool leap = !(year % 4);
	leap = leap && (year % 100);
	leap = leap || !(year % 400);
	return leap;

}
