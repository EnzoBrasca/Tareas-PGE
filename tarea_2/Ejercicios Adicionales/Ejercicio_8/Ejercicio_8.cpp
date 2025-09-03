#include <windows.h>
#include <windowsx.h>
#include <string>
#include <vector>
#include <cwchar>

std::wstring g_nombre;
int g_contadorClics = 0;
int g_ancho = 0;
int g_alto = 0;

RECT g_panelNombreRect;
RECT g_panelClicsRect;
RECT g_panelTamanoRect;


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void ActualizarLayout(int ancho, int alto);
void PintarPanel(HDC hdc, const RECT& panelRect, const std::wstring& etiqueta, const std::wstring& valor);


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"PanelMostradorClass";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, L"Panel de Mostrador", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 700, 200,
        NULL, NULL, hInstance, NULL);

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
    switch (msg)
    {
    case WM_SIZE:
    {
      
        g_ancho = LOWORD(lParam);
        g_alto = HIWORD(lParam);

        ActualizarLayout(g_ancho, g_alto);

        InvalidateRect(hwnd, NULL, TRUE);
    }
    return 0;

    case WM_LBUTTONDOWN:
    {

        g_contadorClics++;
      
        InvalidateRect(hwnd, &g_panelClicsRect, TRUE);
    }
    return 0;

    case WM_CHAR:
    {
        wchar_t ch = static_cast<wchar_t>(wParam);
        if (ch == L'\b') 
        {
            if (!g_nombre.empty()) g_nombre.pop_back();
        }
        else if (iswprint(ch)) 
        {
            g_nombre.push_back(ch);
        }
       
        InvalidateRect(hwnd, &g_panelNombreRect, TRUE);
    }
    return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);


        wchar_t buffer[100];
        swprintf_s(buffer, L"%d", g_contadorClics);
        std::wstring valorClics = buffer;

        swprintf_s(buffer, L"%d x %d", g_ancho, g_alto);
        std::wstring valorTamano = buffer;


        PintarPanel(hdc, g_panelNombreRect, L"Nombre (teclado)", g_nombre);
        PintarPanel(hdc, g_panelClicsRect, L"Entradas (clics)", valorClics);
        PintarPanel(hdc, g_panelTamanoRect, L"Tamaño (WxH)", valorTamano);

        EndPaint(hwnd, &ps);
    }
    return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}


void ActualizarLayout(int ancho, int alto)
{
    const int MARGEN = 10;
    const int anchoPanel = (ancho - (4 * MARGEN)) / 3;
    const int altoPanel = alto - (2 * MARGEN);


    g_panelNombreRect.left = MARGEN;
    g_panelNombreRect.top = MARGEN;
    g_panelNombreRect.right = MARGEN + anchoPanel;
    g_panelNombreRect.bottom = MARGEN + altoPanel;


    g_panelClicsRect.left = g_panelNombreRect.right + MARGEN;
    g_panelClicsRect.top = MARGEN;
    g_panelClicsRect.right = g_panelClicsRect.left + anchoPanel;
    g_panelClicsRect.bottom = MARGEN + altoPanel;

    g_panelTamanoRect.left = g_panelClicsRect.right + MARGEN;
    g_panelTamanoRect.top = MARGEN;
    g_panelTamanoRect.right = g_panelTamanoRect.left + anchoPanel;
    g_panelTamanoRect.bottom = MARGEN + altoPanel;
}

void PintarPanel(HDC hdc, const RECT& panelRect, const std::wstring& etiqueta, const std::wstring& valor)
{

    FillRect(hdc, &panelRect, (HBRUSH)GetStockObject(WHITE_BRUSH));
    FrameRect(hdc, &panelRect, (HBRUSH)GetStockObject(BLACK_BRUSH));


    RECT etiquetaRect = panelRect;
    etiquetaRect.top += 5;
    etiquetaRect.left += 5;
    etiquetaRect.right -= 5;
    etiquetaRect.bottom = panelRect.top + 25; 

    RECT valorRect = panelRect;
    valorRect.top = etiquetaRect.bottom + 5;
    valorRect.left += 5;
    valorRect.right -= 5;
    valorRect.bottom = panelRect.bottom - 5;

    SetTextColor(hdc, RGB(100, 100, 100)); 
    DrawTextW(hdc, etiqueta.c_str(), -1, &etiquetaRect, DT_CENTER | DT_SINGLELINE);

    SetTextColor(hdc, RGB(0, 0, 0)); 
    DrawTextW(hdc, valor.c_str(), -1, &valorRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}