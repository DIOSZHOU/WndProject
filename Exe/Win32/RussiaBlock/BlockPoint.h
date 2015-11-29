#ifndef POINT_H__
#define POINT_H__

class CBlockPoint
{
public:
	CBlockPoint()
	{
		m_x = 0;
		m_y = 0;
	}
	CBlockPoint(int x, int y);
	CBlockPoint(const CBlockPoint& Pt);
	const CBlockPoint& operator=(const CBlockPoint& P)
	{
		m_x = P.m_x;
		m_y = P.m_y;
		return *this;
	}
// 	const CBlockPoint& operator=(const int x, const int y)
// 	{
// 		m_x = x;
// 		m_y = y;
// 		return *this;
// 	}
	const CBlockPoint& operator+=(const int y)  
	{
		m_y += y;
		return *this;
	}

	CBlockPoint& operator-=(const CBlockPoint& P)
	{
		m_x -= P.m_x;
		m_y -= P.m_y;
		return *this;
	}

	/*CBlockPoint& operator-=(const int y)
	{
		m_y -= y;
		return *this;
	}*/
	~CBlockPoint(){}

	int m_x;
	int m_y;
};


#endif