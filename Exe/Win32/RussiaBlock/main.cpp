// RussiaBlock.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "RussiaGame.h"

#define MAX_LOADSTRING 100

TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
 	// TODO: �ڴ˷��ô��롣
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



