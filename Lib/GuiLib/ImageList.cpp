#include "ImageList.h"

namespace GuiLib
{
	CImageList::CImageList(HWND hParent, HMENU hMenu, HINSTANCE hInst):m_hParent(hParent), m_hMenu(hMenu), m_hInst(hInst)
	{

	}

	CImageList::~CImageList()
	{

	}

	BOOL CImageList::Create(int x, int y, int nWidth, int nHeight, DWORD dwStyle, int nIndex[], int nSize)
	{
		return TRUE;
	}


}