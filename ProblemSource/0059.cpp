#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

std::string problem59() {
/*
The file '0059_cipher.txt' has XOR encryption on the byte values listed, with
the passkey being 3 lower case letters. This means if they key is 'abc':
abc = 97 98 99, you XOR (^) the first byte by 97, next by 98, next by 99,
next by 97, etc.
The text is common english, find the password!
*/

/*
Fun one!
Well, there are 26^3 17,576 possible decryptions, so we'll
need some way to programatically check when one has English.
I'm sure there's very sophisticated ways to do this... but we won't
do those lol. I'm just gonna check for 'the' and spaces, and e being common.
Turns out that combined with making sure there are no control characters works.
*/

	// Get string from file
	std::string fileName = "./ProblemSource/0059_cipher.txt";
	std::string fileStr = file2String(fileName,"");

	// Extract message ascii values from file string
	std::string message;
	for (unsigned int i = 0; i < (fileStr.length() - 1); i++) {
		if (fileStr[i] != ',') {
			if (fileStr[i+1] != ',') {
				message.push_back( 10*char2num(fileStr[i]) + char2num(fileStr[i+1]) );
				i++;
			} else {
				message.push_back( char2num(fileStr[i]) );
			}
		}
	}

	const char passLength = 3; // The length of our password

	// Variable initialization
	int temp;
	std::string passStr;
	std::string decodedMessage;
	int sum;
	int pass = 0;
	bool cracked = false;
	unsigned short charCount[128] = {};

	// For each possible password
	while (pass < std::pow(26,passLength) && !cracked) {
		// Create password string
		passStr = "";
		temp = pass;
		for (int i = 0; i < passLength; i++) {
			passStr.push_back(97 + temp/std::pow(26, passLength - 1 - i));
			temp %= (int)std::pow(26, passLength - 1 - i);
		}

		//std::cout << "Pass string: " << passStr << std::endl;

		// Clear charCount array
		for (short i = 0; i < 128; i++)
			charCount[i] = 0;

		decodedMessage = message;
		sum = 0;
		unsigned int i = 0;
		char theCount = 0;
		bool couldWork = true;
		// Decode message and keep track of character stats.
		// If we find an invalid character, stop decoding the message.
		while ((i < message.length()) && couldWork) {
		//	std::cout << "i: " << i << " pass idx: " << i % passLength << std::endl;
			decodedMessage[i] ^= passStr[i % passLength];
		//	std::cout << (int)decodedMessage[i] << std::endl;
			sum += decodedMessage[i];

			// If we see {|}~DEL, or larger, hosed.
			if (decodedMessage[i] < 124) {
				charCount[(short)decodedMessage[i]]++;
			} else {
				couldWork = false;
			}

			// If we see a control character other than CR LF, hosed
			if ( (decodedMessage[i] < 32) && (decodedMessage[i] != 10) && \
				(decodedMessage[i] != 13) )
				couldWork = false;

			// Count 'the'
			if ( (i >= 2) && (decodedMessage[i-2] == 't') && \
				(decodedMessage[i-1] == 'h') && (decodedMessage[i] == 'e') )
				theCount++;

			i++;
		}

		if (couldWork && (charCount[32] > (message.length() / 10) ) && \
			(charCount[101] > (message.length() / 10)) && (theCount > 1) ) {
			cracked = true;
			std::cout << "Pass string: " << passStr << std::endl;
			std::cout << "Decoded: " << decodedMessage << std::endl;
		}

		pass++;
	}

	return std::to_string(sum);
}
