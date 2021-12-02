#include "GameContext.h"
#include "MazeCreator.h"
#include "Constant.h"
#include <time.h>
#include <vector>

using namespace mazeSize;
using namespace maze;
using namespace points;




void GameContext::createRed()
{
	std::vector<double> time(5);
	time[EnemyStateEnum::CHASE] = EnemyTime::CHASE_TIME;
	time[EnemyStateEnum::SCATTER] = EnemyTime::SCATTER_TIME;
	time[EnemyStateEnum::FRIGHTENED] = EnemyTime::FRIGHTNET_TIME;
	time[EnemyStateEnum::DEAD] = EnemyTime::DEAD_TIME;
	time[EnemyStateEnum::WAIT_TO_GO] = EnemyTime::FIRST_GHOST_TIME;
	red = Enemy(time, {1,1});
}

void GameContext::createBlue()
{
	std::vector<double> time(5);
	time[EnemyStateEnum::CHASE] = EnemyTime::CHASE_TIME;
	time[EnemyStateEnum::SCATTER] = 10;
	time[EnemyStateEnum::FRIGHTENED] = EnemyTime::FRIGHTNET_TIME;
	time[EnemyStateEnum::DEAD] = EnemyTime::DEAD_TIME;
	time[EnemyStateEnum::WAIT_TO_GO] = EnemyTime::SECOND_GHOST_TIME;
	blue = Enemy(time, { 1,mazeSize::COLUMS_IN_MAZE - 1 });
}

void GameContext::createOrange()
{
	std::vector<double> time(5);
	time[EnemyStateEnum::CHASE] = EnemyTime::CHASE_TIME;
	time[EnemyStateEnum::SCATTER] = EnemyTime::SCATTER_TIME;
	time[EnemyStateEnum::FRIGHTENED] = EnemyTime::FRIGHTNET_TIME;
	time[EnemyStateEnum::DEAD] = EnemyTime::DEAD_TIME;
	time[EnemyStateEnum::WAIT_TO_GO] = EnemyTime::THIRD_GHOST_TIME;
	orange = Enemy(time, { mazeSize::ROWS_IN_MAZE - 1,1 });
}

void GameContext::createPink()
{
	std::vector<double> time(5);
	time[EnemyStateEnum::CHASE] = EnemyTime::CHASE_TIME;
	time[EnemyStateEnum::SCATTER] = EnemyTime::SCATTER_TIME;
	time[EnemyStateEnum::FRIGHTENED] = EnemyTime::FRIGHTNET_TIME;
	time[EnemyStateEnum::DEAD] = EnemyTime::DEAD_TIME;
	time[EnemyStateEnum::WAIT_TO_GO] = EnemyTime::FOURTH_GHOST_TIME;
	pink = Enemy(time, { mazeSize::ROWS_IN_MAZE - 1,mazeSize::COLUMS_IN_MAZE - 1 });
}

void GameContext::createCherry()
{
	do
	{
		cherryCoord.x = rand() % (mazeSize::COLUMS_IN_MAZE - 1) + 1;
		cherryCoord.y = rand() % (mazeSize::ROWS_IN_MAZE - 1) + 1;
	} while (map[cherryCoord.y][cherryCoord.x] & COIN || map[cherryCoord.y][cherryCoord.x] == WALL);
	cherryTime = 180;
	map[cherryCoord.y][cherryCoord.x] |= CHERRY;
}

void GameContext::createGhost() {
	createRed();
	createBlue();
	createPink();
	createOrange();

	enemies[0] = &red;
	enemies[1] = &blue;
	enemies[2] = &pink;
	enemies[3] = &orange;
}

GameContext::GameContext()
{
	setGameState(GameState::WAIT_START);
	direction = directions::STILL;
	
}

GameContext::~GameContext()
{
	
}

