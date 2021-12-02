#pragma once

#include "Coords.h"
#include "Constant.h"


class Entity
{
public:
	int getSpeed() { return speed; }
	Coords getOffset() { return offset; }
	Coords getCurrentTile() { return currentTile; }
	Coords getDirection() { return direction; }
	ObjID getId() { return id; }
	bool isInGame=false;
	void setSpeed(double sp) { speed = sp; }

	void setDirection(Coords dir) { direction = dir; }
	void setOffset(Coords off) { offset = off; }

protected:
	
	Coords currentTile = {0,0};
	Coords direction = { 0,0 };//from direction constant
	Coords offset = { 0,0 };
	double speed;//percent per Frame
	ObjID id=ObjID::PAC_MAN;
	
};
