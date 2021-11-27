#pragma once
#include <vector>
#include <stack>
#include <map>

namespace maze {
	enum twist {
		TOP_LEFT = 0B011100100,
		TOP_RIGHT = 0B110001001,
		BOTTOM_RIGHT = 0B001001110,
		BOTTOM_LEFT = 0B100100011
	};

	enum pattern {
		VERTICAL_ROW = 0B010010010,
		HORIZONTAL_ROW = 0B000111000,
		CROSS = 0B010111010
	};

	enum DificultyEnum
	{
		HARD=10000,NORMAL=4,EASY=1
	};

	struct MazeContext
	{
		int mazeRows;
		int mazeColums;
		DificultyEnum dificulty;
		long seed;
	};

	struct Cell
	{
		int row;
		int colum;
	};

	struct CellArray {
		Cell cells[4];
		int size = 0;
		int wallsCount = 0;
	};
	
	typedef std::vector<std::vector<int>> TwoDimArr;
	typedef std::vector<Cell> CellList;
	typedef std::stack<Cell> CellStack;
	typedef std::vector< std::vector<int8_t>> smallArray;

	class  MazeCreator
	{
	public:
		MazeCreator();
		~MazeCreator();
		TwoDimArr generateMap(MazeContext);
	private:
		TwoDimArr maze;
		TwoDimArr cellsStatus;
		CellList wallList;
		CellStack visitedCells;
		std::map<int, smallArray> map;
		int mazeRows, mazeColums;
		
		void generateEmptyMaze();
		void goInAllDirections(Cell);
		std::vector<int> generateRandomDirections();
		void goInCells(bool isExist, Cell, Cell);
		void function(CellArray&, Cell, bool condition);
		CellArray getWallsAround(Cell);
		void deleteDeadEnds();
		int getWallsCode(Cell);
		bool tryDeleteWall(Cell);
		smallArray getWallsOnDelete(Cell);
		int deleteTwist(smallArray wallsOnDelete, Cell, int count);
		void deleteTwists(int i1);
		void createTonnel();
	};
}
