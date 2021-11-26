#include "GameCore.h"
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
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = TEXT("Pac-man");  
}

GameCore::GameCore()
{
}

GameCore::~GameCore()
{

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
    hWnd = CreateWindow(
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


    ::SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);

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

    switch (messg)
    {
    case WM_PAINT:
        GetClientRect(hWnd, &Rect);
        hdc = BeginPaint(hWnd, &ps);

        // �������� ��������s ��������� ��� ������� ������������
        hCmpDC = CreateCompatibleDC(hdc);
        hBmp = CreateCompatibleBitmap(hdc, Rect.right - Rect.left,
            Rect.bottom - Rect.top);
        SelectObject(hCmpDC, hBmp);

        // �������� ������� ������
        LOGBRUSH br;
        br.lbStyle = BS_SOLID;
        br.lbColor = 0x0;
        HBRUSH brush;
        brush = CreateBrushIndirect(&br);
        FillRect(hCmpDC, &Rect, brush);
        DeleteObject(brush);

        // ����� ������ �� ��������� hCmpDC

        // �������� ����������� �� �������� ��������� �� �����
        SetStretchBltMode(hdc, COLORONCOLOR);
        BitBlt(hdc, 0, 0, Rect.right - Rect.left, Rect.bottom - Rect.top,
            hCmpDC, 0, 0, SRCCOPY);

        // ������� �������� ��������� �������
        DeleteDC(hCmpDC);
        DeleteObject(hBmp);
        hCmpDC = NULL;
#define t 27
        // �������� ��������s ��������� ��� ������� ������������
        hCmpDC = CreateCompatibleDC(hdc);
        hBmp = CreateCompatibleBitmap(hdc, t-1,t-1);
        SelectObject(hCmpDC, hBmp);

        // �������� ������� ������
        
        br.lbStyle = BS_SOLID;
        br.lbColor = RGB(0,253,255);
        brush = CreateBrushIndirect(&br);
        Rect.left = 0;
        Rect.right = t;
        Rect.top = 0;
        Rect.bottom = t;

        FillRect(hCmpDC, &Rect, brush);
        DeleteObject(brush);
        
        BitBlt(hdc, 300,0 ,t, t,
            hCmpDC, 0, 0, SRCCOPY);

        // ����� ������ �� ��������� hCmpDC
        /*for (size_t i = 0; i < 29; i++)
        {
            BitBlt(hdc, 300+8,  i * t+8,9, t,
                hCmpDC, 0, 0, SRCCOPY);
        }
        for (size_t i = 0; i < 29; i++)
        {
            BitBlt(hdc, 300 + i * t+8, 8+t*2, t, 9,
                hCmpDC, 0, 0, SRCCOPY);
        }
        for (size_t i = 0; i < 29; i++)
        {
            BitBlt(hdc, 300 + i * t+8, 8 , t, 9,
                hCmpDC, 0, 0, SRCCOPY);
        }*/

        for (size_t i = 0; i < 29; i++)
        {
            BitBlt(hdc, 300+8 , i * t , 9, t,
                hCmpDC, 0, 0, SRCCOPY);
        }
        for (size_t i = 0; i < 29; i++)
        {
            BitBlt(hdc, 300 + i * t, t * 2+8, t,9,
                hCmpDC, 0, 0, SRCCOPY);
        }
        for (size_t i = 0; i < 29; i++)
        {
            BitBlt(hdc, 300 + i * t , 8, t, 9,
                hCmpDC, 0, 0, SRCCOPY);
        }
        // �������� ����������� �� �������� ��������� �� �����
        

        // ������� �������� ��������� �������
        DeleteDC(hCmpDC);
        DeleteObject(hBmp);

        hBmp = (HBITMAP)LoadImage(hInstance, TEXT("player.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        if (hBmp == NULL) {
            return false;
        }
        BITMAP bm;
        GetObject(hBmp, sizeof(bm), &bm);
        hCmpDC = CreateCompatibleDC(hdc);
        SelectObject(hCmpDC, hBmp);
        BitBlt(hdc, 300 + t+14- bm.bmWidth/2, t+14- bm.bmHeight/2, bm.bmWidth, bm.bmHeight,
            hCmpDC, 0, 0, SRCCOPY);
        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return (DefWindowProc(hWnd, messg, wParam, lParam));
    }
    return (0);
}

