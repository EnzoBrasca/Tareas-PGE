#include <windows.h>
#include <windowsx.h>
#include <string>
#include <deque>    // Para std::deque
#include <cwchar>   // Para swprintf_s

// Estructura para cada item en nuestra lista de eventos
struct EventItem {
    std::wstring texto;
};

// --- Prototipos de funciones ---
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
std::wstring FormatearMensaje(UINT msg, WPARAM wParam, LPARAM lParam);

// --- Punto de entrada ---
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"VisorEventosClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, L"Zona de Pruebas - Visor de Eventos",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 600, 400,
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

// --- Implementación del Window Procedure ---
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    // Nuestra variable de estado: un deque para los últimos 10 eventos.
    static std::deque<EventItem> ultimosEventos;
    const size_t MAX_EVENTOS = 10;

    // ====================================================================
    //  Lógica de Captura: Se ejecuta para CADA mensaje ANTES del switch
    // ====================================================================

    // ¡CRÍTICO! Evitamos registrar WM_PAINT para no causar un bucle infinito.
    if (msg != WM_PAINT && msg != WM_NCPAINT && msg != WM_ERASEBKGND)
    {
        // 1. Formateamos el mensaje actual a una cadena de texto.
        std::wstring textoEvento = FormatearMensaje(msg, wParam, lParam);

        // 2. Lo añadimos al FRENTE de nuestro deque.
        ultimosEventos.push_front({ textoEvento });

        // 3. Si superamos el límite, eliminamos el más antiguo (del FINAL).
        if (ultimosEventos.size() > MAX_EVENTOS)
        {
            ultimosEventos.pop_back();
        }

        // 4. Solicitamos un repintado para mostrar la lista actualizada.
        InvalidateRect(hwnd, NULL, TRUE);
    }

    // ====================================================================
    //  Switch para el comportamiento funcional de la ventana
    // ====================================================================
    switch (msg)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        RECT clientRect;
        GetClientRect(hwnd, &clientRect);

        // Definimos una altura de línea y una posición inicial
        int yPos = 10;
        const int lineHeight = 20;

        // Recorremos el deque y dibujamos cada evento
        for (const auto& evento : ultimosEventos)
        {
            RECT textRect = { 10, yPos, clientRect.right - 10, yPos + lineHeight };
            DrawTextW(hdc, evento.texto.c_str(), -1, &textRect, DT_LEFT | DT_TOP | DT_SINGLELINE);
            yPos += lineHeight;
        }

        EndPaint(hwnd, &ps);
    }
    return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}


// --- Función Auxiliar para Formatear Mensajes ---
std::wstring FormatearMensaje(UINT msg, WPARAM wParam, LPARAM lParam)
{
    wchar_t buffer[256];

    switch (msg)
    {
    case WM_CHAR:
        swprintf_s(buffer, L"WM_CHAR: '%c' (código: %llu)", (wchar_t)wParam, wParam);
        break;
    case WM_LBUTTONDOWN:
        swprintf_s(buffer, L"WM_LBUTTONDOWN: (x=%d, y=%d)", GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        break;
    case WM_RBUTTONDOWN:
        swprintf_s(buffer, L"WM_RBUTTONDOWN: (x=%d, y=%d)", GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        break;
    case WM_MOUSEMOVE:
        swprintf_s(buffer, L"WM_MOUSEMOVE: (x=%d, y=%d)", GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        break;
    case WM_SIZE:
        swprintf_s(buffer, L"WM_SIZE: %d x %d", LOWORD(lParam), HIWORD(lParam));
        break;
    case WM_CREATE:
        return L"WM_CREATE";
    case WM_CLOSE:
        return L"WM_CLOSE";
    case WM_DESTROY:
        return L"WM_DESTROY";
    default:
        // Para cualquier otro mensaje, mostramos su código hexadecimal
        swprintf_s(buffer, L"Mensaje no mapeado: 0x%04X", msg);
        break;
    }
    return std::wstring(buffer);
}