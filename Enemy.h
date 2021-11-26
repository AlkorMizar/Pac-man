#pragma once
#include "Coords.h"
#include "Constant.h"
#include "BaseClass.h"

class Enemy :Entity
{
public:
	virtual void setCurrentTile(Coords newTile, Coords playerTile) {}
protected:
	EnemyStateEnum state;
	Coords homeCoord;
};
