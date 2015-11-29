#ifndef COMBO_BOX_D98B562B_02B8_48e7_87BE_7132F9A6F40C
#define COMBO_BOX_D98B562B_02B8_48e7_87BE_7132F9A6F40C
/*
*************************************************************************
ģ����  : Combo Boxes
�ļ���  : ComboBox.h    
ʵ�ֹ���: ComboBox controls 
����    : �ܽ�
�汾    : 
����	��
There are three types of combo boxes: 
Simple combo boxes (CBS_SIMPLE)
Drop-down combo boxes (CBS_DROPDOWN)
Drop-down list boxes (CBS_DROPDOWNLIST)
-------------------------------------------------------------------------
��ע    :
-------------------------------------------------------------------------
�޸ļ�¼:   
��  ��          �汾        �޸���      �޸�����

*************************************************************************
* �汾����(c)  <2014.8.19>  ��������Ȩ��                                *
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