#include "eulerUtils.h"
#include <iostream>
#include <string>

#include <algorithm>
#include <set>
#include <unordered_set>
#include <cmath>
bool trueIntersection(int[4], int[4], long long[4]);
bool trueIntersection2(int[4], int[4], double[2]);

std::string problem165() {
// Among 5000 random line segments, how many distinct true intersection points?
// True intersection = exactly 1 intersection in segment interior

/*
For this we use a fun pseudorandom number generator -- called a
Blum Blum Shub (BBS). This is interesting in its own right.

To determine line intersection, we can express the segments
in point-slope form:
S = <x1,y1> + <x2-x1,y2-y1>t
Where t is from 0 to 1
For 2 segments A and B, we calculate the intersection with the following:
A1 + M_A * t1 = B1 + M_B * t2
-->
M_A * t1 - MB * t2 = B1 - A1
-->
(ax2 - ax1) * t1 - (bx2 - bx1) * t2 = bx1 - ax1
(ay2 - ay1) * t1 - (by2 - by1) * t2 = by1 - ay1
-->
A * t1 + B * t2 = C
D * t1 + E * t2 = F

This system of 2 equations, 2 unknowns can be solved with Cramer's rule:
det = AE - BD
t1 = (CE - BF)/det
t2 = (AF - CD)/det

If the determinant is nonzero AND t is > 0 and t < 1, we have a true intersection.

It is easy to iterate through all our line segment pairs and calculate true
intersection points. What's harder is counting the number of DISTINCT points from that!
Doing this in a performant way is what makes this tricky, since there are ~2.86 million
total true intersections, and only a handful (~100) overlaps.
The overlaps also require a lot of precision to distinguish from intersection points that
are seperate but very close together.
*/

	const int N = 5000; // Number of segments to generate

	int allSegments[N][4];
	// Example segments
	//int allSegments[][4] = {{27,44,12,32},{46,53,17,62},{46,70,22,40}};

	unsigned long long s0 = 290797; // RNG Seed
	unsigned long long sn = s0;
	int M = 50515093; // RNG mod
	int limit = 500; // RNG num limit

	int segmentCount = 0;
	int i;

	// Generate line segments
	while (segmentCount < N) {
		i = 0;
		while (i < 4) {
			sn = ( (sn * sn) % M );
			allSegments[segmentCount][i] = (sn % limit);
			i++;
		}
		segmentCount++;
	}

	/*
	std::cout << "Line segments: \n";
	for (int i = 0; i < N; i++) {
		std::cout << "(" << allSegments[i][0] << ", ";
		std::cout << allSegments[i][1] << ") -> ";
		std::cout << "(" << allSegments[i][2] << ", ";
		std::cout << allSegments[i][3] << ")\n";
	}
	*/

	// Analyse line segments for intersections
	//long long intersectionPoint[4];
	double intersectionPoint[2];
	int ans = 0;

	std::unordered_set<std::string> intersectPointDB;
	//float intersectionHash;
	unsigned long long calc;
	std::string intersectionHash;
	//unsigned long long intersectionHash;
	//std::vector<unsigned long long> myVec;
	for (int i = 0; i < N; i++) {
		for (int j = (i+1); j < N; j++) {
			//std::cout << "Segment " << i << " and " << j << std::endl;
			if (trueIntersection2(allSegments[i], allSegments[j], intersectionPoint)) {
				//std::cout << "Intersect @ (" << intersectionPoint[0] << "/" << intersectionPoint[1];
				//std::cout << "," << intersectionPoint[2] << "/" << intersectionPoint[3] << ")\n";

				// Calculate intersection unique ID from num1, num2, and den
				/*
				intersectionHash = intersectionPoint[0] * 1e11 + intersectionPoint[1] * 1e5;
				intersectionHash.append(std::to_string(intersectionPoint[1]));
				intersectionHash.append(std::to_string(intersectionPoint[2]));
				intersectionHash.append(std::to_string(intersectionPoint[3]));
				*/
				//myVec.push_back(intersectionHash);
				//std::cout << "Intersect @ (" << intersectionPoint[0] << ", ";
				//std::cout << intersectionPoint[1] << ")\n";
				
				
				calc = std::round(intersectionPoint[0]*1e10);
				intersectionHash = std::to_string(calc);
				calc = std::round(intersectionPoint[1]*1e10);
				intersectionHash += std::to_string(calc);
				
				//intersectionHash = std::to_string(intersectionPoint[0]);
				//intersectionHash = intersectionPoint[0] * 1e9;
				//std::cout << "Hash: " << intersectionHash << std::endl;
				//myVec.push_back(intersectionHash);

				auto it = intersectPointDB.find(intersectionHash);
				if (it != intersectPointDB.end()) {
					std::cout << "Segment " << i << " and " << j << std::endl;
					std::cout << "Intersect @ (" << intersectionPoint[0] << ", ";
					std::cout << intersectionPoint[1] << ")\n";
					
				} 

				


				intersectPointDB.insert(intersectionHash);
				//ans++;
			}
		}
	}

	/*
	std::sort(myVec.begin(), myVec.end());
	for (unsigned int i = 1; i < myVec.size(); i++) {
		if ( (myVec[i] - myVec[i-1]) > 1e-9 )
			ans++;
	}
	//std::cout << "Set size: " << myVec.size() << std::endl;
	*/
	//std::cout << "Set size: " << intersectPointDB.size() << std::endl;
	ans = intersectPointDB.size();
	return std::to_string(ans);
}

