#include "eulerUtils.h"
#include <iostream>
#include <string>
#include <cmath>
#include <climits>
#include <set>

int optimalPath(int *, std::vector<std::vector<int>>, bool *);
void updateNeighbor(int, int, std::vector<std::vector<bool>> *,\
			unsigned long long, std::vector<std::vector<int>> *, \
			std::vector<std::vector<unsigned int>> *, \
			std::set<unsigned long long> *);

std::string problem83() {
// Path sum - can move left right up and down
// Given a file of 80 by 80, find smallest sum path
// from top left to bottom right

/*
Copy of Problem 81
*/

	// Convention: 0 - Left | 1 - Right | 2 - Up | 3 - Down
	bool allowedDirecs[4] = {true, true, true, true}; // Right and down only

	// Get passwords from file
	std::string fileName = "./ProblemSource/0083_matrix.txt";
	std::vector<std::string> gridRows = file2StringArray(fileName,"\n");

	std::vector<std::vector<int>> grid;
	std::vector<int> row;

	// String vals to num
	int cellVal;
	for (unsigned int i = 0; i < gridRows.size(); i++) {
		row.clear();
		// Delim based on comma
		int commaPlace = -1;
		for (unsigned int j = 0; j <= gridRows[i].size(); j++) {
			if ( (j == gridRows[i].size()) || (gridRows[i][j] == ',') ) {
				cellVal = 0;
				for (int tenPow = (j-commaPlace-2); tenPow >= 0; tenPow--)
					cellVal += std::pow(10,tenPow)*(gridRows[i][j-tenPow-1] - 48);
				//std::cout << "Cell: " << cellVal << std::endl;
				commaPlace = j;
				row.push_back(cellVal);
			}
		}
		/*
		std::cout << "row: [";
		for (int myNum : row)
			std::cout << myNum << ", ";
		std::cout << std::endl;
		*/
		grid.push_back(row);
	}

	/*
	grid = {{131,673,234,103, 18},\
	        {201, 96,342,965,150},\
	        {630,803,746,422,111},\
	        {537,699,497,121,956},\
  	        {805,732,524, 37,331}};
	*/

	// Grid touch vector
	int nRows = grid.size();
	int nCols = grid[0].size();

	int startEndPoints[4] = {0, 0, nCols-1, nRows-1};

	// Find optimal path
	int pathSum = optimalPath(startEndPoints, grid, allowedDirecs);

	return std::to_string(pathSum);
}

