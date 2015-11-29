#ifndef WND_H_1742A294_A76D_4071_A993_42080C169879
#define WND_H_1742A294_A76D_4071_A993_42080C169879
/*
*************************************************************************
模块名  : window base class
文件名  : Wnd.h    
实现功能: 
关于	：About Window Classes 
作者    : 周健
版本    : 
-------------------------------------------------------------------------
备注    :
-------------------------------------------------------------------------
修改记录:   
日  期          版本        修改人      修改内容

*************************************************************************
* 版本所有(c)  <2014.7.15>  保留所有权利                                     *
************************************************************************/

#include "PublicDef.h"

namespace GuiLib
{
	class CWnd
	{
	public:
		CWnd(LPCTSTR m_lpszClass, LPCTSTR m_lpszName);
		virtual ~CWnd();

	public:
		virtual LRESULT OnCommand(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		virtual int Run();
		//消息处理函数
		static LRESULT CALLBACK MsgHandler(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
		//窗口的主消息报处理函数
		virtual LRESULT WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
		virtual BOOL OnPaint(HWND hWnd, UINT uMsg, WPARAM wParam,LPARAM lParam);
		virtual BOOL OnCreate(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
		virtual BOOL OnSize(HWND hWnd, UINT uMsg, WPARAM wParam,LPARAM lParam);
		virtual BOOL Create(HINSTANCE hInstance, HWND hwndParent, int nCmdShow, 
							HICON hIcon, HCURSOR hCursor, HICON hIconSmall, HACCEL m_hAccel, 
							LPTSTR szMenu, int x, int y, int cx, int cy, DWORD dwStyle = WS_OVERLAPPEDWINDOW);


	public:
		virtual void OnLeftKeyDown(HWND hWnd, UINT uMsg, UINT nTime, DWORD dwTime); 
		virtual void OnUpKeyDown(HWND hWnd, UINT uMsg, UINT nTime, DWORD dwTime); 
		virtual void OnRightKeyDown(HWND hWnd, UINT uMsg, UINT nTime, DWORD dwTime); 
		virtual void OnDownKeyDown(HWND hWnd, UINT uMsg, UINT nTime, DWORD dwTime); 

	protected:
		LPCTSTR		m_lpszClass;    // 窗口类名
		LPCTSTR		m_lpszName;     // 窗口文本
		HINSTANCE	m_hInst;        // 实例句柄
		HWND		m_hWnd;
		HACCEL      m_hAccelTable;
		HPEN		m_hPen;
		HPEN		m_hPenOld;
		HFONT		m_hFont;
		HDC			m_hdc;
	};
}
#endif