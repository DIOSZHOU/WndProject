#include "stdafx.h"
#include "RussiaGame.h"

CRussiaGame::CRussiaGame(LPCTSTR m_lpszClass, LPCTSTR m_lpszName) : CWnd(m_lpszClass, m_lpszName)
{
	nNum = 0;
	m_iNextShapID = 0;
	score = 0;
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			m_iMap[i][j] = 0;
		}
	}
 	m_blockModeArray[0] =  CBlock(CBlockPoint(4, 0), CBlockPoint(5, 0), CBlockPoint(6, 0), CBlockPoint(7, 0));
 	m_blockModeArray[1] =  CBlock(CBlockPoint(5, 0), CBlockPoint(6, 0), CBlockPoint(5, 1), CBlockPoint(6, 1));
 	m_blockModeArray[2] =  CBlock(CBlockPoint(5, 0), CBlockPoint(4, 1), CBlockPoint(5, 1), CBlockPoint(6, 1));
 	m_blockModeArray[3] =  CBlock(CBlockPoint(4, 0), CBlockPoint(5, 0), CBlockPoint(5, 1), CBlockPoint(6, 1));
 	m_blockModeArray[4] =  CBlock(CBlockPoint(5, 0), CBlockPoint(6, 0), CBlockPoint(4, 1), CBlockPoint(5, 1));
 	m_blockModeArray[5] =  CBlock(CBlockPoint(4, 0), CBlockPoint(4, 1), CBlockPoint(5, 1), CBlockPoint(6, 1));
 	m_blockModeArray[6] =  CBlock(CBlockPoint(6, 0), CBlockPoint(4, 1), CBlockPoint(5, 1), CBlockPoint(6, 1));
	m_currentBlock = m_blockModeArray[0];
	
}

CRussiaGame::~CRussiaGame()
{

}

void CRussiaGame::DrawLine(HDC hdc)
{
	m_hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));

	m_hPenOld = (HPEN)SelectObject(hdc, m_hPen); 
	for (int i = 0; i <= 20; i++)
	{
		MoveToEx(hdc, GRID_SIZE * 12, GRID_SIZE * i, NULL);
		LineTo(hdc, 0, GRID_SIZE * i);
	}
	
	for (int i = 0; i <= 12; i++)
	{
		MoveToEx(hdc, GRID_SIZE * i, GRID_SIZE * 20, NULL);
		LineTo(hdc, GRID_SIZE * i, 0);
	}
	SelectObject(hdc, m_hPenOld);
	DeleteObject(m_hPen);
}

void CRussiaGame::DrawWord(HDC hdc, HWND hWnd)
{
	RECT clientRect, rc;
	GetClientRect(hWnd, &clientRect);
	rc.left = GRID_SIZE * 12;
	rc.top = 150;
	rc.right = clientRect.right;
	rc.bottom = 500;
	TCHAR szText[256] = {0};
	ZeroMemory(szText, sizeof(szText));
	_stprintf(szText,   L"%s%d", L"分数:", score);

	LOGFONT logfont;
	ZeroMemory(&logfont, sizeof(logfont));
	logfont.lfCharSet = GB2312_CHARSET;
	logfont.lfHeight = -30;
	m_hFont = CreateFontIndirect(&logfont);
	SetTextColor(m_hdc, RGB(255, 0, 0));
	SetBkColor(hdc, RGB(0, 255, 0));
	SetBkMode(hdc, OPAQUE);
	SelectObject(hdc, m_hFont);
	DrawText(hdc, szText, 8, &rc,  DT_CENTER);
	DeleteObject(m_hFont);
}

