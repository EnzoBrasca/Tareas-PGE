#include <windows.h>
#include <vector>

// ----- IDs para los botones de la VENTANA PRINCIPAL -----
// Cada botón representa una "vista" que queremos mostrar.
#define ID_BUTTON_SHOW_VIEW1 101
#define ID_BUTTON_SHOW_VIEW2 102
#define ID_BUTTON_SHOW_VIEW3 103
#define ID_BUTTON_SHOW_VIEW4 104
#define ID_BUTTON_SHOW_VIEW5 105
#define ID_BUTTON_SHOW_VIEW6 106
#define ID_BUTTON_SHOW_VIEW7 107


// Id para el slide down de la ventana principal
#define ID_BUTTON_SHOW_VIEW8 108
#define ID_MENU_OPCION1 201
#define ID_MENU_OPCION2 202
#define ID_MENU_OPCION3 203
#define ID_MENU_OPCION4 204
#define ID_MENU_SEPARADOR 205

// ID para el botón estático de regreso en la ventana secundaria
#define ID_BUTTON_RETURN_TO_MAIN 206

// WM_APP es el inicio del rango para mensajes definidos por la aplicación.
#define WM_APP_CHANGE_VIEW (WM_APP + 1)

// ----- Prototipos de los WndProc -----
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK SecondaryWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// ----- Variables Globales -----
HWND g_hwndMain = NULL;
HWND g_hwndSecondary = NULL;

// Un vector para guardar los handles de los controles que creamos dinámicamente.
// Esto nos permitirá destruirlos fácilmente después.
std::vector<HWND> g_vecChildControls;


// ----- Punto de Entrada (WinMain)-----
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // El registro de clases y la creación de las ventanas principales es igual que antes.
    WNDCLASSEX wcMain = { 0 };
    wcMain.cbSize = sizeof(WNDCLASSEX);
    wcMain.lpfnWndProc = MainWndProc;
    wcMain.hInstance = hInstance;
    wcMain.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcMain.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcMain.lpszClassName = L"MainWindowClass";
    RegisterClassEx(&wcMain);

    WNDCLASSEX wcSecondary = { 0 };
    wcSecondary.cbSize = sizeof(WNDCLASSEX);
    wcSecondary.lpfnWndProc = SecondaryWndProc;
    wcSecondary.hInstance = hInstance;
    wcSecondary.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcSecondary.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
    wcSecondary.lpszClassName = L"SecondaryWindowClass";
    RegisterClassEx(&wcSecondary);

    g_hwndMain = CreateWindowEx(WS_EX_CLIENTEDGE, L"MainWindowClass", L"Menú Principal", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1200, 500, NULL, NULL, hInstance, NULL);
    g_hwndSecondary = CreateWindowEx(WS_EX_CLIENTEDGE, L"SecondaryWindowClass", L"Ventana de Contenido", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1200, 450, NULL, NULL, hInstance, NULL);

    ShowWindow(g_hwndMain, nCmdShow);
    UpdateWindow(g_hwndMain);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

static HWND g_hDropdownButton = NULL;

//Funcion para generar los botones en ambas ventanas evitando la redundancia de codigo

