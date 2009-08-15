#if !defined(AFX_MODELESSDLG_H__F75BEA02_8D91_11D8_8A36_004095358525__INCLUDED_)
#define AFX_MODELESSDLG_H__F75BEA02_8D91_11D8_8A36_004095358525__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ModelessDlg.h : header file
//

//#define MLS_SINGLETON   0x0001
#define MLS_REINIT		0x0002

/////////////////////////////////////////////////////////////////////////////
// CModelessDlg dialog

class CModelessDlg : public CDialog
{
// Construction
public:
	CModelessDlg();   // standard constructor
	virtual BOOL Create(UINT nIDTemplate, CWnd* pParent = NULL, 
		CDocument *pDoc= NULL);
	//{{AFX_VIRTUAL(CPalCopyDlg)
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL
// implementation
public:
	CDocument *GetDocument()	{	return mpDoc;		}
	BOOL IsVisible()			{	return mbVisible;	}
	BOOL Show(BOOL bVisible);
	virtual void Apply();
	virtual void Initialize();
	virtual void Update();
	DWORD ModifyFlags(DWORD dwRemove, DWORD dwAdd);
protected:
	BOOL mbVisible;
	CDocument *mpDoc;
	DWORD mFlags;
	//{{AFX_MSG(CModelessDlg)
	virtual void OnOK();			// IDOK: applies and hides
	virtual void OnCancel();		// IDCANCEL: Cancel just hides
	afx_msg void OnApplyNow();		// ID_APPLY_NOW Applies just applies (well, duh!)
	afx_msg void OnReInit();		// IDRETRY: calls Initialize()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODELESSDLG_H__F75BEA02_8D91_11D8_8A36_004095358525__INCLUDED_)
