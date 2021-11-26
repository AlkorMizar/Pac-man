#define _CRT_SECURE_NO_WARNINGS  

#include <windows.h>
#include "GameCore.h"

GameCore game;

LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam);
////////////////////////////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    game=GameCore(hInstance, hPrevInstance, lpCmdLine, nCmdShow, WndProc);
    return game.play();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
    return game.Process(hWnd, messg, wParam, lParam);
}