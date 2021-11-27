#include "FrameRender.h"
#include <vector>
#include <map>
#include <string>

#pragma comment(lib, "Msimg32.lib")

using namespace std;
using namespace frameContext;

void FrameRender::createMap()
{
    HDC mainDC = GetDC(hWnd);

    map.hdc = CreateCompatibleDC(mainDC);
    map.width = frameContext::BORDER_RIGHT - frameContext::BORDER_LEFT;
    map.height = frameContext::BORDER_BOTTOM - frameContext::BORDER_TOP;
    HBITMAP hBmp = CreateCompatibleBitmap(mainDC, map.width, map.height);
    SelectObject(map.hdc, hBmp);

    LOGBRUSH br;
    br.lbStyle = BS_SOLID;
    br.lbColor = 0x0;
    HBRUSH brush;
    brush = CreateBrushIndirect(&br);
    RECT Rect = { 0 ,0,map.width, map.height };
    FillRect(map.hdc, &Rect, brush);
    DeleteObject(brush);

    HPEN  pen = CreatePen(PS_SOLID, 3, frameContext::BLUE_COLOR);
    SelectObject(map.hdc, pen);
    for (size_t i = 1; i < mazeSize::ROWS_IN_MAZE; i++)
    {
        for (size_t j = 1; j < mazeSize::COLUMS_IN_MAZE; j++)
        {
            if ((currentGameContext.map[i][j] & ObjID::PATH) == ObjID::PATH) {
                if (currentGameContext.map[i - 1][j] == ObjID::WALL) {
                    int x1 = j * frameContext::TILE_SIZE + frameContext::TILE_DELTA;
                    int x2 = x1 + frameContext::TILE_DELTA;

                    int y1 = i * frameContext::TILE_SIZE - frameContext::TILE_DELTA;
                    int y2 = y1;
                    x1 += currentGameContext.map[i - 1][j - 1] == ObjID::WALL ? -frameContext::TILE_DELTA * 2 : 0;
                    x2 += currentGameContext.map[i - 1][j + 1] == ObjID::WALL ? +frameContext::TILE_DELTA * 2 : 0;
                    MoveToEx(map.hdc, x1, y1, NULL);
                    LineTo(map.hdc, x2, y2);
                }

                if (currentGameContext.map[i + 1][j] == ObjID::WALL) {
                    int x1 = j * frameContext::TILE_SIZE + frameContext::TILE_DELTA;
                    int x2 = x1 + frameContext::TILE_DELTA;

                    int y1 = (i + 1) * frameContext::TILE_SIZE + frameContext::TILE_DELTA;
                    int y2 = y1;
                    x1 += currentGameContext.map[i + 1][j - 1] == ObjID::WALL ? -frameContext::TILE_DELTA * 2 : 0;
                    x2 += currentGameContext.map[i + 1][j + 1] == ObjID::WALL ? +frameContext::TILE_DELTA * 2 : 0;
                    MoveToEx(map.hdc, x1, y1, NULL);
                    LineTo(map.hdc, x2, y2);
                }

                if (currentGameContext.map[i][j - 1] == ObjID::WALL) {
                    int x1 = j * frameContext::TILE_SIZE - frameContext::TILE_DELTA;
                    int x2 = x1;

                    int y1 = i * frameContext::TILE_SIZE + frameContext::TILE_DELTA;
                    int y2 = y1 + frameContext::TILE_DELTA;
                    y1 += currentGameContext.map[i - 1][j - 1] == ObjID::WALL ? -frameContext::TILE_DELTA * 2 : 0;
                    y2 += currentGameContext.map[i + 1][j - 1] == ObjID::WALL ? +frameContext::TILE_DELTA * 2 : 0;
                    MoveToEx(map.hdc, x1, y1, NULL);
                    LineTo(map.hdc, x2, y2);
                }

                if (currentGameContext.map[i][j + 1] == ObjID::WALL) {
                    int x1 = (j + 1) * frameContext::TILE_SIZE + frameContext::TILE_DELTA;
                    int x2 = x1;

                    int y1 = i * frameContext::TILE_SIZE + frameContext::TILE_DELTA;
                    int y2 = y1 + frameContext::TILE_DELTA;
                    y1 += currentGameContext.map[i - 1][j + 1] == ObjID::WALL ? -frameContext::TILE_DELTA * 2 : 0;
                    y2 += currentGameContext.map[i + 1][j + 1] == ObjID::WALL ? +frameContext::TILE_DELTA * 2 : 0;
                    MoveToEx(map.hdc, x1, y1, NULL);
                    LineTo(map.hdc, x2, y2);
                }
            }
        }
    }

    DeleteObject(pen);
    ReleaseDC(hWnd, mainDC);
}

