#pragma once

#include "Coords.h"
#include "Constant.h"


class Entity
{
public:
	double getSpeed() { return speed; }
	Coords getOffset() { return offset; }
	Coords getCurrentTile() { return currentTile; }
	Coords getDirection() { return direction; }
	ObjID getId();

	virtual void setDirection(Coords);
	virtual void setOffset(Coords);

protected:
	Coords currentTile;
	Coords direction;//from direction constant
	Coords offset;//from current tile 
	double speed;//perFrame
	ObjID id;
};
