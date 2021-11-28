#pragma once
#include "Coords.h"
#include "Constant.h"
#include "Enemy.h"

class BlueGhost:public Enemy
{
public:
	BlueGhost();
	~BlueGhost();
	void setCurrentTile(Coords newTile, Coords playerTile);
private:

};