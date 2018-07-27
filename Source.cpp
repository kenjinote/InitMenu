#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <windows.h>
#include "resource.h"

TCHAR szClassName[] = TEXT("Window");

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hButton1;
	static HWND hButton2;
	static HWND hButton3;
	static HFONT hFont;
	switch (msg)
	{
	case WM_CREATE:
		hFont = CreateFontW(-MulDiv(10, 96, 72), 0, 0, 0, FW_NORMAL, 0, 0, 0, SHIFTJIS_CHARSET, 0, 0, 0, 0, L"MS Shell Dlg");
		hButton1 = CreateWindow(TEXT("BUTTON"), TEXT("item1"), WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 0, 0, 0, 0, hWnd, 0, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		SendMessage(hButton1, WM_SETFONT, (WPARAM)hFont, 0);
		SendMessage(hButton1, BM_SETCHECK, BST_CHECKED, 0);
		hButton2 = CreateWindow(TEXT("BUTTON"), TEXT("item2"), WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 0, 0, 0, 0, hWnd, 0, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		SendMessage(hButton2, WM_SETFONT, (WPARAM)hFont, 0);
		SendMessage(hButton2, BM_SETCHECK, BST_CHECKED, 0);
		hButton3 = CreateWindow(TEXT("BUTTON"), TEXT("item3"), WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 0, 0, 0, 0, hWnd, 0, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		SendMessage(hButton3, WM_SETFONT, (WPARAM)hFont, 0);
		SendMessage(hButton3, BM_SETCHECK, BST_CHECKED, 0);
		break;
	case WM_SIZE:
		MoveWindow(hButton1, 10, 10, 256, 32, TRUE);
		MoveWindow(hButton2, 10, 50, 256, 32, TRUE);
		MoveWindow(hButton3, 10, 90, 256, 32, TRUE);
		break;
	case WM_INITMENU:
		{
			const BOOL bItem1 = (BOOL)SendMessage(hButton1, BM_GETCHECK, 0, 0);
			const BOOL bItem2 = (BOOL)SendMessage(hButton2, BM_GETCHECK, 0, 0);
			const BOOL bItem3 = (BOOL)SendMessage(hButton3, BM_GETCHECK, 0, 0);
			EnableMenuItem((HMENU)wParam, ID_MENU_ITEM1, bItem1 ? MF_ENABLED : MF_DISABLED);
			EnableMenuItem((HMENU)wParam, ID_MENU_ITEM2, bItem2 ? MF_ENABLED : MF_DISABLED);
			EnableMenuItem((HMENU)wParam, ID_MENU_ITEM3, bItem3 ? MF_ENABLED : MF_DISABLED);
		}
		break;
	case WM_DESTROY:
		DeleteObject(hFont);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR pCmdLine, int nCmdShow)
{
	MSG msg;
	WNDCLASS wndclass = {
		CS_HREDRAW | CS_VREDRAW,
		WndProc,
		0,
		0,
		hInstance,
		0,
		LoadCursor(0,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		MAKEINTRESOURCE(IDR_MENU1),
		szClassName
	};
	RegisterClass(&wndclass);
	HWND hWnd = CreateWindow(
		szClassName,
		TEXT("Window"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		0,
		0,
		hInstance,
		0
	);
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}