int optimalPath(int startEndPoints[], std::vector<std::vector<int>> grid, \
		 bool allowedDirecs[]) {
	//std::cout << "Starting Dijkstra's Algorithm...\n";

	// Initialize unvisited set, distance array, and visited bool array
	std::vector<std::vector<bool>> visitedCell;
	std::vector<std::vector<unsigned int>> distance;
	std::set<unsigned long long> unvisitedCells;
	unsigned long long infDist = INT_MAX;

	std::vector<bool> falseVec;
	std::vector<unsigned int> infVec;
	for (unsigned int i = 0; i < grid[0].size(); i++) {
		falseVec.push_back(false);
		infVec.push_back((unsigned int)infDist);
	}
	for (unsigned int i = 0; i < grid.size(); i++) {
		visitedCell.push_back(falseVec);
		distance.push_back(infVec);
		for (unsigned int j = 0; j < grid[i].size(); j++) {
			visitedCell[i][j] = false;
			distance[i][j] = infDist;
			unvisitedCells.insert((infDist << 16) + (j << 8) + i);
		}
	}
	int startCellDist = grid[startEndPoints[0]][startEndPoints[1]];
	distance[startEndPoints[0]][startEndPoints[1]] = startCellDist;
	unvisitedCells.erase((infDist << 16) + (startEndPoints[1] << 8) + startEndPoints[0]);
	unvisitedCells.insert((startCellDist << 16) + (startEndPoints[1] << 8) + startEndPoints[0]);

	// Loop while we have not vistied end node
	unsigned long long smallestDist;
	int closestNode[2];

	int neighborRow, neighborCol;

	int rowLim = grid.size();
	int colLim = grid[0].size();
	/*
	std::cout << "Beginning to loop on nodes...\n";
	std::cout << "Start node: [" << startEndPoints[0] << ", " << startEndPoints[1] << "]\n";
	std::cout << "End node: [" << startEndPoints[2] << ", " << startEndPoints[3] << "]\n";
	std::cout << "Row lim: " << rowLim << " Col lim: " << colLim << std::endl;
	*/
	int itCount = 0;
	bool goalCellEncountered = false;
	while (!goalCellEncountered) {
		//std::cout << "Finding next smallest dist...\n";

		// Current node is unvisited with smallest distance
		smallestDist = *unvisitedCells.begin();
		closestNode[0] = (smallestDist & 0xFF);
		smallestDist >>= 8;
		closestNode[1] = (smallestDist & 0xFF);
		smallestDist >>= 8;

		//std::cout << "Visiting node: [" << closestNode[0] << ", " << closestNode[1] << "]\n";

		goalCellEncountered = ((closestNode[0] == startEndPoints[2]) && \
					(closestNode[1] == startEndPoints[3]));

		// Update dist of all unvisited neighbors
		// Left
		neighborRow = closestNode[0];
		neighborCol = closestNode[1]-1;
		if ( allowedDirecs[0] && (neighborCol >= 0) ) {
			updateNeighbor(neighborRow, neighborCol, &visitedCell, \
				smallestDist, &grid, &distance, &unvisitedCells);
		}

		// Right
		neighborRow = closestNode[0];
		neighborCol = closestNode[1]+1;
		if ( allowedDirecs[1] && (neighborCol < colLim) ) {
			updateNeighbor(neighborRow, neighborCol, &visitedCell, \
				smallestDist, &grid, &distance, &unvisitedCells);
		}

		// Up
		neighborRow = closestNode[0]-1;
		neighborCol = closestNode[1];
		if ( allowedDirecs[2] && (neighborRow >= 0) ) {
			updateNeighbor(neighborRow, neighborCol, &visitedCell, \
				smallestDist, &grid, &distance, &unvisitedCells);
		}

		// Down
		neighborRow = closestNode[0]+1;
		neighborCol = closestNode[1];
		if ( allowedDirecs[3] && (neighborRow < rowLim) ) {
			updateNeighbor(neighborRow, neighborCol, &visitedCell, \
				smallestDist, &grid, &distance, &unvisitedCells);
		}

		// Remove curr node from unvisited set
		unvisitedCells.erase(unvisitedCells.begin());
		visitedCell[closestNode[0]][closestNode[1]] = true;

		itCount++;
	}

	//std::cout << "It count: " << itCount << std::endl;

	// Min distance of end node from start node
	return smallestDist;
}

void updateNeighbor(int neighborRow, int neighborCol, std::vector<std::vector<bool>> * visitedCell,\
			unsigned long long cellDist, std::vector<std::vector<int>> * grid, \
			std::vector<std::vector<unsigned int>> * distance, \
			std::set<unsigned long long> * unvisitedCells) {
// For a given neighbor cell, check if it has been visited.
// If it has not been visited, and the calculated distance is smaller than the current
// distance we have for it, update the distance value in both the unvisitedCells set and
// the distance 2D array
	if (!visitedCell->at(neighborRow).at(neighborCol)) {
		unsigned long long neighborDist, oldNeighborDist, oldCode, newCode;

		neighborDist = cellDist + grid->at(neighborRow).at(neighborCol);

		// Update min dist to this node
		if ( distance->at(neighborRow).at(neighborCol) > neighborDist) {
			oldNeighborDist = distance->at(neighborRow).at(neighborCol);
			oldCode = (oldNeighborDist << 16) + (neighborCol << 8) + neighborRow;
			newCode = (neighborDist << 16) + (neighborCol << 8) + neighborRow;
			unvisitedCells->erase(oldCode);
			unvisitedCells->insert(newCode);
			distance->at(neighborRow).at(neighborCol) = neighborDist;
		}
	}
}
