#include "GameCore.h"
#include "FrameRender.h"

#include <iostream>
#include <string>

#pragma comment(lib, "Msimg32.lib")

using namespace std;
GameCore::GameCore(HINSTANCE _hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow,WNDPROC wndProc)
{
    hInstance = _hInstance;
    // ��������� ��������� ������ ����
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = wndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = NULL;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = TEXT("Pac-man");  
}

GameCore::GameCore()
{
}

GameCore::~GameCore()
{
    delete frameRender;
}

int GameCore::play()
{
    // ������������ ����� ����
    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, TEXT("�� ���� ���������������� ����� ����!"), TEXT("������"), MB_OK);
        return 0;
    }

    MSG lpMsg;
    int X = GetSystemMetrics(SM_CXSCREEN);
    int Y = GetSystemMetrics(SM_CYSCREEN);
    // ������� �������� ���� ����������
    this->hWnd=hWnd = CreateWindow(
        TEXT("Pac-man"),                // ��� ������                   
        TEXT("Pac-man"), // ����� ���������
        WS_OVERLAPPEDWINDOW,        // ����� ����                                             
        0, 0,                   // ������� ������ �������� ����  
        X, Y,                  // ������ � ������ ����    
        (HWND)NULL,                // ��������� �� ������������ ���� NULL    
        (HMENU)NULL,               // ������������ ���� ������ ����              
        (HINSTANCE)hInstance,       // ��������� �� ������� ����������
        NULL);                  // ���������� � �������� lParam � ������� WM_CREATE

    if (!hWnd)
    {
        MessageBox(NULL, TEXT("�� ������� ������� ������� ����!"), TEXT("������"), MB_OK);
        return 0;
    }

    btnStartNewGame = CreateWindow(L"button", L"Start new game",
        WS_CHILD | BS_OWNERDRAW| WS_VISIBLE | BS_PUSHBUTTON,
        frameContext::BORDER_RIGHT+100,400,
        elementSize::BUTTON_WIDTH, elementSize::BUTTON_HEIGHT,
        hWnd,
        (HMENU)0,
        hInstance, NULL);

    ::SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);

    currentGameContext = GameContext();

    frameRender =new FrameRender(hWnd,hInstance,currentGameContext);
    // ���������� ���� ����
    ShowWindow(hWnd, SW_SHOWMAXIMIZED);
    UpdateWindow(hWnd);

    // ��������� ���� ��������� ��������� �� �������� ����������
    while (GetMessage(&lpMsg, NULL, 0, 0))
    {
        TranslateMessage(&lpMsg);
        DispatchMessage(&lpMsg);
    }
    return (lpMsg.wParam);
}




LRESULT GameCore::Process(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    RECT Rect;
    HDC hdc, hCmpDC;
    HBITMAP hBmp;
    HDC mainDC;
    switch (messg)
    {
    case WM_DRAWITEM:
    {
        LPDRAWITEMSTRUCT pDIS = (LPDRAWITEMSTRUCT)lParam;
        if (pDIS->hwndItem == btnStartNewGame)
        {
            frameRender->renderButton(pDIS->hDC);
        }
        return 0;
    }
    case WM_COMMAND:
    {
        if (wParam == 0)
        {
            MessageBox(hWnd, L"������ ������ Button 1",
                L"Message WM_COMMAND", MB_OK);
        }
        return 0;
    }
    case WM_PAINT: {
        GetClientRect(hWnd, &Rect);
       
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return (DefWindowProc(hWnd, messg, wParam, lParam));
    }
    return (0);
}

void GameCore::startNewGame()
{
}

