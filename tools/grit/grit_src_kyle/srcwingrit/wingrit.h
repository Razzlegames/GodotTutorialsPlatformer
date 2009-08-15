// wingrit.h : main header file for the WINGIT application
//

#if !defined(AFX_WINGRIT_H__B576776F_1933_46EB_A84A_C015F29A42B0__INCLUDED_)
#define AFX_WINGRIT_H__B576776F_1933_46EB_A84A_C015F29A42B0__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

void GetRootDir(CString &str);


/////////////////////////////////////////////////////////////////////////////
// CWingritApp:
// See wingrit.cpp for the implementation of this class
//

class CWingritApp : public CWinApp
{
public:
	CWingritApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWingritApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWingritApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINGRIT_H__B576776F_1933_46EB_A84A_C015F29A42B0__INCLUDED_)
