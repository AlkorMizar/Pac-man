#pragma once
#include "Enemy.h"

class PinkGhost:Enemy
{
public:
	PinkGhost();
	~PinkGhost();
	void setCurrentTile(Coords newTile, Coords playerTile);
private:

};