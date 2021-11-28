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
	HDC hdc;
	int height;
	int width;
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
	void renderText(HDC mainDC);
	void reloadMap() { createMap(); }
	Sprite mapTraced, map, player, coin, superCoin, cherry, blue, red, pink, orange, scatter;

private:
	void renderPlayer();
	void renderEnemies();
	void renderEnemy(Entity& entity,Sprite sp);
	void createMap();
	void rednderPlayerInfo();
	void renderObjects();
	void loadBMP();
	void renderMesh();
	//void drawLine(int i, int j, bool isVertical, int side);
	GameContext& currentGameContext;
	HFONT hFont;
	HWND hWnd;
	HINSTANCE hInstance;
};