void FrameRender::rednderPlayerInfo()
{
    RECT rect = elementSize::COIN_RECT;
    HDC mainDC = GetDC(hWnd);
    HFONT hOldFont = (HFONT)SelectObject(mainDC, hFont);
    SetTextColor(mainDC, BLUE_COLOR);
    SetBkColor(mainDC, BLACK_COLOR);

    std::wstring text = std::to_wstring(currentGameContext.player.getCoinCount());

    rect = elementSize::COIN_COUNT_RECT;

    LOGBRUSH br;
    br.lbStyle = BS_SOLID;
    br.lbColor = BLACK_COLOR;
    HBRUSH brush;
    brush = CreateBrushIndirect(&br);
    FillRect(mainDC, &rect, brush);
    
    DrawText(mainDC,text.c_str(), -1, &rect,
        DT_SINGLELINE
    );


    text = std::to_wstring(currentGameContext.player.getLivesCount());

    rect = elementSize::LIVES_COUNT_RECT;
    FillRect(mainDC, &rect, brush);
    DrawText(mainDC, text.c_str(), -1, &rect,
        DT_SINGLELINE
    );
    DeleteObject(brush);
    ReleaseDC(hWnd, mainDC);
}

void FrameRender::renderObjects()
{
}

void FrameRender::renderButton(HDC hdc)
{
    RECT Rect;
    SetTextColor(hdc, BLUE_COLOR);
    SetBkColor(hdc, BLACK_COLOR);
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
    br.lbColor = BLUE_COLOR;
    HBRUSH brush;
    brush = CreateBrushIndirect(&br);
    FillRect(hCmpDC, &Rect, brush);
    DeleteObject(brush);
    br.lbStyle = BS_SOLID;
    br.lbColor = BLACK_COLOR;
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
    SetTextColor(mainDC, BLUE_COLOR);
    SetBkColor(mainDC, BLACK_COLOR);
    DrawText(mainDC, L"COINS", -1, &rect,
        DT_SINGLELINE 
    );

    rect = elementSize::LIVES_RECT;
    DrawText(mainDC, L"LIVES", -1, &rect,
        DT_SINGLELINE 
    );
    ReleaseDC(hWnd, mainDC);
    rednderPlayerInfo();
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
    renderText();
}

FrameRender::FrameRender(HWND _hWnd, HINSTANCE _hInstance,GameContext& _currentGameContext)
    :currentGameContext(_currentGameContext)
{
    hWnd = _hWnd;
    hInstance = _hInstance;
    hFont = CreateFont(33, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Stencil");
    loadBMP();
    createMap();
}

FrameRender::~FrameRender()
{
}

bool FrameRender::renderNextFrame()
{
    HDC mainDC = GetDC(hWnd);
    mapTraced.hdc = CreateCompatibleDC(map.hdc);;
    mapTraced.width = map.width = frameContext::BORDER_RIGHT - frameContext::BORDER_LEFT;
    mapTraced.height = map.height = frameContext::BORDER_BOTTOM - frameContext::BORDER_TOP;
    HBITMAP hBmp = CreateCompatibleBitmap(mainDC, map.width, map.height);
    SelectObject(mapTraced.hdc, hBmp);
    BitBlt(mapTraced.hdc, 0, 0, map.width, map.height,
        map.hdc, 0, 0, SRCCOPY);
    for (size_t i = 1; i < mazeSize::ROWS_IN_MAZE; i++)
    {
        for (size_t j = 1; j < mazeSize::COLUMS_IN_MAZE; j++)
        {
            if ((currentGameContext.map[i][j] & ObjID::PATH) == ObjID::PATH) {
                Sprite& sp = coin;
                if ((currentGameContext.map[i][j] & ObjID::COIN) == ObjID::COIN) {
                    int x = j * frameContext::TILE_SIZE + frameContext::TILE_CENTER - sp.width / 2;
                    int y = i * frameContext::TILE_SIZE + frameContext::TILE_CENTER - sp.height / 2;
                    BitBlt(mapTraced.hdc, x, y, sp.width, sp.height,
                        sp.hdc, 0, 0, SRCCOPY);
                }
                Sprite& sp1 = superCoin;
                if ((currentGameContext.map[i][j] & ObjID::SUPER_COIN) == ObjID::SUPER_COIN) {
                    int x = j * frameContext::TILE_SIZE + frameContext::TILE_CENTER - sp1.width / 2;
                    int y = i * frameContext::TILE_SIZE + frameContext::TILE_CENTER - sp1.height / 2;
                    BitBlt(mapTraced.hdc, x, y, sp1.width, sp1.height,
                        sp1.hdc, 0, 0, SRCCOPY);
                }
            }
        }
    }


    
    BitBlt(mainDC, frameContext::BORDER_LEFT, 0, map.width, map.height,
        mapTraced.hdc, 0, 0, SRCCOPY);
    return true;
}
