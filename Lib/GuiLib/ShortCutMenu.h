#ifndef SHORT_CUT_MENU_H_30232DC4_217A_4658_B8CB_BFBEBD82BB40
#define SHORT_CUT_MENU_H_30232DC4_217A_4658_B8CB_BFBEBD82BB40
/*
*************************************************************************
ģ����  : Using Menus 
�ļ���  : ShortCutMenu.h 
ʵ�ֹ���: 
����    : �ܽ�
�汾    : 
-------------------------------------------------------------------------
��ע    :
-------------------------------------------------------------------------
�޸ļ�¼:   
��  ��          �汾        �޸���      �޸�����

*************************************************************************
* �汾����(c)  <2014.7.25>  ��������Ȩ��                                     *
************************************************************************/
#pragma once
#include <Windows.h>

class CShortCutMenu
{
public:
	CShortCutMenu(HMENU hMenu);
	~CShortCutMenu();

public:
	BOOL DisplayShortCutMenu(HWND hWnd, POINT pt, int index);

protected:
	HMENU m_hMenu;
};

#endif