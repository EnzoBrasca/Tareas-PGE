#define WIN32_LEAN_AND_MEAN


#include <windows.h>
#include <string>
#include <sstream>
#include <cwctype>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static std::wstring g_typed;
static int          g_clicks = 0;
static int          g_cx = 0, g_cy = 0;

static HFONT  g_fontTitle = nullptr;
static HFONT  g_fontPanel = nullptr;
static HPEN   g_penPanel = nullptr;
static HBRUSH g_brPanel1 = nullptr;
static HBRUSH g_brPanel2 = nullptr;
static HBRUSH g_brPanel3 = nullptr;

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, PWSTR, int nCmdShow) {
    const wchar_t* kClass = L"PGE_Unidad1_UI_Espanol";

    WNDCLASSEXW wc{ sizeof(wc) };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = kClass;
    RegisterClassExW(&wc);

    // Título con EN DASH y tilde usando \uXXXX
    HWND hWnd = CreateWindowExW(
        0, kClass,
        L"Ejercicio 2 contador de entradas",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 960, 600,
        nullptr, nullptr, hInst, nullptr);
    if (!hWnd) return 0;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT m, WPARAM w, LPARAM l) {
    switch (m) {
    case WM_LBUTTONDOWN: {
        ++g_clicks; InvalidateRect(hWnd, nullptr, TRUE); return 0;
    }
    case WM_RBUTTONDOWN: {
        if (g_clicks > 0) {
            --g_clicks; InvalidateRect(hWnd, nullptr, TRUE); return 0;
        }
    }

    case WM_PAINT: {
        PAINTSTRUCT ps; HDC hdc = BeginPaint(hWnd, &ps);
        RECT rc; GetClientRect(hWnd, &rc);
        SetBkMode(hdc, TRANSPARENT);

        const int M = 16;
        RECT area = rc; area.top += 72; area.left += M; area.right -= M; area.bottom -= M;
        RECT p1 = area; p1.right = area.left + (area.right - area.left) / 2 - 8; p1.bottom = area.top + 190;
        HFONT oldP = (HFONT)SelectObject(hdc, g_fontPanel);

        RECT p2 = p1; p2.left = p1.right + 16; p2.right = area.right;
        RECT t2 = p2; t2.left += 12; t2.top += 40;
        std::wstringstream s2; s2 << L"Contador de entradas vendidads: " << g_clicks;
        DrawTextW(hdc, s2.str().c_str(), -1, &t2, DT_LEFT | DT_SINGLELINE | DT_NOPREFIX);

        SelectObject(hdc, oldP);
        EndPaint(hWnd, &ps);
        return 0;
    }
    case WM_DESTROY:
        if (g_fontTitle) { DeleteObject(g_fontTitle);  g_fontTitle = nullptr; }
        if (g_fontPanel) { DeleteObject(g_fontPanel);  g_fontPanel = nullptr; }
        if (g_penPanel) { DeleteObject(g_penPanel);   g_penPanel = nullptr; }
        if (g_brPanel1) { DeleteObject(g_brPanel1);   g_brPanel1 = nullptr; }
        if (g_brPanel2) { DeleteObject(g_brPanel2);   g_brPanel2 = nullptr; }
        if (g_brPanel3) { DeleteObject(g_brPanel3);   g_brPanel3 = nullptr; }
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(hWnd, m, w, l);
}