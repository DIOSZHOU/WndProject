#ifndef REBAR_H_26DBB2CA_4415_4d2d_A9DF_FD8225731396
#define REBAR_H_26DBB2CA_4415_4d2d_A9DF_FD8225731396
/*
*************************************************************************
模块名  : Rebar Control Reference
文件名  : CReBar.h    
实现功能: CReBar
作者    : 周健
版本    : 
关于	：
The toolbar default sizing and positioning behaviors can be turned off by setting the CCS_NORESIZE and CCS_NOPARENTALIGN common control styles.
Toolbar controls that are hosted by rebar controls must set these styles because the rebar control sizes and positions the toolbar.


-------------------------------------------------------------------------
备注    :
-------------------------------------------------------------------------
修改记录:   
日  期          版本        修改人      修改内容

*************************************************************************
* 版本所有(c)  <2014.8.17>  保留所有权利                                     *
************************************************************************/
#include <Windows.h>
#include <commctrl.h>
#include "ComboBox.h"
#include "ToolBar.h"
#include "resource1.h"

#pragma comment(lib,"comctl32.lib")

#define  REBAR_BAND_MASK	RBBIM_COLORS|RBBIM_TEXT|RBBIM_STYLE|RBBIM_CHILD|RBBIM_CHILDSIZE|RBBIM_SIZE
#define  REBAR_BAND_STYLE	RBBS_CHILDEDGE|RBBS_FIXEDBMP

#define  EXPLORER_COMBOBOX_STYLE	WS_CHILD|WS_VISIBLE|CBS_DROPDOWN 
#define  EXPLORER_TOOLBAR_STYLE		WS_CHILD|WS_VISIBLE|CCS_ADJUSTABLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|CCS_NORESIZE|CCS_NOPARENTALIGN

namespace GuiLib
{
	class CReBar
	{
	public:
		CReBar(HWND hParent, HMENU hMenu, HINSTANCE hInst);
		~CReBar();
	
	public:
		virtual BOOL Create(int x, int y, int nWidth, int nHeight, DWORD dwStyle);
		virtual BOOL OnSize(HWND hWnd, UINT uMsg, WPARAM wParam,LPARAM lParam);

	private:
		HMENU m_hMenu;
		HWND m_hParent;
		HINSTANCE m_hInst;
		HWND m_hwndReBar;
		REBARINFO m_sRebarInfo;
		REBARBANDINFO m_sRbBand;

	private:
		CToolBar* m_ToolBar;
		CComboBox* m_ComboBox; 
	};
}



#endif