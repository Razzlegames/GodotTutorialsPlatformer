// wingritDoc.h : interface of the CWingritDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINGITDOC_H__8CF00F0C_BE87_472A_8B24_992F3326A3D7__INCLUDED_)
#define AFX_WINGITDOC_H__8CF00F0C_BE87_472A_8B24_992F3326A3D7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "freeimage.h"
typedef struct CLDIB CLDIB;
 
class CWingritDoc : public CDocument
{
protected: // create from serialization only
	CWingritDoc();
	DECLARE_DYNCREATE(CWingritDoc)

// Attributes
public:
	CLDIB *GetDib() const {	return mDib;	}

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWingritDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void SetTitle(LPCTSTR lpszTitle);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWingritDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	FIBITMAP *mpFidib;
	CLDIB *mDib;
protected:
	void UpdateMainWnd();

// Generated message map functions
protected:
	//{{AFX_MSG(CWingritDoc)
	afx_msg void OnFileOpen();
	afx_msg void OnEditQuantWu();
	afx_msg void OnEditQuantNn();
	afx_msg void OnEditConvertto555();
	afx_msg void OnGbaExport();
	afx_msg void OnUpdateGbaExport(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


UINT GetActiveColors(FIBITMAP *dib);
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINGITDOC_H__8CF00F0C_BE87_472A_8B24_992F3326A3D7__INCLUDED_)