void generarBotones(HWND hwnd) {
    HDC hdc = GetDC(hwnd);
    if (!hdc) {
        return;
    }

	// Definimos las constantes para la posicion y tamaño de los botones
    const int Button_Y_Pos = 20;
    const int Button_Height = 30;
    const int Button_Width = 180;
    const int Initial_X_Pos = 20;
    const int Horizontal_Spacing = 20;
    const int Separador = 40;

	// Calculamos el ancho de cada boton segun el texto que contiene
    const wchar_t* btn1Txt = L"Impuestos";
    SIZE sizeBtn1;

    GetTextExtentPoint32W(hdc, btn1Txt, wcslen(btn1Txt), &sizeBtn1);

    int btn1Width = sizeBtn1.cx + Horizontal_Spacing;

    const wchar_t* btn2Txt = L"Pagos";
    SIZE sizeBtn2;

    GetTextExtentPoint32W(hdc, btn2Txt, wcslen(btn2Txt), &sizeBtn2);

    int btn2Width = sizeBtn2.cx + Horizontal_Spacing;

    const wchar_t* btn3Txt = L"Domicilio Fiscal Electronico";
    SIZE sizeBtn3;

    GetTextExtentPoint32W(hdc, btn3Txt, wcslen(btn3Txt), &sizeBtn3);

    int btn3Width = sizeBtn3.cx + Separador;

    const wchar_t* btn4Txt = L"Debito";
    SIZE sizeBtn4;

    GetTextExtentPoint32W(hdc, btn4Txt, wcslen(btn4Txt), &sizeBtn4);

    int btn4Width = sizeBtn4.cx + Separador;

    const wchar_t* btn5Txt = L"Planes de Pagos";
    SIZE sizeBtn5;

    GetTextExtentPoint32W(hdc, btn5Txt, wcslen(btn5Txt), &sizeBtn5);

    int btn5Width = sizeBtn5.cx + Separador;

    const wchar_t* btn6Txt = L"Declaraciones Juradas";
    SIZE sizeBtn6;

    GetTextExtentPoint32W(hdc, btn6Txt, wcslen(btn6Txt), &sizeBtn6);

    int btn6Width = sizeBtn6.cx + Separador;

    const wchar_t* btn7Txt = L"Usuario";
    SIZE sizeBtn7;

    GetTextExtentPoint32W(hdc, btn7Txt, wcslen(btn7Txt), &sizeBtn7);

    int btn7Width = sizeBtn7.cx + Separador;

    const wchar_t* btn8Txt = L"Gestiones \u25BC";
    SIZE sizeBtn8;

    GetTextExtentPoint32W(hdc, btn8Txt, wcslen(btn8Txt), &sizeBtn8);

    int btn8Width = sizeBtn8.cx + Separador;

	// Creamos el boton desplegable y guardamos su handle en una variable global para usarlo luego
    g_hDropdownButton = CreateWindow(
        L"BUTTON",
        btn8Txt,
        WS_TABSTOP | WS_VISIBLE | WS_CHILD,
        (Initial_X_Pos + btn1Width + btn2Width + btn3Width + btn4Width + btn5Width + btn6Width + btn7Width + 140), Button_Y_Pos, btn8Width, Button_Height,
        hwnd, (HMENU)ID_BUTTON_SHOW_VIEW8, NULL, NULL);

	// Creamos los 7 Botones principales
    CreateWindow(L"BUTTON", btn1Txt, WS_TABSTOP | WS_VISIBLE | WS_CHILD, Initial_X_Pos, Button_Y_Pos, btn1Width, Button_Height, hwnd, (HMENU)ID_BUTTON_SHOW_VIEW1, NULL, NULL);
    CreateWindow(L"BUTTON", btn2Txt, WS_TABSTOP | WS_VISIBLE | WS_CHILD, (Initial_X_Pos + btn1Width + Horizontal_Spacing), Button_Y_Pos, btn2Width, Button_Height, hwnd, (HMENU)ID_BUTTON_SHOW_VIEW2, NULL, NULL);
    CreateWindow(L"BUTTON", btn3Txt, WS_TABSTOP | WS_VISIBLE | WS_CHILD, (Initial_X_Pos + btn1Width + btn2Width + Separador), Button_Y_Pos, btn3Width, Button_Height, hwnd, (HMENU)ID_BUTTON_SHOW_VIEW3, NULL, NULL);
    CreateWindow(L"BUTTON", btn4Txt, WS_TABSTOP | WS_VISIBLE | WS_CHILD, (Initial_X_Pos + btn1Width + btn2Width + btn3Width + 60), Button_Y_Pos, btn4Width, Button_Height, hwnd, (HMENU)ID_BUTTON_SHOW_VIEW4, NULL, NULL);
    CreateWindow(L"BUTTON", btn5Txt, WS_TABSTOP | WS_VISIBLE | WS_CHILD, (Initial_X_Pos + btn1Width + btn2Width + btn3Width + btn4Width + 80), Button_Y_Pos, btn5Width, Button_Height, hwnd, (HMENU)ID_BUTTON_SHOW_VIEW5, NULL, NULL);
    CreateWindow(L"BUTTON", btn6Txt, WS_TABSTOP | WS_VISIBLE | WS_CHILD, (Initial_X_Pos + btn1Width + btn2Width + btn3Width + btn4Width + btn5Width + 100), Button_Y_Pos, btn6Width, Button_Height, hwnd, (HMENU)ID_BUTTON_SHOW_VIEW6, NULL, NULL);
    CreateWindow(L"BUTTON", btn7Txt, WS_TABSTOP | WS_VISIBLE | WS_CHILD, (Initial_X_Pos + btn1Width + btn2Width + btn3Width + btn4Width + btn5Width + btn6Width + 120), Button_Y_Pos, btn7Width, Button_Height, hwnd, (HMENU)ID_BUTTON_SHOW_VIEW7, NULL, NULL);
    
}

