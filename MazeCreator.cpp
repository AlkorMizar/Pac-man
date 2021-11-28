#include <iostream>
#include "Constant.h"
#include "MazeCreator.h"

using namespace maze;
using namespace std;

maze::MazeCreator::MazeCreator::MazeCreator()
{
	map[TOP_LEFT] = { {0,-1},{-1,0},{1,-1},{-1,1} };
	map[TOP_RIGHT] = { {0,1},{-1,0},{1,1},{-1,-1} };
	map[BOTTOM_RIGHT] = { {0,1},{1,0},{-1,1},{1,-1} };
	map[BOTTOM_LEFT] = { {0,-1},{1,0},{-1,-1},{1,1} };
}

std::vector<int> maze::MazeCreator::generateRandomDirections() {
	std::vector<int> directions = { 1, 2, 3, 4 };
	std::vector<int> randoms(4);
	int i = 0;
	while (directions.size()) {
		int j = rand() % directions.size();
		randoms[i++] = directions[j];
		directions.erase(directions.begin() + j);
	}
	return randoms;
}

void maze::MazeCreator::goInCells(bool isExist, Cell one, Cell two) {
	if (isExist && !maze[two.row][two.colum]) {
		maze[two.row][two.colum] = true;
		maze[one.row][one.colum] = true;
		goInAllDirections(two);
	}
}

void maze::MazeCreator::generateEmptyMaze()
{
	for (int i = 1; i < mazeRows; i++)
	{
		for (int j = 1; j < mazeColums; j++)
		{
			maze[i][j] = ObjID::PATH;
		}
	}
}

void maze::MazeCreator::goInAllDirections(Cell cell) {
	// 4 random directions
	auto randDirs = generateRandomDirections();
	// Examine each direction
	for (int i = 0; i < 4; i++) {

		switch (randDirs[i]) {
		case 1: // Up
			//?Whether 2 cells up is out or not
			goInCells(cell.row > 1, Cell{ cell.row - 1,cell.colum }, Cell{ cell.row - 2,cell.colum });
			break;
		case 2: // Right
			// Whether 2 cells to the right is out or not

			goInCells(cell.colum < mazeColums - 2, Cell{ cell.row,cell.colum + 1 }, Cell{ cell.row,cell.colum + 2 });
			break;
		case 3: // Down
			// Whether 2 cells down is out or not
			goInCells(cell.row < mazeRows - 2, Cell{ cell.row + 1,cell.colum }, Cell{ cell.row + 2,cell.colum });
			break;
		case 4: // Left
			// Whether 2 cells to the left is out or not
			goInCells(cell.colum > 1, Cell{ cell.row ,cell.colum - 1 }, Cell{ cell.row,cell.colum - 2 });
			break;
		}
	}

}

void maze::MazeCreator::function(CellArray& result, Cell x, bool condition) {
	if (condition && !maze[x.row][x.colum]) {
		result.cells[result.size] = x;
		result.size += 1;
	}					//isBorder  or    isWall
	result.wallsCount += !condition || !maze[x.row][x.colum];
}

CellArray maze::MazeCreator::getWallsAround(Cell cell) {
	CellArray result;
	function(result, Cell{ cell.row - 1,cell.colum }, cell.row - 1);
	function(result, Cell{ cell.row + 1,cell.colum }, cell.row < mazeRows - 1);
	function(result, Cell{ cell.row,cell.colum - 1 }, cell.colum - 1);
	function(result, Cell{ cell.row,cell.colum + 1 }, cell.colum < mazeColums - 1);
	return result;
}

void maze::MazeCreator::deleteDeadEnds() {
	for (int i = 1; i < mazeRows; i++)
	{
		for (int j = 1; j < mazeColums; j++)
		{
			if (maze[i][j]) {
				auto wallsAround = getWallsAround(Cell{ i,j });
				if (wallsAround.wallsCount == 3) {
					Cell cell = wallsAround.cells[rand() % wallsAround.size];
					maze[cell.row][cell.colum] = true;
				}
			}
		}
	}
}

int maze::MazeCreator::getWallsCode(Cell cell) {
	int r = cell.row - 1,
		c = cell.colum - 1;
	int wallsCode = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			wallsCode = wallsCode << 1 | !maze[r + i][c + j];
		}
	}
	return wallsCode;
}

bool maze::MazeCreator::tryDeleteWall(Cell w) {
	bool isBorder = w.row != 0 && w.colum != 0 && w.row != mazeRows && w.colum != mazeColums;
	if (isBorder) {
		int wallsCode = getWallsCode(w);
		int pattern = wallsCode & CROSS;
		maze[w.row][w.colum] = (pattern == VERTICAL_ROW || pattern == HORIZONTAL_ROW);
		return maze[w.row][w.colum];
	}
	return false;
}

smallArray maze::MazeCreator::getWallsOnDelete(Cell cell) {
	int wallsCode = getWallsCode(cell);
	smallArray wallsOnDelete;
	wallsOnDelete = map[wallsCode & TOP_LEFT].size() ? map[TOP_LEFT] :
		map[wallsCode & TOP_RIGHT].size() ? map[TOP_RIGHT] :
		map[wallsCode & BOTTOM_RIGHT].size() ? map[BOTTOM_RIGHT] :
		map[wallsCode & BOTTOM_LEFT].size() ? map[BOTTOM_LEFT] :
		wallsOnDelete;
	return wallsOnDelete;
}

int maze::MazeCreator::deleteTwist(smallArray wallsOnDelete, Cell cell, int count) {
	auto s = wallsOnDelete.size();
	bool stop = false;
	int i = 0;
	for (; i < 4 && !stop; i++)
	{
		auto wall = Cell{ cell.row + wallsOnDelete[(count + i) % s][0],cell.colum + wallsOnDelete[(count + i) % s][1] };
		stop = tryDeleteWall(wall);
	}

	return (count + i) % s;
	return count;
}

void maze::MazeCreator::deleteTwists(int i1) {
	int count = 0;
	int c = 0;
	for (int i = 1; i < mazeRows; i++)
	{
		for (int j = 1; j < mazeColums; j++)
		{
			if (maze[i][j]) {
				auto del = getWallsOnDelete(Cell{ i,j });
				if (del.size() && (c++ % i1 == 0)) {
					count = deleteTwist(del, Cell{ i,j }, count);
				}


			}
		}
	}
}

void maze::MazeCreator::createTonnel() {
	int tonnelRow = mazeRows / 2;
	if (!maze[tonnelRow][1] || !maze[tonnelRow][mazeColums - 1]) {
		tonnelRow--;
		if (!maze[tonnelRow][1] || !maze[tonnelRow][mazeColums - 1]) {
			tonnelRow += 2;
		}
	}
	maze[tonnelRow][0] = maze[tonnelRow][mazeColums] = ObjID::PATH | ObjID::TONNEL;
}

TwoDimArr maze::MazeCreator::generateMap(MazeContext context)
{
	mazeRows = context.mazeRows;
	mazeColums = context.mazeColums;

	maze = TwoDimArr(mazeRows + 1, std::vector<int>(mazeColums + 1));
	if (context.seed != 0) {
		srand(context.seed);
		int r = rand() % mazeRows % 2 * 2 + 1;
		int c = rand() % mazeColums % 2 * 2 + 1;
		maze[r][c] = 0;
		//?Allocate the maze with recursive method
		goInAllDirections(Cell{ r,c });
		deleteDeadEnds();
		deleteTwists(context.dificulty);
	}
	else {
		generateEmptyMaze();
	}	
	createTonnel();
	return maze;
}

maze::MazeCreator::MazeCreator::~MazeCreator()
{
	
}