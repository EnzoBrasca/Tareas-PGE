#include <windows.h>
#include <windowsx.h>
#include <string> 
#include <cctype>  

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"CajaRegistradora";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_IBEAM); // Cursor de texto (I-beam) es más apropiado aquí

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Caja Registradora",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 200,
        NULL, NULL, hInstance, NULL
    );

    if (hwnd == NULL) return 0;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static std::wstring importe;

    switch (msg)
    {
   
        case WM_CHAR:
        {
            wchar_t ch = static_cast<wchar_t>(wParam);
            bool estadoCambiado = false;

            
            if (ch == L'\b') 
            {
                if (!importe.empty())
                {
                    importe.pop_back(); 
                    estadoCambiado = true;
                }
            }
           
            else if (iswdigit(ch))
            {
                importe.push_back(ch); 
                estadoCambiado = true;
            }
            
            else if (ch == L',' || ch == L'.')
            {
                
                if (importe.find(L',') == std::wstring::npos)
                {
                    importe.push_back(L',');
                    estadoCambiado = true;
                }
            }
           

            
            if (estadoCambiado)
            {
                InvalidateRect(hwnd, NULL, TRUE);
            }
        }
    return 0; 

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

       
        std::wstring displayText = L"Importe: " + importe;

        RECT clientRect;
        GetClientRect(hwnd, &clientRect);

       
        clientRect.left += 10;
        clientRect.top += 10;

  
        DrawTextW(hdc, displayText.c_str(), -1, &clientRect, DT_LEFT | DT_TOP | DT_SINGLELINE);

        EndPaint(hwnd, &ps);
    }
    return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}