// ----- WndProc de la Ventana Principal -----
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
    {
		// Creamos los botones y el label en la ventana principal
        HDC hdc = GetDC(hwnd);
        if (!hdc) {
            return -1;
        }
        const wchar_t* labelTxt = L"Bienvenido a la pagina de rentas Cordoba \n Porfavor seleccione alguna de las opciones disponibles para acceder a las funcionalidades";
        SIZE sizeLabel;

        GetTextExtentPoint32W(hdc, labelTxt, wcslen(labelTxt), &sizeLabel);

        int labelWidth = sizeLabel.cx;
        CreateWindow(L"STATIC", labelTxt, WS_VISIBLE | WS_CHILD, 50, 100, labelWidth, 50, hwnd, NULL, NULL, NULL);
		generarBotones(hwnd);
        break;
    }

    case WM_COMMAND:
    {
		// Manejo de los comandos de los botones
        int wmId = LOWORD(wParam);
        HMENU hMenu = CreatePopupMenu();
        RECT rect;
        //Verificacion de que boton se presiono
        switch (wmId) {
        case ID_BUTTON_SHOW_VIEW1:
            ShowWindow(g_hwndMain, SW_HIDE);

            SendMessage(g_hwndSecondary, WM_APP_CHANGE_VIEW, (WPARAM)wmId, 0);

            ShowWindow(g_hwndSecondary, SW_SHOW);
            break;
        case ID_BUTTON_SHOW_VIEW2:
            ShowWindow(g_hwndMain, SW_HIDE);

            SendMessage(g_hwndSecondary, WM_APP_CHANGE_VIEW, (WPARAM)wmId, 0);

            ShowWindow(g_hwndSecondary, SW_SHOW);
            break;
        case ID_BUTTON_SHOW_VIEW3:
            ShowWindow(g_hwndMain, SW_HIDE);

            SendMessage(g_hwndSecondary, WM_APP_CHANGE_VIEW, (WPARAM)wmId, 0);

            ShowWindow(g_hwndSecondary, SW_SHOW);
            break;
        case ID_BUTTON_SHOW_VIEW4:
            ShowWindow(g_hwndMain, SW_HIDE);

            SendMessage(g_hwndSecondary, WM_APP_CHANGE_VIEW, (WPARAM)wmId, 0);

            ShowWindow(g_hwndSecondary, SW_SHOW);
            break;
        case ID_BUTTON_SHOW_VIEW5:
            ShowWindow(g_hwndMain, SW_HIDE);

            SendMessage(g_hwndSecondary, WM_APP_CHANGE_VIEW, (WPARAM)wmId, 0);

            ShowWindow(g_hwndSecondary, SW_SHOW);
            break;
        case ID_BUTTON_SHOW_VIEW6:
            ShowWindow(g_hwndMain, SW_HIDE);

            SendMessage(g_hwndSecondary, WM_APP_CHANGE_VIEW, (WPARAM)wmId, 0);

            ShowWindow(g_hwndSecondary, SW_SHOW);
            break;
        case ID_BUTTON_SHOW_VIEW7:
            ShowWindow(g_hwndMain, SW_HIDE);

            SendMessage(g_hwndSecondary, WM_APP_CHANGE_VIEW, (WPARAM)wmId, 0);

            ShowWindow(g_hwndSecondary, SW_SHOW);
            break;
        
        case ID_BUTTON_SHOW_VIEW8:
			// Crear el menú desplegable
            AppendMenuW(hMenu, MF_STRING, ID_MENU_OPCION1, L"Valores de Ref...");
            AppendMenuW(hMenu, MF_STRING, ID_MENU_OPCION2, L"Compensacion");
            AppendMenuW(hMenu, MF_STRING, ID_MENU_OPCION3, L"Exencion...");
            AppendMenuW(hMenu, MF_STRING, ID_MENU_OPCION4, L"Transferencia");

            AppendMenuW(hMenu, MF_SEPARATOR, ID_MENU_SEPARADOR, NULL);

			// Obtener la posición del botón desplegable para mostrar el menú justo debajo de él
            GetWindowRect(g_hDropdownButton, &rect);

            TrackPopupMenuEx(hMenu, TPM_LEFTALIGN | TPM_TOPALIGN, rect.left, rect.bottom, hwnd, NULL);
            
            DestroyMenu(hMenu);
            break;
		case ID_MENU_OPCION1:
            ShowWindow(g_hwndMain, SW_HIDE);

            SendMessage(g_hwndSecondary, WM_APP_CHANGE_VIEW, (WPARAM)wmId, 0);

            ShowWindow(g_hwndSecondary, SW_SHOW);
            break;
		case ID_MENU_OPCION2:
			ShowWindow(g_hwndMain, SW_HIDE);

			SendMessage(g_hwndSecondary, WM_APP_CHANGE_VIEW, (WPARAM)wmId, 0);

			ShowWindow(g_hwndSecondary, SW_SHOW);
			break;
		case ID_MENU_OPCION3:
            ShowWindow(g_hwndMain, SW_HIDE);

            SendMessage(g_hwndSecondary, WM_APP_CHANGE_VIEW, (WPARAM)wmId, 0);

            ShowWindow(g_hwndSecondary, SW_SHOW);
            break;
		case ID_MENU_OPCION4:
            ShowWindow(g_hwndMain, SW_HIDE);

            SendMessage(g_hwndSecondary, WM_APP_CHANGE_VIEW, (WPARAM)wmId, 0);

            ShowWindow(g_hwndSecondary, SW_SHOW);
            break;
        } break;
    }
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}



