#include "ToolBar.h"

namespace GuiLib
{
	CToolBar::CToolBar(HWND hParent, HMENU hMenu, HINSTANCE hInst):m_hParent(hParent), m_hMenu(hMenu), m_hInst(hInst)
	{
		INITCOMMONCONTROLSEX icex;
		icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
		icex.dwICC = ICC_BAR_CLASSES;
		InitCommonControlsEx(&icex);

		ZeroMemory(&m_tbab, sizeof(m_tbab));
		ZeroMemory(m_tBtn, STD_CTRL_NUMER);
		m_iStdbmp[0] = STD_FILENEW;
		m_iStdbmp[1] = STD_FILEOPEN;
		m_iStdbmp[2] = STD_FILESAVE;
		m_iStdbmp[3] = STD_PRINT;
		m_iStdbmp[4] = STD_COPY;
		m_iStdbmp[5] = STD_PASTE;
	}

	CToolBar::~CToolBar()
	{

	}

	BOOL CToolBar::Create(int x, int y, int nWidth, int nHeight, DWORD dwStyle, int nIndex[], int nSize)
	{
		BOOL bRet = FALSE;
		m_hwndTB = CreateWindowEx(0, TOOLBARCLASSNAME, NULL, dwStyle, x, y, nWidth, nHeight, m_hParent, m_hMenu, m_hInst, NULL); 
		if (!m_hwndTB)
		{
			goto cleanup;
		}
		// Send the TB_BUTTONSTRUCTSIZE message, which is required for 
		// backward compatibility. 
		SendMessage(m_hwndTB, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
		m_tbab.hInst = HINST_COMMCTRL;  
		m_tbab.nID = IDB_STD_LARGE_COLOR;  
		SendMessage(m_hwndTB, TB_ADDBITMAP, 0, (LPARAM)&m_tbab);  

		for (int i = 0; i < nSize; i++)
		{
			m_tBtn[i].iBitmap = m_iStdbmp[i];
			m_tBtn[i].idCommand = nIndex[i];
			m_tBtn[i].fsState = TBSTATE_ENABLED;
			m_tBtn[i].fsStyle = TBSTYLE_TOOLTIPS;
			m_tBtn[i].dwData = 0;
			m_tBtn[i].iString = NULL;
		}
		SendMessage(m_hwndTB, TB_ADDBUTTONS, (WPARAM)nSize,(LPARAM) (LPTBBUTTON) &m_tBtn);
		SendMessage(m_hwndTB, TB_AUTOSIZE, 0, 0);
		ShowWindow(m_hwndTB, SW_SHOW);
		bRet = TRUE;
cleanup:	
		return bRet;
	}

	BOOL CToolBar::OnSize(HWND hWnd, UINT uMsg, WPARAM wParam,LPARAM lParam)
	{
		if (m_hwndTB)
		{
			return MoveWindow(m_hwndTB, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);  
		}
		return false;
	}
}