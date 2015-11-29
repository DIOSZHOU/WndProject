#include "ComboBox.h"

namespace GuiLib
{
	CComboBox::CComboBox(HWND hParent, HMENU hMenu, HINSTANCE hInst)
		: m_hParent(hParent), m_hMenu(hMenu), m_hInst(hInst)
	{
		INITCOMMONCONTROLSEX icex;
		icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
		icex.dwICC = ICC_BAR_CLASSES;
		InitCommonControlsEx(&icex);
	}
	
	CComboBox::~CComboBox()
	{

	}

	BOOL CComboBox::Create(int x, int y, int nWidth, int nHeight, DWORD dwStyle)
	{
		BOOL bRet = FALSE;
		POINT pt = {1, 1}; 
		m_hComboBox = CreateWindowEx(0, _T("COMBOBOX"), _T(""), dwStyle, x, y, nWidth, nHeight, m_hParent, NULL, m_hInst, LPVOID(this));
		//SendMessage(m_hComboBox,CB_SHOWDROPDOWN,TRUE,0);//下拉
		// Get the edit window handle to each combo box. 
		//m_hwndEdit = ChildWindowFromPoint(m_hComboBox, pt); 
		// Change the window procedure for both edit windows 
		// to the subclass procedure. 
		SetWindowLong(m_hComboBox, GWL_USERDATA,(LONG)this);
		m_lpfnEditWndProc = reinterpret_cast<WNDPROC>(SetWindowLong(m_hwndEdit, GWL_WNDPROC, (long)SubClassProc));	//替换窗口过程,保存原来过程
		return bRet;
	}

	LRESULT CComboBox::SubClassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		BOOL bRet = FALSE;
		CComboBox* pComboBox = reinterpret_cast<CComboBox*>(::GetWindowLong(hWnd, GWL_USERDATA));
		switch (uMsg) 
		{ 
		case WM_KEYDOWN: 
			switch (wParam) 
			{ 
			case VK_TAB: 
				//SendMessage(m_hParent, WM_TAB, 0, 0); 
				return 0; 
			case VK_ESCAPE: 
				//SendMessage(m_hParent, WM_ESC, 0, 0); 
				return 0; 
			case VK_RETURN: 
				//SendMessage(m_hParent, WM_ENTER, 0, 0); 
				return 0; 
			} 
			break; 

		case WM_KEYUP: 
		case WM_CHAR: 
			switch (wParam) 
			{ 
			case VK_TAB: 
			case VK_ESCAPE: 
			case VK_RETURN: 
				return 0; 
			} 
		}

		return CallWindowProc(pComboBox->m_lpfnEditWndProc, hWnd, uMsg, wParam, lParam);
	}

	BOOL CComboBox::OnSize(HWND hWnd, UINT uMsg, WPARAM wParam,LPARAM lParam)
	{
		if (m_hComboBox)
		{
			return MoveWindow(m_hComboBox, 0, 0, LOWORD(lParam) - 200, 200, TRUE);  
		}
		return false;
	}
}