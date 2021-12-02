#include "RedGhost.h"
#include <vector>

RedGhost::RedGhost(std::vector<int> time) :Enemy(time)
{

	offset = { 0,0 };
	directedTile = homeCoord = { mazeSize::COLUMS_IN_MAZE - 1,mazeSize::ROWS_IN_MAZE - 1 };
	timeConstant = std::vector<int>(5);
	timeConstant[EnemyStateEnum::CHASE] = 700;
	timeConstant[EnemyStateEnum::SCATTER] = 45;
	timeConstant[EnemyStateEnum::FRIGHTENED] = 100;
	timeConstant[EnemyStateEnum::DEAD] = 100;

	timeConstant[EnemyStateEnum::WAIT_TO_GO] = 150;
}

RedGhost::~RedGhost()
{
}

