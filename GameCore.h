#pragma once
#define _CRT_SECURE_NO_WARNINGS

#define WM_SYSCOMMAND  

#include <windows.h>

#include "Player.h"
#include "RedGhost.h"
#include "BlueGhost.h"
#include "PinkGhost.h"
#include "OrangeGhost.h"
#include "Constant.h"
#include "MazeCreator.h"

class GameCore
{
public:
	GameCore(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, WNDPROC wndProc);
	GameCore();
	~GameCore();
	int play();
	LRESULT Process(HWND, UINT, WPARAM, LPARAM);
private:
	HWND hWnd;
	WNDCLASS wc;
	HINSTANCE hInstance;

	Player player;
	RedGhost red;
	PinkGhost pink;
	BlueGhost blue;
	OrangeGhost orange;
};