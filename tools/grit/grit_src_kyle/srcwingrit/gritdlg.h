#if !defined(AFX_DLGS_H__06717BD8_84A4_486B_)
#define AFX_DLGS_H__06717BD8_84A4_486B_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// gritdlg.h : header file

enum eCprs
{	CPRS_NONE=0, CPRS_LZ, CPRS_HUFF, CPRS_RLE, CPRS_HDR, CPRS_END };

enum eFileTypes
{	FMT_C=0, FMT_GAS, FMT_BIN, FMT_GBFS, FMT_GRF, /*FMT_O,*/ FMT_END };

enum eGfxModes
{	GFX_MODE_TILE=0, GFX_MODE_BMP, GFX_MODE_BMP_A, GFX_MODE_BMP_T	};

typedef struct CLDIB	CLDIB;
typedef struct GritRec	GritRec;


/////////////////////////////////////////////////////////////////////////////
// CxpGbaDlg dialog

class CxpGbaDlg : public CDialog
{
// Construction
public:
	CxpGbaDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CxpGbaDlg();
// implementation
	//- void SetSrcPath(const CString &fname);
	void SetDstPath(const char *path);
	void SetDib(CLDIB *dib)	{	mpDib= dib;	}
	//- CString	mSrcPath;
	CString mDstDir;
	CString mDstTitle;
	// CString mDstPath;	// in DDX part
	CLDIB *mpDib;
	GritRec *mgr;
// Attributes:
	BOOL IsTiled() const		{	return mGfxMode==GFX_MODE_TILE;		}
	BOOL IsMap() const			{	return IsTiled() && mbMap==TRUE;	}
	BOOL IsRdx() const			{	return IsMap() && mbMapRdx==TRUE;	}
	BOOL IsObjCstm() const		{	return mbObjCustom;					}
	BOOL IsAreaCstm() const		{	return moAreaSize==0;				}
	BOOL IsRiffable() const
	{	return mFileType==FMT_C || mFileType==FMT_GAS;			}
	BOOL IsRiffed() const		
	{	return (IsRiffable() && mbRiff) || mFileType==FMT_GRF;	}
// Dialog Data
	//{{AFX_DATA(CxpGbaDlg)
	enum { IDD = IDD_XP_GBA };
	BOOL	mbGfx;
	int		mGfxBpp;
	int		mGfxCprs;
	int		mGfxMode;
	CString	mGfxTransStr;
	BOOL	mbMap;
	int		moMapFormat;
	BOOL	mbMapRdx;
	BOOL	mbMapRdxFlip;
	BOOL	mbMapRdxPal;
	BOOL	mbMetaPal;
	int		mMapCprs;
	int		mMapOffset;
	BOOL	mbPal;
	int		mPalStart;
	int		mPalCount;
	BYTE	mPalTrans;
	BOOL	mbObjCustom;
	int		moObjShape;
	int		moObjSize;
	int		mObjHorz;
	int		mObjVert;
	int		moAreaSize;
	int		mAreaLeft;
	int		mAreaTop;
	int		mAreaWidth;
	int		mAreaHeight;
	CString	mDstPath;
	int		mFileType;
	int		moVarChunk;
	BOOL	mbHeader;
	BOOL	mbAppend;
	BOOL	mbSymChk;
	CString	mSymName;
	BOOL	mbTileset;
	CString	mTilesetPath;
	BOOL	mbRiff;
	//}}AFX_DATA
	CString	mSummary;
	BOOL mbBusy;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CxpGbaDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	void UpdatePal();
	void UpdateGfx();
	void UpdateObj();
	void UpdateMap();
	void UpdateRdx();
	void UpdateArea();
	void UpdateRiff();
	void UpdateSummary();
	void UpdateOptString();
	BOOL UpdateGritRec(BOOL b2gr);
	BOOL Validate();
	// Generated message map functions
	//{{AFX_MSG(CxpGbaDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPalChk();
	afx_msg void OnGfxChk();
	afx_msg void OnSelendokGfxMode();
	afx_msg void OnMapChk();
	afx_msg void OnObjCustom();
	afx_msg void OnSelendokFileType();
	afx_msg void OnVarChk();
	afx_msg void OnFileBrowse();
	virtual void OnOK();
	afx_msg void OnValidate();
	afx_msg void OnMapRdx();
	afx_msg void OnTilesetChk();
	afx_msg void OnTilesetBrowse();
	afx_msg void OnRiffChk();
	//}}AFX_MSG
	afx_msg void OnAreaFormat(int nID);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGS_H__06717BD8_84A4_486B_)
