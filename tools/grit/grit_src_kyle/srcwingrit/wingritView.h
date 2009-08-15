// wingritView.h : interface of the CWingritView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINGITVIEW_H__C9C68B24_E8A1_4C20_8813_286350AFF5B6__INCLUDED_)
#define AFX_WINGITVIEW_H__C9C68B24_E8A1_4C20_8813_286350AFF5B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CWingritView : public CView
{
protected: // create from serialization only
	CWingritView();
	DECLARE_DYNCREATE(CWingritView)

// Attributes
public:
	CWingritDoc* GetDocument();

// Operations
public:
	static void OnTextNotify(UINT iMsg, UINT nID);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWingritView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWingritView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int mZoom;	// NOTE: .8 fixed point!
	CPoint mptOrg;
	BOOL mbDown;
	CPoint mptLast;

// Generated message map functions
protected:
	//{{AFX_MSG(CWingritView)
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in wingritView.cpp
inline CWingritDoc* CWingritView::GetDocument()
   { return (CWingritDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINGITVIEW_H__C9C68B24_E8A1_4C20_8813_286350AFF5B6__INCLUDED_)
