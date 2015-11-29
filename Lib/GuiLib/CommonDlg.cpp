
#include "CommonDlg.h"

namespace GuiLib
{
	CCommonDlg::CCommonDlg(void) 
	{
		ZeroMemory(m_szPath, MAX_FILE_PATH);
	}

	CCommonDlg::~CCommonDlg(void)
	{
	}

	LPTSTR CCommonDlg::GetPath()
	{
		return m_szPath;
	}

	COpenDlg::COpenDlg()
	{
		ZeroMemory(&m_openfile, sizeof(m_openfile));
		m_openfile.lStructSize = sizeof(m_openfile);
		m_openfile.hwndOwner = NULL;
		m_openfile.hInstance = NULL;
		m_openfile.lpstrFilter =  _T("Text Files(*.txt)\0*.txt\0All Files\0*.*\0\0");
		m_openfile.lpstrCustomFilter = NULL;
		m_openfile.nFilterIndex = 1;
		m_openfile.lpstrFile = m_szPath;
		m_openfile.lpstrFile[0] = NULL;
		m_openfile.nMaxFile = MAX_FILE_PATH;
		m_openfile.lpstrFileTitle = NULL;
		m_openfile.lpstrInitialDir = _T("Record//");
		m_openfile.lpstrTitle = NULL;
		m_openfile.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		m_openfile.nFileOffset = NULL;
		m_openfile.nFileExtension = NULL;
		m_openfile.lpstrDefExt = NULL;
		m_openfile.lCustData = NULL;
		m_openfile.lpfnHook = NULL;
		m_openfile.lpTemplateName = NULL;
#if (_WIN32_WINNT >= 0x0500)
		m_openfile.pvReserved = NULL;
		m_openfile.dwReserved = NULL;
		m_openfile.FlagsEx = NULL;
#endif // (_WIN32_WINNT >= 0x0500)

	}

	COpenDlg::~COpenDlg()
	{

	}

	BOOL COpenDlg::DoOpen(HWND hWndParent, LPCTSTR pszTitle)
	{
		BOOL bRet = false;
		m_openfile.hwndOwner = hWndParent;

		if (GetOpenFileName(&m_openfile))  
		{  
			SetPath(m_openfile.lpstrFile);
			bRet = true;
		}
		return bRet;
	}

	BOOL COpenDlg::DoSaveAs(HWND hWndParent, LPCTSTR pszTitle)
	{
		BOOL bRet = false;
		m_openfile.hwndOwner = hWndParent;

		if (GetSaveFileName(&m_openfile))  
		{  
			SetPath(m_openfile.lpstrFile);
			bRet = true;
		}
		return bRet;
	}

	void COpenDlg::SetPath(LPTSTR &pszPath)
	{
		memcpy(m_szPath, pszPath, MAX_FILE_PATH);
	}

	CBrowsDlg::CBrowsDlg()
	{
		ZeroMemory(&m_brows, sizeof(m_brows));
		m_brows.hwndOwner = NULL; 
		m_brows.pidlRoot = NULL;   
		m_brows.pszDisplayName = NULL; 
		m_brows.lpszTitle = NULL;   
		m_brows.ulFlags = BIF_BROWSEINCLUDEFILES | BIF_EDITBOX | BIF_VALIDATE;
		m_brows.lpfn = NULL;
		m_brows.lParam = NULL;
		m_brows.iImage = NULL;
	}

	CBrowsDlg::~CBrowsDlg()
	{

	}

	BOOL CBrowsDlg::DoOpen(HWND hWndParent, LPCTSTR pszTitle)
	{
		BOOL bRet = false;
		if(pszTitle == NULL)
		{
			m_brows.lpszTitle = _T("选择目标文件夹");
		}
		else
		{
			m_brows.lpszTitle = pszTitle;
		}
		m_brows.hwndOwner = hWndParent;
		LPITEMIDLIST pItem = ::SHBrowseForFolder(&m_brows);
		if(NULL != pItem)
		{
			::SHGetPathFromIDList(pItem, m_szPath);
			bRet = TRUE;
		}
		return bRet;
	}

	CPrintDlg::CPrintDlg()
	{
		ZeroMemory(&m_bprint, sizeof(m_bprint));
		m_bprint.lStructSize = sizeof(m_bprint);
		m_bprint.hwndOwner = NULL;
		m_bprint.hDevMode = NULL;
		m_bprint.hDevNames = NULL;
		m_bprint.hDC = NULL;
		m_bprint.Flags = PD_ALLPAGES;
		m_bprint.nFromPage = 1;
		m_bprint.nToPage = 2;
		m_bprint.nMinPage = 2;
		m_bprint.nMaxPage = 2;
		m_bprint.nCopies = 0;
		m_bprint.hInstance = NULL;
		m_bprint.lCustData = NULL;
		m_bprint.lpfnPrintHook = NULL;
		m_bprint.lpfnSetupHook = NULL;
		m_bprint.lpPrintTemplateName = NULL;
		m_bprint.lpSetupTemplateName = NULL;
		m_bprint.hPrintTemplate = NULL;
		m_bprint.hSetupTemplate = NULL;
	}

	CPrintDlg::~CPrintDlg()
	{

	}

	BOOL CPrintDlg::DoOpen(HWND hWndParent, LPCTSTR pszTitle)
	{
		BOOL bRet = false;
		m_bprint.hwndOwner = hWndParent;

		if (PrintDlg(&m_bprint))  
		{  
			bRet = true;
		}
		return bRet;
	}

