#include "FrameRender.h"
#include <vector>
#include <map>
#include <string>

#pragma comment(lib, "Msimg32.lib")


void FrameRender::createMap()
{

}

void FrameRender::rednderPlayerInfo()
{
    RECT rect = elementSize::COIN_RECT;
    HDC mainDC = GetDC(hWnd);
    HFONT hOldFont = (HFONT)SelectObject(mainDC, hFont);
    SetTextColor(mainDC, frameContext::BLUE_COLOR);
    SetBkColor(mainDC, frameContext::BLACK_COLOR);

    std::wstring text = std::to_wstring(currentGameContext.player.getCoinCount());

    rect = elementSize::COIN_COUNT_RECT;
    DrawText(mainDC,text.c_str(), -1, &rect,
        DT_SINGLELINE
    );

    text = std::to_wstring(currentGameContext.player.getLivesCount());

    rect = elementSize::LIVES_COUNT_RECT;
    DrawText(mainDC, text.c_str(), -1, &rect,
        DT_SINGLELINE
    );

    ReleaseDC(hWnd, mainDC);
}

void FrameRender::renderObjects()
{
}

void FrameRender::renderButton(HDC hdc)
{
    RECT Rect;
    SetTextColor(hdc, frameContext::BLUE_COLOR);
    SetBkColor(hdc, frameContext::BLACK_COLOR);
    HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
    

    Rect.top = 0;
    Rect.bottom = elementSize::BUTTON_HEIGHT;
    Rect.left = 0;
    Rect.right = elementSize::BUTTON_WIDTH;

    HDC hCmpDC = CreateCompatibleDC(hdc);
    HBITMAP hBmp = CreateCompatibleBitmap(hdc, elementSize::BUTTON_WIDTH, elementSize::BUTTON_HEIGHT);
    SelectObject(hCmpDC, hBmp);

    // Закраска фоновым цветом
    LOGBRUSH br;
    br.lbStyle = BS_SOLID;
    br.lbColor = frameContext::BLUE_COLOR;
    HBRUSH brush;
    brush = CreateBrushIndirect(&br);
    FillRect(hCmpDC, &Rect, brush);
    DeleteObject(brush);
    br.lbStyle = BS_SOLID;
    br.lbColor = frameContext::BLACK_COLOR;
    brush = CreateBrushIndirect(&br);
    Rect.top = 3;
    Rect.bottom = elementSize::BUTTON_HEIGHT-3;
    Rect.left = 3;
    Rect.right = elementSize::BUTTON_WIDTH-3;
    FillRect(hCmpDC, &Rect, brush);
    DeleteObject(brush);

    Rect.top = 0;
    Rect.bottom = elementSize::BUTTON_HEIGHT;
    Rect.left = 0;
    Rect.right = elementSize::BUTTON_WIDTH;

    SetStretchBltMode(hdc, COLORONCOLOR);
    BitBlt(hdc, 0, 0, elementSize::BUTTON_WIDTH, elementSize::BUTTON_HEIGHT,
        hCmpDC, 0, 0, SRCCOPY);
    DeleteDC(hCmpDC);
    DeleteObject(hBmp);
    DrawText(hdc, L"Start new game", -1, &Rect,
        DT_SINGLELINE | DT_CENTER | DT_VCENTER
    );
}

void FrameRender::renderText()
{

    RECT rect = elementSize::COIN_RECT;
    HDC mainDC = GetDC(hWnd);
    HFONT hOldFont = (HFONT)SelectObject(mainDC, hFont);
    SetTextColor(mainDC, frameContext::BLUE_COLOR);
    SetBkColor(mainDC, frameContext::BLACK_COLOR);
    DrawText(mainDC, L"COINS", -1, &rect,
        DT_SINGLELINE 
    );

    rect = elementSize::LIVES_RECT;
    DrawText(mainDC, L"LIVES", -1, &rect,
        DT_SINGLELINE 
    );
    ReleaseDC(hWnd, mainDC);
}

void FrameRender::loadBMP() {
    
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

    ReleaseDC(hWnd, mainDC);
}

FrameRender::FrameRender(HWND _hWnd, HINSTANCE _hInstance,GameContext& _currentGameContext)
    :currentGameContext(_currentGameContext)
{
    hWnd = _hWnd;
    hInstance = _hInstance;
    hFont = CreateFont(33, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Stencil");
    loadBMP();
    createMap();

    renderText();
    rednderPlayerInfo();
}

FrameRender::~FrameRender()
{
}

bool FrameRender::renderNextFrame()
{
    return false;
}
