// LogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "LogDlg.h"

#include <stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogDlg dialog


CLogDlg::CLogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLogDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLogDlg)
	mSummary = _T("");
	//}}AFX_DATA_INIT
}


void CLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogDlg)
	DDX_Text(pDX, IDC_SUMMARY, mSummary);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLogDlg, CDialog)
	//{{AFX_MSG_MAP(CLogDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogDlg message handlers

void CLogDlg::SetText(const CString &str)
{
	mSummary= str;
}

void CLogDlg::SetTextFromFile(const CString &fpath)
{
	CFile file;
	
	if( !file.Open(fpath, CFile::modeRead | CFile::typeBinary) )
		return;

	long fsize= file.GetLength();
	file.Read(mSummary.GetBuffer(fsize), fsize);
	mSummary.ReleaseBuffer(fsize);

	file.Close();
}
