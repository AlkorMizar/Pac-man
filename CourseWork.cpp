#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassName[] = TEXT("Pac-man");

////////////////////////////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG lpMsg;
    WNDCLASS wc;

    // Заполняем структуру класса окна
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = NULL;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = szClassName;

    // Регистрируем класс окна
    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, TEXT("Не могу зарегистрировать класс окна!"), TEXT("Ошибка"), MB_OK);
        return 0;
    }

    // Создаем основное окно приложения
    hWnd = CreateWindow(
        szClassName,                // Имя класса                   
        TEXT("Pac-man"), // Текст заголовка
        WS_OVERLAPPEDWINDOW,        // Стиль окна                                             
        50, 50,                   // Позиция левого верхнего угла  
        600, 600,                  // Ширина и высота окна    
        (HWND)NULL,                // Указатель на родительское окно NULL    
        (HMENU)NULL,               // Используется меню класса окна              
        (HINSTANCE)hInstance,       // Указатель на текущее приложение
        NULL);                  // Передается в качестве lParam в событие WM_CREATE

    if (!hWnd)
    {
        MessageBox(NULL, TEXT("Не удается создать главное окно!"), TEXT("Ошибка"), MB_OK);
        return 0;
    }

    // Показываем наше окно
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // Выполняем цикл обработки сообщений до закрытия приложения
    while (GetMessage(&lpMsg, NULL, 0, 0))
    {
        TranslateMessage(&lpMsg);
        DispatchMessage(&lpMsg);
    }
    return (lpMsg.wParam);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
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

        // Создание теневогоs контекста для двойной буфферизации
        hCmpDC = CreateCompatibleDC(hdc);
        hBmp = CreateCompatibleBitmap(hdc, Rect.right - Rect.left,
            Rect.bottom - Rect.top);
        SelectObject(hCmpDC, hBmp);

        // Закраска фоновым цветом
        LOGBRUSH br;
        br.lbStyle = BS_SOLID;
        br.lbColor = 0xEECCCC;
        HBRUSH brush;
        brush = CreateBrushIndirect(&br);
        FillRect(hCmpDC, &Rect, brush);
        DeleteObject(brush);

        // Здесь рисуем на контексте hCmpDC

        // Копируем изображение из теневого контекста на экран
        SetStretchBltMode(hdc, COLORONCOLOR);
        BitBlt(hdc, 0, 0, Rect.right - Rect.left, Rect.bottom - Rect.top,
            hCmpDC, 0, 0, SRCCOPY);

        // Удаляем ненужные системные объекты
        DeleteDC(hCmpDC);
        DeleteObject(hBmp);
        hCmpDC = NULL;

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