#include "GameCore.h"
#include "FrameRender.h"

#include <iostream>
#include <string>

#pragma comment(lib, "Msimg32.lib")

using namespace std;
GameCore::GameCore(HINSTANCE _hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow,WNDPROC wndProc)
{
    hInstance = _hInstance;
    // Заполняем структуру класса окна
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
    // Регистрируем класс окна
    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, TEXT("Не могу зарегистрировать класс окна!"), TEXT("Ошибка"), MB_OK);
        return 0;
    }

    MSG lpMsg;
    int X = GetSystemMetrics(SM_CXSCREEN);
    int Y = GetSystemMetrics(SM_CYSCREEN);
    // Создаем основное окно приложения
    this->hWnd=hWnd = CreateWindow(
        TEXT("Pac-man"),                // Имя класса                   
        TEXT("Pac-man"), // Текст заголовка
        WS_OVERLAPPEDWINDOW,        // Стиль окна                                             
        0, 0,                   // Позиция левого верхнего угла  
        X, Y,                  // Ширина и высота окна    
        (HWND)NULL,                // Указатель на родительское окно NULL    
        (HMENU)NULL,               // Используется меню класса окна              
        (HINSTANCE)hInstance,       // Указатель на текущее приложение
        NULL);                  // Передается в качестве lParam в событие WM_CREATE

    currentGameContext = GameContext();

    frameRender = new FrameRender(hWnd, hInstance, currentGameContext);
    if (!hWnd)
    {
        MessageBox(NULL, TEXT("Не удается создать главное окно!"), TEXT("Ошибка"), MB_OK);
        return 0;
    }

    btnStartNewGame = CreateWindow(L"button", L"Start new game",
        WS_CHILD | BS_OWNERDRAW| WS_VISIBLE | BS_PUSHBUTTON,
        frameContext::BORDER_RIGHT+100,400,
        elementSize::BUTTON_WIDTH, elementSize::BUTTON_HEIGHT,
        hWnd,
        (HMENU)0,
        hInstance, NULL);

    SetTimer(hWnd,             // handle to main window 
        ID_MAIN_TIMER,            // timer identifier 
        15,                  
        (TIMERPROC)NULL);     // no timer callback 

    ::SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);

    // Показываем наше окно
    ShowWindow(hWnd, SW_SHOWMAXIMIZED);
    UpdateWindow(hWnd);

    // Выполняем цикл обработки сообщений до закрытия приложения
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
            frameRender->renderText(GetDC(hWnd));
            
        }
        return 0;
    }
    case WM_TIMER:
    {
        currentGameContext.reCalculate();
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
    case WM_COMMAND:
    {
        if (wParam == 0)
        {
            currentGameContext.setGameState(GameState::START_PLAYING);
            frameRender->reloadMap();
            
        }
        return 0;
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

