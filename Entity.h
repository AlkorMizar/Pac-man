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
	bool isInGame;
	bool move() {
	}

	virtual void setDirection(Coords) {}
	virtual void setOffset(Coords) {}

protected:
	
	Coords currentTile;
	Coords direction;//from direction constant
	Coords offset;
	int speed=8;//percent per Frame
	ObjID id;
	
};
