#pragma once
#include "Coords.h"

#include <windows.h>

namespace directions {
	const Coords    UP{ 0, 1 };
	const Coords  DOWN{ 0,-1 };
	const Coords RIGHT{ 1, 0 };
	const Coords  LEFT{ -1, 0 };
}


namespace mazeSize {
	const int ROWS_IN_MAZE = 28;
	const int COLUMS_IN_MAZE = 28;
}

namespace frameContext {
	const int FRAME_RATE = 41;
	const int TILE_SIZE = 27,
		TILE_CENTER = 27 / 2 + 1,
		BORDER_TOP = 0,
		BORDER_BOTTOM = TILE_SIZE * (mazeSize::COLUMS_IN_MAZE+1),
		BORDER_LEFT = 300,
		BORDER_RIGHT = BORDER_LEFT + TILE_SIZE * (mazeSize::ROWS_IN_MAZE+1),
		TILE_DELTA = TILE_SIZE/3;
	const int BLUE_COLOR = RGB(0, 39, 255);
	const int BLACK_COLOR = 0;	
}

namespace elementSize {
	const int BUTTON_WIDTH = 250;
	const int BUTTON_HEIGHT = 100;
	
	const int X = 50;

	const int COIN_WIDTH = 250;
	const int COIN_HEIGHT = 40;

	const int COIN_COUNT_WIDTH = 250;
	const int COIN_COUNT_HEIGHT = COIN_HEIGHT;

	const int LIVES_WIDTH = 250;
	const int LIVES_HEIGHT = COIN_HEIGHT;

	const int LIVES_COUNT_WIDTH = 250;
	const int LIVES_COUNT_HEIGHT = COIN_HEIGHT;

	const int COIN_Y = 90;
	const int COIN_COUNT_Y = 5+COIN_Y+COIN_HEIGHT;
	const int LIVES_Y = 120+COIN_COUNT_Y+ COIN_COUNT_HEIGHT;
	const int LIVES_COUNT_Y = 5+LIVES_Y+LIVES_HEIGHT;

	const RECT COIN_RECT = { X,COIN_Y,X + COIN_WIDTH,COIN_Y + COIN_HEIGHT };
	const RECT COIN_COUNT_RECT = { X,COIN_COUNT_Y,X + COIN_COUNT_WIDTH,COIN_COUNT_Y + COIN_COUNT_HEIGHT };
	const RECT LIVES_RECT = { X,LIVES_Y,X + LIVES_WIDTH,LIVES_Y + LIVES_HEIGHT };
	const RECT LIVES_COUNT_RECT = { X,LIVES_COUNT_Y,X + LIVES_COUNT_WIDTH,LIVES_COUNT_Y + LIVES_COUNT_HEIGHT };

}


enum ObjID :int
{
	WALL       = 0,
	PATH       = 1,
	COIN       = PATH<<1,
	SUPER_COIN = COIN<<1,
	PAC_MAN    = SUPER_COIN<<1,
	RED_GH     = PAC_MAN<<1,
	PINK_GH    = RED_GH<<1,
	BLUE_GH    = PINK_GH << 1,
	ORANGE_GH  = BLUE_GH << 1,
	CHERRY     = ORANGE_GH << 1,
	MENU       = CHERRY << 1,
	TONNEL     = MENU << 1
};


enum EnemyStateEnum {
	CHASE, SCATTER, FRIGHTENED
};

enum PalyerStateEnum {
	NORMAL, POWER_UP
};