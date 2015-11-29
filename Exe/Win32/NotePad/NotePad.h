#ifndef NOTEPAD_H_2C79EE3E_CAA0_42ed_8A06_3F0AF3DB74BD
#define NOTEPAD_H_2C79EE3E_CAA0_42ed_8A06_3F0AF3DB74BD
/*
*************************************************************************
模块名  : NotePad 
文件名  : NotePad.h 
实现功能: 
作者    : 周健
版本    : 
-------------------------------------------------------------------------
备注    :
-------------------------------------------------------------------------
修改记录:   
日  期          版本        修改人      修改内容

*************************************************************************
* 版本所有(c)  <2014.8.12>  保留所有权利                                     *
************************************************************************/

#include "resource.h"
#include "PublicDef.h"
#include "CommonDlg.h"

#define	 NOTEPAD_WND				WS_OVERLAPPEDWINDOW
#define  COMMONDLG_NUMBER	6
//#define  NOTEPAD_EDIT_STYLE			WS_CHILD|WS_VISIBLE|WS_VSCROLL|WS_HSCROLL|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE
#define  NOTEPAD_EDIT_STYLE			WS_CHILD|WS_VISIBLE|WS_VSCROLL|ES_AUTOVSCROLL|ES_MULTILINE
#define  NOTEPAD_TOOLBAR_STYLE		WS_CHILD|WS_VISIBLE|CCS_ADJUSTABLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN
#define  NOTEPAD_STATUSBAR_STYLE	WS_CHILD|WS_VISIBLE|WS_BORDER|SBARS_SIZEGRIP 

using namespace GuiLib;

class CNotePad : public CWnd
{
public:
	CNotePad(LPCTSTR m_lpszClass, LPCTSTR m_lpszName);
	~CNotePad();

public:
	BOOL OnFileNew(HWND hWnd, WPARAM wParam, LPARAM lParam);
	BOOL OnFileOpen(HWND hWnd, WPARAM wParam, LPARAM lParam);
	BOOL OnFileSave(HWND hWnd, WPARAM wParam, LPARAM lParam);
	BOOL OnFileSaveAs(HWND hWnd, WPARAM wParam, LPARAM lParam);
	BOOL OnFilePrint(HWND hWnd, WPARAM wParam, LPARAM lParam);
	BOOL OnPageSet(HWND hWnd, WPARAM wParam, LPARAM lParam);
	BOOL OnColor(HWND hWnd, WPARAM wParam, LPARAM lParam);
	BOOL OnFileCopy(HWND hWnd, WPARAM wParam, LPARAM lParam);
	BOOL OnFilePaste(HWND hWnd, WPARAM wParam, LPARAM lParam);
	BOOL OnFont(HWND hWnd, WPARAM wParam, LPARAM lParam);
    
public:
	LRESULT OnCommand(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnMouseMove(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);
	BOOL OnCreate(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
	BOOL OnSize(HWND hWnd, UINT uMsg, WPARAM wParam,LPARAM lParam);
	static INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

private:
	vector<CCommonDlg*> m_commenDlg;
	CEdit* m_Edit;
	CToolBar* m_ToolBar;
	CStatusBar* m_StatusBar;
};

#endif