bool trueIntersection(int segment1[4], int segment2[4], long long intersectionPoint[4]) {
// Assume segment comes in as: [x1,y1,x2,y2]
// To avoid floating points, we calculate exact fractions.
// Where t1 = num1/det, t2 = num2/det
// If intersection exists, return simplified [numX,denX,numY,denY]
	bool ans = false;

	// System of eqs
	int A,B,C,D,E,F,det,num1,num2;
	//double t1, t2;
	A = segment1[2] - segment1[0];
	B = segment2[0] - segment2[2];
	D = segment1[3] - segment1[1];
	E = segment2[1] - segment2[3];
	det = A*E - B*D;
	//std::cout << "det: " << det << std::endl;
	if (det != 0) {
		C = segment2[0] - segment1[0];
		F = segment2[1] - segment1[1];
		num1 = (C*E - B*F);
		num2 = (A*F - C*D);
		if (det < 0) {
			det = -det;
			num1 = -num1;
			num2 = -num2;
		}
		//t1 = (double)(C*E - B*F)/det;
		//t2 = (double)(A*F - C*D)/det;
		//std::cout << "t1: " << t1 << " t2: " << t2 << std::endl;
		if ( (num1 > 0) && (num1 < det) && (num2 > 0) && (num2 < det) ) {
			ans = true;
			intersectionPoint[0] = segment1[0]*det + num1*A;
			intersectionPoint[1] = det;
			intersectionPoint[2] = segment1[1]*det + num1*D;
			intersectionPoint[3] = det;
			//simplifyFraction(&intersectionPoint[0], &intersectionPoint[1]);
			//simplifyFraction(&intersectionPoint[2], &intersectionPoint[3]);
		}
	}

	return ans;
}

bool trueIntersection2(int segment1[4], int segment2[4], double intersectionPoint[2]) {
// Assume segment comes in as: [x1,y1,x2,y2]
// To avoid floating points, we calculate exact fractions.
// Where t1 = num1/det, t2 = num2/det
// If intersection exists, return simplified [numX,denX,numY,denY]
	bool ans = false;

	// System of eqs
	int A,B,C,D,E,F,det,num1,num2;
	A = segment1[2] - segment1[0];
	B = segment2[0] - segment2[2];
	D = segment1[3] - segment1[1];
	E = segment2[1] - segment2[3];
	det = A*E - B*D;
	//std::cout << "det: " << det << std::endl;
	if (det != 0) {
		C = segment2[0] - segment1[0];
		F = segment2[1] - segment1[1];
		num1 = (C*E - B*F);
		num2 = (A*F - C*D);
		if (det < 0) {
			det = -det;
			num1 = -num1;
			num2 = -num2;
		}
		//t1 = (double)(C*E - B*F)/det;
		//t2 = (double)(A*F - C*D)/det;
		//std::cout << "t1: " << t1 << " t2: " << t2 << std::endl;
		if ( (num1 > 0) && (num1 < det) && (num2 > 0) && (num2 < det) ) {
			ans = true;
			intersectionPoint[0] = segment1[0] + (double)num1/det*A;
			intersectionPoint[1] = segment1[1] + (double)num1/det*D;
		}
	}

	return ans;
}

