#pragma once
#include "Coords.h"
#include "Constant.h"
#include "Entity.h"

class Enemy :public Entity
{
public:
	virtual void setCurrentTile(Coords newTile, Coords playerTile) {}
	bool isInScatter=false;
protected:
	EnemyStateEnum state;
	Coords homeCoord;
};
