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

void DrawPanelFrame(HDC hdc, const RECT& r, HBRUSH bg, LPCWSTR titulo) {
    FillRect(hdc, &r, bg);
    HPEN   oldPen = (HPEN)SelectObject(hdc, g_penPanel);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
    Rectangle(hdc, r.left, r.top, r.right, r.bottom);
    SelectObject(hdc, oldBrush);
    SelectObject(hdc, oldPen);

    HFONT old = (HFONT)SelectObject(hdc, g_fontPanel);
    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, RGB(25, 25, 25));
    RECT rt = r; rt.bottom = rt.top + 26; rt.left += 10;
    DrawTextW(hdc, titulo, -1, &rt, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
    SelectObject(hdc, old);
}


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
        L"Ejercicio 3 Pagina responsive",
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
        case WM_SIZE:
            g_cx = LOWORD(l); g_cy = HIWORD(l); InvalidateRect(hWnd, nullptr, TRUE); return 0;
        case WM_PAINT: {
            PAINTSTRUCT ps; HDC hdc = BeginPaint(hWnd, &ps);
            RECT rc; GetClientRect(hWnd, &rc);
            SetBkMode(hdc, TRANSPARENT);

            const int M = 16;
            RECT area = rc; area.top += 72; area.left += M; area.right -= M; area.bottom -= M;
            RECT p1 = area; p1.right = area.left + (area.right - area.left) / 2 - 8; p1.bottom = area.top + 190;
            HFONT oldP = (HFONT)SelectObject(hdc, g_fontPanel);

            RECT p3 = area; p3.top = p1.bottom + 16; p3.bottom = area.bottom;
            DrawPanelFrame(hdc, p3, g_brPanel3, L"Tama\u00F1o del \u00E1rea cliente (WM_SIZE)");
            RECT t3 = p3; t3.left += 12; t3.top += 40;
            std::wstringstream s3; s3 << L"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eu maximus eros. Quisque bibendum sagittis ipsum. Morbi ornare, sem ut congue cursus, lectus nunc sodales lacus, at consequat risus ligula a odio. Sed sed erat facilisis diam semper fringilla. Suspendisse a leo eget mauris pretium ullamcorper a ac mi. Duis nibh eros, gravida quis augue a, malesuada fermentum erat. Curabitur vehicula egestas blandit. Quisque suscipit tortor imperdiet elit laoreet, a varius dui vestibulum. Vestibulum in lacus nec leo mattis congue. Etiam nulla libero, pulvinar quis euismod in, ornare et orciUt vel leo id justo facilisis condimentum.Proin vitae nisl rutrum, suscipit augue sit amet, auctor metus.Cras sagittis cursus fermentum.Aliquam vitae ex quis mauris faucibus aliquet facilisis et arcu.Sed velit nulla, auctor eu risus molestie, hendrerit lobortis turpis.In fringilla malesuada diam, ut semper nisl finibus at.Aenean mattis dolor ullamcorper ligula gravida placerat.Aliquam mauris mi, sodales at dui non, tempus posuere nibh.Nullam congue interdum urna, id suscipit diam blandit sed.Vestibulum ante eros, sodales id rhoncus quis, consectetur egestas leo.Pellentesque nec sodales risus.Suspendisse a malesuada magna, id malesuada sapien.Sed condimentum lacus et augue aliquet gravida.Nam et eros sapien.Duis semper erat eu commodo sagittis.";
            DrawTextW(hdc, s3.str().c_str(), -1, &t3, DT_LEFT | DT_SINGLELINE | DT_NOPREFIX);

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
