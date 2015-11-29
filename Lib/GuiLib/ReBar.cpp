#include "ReBar.h"

namespace GuiLib
{
	CReBar::CReBar(HWND hParent, HMENU hMenu, HINSTANCE hInst):m_hParent(hParent), m_hMenu(hMenu), m_hInst(hInst)
	{
		INITCOMMONCONTROLSEX icex;
		icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
		icex.dwICC = ICC_COOL_CLASSES|ICC_BAR_CLASSES;
		InitCommonControlsEx(&icex);

		m_sRebarInfo.cbSize = sizeof(REBARINFO);
		m_sRebarInfo.fMask = 0;
		m_sRebarInfo.himl = (HIMAGELIST)NULL;

	}

	CReBar::~CReBar()
	{

	}

	BOOL CReBar::Create(int x, int y, int nWidth, int nHeight, DWORD dwStyle)
	{	
		BOOL bRet = FALSE;
		m_hwndReBar = CreateWindowEx(WS_EX_TOOLWINDOW, REBARCLASSNAME, NULL, dwStyle, x, y, nWidth, nHeight,m_hParent, NULL, m_hInst, NULL);
		if (NULL == m_hwndReBar)
		{
			return bRet;
		}
		m_ToolBar = new CToolBar(m_hwndReBar, NULL, m_hInst);
		/*
		int nIndex[] = {ID_NEW, ID_OPEN, ID_SAVEAS, ID_PRINT, ID_COPY, ID_PASTE};*/
		int nIndex[] = {0, 1, 2, 3, 4, 5};
		m_ToolBar->Create(600, 0, 100, 10, EXPLORER_TOOLBAR_STYLE, nIndex, sizeof(nIndex)/sizeof(int));
		m_ComboBox = new CComboBox(m_hwndReBar, NULL, m_hInst);
		m_ComboBox->Create(0, 0, 100, 20, EXPLORER_COMBOBOX_STYLE);
		if(!SendMessage(m_hwndReBar, RB_SETBARINFO, 0, (LPARAM)&m_sRebarInfo))
		{
			return NULL;
		}

		// Initialize structure members that both bands will share.
		m_sRbBand.cbSize = sizeof(REBARBANDINFO);  // Required
		m_sRbBand.fMask  = REBAR_BAND_MASK;
		m_sRbBand.fStyle = REBAR_BAND_STYLE;
		m_sRbBand.hbmBack = NULL;//LoadBitmap(m_hInst, MAKEINTRESOURCE(IDB_BITMAP1));   

		m_sRbBand.clrBack = RGB(222, 222, 222);
		//m_sRbBand.clrFore = RGB(255, 255, 255);
		// Create the combo box control to be added.
		// Set values unique to the band with the combo box.
		RECT rc;
		HWND hwndCombobox = m_ComboBox->GetCBoxHandle();
		GetWindowRect(hwndCombobox, &rc);
		m_sRbBand.lpText     = _T("Combo Box");
		m_sRbBand.hwndChild  = hwndCombobox;
		m_sRbBand.cxMinChild = 0;
		m_sRbBand.cyMinChild = rc.bottom - rc.top;
		m_sRbBand.cx         = 200;

		// Add the band that has the combo box.
		SendMessage(m_hwndReBar, RB_INSERTBAND, (WPARAM)-1, (LPARAM)&m_sRbBand);

		// Create the toolbar control to be added.

		// Get the height of the toolbar.
		HWND hwndToolbar = m_ToolBar->GetTBHandle();
		DWORD dwBtnSize = SendMessage(hwndToolbar, TB_GETBUTTONSIZE, 0, 0);

		// Set values unique to the band with the toolbar.
		m_sRbBand.lpText     = _T("Tool Bar");
		m_sRbBand.hwndChild  = hwndToolbar;
		m_sRbBand.cxMinChild = 0;
		m_sRbBand.cyMinChild = HIWORD(dwBtnSize);
		m_sRbBand.cx         = 250;

		// Add the band that has the toolbar.
		SendMessage(m_hwndReBar, RB_INSERTBAND, (WPARAM)-1, (LPARAM)&m_sRbBand);


		return bRet;
	}

	BOOL CReBar::OnSize(HWND hWnd, UINT uMsg, WPARAM wParam,LPARAM lParam)
	{
		BOOL bRet = FALSE;

		return bRet;
	}
}