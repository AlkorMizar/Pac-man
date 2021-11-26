#pragma once

#include <windows.h>

class FrameRender
{
public:
	FrameRender(HWND hWnd);
	~FrameRender();
	
private:
	HDC menu, map, player, coin, bigCoin, cherry;
};