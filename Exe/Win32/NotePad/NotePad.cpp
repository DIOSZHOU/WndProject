// NotePad.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "NotePad.h"

CNotePad::CNotePad(LPCTSTR m_lpszClass, LPCTSTR m_lpszName) : CWnd(m_lpszClass, m_lpszName)
{
	CCommonDlg *Comme = NULL;
	m_commenDlg.reserve(COMMONDLG_NUMBER);
	Comme = new COpenDlg;
	m_commenDlg.push_back(Comme);
	Comme = new CBrowsDlg;
	m_commenDlg.push_back(Comme);
	Comme = new CPrintDlg;
	m_commenDlg.push_back(Comme);
	Comme = new CpageSetDlg;
	m_commenDlg.push_back(Comme);
	Comme = new CFontDlg;
	m_commenDlg.push_back(Comme);
	Comme = new CColorDlg;
	m_commenDlg.push_back(Comme);
}

CNotePad::~CNotePad()
{
	if (m_Edit)
	{
		delete m_Edit;
		m_Edit = NULL;
	}
	
}

LRESULT CNotePad::OnCommand(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	BOOL bRet = false;
	int wmId, wmEvent;
	wmId    = LOWORD(wParam);
	wmEvent = HIWORD(wParam);
	switch (wmEvent)
	{
	case EN_CHANGE:
		 bRet = 1;
		break;
	case EN_HSCROLL:
		 bRet = 1;
		break;
	}
	// 分析菜单选择:
	switch (wmId)
	{
		case IDM_ABOUT:
			DialogBox(m_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_NEW:
			bRet = OnFileNew(hWnd, wParam, lParam);
			break;
		case ID_OPEN:
			bRet = OnFileOpen(hWnd, wParam, lParam);
			break;
		case ID_SAVE:
			bRet = OnFileSave(hWnd, wParam, lParam);
			break;
		case ID_SAVEAS:
			bRet = OnFileSaveAs(hWnd, wParam, lParam);
			break;
		case ID_PRINT:
			bRet = OnFilePrint(hWnd, wParam, lParam);
			break;
		case ID_PAGESET:
			bRet = OnPageSet(hWnd, wParam, lParam);
			break;
		case ID_COPY:
			bRet = OnFileCopy(hWnd, wParam, lParam);
			break;
		case ID_PASTE:
			bRet = OnFilePaste(hWnd, wParam, lParam);
			break;
		case ID_COLOR:
			bRet = OnColor(hWnd, wParam, lParam);
			break;
		case ID_FONT:
			bRet = OnFont(hWnd, wParam, lParam);
			break;
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return bRet;
}

INT_PTR CALLBACK CNotePad::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
		case WM_INITDIALOG:
			return (INT_PTR)TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
			{
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
			break;
	}
	return (INT_PTR)FALSE;
}

BOOL CNotePad::OnCreate(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	BOOL bRet = false;
	
	HFONT hFont = CreateFont(15, 0, 0, 0, 50, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, _T("黑体"));
#if 0
	m_Edit = new CEdit(hWnd, ::LoadMenu(m_hInst, MAKEINTRESOURCE(IDC_NOTEPAD)), (HINSTANCE) GetWindowLong(hWnd, GWL_HINSTANCE), hFont);
	if (m_Edit->Create(0, 0, 800, 480, NOTEPAD_EDIT_STYLE))
	{
		bRet = true;
	}
#else
	m_Edit = new CRichEdit(hWnd, ::LoadMenu(m_hInst, MAKEINTRESOURCE(IDC_NOTEPAD)), (HINSTANCE) GetWindowLong(hWnd, GWL_HINSTANCE), hFont);
	RECT rct;
	GetClientRect(hWnd, &rct);
	int nWidth = rct.right - rct.left;
	int nHigh = rct.bottom - rct.top;
	if (m_Edit->Create(0, 31, nWidth, nHigh - 62, NOTEPAD_EDIT_STYLE))
	{
		bRet = true;
	}
#endif
	m_ToolBar = new CToolBar(hWnd, ::LoadMenu(m_hInst, MAKEINTRESOURCE(IDC_NOTEPAD)), (HINSTANCE) GetWindowLong(hWnd, GWL_HINSTANCE));
	int nIndex[] = {ID_NEW, ID_OPEN, ID_SAVEAS, ID_PRINT, ID_COPY, ID_PASTE};
	m_ToolBar->Create(0, 0, 100, 30, NOTEPAD_TOOLBAR_STYLE, nIndex, sizeof(nIndex)/sizeof(int));

	m_StatusBar = new CStatusBar(hWnd, ::LoadMenu(m_hInst, MAKEINTRESOURCE(IDC_NOTEPAD)), (HINSTANCE) GetWindowLong(hWnd, GWL_HINSTANCE));
	m_StatusBar->Create(0, 0, 100, 100, NOTEPAD_STATUSBAR_STYLE, 2);
	//SetParent(m_StatusBar->GetHwnd(), m_hWnd);
	return bRet;
}

BOOL CNotePad::OnSize(HWND hWnd, UINT uMsg, WPARAM wParam,LPARAM lParam)
{
	BOOL bRet = false;
	if (m_Edit->OnSize(hWnd, uMsg, wParam, lParam) 
		&& m_ToolBar->OnSize(hWnd, uMsg, wParam, lParam) 
		&& m_StatusBar->OnSize(hWnd, uMsg, wParam, lParam))
	{
		bRet = true;
	}
	return bRet;
}

BOOL CNotePad::OnFileNew(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL bRet = false;
	if(m_Edit->Clear())
	{
		bRet = true;
	}
	return bRet;
}

BOOL CNotePad::OnFileOpen(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL bRet = false;
	DWORD nHight = 0;
	DWORD nLen = 0;
	CCommonDlg *m_Open = m_commenDlg.at(0);
	if(!m_Open->DoOpen(m_hWnd))	
	{
		return bRet;
	}
	HANDLE hFile = CreateFile(m_Open->GetPath(), GENERIC_READ, 
					FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD nLow = GetFileSize(hFile, &nHight);
	LPTSTR m_lpReadBuf = new TCHAR[nLow + 1];
	ZeroMemory(m_lpReadBuf, nLow + 1);
	if(ReadFile(hFile, m_lpReadBuf, nLow + 1, &nLen, NULL))
	{
		bRet = TRUE;
	}
	/*如果是ANSI BEGIN*/
#if 0
	int nNum = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)m_lpReadBuf, -1, NULL, 0);
	LPTSTR m_lpReadBufUni = new TCHAR[nNum + 1];
	ZeroMemory(m_lpReadBufUni, nNum + 1);
	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)m_lpReadBuf, -1, m_lpReadBufUni, nNum);
	m_Edit->SetText(m_lpReadBufUni);
	if (m_lpReadBufUni)
	{
		delete []m_lpReadBufUni;
		m_lpReadBufUni = NULL;
	}
