#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <cmath>
void recursiveGetSquareProbability(const double[], int, double[], int, \
				int, char, const char);

std::string problem84() {
// In Monopoly, we can label each square 00 (GO) thru
// 39 (Boardwalk). The 3 most popular squares
// are Jail (6.24%) = 10, E3 (3.18%) = 24, and GO (3.09%) = 00
// These concatenate to make 102400 (6 digit modal string)
// Find the modal string if we used 2 D4 instead of 2 D6

/*
This one's got a lengthy setup and naming scheme for
the squares.

Naming convention for squares array:
[0] - GO
[10] - Jail
[20] - Free Parking
[30] - Go to jail (zero probability of finishing here)
[39] - Boardwalk, last one

-- Take 1 --
This isn't about calculating the probability in exact terms,
its just about relative probability.

I think we can, up to a certain recursion depth, do the following:
1. Get dice value probability distribution
2. Have a probability array for all 40 squares that gets updated each
step
3. Calculate probability of ending first roll (starting from GO) on
all other squares
4. For each of the possbible landing squares, repeat starting a new roll
from that square

Oops. Slow and wrong. Let's just start at the even 2.5% distribution,
then make adjustments for GTC, CC, and CH. THEN we make adjustments
for 3 double go to jail rule.

-- Take 2 --
Perhaps we can just calculate every square at once and adjust based on cards
Well that works for everything except the triple doubles rule. How do you know
how often you'll get to a certain square from rolling 3 doubles? And do you account
for that distribution before or after card effects?

-- Take 3 --
Simulate rolls again, but faster. No recursion.
The number of rolls to simulate is a bit of a tuned parameter, but basically
it's the point where with no special rules, the probabilities even out to 2.5%
for each square. You've gone around the board enough times where it all evens out.
Wow, so it turns out you don't even need to account for the triple doubles rule
to get the correct answer. It's all about the relative probabilities!
Even though my exact values are def wrong.
JAIL/10 - 6.24% vs my 5.90%
E3/24 - 3.18% vs my 3.19%
GO/0 - 3.09% vs my 3.11%

Here's the question, do I implement the role just to match the example? Ugh...
Ok I did it but in a sorta hand-wavy way.
*/

	// Assume we use 2 N-sided dice
	const int N = 4;
	int concatNVals = 3; // How many of the most popular values we concat for ans

	// Monopoly params
	const int NSquares = 40;
	int consecutiveDoublesJail = 3;

	// Square indexes
	int go = 0;
	int goToJail = 30;
	int jail = 10;
	int communityChestIdx[] = {2, 17, 33};
	int chanceIdx[] = {7, 22, 36};
	int railroadIdx[] = {5, 15, 25, 35};
	int utilityIdx[] = {12, 28};

	// Init probability array
	double squareProbability[NSquares];
	for (unsigned int i = 0; i < (sizeof(squareProbability)/sizeof(double)); i++)
		squareProbability[i] = 0;
	squareProbability[0] = 1;

	double cumSumChange[NSquares];
	int currSquare;
	double baseP;
	unsigned int i;
	bool onCC, onCH;
	int nextRailroad, nextUtility;
	// Simulate a large number of rolls
	for (int rollN = 0; rollN < 120; rollN++) {
		//std::cout << "Roll # " << rollN << std::endl;

		// Clear probability adjustment array
		for (int i = 0; i < NSquares; i++)
			cumSumChange[i] = 0;

		// For each possible starting square
		for (int startSquare = 0; startSquare < NSquares; startSquare++) {
			if (squareProbability[startSquare] > 0) {
				//std::cout << "Starting square: " << startSquare << std::endl;
				cumSumChange[startSquare] -= squareProbability[startSquare];
				// For each possible dice combo
				for (int die1 = 1; die1 <= N; die1++) {
					for (int die2 = 1; die2 <= N; die2++) {
						int rollVal = die1 + die2;
						//std::cout << "Roll value: " << rollVal << std::endl;
						currSquare = ((startSquare+rollVal) % NSquares);

						// Basic dice odds
						baseP = squareProbability[startSquare]/(N*N);
						cumSumChange[currSquare] += baseP;

						// Check for chance, and chest
						onCC = false;
						i = 0;
						while (!onCC && (i < (sizeof(communityChestIdx)/sizeof(int))))
							onCC = (currSquare == communityChestIdx[i++]);

						onCH = false;
						i = 0;
						while (!onCH && (i < (sizeof(chanceIdx)/sizeof(int))))
							onCH = (currSquare == chanceIdx[i++]);

						if (currSquare == goToJail) {
						// Go to jail square
							cumSumChange[jail] += baseP;
							cumSumChange[currSquare] -= baseP;
						} else if (onCC) {
						// Community chest
							cumSumChange[go] += baseP/16;
							cumSumChange[jail] += baseP/16;
							cumSumChange[currSquare] -= (baseP*2./16);
						} else if (onCH) {
						// Chance
							cumSumChange[go] += baseP/16;
							cumSumChange[jail] += baseP/16;
							cumSumChange[11] += baseP/16;
							cumSumChange[24] += baseP/16;
							cumSumChange[39] += baseP/16;
							cumSumChange[5] += baseP/16;

							// Next railroad
							i = sizeof(railroadIdx)/sizeof(int) - 1;
							if (currSquare > railroadIdx[i]) {
								nextRailroad = railroadIdx[0];
							} else {
								i = 0;
								nextRailroad = 0;
								while (nextRailroad < currSquare)
									nextRailroad = railroadIdx[i++];
							}
							cumSumChange[nextRailroad] += baseP*2./16;

							// Next utility
							i = sizeof(utilityIdx)/sizeof(int) - 1;
							if (currSquare > utilityIdx[i]) {
								nextUtility = utilityIdx[0];
							} else {
								i = 0;
								nextUtility = 0;
								while (nextUtility < currSquare)
									nextUtility = utilityIdx[i++];
							}
							cumSumChange[nextUtility] += baseP/16;

							// Back 3 - can lead to community chest!
							i = 0;
							while (!onCC && (i < (sizeof(communityChestIdx)/sizeof(int))))
								onCC = ((currSquare-3) == communityChestIdx[i++]);
							if (currSquare < 3) {
								cumSumChange[currSquare + NSquares - 3] += baseP/16;
							} else if (onCC) { // CH3 -> CC3
								cumSumChange[go] += (baseP/16)/16;
								cumSumChange[jail] += (baseP/16)/16;
								cumSumChange[currSquare - 3] += (baseP/16)*14./16;
							} else {
								cumSumChange[currSquare - 3] += baseP/16;
							}
							cumSumChange[currSquare] -= (baseP*10./16);
						} else if ( (rollN >= consecutiveDoublesJail) && (die1 == die2)) {
						// Lazy way to account for consec double rule:
						// Assume there's a 1/N^2 chance we got here from consec doubles.
							cumSumChange[jail] += (baseP * \
								1./std::pow(N,consecutiveDoublesJail-1));
							cumSumChange[currSquare] -= (baseP * \
								1./std::pow(N,consecutiveDoublesJail-1));
						}
					}
				}
			}
		}

		// Add probability adjustment array
		//std::cout << "Adding cum sum...\n";
		for (int i = 0; i < NSquares; i++)
			squareProbability[i] += cumSumChange[i];
		/*
		double sum = 0;
		std::cout << "Prob dist: [";
		for (double i : squareProbability) {
			std::cout << i << ", ";
			sum += i;
		}
		std::cout << "]\n";
		std::cout << "Sum of prob dist: " << sum << std::endl;
		*/
	}
	/*
	double sum = 0;
	std::cout << "Prob dist: [";
	for (double i : squareProbability) {
		std::cout << i << ", ";
		sum += i;
	}
	std::cout << "]\n";
	std::cout << "Sum of prob dist: " << sum << std::endl;
	*/
	// Concatenate idx for 3 most popular squares
	std::string ans;
	double highestVal;
	double valLimit = 1;
	int highestValIdx;
	// Just loop thru our array of 40 3 times and find next highest val.
	for (int i = 1; i <= concatNVals; i++) {
		highestVal = 0;
		highestValIdx = 0;
		for (unsigned int j = 0; j < (sizeof(squareProbability)/sizeof(double)); j++) {
			if ((squareProbability[j] > highestVal) && (squareProbability[j] < valLimit)) {
				highestVal = squareProbability[j];
				highestValIdx = j;
			}
		}
		valLimit = highestVal; // Remove that one
		if (highestValIdx < 10)
			ans += ("0" + std::to_string(highestValIdx));
		else
			ans += std::to_string(highestValIdx);
	}

	return ans;
}