// ----- Funciones para Crear y Destruir Vistas Dinámicamente -----
void DestroyChildControls() {
    for (HWND hControl : g_vecChildControls) {
        DestroyWindow(hControl);
    }
    g_vecChildControls.clear(); 
}
// Cada una de estas funciones crea una "vista" diferente en la ventana secundaria.
void CreateView1(HWND hWndParent) {
 
    HWND hLabel = CreateWindow(L"STATIC", L"Aqui usted puede ver y pagar sus impuestos", WS_VISIBLE | WS_CHILD, 50, 100, 400, 20, hWndParent, NULL, NULL, NULL);

    g_vecChildControls.push_back(hLabel);
}

void CreateView2(HWND hWndParent) {
    HWND hLabel = CreateWindow(L"STATIC", L"Aqui usted puede ver su historial de pagos", WS_VISIBLE | WS_CHILD, 50, 100, 400, 20, hWndParent, NULL, NULL, NULL);

    g_vecChildControls.push_back(hLabel);
}
void CreateView3(HWND hWndParent) {

    HWND hLabel = CreateWindow(L"STATIC", L"Aqui usted puede administrar y ver las notificaciones de su domicilio fiscal", WS_VISIBLE | WS_CHILD, 50, 100, 400, 30, hWndParent, NULL, NULL, NULL);

    g_vecChildControls.push_back(hLabel);
}

void CreateView4(HWND hWndParent) {
    HWND hLabel = CreateWindow(L"STATIC", L"Aqui usted puede gestionar sus planes de debito automatico", WS_VISIBLE | WS_CHILD, 50, 100, 400, 20, hWndParent, NULL, NULL, NULL)
        ;
    g_vecChildControls.push_back(hLabel);
}

void CreateView5(HWND hWndParent) {
    HWND hLabel = CreateWindow(L"STATIC", L"Aqui usted puede ver los planes de pago que tiene a su nombre", WS_VISIBLE | WS_CHILD, 50, 100, 400, 30, hWndParent, NULL, NULL, NULL);
    
    g_vecChildControls.push_back(hLabel);
}

