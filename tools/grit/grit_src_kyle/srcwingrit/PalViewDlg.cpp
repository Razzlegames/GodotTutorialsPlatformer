// PalViewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "wingrit.h"
#include "PalViewDlg.h"
#include "wingritdoc.h"
#include "cldib_core.h"
//-#include "freeimage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPalViewDlg dialog

//inline COLORREF rgb2clr(RGBQUAD &rgb)
//{	return RGB(rgb.rgbRed, rgb.rgbGreen, rgb.rgbBlue);		}


CPalViewDlg::CPalViewDlg()  : CModelessDlg()
{
	//{{AFX_DATA_INIT(CPalViewDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CPalViewDlg::Create(CWnd* pParent, CDocument *pDoc)
{
	if( !CModelessDlg::Create(CPalViewDlg::IDD, pParent, pDoc) )
		return FALSE;

	return TRUE;
}

void CPalViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CModelessDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPalViewDlg)
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_PAL_ID, mPalInfoId);
	DDX_Control(pDX, IDC_PAL_VAL, mPalInfoVal);
	DDX_Control(pDX, IDC_PAL_VIEW, mPalView);
}


BEGIN_MESSAGE_MAP(CPalViewDlg, CModelessDlg)
	//{{AFX_MSG_MAP(CPalViewDlg)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPalViewDlg message handlers

BOOL CPalViewDlg::OnInitDialog() 
{
	CModelessDlg::OnInitDialog();
	
	mPalView.SetWindowPos(NULL, 0, 0, 130, 130, 
		SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW | SWP_DRAWFRAME);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPalViewDlg::Initialize()
{
	UpdateData(TRUE);

	//UpdateData(FALSE);
}

void CPalViewDlg::Apply() 
{
	UpdateData(TRUE);
	ASSERT(mpDoc);
}

void CPalViewDlg::Update()
{
	Invalidate();
}

void CPalViewDlg::OnPaint() 
{
	//CPaintDC dc(this); // device context for painting	

	PAINTSTRUCT ps;
	BeginPaint(&ps);
	EndPaint(&ps);

	// palview
	CClientDC dc(&mPalView);
	DrawPalView(&dc);

	// Do not call CDialogBar::OnPaint() for painting messages
}

// redraw complete palview
void CPalViewDlg::DrawPalView(CDC *pdc)
{
	CLDIB *dib= ((CWingritDoc*)mpDoc)->GetDib();

	pdc->FillSolidRect(0, 0, 128, 120, ::GetSysColor(COLOR_3DFACE));

	if(dib == NULL)
		return;

	if(dib_get_bpp(dib) <= 8)
	{
		int ii, x=1, y=1;
		int nclrs= dib_get_nclrs(dib);
		RGBQUAD *pal= dib_get_pal(dib);

		for(ii=0; ii<nclrs;ii++)
		{
			pdc->FillSolidRect(x, y, 6, 6, rgb2clr(pal[ii]));
			x += 8;
			if( (ii&0x0f) == 0x0f)
			{	x= 1;		y += 8;		}
		}
	}
	else
	{

	}

/*	CPoint *ppt= (CPoint*)(gRects+RC_PAL_VIEW), org;
	org= pdc->SetViewportOrg(*ppt);
	// erase background
	pdc->FillSolidRect(0, 0, 128, 128, 0);
	int ii=0, x=1, y=1;
	while(ii<PAL_MAX)

	for(ii=0; ii<PAL_MAX;ii++)
	{
		pdc->FillSolidRect(x, y, WW, HH, mPal[ii]);
		x += DX;
		if( (ii&0x0f) == 0x0f)
		{	x= 1;		y += DY;		}
	}
	*/
}

void CPalViewDlg::OnMouseMove(UINT nFlags, CPoint pt) 
{
	CRect rcPal;
	// convert to screen coords
	ClientToScreen(&pt);
	mPalView.GetClientRect(&rcPal);
	mPalView.ClientToScreen(&rcPal);

	mPalInfoId.SetWindowText("");
	mPalInfoVal.SetWindowText("");

	if(!rcPal.PtInRect(pt))
		return;

	int clrid;
	pt -= rcPal.TopLeft();

	clrid= pt.x/8 + pt.y/8*16;

	CLDIB *dib= ((CWingritDoc*)mpDoc)->GetDib();
	if(dib == NULL)
		return;

	if(dib_get_nclrs(dib) <= clrid)
		return;

	RGBQUAD rgb= dib_get_pal(dib)[clrid];
	CString str;

	str.Format("%02xh", clrid);
	mPalInfoId.SetWindowText(str);
	str.Format("r%d, g%d, b%d", rgb.rgbRed, rgb.rgbGreen, rgb.rgbBlue);
	mPalInfoVal.SetWindowText(str);

	//CDialog::OnMouseMove(nFlags, pt);
}
