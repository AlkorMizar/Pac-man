#include "FrameRender.h"
#include <vector>
#include <map>
#include <string>

#pragma comment(lib, "Msimg32.lib")

using namespace std;
using namespace frameContext;


void FrameRender::renderMesh()
{
    HPEN  pen = CreatePen(PS_SOLID, 1, RGB(50,50,50));
    
    SelectObject(map.hdc, pen);
    for (size_t i = 1; i < mazeSize::ROWS_IN_MAZE+1; i++)
    {
        MoveToEx(map.hdc,TILE_SIZE, i*TILE_SIZE, NULL);
        LineTo(map.hdc, mazeSize::ROWS_IN_MAZE*TILE_SIZE, i * TILE_SIZE);
        MoveToEx(map.hdc, i * TILE_SIZE, TILE_SIZE, NULL);
        LineTo(map.hdc, i * TILE_SIZE, mazeSize::ROWS_IN_MAZE * TILE_SIZE);
    }

    DeleteObject(pen);
}

void FrameRender::createMap()
{
    HDC mainDC = GetDC(hWnd);

    map.hdc = CreateCompatibleDC(mainDC);
    mapTraced.width=map.width = frameContext::BORDER_RIGHT - frameContext::BORDER_LEFT;
    mapTraced.height=map.height = frameContext::BORDER_BOTTOM - frameContext::BORDER_TOP;
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
                    int x1 = j * frameContext::TILE_SIZE + frameContext::TILE_BORDER;
                    int x2 = x1 + frameContext::TILE_CENTER_L;

                    int y1 = i * frameContext::TILE_SIZE - frameContext::TILE_BORDER;
                    int y2 = y1;
                    x1 += currentGameContext.map[i - 1][j - 1] == ObjID::WALL ? -frameContext::TILE_BORDER * 2 : 0;
                    x2 += currentGameContext.map[i - 1][j + 1] == ObjID::WALL ? +frameContext::TILE_BORDER * 2 : 0;
                    MoveToEx(map.hdc, x1, y1, NULL);
                    LineTo(map.hdc, x2, y2);
                }

                if (currentGameContext.map[i + 1][j] == ObjID::WALL) {
                    int x1 = j * frameContext::TILE_SIZE + frameContext::TILE_BORDER;
                    int x2 = x1 + frameContext::TILE_CENTER_L;

                    int y1 = (i + 1) * frameContext::TILE_SIZE + frameContext::TILE_BORDER;
                    int y2 = y1;
                    x1 += currentGameContext.map[i + 1][j - 1] == ObjID::WALL ? -frameContext::TILE_BORDER * 2 : 0;
                    x2 += currentGameContext.map[i + 1][j + 1] == ObjID::WALL ? +frameContext::TILE_BORDER * 2 : 0;
                    MoveToEx(map.hdc, x1, y1, NULL);
                    LineTo(map.hdc, x2, y2);
                }

                if (currentGameContext.map[i][j - 1] == ObjID::WALL) {
                    int x1 = j * frameContext::TILE_SIZE - frameContext::TILE_BORDER;
                    int x2 = x1;

                    int y1 = i * frameContext::TILE_SIZE + frameContext::TILE_BORDER;
                    int y2 = y1 + frameContext::TILE_CENTER_L;
                    y1 += currentGameContext.map[i - 1][j - 1] == ObjID::WALL ? -frameContext::TILE_BORDER * 2 : 0;
                    y2 += currentGameContext.map[i + 1][j - 1] == ObjID::WALL ? +frameContext::TILE_BORDER * 2 : 0;
                    MoveToEx(map.hdc, x1, y1, NULL);
                    LineTo(map.hdc, x2, y2);
                }

                if (currentGameContext.map[i][j + 1] == ObjID::WALL) {
                    int x1 = (j + 1) * frameContext::TILE_SIZE + frameContext::TILE_BORDER;
                    int x2 = x1;

                    int y1 = i * frameContext::TILE_SIZE + frameContext::TILE_BORDER;
                    int y2 = y1 + frameContext::TILE_CENTER_L;
                    y1 += currentGameContext.map[i - 1][j + 1] == ObjID::WALL ? -frameContext::TILE_BORDER * 2 : 0;
                    y2 += currentGameContext.map[i + 1][j + 1] == ObjID::WALL ? +frameContext::TILE_BORDER * 2 : 0;
                    MoveToEx(map.hdc, x1, y1, NULL);
                    LineTo(map.hdc, x2, y2);
                }
            }
        }
    }
   // renderMesh();
    
    DeleteObject(hBmp);
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

    text = std::to_wstring(currentGameContext.coinCount);

    rect = elementSize::LEVEL_COUNT_RECT;
    FillRect(mainDC, &rect, brush);
    DrawText(mainDC, text.c_str(), -1, &rect,
        DT_SINGLELINE
    );

    DeleteObject(brush);
    
    ReleaseDC(hWnd, mainDC);
}


