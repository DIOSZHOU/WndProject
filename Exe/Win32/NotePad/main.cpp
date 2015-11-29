#include "stdafx.h"
#include "NotePad.h"

#define MAX_LOADSTRING 100
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_NOTEPAD, szWindowClass, MAX_LOADSTRING);
	LPTSTR szMenu = MAKEINTRESOURCE(IDC_NOTEPAD);
	HICON hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_NOTEPAD));
	HCURSOR hCursor = LoadCursor(NULL, IDC_ARROW);
	HICON hIconSmall = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_NOTEPAD));
	CNotePad MyNotePad(szWindowClass, szTitle);
	MyNotePad.Create(hInstance, NULL, nCmdShow, hIcon, hCursor, hIconSmall, hAccelTable, 
		szMenu, 300, 100, 800, 600, NOTEPAD_WND);
	return MyNotePad.Run();
}