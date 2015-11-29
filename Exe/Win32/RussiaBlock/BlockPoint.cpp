#include "stdafx.h"
#include "BlockPoint.h"

CBlockPoint::CBlockPoint(int x, int y)
{
	m_x = x;
	m_y = y;
}

CBlockPoint::CBlockPoint(const CBlockPoint& Pt)
{
	m_x = Pt.m_x;
	m_y = Pt.m_y;
}

