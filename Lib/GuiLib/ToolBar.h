#ifndef TOOL_BAR_H_B48E386D_D004_444e_8FB7_CAB0697044E3
#define TOOL_BAR_H_B48E386D_D004_444e_8FB7_CAB0697044E3
/*
*************************************************************************
模块名  : Using ToolBar Control
文件名  : ToolBar.h    
实现功能: ToolBar
作者    : 周健
版本    : 
关于	：toolbar是MFC自定义的资源类型其中包含图片和ID信息，不属于SDK预定义的资源类型。
		  SDK用工具栏需要自己编码调用工具栏的消息接口。
		  However, the CreateWindowEx function does not have parameters for specifying toolbar size. 
		  The toolbar window procedure automatically sets the size and position of the toolbar window. 
		  The height is based on the height of the buttons in the toolbar. 
		  The width is the same as the width of the parent window's client area.

		  CCS_TOP 
		  Causes the control to position itself at the top of the parent window's client area and sets the width to be the same as the parent window's width. 
		  Toolbars have this style by default. 
		  CCS_BOTTOM 
		  Causes the control to position itself at the bottom of the parent window's client area and sets the width to be the same as the parent window's width. 
		  Status windows have this style by default.
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

#pragma comment(lib,"comctl32.lib")
#define	 STD_CTRL_NUMER		6

namespace GuiLib
{
	class CToolBar
	{
	public:
		CToolBar(HWND hParent, HMENU hMenu, HINSTANCE hInst);
		~CToolBar();
	
	public:
		virtual BOOL Create(int x, int y, int nWidth, int nHeight, DWORD dwStyle, int nIndex[], int nSize);
		virtual BOOL OnSize(HWND hWnd, UINT uMsg, WPARAM wParam,LPARAM lParam);
		HWND GetTBHandle(){return m_hwndTB;}
	
	private:
		HMENU m_hMenu;
		HWND m_hParent;
		HINSTANCE m_hInst;
		HWND m_hwndTB;
		int m_iStdbmp[STD_CTRL_NUMER];
		TBBUTTON m_tBtn[STD_CTRL_NUMER];
		TBADDBITMAP m_tbab; 
	};
}


#endif