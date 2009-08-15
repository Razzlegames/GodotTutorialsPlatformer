#if !defined(AFX_PALVIEWDLG_H__170E72A2_C0AF_469F_94BD_2E385C047900__INCLUDED_)
#define AFX_PALVIEWDLG_H__170E72A2_C0AF_469F_94BD_2E385C047900__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PalViewDlg.h : header file
//

#include "ModeLessDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CPalViewDlg dialog

class CPalViewDlg : public CModelessDlg
{
// Construction
public:
	CPalViewDlg();   // standard constructor
	BOOL Create(CWnd* pParent = NULL, CDocument *pDoc= NULL);
// Dialog Data
	//{{AFX_DATA(CPalViewDlg)
	enum { IDD = IDD_PAL_VIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Overrides
	//{{AFX_VIRTUAL(CPalViewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:
	void DrawPalView(CDC *pdc);
public:
	virtual void Initialize();
	virtual void Apply();
	virtual void Update();
protected:
	CStatic mPalInfoId;
	CStatic mPalInfoVal;
	CStatic mPalView;
	//{{AFX_MSG(CPalViewDlg)
	afx_msg void OnMouseMove(UINT nFlags, CPoint pt);
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PALVIEWDLG_H__170E72A2_C0AF_469F_94BD_2E385C047900__INCLUDED_)
