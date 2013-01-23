// huanhuan.h : main header file for the HUANHUAN application
//

#if !defined(AFX_HUANHUAN_H__7F507DA3_3317_4E1F_9ADB_19492D42A657__INCLUDED_)
#define AFX_HUANHUAN_H__7F507DA3_3317_4E1F_9ADB_19492D42A657__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHuanhuanApp:
// See huanhuan.cpp for the implementation of this class
//

class CHuanhuanApp : public CWinApp
{
public:
	CHuanhuanApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHuanhuanApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHuanhuanApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HUANHUAN_H__7F507DA3_3317_4E1F_9ADB_19492D42A657__INCLUDED_)
