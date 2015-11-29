#ifndef EDIT_H_8E34B6AE_27BA_417a_A845_BFC57D8DA3EA
#define EDIT_H_8E34B6AE_27BA_417a_A845_BFC57D8DA3EA
/*
*************************************************************************
ģ����  : Using Edit Controls / Edit Controls / Edit Control Text Operations
�ļ���  : Edit.h    
ʵ�ֹ���: Multiline edit controls 

Single-line edit controls are useful for retrieving a single string from the user. 
Multiline edit controls make it easy for your application to implement most of the 
features of a simple word processor. 

����    : �ܽ�
�汾    : 
-------------------------------------------------------------------------
��ע    :
-------------------------------------------------------------------------
�޸ļ�¼:   
��  ��          �汾        �޸���      �޸�����

*************************************************************************
* �汾����(c)  <2014.7.15>  ��������Ȩ��                                     *
************************************************************************/

#include "PublicDef.h"
#include "ShortCutMenu.h"
#include <Richedit.h>

namespace GuiLib
{
	class CEdit
	{
	public:
		CEdit(HWND hParent, HMENU hMenu, HINSTANCE hInst, HFONT hFont);
		virtual ~CEdit();

	public:
		virtual BOOL Create(int x, int y, int nWidth, int nHeight, DWORD dwStyle);
		virtual BOOL OnSize(HWND hWnd, UINT uMsg, WPARAM wParam,LPARAM lParam);
		virtual BOOL OnRbuttonUp(HWND hWnd, UINT uMsg, WPARAM wParam,LPARAM lParam);

	public:
		static INT_PTR CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		BOOL SetText(LPTSTR &m_szSendBuf);
		BOOL GetText(LPTSTR &m_szReadBuf);
		BOOL Clear();
		BOOL Copy();
		BOOL Paste();
		DWORD GetTextLenth();
		HWND GetHwnd();

	public:
		virtual VOID SetFont(CHOOSEFONT &cFontInfor) {return;};
		

	
	protected:
		HFONT m_hFont;
		HMENU m_hMenu;
		HWND m_hParent;
		HINSTANCE m_hInst;
		HWND m_hEdit;

		WNDPROC m_pfnPrevWndProc;
		CShortCutMenu *m_ShortCutMenu;
	};


	/*
	*************************************************************************
	ģ����  : Rich Edit Controls
	�ļ���  : Edit.h    
	ʵ�ֹ���: Rich edit controls support almost all of the messages and notification messages used with multiline edit controls
	����    : �ܽ�
	�汾    : 
	-------------------------------------------------------------------------
	��ע    :
	-------------------------------------------------------------------------
	�޸ļ�¼:   
	��  ��          �汾        �޸���      �޸�����

	*************************************************************************
	* �汾����(c)  <2014.8.13>  ��������Ȩ��                                     *
	************************************************************************/

#define CHAR_FORMAT_DWMASK		CFM_BOLD|CFM_CHARSET|CFM_COLOR|CFM_FACE|CFM_ITALIC|CFM_PROTECTED|CFM_SIZE|CFM_STRIKEOUT|CFM_UNDERLINE|CFM_OFFSET
#define CRICH_EDIT				(WM_USER + 1000)

	class CRichEdit : public CEdit
	{
	public:
		CRichEdit(HWND hParent, HMENU hMenu, HINSTANCE hInst, HFONT hFont);
		~CRichEdit();

	public:
		static INT_PTR CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		virtual BOOL OnRbuttonUp(HWND hWnd, UINT uMsg, WPARAM wParam,LPARAM lParam);
		virtual BOOL Create(int x, int y, int nWidth, int nHeight, DWORD dwStyle);

	public:
		virtual VOID SetFont(CHOOSEFONT &cFontInfor);

	protected:
		CHARFORMAT m_sFormat;

	private:
		HMODULE m_hRichEditDll;
	};
}

#endif