	CpageSetDlg::CpageSetDlg()
	{
		ZeroMemory(&m_bpageset, sizeof(m_bpageset));
		m_bpageset.lStructSize = sizeof(m_bpageset);
		m_bpageset.hwndOwner = NULL;
		m_bpageset.hDevMode = NULL;
		m_bpageset.hDevNames = NULL;
		m_bpageset.Flags = PSD_DEFAULTMINMARGINS;
		m_bpageset.ptPaperSize.x = 0;
		m_bpageset.ptPaperSize.y = 0;
		m_bpageset.rtMinMargin.bottom = 200;
		m_bpageset.rtMinMargin.left = 100;
		m_bpageset.rtMinMargin.right = 100;
		m_bpageset.rtMinMargin.top = 100;
		m_bpageset.rtMargin.bottom = 200;
		m_bpageset.rtMargin.left = 100;
		m_bpageset.rtMargin.right = 200;
		m_bpageset.rtMargin.top = 200;
		m_bpageset.hInstance = NULL;
		m_bpageset.lCustData = NULL;
		m_bpageset.lpfnPageSetupHook = NULL;
		m_bpageset.lpfnPagePaintHook = NULL;
		m_bpageset.lpPageSetupTemplateName = NULL;
		m_bpageset.hPageSetupTemplate = NULL;
	}

	CpageSetDlg::~CpageSetDlg()
	{

	}

	BOOL CpageSetDlg::DoOpen(HWND hWndParent, LPCTSTR pszTitle)
	{
		BOOL bRet = false;
		m_bpageset.hwndOwner = hWndParent;

		if (PageSetupDlg(&m_bpageset))  
		{  
			bRet = true;
		}
		return bRet;
	}

	CFontDlg::CFontDlg()
	{
		ZeroMemory(&m_cFont, sizeof(m_cFont));
		ZeroMemory(&m_logfont, sizeof(m_logfont));
		m_cFont.lStructSize = sizeof(m_cFont);
		m_cFont.hwndOwner = NULL;
		m_cFont.hDC = NULL;
		m_cFont.lpLogFont = &m_logfont;
		m_cFont.iPointSize = NULL;
		m_cFont.Flags = CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS | CF_EFFECTS;
		m_cFont.rgbColors = RGB(255, 0, 255);
		m_cFont.lCustData = NULL;
		m_cFont.lpfnHook = NULL;
		m_cFont.lpTemplateName = NULL;
		m_cFont.hInstance = NULL;
		m_cFont.lpszStyle = NULL;
		m_cFont.nFontType = NULL;
		m_cFont.nSizeMin = 2;
		m_cFont.nSizeMax = 200;
	}

	CFontDlg::~CFontDlg()
	{

	}

	BOOL CFontDlg::DoOpen(HWND hWndParent, LPCTSTR pszTitle)
	{
		BOOL bRet = false;
		m_cFont.hwndOwner = hWndParent;

		if (ChooseFont(&m_cFont))  
		{  
			bRet = true;
		}
		return bRet;
	}


	CColorDlg::CColorDlg()
	{
		ZeroMemory(&m_bColor, sizeof(m_bColor));
		m_bColor.lStructSize = sizeof(m_bColor);
		m_bColor.hwndOwner = NULL;
		m_bColor.hInstance = NULL;
		m_bColor.rgbResult = RGB(255, 0, 0);
		m_bColor.lpCustColors = CColorDlg::m_aColor;
		m_bColor.Flags = CC_RGBINIT;
		m_bColor.lCustData = NULL;
		m_bColor.lpfnHook = NULL;
		m_bColor.lpTemplateName = NULL;
	}

	CColorDlg::~CColorDlg()
	{

	}

	BOOL CColorDlg::DoOpen(HWND hWndParent, LPCTSTR pszTitle)
	{
		BOOL bRet = false;
		m_bColor.hwndOwner = hWndParent;

		if (ChooseColor(&m_bColor))  
		{  
			bRet = true;
		}
		return bRet;
	}

	CFindReplaceDlg::CFindReplaceDlg()
	{
		ZeroMemory(m_strFind, MAX_PATH);
		ZeroMemory(m_strReplace, MAX_PATH);
		ZeroMemory(&m_bFindStr, sizeof(m_bFindStr));
		m_bFindStr.lStructSize = sizeof(m_bFindStr);
		m_bFindStr.hwndOwner = NULL;
		m_bFindStr.hInstance = NULL;
		m_bFindStr.Flags = FR_DIALOGTERM;
		m_bFindStr.lpstrFindWhat = m_strFind;
		m_bFindStr.lpstrReplaceWith = m_strReplace;
		m_bFindStr.wFindWhatLen = MAX_PATH;
		m_bFindStr.wReplaceWithLen = MAX_PATH;
		m_bFindStr.lCustData = NULL;
		m_bFindStr.lpfnHook = NULL;
		m_bFindStr.lpTemplateName = NULL;
	}

	CFindReplaceDlg::~CFindReplaceDlg()
	{

	}
	
	BOOL CFindReplaceDlg::DoFind(HWND hWndParent, LPCTSTR pszTitle)
	{
		BOOL bRet = false;
		//WM_FINDREPLACE = RegisterWindowMessage(FINDMSGSTRING);
		m_bFindStr.hwndOwner = hWndParent;
		m_hFind = FindText(&m_bFindStr);
		if (m_hFind)  
		{  
			bRet = true;
		}
		return bRet;
	}

	BOOL CFindReplaceDlg::DoReplace(HWND hWndParent, LPCTSTR pszTitle)
	{
		BOOL bRet = false;
		//m_uFindReplace = RegisterWindowMessage(FINDMSGSTRING);
		m_bFindStr.hwndOwner = hWndParent;
		m_hFind = ReplaceText(&m_bFindStr);
		if (m_hFind)  
		{  
			bRet = true;
		}
		return bRet;
	}
}

