// wingritDoc.cpp : implementation of the CWingritDoc class
//

#include "stdafx.h"
#include "wingrit.h"

#include "wingritDoc.h"
#include "freeimage.h"
#include "fi.h"
#include "filefilter.h"

#include <cldib.h>

#include "gritdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWingritDoc

IMPLEMENT_DYNCREATE(CWingritDoc, CDocument)

BEGIN_MESSAGE_MAP(CWingritDoc, CDocument)
	//{{AFX_MSG_MAP(CWingritDoc)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_EDIT_QUANT_WU, OnEditQuantWu)
	ON_COMMAND(ID_EDIT_QUANT_NN, OnEditQuantNn)
	ON_COMMAND(ID_EDIT_CONVERTTO555, OnEditConvertto555)
	ON_COMMAND(ID_VIEW_GBAEXPORT, OnGbaExport)
	ON_UPDATE_COMMAND_UI(ID_VIEW_GBAEXPORT, OnUpdateGbaExport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWingritDoc construction/destruction

void CWingritDoc::UpdateMainWnd()
{
	if(::AfxGetMainWnd() != NULL)
		::AfxGetMainWnd()->SendMessage(WM_COMMAND, 
			MAKEWPARAM(IDM_DOC_UPDATE,0), NULL);
}

CWingritDoc::CWingritDoc()
{
	mpFidib=NULL;
	mDib= NULL;

}

CWingritDoc::~CWingritDoc()
{
	dib_free(mDib);
	mDib= NULL;
}

void CWingritDoc::OnFileOpen() 
{	OnOpenDocument(NULL);				}


BOOL CWingritDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	dib_free(mDib);
	mDib= NULL;
	UpdateMainWnd();

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

BOOL CWingritDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{	
	static CFileFilter ffOpen(ID_FILE_OPEN, "Open");

	// Make filter list if none exists yet
	if(ffOpen.GetFilterSize() == 0)
	{
		const int NFILTERS=7;
		FREE_IMAGE_FORMAT iFilters[NFILTERS]= 
		{
			FIF_BMP, FIF_GIF, FIF_JPEG, FIF_PCX, 
			FIF_PNG, FIF_TARGA, FIF_TIFF 
		};

		// Get full list
		int fif_count;
		char buffy[1024];
		
		fif_count= fiFillOfnFilter(buffy, FIF_MODE_WRITE, iFilters, 7);
		ffOpen.SetFilters(buffy);
	}

	// Actual loading stuff
	CString fpath(lpszPathName), fext;
	if(lpszPathName == NULL)
		ffOpen.DoPromptFilePath(fpath, true);

	if(!ffOpen.GetFileExt(fpath, fext))
		return FALSE;
	fext.MakeLower();

	CLDIB *dib= dib_load(fpath, NULL);

	if(dib == NULL)
		return FALSE;

	dib_free(mDib);
	mDib= dib;

	SetPathName(fpath, TRUE);
	UpdateAllViews(NULL);
	UpdateMainWnd();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CWingritDoc serialization

void CWingritDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CWingritDoc diagnostics

#ifdef _DEBUG
void CWingritDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWingritDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWingritDoc commands

void CWingritDoc::OnEditQuantWu() 
{
	if(mDib == NULL || dib_get_bpp(mDib) <= 8)
		return;

	if(!dib_convert(mDib, 8, 0))
	{
		SetPathName(GetPathName());
		UpdateAllViews(NULL);
		UpdateMainWnd();
	}
}

// TODO: remove
void CWingritDoc::OnEditQuantNn() 
{
	return;
}

void CWingritDoc::OnEditConvertto555() 
{
	if(mpFidib == NULL)
		return;
	if(dib_get_bpp(mDib)<=8)
		return;

	if(!dib_convert(mDib, 16, 0))
	{
		SetPathName(GetPathName());
		UpdateAllViews(NULL);
		UpdateMainWnd();
	}	
}

void CWingritDoc::OnGbaExport() 
{
	static CxpGbaDlg dlg;
	dlg.SetDstPath(GetPathName());
	dlg.SetDib(GetDib());
	dlg.DoModal();		
}

void CWingritDoc::OnUpdateGbaExport(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(mDib != NULL);	
}

void CWingritDoc::SetTitle(LPCTSTR lpszTitle) 
{
	CString title, str;

	if(lpszTitle == NULL)
	{
		if(GetPathName().IsEmpty())
			title.LoadString(AFX_IDS_UNTITLED);
		else
			CFileFilter::GetFileName(GetPathName(), title);
	}
	else
		title= lpszTitle;
	
	if(mDib)
	{
		str.Format("%s [%dx%d@%d]", title, 
			dib_get_width(mDib), dib_get_height(mDib), 
			dib_get_bpp(mDib));
	}
	
	CDocument::SetTitle(str);
}
