// RussiaBlock.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "RussiaGame.h"

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
 	// TODO: 在此放置代码。
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_RUSSIABLOCK, szWindowClass, MAX_LOADSTRING);
	LPTSTR szMenu = MAKEINTRESOURCE(IDC_MENU_RUSSIABLOCK);
	HICON hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_RUSSIABLOCK));
	HCURSOR hCursor = LoadCursor(NULL, IDC_ARROW);
	HICON hIconSmall = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_RUSSIABLOCK));

	CRussiaGame MyRussia(szWindowClass, szTitle);
	MyRussia.Create(hInstance, NULL, nCmdShow, hIcon, hCursor, hIconSmall, hAccelTable, 
		szMenu, 400, 100, 500, 600, RUSSIAGAME_WND_STYLY);
	return MyRussia.Run();
}



