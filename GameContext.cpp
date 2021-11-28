#include "GameContext.h"
#include "MazeCreator.h"
#include "Constant.h"
#include <time.h>

using namespace mazeSize;
using namespace maze;
using namespace points;

GameContext::GameContext()
{
	setGameState(GameState::WAIT_START);
	direction = directions::STILL;
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
		map = mazeCreator.generateMap(MazeContext{ ROWS_IN_MAZE,
												   COLUMS_IN_MAZE,
												   DificultyEnum::HARD,
												   0 });
		player.isInGame = true;
		player.setCurrentTile(Coords{ 0,ROWS_IN_MAZE / 2 });
		break;
	}
	case START_PLAYING:{
		map = mazeCreator.generateMap(maze::MazeContext{ mazeSize::ROWS_IN_MAZE,
														 mazeSize::COLUMS_IN_MAZE,
														 maze::DificultyEnum::EASY,
														 static_cast<long>(12356413216542132221) });
		
		for (size_t i = 1; i < mazeSize::ROWS_IN_MAZE; i++)
		{
			for (size_t j = 1; j < mazeSize::COLUMS_IN_MAZE; j++)
			{
				if (map[i][j]  & ObjID::PATH) {
					map[i][j] |= ObjID::COIN;
				}
			}
		}
		int tonelI = map[ROWS_IN_MAZE / 2][0] & ObjID::TONNEL ? ROWS_IN_MAZE / 2 :
					 map[ROWS_IN_MAZE / 2 - 1][0] & ObjID::TONNEL ? ROWS_IN_MAZE / 2 - 1 :
					 map[ROWS_IN_MAZE / 2 + 1][0] & ObjID::TONNEL ? ROWS_IN_MAZE / 2 + 1 : 0;
		map[1][1] = ObjID::PATH | ObjID::SUPER_COIN;
		map[1][mazeSize::ROWS_IN_MAZE-1] = ObjID::PATH | ObjID::SUPER_COIN;
		map[mazeSize::COLUMS_IN_MAZE-1][1] = ObjID::PATH | ObjID::SUPER_COIN;
		map[mazeSize::COLUMS_IN_MAZE - 1][mazeSize::ROWS_IN_MAZE - 1] = ObjID::PATH | ObjID::SUPER_COIN;
		player.isInGame = true;
		player.setCurrentTile(Coords{ 0,tonelI });
		break;
	}
	default:
		break;
	}
}
void GameContext::reCalculate()
{
	Coords nextT = player.getCurrentTile() + player.getDirection();
	bool isTonnel = nextT.x == -1 || nextT.x == mazeSize::COLUMS_IN_MAZE + 1;
	if (isTonnel || map[nextT.y][nextT.x] & PATH) {
		auto offset = player.getOffset();
		auto dir = player.getDirection();
		offset = offset + dir * player.getSpeed();
		if (abs(offset.x) >= 100 || abs(offset.y)>=100) {
			player.setOffset({ 0,0 });		
			player.setDirection(direction);
			if (isTonnel) {
				nextT.x = (nextT.x+29)%29;
			}
			player.setCurrentTile(nextT);
		}
		else
		{
			if (dir.x == 0) {
				player.setOffset({ 0,offset.y });
			}
			else
			{
				player.setOffset({ offset.x,0 });
			}
			
		}
	}
	else
	{
		player.setDirection(directions::STILL);
		isNewDir = false;
	}
}

void GameContext::setPlayerDirection(Coords dir)
{
	Coords oldCoord = player.getDirection(); 
	direction = dir;
	if (oldCoord==directions::STILL) {
		player.setDirection(dir);
	}
	else if(oldCoord.x==dir.x || oldCoord.y == dir.y)
	{

	}
	
}
