#pragma once
#define _CRT_SECURE_NO_WARNINGS

#define WM_SYSCOMMAND  

#include <windows.h>
#include <string>

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
	const int ID_COMBOBOX = 3;
	const int ID_TEXTBOX = 4;
	void startNewGame();
	GameContext currentGameContext;
	HWND hWnd=0;
	WNDCLASS wc;
	HINSTANCE hInstance=0;
	HWND btnStartNewGame,dificaltyChooser,seedWriter;
	FrameRender *frameRender=0;
	maze::MazeTypeEnum currDif=maze::MazeTypeEnum::NORMAL;
	std::wstring diffText;
};