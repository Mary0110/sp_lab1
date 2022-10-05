
// lab1.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "lab1.h"
#include <string>


#define MAX_LOADSTRING 100
enum  operation { ADD, SUB, MULT, REM };
operation op = ADD;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB1));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = CreateSolidBrush(RGB(243,207,198));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));


    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable
  
   //param 6,7 - window size
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW| WS_CAPTION|WS_SYSMENU|WS_MAXIMIZEBOX,
      CW_USEDEFAULT, 0,410,110,NULL,NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    //static HWND hButton1, hButton2, hEdit;

    switch (message)
    {
    case WM_CREATE:
    {
        CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT("0"), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
            20, 10, 85, 25, hWnd, (HMENU)IDC_LHS, GetModuleHandle(NULL), NULL);
        CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT("0"), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
            175, 10, 85, 25, hWnd, (HMENU)IDC_RHS, GetModuleHandle(NULL), NULL);
        CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT("0"), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
            290, 10, 85, 25, hWnd, (HMENU)IDC_RESULT, GetModuleHandle(NULL), NULL);
        CreateWindowEx(NULL, TEXT("BUTTON"), TEXT("+"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP,
            125, 10, 30, 25, hWnd, (HMENU)IDC_OPBUTTON, GetModuleHandle(NULL), NULL);

        break;
        //hButton2 = CreateWindow(L"button", L"Нижняя кнопка", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
       //     150, 150, 150, 30, hWnd, (HMENU)BUTTON_2, hInst, NULL);
       // hEdit = CreateWindow(L"edit", L"Text", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
        //    400, 400, 300, 30, hWnd, (HMENU)EDIT_ID, hInst, NULL);
       // return 0;



    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case IDM_ADD:
            SetDlgItemText(hWnd, IDC_OPBUTTON, TEXT("+"));
            op = ADD;
            break;
        case IDM_SUB:
            SetDlgItemText(hWnd, IDC_OPBUTTON, TEXT("-"));
            op = SUB;
            break;
        case IDM_MULT:
            SetDlgItemText(hWnd, IDC_OPBUTTON, TEXT("*"));
            op = MULT;
            break;
        case IDM_REM:
            SetDlgItemText(hWnd, IDC_OPBUTTON, TEXT("%"));
            op = REM;
            break;
            // case IDM_SUB:
        case IDC_OPBUTTON:
        {
            BOOL success = false;
            int lhs = GetDlgItemInt(hWnd, IDC_LHS, &success, true);
           //  std::string test1 = std::to_string(lhs);
           // MessageBoxA(hWnd, test1.c_str(), "testx", MB_OK);
            SendMessage((HWND)lParam, BM_SETSTATE, TRUE, 0L);


            if (!success) {
                MessageBox(hWnd, TEXT("The first expression is incorrect"), TEXT("Error"), MB_OK);
                break;
            }
            int rhs = GetDlgItemInt(hWnd, IDC_RHS, &success, true);
            //std::string test2 = std::to_string(rhs);
           // MessageBoxA(hWnd, test2.c_str(), "testx", MB_OK);

            if (!success) {
                MessageBox(hWnd, TEXT("The second expression is incorrect"), TEXT("Error"), MB_OK);
                break;
            }
            int result = 0;
            switch (op) {
            case ADD:
                result = lhs + rhs;
                break;
            case SUB:
                result = lhs - rhs;
                break;
            case MULT:
                result = lhs * rhs;
                break;
            case REM:
                if (rhs == 0) {
                    SetDlgItemText(hWnd, IDC_RESULT, TEXT("UNDERFINED"));
                    return 0;
                }
                else {
                    result = lhs % rhs;
                }

            }

            SetDlgItemInt(hWnd, IDC_RESULT, result, true);
            break;
        }

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        MoveToEx(hdc, 270, 20, NULL);
        LineTo(hdc, 280, 20);
        MoveToEx(hdc, 270, 25, NULL);
        LineTo(hdc, 280, 25);
        //  Add any drawing code that uses hdc here...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
    }
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
