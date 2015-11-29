#ifndef WND_H_1742A294_A76D_4071_A993_42080C169879
#define WND_H_1742A294_A76D_4071_A993_42080C169879
/*
*************************************************************************
ģ����  : window base class
�ļ���  : Wnd.h    
ʵ�ֹ���: 
����	��About Window Classes 
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
		//��Ϣ������
		static LRESULT CALLBACK MsgHandler(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
		//���ڵ�����Ϣ��������
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
		LPCTSTR		m_lpszClass;    // ��������
		LPCTSTR		m_lpszName;     // �����ı�
		HINSTANCE	m_hInst;        // ʵ�����
		HWND		m_hWnd;
		HACCEL      m_hAccelTable;
		HPEN		m_hPen;
		HPEN		m_hPenOld;
		HFONT		m_hFont;
		HDC			m_hdc;
	};
}
#endif