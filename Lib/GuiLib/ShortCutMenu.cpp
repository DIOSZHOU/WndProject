#include "ShortCutMenu.h"

CShortCutMenu::CShortCutMenu(HMENU hMenu) : m_hMenu(hMenu)
{

}

CShortCutMenu::~CShortCutMenu()
{
	if (m_hMenu)
	{
		DestroyMenu(m_hMenu);
	}
}

BOOL CShortCutMenu::DisplayShortCutMenu(HWND hWnd, POINT pt, int index)
{
	BOOL bRet = FALSE;
	HMENU m_hPopMenu = GetSubMenu(m_hMenu, index);
	ClientToScreen(hWnd, (LPPOINT) &pt); 
	bRet = TrackPopupMenu(m_hPopMenu, TPM_LEFTALIGN | TPM_LEFTBUTTON, pt.x, pt.y, 0, hWnd, NULL);
	return bRet;
}