
#include "stdafx.h"
#include "FileFilter.h"

#include <string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// === CFileFilter ====================================================

CFileFilter::CFileFilter(int type, const CString &name)
{
	mDlgType= type;
	mDlgName= name;
	mFilterSize= 0;
	mCurrID= -1;
	mFilters= NULL;
}

CFileFilter::~CFileFilter()
{
	Destroy();
}

void CFileFilter::Destroy()
{
	mFilterSize= 0;
	if(mFilters)
	{	delete[] mFilters; mFilters= NULL;	}
}

void CFileFilter::SetDlgName(const CString &name)
{
	if(!name.IsEmpty())
		mDlgName= name;
}

// init filter list from resource string
BOOL CFileFilter::SetFilters(int nSize, const UINT *filters)
{
	if(nSize<1)
		return FALSE;
	int ii, jj;

	CString *strings= new CString[nSize];
	for(ii=0, jj=0; ii<nSize; ii++)
	{
		if(strings[jj].LoadString(filters[ii]))
			jj++;
	}
	SetFilters(jj, strings);
	delete[] strings;
	return (jj>0);
}

// no type info
BOOL CFileFilter::SetFilters(int nSize, const CString *filters)
{
	if(nSize<1)
		return FALSE;

	int ii;
	if(mFilterSize != 0)
		Destroy();
	mFilterSize= nSize;
	mFilters= new CString[mFilterSize];
	for(ii=0; ii<mFilterSize; ii++)
		mFilters[ii]= filters[ii];

	return TRUE;
}

//! Set from a (fully prepared) filter string.
BOOL CFileFilter::SetFilters(const char *filters)
{
	int ii, nSize=0;
	const char *str= filters, *ch;

	// Count number of '|'s
	while( ch=strchr(str, '|') )
	{
		nSize++;
		str= ch+1;
	}

	nSize /= 2;
	if(nSize < 1)
		return FALSE;

	// Destroy old stuff and fill list
	if(mFilterSize != 0)
		Destroy();
	mFilterSize= nSize;
	mFilters= new CString[mFilterSize];

	str= filters;
	for(ii=0; ii<mFilterSize; ii++)
	{
		// Find even '|';
		ch= strchr(str , '|');
		ch= strchr(ch+1, '|')+1;

		// init mFilter
		mFilters[ii]= CString(str, ch-str);
		str= ch;
	}

	return TRUE;
}


// fpath is formatted as "dir\title.ext"
// GetFileTitle, GetFileDir and GetFileExt retrieve the title, dir and ext
// parts respectively
BOOL CFileFilter::GetFileTitle(const CString &fpath, CString &ftitle)
{
	if(fpath.IsEmpty())
	{
		ftitle= "";
		return FALSE;
	}
	int pos= fpath.ReverseFind('\\');
	pos++;	// skips '\\' OR goes to fpath[0] if no '\\' found
	ftitle= fpath.Mid(pos);
	pos= ftitle.ReverseFind('.');
	if(pos != -1)	// extension found, remove
		ftitle= ftitle.Left(pos);
	
	return TRUE;
}

BOOL CFileFilter::GetFileDir(const CString &fpath, CString &fdir)
{
	int pos= fpath.ReverseFind('\\');

	if(pos == -1)	// no '\' found
	{	
		fdir= "";
		return FALSE;
	}
	fdir= fpath.Left(pos);
	
	return TRUE;
}

BOOL CFileFilter::GetFileExt(const CString &fpath, CString &fext)
{
	int pos= fpath.ReverseFind('.');

	// No extension found (and watch for '.' in dir)
	if(pos == -1 || fpath.Find('\\', pos) > 0)
	{	
		fext= "";
		return FALSE;
	}
	fext= fpath.Right(fpath.GetLength() - pos - 1);
	return TRUE;
}

BOOL CFileFilter::GetFileName(const CString &fpath, CString &fname)
{
	int pos= fpath.ReverseFind('\\');
	if(pos>=0)
		fname= fpath.Right(fpath.GetLength() - pos - 1);
	else
		fname= fpath;
	
	return TRUE;
}

