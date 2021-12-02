#pragma once
#include "Player.h"
#include "Enemy.h"
#include "MazeCreator.h"

namespace EnemyTime{
	const double COEFFICIENT = 0.1;
	const double SPEED_COEF = 0.05;
	const double FIRST_GHOST_TIME = 120/(1-COEFFICIENT);
	const double TIME_BETWEN_GHOST = 100 / (1 - COEFFICIENT);
	const double DEAD_TIME = 200 / (1 - COEFFICIENT);
	const double FRIGHTNET_TIME = 200 / (1 - COEFFICIENT);
	const double SCATTER_TIME = 150 / (1 - COEFFICIENT);
	const double CHASE_TIME = 500 / (1 + COEFFICIENT);
	const double SECOND_GHOST_TIME = (FIRST_GHOST_TIME + TIME_BETWEN_GHOST) / (1 - COEFFICIENT);
	const double THIRD_GHOST_TIME = (SECOND_GHOST_TIME + TIME_BETWEN_GHOST) / (1 - COEFFICIENT);
	const double FOURTH_GHOST_TIME = (THIRD_GHOST_TIME + TIME_BETWEN_GHOST) / (1 - COEFFICIENT);
	
}

enum GameState
{
	WAIT_START,START_PLAYING,PLAYING,DEAD_PLAYER,WON
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
	void startNewGame(maze::MazeTypeEnum diff,long seed);
	long getCurrentSeed() {
		return seed;
	}
	maze::MazeTypeEnum getDifficulty() {
		return diff;
	}

	Player player;
	Enemy red;
	Enemy pink;
	Enemy blue;
	Enemy orange;
	int level;
	Coords cherryCoord;
	bool isCherryTime = false;
	int coinCount = 0;

private:

	void calculateGameStatus();

	void moveEnemy(Enemy& enemy,Coords dirrectedTile);
	void createRed();
	void createBlue();
	void createOrange();
	void createPink();
	void createCherry();
	void movePlayer();
	void moveRed();
	void movePink();
	void moveBlue();
	void moveOrange();
	void createGhost();
	int superCoinCount=0;
	
	int cherryTime;
	maze::MazeCreator mazeCreator;
	GameState state= WAIT_START;
	Coords direction=directions::STILL;
	bool isNewDir=false;
	long seed=-1;
	maze::MazeTypeEnum diff=maze::MazeTypeEnum::NORMAL;
	std::vector<Enemy*> enemies= std::vector<Enemy*>(4);
};