void GameContext::setGameState(GameState state)
{
	this->state = state;
	switch (state)
	{
	case WAIT_START: {
		map = mazeCreator.generateMap(maze::MazeContext{ mazeSize::ROWS_IN_MAZE,
														 mazeSize::COLUMS_IN_MAZE,
														 maze::MazeTypeEnum::NORMAL,
														 static_cast<long>(0) });
		player.setLivesCount(0);
		player.isInGame = false;
		red.isInGame = false;
		pink.isInGame = false;
		orange.isInGame = false;
		blue.isInGame = false;
		break;
		level = 0;
	}
	case START_PLAYING: {
		createGhost();
		level = 1;
		map = mazeCreator.generateMap(maze::MazeContext{ mazeSize::ROWS_IN_MAZE,
													 mazeSize::COLUMS_IN_MAZE,
													 diff,
													 seed });
		player.setCoinCount(0);
		player.setLivesCount(3);
		superCoinCount = 4;
		coinCount = 0;
		for (size_t i = 1; i < mazeSize::ROWS_IN_MAZE; i++)
		{
			for (size_t j = 1; j < mazeSize::COLUMS_IN_MAZE; j++)
			{
				if (map[i][j] & ObjID::PATH) {
					map[i][j] |= ObjID::COIN;
					coinCount++;
				}
			}
		}
		coinCount -= 4;
		int tonelI = map[ROWS_IN_MAZE / 2][0] & ObjID::TONNEL ? ROWS_IN_MAZE / 2 :
			map[ROWS_IN_MAZE / 2 - 1][0] & ObjID::TONNEL ? ROWS_IN_MAZE / 2 - 1 :
			map[ROWS_IN_MAZE / 2 + 1][0] & ObjID::TONNEL ? ROWS_IN_MAZE / 2 + 1 : 0;
		map[1][1] = ObjID::PATH | ObjID::SUPER_COIN;
		map[1][mazeSize::ROWS_IN_MAZE - 1] = ObjID::PATH | ObjID::SUPER_COIN;
		map[mazeSize::COLUMS_IN_MAZE - 1][1] = ObjID::PATH | ObjID::SUPER_COIN;
		map[mazeSize::COLUMS_IN_MAZE - 1][mazeSize::ROWS_IN_MAZE - 1] = ObjID::PATH | ObjID::SUPER_COIN;
		cherryTime = -1;
		cherryCoord = { -1,-1 };
		isCherryTime = false;
		
		setGameState(PLAYING);
		
		break;
	}
	case WON:
		level++;
	case PLAYING: {
		
		int tonelI = map[ROWS_IN_MAZE / 2][0] & ObjID::TONNEL ? ROWS_IN_MAZE / 2 :
			map[ROWS_IN_MAZE / 2 - 1][0] & ObjID::TONNEL ? ROWS_IN_MAZE / 2 - 1 :
			map[ROWS_IN_MAZE / 2 + 1][0] & ObjID::TONNEL ? ROWS_IN_MAZE / 2 + 1 : 0;
		
		player.isInGame = true;
		player.setCurrentTile(Coords{ 0,tonelI });
		player.setOffset({ 0,0 });
		player.setDirection(directions::STILL);

		for (int i = 0; i < 4; i++)
		{
			enemies[i]->timeConstant[EnemyStateEnum::CHASE] *= 1+EnemyTime::COEFFICIENT;
			enemies[i]->timeConstant[EnemyStateEnum::SCATTER] *= 1 - EnemyTime::COEFFICIENT;
			enemies[i]->timeConstant[EnemyStateEnum::FRIGHTENED] *= 1 - EnemyTime::COEFFICIENT;
			enemies[i]->timeConstant[EnemyStateEnum::DEAD] *= 1 - EnemyTime::COEFFICIENT;
			enemies[i]->timeConstant[EnemyStateEnum::WAIT_TO_GO] *= 1 - EnemyTime::COEFFICIENT;
			enemies[i]->changeState(EnemyStateEnum::WAIT_TO_GO);
			enemies[i]->setAppeareIn(Coords{ mazeSize::COLUMS_IN_MAZE,tonelI });
			enemies[i]->setSpeed(enemies[i]->getSpeed()*(1+EnemyTime::SPEED_COEF));
		}
		break;
	}
	case DEAD_PLAYER: {
		
		player.DecreaseLives();
		if (player.getLivesCount()>0) {
			setGameState(GameState::PLAYING);
		}
		else
		{
			setGameState(GameState::WAIT_START);
		}
	}
	break;
	default:
		break;
	}
}


