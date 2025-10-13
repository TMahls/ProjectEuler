#ifndef EULERUTILS_H
#define EULERUTILS_H

#include "BigInt.h" // Big int class included in the utils library
#include <vector>

void giveUp(); // The most important one! ;)

// Basic utils
std::string file2String(std::string fileName, const char * lineDelim);
std::vector<std::string> file2StringArray(std::string fileName, const char * delim);
void printArray(); //TODO
void printVec(); //TODO

// Primes + Factors
void getPrimeFactors(long long N, long long * primeFactorsArr);
void getFactors(long long N, long long * factorsArr, int NFactors);
void getFactorsVec(long long N, std::vector<long long> & factorsVec);
int getFactorSum(long long N);
int countFactors(long long N);
int countPrimeFactors(long long N);
bool isPrime(long long N);

// Digit manipulation
bool isPandigital(std::string N);
bool isPalindrome(std::string N);
int numDigits(long long N);
char extractDigit(long long N, short n);
std::string convertBase10Int(long long N, int base);
std::string convertToBase(std::string in, int inBase, int outBase);
bool isValidBasePair(int inBase, int outBase);
std::string int2BaseStr(BigInt in, int base, std::string baseChars);

long long triangleNum(int N);
int inverseTriangleNum(long long N);

char char2num(char n);
char num2char(char n);

long long sgn(long long val);

// Fractions
void simplifyFraction(long long * num, long long * den);
long long gcf(long long a, long long b);

// String tools
std::string getNextPerm(std::string in);
std::string getNthPerm(std::string in, long long N);
std::vector<std::vector<short>> getAllPerms(std::vector<short>);
bool isPerm(std::string a, std::string b);
bool isReverseSorted(std::string in);

// Probability
BigInt bigFactorial(int n);
BigInt nPr(int n, int r);
BigInt nCr(int n, int r);
long long factorial(int n);

// Specialty
int collatzSequenceLength(long long startingNum);
bool isLeapYear(int year);

#endif
