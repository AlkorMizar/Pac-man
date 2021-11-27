#pragma once

#include <windows.h>
#include "GameContext.h"

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
	
	Sprite menu, map, player, coin, superCoin, cherry, blue, red, pink, orange, scatter;

private:
	const int TILE_SIZE = 27,
		TILE_CENTER = 27 / 2 + 1,
		BORDER_LEFT = 300,
		MAZE_BORDER_FIRST_COORD = 9,
		MAZE_BORDER_LEFT_COORD = 17;

	void createMenu();
	void loadBMP(HWND hWnd, HINSTANCE hInstance);
	GameContext& currentGameContext;
};

