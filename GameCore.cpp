#include "GameCore.h"
#include "FrameRender.h"

#include <string>

#include <CommCtrl.h>
#include <time.h>

#pragma comment(lib, "Msimg32.lib")

#define WM_COMMAND                      0x0111
#define WM_SYSCOMMAND                   0x0112

using namespace std;
using namespace elementSize;

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

    currentGameContext = GameContext();

    frameRender = new FrameRender(hWnd, hInstance, currentGameContext);
    if (!hWnd)
    {
        MessageBox(NULL, TEXT("�� ������� ������� ������� ����!"), TEXT("������"), MB_OK);
        return 0;
    }

    btnStartNewGame = CreateWindow(L"button", L"Start new game",
        WS_CHILD | BS_OWNERDRAW| WS_VISIBLE | BS_PUSHBUTTON,
        ::BUTTON_RECT.left,::BUTTON_RECT.top,
        ::BUTTON_WIDTH, ::BUTTON_HEIGHT,
        hWnd,
        (HMENU)NEW_START,
        hInstance, NULL);

    CreateWindow(L"button", L"NORMAL",
        WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
        ::COMBOBOX_RECT.left, ::COMBOBOX_RECT.top, 100, 30, hWnd, (HMENU)10001, hInstance, NULL);
    CreateWindow(L"button", L"MAZE LIKE",
        WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
        ::COMBOBOX_RECT.left, ::COMBOBOX_RECT.top+30, 100, 30, hWnd, (HMENU)10002, hInstance, NULL);
    

    seedWriter = CreateWindow(L"edit", L"",
        WS_CHILD | WS_VISIBLE| ES_CENTER| ES_NUMBER,
        ::TEXTBOX_RECT.left, ::TEXTBOX_RECT.top,
        ::BUTTON_WIDTH, ::TEXT_BOX_HEIGHT,
        hWnd,
        (HMENU)NEW_START,
        hInstance, NULL);

    SetTimer(hWnd,             // handle to main window 
        ID_MAIN_TIMER,            // timer identifier 
        16,                  
        (TIMERPROC)NULL);     // no timer callback 

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
    HDC mainDC;
    switch (messg)
    {
    case WM_COMMAND:
    {
        if (wParam == NEW_START) {
            int editlength = GetWindowTextLength(seedWriter)+1;
            std::vector<wchar_t> txt(editlength);
            GetWindowText(seedWriter, (LPWSTR)&txt[0], editlength);

            long seed = static_cast<long>(time(NULL));
            std::wstring text = L"Creating map using random seed ";
            try
            {
                int s = std::stoll(&txt[0]);
                if (s != currentGameContext.getCurrentSeed() ||
                    currDif != currentGameContext.getDifficulty()) {
                    seed = s;
                    text = L"Creating map using user's seed ";
                }
            }
            catch (const std::exception&)
            {
            }

            SetWindowText(seedWriter, (LPWSTR)std::to_wstring(seed).c_str());

            MessageBox(NULL, text.c_str(), L"edit text", MB_OK);
            currentGameContext.startNewGame(currDif,seed);
            frameRender->reloadMap();
        }
        // ���� �� ������ �� 1-� �����������.
        if (LOWORD(wParam) == 10001) {
            diffText = L"EASY";
            currDif = maze::MazeTypeEnum::NORMAL;
        }
        // ���� �� ������ �� 2-� �����������.
        if (LOWORD(wParam) == 10002) {
            diffText = L"NORMAL";
            currDif = maze::MazeTypeEnum::MAZE_LIKE;
        }
        break;
    }
    case WM_DRAWITEM:
    {
        LPDRAWITEMSTRUCT pDIS = (LPDRAWITEMSTRUCT)lParam;
        if (pDIS->hwndItem == btnStartNewGame)
        {
            frameRender->renderButton(pDIS->hDC);
            frameRender->renderText();
            
        }
        break;
    }
    case WM_TIMER:
    {
        currentGameContext.reCalculate();
        if (currentGameContext.getGameState() == GameState::WAIT_START) {
            frameRender->reloadMap();
        }
        frameRender->renderNextFrame(); 
        break;
    }
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_DOWN: {
            currentGameContext.setPlayerDirection(directions::DOWN);
            break; }
        case VK_LEFT: {
            currentGameContext.setPlayerDirection(directions::LEFT);
            break; }
        case VK_UP: {
            currentGameContext.setPlayerDirection(directions::UP);
            break; }
        case VK_RIGHT: {
            currentGameContext.setPlayerDirection(directions::RIGHT);
            break; }
        default:
            break;
        }
        break;
    }
    
    case WM_DESTROY: {
        PostQuitMessage(0);
        break;
    }
    return 0;
    default:
        return (DefWindowProc(hWnd, messg, wParam, lParam));
    }
    return (0);
}

void GameCore::startNewGame()
{
}

