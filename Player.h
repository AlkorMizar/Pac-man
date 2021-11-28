#pragma once
#include "Entity.h"
#include "Coords.h"

class Player:public Entity
{
public:
	Player();
	~Player();
	int getCoinCount();
	int getLivesCount();
	void setLivesCount(int);
	void DecreaseLives();
	void setCoinCount(int);
	void increaseCoinCount(int val) { coinsCount += val; }
	void setCurrentTile(Coords);
	void setDirection(Coords);
	void setOffset(Coords);
private:
	int coinsCount;
	int livesCount;
};