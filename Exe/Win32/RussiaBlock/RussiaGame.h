#ifndef RUSSIA_GAME_H__
#define RUSSIA_GAME_H__


#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Wnd.h"
#include "Block.h"
#include "resource.h"
using namespace std;

#define GRID_SIZE	25
#define GRID_ROW	12
#define GRID_LINE	20
#define GRID_LEFT	0

#define RUSSIAGAME_WND_STYLY		WS_SYSMENU|WS_MINIMIZEBOX
using namespace GuiLib;


class CRussiaGame : public CWnd
{
public:
	CRussiaGame(LPCTSTR m_lpszClass, LPCTSTR m_lpszName);
	~CRussiaGame();

public:
	LRESULT OnCommand(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);
	BOOL OnCreate(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
	BOOL OnSize(HWND hWnd, UINT uMsg, WPARAM wParam,LPARAM lParam);
	BOOL OnPaint(HWND hWnd, UINT uMsg, WPARAM wParam,LPARAM lParam);
	static INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	virtual void OnLeftKeyDown(HWND hWnd, UINT uMsg, UINT nTime, DWORD dwTime); 
	virtual void OnUpKeyDown(HWND hWnd, UINT uMsg, UINT nTime, DWORD dwTime); 
	virtual void OnRightKeyDown(HWND hWnd, UINT uMsg, UINT nTime, DWORD dwTime); 
	virtual void OnDownKeyDown(HWND hWnd, UINT uMsg, UINT nTime, DWORD dwTime); 

public:
	int GetCurrentBlockID();
	BOOL OnInit();
	BOOL SystemInit();
	void SetNewBlock(HWND hWnd, UINT uMsg, UINT nTime, DWORD dwTime); 
	void DrawLine(HDC hdc);
	void DrawWord(HDC hdc, HWND hWnd);
	void DrawBlock(HDC hdc, int x, int y);
	void ReDrawBottomBlock(HDC hdc,HWND hWnd, UINT uMsg);
	/*virtual void GameStart(HWND hWnd, UINT uMsg, UINT nTime, DWORD dwTime);
	virtual void GamePause(HWND hWnd, UINT uMsg, UINT nTime, DWORD dwTime);
	virtual void GameOver(HWND hWnd, UINT uMsg, UINT nTime, DWORD dwTime);
	*/
	UINT SetBlockTimer(HWND hWnd, UINT uMsg);
	BOOL KillBlockTimer(HWND hWnd, UINT message);
	static void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT nTime, DWORD dwTime);

	BOOL IsValidLeft();		
	BOOL IsValidRight();
	BOOL IsValidBottom();
	BOOL IsCrash();					//下面碰到Block了
	BOOL IsLeftCrash();
	BOOL IsRightCrash();
	BOOL IsFullLine(int Row);		
	BOOL IsValidRotate();
	void EliminateLine();			//处理消行
	int nNum;
private:
	CBlock m_blockModeArray[7];
	CBlock m_currentBlock;
	int m_iMap[12][20];
	int m_iNextShapID;
	int score;
	RECT GameRect;
};

#endif