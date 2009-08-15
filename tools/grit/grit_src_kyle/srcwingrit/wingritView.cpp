// wingritView.cpp : implementation of the CWingritView class
//

#include "stdafx.h"
#include "wingrit.h"

#include "wingritDoc.h"
#include "wingritView.h"

#include "mainfrm.h"
#include "cldib_core.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWingritView

IMPLEMENT_DYNCREATE(CWingritView, CView)

BEGIN_MESSAGE_MAP(CWingritView, CView)
	//{{AFX_MSG_MAP(CWingritView)
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWingritView construction/destruction

CWingritView::CWingritView() : mZoom(1<<8), mptOrg(0,0), 
	mbDown(FALSE), mptLast(0,0)
{

}

CWingritView::~CWingritView()
{

}

BOOL CWingritView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CWingritView drawing

void CWingritView::OnDraw(CDC* pdc)
{
	CWingritDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CLDIB *dib= pDoc->GetDib();

	if(dib != NULL)
	{
		int ww= dib_get_width(dib), hh= dib_get_height(dib);
		dib_blit(pdc->GetSafeHdc(), 
			mptOrg.x, mptOrg.y, mZoom*ww>>8, mZoom*hh>>8, 
			dib, 
			0, 0, ww, hh, 
			SRCCOPY);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CWingritView diagnostics

#ifdef _DEBUG
void CWingritView::AssertValid() const
{
	CView::AssertValid();
}

void CWingritView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWingritDoc* CWingritView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWingritDoc)));
	return (CWingritDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWingritView message handlers


void CWingritView::OnTextNotify(UINT iMsg, UINT nID)
{
	::AfxGetMainWnd()->Invalidate();
}

void CWingritView::OnMButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	mbDown= TRUE;
	mptLast= point;
	
	//CView::OnMButtonDown(nFlags, point);
}

void CWingritView::OnMButtonUp(UINT nFlags, CPoint point) 
{
	mbDown= FALSE;
	
	//CView::OnMButtonUp(nFlags, point);
}

void CWingritView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(mbDown)
	{
		mptOrg += point-mptLast;
		mptLast= point;
		Invalidate();
	}
	else
		CView::OnMouseMove(nFlags, point);
}

BOOL CWingritView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	int zoom= mZoom;
	if(zDelta>0 && zoom<(16<<8))
		zoom <<= 1;
	else if(zDelta<0 && zoom>64)
		zoom >>= 1;
	if(zoom != mZoom)
	{
		mZoom= zoom;
		Invalidate();
	}
	
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}
