#include "GameContext.h"
#include "MazeCreator.h"
#include "Constant.h"
#include <time.h>

GameContext::GameContext()
{
	setGameState(GameState::WAIT_START);
}

GameContext::~GameContext()
{
}

void GameContext::setGameState(GameState state)
{
	this->state = state;
	switch (state)
	{
	case WAIT_START: {
		map = mazeCreator.generateMap(maze::MazeContext{ mazeSize::ROWS_IN_MAZE,
														 mazeSize::COLUMS_IN_MAZE,
														 maze::DificultyEnum::HARD,
														 0 });
		break;
	}
	case START_PALING:{
		map = mazeCreator.generateMap(maze::MazeContext{ mazeSize::ROWS_IN_MAZE,
														 mazeSize::COLUMS_IN_MAZE,
														 maze::DificultyEnum::EASY,
														 static_cast<long>(12356413216542132221) });
		for (size_t i = 1; i < mazeSize::ROWS_IN_MAZE; i++)
		{
			for (size_t j = 1; j < mazeSize::COLUMS_IN_MAZE; j++)
			{
				if (map[i][j]  == ObjID::PATH) {
					map[i][j] |= ObjID::COIN;
				}
			}
		}
		map[1][1] = ObjID::PATH | ObjID::SUPER_COIN;
		map[1][mazeSize::ROWS_IN_MAZE-1] = ObjID::PATH | ObjID::SUPER_COIN;
		map[mazeSize::COLUMS_IN_MAZE-1][1] = ObjID::PATH | ObjID::SUPER_COIN;
		map[mazeSize::COLUMS_IN_MAZE - 1][mazeSize::ROWS_IN_MAZE - 1] = ObjID::PATH | ObjID::SUPER_COIN;
		break;
	}
	default:
		break;
	}
}
