#include "stdafx.h"
#include "Block.h"

CBlock::CBlock()
{
	Zero = ORI; 
	One = ORI;
	Two = ORI;
	Three = ORI; 
	Four = ORI; 
	Five = ORI;
	Six = ORI; 
}

CBlock::CBlock(CBlockPoint P0, CBlockPoint P1, CBlockPoint P2, CBlockPoint P3)
		:Point0(P0), Point1(P1), Point2(P2), Point3(P3)
{
	Zero = ORI; 
	One = ORI;
	Two = ORI;
	Three = ORI; 
	Four = ORI; 
	Five = ORI;
	Six = ORI; 
}

void CBlock::GetX(int &xMax, int &xMin)
{
	int x[4];
	 x[0] = Point0.m_x;
	 x[1] = Point1.m_x;
	 x[2] = Point2.m_x;
	 x[3] = Point3.m_x;
	int Max = x[0];
	int Min = x[0];
	for (int i = 1; i < 4; i++)
	{
		if (Max < x[i])
		{
			Max = x[i];
		}
		if (Min > x[i])
		{
			Min = x[i];
		}
	}
	xMax = Max;
	xMin = Min;
}
void CBlock::GetY(int &yMax, int &yMin)
{
	int y[4];
	 y[0] = Point0.m_y;
	 y[1] = Point1.m_y;
	 y[2] = Point2.m_y;
	 y[3] = Point3.m_y;
	int Max = y[0];
	int Min = y[0];
	for (int i = 1; i < 4; i++)
	{
		if (Max < y[i])
		{
			Max = y[i];
		}
		if (Min > y[i])
		{
			Min = y[i];
		}
	}
	yMax = Max;
	yMin = Min;
}

const RECT& CBlock::GetBlockRect()
{	
	RECT rect;
	int xMax, xMin, yMax, yMin;
	GetX(xMax, xMin);
	GetY(yMax, yMin);
	rect.left = xMin;
	rect.top = yMin;
	rect.right = xMax;
	rect.bottom = yMax;
	return rect;
}

void CBlock::ChangeShape(int nNum)
{
	switch(nNum)
	{
	case 0:
		ChangeBlockZero();
		break;
	case 1:
		ChangeBlockOne();
		break;
	case 2:
		ChangeBlockTwo();
		break;
	case 3:
		ChangeBlockThree();
		break;
	case 4:
		ChangeBlockFour();
		break;
	case 5:
		ChangeBlockFive();
		break;
	case 6:
		ChangeBlockSix();
		break;
	}
}

BOOL CBlock::ChangeBlockZero()
{
	BOOL bRet = FALSE;
	if (Zero == ORI)
	{
		Point0.m_x += 1;
		Point0.m_y -= 1;
		Point2.m_x -= 1;
		Point2.m_y += 1;
		Point3.m_x -= 2;
		Point3.m_y += 2;
		Zero = ONE;
		bRet = TRUE;
	}
	else if (Zero == ONE)
	{
		Point0.m_x -= 1;
		Point0.m_y += 1;
		Point2.m_x += 1;
		Point2.m_y -= 1;
		Point3.m_x += 2;
		Point3.m_y -= 2;
		Zero = ORI;
		bRet = TRUE;
	}
	return bRet;
}

BOOL CBlock::ChangeBlockOne()
{
	BOOL bRet = FALSE;
	return bRet;
}

BOOL CBlock::ChangeBlockTwo()
{
	BOOL bRet = FALSE;
	if (Two == ORI)
	{
		Point1.m_x += 1;
		Point1.m_y += 1;
		Two = ONE;
		bRet = TRUE;
	}
	else if (Two == ONE)
	{
		Point0.m_x -= 1;
		Point0.m_y += 1;
		Two = TWO;
		bRet = TRUE;
	}
	else if (Two == TWO)
	{
		Point3.m_x -= 1;
		Point3.m_y -= 1;
		Two = THREE;
		bRet = TRUE;
	}
	else if (Two == THREE)
	{
		Point0.m_x += 1;
		Point0.m_y -= 1;
		Point1.m_x -= 1;
		Point1.m_y -= 1;
		Point3.m_x += 1;
		Point3.m_y += 1;
		Two = ORI;
		bRet = TRUE;
	}
	
	return bRet;
}

BOOL CBlock::ChangeBlockThree()
{
	BOOL bRet = FALSE;
	if (Three == ORI)
	{
		Point2.m_x -= 1;
		Point3.m_x -= 1;
		Point3.m_y -= 2;
		Three = ONE;
		bRet = TRUE;
	}
	else if (Three == ONE)
	{
		Point2.m_x += 1;
		Point3.m_x += 1;
		Point3.m_y += 2;
		Three = ORI;
		bRet = TRUE;
	}
	return bRet;
}

BOOL CBlock::ChangeBlockFour()
{
	BOOL bRet = FALSE;
	if (Four == ORI)
	{
		Point1.m_y += 1;
		Point2.m_x += 2;
		Point2.m_y += 1;
		Four = ONE;
		bRet = TRUE;
	}
	else if (Four == ONE)
	{
		Point1.m_y -= 1;
		Point2.m_x -= 2;
		Point2.m_y -= 1;
		Four = ORI;
		bRet = TRUE;
	}
	return bRet;
}

BOOL CBlock::ChangeBlockFive()
{
	BOOL bRet = FALSE;
	if (Five == ORI)
	{
		Point0.m_y += 2;
		Point3.m_x -= 2;
		Point3.m_y += 2;
		Five = ONE;
		bRet = TRUE;
	}
	else if (Five == ONE)
	{
		Point0.m_x += 1;
		Point3.m_x -= 1;
		Point3.m_y -= 2;
		Five = TWO;
		bRet = TRUE;
	}
	else if (Five == TWO)
	{
		Point0.m_y -= 2;
		Point3.m_x += 2;
		Point3.m_y -= 2;
		Five = THREE;
		bRet = TRUE;
	}
	else if (Five == THREE)
	{
		Point0.m_x -= 1;
		Point3.m_x += 1;
		Point3.m_y += 2;
		Five = ORI;
		bRet = TRUE;
	}
	return bRet;
}

BOOL CBlock::ChangeBlockSix()
{
	BOOL bRet = FALSE;
	if (Six == ORI)
	{
		Point0.m_x -= 1;
		Point1.m_x += 1;
		Point1.m_y -= 2;
		Six = ONE;
		bRet = TRUE;
	}
	else if (Six == ONE)
	{
		Point0.m_y += 2;
		Point1.m_x += 2;
		Point1.m_y += 2;
		Six = TWO;
		bRet = TRUE;
	}
	else if(Six == TWO)
	{
		Point0.m_x += 1;
		Point1.m_x -= 1;
		Point1.m_y += 2;
		Six = THREE;
		bRet = TRUE;
	}
	else if (Six == THREE)
	{
		Point0.m_y -= 2;
		Point1.m_x -= 2;
		Point1.m_y -= 2;
		Six = ORI;
		bRet = TRUE;
	}
	return bRet;
}

