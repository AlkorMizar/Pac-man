#pragma once
#define _CRT_SECURE_NO_WARNINGS

#define WM_SYSCOMMAND  

#include <windows.h>

#include "Constant.h"
#include "MazeCreator.h"
#include "GameContext.h"
#include "FrameRender.h"

class GameCore
{
public:
	GameCore(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, WNDPROC wndProc);
	GameCore();
	~GameCore();
	int play();
	LRESULT Process(HWND, UINT, WPARAM, LPARAM);

private:
	const int NEW_START = 1;
	const int ID_MAIN_TIMER = 2;
	void startNewGame();
	GameContext currentGameContext;
	HWND hWnd;
	WNDCLASS wc;
	HINSTANCE hInstance;
	HWND btnStartNewGame;
	FrameRender *frameRender;
};