#else
	/*END*/
	m_Edit->SetText(m_lpReadBuf);
#endif
	CloseHandle( hFile );
	if (m_lpReadBuf)
	{
		delete []m_lpReadBuf;
		m_lpReadBuf = NULL;
	}
	return bRet;
}

BOOL CNotePad::OnFileSave(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL bRet = false;
	DWORD nLow = 0;
	CCommonDlg *m_Open = m_commenDlg.at(0);
	DWORD nLen = m_Edit->GetTextLenth();
	LPTSTR m_lpReadFile = new TCHAR[nLen + 1];
	ZeroMemory(m_lpReadFile, nLen + 1);
	m_Edit->GetText(m_lpReadFile);
	LPTSTR lpFilePath = m_Open->GetPath();
	HANDLE hFile = CreateFile(lpFilePath, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL, NULL );
	if(WriteFile(hFile, m_lpReadFile, nLen + 1, &nLow, NULL))
	{
		bRet = true;
	}
	CloseHandle(hFile);
	if (m_lpReadFile)
	{
		delete []m_lpReadFile;
		m_lpReadFile = NULL;
	}
	return bRet;
}

BOOL CNotePad::OnFileSaveAs(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL bRet = false;
	DWORD nLow = 0;
	CCommonDlg *m_SaveAs = m_commenDlg.at(0);
	DWORD nLen = m_Edit->GetTextLenth();
	LPTSTR m_lpReadFile = new TCHAR[nLen + 1];
	ZeroMemory(m_lpReadFile, nLen + 1);
	m_Edit->GetText(m_lpReadFile);
 	if (!dynamic_cast<COpenDlg*>(m_SaveAs)->DoSaveAs(m_Edit->GetHwnd()))
	{
		return bRet;
	}
	LPTSTR lpFilePath = m_SaveAs->GetPath();
	HANDLE hFile = CreateFile(lpFilePath, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, 
								FILE_ATTRIBUTE_NORMAL, NULL );
	if(WriteFile(hFile, m_lpReadFile, nLen + 1, &nLow, NULL))
	{
		bRet = true;
	}
	CloseHandle(hFile);
	if (m_lpReadFile)
	{
		delete []m_lpReadFile;
		m_lpReadFile = NULL;
	}
	return bRet;
}

