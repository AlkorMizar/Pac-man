#pragma once
#include "BaseClass.h"
#include "Coords.h"

class Player:Entity
{
public:
	Player();
	~Player();
	int getCoinCount();
	int getLivesCount();
	void setLivesCount(int);
	void DecreaseLives();
	void setCoinCount(int);
	void setCurrentTile(Coords);
private:
	int coinsCount;
	int livesCount;
};