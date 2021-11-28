#pragma once
#include "Enemy.h"

class PinkGhost:public Enemy
{
public:
	PinkGhost();
	~PinkGhost();
	void setCurrentTile(Coords newTile, Coords playerTile);
private:

};