BOOL CRussiaGame::OnPaint(HWND hWnd, UINT uMsg, WPARAM wParam,LPARAM lParam)
{
	

	RECT rc;
	::GetClientRect(hWnd, &rc);
	int clientWidth = rc.right - rc.left;
	int clientHeight = rc.bottom - rc.top;
	//SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)(HBRUSH)GetStockObject(NULL_BRUSH));
	PAINTSTRUCT ps;
	m_hdc = BeginPaint(hWnd, &ps);		//只响应WM_PAINT，InvalidateRect();最后一个参数为TRUE，则background brush会擦出
	HDC hdc = GetDC(NULL);
	HBITMAP bmp = CreateCompatibleBitmap(hdc, rc.right-rc.left, rc.bottom-rc.top);
	HDC mem_dc = CreateCompatibleDC(hdc);
	HBITMAP old_bmp = (HBITMAP)SelectObject(mem_dc, bmp);
	FillRect(mem_dc, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));

	DrawLine(mem_dc);
	DrawWord(mem_dc, hWnd);
	DrawBlock(mem_dc,m_currentBlock.Point0.m_x, m_currentBlock.Point0.m_y);
	DrawBlock(mem_dc,m_currentBlock.Point1.m_x, m_currentBlock.Point1.m_y);
	DrawBlock(mem_dc,m_currentBlock.Point2.m_x, m_currentBlock.Point2.m_y);
	DrawBlock(mem_dc,m_currentBlock.Point3.m_x, m_currentBlock.Point3.m_y);
	ReDrawBottomBlock(mem_dc, hWnd, uMsg);
	
	BitBlt(m_hdc, 0, 0, clientWidth, clientHeight, mem_dc, 0, 0, SRCCOPY);
	SelectObject(mem_dc, old_bmp);
	DeleteObject(bmp);
	DeleteObject(mem_dc);

	ReleaseDC(NULL, hdc);
	EndPaint(hWnd, &ps);
	return TRUE;
}

void CRussiaGame::DrawBlock(HDC hdc, int x, int y)
{
	RECT rect1;
	HBRUSH m_hBrush;
	HBRUSH m_hBrushOld;
	m_hBrush = CreateSolidBrush(RGB(255, 0, 0));
	m_hBrushOld = (HBRUSH)SelectObject(hdc, m_hBrush);
	rect1.left = x * GRID_SIZE + 2;
	rect1.top = y * GRID_SIZE + 2;
	rect1.right = x * GRID_SIZE +  GRID_SIZE - 2;
	rect1.bottom = y * GRID_SIZE +  GRID_SIZE - 2;
	FillRect(hdc,&rect1, m_hBrush);
	SelectObject(hdc, m_hBrushOld);
	DeleteObject(m_hBrush);
}

void CRussiaGame::SetNewBlock(HWND hWnd, UINT uMsg, UINT nTime, DWORD dwTime)
{
	if (!IsValidBottom() || IsCrash())
	{
		m_iMap[m_currentBlock.Point0.m_x][m_currentBlock.Point0.m_y] = 1;
		m_iMap[m_currentBlock.Point1.m_x][m_currentBlock.Point1.m_y] = 1;
		m_iMap[m_currentBlock.Point2.m_x][m_currentBlock.Point2.m_y] = 1;
		m_iMap[m_currentBlock.Point3.m_x][m_currentBlock.Point3.m_y] = 1;
		EliminateLine();
		OnInit();
		return;
	}
	 m_currentBlock.Point0.m_y += 1;
	 m_currentBlock.Point1.m_y += 1;
	 m_currentBlock.Point2.m_y += 1;
	 m_currentBlock.Point3.m_y += 1;
	 InvalidateRect(hWnd, NULL, TRUE);
}

void CRussiaGame::ReDrawBottomBlock(HDC hdc, HWND hWnd, UINT uMsg)
{
	for (int i = 0; i < 12; i++)
	{
		for(int j = 0; j < 20; j++)
		{
			if (m_iMap[i][j] == 1)
			{
				DrawBlock(hdc, i, j);
			}
		}
	}
}

void CRussiaGame::OnLeftKeyDown(HWND hWnd, UINT uMsg, UINT nTime, DWORD dwTime)
{
	if (!IsValidLeft() || IsLeftCrash())
	{
		return;
	}
	m_currentBlock.Point0.m_x -= 1;
	m_currentBlock.Point1.m_x -= 1;
	m_currentBlock.Point2.m_x -= 1;
	m_currentBlock.Point3.m_x -= 1;
	InvalidateRect(hWnd, NULL, TRUE);
}

