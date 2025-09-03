#define UNICODE
#define _UNICODE
#define	WIN32_LEAN_AND_MEAN
#pragma execution_character_set("utf-8")

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
        L"Ejercicio 1 recepcion de hotel",
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
    case WM_CHAR:
    {
        wchar_t ch = (wchar_t)w;
        if (ch == L'\b') { if (!g_typed.empty()) g_typed.pop_back(); }
        else if (iswprint(ch)) g_typed.push_back(ch);
        InvalidateRect(hWnd, nullptr, TRUE);
        return 0;
    }
    case WM_PAINT: {
        PAINTSTRUCT ps; HDC hdc = BeginPaint(hWnd, &ps);
        RECT rc; GetClientRect(hWnd, &rc);
        SetBkMode(hdc, TRANSPARENT);

        
        HFONT old = (HFONT)SelectObject(hdc, g_fontTitle);
        SetTextColor(hdc, RGB(20, 60, 120));
        RECT hdr = rc; hdr.bottom = hdr.top + 60; hdr.left += 16; hdr.top += 8;
        DrawTextW(hdc, L"Unidad I \u2013 Bucle despachador de eventos (Win32)",
            -1, &hdr, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
        SelectObject(hdc, old);
        SetTextColor(hdc, RGB(0, 0, 0));

        const int M = 16;
        RECT area = rc; area.top += 72; area.left += M; area.right -= M; area.bottom -= M;

        RECT p1 = area; p1.right = area.left + (area.right - area.left) / 2 - 8; p1.bottom = area.top + 190;
        HFONT oldP = (HFONT)SelectObject(hdc, g_fontPanel);
        RECT t1 = p1; t1.left += 12; t1.top += 36; t1.right -= 12;

        const wchar_t* demoEsp =
            L"Demostraci\u00F3n de caracteres: \u00E1\u00E9\u00ED\u00F3\u00FA "
            L"\u00C1\u00C9\u00CD\u00D3\u00DA \u00F1 \u00D1 \u00FC \u00DC "
            L"\u00BFC\u00F3mo est\u00E1s? \u00A1Hola!";
        std::wstring linea = L"Teclado: " + (g_typed.empty() ? L"(vac\u00EDo)" : g_typed);
        DrawTextW(hdc, demoEsp, -1, &t1, DT_LEFT | DT_WORDBREAK | DT_NOPREFIX);
        t1.top += 52;
        DrawTextW(hdc, linea.c_str(), -1, &t1, DT_LEFT | DT_WORDBREAK | DT_NOPREFIX);

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