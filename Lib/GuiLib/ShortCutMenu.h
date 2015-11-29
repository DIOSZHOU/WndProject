#ifndef SHORT_CUT_MENU_H_30232DC4_217A_4658_B8CB_BFBEBD82BB40
#define SHORT_CUT_MENU_H_30232DC4_217A_4658_B8CB_BFBEBD82BB40
/*
*************************************************************************
模块名  : Using Menus 
文件名  : ShortCutMenu.h 
实现功能: 
作者    : 周健
版本    : 
-------------------------------------------------------------------------
备注    :
-------------------------------------------------------------------------
修改记录:   
日  期          版本        修改人      修改内容

*************************************************************************
* 版本所有(c)  <2014.7.25>  保留所有权利                                     *
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