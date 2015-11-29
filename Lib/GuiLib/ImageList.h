#ifndef IMAGE_LIST_H_A1728955_E41B_4bf7_B552_5678A0D3441E
#define IMAGE_LIST_H_A1728955_E41B_4bf7_B552_5678A0D3441E
/*
*************************************************************************
ģ����  : Image List Reference
�ļ���  : ImageList.h    
ʵ�ֹ���: ImageList
����    : �ܽ�
�汾    : 
����	��An image list is a collection of images of the same size, each of which can be referred to by its index.
-------------------------------------------------------------------------
��ע    :
-------------------------------------------------------------------------
�޸ļ�¼:   
��  ��          �汾        �޸���      �޸�����

*************************************************************************
* �汾����(c)  <2014.8.27>  ��������Ȩ��                                     *
************************************************************************/

#include <Windows.h>
#include <commctrl.h>

#pragma comment(lib,"comctl32.lib")

namespace GuiLib
{
	class CImageList
	{
	public:
		CImageList(HWND hParent, HMENU hMenu, HINSTANCE hInst);
		~CImageList();

	public:
		virtual BOOL Create(int x, int y, int nWidth, int nHeight, DWORD dwStyle, int nIndex[], int nSize);
		//HWND GetTBHandle(){return m_hwndTB;}

	private:
		HMENU m_hMenu;
		HWND m_hParent;
		HINSTANCE m_hInst;
	};
}

#endif