void CRussiaGame::OnRightKeyDown(HWND hWnd, UINT uMsg, UINT nTime, DWORD dwTime)
{
	if (!IsValidRight() || IsRightCrash())
	{
		return;
	}
	m_currentBlock.Point0.m_x += 1;
	m_currentBlock.Point1.m_x += 1;
	m_currentBlock.Point2.m_x += 1;
	m_currentBlock.Point3.m_x += 1;
	InvalidateRect(hWnd, NULL, TRUE);
}

void CRussiaGame::OnDownKeyDown(HWND hWnd, UINT uMsg, UINT nTime, DWORD dwTime)
{
	if (!IsValidBottom() || IsCrash())
	{
		m_iMap[m_currentBlock.Point0.m_x][m_currentBlock.Point0.m_y] = 1;
		m_iMap[m_currentBlock.Point1.m_x][m_currentBlock.Point1.m_y] = 1;
		m_iMap[m_currentBlock.Point2.m_x][m_currentBlock.Point2.m_y] = 1;
		m_iMap[m_currentBlock.Point3.m_x][m_currentBlock.Point3.m_y] = 1;
		EliminateLine();
		OnInit();
		return;
	}
	m_currentBlock.Point0.m_y += 1;
	m_currentBlock.Point1.m_y += 1;
	m_currentBlock.Point2.m_y += 1;
	m_currentBlock.Point3.m_y += 1;
	InvalidateRect(hWnd, NULL, TRUE);
}

void CRussiaGame::OnUpKeyDown(HWND hWnd, UINT uMsg, UINT nTime, DWORD dwTime)
{
	if (IsValidRotate())
	{
		m_currentBlock.ChangeShape(nNum);
		InvalidateRect(hWnd, NULL, TRUE);
	}
}

