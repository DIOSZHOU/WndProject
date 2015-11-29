#include "Edit.h"
#include <WindowsX.h>

namespace GuiLib
{
	CEdit::CEdit(HWND hParent, HMENU hMenu, HINSTANCE hInst, HFONT hFont) 
		: m_hParent(hParent), m_hMenu(hMenu), m_hInst(hInst), m_hFont(hFont)
	{
		m_hEdit = NULL;
	}

	CEdit::~CEdit()
	{

	}

	BOOL CEdit::Create(int x, int y, int nWidth, int nHeight, DWORD dwStyle)
	{
		BOOL bRet = false;
		m_hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), dwStyle, x, y, nWidth, nHeight, m_hParent, m_hMenu, m_hInst, LPVOID(this));
		SetWindowLong(m_hEdit, GWL_USERDATA,(LONG)this);
		m_pfnPrevWndProc = (WNDPROC)SetWindowLong(m_hEdit, GWL_WNDPROC, (long)WndProc);	//替换窗口过程,保存原来过程
		if (m_hEdit)
		{
			bRet = true;
			SendMessage(m_hEdit, WM_SETFONT, (WPARAM)m_hFont, true);
			m_ShortCutMenu = new CShortCutMenu(m_hMenu);
		}
		return bRet;
	}

	INT_PTR CALLBACK CEdit::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		BOOL bRet = FALSE;
		CEdit* pEdit = reinterpret_cast<CEdit*>(::GetWindowLong(hWnd, GWL_USERDATA));
		switch (message)
		{
		case WM_RBUTTONUP:
			{
				bRet = pEdit->OnRbuttonUp(hWnd, message, wParam, lParam);
			}
			break;
		case WM_GETTEXT:
			break;
		case EM_CHARFROMPOS:
			bRet = 1;
			break;
		default:
			return CallWindowProc(pEdit->m_pfnPrevWndProc, hWnd, message, wParam, lParam);
		}
		return bRet;
	}

	BOOL CEdit::OnRbuttonUp(HWND hWnd, UINT uMsg, WPARAM wParam,LPARAM lParam)
	{
		BOOL bRet = false;
		RECT rc;
		POINT pt;
		GetClientRect(hWnd, (LPRECT) &rc); 
		pt.x = GET_X_LPARAM(lParam); 
		pt.y = GET_Y_LPARAM(lParam); 
		if (PtInRect((LPRECT)&rc, pt))
		{
			bRet = m_ShortCutMenu->DisplayShortCutMenu(m_hParent, pt, 1);
		}
		return bRet;
	}

	BOOL CEdit::OnSize(HWND hWnd, UINT uMsg, WPARAM wParam,LPARAM lParam)
	{
		if (m_hEdit)
		{
			RECT rct;
			GetClientRect(hWnd, &rct);
			int nWidth = rct.right - rct.left;
			int nHigh = rct.bottom - rct.top;
			return MoveWindow(m_hEdit, rct.left, rct.top + 31, nWidth, nHigh - 60, TRUE);  
		}
		return false;
	}


	BOOL CEdit::SetText(LPTSTR &m_szSendBuf)
	{
		BOOL bRet = FALSE;
		bRet = SendMessage(m_hEdit, WM_SETTEXT, 0, (LPARAM)m_szSendBuf);
		return bRet;
	}

	BOOL CEdit::GetText(LPTSTR &m_szReadBuf)
	{
		BOOL bRet = FALSE;
		DWORD dTextLenth = GetTextLenth();
		bRet = SendMessage(m_hEdit, WM_GETTEXT,(WPARAM)(dTextLenth + 1),(LPARAM)m_szReadBuf);
		return bRet;
	}

	DWORD CEdit::GetTextLenth()
	{
		return SendMessage(m_hEdit, WM_GETTEXTLENGTH, 0, 0);
	}

	HWND CEdit::GetHwnd()
	{
		return m_hEdit;
	}

	BOOL CEdit::Clear()
	{
		SendMessage(m_hEdit, EM_SETSEL, 0, -1);
		return SendMessage(m_hEdit, WM_CLEAR, 0, 0);
	}

	BOOL CEdit::Copy()
	{
		SendMessage(m_hEdit, EM_SETSEL, 0, -1);
		return SendMessage(m_hEdit, WM_COPY, 0, 0);
	}

	BOOL CEdit::Paste()
	{
		SendMessage(m_hEdit, EM_SETSEL, 0, -1);
		return SendMessage(m_hEdit, WM_PASTE, 0, 0);
	}

	
	CRichEdit::CRichEdit(HWND hParent, HMENU hMenu, HINSTANCE hInst, HFONT hFont) : CEdit(hParent, hMenu, hInst, hFont)
	{
		m_hRichEditDll = LoadLibrary(_T("Riched20.dll"));

		ZeroMemory(&m_sFormat, sizeof(m_sFormat));
	}

	CRichEdit::~CRichEdit()
	{
		FreeLibrary(m_hRichEditDll);
	}

	BOOL CRichEdit::Create(int x, int y, int nWidth, int nHeight, DWORD dwStyle)
	{
		BOOL bRet = FALSE;
		m_hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, RICHEDIT_CLASS, _T(""), dwStyle, x, y, nWidth, nHeight, m_hParent, m_hMenu, m_hInst, LPVOID(this));
		SetWindowLong(m_hEdit, GWL_USERDATA,(LONG)this);
		m_pfnPrevWndProc = (WNDPROC)SetWindowLong(m_hEdit, GWL_WNDPROC, (long)WndProc);	//替换窗口过程,保存原来过程
		if (m_hEdit)
		{
			bRet = true;
			SendMessage(m_hEdit, WM_SETFONT, (WPARAM)m_hFont, true);
			m_ShortCutMenu = new CShortCutMenu(m_hMenu);
		}
		SendMessage(m_hEdit, EM_SETEVENTMASK, 0, ENM_MOUSEEVENTS);
		if (m_hEdit)
		{
			bRet = TRUE;
		}
		return bRet;
	}

	INT_PTR CALLBACK CRichEdit::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		BOOL bRet = FALSE;
		CRichEdit* pEdit = reinterpret_cast<CRichEdit*>(::GetWindowLong(hWnd, GWL_USERDATA));
		switch (message)
		{
		case WM_RBUTTONUP:
			{
				bRet = pEdit->OnRbuttonUp(hWnd, message, wParam, lParam);
			}
			break;
		case WM_MOUSEMOVE:	//发送鼠标坐标给到父窗口，然后还是要处理WM_MOUSEMOVE,不然选择文字没作用
			{
				SendMessage(pEdit->m_hParent, WM_NOTIFY, (WPARAM)CRICH_EDIT, lParam);
			}
			//break;
		default:
			return CallWindowProc(pEdit->m_pfnPrevWndProc, hWnd, message, wParam, lParam);
		}
		return bRet;
	}

	BOOL CRichEdit::OnRbuttonUp(HWND hWnd, UINT uMsg, WPARAM wParam,LPARAM lParam)
	{
		BOOL bRet = false;
		RECT rc;
		POINT pt;
		GetClientRect(hWnd, (LPRECT) &rc); 
		pt.x = GET_X_LPARAM(lParam); 
		pt.y = GET_Y_LPARAM(lParam); 
		if (PtInRect((LPRECT)&rc, pt))
		{
			bRet = m_ShortCutMenu->DisplayShortCutMenu(m_hParent, pt, 2);
		}
		return bRet;
	}

	VOID CRichEdit::SetFont(CHOOSEFONT &cFontInfor)
	{
		m_sFormat.cbSize = sizeof CHARFORMAT;
		m_sFormat.dwMask = CHAR_FORMAT_DWMASK;
		m_sFormat.dwEffects = CFE_BOLD;
		m_sFormat.yHeight = cFontInfor.lpLogFont->lfHeight * 20;
		m_sFormat.yOffset = 0;
		m_sFormat.crTextColor = cFontInfor.rgbColors;
		m_sFormat.bCharSet = cFontInfor.lpLogFont->lfCharSet;
		m_sFormat.bPitchAndFamily = cFontInfor.lpLogFont->lfPitchAndFamily;
		memcpy(m_sFormat.szFaceName, cFontInfor.lpLogFont->lfFaceName, LF_FACESIZE);
		SendMessage(m_hEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)(&m_sFormat));
	}
}
