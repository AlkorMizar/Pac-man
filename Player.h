#pragma once
#include "BaseClass.h"
#include "Coords.h"

class Player:Entity
{
public:
	Player();
	~Player();
	int getCoinCount();
	void setCoinCount(int);
	void setCurrentTile(Coords);
private:

};