BOOL CRussiaGame::IsValidRotate()
{
	int X0 = m_currentBlock.Point0.m_x;
	int Y0 = m_currentBlock.Point0.m_y;
	int X1 = m_currentBlock.Point1.m_x;
	int Y1 = m_currentBlock.Point1.m_y;
	int X2 = m_currentBlock.Point2.m_x;
	int Y2 = m_currentBlock.Point2.m_y;
	int X3 = m_currentBlock.Point3.m_x;
	int Y3 = m_currentBlock.Point3.m_y;
	BOOL bRet = FALSE;
	switch(nNum)
	{
	case 0:
		{
			if (m_currentBlock.Zero == ORI)
			{
				if (m_iMap[X1][Y1 + 1] != 1 && Y1 < GRID_LINE - 2
					&& m_iMap[X1][Y1 + 2] != 1 
					&& m_iMap[X2][Y2 + 1] != 1 
					&& m_iMap[X2][Y2 + 2] != 1 
					&& m_iMap[X3][Y3 + 1] != 1 
					&& m_iMap[X3][Y3 + 2] != 1 
					&& m_iMap[X0][Y0 - 1] != 1 
					&& m_iMap[X1][Y1 - 1] != 1 )
				{
					bRet = TRUE;
				}
			}
			else if (m_currentBlock.Zero == ONE)
			{
				if (X0 >= 2  && X0 < GRID_ROW - 2
					&& m_iMap[X1 - 1][Y1] != 1 
					&& m_iMap[X1 - 2][Y1] != 1 
					&& m_iMap[X2 - 1][Y2] != 1 
					&& m_iMap[X2 - 2][Y2] != 1 
					&& m_iMap[X3 - 1][Y3] != 1 
					&& m_iMap[X3 - 2][Y3] != 1 
					
					&& m_iMap[X0 + 1][Y0] != 1 
					&& m_iMap[X0 + 2][Y0] != 1 
					&& m_iMap[X1 + 1][Y1] != 1 
					&& m_iMap[X1 + 2][Y1] != 1 )
				{
					bRet = TRUE;
				}
			}
		}
		break;
	case 2:
		{
			if (m_currentBlock.Two == ORI)
			{
				if (m_iMap[X0 + 1][Y0] != 1 && Y2 < GRID_LINE - 1
					&& m_iMap[X1][Y1 - 1] != 1
					&& m_iMap[X2][Y2 + 1] != 1
					&& m_iMap[X3][Y3 + 1] != 1)
				{
					bRet = TRUE;
				}
			}
			else if (m_currentBlock.Two == ONE)
			{
				if (X0 > GRID_LEFT
					&& m_iMap[X0 + 1][Y0] != 1
					&& m_iMap[X1 - 1][Y1] != 1
					&& m_iMap[X2 - 1][Y2] != 1
					&& m_iMap[X3][Y3 + 1] != 1)
				{
					bRet = TRUE;
				}
			}
			else if (m_currentBlock.Two == TWO)
			{
				if (m_iMap[X0][Y0 - 1] != 1
					&& m_iMap[X2][Y2 - 1] != 1
					&& m_iMap[X3][Y3 + 1] != 1
					&& m_iMap[X1 - 1][Y1] != 1 )
				{
					bRet = TRUE;
				}
			}
			else if (m_currentBlock.Two == THREE)
			{
				if (X3 < GRID_ROW - 1
					&&m_iMap[X3 + 1][Y3] != 1
					&& m_iMap[X2 + 1][ Y2] != 1
					&& m_iMap[X1 - 1][Y1] != 1
					&& m_iMap[X0][Y0 - 1] != 1)
				{
					bRet = TRUE;
				}
			}
		}
		break;
	case 3:
		{
			if (m_currentBlock.Three == ORI)
			{
				if (m_iMap[X0][Y0 - 1] != 1
					&& m_iMap[X1][Y1 - 1] != 1
					&& m_iMap[X2 - 1][Y2] != 1
					&& m_iMap[X3][Y3 + 1] != 1
					&& m_iMap[X2][Y2 + 1] != 1
					&& m_iMap[X2 - 1][Y2 + 1] != 1)
				{
					bRet = TRUE;
				}
			}
			else if (m_currentBlock.Three == ONE)
			{
				if (X0 > GRID_LEFT && X3 < GRID_ROW - 1
					&&m_iMap[X2 - 1][Y2] != 1
					&& m_iMap[X0 - 1][Y0] != 1
					&& m_iMap[X3 + 1][Y3] != 1
					&& m_iMap[X1 + 1][Y1] != 1
					&& m_iMap[X1 + 1][Y1 + 1] != 1
					&& m_iMap[X1][Y1 + 1] != 1)
				{
					bRet = TRUE;
				}
			}
		}
		break;
	case 4:
		{
			if (m_currentBlock.Four == ORI)
			{
				if (m_iMap[X1][Y1 + 1] != 1 && Y2 < GRID_LINE - 1
					&& m_iMap[X1][Y1 + 2] != 1
					&& m_iMap[X2][Y2 - 1] != 1
					&& m_iMap[X2][Y2 - 2] != 1
					&& m_iMap[X3][Y3 + 1] != 1)
				{
					bRet = TRUE;
				}
			}
			else if (m_currentBlock.Four == ONE)
			{
				if (X0 > GRID_LEFT && X1 < GRID_ROW - 1
					&& m_iMap[X3][Y3 + 1] != 1
					&& m_iMap[X3 - 1][Y3 + 1] != 1
					&& m_iMap[X3 - 1][Y3] != 1
					&& m_iMap[X0 + 1][Y0] != 1
					&& m_iMap[X1 + 1][Y1] != 1
					&& m_iMap[X1 + 1][Y1 - 1] != 1)
				{
					bRet = TRUE;
				}
			}
		}
		break;
	case 5:
		{
			if (m_currentBlock.Five == ORI)
			{
				if (X0 > GRID_LEFT && Y1 < GRID_LINE - 2
					&& m_iMap[X2][Y2 + 1] != 1
					&& m_iMap[X2][Y2 + 2] != 1
					&& m_iMap[X2 + 1][Y2 + 1] != 1
					&& m_iMap[X2 + 1][Y2 + 2] != 1
					&& m_iMap[X2 - 1][Y2 + 1] != 1
					&& m_iMap[X2 - 1][Y2 + 2] != 1
					&& m_iMap[X0 - 1][Y0] != 1
					&& m_iMap[X0 - 1][Y0 + 1] != 1
					&& m_iMap[X0 + 1][Y0] != 1)
				{
					bRet = TRUE;
				}
			} 
			else if (m_currentBlock.Five == ONE)
			{
				if (X0 > GRID_LEFT
					&&m_iMap[X1 - 1][Y1] != 1
					&&m_iMap[X1 - 1][Y1 + 1] != 1
					&&m_iMap[X1 - 1][Y1 + 2] != 1
					&&m_iMap[X1][Y1 - 1] != 1
					&&m_iMap[X1 + 1][Y1 - 1] != 1
					&&m_iMap[X1 + 1][Y1 + 1] != 1) 
				{
					bRet = TRUE;
				}
			}
			else if (m_currentBlock.Five == TWO)
			{
				if (X0 < GRID_ROW 
					&&m_iMap[X1 - 1][Y1 - 1] != 1
					&&m_iMap[X1 - 1][Y1 - 2] != 1
					&&m_iMap[X1][Y1 - 1] != 1
					&&m_iMap[X1][Y1 - 2] != 1
					&&m_iMap[X1 + 1][Y1 - 1] != 1
					&&m_iMap[X1 + 1][Y1 - 2] != 1
					&&m_iMap[X2 + 1][Y2] != 1
					&&m_iMap[X2 + 1][Y2 + 1] != 1
					&&m_iMap[X1][Y1 + 1] != 1)
				{
					bRet = TRUE;
				}
			}
			else if (m_currentBlock.Five == THREE)
			{
				if (X0 < GRID_ROW - 1 && Y1 < GRID_LINE - 2
					&&m_iMap[X2 + 1][Y2] != 1
					&&m_iMap[X2 + 1][Y2 - 1] != 1
					&&m_iMap[X2 + 1][Y2 - 2] != 1
					&&m_iMap[X2][Y2 + 1] != 1
					&&m_iMap[X2 - 1][Y2 + 1] != 1
					&&m_iMap[X2 - 1][Y2 - 1] != 1)
				{
					bRet = TRUE;
				}
			}
		}
		break;
	case 6:
		{
			if (m_currentBlock.Six == ORI)
			{
				if (m_iMap[X1][Y1 - 1] != 1
					&& m_iMap[X1][Y1 - 2] != 1
					&& m_iMap[X1 + 1][Y1 - 1] != 1
					&& m_iMap[X1 + 1][Y1 - 2] != 1
					&& m_iMap[X0 + 1][Y0] != 1
					&& m_iMap[X0 + 1][Y0 + 1] != 1)
				{
					bRet = TRUE;
				}
			}
			else if (m_currentBlock.Six == ONE)
			{
 				if (m_iMap[X0 + 1][Y0] != 1 && X3 < GRID_ROW - 1
					&& m_iMap[X0 + 2][Y0] != 1
					&& m_iMap[X0 + 1][Y0 - 1] != 1
					&& m_iMap[X0 + 2][Y0 - 1] != 1
					&& m_iMap[X0 + 2][Y0 + 1] != 1
					&& m_iMap[X2][Y2 + 1] != 1
					&& m_iMap[X2 + 1][Y2 + 1] != 1)
 				{
					bRet = TRUE;
 				}
			}
			else if (m_currentBlock.Six == TWO)
			{
				if (m_iMap[X0 + 1][Y0] != 1	&& Y0 < GRID_LINE - 2
					&& m_iMap[X0 + 2][Y0] != 1
					&& m_iMap[X0 + 1][Y0 + 1] != 1
					&& m_iMap[X0 + 2][Y0 + 1] != 1
					&& m_iMap[X0 - 1][Y0] != 1
					&& m_iMap[X0 - 1][Y0 - 1] != 1)
				{
					bRet = TRUE;
				}
			}
			else if (m_currentBlock.Six == THREE)
			{
				if (m_iMap[X0 - 1][Y0] != 1
					&& m_iMap[X0 - 2][Y0] != 1
					&& m_iMap[X0 - 1][Y0 + 1] != 1
					&& m_iMap[X0 - 2][Y0 + 1] != 1
					&& m_iMap[X0 - 2][Y0 - 1] != 1
					&& m_iMap[X2][Y2 - 1] != 1
					&& m_iMap[X2 + 1][Y2 - 1] != 1)
				{
					bRet = TRUE;
				}
			}
		}
		break;

	}
	
	return bRet;
}

