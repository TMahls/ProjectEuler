#include "BigInt.h"
#include <string>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <vector>

// -- Constructors --
BigInt::BigInt() {
	digits = "";
}

BigInt::BigInt(unsigned long long nr) {
	do {
		digits.push_back(nr % 10);
		nr /= 10;
	} while (nr);
}

BigInt::BigInt(std::string & s) {
	digits = "";
	for (int i = s.size() - 1; i >= 0; i--) { // Input validation
		if (!std::isdigit(s[i]))
			throw std::invalid_argument("Input string contains non-digits");
		digits.push_back(s[i] - '0');
	}
}

BigInt::BigInt(const char * s) {
	digits = "";
	for (int i = strlen(s) - 1; i >= 0; i--) { // Input validation
		if (!std::isdigit(s[i]))
			throw std::invalid_argument("Input string contains non-digits");
		digits.push_back(s[i] - '0');
	}
}

BigInt::BigInt(BigInt & a) {
	digits = a.digits;
}

// -- Helper Functions --
int length(const BigInt & a) {
	return a.digits.size();
}

bool isZero(const BigInt & a) {
	return ((length(a) == 1) && (a.digits[0] == 0));
}

BigInt pow(BigInt a, BigInt b) {
// Return a to the bth power (a ^ b)
// More efficient than just mutliplying b times.
	BigInt total(a);
	BigInt currExp(1);
	while (currExp <= (b / 2)) {
		total *= total;
		currExp *= 2;
	}
	BigInt remainingMultiplies;
	remainingMultiplies = b - currExp;
	while (!isZero(remainingMultiplies)) {
		total *= a;
		remainingMultiplies--;
	}

	return total;
}

BigInt sqrt(BigInt a) {
// Binary search
// I tried babylonian/heron's method below, surprisingly it is
// less performant.
	BigInt lowerBound(1);
	BigInt upperBound(a);
	BigInt middle;
	BigInt result;
	while ((upperBound - lowerBound) > 1) {
		middle = (lowerBound + upperBound) / 2;
		result = middle * middle;

		if (result > a) {
			upperBound = middle;
		} else if (result < a) {
			lowerBound = middle;
		} else {
			return middle;
		}
	}
	middle = (lowerBound + upperBound) / 2;
	return middle;

	/*
	BigInt lastAns;
	BigInt ans(1);
	bool condition;
	do {
		lastAns = ans;
		ans = (lastAns + a/lastAns)/2;
		//std::cout << "Ans: " << ans << std::endl;
		//std::cout << "Last ans: " << lastAns << std::endl;
		if (lastAns > ans)
			condition = (lastAns - ans) > 1;
		else
			condition = (ans - lastAns) > 1;
	} while ( condition );
	return ans;
	*/
}

std::string toString(BigInt a) {
	std::string aDigitsReversed = "";

	for (int i = length(a) - 1; i >= 0; i--)
		aDigitsReversed.push_back(a.digits[i] + 48);

	return aDigitsReversed;
}

// -- Operator Overloads --
// Assignment and logical operators
BigInt & BigInt::operator=(const BigInt & a) {
	// Guard self assignment
	if (this == & a)
		return * this;

	digits = a.digits;
	return * this;
}

bool operator==(const BigInt & a, const BigInt & b) {
	return (a.digits == b.digits);
}

bool operator!=(const BigInt & a, const BigInt & b) {
	return !(a == b);
}

bool operator<(const BigInt & a, const BigInt & b) {
	int n = length(a);
	int m = length(b);
	if (n != m) // Return longer string
		return n < m;
	while (n--) // Start from largest digit place, compare
		if (a.digits[n] != b.digits[n])
			return a.digits[n] < b.digits[n];
	return false; // Default
}

bool operator<=(const BigInt & a, const BigInt & b) {
	return !(a > b);
}

bool operator>(const BigInt & a, const BigInt & b) {
	return (b < a);
}

bool operator>=(const BigInt & a, const BigInt & b) {
	return !(a < b);
}

// Arithmetic
// Prefix increment
BigInt & BigInt::operator++() {
	int n = digits.size(); // Overflow all 9's digits
	int i;
	for (i = 0; (i < n) && (digits[i] == 9); i++)
		digits[i] = 0;

	if (i == n) // 99 to 100 -> String length increase
		digits.push_back(1);
	else // Increment first non-9 digit
		digits[i]++;

	return * this;
}

// Postfix increment
BigInt BigInt::operator++(int) {
	BigInt old = * this; // Copy old value
	operator++(); // Prefix increment
	return old; // Return old value
}

// Prefix decrement
BigInt & BigInt::operator--() {
	if ((digits[0] == 0) && (digits.size() == 1))
		throw std::invalid_argument("Underflow -- cannot decrement BigInt below 0");

	int n = digits.size();
	int i;
	for (i = 0; (i < n) && (digits[i] == 0); i++)
		digits[i] = 9;

	digits[i]--;
	if ((n > 1) && (digits[n - 1] == 0)) // 199 to 99 -> String length decrease
		digits.pop_back();

	return * this;
}

// Postfix decrement
BigInt BigInt::operator--(int) {
	BigInt old = * this; // Copy old value
	operator--(); // Prefix decrement
	return old; // Return old value
}