BOOL CNotePad::OnFileCopy(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL bRet = false;
	if(m_Edit->Copy())
	{
		bRet = true;
	}
	return bRet;
}

BOOL CNotePad::OnFilePaste(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL bRet = false;
	if(m_Edit->Paste())
	{
		bRet = true;
	}
	return bRet;
}


BOOL CNotePad::OnFilePrint(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL bRet = false;
	CCommonDlg *m_FilePrint = m_commenDlg.at(2);
	if ((dynamic_cast<CPrintDlg*>(m_FilePrint))->DoOpen(hWnd))
	{
		bRet = TRUE;
	}
	return bRet;
}

BOOL CNotePad::OnPageSet(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL bRet = false;
	CCommonDlg *m_PageSet = m_commenDlg.at(3);
	if ((dynamic_cast<CpageSetDlg*>(m_PageSet))->DoOpen(hWnd))
	{
		bRet = TRUE;
	}
	return bRet;
}

BOOL CNotePad::OnColor(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL bRet = false;
	CCommonDlg *m_Color = m_commenDlg.at(5);
	if ((dynamic_cast<CColorDlg*>(m_Color))->DoOpen(hWnd))
	{
		bRet = TRUE;
	}
	return bRet;
}


BOOL CNotePad::OnFont(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL bRet = FALSE;
	CCommonDlg *cfontDlg = m_commenDlg.at(4);
	if(cfontDlg->DoOpen(hWnd))
	{
		CHOOSEFONT chFontInfor;
		(dynamic_cast<CFontDlg*>(cfontDlg))->GetChooseFontValue(chFontInfor);
#if 0
		(dynamic_cast<CFontDlg*>(cfont))->GetFontValue(logfont);
		HFONT hfont = CreateFont(logfont.lfHeight, logfont.lfWidth, logfont.lfEscapement, 
			logfont.lfOrientation, logfont.lfWeight, logfont.lfItalic, logfont.lfUnderline, 
			logfont.lfStrikeOut, logfont.lfCharSet, logfont.lfOutPrecision, logfont.lfClipPrecision,
			logfont.lfQuality, logfont.lfPitchAndFamily, logfont.lfFaceName);
		m_Edit->SetFont(hfont);
#else
		m_Edit->SetFont(chFontInfor);
#endif
		bRet = TRUE;
	}
	return bRet;
}

LRESULT CNotePad::OnMouseMove(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	BOOL bRet = FALSE;
	TCHAR szText[MAX_PATH] = {0};
	_stprintf(szText, _T("X = %d   Y = %d"), LOWORD(lParam), HIWORD(lParam));
	m_StatusBar->SetText(1, szText);
	bRet = TRUE;
	return bRet;
}

LRESULT CNotePad::WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	BOOL bRet = false;
	switch (message)
	{
	case WM_COMMAND:
		bRet = OnCommand(hWnd, message, wParam, lParam);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此添加任意绘图代码...
		EndPaint(hWnd, &ps);
		break;
	case WM_CREATE:
		bRet = OnCreate(hWnd, message, wParam, lParam);
		break;
	case WM_SIZE:
		bRet = OnSize(hWnd, message, wParam, lParam);
		break;
	case WM_CTLCOLOREDIT:
		{
			/*HDC hEditDC = (HDC)wParam;
			SetTextColor( hEditDC, RGB(0, 0, 0));
			SetBkColor( hEditDC, RGB(255, 255, 255)); 
			return (LRESULT)CreateSolidBrush(RGB(255, 255, 255))*/;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_NOTIFY:
		{
			if (wParam == CRICH_EDIT)
			{
				bRet = OnMouseMove(hWnd, message, wParam, lParam);
			}
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return bRet;
}
