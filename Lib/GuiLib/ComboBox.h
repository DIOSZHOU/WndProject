#ifndef COMBO_BOX_D98B562B_02B8_48e7_87BE_7132F9A6F40C
#define COMBO_BOX_D98B562B_02B8_48e7_87BE_7132F9A6F40C
/*
*************************************************************************
模块名  : Combo Boxes
文件名  : ComboBox.h    
实现功能: ComboBox controls 
作者    : 周健
版本    : 
关于	：
There are three types of combo boxes: 
Simple combo boxes (CBS_SIMPLE)
Drop-down combo boxes (CBS_DROPDOWN)
Drop-down list boxes (CBS_DROPDOWNLIST)
-------------------------------------------------------------------------
备注    :
-------------------------------------------------------------------------
修改记录:   
日  期          版本        修改人      修改内容

*************************************************************************
* 版本所有(c)  <2014.8.19>  保留所有权利                                *
************************************************************************/

#include <Windows.h>
#include <commctrl.h>
#include <tchar.h>

#pragma comment(lib,"comctl32.lib")

namespace GuiLib
{
	class CComboBox
	{
	public:
		CComboBox(HWND hParent, HMENU hMenu, HINSTANCE hInst);
		~CComboBox();

	public:
		virtual BOOL Create(int x, int y, int nWidth, int nHeight, DWORD dwStyle);
		static LRESULT CALLBACK SubClassProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		BOOL OnSize(HWND hWnd, UINT uMsg, WPARAM wParam,LPARAM lParam);
		HWND GetCBoxHandle() {return m_hComboBox;}

	private:
		HMENU m_hMenu;
		HWND m_hParent;
		HINSTANCE m_hInst;
		HWND m_hComboBox;
		HWND m_hwndEdit;
		WNDPROC m_lpfnEditWndProc; 
	};
}

#endif