BigInt & operator+=(BigInt & a, const BigInt & b) {
	int n = length(a);
	int m = length(b);
	if (m > n) { // Append leading 0's if a is shorter
		a.digits.append(m - n, 0);
		n = length(a);
	}

	int carry = 0;
	int sum;
	for (int i = 0; i < n; i++) {
		if (i < m)
			sum = a.digits[i] + b.digits[i] + carry;
		else
			sum = a.digits[i] + carry;
		carry = sum / 10; // Carry
		a.digits[i] = sum % 10;
	}

	if (carry) // One final carry increases length of a
		a.digits.push_back(carry);

	return a;
}

BigInt operator+(const BigInt & a, const BigInt & b) {
	// Need temp variable since these are both constants
	BigInt temp;
	temp = a;
	temp += b;
	return temp;
}

BigInt & operator-=(BigInt & a, const BigInt & b) {
	if (a < b)
		throw std::invalid_argument("Underflow -- cannot decrement BigInt below 0");
	int n = length(a);
	int m = length(b);

	int carry = 0;
	int sum;
	for (int i = 0; i < n; i++) {
		if (i < m)
			sum = a.digits[i] - b.digits[i] + carry;
		else
			sum = a.digits[i] + carry;

		if (sum < 0) {
			sum += 10;
			carry = -1;
		} else {
			carry = 0;
		}

		a.digits[i] = sum;
	}

	while ((n > 1) && (a.digits[n - 1] == 0)) {
		a.digits.pop_back();
		n--;
	}

	return a;
}

BigInt operator-(const BigInt & a, const BigInt & b) {
	// Need temp variable since these are both constants
	BigInt temp;
	temp = a;
	temp -= b;
	return temp;
}

BigInt & operator*=(BigInt & a, const BigInt & b) {
	if (isZero(a) || isZero(b)) {
		a = BigInt("0");
		return a;
	}

	int n = length(a);
	int m = length(b);

	std::vector<int> v(n + m, 0);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			v[i + j] += a.digits[i] * b.digits[j];

	a.digits.resize(n + m);

	int carry = 0;
	int sum;
	for (int i = 0; i < (n + m); i++) {
		sum = v[i] + carry;
		v[i] = sum % 10;
		carry = sum / 10;
		a.digits[i] = v[i];
	}

	// Remove leading 0's
	n = length(a);
	while ((n > 1) && (a.digits[n - 1] == 0)) {
		a.digits.pop_back();
		n--; // Because we lose length of 1
	}

	return a;
}

BigInt operator*(const BigInt & a, const BigInt & b) {
	// Need temp variable since these are both constants
	BigInt temp;
	temp = a;
	temp *= b;
	return temp;
}

BigInt & operator/=(BigInt & a, const BigInt & b) {
	if (isZero(b))
		throw std::invalid_argument("Cannot divide BigInt by 0.");

	if (a < b) {
		a = BigInt("0");
		return a;
	}

	if (a == b) {
		a = BigInt("1");
		return a;
	}

	int n = length(a);
	int catIdx = 0;
	std::vector<int> cat(n, 0);
	BigInt carry;

	int i;
	for (i = n - 1; (carry * 10 + a.digits[i]) < b; i--)
		carry = carry * 10 + a.digits[i];

	int cc;
	while (i >= 0) {
		carry = carry * 10 + a.digits[i];

		for (cc = 9; cc * b > carry; cc--);

		carry -= cc * b;

		cat[catIdx++] = cc;

		i--;
	}

	a.digits.resize(cat.size());
	for (i = 0; i < catIdx; i++)
		a.digits[i] = cat[catIdx - i - 1];
	a.digits.resize(catIdx);

	return a;
}

BigInt operator/(const BigInt & a, const BigInt & b) {
	// Need temp variable since these are both constants
	BigInt temp;
	temp = a;
	temp /= b;
	return temp;
}

BigInt & operator%=(BigInt & a, const BigInt & b) {
	if (isZero(b))
		throw std::invalid_argument("Cannot mod BigInt by 0.");

	if (a < b)
		return a;

	if (a == b) { // Return 0
		a = BigInt("0");
		return a;
	}

	int n = length(a);
	int catIdx = 0;
	std::vector<int> cat(n, 0);
	BigInt carry;

	int i;
	for (i = (n - 1); (carry * 10 + a.digits[i]) < b; i--)
		carry = carry * 10 + a.digits[i];

	int cc;
	while (i >= 0) {
		carry = carry * 10 + a.digits[i];

		for (cc = 9; cc * b > carry; cc--);

		carry -= cc * b;

		cat[catIdx++] = cc;

		i--;
	}

	a = carry;
	return a;
}

BigInt operator%(const BigInt & a, const BigInt & b) {
	// Need temp variable since these are both constants
	BigInt temp;
	temp = a;
	temp %= b;
	return temp;
}

// Input & Output
std::istream & operator>>(std::istream & is, BigInt & a) {
	std::string s;
	is >> s;
	int n = s.size();
	for (int i = n - 1; i >= 0; i--) {
		if (!std::isdigit(s[i])) {
			throw std::invalid_argument("Input string contains non-digits");
			is.setstate(std::ios::failbit);
		}
		a.digits[n - i - 1] = s[i];
	}
	return is;
}

std::ostream & operator<<(std::ostream & os, const BigInt & a) {
	for (int i = length(a) - 1; i >= 0; i--)
		os << (short)(a.digits[i]);
	return os;

}
