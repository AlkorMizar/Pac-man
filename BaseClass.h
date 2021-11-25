#pragma once
class Entity
{
public:
	Entity();
	~Entity();
	int getId();
	double getSpeed();
	void getImg();

private:
	int id;
	double speed;
};