#include "eulerUtils.h"
#include <iostream>
#include <string>

std::string problem19() {
// How many sundays fell on the first of the month
// between 1901 Jan 01 and 2000 Dec 31

	short currYear = 1900;
	short currMonth = 1;
	short currDay = 1;
	short currWeekday = 2; // We'll let Sunday be 1

	short startCountYear = 1901; // We only count sundays from 1901 onward

	short finalYear = 2000;
	short finalMonth = 12;
	short finalDay = 31;

	short daysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	unsigned short ans = 0;

	// Iterate one day at a time until the end (brute force)
	while ( (currYear != finalYear) || (currMonth != finalMonth) || \
		 (currDay != finalDay)) {
		currDay++;
		currWeekday = (currWeekday % 7) + 1;

		if ( currDay > daysPerMonth[currMonth - 1] ) {
			currMonth++;
			currDay = 1;
			if ( currMonth > 12 ) {
				currYear++;
				currMonth = 1;
				if (isLeapYear(currYear))
					daysPerMonth[1] = 29;
				else
					daysPerMonth[1] = 28;
			}
		}

		if ( (currDay == 1) && (currWeekday == 1) && (currYear >= startCountYear)){
			ans++;
			//std::cout << "The day below was a sunday on a first o the month!\n";
		}

		//std::cout << currYear << "-" << currMonth << "-" << currDay << " was weekday " << currWeekday << std::endl;
	}

	return std::to_string(ans);
}
