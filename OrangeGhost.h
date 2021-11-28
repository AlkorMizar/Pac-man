#pragma once
#include "Enemy.h"

class OrangeGhost:public Enemy
{
public:
	OrangeGhost();
	~OrangeGhost();
	void setCurrentTile(Coords newTile, Coords playerTile);
private:

};