void GameContext::movePlayer() {
	Coords nextT = player.getCurrentTile() + player.getDirection();
	nextT = (nextT + 29) % 29;
	if (map[nextT.y][nextT.x] & PATH) {
		auto offset = player.getOffset();
		auto dir = player.getDirection();
		offset = offset + dir * player.getSpeed();
		if (abs(offset.x) >= 100 || abs(offset.y) >= 100) {
			offset = offset % 100;
			player.setOffset(offset);


			player.setCurrentTile(nextT);
			auto nnt = nextT + direction;
			nnt = (nnt + 29) % 29;
			if (map[nnt.y][nnt.x] & PATH) {
				player.setDirection(direction);
			}
			if (map[nextT.y][nextT.x] & COIN) {
				map[nextT.y][nextT.x] ^= COIN;
				player.increaseCoinCount(COIN_POINT);
				coinCount--;
			}
			else
			{
				if (map[nextT.y][nextT.x] & SUPER_COIN) {
					map[nextT.y][nextT.x] ^= SUPER_COIN;
					player.increaseCoinCount(SUPER_COIN_POINT);
					superCoinCount--;
					red.isFritned = true && !red.isDead && red.isInGame;
					blue.isFritned = true && !blue.isDead && blue.isInGame;
					pink.isFritned = true && !pink.isDead && pink.isInGame;
					orange.isFritned = true && !orange.isDead && orange.isInGame;
				}
				else
				{
					if (isCherryTime && map[nextT.y][nextT.x] & CHERRY)
					{
						map[nextT.y][nextT.x] ^= CHERRY;
						player.increaseCoinCount(CHERRY_POINT);
						isCherryTime = false;
					}
				}
			}
		}
		else
		{
			if (dir.x == 0) {
				player.setOffset({ 0,offset.y });
			}
			else
			{
				player.setOffset({ offset.x,0 });
			}

		}
	}
	else
	{
		player.setDirection(directions::STILL);
	}
}

void GameContext::calculateGameStatus()
{
	Coords playerCoord = player.getCurrentTile();

	for (int i = 0; i < 4; i++)
	{
		if (playerCoord == enemies[i]->getCurrentTile() && enemies[i]->isInGame) {
			if (enemies[i]->isFritned && !enemies[i]->isDead) {
				enemies[i]->isDead = true;
				enemies[i]->decreaseTime();
				player.increaseCoinCount(GHOST_POINT);
			}
			else
			{
				setGameState(GameState::DEAD_PLAYER);
			}
		}
	}
	if (!coinCount && !superCoinCount) {
		setGameState(GameState::WON);
	}
}

