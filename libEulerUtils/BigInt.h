#ifndef BIGINT_H
#define BIGINT_H

#include <string>

class BigInt{
	std::string digits;

public:
	// -- Function Declarations --
	// Constructors
	BigInt();
	BigInt(unsigned long long);
	BigInt(std::string &);
	BigInt(const char *);
	BigInt(BigInt &);

	// Helper Functions
	friend int length(const BigInt &);
	friend bool isZero(const BigInt &);
	friend BigInt pow(BigInt, BigInt);
	friend BigInt sqrt(BigInt);
	friend std::string toString(BigInt);

	// Operator Overloads
	// Assignment and logical operators
	BigInt & operator=(const BigInt &);
	friend bool operator==(const BigInt &, const BigInt &);
	friend bool operator!=(const BigInt &, const BigInt &);
	friend bool operator<(const BigInt &, const BigInt &);
	friend bool operator<=(const BigInt &, const BigInt &);
	friend bool operator>(const BigInt &, const BigInt &);
	friend bool operator>=(const BigInt &, const BigInt &);

	// Arithmetic
	BigInt & operator++();
	BigInt operator++(int);
	BigInt & operator--();
	BigInt operator--(int);

	friend BigInt & operator+=(BigInt &, const BigInt &);
	friend BigInt operator+(const BigInt &, const BigInt &);

	friend BigInt & operator-=(BigInt &, const BigInt &);
	friend BigInt operator-(const BigInt &, const BigInt &);

	friend BigInt & operator*=(BigInt &, const BigInt &);
	friend BigInt operator*(const BigInt &, const BigInt &);

	friend BigInt & operator/=(BigInt &, const BigInt &);
	friend BigInt operator/(const BigInt &, const BigInt &);

	friend BigInt & operator%=(BigInt &, const BigInt &);
	friend BigInt operator%(const BigInt &, const BigInt &);

	// Input & Output
	friend std::istream & operator>>(std::istream &, BigInt &);
	friend std::ostream & operator<<(std::ostream &, const BigInt &);
};

#endif
