#ifndef COMMON_Dlg_F042E318_60E9_4ae6_A72D_C630B24E60D7
#define COMMON_Dlg_F042E318_60E9_4ae6_A72D_C630B24E60D7

/*
*************************************************************************
模块名  : Using Common Dialog Boxes 
文件名  : CommonDlg.h 
实现功能: 
作者    : 周健
版本    : 
-------------------------------------------------------------------------
备注    :
-------------------------------------------------------------------------
修改记录:   
日  期          版本        修改人      修改内容

*************************************************************************
* 版本所有(c)  <2014.7.28>  保留所有权利                                     *
************************************************************************/

#pragma once

#include "PublicDef.h"

namespace GuiLib
{
	class CCommonDlg
	{
	public:
		CCommonDlg(void);
		virtual ~CCommonDlg(void);

	public:
		virtual BOOL DoOpen(HWND hWndParent, LPCTSTR pszTitle = NULL) {return TRUE;}
		LPTSTR GetPath();

	protected:
		TCHAR m_szPath[MAX_FILE_PATH];
	};

	class COpenDlg : public CCommonDlg
	{
	public:
		COpenDlg();
		~COpenDlg();

	public:
		BOOL DoOpen(HWND hWndParent, LPCTSTR pszTitle = NULL);
		BOOL DoSaveAs(HWND hWndParent, LPCTSTR pszTitle = NULL);
		void SetPath(LPTSTR &pszPath);

	private:
		OPENFILENAME m_openfile;
	};

	class CBrowsDlg : public CCommonDlg
	{
	public:
		CBrowsDlg();
		~CBrowsDlg();

	public:
		BOOL DoOpen(HWND hWndParent, LPCTSTR pszTitle = NULL);
		void SetPath(LPTSTR &pszPath) {return;}

	private:
		BROWSEINFO m_brows;
	};

	class CPrintDlg : public CCommonDlg
	{
	public:
		CPrintDlg();
		~CPrintDlg();

	public:
		BOOL DoOpen(HWND hWndParent, LPCTSTR pszTitle = NULL);

	private:
		PRINTDLG  m_bprint;
	};

	class CpageSetDlg : public CCommonDlg
	{
	public:
		CpageSetDlg();
		~CpageSetDlg();

	public:
		BOOL DoOpen(HWND hWndParent, LPCTSTR pszTitle = NULL);

	private:
		PAGESETUPDLG  m_bpageset;
	};

	class CFontDlg : public CCommonDlg
	{
	public:
		CFontDlg();
		~CFontDlg();

	public:
		BOOL DoOpen(HWND hWndParent, LPCTSTR pszTitle = NULL);
		VOID GetFontValue(LOGFONT &logfont) {logfont = this->m_logfont;}
		VOID GetChooseFontValue(CHOOSEFONT &chfont) {chfont = this->m_cFont;}
	private:
		CHOOSEFONT  m_cFont;
		LOGFONT m_logfont;
	};

	class CColorDlg : public CCommonDlg
	{
	public:
		CColorDlg();
		~CColorDlg();

	public:
		BOOL DoOpen(HWND hWndParent, LPCTSTR pszTitle = NULL);

	private:
		CHOOSECOLOR  m_bColor;
		COLORREF m_aColor[16];
	};

	class CFindReplaceDlg
	{
	public:
		CFindReplaceDlg();
		~CFindReplaceDlg();

	public:
		BOOL DoFind(HWND hWndParent, LPCTSTR pszTitle = NULL);
		BOOL DoReplace(HWND hWndParent, LPCTSTR pszTitle = NULL);

	private:
		FINDREPLACE  m_bFindStr;
		HWND m_hFind;
		UINT m_uFindReplace;
		TCHAR m_strFind[MAX_PATH];
		TCHAR m_strReplace[MAX_PATH];
	};

}


#endif	
