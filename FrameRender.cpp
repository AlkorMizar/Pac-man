#include "FrameRender.h"
#include <vector>
#include <map>
#include <string>

#pragma comment(lib, "Msimg32.lib")
void FrameRender::createMenu() {

}

void FrameRender::loadBMP(HWND hWnd, HINSTANCE hInstance) {
    HDC mainDC = GetDC(hWnd);
    std::map<std::wstring, Sprite&> objDC{ {L"coin.bmp",coin},{L"superCoin.bmp",superCoin} ,{L"cherry.bmp",cherry} ,
                                        {L"player.bmp",player},{L"scatter.bmp",scatter},
                                        {L"red.bmp",red} ,{L"pinky.bmp",pink} ,{L"orange.bmp",orange} ,{L"blue.bmp",blue} };

    for (auto& kv : objDC) {
        HBITMAP hBmp = (HBITMAP)LoadImage(hInstance, kv.first.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        if (hBmp != NULL) {
            BITMAP bm;
            GetObject(hBmp, sizeof(bm), &bm);
            kv.second.set(CreateCompatibleDC(mainDC), bm.bmWidth, bm.bmHeight);
            SelectObject(kv.second.hdc, hBmp);
            DeleteObject(hBmp);
        }
    }
}

FrameRender::FrameRender(HWND hWnd, HINSTANCE hInstance,GameContext& _currentGameContext)
    :currentGameContext(_currentGameContext)
{
    loadBMP(hWnd, hInstance);
    createMenu();
}

FrameRender::~FrameRender()
{
}
