#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	const wchar_t CLASS_NAME[] = L"Pizarra";

    WNDCLASS wc = { };
    wc.lpfnWndProc = WndProc;           
    wc.hInstance = hInst;           
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); 

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Aula con Pizarra",
        WS_OVERLAPPEDWINDOW,


        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,

        NULL,
        NULL,
        hInst,
        NULL
    );
        if (hwnd == NULL)
        {
            return 0;
        }

        ShowWindow(hwnd, nCmdShow);
        UpdateWindow(hwnd);

        MSG msg = { };
        while (GetMessage(&msg, NULL, 0, 0) > 0)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_PAINT:
    {
        const wchar_t* instrucciones = L"Bienvenido a la clase de Win32.\n\n"
            L"Recuerda: todo el dibujo debe ocurrir dentro del mensaje WM_PAINT.\n"
            L"Esto asegura que la ventana se repinte correctamente siempre que sea necesario.";

        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        RECT clientRect;
        GetClientRect(hwnd, &clientRect);

        SetBkMode(hdc, TRANSPARENT);

        DrawTextW(hdc, instrucciones, -1, &clientRect, DT_CENTER | DT_WORDBREAK);

        EndPaint(hwnd, &ps);
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}