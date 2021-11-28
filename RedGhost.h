#pragma once
#include "Enemy.h"

class RedGhost:public Enemy
{
public:
	RedGhost();
	~RedGhost();
	void setCurrentTile(Coords newTile, Coords playerTile);
private:

};