void FrameRender::renderButton(HDC hdc)
{
    RECT Rect;
    
    HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
    SetTextColor(hdc, BLUE_COLOR);
    SetBkColor(hdc, BLACK_COLOR);

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
    DrawText(hdc, L"Start new game", -1, &Rect,
        DT_SINGLELINE | DT_CENTER | DT_VCENTER
    );


    DeleteObject(hCmpDC);
    DeleteObject(hBmp);
    
    
}

void FrameRender::renderText()
{
    HDC mainDC = GetDC(hWnd);
    
    RECT rect = elementSize::COIN_RECT;
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

    rect = elementSize::LEVEL_TEXT_RECT;
    DrawText(mainDC, L"LEVELS", -1, &rect,
        DT_SINGLELINE
    );

    ReleaseDC(hWnd, mainDC);
}

void FrameRender::loadBMP() {
    
    HDC mainDC = GetDC(hWnd);
    
    std::map<std::wstring, Sprite&> objDC{ {L"coin.bmp",coin},{L"superCoin.bmp",superCoin} ,{L"cherry.bmp",cherry} ,
                                           {L"scatter.bmp",scatter},{L"red.bmp",red} ,{L"pinky.bmp",pink} ,
                                           {L"orange.bmp",orange} ,{L"blue.bmp",blue} };

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
}

FrameRender::~FrameRender()
{
}


