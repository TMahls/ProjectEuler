#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <cmath>
#include <chrono>

#ifdef VERIFY_ANSWER
#include <fstream>
#endif

#ifdef PROBLEM_NUM
/*
What follows is a little convoluted.
See the gcc manual 3.10.6 - Argument Prescan
"Macros that call other macros that stringize or concatenate"

Essentially our goal here is to use our PROBLEM_NUM macro
(supplied as a compiler argument) to make a function problem[1,2,3..]()

If macro expansion was just simple find and replace, we could
have the following line and be done with it:

std::string problemPROBLEM_NUM();

But this does not work, 'PROBLEM_NUM' does not get expanded.

*/
#define PROBLEMX(x) problem ## x
#define PROBLEMXMACRO(x) PROBLEMX(x) // We need this to allow 'x' to be macro-expanded
#define PROBLEM_FCN PROBLEMXMACRO(PROBLEM_NUM)
std::string PROBLEM_FCN();
#endif

// ANSI Color Codes
const std::string brightCyan = "\033[96m";
const std::string brightGreen = "\033[92m";
const std::string brightRed = "\033[91m";
const std::string resetColor = "\033[0m";

int main(){
	// Time the application
	const std::chrono::time_point<std::chrono::high_resolution_clock> startTime = \
		std::chrono::high_resolution_clock::now();

	// Use the problem num macro
	#ifdef PROBLEM_NUM
	std::string answer = PROBLEM_FCN();
	#endif

	const std::chrono::time_point<std::chrono::high_resolution_clock> stopTime = \
		std::chrono::high_resolution_clock::now();

	double duration_ns = std::chrono::nanoseconds(stopTime - startTime).count();

	// How many times we need to divide by 1000 to get in the range of 0-999
	short timeFactor = std::floor(std::log(duration_ns) / (3 * std::log(10)));
	int timerScaled = duration_ns / std::pow(1000, timeFactor);

	std::string timerUnitScaled;
	switch(timeFactor) {
		case 0:
			timerUnitScaled = "nanoseconds";
			break;
		case 1:
			timerUnitScaled = "microseconds";
			break;
		case 2:
			timerUnitScaled = "milliseconds";
			break;
		default:
			// Technically this will break for times over 1000 seconds
			// But we aren't measuring that long of a time scale :)
			timerUnitScaled = "seconds";
			break;
	}

	// Generate coded answer for answer database
	std::string codedAnswer = convertToBase(answer, 0, 64);
	for (unsigned int i = 0; i < codedAnswer.length(); i++)
		codedAnswer[i] -= 5;

	std::cout << "Solution: " <<  brightCyan << answer << resetColor << std::endl;
	if ( ( (timeFactor == 2) && (timerScaled >= 500)) || (timeFactor > 2) )
		// 500 ms or larger runtime gets highlighted red
		std::cout << "Time taken: " << brightRed << timerScaled << " " << \
			timerUnitScaled << resetColor << std::endl;
	else
		std::cout << "Time taken: " << timerScaled << " " << timerUnitScaled << std::endl;

	std::cout <<  "Answer key obfuscation: " << codedAnswer << std::endl;

	#if defined(VERIFY_ANSWER) && defined(PROBLEM_NUM)
	/*
	This is mainly used with 'runAllProblems.sh' to ensure library changes
	aren't starting to give us wrong answers in past problems. The answer
	key in './answerData.txt' is mildly obfuscated, mostly to prevent accidental
	peeking. If you want to view/edit the answer data, you have to be very purposeful.
	*/

	std::cout << "Verifying answer...\n";

	std::string fileName = "./answerData.txt";
	std::ifstream inputFile(fileName);

	if (!inputFile.is_open()) {
		std::cerr << "ERROR: Could not open the input file " << fileName << std::endl;
		return 1;
	}

	std::string line;
	std::string problemSubstr;
	int lineProblemNum;
	bool answerFound = 0;
	std::string answerKeyStr;
	while (std::getline(inputFile, line) && !answerFound) {
		// Look for the line with our problem number
		int commaIdx = 0;
		unsigned int i = 0;
		while (i < line.length() && (commaIdx == 0)) {
			if (line[i] == ',')
				commaIdx = i;
			i++;
		}

		problemSubstr = line.substr(0, commaIdx);
		lineProblemNum = std::stoi(problemSubstr);

		if (lineProblemNum == PROBLEM_NUM) {
			answerFound = 1;
			answerKeyStr = line.substr(commaIdx+2, line.length());

			if (codedAnswer.compare(answerKeyStr) == 0)
				std::cout << brightGreen << "-- CORRECT! :) --\n" << resetColor;
			else
				std::cout << brightRed << "-- INCORRECT! :( --\n" << resetColor;

		}
	}

	if (!answerFound)
		std::cout << brightRed << "-- ANSWER NOT FOUND IN KEY --\n" << resetColor;

	inputFile.close();


	#endif

	return 0;
}