void GameContext::moveEnemy(Enemy& enemy, Coords dirrectedTile)
{
	enemy.decreaseTime();
	EnemyStateEnum st = enemy.getState();

	if (st == WAIT_TO_GO || st == DEAD) {
		return;
	}

	if (enemy.waitDirection) {
		Coords nextTile;
		Coords currentDir = enemy.getDirection();
		std::vector<Coords> possDir = { {currentDir.y,currentDir.x},currentDir,{-currentDir.y,-currentDir.x} };
		enemy.waitDirection = false;
		switch (st)
		{
		case CHASE:
		{
			int minL = INT_MAX, m_i = -1;
			for (size_t i = 0; i < 3; i++)
			{
				nextTile = enemy.getCurrentTile() + possDir[i];
				nextTile = (nextTile + 29) % 29;
				
				if (map[nextTile.y][nextTile.x] & PATH) {
					int m = sqrt(pow(dirrectedTile.y - nextTile.y, 2) + pow((dirrectedTile.x - nextTile.x), 2));
					if (minL > m) {
						m_i = i;
						minL = m;
					}
				}
			}
			enemy.setDirection(possDir[m_i]);
		}
		break;
		case SCATTER: {
			int minL = INT_MAX, m_i = -1;
			for (size_t i = 0; i < 3; i++)
			{
				nextTile = enemy.getCurrentTile() + possDir[i];
				nextTile = (nextTile + 29) % 29;
				if (map[nextTile.y][nextTile.x] & PATH) {
					int m = sqrt(pow(enemy.homeCoord.y - nextTile.y, 2) + pow(enemy.homeCoord.x - nextTile.x, 2));
					if (minL > m) {
						m_i = i;
						minL = m;
					}
				}
			}
			enemy.setDirection(possDir[m_i]);
		}
					break;
		case FRIGHTENED: {
			int i = 0;
			do {
				i = rand() % 3;
				nextTile = enemy.getCurrentTile() + possDir[i];
				nextTile = (nextTile + 29) % 29;
			} while (!(map[nextTile.y][nextTile.x] & PATH));
			enemy.setDirection(possDir[i]);
		}
					   break;

		}
	}
	else
	{
		Coords nextT = enemy.getCurrentTile() + enemy.getDirection();

		nextT = (nextT + 29) % 29;
		auto offset = enemy.getOffset();
		auto dir = enemy.getDirection();
		offset = offset + dir * enemy.getSpeed();
		if (abs(offset.x) >= 100 || abs(offset.y) >= 100) {
			offset = offset % 100;
			enemy.setOffset(offset);
			enemy.setCurrentTile(nextT);
			enemy.waitDirection = true;
		}
		else
		{
			enemy.setOffset(offset);
		}
	}
}

void GameContext::moveRed()
{
	moveEnemy(red, player.getCurrentTile());
}

void GameContext::movePink()
{
	Coords tile = player.getCurrentTile() + player.getDirection() * 4;
	moveEnemy(pink, tile);
}

void GameContext::moveBlue()
{
	Coords tile = player.getCurrentTile() + player.getDirection() * 2;
	Coords tileR = red.getCurrentTile();
	tile = { tile.x * 2 - tileR.x,tile.y * 2 - tileR.y };
	moveEnemy(blue, tile);
}

void GameContext::moveOrange()
{
	Coords tile = player.getCurrentTile();
	Coords tileR = orange.getCurrentTile();
	int m = sqrt(pow(tile.y - tileR.y, 2) + pow(tile.x - tileR.x, 2));
	if (m < 8) {
		tile = orange.homeCoord;
	}
	moveEnemy(orange, tile);
}

void GameContext::reCalculate()
{
	if (state != GameState::PLAYING) {
		return;
	}
	movePlayer();
	moveRed();
	moveBlue();
	movePink();
	moveOrange();

	calculateGameStatus();

	if (coinCount % 100 == 0 && !isCherryTime){
		isCherryTime = true;
		createCherry();
	}
	if (cherryTime == 0) {
		map[cherryCoord.y][cherryCoord.x] ^= CHERRY;
		isCherryTime = false;
	}
	cherryTime--;
}

void GameContext::setPlayerDirection(Coords dir)
{
	Coords oldCoord = player.getDirection(); 
	direction = dir;
	if (oldCoord==directions::STILL) {
		player.setDirection(dir);
	}
	else if(oldCoord.x==dir.x || oldCoord.y == dir.y)
	{
		player.setDirection(dir);
	}
	
}

void GameContext::startNewGame(maze::MazeTypeEnum diff, long seed)
{
	this->seed = seed;
	this->diff = diff;
	setGameState(START_PLAYING);
}
