#include <windows.h>
#include <windowsx.h>
#include <wchar.h> 

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
        L"Ascensor",
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

const int NUM_BOTONES = 3;
const int ANCHO_BOTON = 100;
const int ALTO_BOTON = 40;
const int MARGEN_VERTICAL = 10;
const int POS_INICIAL_X = 50;
const int POS_INICIAL_Y = 50;


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    static RECT botones[NUM_BOTONES];

    static int ultimoPisoVisitado = 0;

    static RECT rectLabel;

    switch (msg) {
        case WM_CREATE:
        {
            for (int i = 0; i < NUM_BOTONES; ++i)
            {
                botones[i].left = POS_INICIAL_X;
                botones[i].right = POS_INICIAL_X + ANCHO_BOTON;

                botones[i].top = POS_INICIAL_Y + i * (ALTO_BOTON + MARGEN_VERTICAL);
                botones[i].bottom = botones[i].top + ALTO_BOTON;
            }
            rectLabel.left = POS_INICIAL_X;
            rectLabel.right = POS_INICIAL_X + 250; 
            rectLabel.top = botones[NUM_BOTONES - 1].bottom + MARGEN_VERTICAL * 2; 
            rectLabel.bottom = rectLabel.top + 50;
	    }break;

        case WM_LBUTTONDOWN:
        {
            POINT puntoDelClic = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };

            for (int i = 0; i < NUM_BOTONES; ++i)
            {
                if (PtInRect(&botones[i], puntoDelClic))
                {
                   
                    ultimoPisoVisitado = i + 1;

                    InvalidateRect(hwnd, &rectLabel, TRUE);
                    break;
                }
            }
        }
        return 0;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            HBRUSH hBrushAzul = CreateSolidBrush(RGB(200, 220, 255));
            HBRUSH hBrushNegro = (HBRUSH)GetStockObject(BLACK_BRUSH);
            SetBkMode(hdc, TRANSPARENT);

            for (int i = 0; i < NUM_BOTONES; ++i)
            {
                FillRect(hdc, &botones[i], hBrushAzul);

               
                FrameRect(hdc, &botones[i], hBrushNegro);

                
                wchar_t textoBoton[20];
                swprintf_s(textoBoton, L"Botón %d", i + 1);
                DrawTextW(hdc, textoBoton, -1, &botones[i], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            }
            wchar_t textoLabel[100];
            if (ultimoPisoVisitado == 0)
            {
                swprintf_s(textoLabel, L"Último piso visitado: Ninguno");
            }
            else
            {
                swprintf_s(textoLabel, L"Último piso visitado: %d", ultimoPisoVisitado);
            }
           
            DrawTextW(hdc, textoLabel, -1, &rectLabel, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
            DeleteObject(hBrushAzul);

            EndPaint(hwnd, &ps);
        }
        return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}