void FrameRender::renderPlayer()
{
    if (currentGameContext.player.isInGame) {
        HBITMAP hBmp = (HBITMAP)LoadImage(hInstance, L"playerDOWN.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);;
        Coords dir = currentGameContext.player.getDirection();
        beforDirectionOfPlayer=dir = dir == directions::STILL ? beforDirectionOfPlayer : dir;
        if (dir == directions::DOWN) {
            hBmp = (HBITMAP)LoadImage(hInstance, L"playerDOWN.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        }
        else if(dir == directions::UP) {
            hBmp = (HBITMAP)LoadImage(hInstance, L"playerUP.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

        }
        else if (dir == directions::RIGHT) {
            hBmp = (HBITMAP)LoadImage(hInstance, L"playerRIGHT.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

        }
        else if (dir == directions::LEFT) {
            hBmp = (HBITMAP)LoadImage(hInstance, L"playerLEFT.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        }
         
        if (hBmp != NULL) {
            BITMAP bm;
            GetObject(hBmp, sizeof(bm), &bm);

            player.set(CreateCompatibleDC(mapTraced.hdc), bm.bmWidth, bm.bmHeight);
            SelectObject(player.hdc, hBmp);
            DeleteObject(hBmp);
        }
        else {
            MessageBox(NULL, TEXT("Starting new game!"), TEXT("New game"), MB_OK);
        }
        Coords tile = currentGameContext.player.getCurrentTile()*TILE_SIZE;
        Coords offset = currentGameContext.player.getOffset() * (TILE_SIZE / 100.0);
        int x1 = tile.x +offset.x + TILE_CENTER - player.width / 2,
            y1 = tile.y + offset.y + TILE_CENTER - player.height / 2;
        TransparentBlt(mapTraced.hdc, x1, y1, player.width, player.height, player.hdc, 0, 0, player.width, player.height, frameContext::BLACK_COLOR);

        DeleteObject(player.hdc);
    }
}

void FrameRender::renderEnemies(){
    renderEnemy(currentGameContext.player,player);
    renderEnemy(currentGameContext.red,
        currentGameContext.red.isFritned ? scatter : red);
    renderEnemy(currentGameContext.blue,
        currentGameContext.blue.isFritned ? scatter : blue);
    renderEnemy(currentGameContext.pink,
        currentGameContext.pink.isFritned ? scatter : pink);
    renderEnemy(currentGameContext.orange,
        currentGameContext.orange.isFritned ? scatter : orange);
}

void FrameRender::renderEnemy(Entity& entity, Sprite& sp)
{
    if (entity.isInGame) {
        Coords tile = entity.getCurrentTile() * TILE_SIZE;
        Coords offset = entity.getOffset() * (TILE_SIZE / 100.0);
        int x1 = tile.x + offset.x + TILE_CENTER - sp.width / 2,
            y1 = tile.y + offset.y + TILE_CENTER - sp.height / 2;
        TransparentBlt(mapTraced.hdc, x1, y1, sp.width, sp.height, sp.hdc, 0, 0, sp.width, sp.height, frameContext::BLACK_COLOR);
        
    }
}


bool FrameRender::renderNextFrame()
{
    HDC mainDC = GetDC(hWnd);
    
    mapTraced.hdc = CreateCompatibleDC(map.hdc);
    HBITMAP hBmp = CreateCompatibleBitmap(mainDC, map.width, map.height);
    
    SelectObject(mapTraced.hdc, hBmp);
    BitBlt(mapTraced.hdc, 0, 0, map.width, map.height,
        map.hdc, 0, 0, SRCCOPY);
    int x, y;
    for (size_t i = 1; i < mazeSize::ROWS_IN_MAZE; i++)
    {
        for (size_t j = 1; j < mazeSize::COLUMS_IN_MAZE; j++)
        {
            if ((currentGameContext.map[i][j] & ObjID::PATH) == ObjID::PATH) {
                
                if ((currentGameContext.map[i][j] & ObjID::COIN) == ObjID::COIN) {
                    x = j * frameContext::TILE_SIZE + frameContext::TILE_CENTER - coin.width / 2;
                    y = i * frameContext::TILE_SIZE + frameContext::TILE_CENTER - coin.height / 2;
                    BitBlt(mapTraced.hdc, x, y, coin.width, coin.height,
                        coin.hdc, 0, 0, SRCCOPY);
                }
                if ((currentGameContext.map[i][j] & ObjID::SUPER_COIN) == ObjID::SUPER_COIN) {
                    x = j * frameContext::TILE_SIZE + frameContext::TILE_CENTER - superCoin.width / 2;
                    y = i * frameContext::TILE_SIZE + frameContext::TILE_CENTER - superCoin.height / 2;
                    BitBlt(mapTraced.hdc, x, y, superCoin.width, superCoin.height,
                        superCoin.hdc, 0, 0, SRCCOPY);
                }
            }
        }
    }   
    if (currentGameContext.isCherryTime) {
        x = currentGameContext.cherryCoord.x * frameContext::TILE_SIZE + frameContext::TILE_CENTER  - cherry.width / 2;
        y = currentGameContext.cherryCoord.y * frameContext::TILE_SIZE + frameContext::TILE_CENTER  - cherry.height / 2;
        BitBlt(mapTraced.hdc, x, y, cherry.width, cherry.height,
            cherry.hdc, 0, 0, SRCCOPY);
    }
    renderEnemies();
    renderPlayer();

    BitBlt(mainDC, frameContext::BORDER_LEFT, 0, map.width, map.height,
        mapTraced.hdc, 0, 0, SRCCOPY);

    rednderPlayerInfo();

    DeleteObject(hBmp);
    DeleteObject(mapTraced.hdc);
    
    ReleaseDC(hWnd, mainDC);
    
    return true;
}