void CreateView6(HWND hWndParent) {
    HWND hLabel = CreateWindow(L"STATIC", L"Aqui usted puede consultar sus declaraciones juradas", WS_VISIBLE | WS_CHILD, 50, 100, 400, 20, hWndParent, NULL, NULL, NULL);
   
    g_vecChildControls.push_back(hLabel);
}
void CreateView7(HWND hWndParent) {
    
    HWND hLabel = CreateWindow(L"STATIC", L"Perfil de Usuario: Juan Pérez", WS_VISIBLE | WS_CHILD, 50, 100, 400, 20, hWndParent, NULL, NULL, NULL);
    HWND hButton = CreateWindow(L"BUTTON", L"Editar Perfil", WS_VISIBLE | WS_CHILD, 50, 180, 150, 30, hWndParent, NULL, NULL, NULL);

    g_vecChildControls.push_back(hLabel);
    g_vecChildControls.push_back(hButton);
}
void CreateViewOpcion1(HWND hWndParent) {

    HWND hLabel = CreateWindow(L"STATIC", L"Aqui puede consultar los valores de referencia de los alquileres", WS_VISIBLE | WS_CHILD, 50, 50, 400, 40, hWndParent, NULL, NULL, NULL);

    g_vecChildControls.push_back(hLabel);
}
void CreateViewOpcion2(HWND hWndParent) {

    HWND hLabel = CreateWindow(L"STATIC", L"Aqui puede solicitar su compensacion", WS_VISIBLE | WS_CHILD, 50, 50, 400, 20, hWndParent, NULL, NULL, NULL);

    g_vecChildControls.push_back(hLabel);
}
void CreateViewOpcion3(HWND hWndParent) {

    HWND hLabel = CreateWindow(L"STATIC", L"Aqui puede solicitar una exncion por ser adulto mayor o vulnerble socialmente", WS_VISIBLE | WS_CHILD, 50, 50, 400, 50, hWndParent, NULL, NULL, NULL);

    g_vecChildControls.push_back(hLabel);
}
void CreateViewOpcion4(HWND hWndParent) {

    HWND hLabel = CreateWindow(L"STATIC", L"Aqui puede trasnferir su credito", WS_VISIBLE | WS_CHILD, 50, 50, 400, 20, hWndParent, NULL, NULL, NULL);

    g_vecChildControls.push_back(hLabel);
}

