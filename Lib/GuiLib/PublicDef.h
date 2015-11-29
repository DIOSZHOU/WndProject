#ifndef PUBLIC_DEF_H_CAFC0DB6_42D6_4d77_AA06_5071A314685A
#define PUBLIC_DEF_H_CAFC0DB6_42D6_4d77_AA06_5071A314685A

#include <Windows.h>
#include <tchar.h>
#include <shlobj.h>
#include <Commdlg.h>
#include <vector>
//#include <string>
#include <iostream>

#include "Wnd.h"
#include "Edit.h"
#include "ToolBar.h"
#include "StatusBar.h"
#include "ComboBox.h"
#include "ReBar.h"

//using namespace std;	//vector
using std::vector;
//typedef std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR>> tstring;

#define  MAX_FILE_PATH	4096

#define  WM_FINDREPLACE		(WM_USER + 1)

#define  CRICH_EDIT		(WM_USER + 1000)


#endif