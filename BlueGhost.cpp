#include "BlueGhost.h"
#include <vector>

BlueGhost::BlueGhost(std::vector<int> time) :Enemy(time)
	
{
	offset = {0,0};
	directedTile=homeCoord = { 1,1 };
	timeConstant = std::vector<int>(5);
	changeState(EnemyStateEnum::WAIT_TO_GO);
	timeConstant[EnemyStateEnum::CHASE] = 700;
	timeConstant[EnemyStateEnum::SCATTER] = 45;
	timeConstant[EnemyStateEnum::FRIGHTENED] = 100;
	timeConstant[EnemyStateEnum::DEAD] = 100;

	timeConstant[EnemyStateEnum::WAIT_TO_GO] = 300;
}


BlueGhost::~BlueGhost()
{
}