// ----- WndProc de la Ventana Secundaria -----
LRESULT CALLBACK SecondaryWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
    {
		// Al crear la ventana secundaria, generamos los botones y el botón de regreso
		generarBotones(hwnd);
        CreateWindow(L"BUTTON", L"Regresar al Menú", WS_VISIBLE | WS_CHILD, 150, 300, 180, 40, hwnd, (HMENU)ID_BUTTON_RETURN_TO_MAIN, NULL, NULL);
        break;
    }

    case WM_APP_CHANGE_VIEW:
    {
        DestroyChildControls();

        // Leemos qué vista nos pidieron cargar (el ID del botón que pasamos en SendMessage)
        int viewId = (int)wParam;

        // Creamos la nueva interfaz según el ID.
        switch (viewId) {
        case ID_BUTTON_SHOW_VIEW1:
            CreateView1(hwnd);
            SetWindowText(hwnd, L"Rentas Cordoba"); 
            break;
        case ID_BUTTON_SHOW_VIEW2:
            CreateView2(hwnd);
            SetWindowText(hwnd, L"Rentas Cordoba"); 
            break;
        case ID_BUTTON_SHOW_VIEW3:
            CreateView3(hwnd);
            SetWindowText(hwnd, L"Rentas Cordoba"); 
            break;
        case ID_BUTTON_SHOW_VIEW4:
            CreateView4(hwnd);
            SetWindowText(hwnd, L"Rentas Cordoba"); 
            break;
        case ID_BUTTON_SHOW_VIEW5:
            CreateView5(hwnd);
            SetWindowText(hwnd, L"Rentas Cordoba");
            break;
        case ID_BUTTON_SHOW_VIEW6:
            CreateView6(hwnd);
            SetWindowText(hwnd, L"Rentas Cordoba");
            break;
        case ID_BUTTON_SHOW_VIEW7:
            CreateView7(hwnd);
            SetWindowText(hwnd, L"Rentas Cordoba"); 
            break;
		case ID_MENU_OPCION1:
            CreateViewOpcion1(hwnd);
            SetWindowText(hwnd, L"Rentas Cordoba"); 
            break;
        case ID_MENU_OPCION2:
            CreateViewOpcion2(hwnd);
            SetWindowText(hwnd, L"Rentas Cordoba"); 
            break;
        case ID_MENU_OPCION3:
            CreateViewOpcion3(hwnd);
            SetWindowText(hwnd, L"Rentas Cordoba"); 
            break;
        case ID_MENU_OPCION4:
            CreateViewOpcion4(hwnd);
            SetWindowText(hwnd, L"Rentas Cordoba"); 
            break;
        }
        break;
    }

    case WM_COMMAND:
    {
        // Manejamos el comando del botón de regreso y de los demas botones
        int wmId = LOWORD(wParam);
        HMENU hMenu = CreatePopupMenu();
        RECT rect;
        switch (wmId) {
        case ID_BUTTON_SHOW_VIEW1:
            ShowWindow(g_hwndMain, SW_HIDE);

            SendMessage(g_hwndSecondary, WM_APP_CHANGE_VIEW, (WPARAM)wmId, 0);

            ShowWindow(g_hwndSecondary, SW_SHOW);
            break;
        case ID_BUTTON_SHOW_VIEW2:
            ShowWindow(g_hwndMain, SW_HIDE);

            SendMessage(g_hwndSecondary, WM_APP_CHANGE_VIEW, (WPARAM)wmId, 0);

            ShowWindow(g_hwndSecondary, SW_SHOW);
            break;
        case ID_BUTTON_SHOW_VIEW3:
            ShowWindow(g_hwndMain, SW_HIDE);

            SendMessage(g_hwndSecondary, WM_APP_CHANGE_VIEW, (WPARAM)wmId, 0);

            ShowWindow(g_hwndSecondary, SW_SHOW);
            break;
        case ID_BUTTON_SHOW_VIEW4:
            ShowWindow(g_hwndMain, SW_HIDE);

            SendMessage(g_hwndSecondary, WM_APP_CHANGE_VIEW, (WPARAM)wmId, 0);

            ShowWindow(g_hwndSecondary, SW_SHOW);
            break;
        case ID_BUTTON_SHOW_VIEW5:
            ShowWindow(g_hwndMain, SW_HIDE);

            SendMessage(g_hwndSecondary, WM_APP_CHANGE_VIEW, (WPARAM)wmId, 0);

            ShowWindow(g_hwndSecondary, SW_SHOW);
            break;
        case ID_BUTTON_SHOW_VIEW6:
            ShowWindow(g_hwndMain, SW_HIDE);

            SendMessage(g_hwndSecondary, WM_APP_CHANGE_VIEW, (WPARAM)wmId, 0);

            ShowWindow(g_hwndSecondary, SW_SHOW);
            break;
        case ID_BUTTON_SHOW_VIEW7:
            ShowWindow(g_hwndMain, SW_HIDE);

            SendMessage(g_hwndSecondary, WM_APP_CHANGE_VIEW, (WPARAM)wmId, 0);

            ShowWindow(g_hwndSecondary, SW_SHOW);
            break;

        case ID_BUTTON_SHOW_VIEW8:



            AppendMenuW(hMenu, MF_STRING, ID_MENU_OPCION1, L"Valores de Ref...");
            AppendMenuW(hMenu, MF_STRING, ID_MENU_OPCION2, L"Compensacion");
            AppendMenuW(hMenu, MF_STRING, ID_MENU_OPCION3, L"Exencion...");
            AppendMenuW(hMenu, MF_STRING, ID_MENU_OPCION4, L"Transferencia");

            AppendMenuW(hMenu, MF_SEPARATOR, ID_MENU_SEPARADOR, NULL);


            GetWindowRect(g_hDropdownButton, &rect);


            TrackPopupMenuEx(hMenu, TPM_LEFTALIGN | TPM_TOPALIGN, rect.left, rect.bottom, hwnd, NULL);

            DestroyMenu(hMenu);
            break;
        case ID_MENU_OPCION1:
            ShowWindow(g_hwndMain, SW_HIDE);

            SendMessage(g_hwndSecondary, WM_APP_CHANGE_VIEW, (WPARAM)wmId, 0);

            ShowWindow(g_hwndSecondary, SW_SHOW);
            break;
        case ID_MENU_OPCION2:
            ShowWindow(g_hwndMain, SW_HIDE);

            SendMessage(g_hwndSecondary, WM_APP_CHANGE_VIEW, (WPARAM)wmId, 0);

            ShowWindow(g_hwndSecondary, SW_SHOW);
            break;
        case ID_MENU_OPCION3:
            ShowWindow(g_hwndMain, SW_HIDE);

            SendMessage(g_hwndSecondary, WM_APP_CHANGE_VIEW, (WPARAM)wmId, 0);

            ShowWindow(g_hwndSecondary, SW_SHOW);
            break;
        case ID_MENU_OPCION4:
            ShowWindow(g_hwndMain, SW_HIDE);

            SendMessage(g_hwndSecondary, WM_APP_CHANGE_VIEW, (WPARAM)wmId, 0);

            ShowWindow(g_hwndSecondary, SW_SHOW);
            break;
		case ID_BUTTON_RETURN_TO_MAIN:
			ShowWindow(g_hwndSecondary, SW_HIDE);
			ShowWindow(g_hwndMain, SW_SHOW);
			break;
        } 
	}break;
    case WM_CLOSE:
        DestroyWindow(g_hwndMain);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}