BOOL CRussiaGame::IsValidLeft()
{
	BOOL bRet = FALSE;
	if (m_currentBlock.Point0.m_x > GRID_LEFT 
		&& m_currentBlock.Point1.m_x > GRID_LEFT 
		&& m_currentBlock.Point2.m_x > GRID_LEFT 
		&& m_currentBlock.Point3.m_x > GRID_LEFT )
	{
		bRet = TRUE;
	}
	return bRet;
}

BOOL CRussiaGame::IsValidRight()
{
	BOOL bRet = FALSE;
	if (m_currentBlock.Point0.m_x < GRID_ROW - 1
		&& m_currentBlock.Point1.m_x < GRID_ROW - 1
		&& m_currentBlock.Point2.m_x < GRID_ROW - 1
		&& m_currentBlock.Point3.m_x < GRID_ROW - 1)
	{
		bRet = TRUE;
	}
	return bRet;
}

BOOL CRussiaGame::IsValidBottom()
{
	BOOL bRet = FALSE;
	if (m_currentBlock.Point0.m_y < GRID_LINE - 1
		&& m_currentBlock.Point1.m_y <GRID_LINE - 1
		&& m_currentBlock.Point2.m_y <GRID_LINE - 1
		&& m_currentBlock.Point3.m_y <GRID_LINE - 1)
	{
		bRet = TRUE;
	}
	return bRet;
}

