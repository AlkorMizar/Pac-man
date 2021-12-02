#pragma once

#include <windows.h>
#include "GameContext.h"
#include "Constant.h"
#include "Entity.h"

class Sprite
{
public:
	Sprite(HDC _hdc, int _width, int _heigth) {
		hdc = _hdc;
		width = _width;
		height = _heigth;
	}
	Sprite() {
		hdc = 0;
		width = 0;
		height = 0;
	}
	~Sprite() {
		DeleteDC(hdc);
	}
	void set(HDC _hdc, int _width, int _heigth) {
		hdc = _hdc;
		width = _width;
		height = _heigth;
	}
	HDC hdc=0;
	int height=0;
	int width=0;
private:

};


class FrameRender
{
public:
	FrameRender(HWND hWnd, HINSTANCE _hInstance, GameContext& _currentGameContext);
	~FrameRender();
	void setCurrentContext(GameContext& _currentGameContext) { currentGameContext = _currentGameContext; }
	bool renderNextFrame();
	void renderButton(HDC hdc);
	void renderText();
	void reloadMap() { 
		DeleteObject(map.hdc);
		createMap(); }
	Sprite mapTraced, map, player, coin, superCoin, cherry, blue, red, pink, orange, scatter;

private:
	void renderPlayer();
	void renderEnemies();
	void renderEnemy(Entity& entity,Sprite& sp);
	void createMap();
	void rednderPlayerInfo();
	void loadBMP();
	void renderMesh();
	GameContext& currentGameContext;
	HFONT hFont=0;
	HWND hWnd=0;
	HINSTANCE hInstance=0;
	int i = 0;
	Coords beforDirectionOfPlayer=directions::RIGHT;
};

