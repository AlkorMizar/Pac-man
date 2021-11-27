#pragma once
#include "Coords.h"
namespace directions {
	const Coords    UP{ 0, 1 };
	const Coords  DOWN{ 0,-1 };
	const Coords RIGHT{ 1, 0 };
	const Coords  LEFT{ -1, 0 };
}

namespace FrameRate {
	const int FRAME_RATE = 41;
}

namespace mazeSize {
	const int ROWS_IN_MAZE = 28;
	const int COLUMS_IN_MAZE = 28;
}

enum ObjID :int
{
	WALL       = 0b0,
	PATH       = 0b1,
	COIN       = 0b01,
	SUPER_COIN = 0b001,
	PAC_MAN    = 0b0001,
	RED_GH     = 0b00001,
	PINK_GH    = 0b000001,
	BLUE_GH    = 0b0000001,
	ORANGE_GH  = 0b00000001,
	CHERRY     = 0b000000001,
	MENU       = 0b0000000001,
	TONNEL    = 0b00000000001
};

enum EnemyStateEnum {
	CHASE, SCATTER, FRIGHTENED
};

enum PalyerStateEnum {
	NORMAL, POWER_UP
};