BOOL CRussiaGame::IsCrash()
{
	BOOL bRet = FALSE;
	if (m_iMap[m_currentBlock.Point0.m_x][m_currentBlock.Point0.m_y + 1] == 1)
	{
		bRet = TRUE;
	}
	else if (m_iMap[m_currentBlock.Point1.m_x][m_currentBlock.Point1.m_y + 1] == 1)
	{
		bRet = TRUE;
	}
	else if (m_iMap[m_currentBlock.Point2.m_x][m_currentBlock.Point2.m_y + 1] == 1)
	{
		bRet = TRUE;
	}
	else if (m_iMap[m_currentBlock.Point3.m_x][m_currentBlock.Point3.m_y + 1] == 1)
	{
		bRet = TRUE;
	}
	return bRet;
}

BOOL CRussiaGame::IsLeftCrash()
{
	BOOL bRet = FALSE;
	if (m_iMap[m_currentBlock.Point0.m_x - 1][m_currentBlock.Point0.m_y] == 1)
	{
		bRet = TRUE;
	}
	else if (m_iMap[m_currentBlock.Point1.m_x - 1][m_currentBlock.Point1.m_y] == 1)
	{
		bRet = TRUE;
	}
	else if (m_iMap[m_currentBlock.Point2.m_x - 1][m_currentBlock.Point2.m_y] == 1)
	{
		bRet = TRUE;
	}
	else if (m_iMap[m_currentBlock.Point3.m_x - 1][m_currentBlock.Point3.m_y] == 1)
	{
		bRet = TRUE;
	}
	return bRet;
}

BOOL CRussiaGame::IsRightCrash()
{
	BOOL bRet = FALSE;
	if (m_iMap[m_currentBlock.Point0.m_x + 1][m_currentBlock.Point0.m_y] == 1)
	{
		bRet = TRUE;
	}
	else if (m_iMap[m_currentBlock.Point1.m_x + 1][m_currentBlock.Point1.m_y] == 1)
	{
		bRet = TRUE;
	}
	else if (m_iMap[m_currentBlock.Point2.m_x + 1][m_currentBlock.Point2.m_y] == 1)
	{
		bRet = TRUE;
	}
	else if (m_iMap[m_currentBlock.Point3.m_x + 1][m_currentBlock.Point3.m_y] == 1)
	{
		bRet = TRUE;
	}
	return bRet;

}

