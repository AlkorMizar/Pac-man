#pragma once
#include "Player.h"
#include "RedGhost.h"
#include "BlueGhost.h"
#include "PinkGhost.h"
#include "OrangeGhost.h"
#include "MazeCreator.h"

enum GameState
{
	WAIT_START,START_PALING,PLAYING,DEAD
};

class GameContext
{
public:
	GameContext();
	~GameContext();
	GameState getGameState() { return state; }
	void setGameState(GameState);

private:
	maze::MazeCreator mazeCreator;
	GameState state;

	maze::TwoDimArr map;

	Player player;
	RedGhost red;
	PinkGhost pink;
	BlueGhost blue;
	OrangeGhost orange;
};