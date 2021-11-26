#include "Player.h"

Player::Player()
{
	coinsCount = 0;
	livesCount = 3;
}

Player::~Player()
{
}

int Player::getCoinCount()
{
	return 0;
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

void Player::setCoinCount(int)
{
}

void Player::setCurrentTile(Coords)
{
}
