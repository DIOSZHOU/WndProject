#include "Wnd.h"

namespace GuiLib
{
	CWnd::CWnd(LPCTSTR m_lpszClass, LPCTSTR m_lpszName) 
		: m_lpszClass (m_lpszClass), m_lpszName(m_lpszName)
	{
 		//m_lpszClass = m_lpszClass;	//必须用初始化列表，不然弹框
 		//m_lpszName = m_lpszName;
	}

	CWnd::~CWnd()
	{

	}

	BOOL CWnd::Create(HINSTANCE hInstance, HWND hwndParent, int nCmdShow, 
						HICON hIcon, HCURSOR hCursor, HICON hIconSmall, HACCEL m_hAccel, 
						LPTSTR szMenu, int x, int y, int cx, int cy, DWORD dwStyle)
	{
		WNDCLASSEX wcex;
		m_hInst = hInstance;
		if(!GetClassInfoEx(m_hInst, m_lpszClass, &wcex))
		{
			wcex.cbSize = sizeof(WNDCLASSEX);

			wcex.style			= CS_HREDRAW | CS_VREDRAW;
			wcex.lpfnWndProc	= (WNDPROC)MsgHandler;	//WNDPROC类型定义了一个指针指向这个回调函数，这个回调函数4个参数，用类的成员函数有this
			wcex.cbClsExtra		= 0;
			wcex.cbWndExtra		= 0;
			wcex.hInstance		= hInstance;
			wcex.hIcon			= hIcon;		//LoadIcon(hInstance, MAKEINTRESOURCE(IDI_NOTEPAD));
			wcex.hCursor		= hCursor;		//LoadCursor(NULL, IDC_ARROW);
			wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
			wcex.lpszMenuName	= szMenu;		//MAKEINTRESOURCE(IDC_NOTEPAD);
			wcex.lpszClassName	= m_lpszClass;
			wcex.hIconSm		= hIconSmall;	//LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
		}
		if (!RegisterClassEx(&wcex))
			return FALSE;
		
		m_hWnd = ::CreateWindow(m_lpszClass, m_lpszName, dwStyle, x, y, cx, cy, 0, 0, hInstance, LPVOID(this));
		if(m_hWnd == NULL)
		{
			DWORD dwLastError = GetLastError();
			return FALSE;
		}
		SetWindowLong(m_hWnd, GWL_USERDATA,(LONG)this);	//改变指定窗口属性
		/*if(!OnCreate(m_hWnd, NULL, 0, 0))
		{
			DestroyWindow(m_hWnd);
			return FALSE;
		}*/
		ShowWindow(m_hWnd, nCmdShow);
		UpdateWindow(m_hWnd);
		m_hAccelTable = m_hAccel;
		return true;
	}

	 LRESULT CALLBACK CWnd::MsgHandler(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
	 {
		 void* user_data = reinterpret_cast<void*>(::GetWindowLong(hWnd, GWL_USERDATA));
		 CWnd* pWnd = NULL;
		 if(user_data)
		 {
			 pWnd = reinterpret_cast<CWnd*>(user_data);
		 }
		 else
		 {
			 if (uMsg == WM_CREATE && NULL == pWnd)
			 {
				  //createwindow还未返回，WM_CREATE消息就已经发送出来了，通过lparam参数把this指针传递过来
				  pWnd = (CWnd*)(((CREATESTRUCT*)lParam)->lpCreateParams);
			 }
		 }
		 if(NULL == pWnd)
		 {
			 if(uMsg == WM_DESTROY)
			 {
				 ::PostQuitMessage(0);
				 return 0;
			 }
			 return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
		 }
		
		 return pWnd->WndProc(hWnd, uMsg, wParam, lParam);  
	 }

	 BOOL CWnd::OnCreate(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
	 {
		return true;
	 }

	 BOOL CWnd::OnSize(HWND hWnd, UINT uMsg, WPARAM wParam,LPARAM lParam)
	 {
		 return true;
	 }

	 BOOL CWnd::OnPaint(HWND hWnd, UINT uMsg, WPARAM wParam,LPARAM lParam)
	 {
		 return true;
	 }


	 void CWnd:: OnLeftKeyDown(HWND hWnd, UINT uMsg, UINT nTime, DWORD dwTime)
	 {

	 }

	 void CWnd:: OnUpKeyDown(HWND hWnd, UINT uMsg, UINT nTime, DWORD dwTime)
	 {

	 }

	 void CWnd::OnRightKeyDown(HWND hWnd, UINT uMsg, UINT nTime, DWORD dwTime)
	 {

	 }

	 void CWnd::OnDownKeyDown(HWND hWnd, UINT uMsg, UINT nTime, DWORD dwTime)
	 {

	 }

	 LRESULT CWnd::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	 {
		 //PAINTSTRUCT ps;
		 //HDC hdc;
		 BOOL bRet = FALSE;
		 switch (message)
		 {
		 case WM_COMMAND:
			 bRet = OnCommand(hWnd, message, wParam, lParam);
			 break;
		 case WM_PAINT:
			 bRet = OnPaint(hWnd, message, wParam, lParam);
			 break;
		 case WM_SIZE:
			 bRet = OnSize(hWnd, message, wParam, lParam);
			 break;
		 case WM_KEYDOWN:
			 switch(wParam)
			 {
			 case 37:
				 OnLeftKeyDown(hWnd, message, wParam, lParam);
				 break;
			 case 38:
				 OnUpKeyDown(hWnd, message, wParam, lParam);
				 break;
			 case 39:
				 OnRightKeyDown(hWnd, message, wParam, lParam);
				 break;
			 case 40:
				 OnDownKeyDown(hWnd, message, wParam, lParam);
				 break;
			 }
			 break;
		 case WM_DESTROY:
			 PostQuitMessage(0);
			 break;
		 default:
			 return DefWindowProc(hWnd, message, wParam, lParam);
		 }
		 return bRet;
	 }


	 LRESULT CWnd::OnCommand(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	 {
		 return true;
	 }

	 int CWnd::Run()
	 {
		 MSG msg;
		 while (GetMessage(&msg, NULL, 0, 0))
		 {
			 if (!TranslateAccelerator(msg.hwnd, m_hAccelTable, &msg))
			 {
				 TranslateMessage(&msg);
				 DispatchMessage(&msg);
			 }
		 }
		 return (int) msg.wParam;
	 }
}