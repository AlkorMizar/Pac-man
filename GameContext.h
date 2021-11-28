#pragma once
#include "Player.h"
#include "RedGhost.h"
#include "BlueGhost.h"
#include "PinkGhost.h"
#include "OrangeGhost.h"
#include "MazeCreator.h"

enum GameState
{
	WAIT_START,START_PLAYING,PLAYING,DEAD
};

class GameContext
{
public:
	GameContext();
	~GameContext();
	GameState getGameState() { return state; }
	void setGameState(GameState);
	void reCalculate();
	maze::TwoDimArr map;
	void setPlayerDirection(Coords dir);

	Player player;
	RedGhost red;
	PinkGhost pink;
	BlueGhost blue;
	OrangeGhost orange;

private:
	maze::MazeCreator mazeCreator;
	GameState state;
	Coords direction;
	bool isNewDir=false;
};