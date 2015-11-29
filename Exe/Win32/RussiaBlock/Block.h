#ifndef CBLOCK_H__
#define CBLOCK_H__
#include "BlockPoint.h"

typedef enum
{
	ORI = 0,
	ONE,
	TWO,
	THREE,
}DIRECT;

class CBlock
{
public:
	CBlock();
	CBlock(CBlockPoint P0, CBlockPoint P1, CBlockPoint P2, CBlockPoint P3);
	~CBlock(){}
	void GetX(int &xMax, int &xMin);
	void GetY(int &yMax, int &yMin);
	const RECT& GetBlockRect();
	BOOL ChangeBlockZero();
	BOOL ChangeBlockOne();
	BOOL ChangeBlockTwo();
	BOOL ChangeBlockThree();
	BOOL ChangeBlockFour();
	BOOL ChangeBlockFive();
	BOOL ChangeBlockSix();
	
	void ChangeShape(int nNum);

//private:
	DIRECT Zero, One, Two, Three, Four, Five, Six; 
	CBlockPoint Point0;
	CBlockPoint Point1;
	CBlockPoint Point2;
	CBlockPoint Point3;
};

#endif