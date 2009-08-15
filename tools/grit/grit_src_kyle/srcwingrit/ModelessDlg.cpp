// ModelessDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ModelessDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModelessDlg dialog


CModelessDlg::CModelessDlg() : CDialog()
{
	mbVisible= FALSE;
	mpDoc= NULL;
}

BEGIN_MESSAGE_MAP(CModelessDlg, CDialog)
	//{{AFX_MSG_MAP(CModelessDlg)
	ON_BN_CLICKED(ID_APPLY_NOW, OnApplyNow)
	ON_BN_CLICKED(IDRETRY, OnReInit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModelessDlg message handlers

BOOL CModelessDlg::Create(UINT nIDTemplate, CWnd* pParent /*=NULL*/, 
	CDocument *pDoc /*=NULL*/) 
{
	if(!CDialog::Create(nIDTemplate, pParent))
		return FALSE;
	mpDoc= pDoc;
	Initialize();
	return TRUE;
}

void CModelessDlg::PostNcDestroy()
{
	delete this;
}

void CModelessDlg::OnOK()
{
	Apply();
	Show(FALSE);
}

void CModelessDlg::OnCancel()
{
	Show(FALSE);
}

void CModelessDlg::OnApplyNow()
{
	Apply();
}

void CModelessDlg::OnReInit()
{
	Initialize();
}

// --- operations ---
BOOL CModelessDlg::Show(BOOL bVisible)
{
	// initialize at show up
	if( (mFlags & MLS_REINIT) && mbVisible==FALSE && bVisible == TRUE)
		Initialize();
	mbVisible= bVisible;

	return ShowWindow(bVisible ? SW_SHOW : SW_HIDE);
}

DWORD CModelessDlg::ModifyFlags(DWORD dwRemove, DWORD dwAdd)
{
	mFlags &= ~dwRemove;
	mFlags |= dwAdd;
	return mFlags;
}

void CModelessDlg::Initialize()
{}

void CModelessDlg::Apply()
{}

void CModelessDlg::Update()
{}
