#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <climits>

#define CARDS_PER_HAND 5
#define N_CARD_RANKS 13 // 2 to Ace

char rankCheck(char[], char[]);
unsigned char rankSubCheck(char[], char);
void selectionSort(char[]);
char char2CardRank(char);

std::string problem54() {
// 'poker.txt' has 1000 poker hands.
// How many does player 1 win?

/*
Oh boy this one! It takes a lot of code, there
are a lot of rules to program in. This is more lines
than my high school self did, but it's more readable,
flexible, and fast. You could have 97 players playing a 7
card hand and it should still handle it! The scoring would
be wonky though ;)

I'd like to distill each hand to having a numerical
score, that way I can just compare. We can use base 13
for this, where each digit represents something.

We could have one binary number with all the ranks:
RF _ SF _ 4K _ FH _ F _ S _ 3K _ 2P _ P _ H
Actually jk, we don't even need that. Just a 1-10 of the
highest rank in the hand.

If both players have the same rank score, rank subscore-
Such as a pair of 8's beating a pair of 2's, even if the
2's have an ace high.

If they have the same subscore, we go to the high card score:
Highest_2_3_4_Lowest

This is a 5-digit base 13 number.

For fun (I like making programs flexible), we'll make the
number of players, number of different card ranks, and cards
per hand a parameter.

*/

	// Read file
	std::string fileName = "./ProblemSource/0054_poker.txt";
	std::string pokerStr = file2String(fileName," ");

	// Initialize vars
	short ans = 0;
	const char nPlayers = 2;
	char playerNums[nPlayers][CARDS_PER_HAND];
	char playerSuits[nPlayers][CARDS_PER_HAND];
	char idxPerCard = 3; // Num-Suit-Space
	char idxPerPlayer = CARDS_PER_HAND * idxPerCard;

	char rankScore[nPlayers];
	unsigned char rankSubscore[nPlayers];
	int highCardScore[nPlayers];
	char highestRank;
	unsigned char highestSubscore;
	int highestCardScore;

	// Read one hand at a time
	for (unsigned short i = 0; i < pokerStr.length(); i += (idxPerCard * nPlayers * CARDS_PER_HAND)) {
		highestRank = 0;
		for (short playerIdx = 0; playerIdx < nPlayers; playerIdx++) {
			// Populate num and suit arrays
			for (short cardIdx = 0; cardIdx < CARDS_PER_HAND; cardIdx++) {
				playerNums[playerIdx][cardIdx] = \
				char2CardRank(pokerStr[i + playerIdx*idxPerPlayer + cardIdx*idxPerCard]);
				playerSuits[playerIdx][cardIdx] = \
				pokerStr[i + playerIdx*idxPerPlayer + cardIdx*idxPerCard + 1];
			}

			// Sort by card rank to make scoring easier
			selectionSort(playerNums[playerIdx]);

			// Determine ranks
			rankScore[playerIdx] = \
				rankCheck(playerNums[playerIdx], playerSuits[playerIdx]);

			rankSubscore[playerIdx] = rankSubCheck(playerNums[playerIdx], rankScore[playerIdx]);

			// Determine high card score
			// For this we take sorted version of playerNums
			// We're making a 'CARDS_PER_HAND' digit number in base
			// 'N_CARD_RANKS'.
			int cardPow = 1;
			highCardScore[playerIdx] = 0;
			for (short cardIdx = 0; cardIdx < CARDS_PER_HAND; cardIdx++) {
				highCardScore[playerIdx] += cardPow * playerNums[playerIdx][cardIdx];
				cardPow *= N_CARD_RANKS;
			}

			// Keep track of highest rank score
			if (rankScore[playerIdx] > highestRank)
				highestRank = rankScore[playerIdx];

		}

		// Determine which player wins
		// Find highest subscore within the winning rank
		highestSubscore = 0;
		highestCardScore = 0;
		for (short playerIdx = 0; playerIdx < nPlayers; playerIdx++)
			if ( (rankScore[playerIdx] == highestRank) )
				if (rankSubscore[playerIdx] > highestSubscore)
					highestSubscore = rankSubscore[playerIdx];
		// Find highest card score within winning subscore
		for (short playerIdx = 0; playerIdx < nPlayers; playerIdx++)
			if ( (rankScore[playerIdx] == highestRank) && \
				(rankSubscore[playerIdx] == highestSubscore) )
				if (highCardScore[playerIdx] > highestCardScore)
					highestCardScore = highCardScore[playerIdx];

		char winningPlayer = 0;
		short playerIdx = 0;
		bool winnerFound = false;
		while ( (playerIdx < nPlayers) && !winnerFound) {
			/*
			if (rankScore[playerIdx] == highestRank) {
				std::cout << "TIE ";
				std::cout << "Player 1 nums: ";
				for (int i = 0; i < CARDS_PER_HAND; i++)
					std::cout << (short)playerNums[0][i] << " , ";
				std::cout << "   Player 1 Suits: ";
				for (int i = 0; i < CARDS_PER_HAND; i++)
					std::cout << (short)playerSuits[0][i] << " , ";
				std::cout << "\nPlayer 2 nums: ";
				for (int i = 0; i < CARDS_PER_HAND; i++)
					std::cout << (short)playerNums[1][i] << " , ";
				std::cout << "   Player 2 Suits: ";
				for (int i = 0; i < CARDS_PER_HAND; i++)
					std::cout << (short)playerSuits[1][i] << " , ";
				std::cout  << std::endl;
			}
			*/

			if ( (rankScore[playerIdx] == highestRank) && \
				(rankSubscore[playerIdx] == highestSubscore) && \
				(highCardScore[playerIdx] == highestCardScore)) {
				winningPlayer = playerIdx;
				winnerFound = true;
				//std::cout << "Player " << winningPlayer+1 << " wins!\n";
			}
			playerIdx++;
		}

		// Increment answer if player 1 wins
		if (winningPlayer == 0)
			ans++;
	}

	return std::to_string(ans);
}