// Get the long name of a file, since the $#^%#@ Windows shell
// passes the short one, *grumble*
BOOL CFileFilter::GetLongPath(CString &fpath, CString *pflong)
{
	if(pflong == NULL)
		pflong= &fpath;
	
	// no "~", i.e. already long
	if(fpath.Find("~") == -1)
	{
		*pflong=fpath;
		return TRUE;
	}
	
	// file is short
	WIN32_FIND_DATA fd;
	if( ::FindFirstFile(fpath, &fd) == INVALID_HANDLE_VALUE )
		return FALSE;
	
	CString fname(fd.cFileName);
	if(fpath.Find("\\") == -1)	// no src dir, we're done
	{
		*pflong= fname;
		return TRUE;
	}	
	
	if(fname.Find("\\") == -1)	// src dir, but no dst dir, add one
	{
		// one
		// directory 
		// level
		// at 
		// a 
		// time
		// It's absolutely insane, but the only way :(
		
		CString fdir, str, dirfull, dirtitle;
		GetFileDir(fpath, fdir);
		
		while(fdir.Find("~") != -1)
		{
			::FindFirstFile(fdir, &fd);		// c:\foo~1\bar\test
			str= fd.cFileName;
			GetFileTitle(str, dirtitle);	// test
			GetFileDir(fdir, str);			// c:\foo~1\bar;
			fdir= str;

			dirfull= dirtitle + "\\" + dirfull;		// \test
		}
		fname= fdir+"\\"+dirfull+fname;
		
	}
	*pflong= fname;

	return TRUE;
}


// find the first filter that includes the fext extension
// or of just the fext entension (bSingle==TRUE)
int CFileFilter::GetFilterID(const CString &fext, 
	BOOL bSingle /*= FALSE*/) const
{
	if(fext.IsEmpty())
		return -1;

	int ii;
	CString str("*.");
	str += fext;
	for(ii=0; ii<mFilterSize; ii++)
	{
		if(mFilters[ii].Find(str) >= 0)	// found one
		{
			if(!bSingle || mFilters[ii].Find(';') == -1)
				return ii;	// exactly one or don't care
		}
	}

	return -1;
}

// get the primary extension of mFilter[id]
CString CFileFilter::GetFilterExt(int id) const
{
	if(id<0 || id > mFilterSize)
		return "";
	int pos;
	CString str;
	pos= mFilters[id].Find('|');
	if(pos<0)
		return "";
	// account for initial '|' and "*." in filter
	str= mFilters[id].Mid(pos+3);
	pos= str.FindOneOf(";|");
	if(pos<0)
		return "";
	str= str.Left(pos);
	return str;
}

void CFileFilter::SetCurrFilterID(int id)
{
	if(id<0 || id > mFilterSize)
		return;
	mCurrID= id;
}

int CFileFilter::DoPromptFilePath(CString &fpath, BOOL bOpen)
{
	int ii;
	CString fdir, ftitle, fltr;
	// get dir from fpath or profile
	if(!GetFileDir(fpath, fdir))
	{
		CString flast= 
			::AfxGetApp()->GetProfileString("Last File", mDlgName, NULL);
		GetFileDir(flast, fdir);
	}
	if(mCurrID<0)
		mCurrID= AfxGetApp()->GetProfileInt("Last Filter", mDlgName, 0);

	// setup filters
	for(ii=0; ii<mFilterSize; ii++)
		fltr += mFilters[ii];
	
	DWORD dwFlags;
	if(bOpen)	// loading file: no init name
	{
		dwFlags= OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
	}
	else		// storing file: init name is fpath's title
	{
		dwFlags= OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
		GetFileTitle(fpath, ftitle);
	}

	CFileDialog fdlg(bOpen, NULL, ftitle, dwFlags, fltr, NULL);
	fdlg.m_ofn.lpstrInitialDir= fdir;
	fdlg.m_ofn.nFilterIndex= mCurrID+1;
	fdlg.m_ofn.lpstrTitle= mDlgName;

	if(fdlg.DoModal() == IDOK)
	{
		fpath= fdlg.GetPathName();
		GetFileDir(fpath, fdir);
		mCurrID= fdlg.m_ofn.nFilterIndex-1;
		CString fext;
		// no extension given, make one up
		if(!GetFileExt(fpath, fext) && mCurrID >= 0)
		{
			fext= GetFilterExt(mCurrID);
			// unless the filter's extension is invalid
			if(fext.IsEmpty() || fext.FindOneOf("*?") >= 0)
			{
				fpath.Empty();
				return FF_BAD;
			}
			fpath += "." + fext;
		}	

		::AfxGetApp()->WriteProfileString("Last File", mDlgName, fpath);
		::AfxGetApp()->WriteProfileInt("Last Filter", mDlgName, mCurrID);
		return GetFilterID(fext, true);
	}
	fpath.Empty();
	return FF_CANCEL;
}
