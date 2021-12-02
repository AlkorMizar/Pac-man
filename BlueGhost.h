#pragma once
#include "Coords.h"
#include "Constant.h"
#include "Enemy.h"

#include <vector>

class BlueGhost:public Enemy
{
public:
	BlueGhost(std::vector<int>);
	~BlueGhost();
private:

};