char rankCheck(char playerNums[], char playerSuits[]) {
// Evaluate rank of poker hand
// 9 = royal flush, 8 = straight flush, ... 1 = Pair, 0 = High card
	bool flush = true;
	bool straight = true;
	char largestConsecCount;
	char currConsecCount;
	char pairCount = 0;
	// pairCount 3 -> 4k or FH. 2 -> 3k or 2p. 1 -> 1p
	for (short i = 0; i < CARDS_PER_HAND; i++) {
		if (playerSuits[i] != playerSuits[0])
			flush = false;
		if (playerNums[i] != playerNums[0] + i)
			straight = false;

		if ( (i > 0) && (playerNums[i] == playerNums[i - 1]) ) {
			pairCount++;
			currConsecCount++;
		} else {
			currConsecCount = 1;
		}

		if (currConsecCount > largestConsecCount)
			largestConsecCount = currConsecCount;
	}

	if (flush && straight) { // Royal Flush or Straight Flush
		if (playerSuits[0] == 8) // Ten is lowest card
			return 9;
		return 8;
	}
	if (pairCount == 3) { // Four of a kind or full house
		if (largestConsecCount == 4)
			return 7;
		return 6;
	}
	if (flush)
		return 5;
	if (straight)
		return 4;
	if (pairCount == 2) { // 3 of a kind7 or two pair
		if (largestConsecCount == 3)
			return 3;
		return 2;
	}
	if (pairCount == 1) // One pair
		return 1;
	return 0; // High card
}

unsigned char rankSubCheck(char cardNums[], char rankScore) {
// Evaluate the sub-rank of a poker hand. The sub-rank is what
// you evaluate between rank and high card. For instance, pair
// of 3's beats a pair of 2's, even if the pair of 2's has an Ace.
// Only needed for: 4k, fh, 3k, 2p, p.

	short idx = 0;
	short idx2 = 0;
	switch (rankScore) {
		case 7: // 4 of a kind
			// Return card rank of 4k
			if (cardNums[0] == cardNums[1])
				return cardNums[0];
			return cardNums[1];
		case 6:
		case 3: // Full house and 3 of a kind
			// Rerturn card rank of 3k
			//short idx = 0;
			for (short i = 0; i < (CARDS_PER_HAND - 2); i++) {
				if ( (cardNums[i] == cardNums[i+1]) && \
					(cardNums[i+1] == cardNums[i+2]) )
					idx = i;
			}
			return cardNums[idx];
		case 2: // 2 pair
		{
			short i = 0;
			bool firstPairFound = false;
			while ( (i < (CARDS_PER_HAND - 1)) && !firstPairFound ) {
				if (cardNums[i] == cardNums[i+1]) {
					idx = i;
					firstPairFound = true;
				}
				i++;
			}

			for (short i = idx; i < (CARDS_PER_HAND - 1); i++)
				if (cardNums[i] == cardNums[i+1])
					idx2 = i;

			if (cardNums[idx2] > cardNums[idx])
				return ( N_CARD_RANKS*cardNums[idx2] + cardNums[idx]);
			return ( N_CARD_RANKS*cardNums[idx] + cardNums[idx2]);
		}
		case 1: // pair
			// Return card rank of pair
			for (short i = 0; i < (CARDS_PER_HAND - 1); i++)
				if (cardNums[i] == cardNums[i+1])
					idx = i;
			return cardNums[idx];
	}
	return 0;
}

void selectionSort(char arr[]) {
// Sort the input array (increasing)
	char minValue;
	short minIdx;
	for (short i = 0; i < (CARDS_PER_HAND-1); i++) {
		minValue = arr[i];
		minIdx = i;
		for (short j = i + 1; j < CARDS_PER_HAND; j++) {
			 if ( arr[j] < minValue) {
				minValue = arr[j];
				minIdx = j;
			}
		}
		// Swap i and min value
		arr[minIdx] = arr[i];
		arr[i] = minValue;
	}
}

char char2CardRank(char in) {
// Given the input char of a card number,
// Return the value of the card (2 = 0, Ace high = 12

	if (in < 58) // 2 thru 9
		return in - 50;
	else if (in == 'T')
		return 8;
	else if (in == 'J')
		return 9;
	else if (in == 'Q')
		return 10;
	else if (in == 'K')
		return 11;
	else if (in == 'A')
		return 12;
	else
		return 0;
}
