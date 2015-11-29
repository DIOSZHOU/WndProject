#ifndef STATUS_BAR_H_8A193A27_DA2F_49f6_9D81_0805103A8E87
#define STATUS_BAR_H_8A193A27_DA2F_49f6_9D81_0805103A8E87
/*
*************************************************************************
ģ����  : Status Bar Reference
�ļ���  : StatusBar.h    
ʵ�ֹ���: StatusBar
����    : �ܽ�
�汾    : 
����	��
-------------------------------------------------------------------------
��ע    :
-------------------------------------------------------------------------
�޸ļ�¼:   
��  ��          �汾        �޸���      �޸�����

*************************************************************************
* �汾����(c)  <2014.8.17>  ��������Ȩ��                                     *
************************************************************************/
#include <windows.h>
#include <commctrl.h>
#include <tchar.h>

#define STATUEBAR_PART_NUM		3		
#pragma comment(lib,"comctl32.lib")

namespace GuiLib
{
	class CStatusBar
	{
	public:
		CStatusBar(HWND hParent, HMENU hMenu, HINSTANCE hInst);
		~CStatusBar();

	public:
		virtual BOOL Create(int x, int y, int iWidth, int iHeight, DWORD dwStyle, int nParts);
		virtual BOOL OnSize(HWND hWnd, UINT uMsg, WPARAM wParam,LPARAM lParam);
		
	public:
		VOID SetText(int nParts, LPTSTR lpText);
		HWND GetHwnd() {return m_hwndStatus;}
	private:
		HMENU m_hMenu;
		HWND m_hParent;
		HINSTANCE m_hInst;
		HWND m_hwndStatus;
		HLOCAL m_hLoc;
	};
}

#endif