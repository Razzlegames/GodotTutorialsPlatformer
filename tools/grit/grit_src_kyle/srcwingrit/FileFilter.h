//
// File functionality
//   Not exactly proper functionality, but it'll do for now
//


#if !defined(FILEFILTER_H)
#define FILEFILTER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// === CFileFilter ====================================================
// for parsing pathnames to file title/dir & ext and 
// help for using file filters


#define FF_BAD		-1
#define FF_CANCEL	-2
// a filter 'ID' is the 0-based index of the filter list
// (even though, internally, OFN works with 1-based IDs)
class CFileFilter
{
public:
	// initialization
	CFileFilter(int type, const CString &name);
	~CFileFilter();
	BOOL SetFilters(int nSize, const UINT *filters);
	BOOL SetFilters(int nSize, const CString *filters);
	BOOL SetFilters(const char *filters);
	// file stuff: (also in CFileDialog, but why go all the way out there)
	static BOOL GetFileTitle(const CString &fpath, CString &ftitle);
	static BOOL GetFileDir(const CString &fpath, CString &fdir);
	static BOOL GetFileExt(const CString &fpath, CString &fext);
	static BOOL GetFileName(const CString &fpath, CString &fname);
	static BOOL GetLongPath(CString &fpath, CString *flong= NULL);
	// filter and CFileDialog stuff
	int DoPromptFilePath(CString &fpath, BOOL bOpen);
	int GetFilterSize() const			{	return mFilterSize;	}
	int GetFilterID(const CString &fext, BOOL bSingle= FALSE) const;
	CString GetFilterExt(int id) const;
	int GetCurrFilterID() const		{	return mCurrID;		}
	void SetCurrFilterID(int id);
	int GetDlgType() const				{	return mDlgType;	}
	const CString &GetDlgName() const	{	return mDlgName;	}
	void SetDlgName(const CString &name);
private:
	void Destroy();
	int mDlgType;
	CString mDlgName;
	int mFilterSize;
	int mCurrID;
	CString *mFilters;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(FILEFILTER_H)
