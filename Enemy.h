#pragma once
#include "Coords.h"
#include "Constant.h"
#include "Entity.h"
#include <vector>
#include <limits>

class Enemy :public Entity
{
public:
	Enemy() {}
	Enemy(std::vector<double>) {};
	Enemy(std::vector<double>time, Coords _homeCoords) {
		speed = 13;
		offset = { 0,0 };
		directedTile = homeCoord = _homeCoords;
		timeConstant = time;
	}
	void setCurrentTile(Coords newTile) {
		currentTile = newTile;
	}
	
	void setAppeareIn(Coords tile) { appearIn = tile; }

	bool isFritned=false;
	bool isDead = false;
	bool waitDirection=true;

	void changeState(EnemyStateEnum state)
	{
		this->state = state;
		switch (state)
		{
		case WAIT_TO_GO:
			isInGame = false;
			isDead = false;
			currentTile = appearIn;
			isFritned = false;
			offset = { 0,0 };
			break;
		case SCATTER:
		case CHASE:
			isInGame = true;
			isDead = false;
			isFritned = false;
			break;
		case DEAD:
			isInGame = false;
			isDead = true;
			isFritned = false;
			currentTile = appearIn;
			offset = { 0,0 };
			break;
		case FRIGHTENED:
			isFritned = true;
			isInGame = true;
			isDead = false;
			break;
		default:
			break;
		}
		stageLifeTime = timeConstant[state];
	}

	void decreaseTime()
	{
		if (isDead && state != EnemyStateEnum::DEAD) {
			changeState(EnemyStateEnum::DEAD);
			currentTile = appearIn;
			isFritned = false;
			isInGame = false;
		}
		if (isFritned && state != EnemyStateEnum::FRIGHTENED) {
			direction = -direction;
			offset = { 0,0 };
			waitDirection = true;
			changeState(EnemyStateEnum::FRIGHTENED);
		}
		stageLifeTime--;
		if (stageLifeTime<0) {
			
			switch (state)
			{
			case WAIT_TO_GO:
				isInGame = true; 
				currentTile = appearIn;
				offset = { 0,0 };
				direction = directions::LEFT;
			case CHASE:
				directedTile = homeCoord;
				changeState(EnemyStateEnum::SCATTER);
				break;
			case DEAD:
				isDead = false;
				isInGame = true;
				currentTile = appearIn;
				offset = { 0,0 };
			case SCATTER:
			case FRIGHTENED:
				isFritned = false;
				changeState(EnemyStateEnum::CHASE);
				break;
			default:
				break;
			}
		}
	}
	EnemyStateEnum getState() {
		return state;
	}

	Coords homeCoord = { 0,0 };
	std::vector<double> timeConstant;
protected:
	long stageLifeTime=LONG_MAX;
	Coords directedTile;
	Coords appearIn;
	EnemyStateEnum state=EnemyStateEnum::WAIT_TO_GO;

};
