
// owndraw_ctrl.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Cowndraw_ctrlApp:
// See owndraw_ctrl.cpp for the implementation of this class
//

class Cowndraw_ctrlApp : public CWinApp
{
public:
	Cowndraw_ctrlApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern Cowndraw_ctrlApp theApp;