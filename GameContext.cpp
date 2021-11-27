#include "GameContext.h"
#include "MazeCreator.h"
#include "Constant.h"

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
														 mazeSize::ROWS_IN_MAZE,
														 maze::DificultyEnum::EASY,
														 0 });
		break;
	}
	case START_PALING:{
	
	}
	default:
		break;
	}
}
