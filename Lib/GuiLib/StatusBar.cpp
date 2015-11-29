#include "StatusBar.h"

namespace GuiLib
{
	CStatusBar::CStatusBar(HWND hParent, HMENU hMenu, HINSTANCE hInst):m_hParent(hParent), m_hMenu(hMenu), m_hInst(hInst)
	{
		INITCOMMONCONTROLSEX icex;
		icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
		icex.dwICC = ICC_BAR_CLASSES;
		InitCommonControlsEx(&icex);

		
	}

	CStatusBar::~CStatusBar()
	{

	}

	BOOL CStatusBar::Create(int x, int y, int iWidth, int iHeight, DWORD dwStyle, int nParts)
	{
		BOOL bRet = FALSE;
		LPINT lpParts;
		RECT rcClient;
		int nWidth = 0;
		m_hwndStatus = CreateWindowEx(0, STATUSCLASSNAME, NULL, dwStyle, x, y, iWidth, iHeight, m_hParent, m_hMenu, m_hInst, NULL); 
		if (!m_hwndStatus)
		{
			return bRet;
		}
		GetClientRect(m_hParent, &rcClient);
		//allocates the specified number of bytes from the heap
		m_hLoc = LocalAlloc(LHND, sizeof(int) * nParts);
		lpParts = (LPINT)LocalLock(m_hLoc);
		nWidth = (rcClient.right - rcClient.left) / nParts;
		for (int i = 0; i < nParts; i++)
		{
			lpParts[i] = nWidth;
			nWidth += nWidth;
		}
		SendMessage(m_hwndStatus, SB_SETPARTS, (WPARAM)nParts, (LPARAM)lpParts);
		LocalUnlock(m_hLoc);
		LocalFree(m_hLoc);
		bRet = TRUE;
		return bRet;
	}

	VOID CStatusBar::SetText(int nParts, LPTSTR lpText)
	{
		SendMessage(m_hwndStatus, SB_SETTEXT, (WPARAM)nParts, (LPARAM)lpText);
	}

	BOOL CStatusBar::OnSize(HWND hWnd, UINT uMsg, WPARAM wParam,LPARAM lParam)
	{
		if (m_hwndStatus)
		{
			return MoveWindow(m_hwndStatus, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);  
		}
		return false;
	}
}