BOOL CRussiaGame::IsFullLine(int Row)
{
	BOOL bRet = TRUE;
	for (int i = 0; i < 12; i++)
	{
		if (m_iMap[i][Row] == 0)
		{
			bRet = FALSE;
			
		}
	}
	return bRet;
}

void CRussiaGame::EliminateLine()
{
	for (int Row = 19; Row >= 0; Row--)
	{
		if (IsFullLine(Row))
		{
			for(int i = Row - 1; i >= 0; i--)
			{
				for (int j = 0; j < 12; j++)
				{
					m_iMap[j][i+1] = m_iMap[j][i];
				}
			}
			Row += 1;
			score += 100;
			InvalidateRect(m_hWnd, NULL, TRUE);
		}
	}
}

int CRussiaGame::GetCurrentBlockID()
{
	srand((unsigned)time(0));
	return rand() % 6;
}

BOOL CRussiaGame::OnInit()
{
	
	nNum = GetCurrentBlockID();
	m_currentBlock = m_blockModeArray[nNum];
	return TRUE;
}

BOOL CRussiaGame::SystemInit()
{
	BOOL bRet = FALSE;
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			m_iMap[i][j] = 0;
		}
	}
	bRet = TRUE;
	InvalidateRect(m_hWnd, NULL, TRUE);
	return bRet;
}

UINT CRussiaGame::SetBlockTimer(HWND hWnd, UINT uMsg)
{
	UINT bRet = SetTimer(hWnd, (UINT)(this), 500, TimerProc);
	return bRet;
}

void CALLBACK CRussiaGame::TimerProc(HWND hWnd, UINT uMsg, UINT nTime, DWORD dwTime)
{
	CRussiaGame * pThis = static_cast<CRussiaGame *>((CRussiaGame *)nTime);
	if (pThis)
	{
		pThis->SetNewBlock(hWnd, uMsg, nTime, dwTime);
	}    

}

BOOL CRussiaGame::KillBlockTimer(HWND hWnd, UINT message)
{
	KillTimer(hWnd, (UINT)(this));
	return TRUE;
}

LRESULT CRussiaGame::WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	/*PAINTSTRUCT ps;
	HDC hdc;*/
	BOOL bRet = false;
	switch (message)
	{
	case WM_COMMAND:
		bRet = OnCommand(hWnd, message, wParam, lParam);
		break;
	case WM_PAINT:
		bRet = OnPaint(hWnd, message, wParam, lParam);
		break;
	case WM_CREATE:
		bRet = OnCreate(hWnd, message, wParam, lParam);
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
	case WM_CTLCOLOREDIT:
		{
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_NOTIFY:
		{
			/*if (wParam == CRICH_EDIT)
			{
				bRet = OnMouseMove(hWnd, message, wParam, lParam);
			}*/
		}
		break;
	case WM_ERASEBKGND:
		////OnEraseBkgnd(hWnd, message, wParam, lParam);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return bRet;
}

LRESULT CRussiaGame::OnCommand(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	BOOL bRet = false;
	int wmId, wmEvent;
	wmId    = LOWORD(wParam);
	wmEvent = HIWORD(wParam);
	// 分析菜单选择:
	switch (wmId)
	{
	case IDM_ABOUT:
		DialogBox(m_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return bRet;
}

BOOL CRussiaGame::OnCreate(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	BOOL bRet = false;

	SetBlockTimer(hWnd, uMsg);
	return bRet;
}

BOOL CRussiaGame::OnSize(HWND hWnd, UINT uMsg, WPARAM wParam,LPARAM lParam)
{
	BOOL bRet = false;
	RECT clientRect;
	GetClientRect(m_hWnd, &clientRect);
	GameRect.left = clientRect.left;
	GameRect.top = clientRect.top;
	GameRect.right = 25 * 12;
	GameRect.bottom = clientRect.bottom;
	return bRet;
}

INT_PTR CALLBACK CRussiaGame::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
