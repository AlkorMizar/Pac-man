#include "Player.h"

Player::Player()
{
	coinsCount = 0;
	livesCount = 3;
	speed =14;// 10% per frame
	currentTile=Coords{ 0,0 };
	offset = {0,0};
	isInGame = false;
	direction = directions::STILL;
}

Player::~Player()
{
}

int Player::getCoinCount()
{
	return coinsCount;
}

int Player::getLivesCount()
{
	return livesCount;
}

void Player::setLivesCount(int val)
{
	livesCount = val;
}

void Player::DecreaseLives()
{
	livesCount--;
}

void Player::setCoinCount(int val)
{
	coinsCount = val;
}

void Player::setCurrentTile(Coords tile)
{
	currentTile = tile;
}

void Player::setDirection(Coords dir) {
	direction = dir;
}

void Player::setOffset(Coords n) {
	offset = n;
}

