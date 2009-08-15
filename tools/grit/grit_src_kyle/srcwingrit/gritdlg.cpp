//
// gritdlg.cpp
//   gritdlg implementation file
// (20050908 - 20070402, cearn)
//
// === NOTES === 
// * Minor changes for libgrit 0.7


#include "stdafx.h"
#include "wingrit.h"
#include "resource.h"
#include "gritdlg.h"
#include "FileFilter.h"
#include "LogDlg.h"

#include <cldib.h>
#include <grit.h>

#include "fi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// === CONSTANTS ======================================================

extern const int cObjSizes[12][2];

const int cObjSizes[12][2]= 
{
	{1,1}, {2,2}, {4,4}, {8,8}, 
	{2,1}, {4,1}, {4,2}, {8,4}, 
	{1,2}, {1,4}, {2,4}, {4,8}
};


// to avoid msg-box on empty field
static void AFXAPI DDX_IntHack(CDataExchange* pDX, int nIDC, int& value)
{
	if(pDX->m_bSaveAndValidate)
	{
		char str[32];
		if(::GetWindowText(pDX->PrepareEditCtrl(nIDC), str, 32) != 0)
			DDX_Text(pDX, nIDC, value);
		else 
			value= 0;
	}
	else
		DDX_Text(pDX, nIDC, value);
}

/////////////////////////////////////////////////////////////////////////////
// CxpGbaDlg dialog

CxpGbaDlg::CxpGbaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CxpGbaDlg::IDD, pParent)
{
	mDstDir= "";
	mDstTitle= "";
	mgr= grit_alloc();
	//- mgr= xgi_create();
	//{{AFX_DATA_INIT(CxpGbaDlg)
	mbGfx = TRUE;
	mGfxBpp = 3;
	mGfxCprs = GRIT_CPRS_OFF;
	mGfxMode = 0;
	mGfxTransStr = _T("FF00FF");
	mbMap = FALSE;
	moMapFormat = 0;
	mbMapRdx = TRUE;
	mbMapRdxFlip = TRUE;
	mbMapRdxPal = TRUE;
	mbMetaPal = FALSE;
	mMapCprs = GRIT_CPRS_OFF;
	mMapOffset = 0;
	mbPal = TRUE;
	mPalStart = 0;
	mPalCount = 256;
	mPalTrans = 0;
	mbObjCustom = FALSE;
	moObjShape = 0;
	moObjSize = 0;
	mObjHorz = 1;
	mObjVert = 1;
	moAreaSize = 1;
	mAreaLeft = 0;
	mAreaTop = 0;
	mAreaWidth = 8;
	mAreaHeight = 8;
	mDstPath = _T("");
	mFileType = GRIT_FTYPE_S;
	moVarChunk = 1;
	mbHeader = TRUE;
	mbAppend = FALSE;
	mbSymChk = FALSE;
	mSymName = _T("bar");
	mbTileset = FALSE;
	mTilesetPath = _T("");
	mbRiff = FALSE;
	//}}AFX_DATA_INIT
	mSummary = "";
	mbBusy= FALSE;
}

CxpGbaDlg::~CxpGbaDlg()
{
	grit_free(mgr);
}

void CxpGbaDlg::DoDataExchange(CDataExchange* pDX)
{
	mbBusy=TRUE;
	CDialog::DoDataExchange(pDX);
	DDX_IntHack(pDX, IDC_START, mPalStart);
	DDV_MinMaxInt(pDX, mPalStart, 0, 255);
	DDX_IntHack(pDX, IDC_COUNT, mPalCount);
	DDV_MinMaxInt(pDX, mPalCount, 0, 256);
	DDX_IntHack(pDX, IDC_OBJ_HORZ, mObjHorz);
	DDV_MinMaxInt(pDX, mObjHorz, 0, 256);
	DDX_IntHack(pDX, IDC_OBJ_VERT, mObjVert);
	DDV_MinMaxInt(pDX, mObjVert, 0, 256);
	DDX_IntHack(pDX, IDC_LEFT, mAreaLeft);
	DDX_IntHack(pDX, IDC_TOP, mAreaTop);
	DDX_IntHack(pDX, IDC_WIDTH, mAreaWidth);
	DDX_IntHack(pDX, IDC_HEIGHT, mAreaHeight);
	//{{AFX_DATA_MAP(CxpGbaDlg)
	DDX_Check(pDX, IDC_IMG_CHK, mbGfx);
	DDX_CBIndex(pDX, IDC_IMG_BPP, mGfxBpp);
	DDX_CBIndex(pDX, IDC_IMG_CPRS, mGfxCprs);
	DDX_CBIndex(pDX, IDC_IMG_MODE, mGfxMode);
	DDX_Text(pDX, IDC_IMG_TRANS, mGfxTransStr);
	DDV_MaxChars(pDX, mGfxTransStr, 8);
	DDX_Check(pDX, IDC_MAP_CHK, mbMap);
	DDX_Radio(pDX, IDC_MAP_FLAT, moMapFormat);
	DDX_Check(pDX, IDC_MAP_RDX, mbMapRdx);
	DDX_Check(pDX, IDC_MAP_RDX_FLIP, mbMapRdxFlip);
	DDX_Check(pDX, IDC_MAP_RDX_PAL, mbMapRdxPal);
	DDX_Check(pDX, IDC_META_PAL, mbMetaPal);
	DDX_CBIndex(pDX, IDC_MAP_CPRS, mMapCprs);
	DDX_Text(pDX, IDC_MAP_OFS, mMapOffset);
	DDX_Check(pDX, IDC_PAL_CHK, mbPal);
	DDX_Text(pDX, IDC_PAL_TRANS, mPalTrans);
	DDV_MinMaxByte(pDX, mPalTrans, 0, 255);
	DDX_Check(pDX, IDC_OBJ_CUSTOM, mbObjCustom);
	DDX_Radio(pDX, IDC_OBJ_SQR, moObjShape);
	DDX_Radio(pDX, IDC_OBJ_8, moObjSize);
	DDX_Radio(pDX, IDC_AREA_CSM, moAreaSize);
	DDX_Text(pDX, IDC_FILE_PATH, mDstPath);
	DDX_CBIndex(pDX, IDC_FILE_TYPE, mFileType);
	DDX_Radio(pDX, IDC_VAR_8, moVarChunk);
	DDX_Check(pDX, IDC_FILE_HDR, mbHeader);
	DDX_Check(pDX, IDC_FILE_CAT, mbAppend);
	DDX_Check(pDX, IDC_VAR_CHK, mbSymChk);
	DDX_Text(pDX, IDC_VAR_NAME, mSymName);
	DDV_MaxChars(pDX, mSymName, 256);
	DDX_Check(pDX, IDC_TILESET_CHK, mbTileset);
	DDX_Text(pDX, IDC_TILESET_PATH, mTilesetPath);
	DDX_Check(pDX, IDC_RIFF_CHK, mbRiff);
	//}}AFX_DATA_MAP
	mbBusy= FALSE;
}


BEGIN_MESSAGE_MAP(CxpGbaDlg, CDialog)
	//{{AFX_MSG_MAP(CxpGbaDlg)
	ON_BN_CLICKED(IDC_PAL_CHK, OnPalChk)
	ON_BN_CLICKED(IDC_IMG_CHK, OnGfxChk)
	ON_CBN_SELENDOK(IDC_IMG_MODE, OnSelendokGfxMode)
	ON_BN_CLICKED(IDC_MAP_CHK, OnMapChk)
	ON_BN_CLICKED(IDC_OBJ_CUSTOM, OnObjCustom)
	ON_CBN_SELENDOK(IDC_FILE_TYPE, OnSelendokFileType)
	ON_BN_CLICKED(IDC_VAR_CHK, OnVarChk)
	ON_BN_CLICKED(IDC_FILE_BROWSE, OnFileBrowse)
	ON_BN_CLICKED(ID_APPLY_NOW, OnValidate)
	ON_BN_CLICKED(IDC_MAP_RDX, OnMapRdx)
	ON_BN_CLICKED(IDC_TILESET_CHK, OnTilesetChk)
	ON_BN_CLICKED(IDC_TILESET_BROWSE, OnTilesetBrowse)
	ON_BN_CLICKED(IDC_RIFF_CHK, OnRiffChk)
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(IDC_AREA_CSM, IDC_AREA_SEL, OnAreaFormat)
END_MESSAGE_MAP()


// === Implementation =================================================


//! Update palette controls for changes made elsewhere
void CxpGbaDlg::UpdatePal()
{
	GetDlgItem(IDC_START)->EnableWindow(mbPal);
	GetDlgItem(IDC_COUNT)->EnableWindow(mbPal);
	GetDlgItem(IDC_PAL_TRANS)->EnableWindow(mbPal);
}


//! Update image controls for changes made elsewhere
void CxpGbaDlg::UpdateGfx()
{
	GetDlgItem(IDC_IMG_MODE)->EnableWindow(mbGfx);
	GetDlgItem(IDC_IMG_BPP)->EnableWindow(mbGfx);
	GetDlgItem(IDC_IMG_CPRS)->EnableWindow(mbGfx);

	GetDlgItem(IDC_IMG_TRANS)->EnableWindow(mbGfx && mGfxMode==GFX_MODE_BMP_T);
}

//! Update map controls for changes made elsewhere
void CxpGbaDlg::UpdateMap()
{
	BOOL bMap= IsMap();

	GetDlgItem(IDC_MAP_CHK)->EnableWindow(IsTiled());

	GetDlgItem(IDC_MAP_FLAT)->EnableWindow(bMap);
	GetDlgItem(IDC_MAP_SBB)->EnableWindow(bMap);
	GetDlgItem(IDC_MAP_AFF)->EnableWindow(bMap);
	GetDlgItem(IDC_MAP_RDX)->EnableWindow(bMap);
	UpdateRdx();
	GetDlgItem(IDC_META_PAL)->EnableWindow(bMap);
	GetDlgItem(IDC_MAP_CPRS)->EnableWindow(bMap);
	GetDlgItem(IDC_MAP_OFS)->EnableWindow(bMap);

	GetDlgItem(IDC_TILESET_CHK)->EnableWindow(bMap);

	BOOL bTileset= bMap && mbTileset;
	GetDlgItem(IDC_TILESET_PATH)->EnableWindow(bTileset);
	GetDlgItem(IDC_TILESET_BROWSE)->EnableWindow(bTileset);
}


//! Update tile reduction controls for changes made elsewhere
void CxpGbaDlg::UpdateRdx()
{
	BOOL bRdx= IsRdx();
	GetDlgItem(IDC_MAP_RDX_PAL)->EnableWindow(bRdx);
	GetDlgItem(IDC_MAP_RDX_FLIP)->EnableWindow(bRdx);
}

//! Update meta-tiling controls for changes made elsewhere
void CxpGbaDlg::UpdateObj()
{
	int ii;

	BOOL bFixed=FALSE, bCustom=FALSE;
	if(IsTiled())	// if tiles on 
		mbObjCustom==TRUE ? bCustom=TRUE : bFixed=TRUE;
	
	// custom checkbox
	GetDlgItem(IDC_OBJ_CUSTOM)->EnableWindow(IsTiled());
	// fixed sizes
	for(ii=IDC_OBJ_SQR; ii<=IDC_OBJ_TALL; ii++)
		GetDlgItem(ii)->EnableWindow(bFixed);
	for(ii=IDC_OBJ_8; ii<=IDC_OBJ_64; ii++)
		GetDlgItem(ii)->EnableWindow(bFixed);
	// var sizes
	GetDlgItem(IDC_OBJ_HORZ)->EnableWindow(bCustom);
	GetDlgItem(IDC_OBJ_VERT)->EnableWindow(bCustom);
}

//! Update area controls for changes made elsewhere
void CxpGbaDlg::UpdateArea()
{
	BOOL bCustom= IsAreaCstm();

	GetDlgItem(IDC_LEFT)->EnableWindow(bCustom);
	GetDlgItem(IDC_TOP)->EnableWindow(bCustom);
	GetDlgItem(IDC_WIDTH)->EnableWindow(bCustom);
	GetDlgItem(IDC_HEIGHT)->EnableWindow(bCustom);
}

void CxpGbaDlg::UpdateRiff()
{
	GetDlgItem(IDC_RIFF_CHK)->EnableWindow(IsRiffable());

	if(GetDlgItem(IDC_IMG_CPRS)->IsWindowEnabled())
		if(IsRiffed() && mGfxCprs == CPRS_NONE)
			mGfxCprs= CPRS_HDR;

	if(GetDlgItem(IDC_MAP_CPRS)->IsWindowEnabled())
		if(IsRiffed() && mMapCprs == CPRS_NONE)
			mMapCprs= CPRS_HDR;	
}

// TODO: reformat for new options
void CxpGbaDlg::UpdateSummary()
{
	// anti-bounce code (trust me, you need this)
	if(!mbBusy)
		UpdateData(TRUE);
	DWORD dw;
	CString sPal, sGfx, sArea, sMeta, sMap, sFiles;
	CString str;
	BOOL bPal, bGfx, bMeta, bMap, bArea;

	ASSERT(moMapFormat<3);

	bPal= mbPal;
	bGfx= mbGfx;
	bArea= mbGfx || mbMap;
	bMeta= GetDlgItem(IDC_OBJ_CUSTOM)->IsWindowEnabled();
	bMap= mbMap && IsTiled();

	// TODO: Validation!!!

	// --- image ---
	if(bGfx)
	{
		// TODO: transparent color
		GetDlgItem(IDC_IMG_MODE)->GetWindowText(str);
		sGfx= "gfx: " + str;
		if(mGfxMode == GFX_MODE_BMP_T)
		{
			RGBQUAD rgb= str2rgb(mGfxTransStr);
			str.Format(" (%d, %d, %d)", rgb.rgbRed, rgb.rgbGreen, rgb.rgbBlue);
			sGfx += str;
		}
		str.Format(", %dbpp, cprs: ", (1<<mGfxBpp));
		sGfx += str;
		GetDlgItem(IDC_IMG_CPRS)->GetWindowText(str);
		sGfx += str;
	}
	else
		sGfx= "gfx: -";
	
	// --- area ---
	if(bArea)
	{
		dw= moAreaSize+IDC_AREA_CSM;
		if(dw == IDC_AREA_CSM)
		{
			sArea.Format("area: (%d,%d)-(%d,%d)   [%d, %d]", 
				mAreaLeft, mAreaTop, mAreaLeft+mAreaWidth, mAreaTop+mAreaHeight, 
				mAreaWidth, mAreaHeight);
		}
		else if(dw == IDC_AREA_IMG)
		{
			sArea.Format("area: (%d,%d)-(%d,%d)   [%d, %d]", 
				0, 0, dib_get_width(mpDib), dib_get_height(mpDib), 
				dib_get_width(mpDib), dib_get_height(mpDib));
		}
	}
	else
		sArea="area: -";

	// --- object ---
	if(bMeta)
	{
		SIZE sz;
		if(mbObjCustom)
		{	sz.cx= mObjHorz; sz.cy= mObjVert;	}
		else
		{
			sz.cx= cObjSizes[moObjShape*4 + moObjSize][0];
			sz.cy= cObjSizes[moObjShape*4 + moObjSize][1];
		}

		sMeta.Format("meta: %dx%d tiles (%dx%d px)", 
			sz.cx, sz.cy, sz.cx<<3, sz.cy<<3);
	}
	else
		sMeta= "obj: -";

	// --- map ---
	if(bMap)
	{
		dw= moMapFormat+IDC_MAP_FLAT;
		switch(dw)
		{
		case IDC_MAP_FLAT:
			str= "flat";	break;
		case IDC_MAP_SBB:
			str= "in SBBs";	break;
		case IDC_MAP_AFF:
			str= "affine";	break;
		}
		sMap.Format("map: %s, +%d ", str, mMapOffset);
		if(IsRdx())
		{
			sMap += "reduced [t";
			if(mbMapRdxFlip)
				sMap += "f";
			if(mbMapRdxPal)
				sMap += "p";
			sMap += "]";
		}
	}
	else
		sMap= "map: -";
	
	// --- palette ---
	if(bPal)
	{
		if(mPalStart+mPalCount>256)
			mPalCount= 256-mPalStart;
		//GetDlgItem(IDC_START)->GetWindowText(str);
		sPal.Format("pal: %d-%d [%d]", mPalStart, mPalStart+mPalCount, mPalCount);

		// TODO: palette transparency index
	}
	else
		sPal= "pal: -";

	// --- files ---
	// TODO: add tileset file

	switch(mFileType)
	{
	case FMT_C:		// C (+h)
		str= mDstTitle + ".c   ";
		break;
	case FMT_GAS:		// assembly (+h)
		str= mDstTitle + ".s   ";
		break;
	case -1:		// COFF (+h)
		str= mDstTitle + ".o   ";
		break;
	case FMT_BIN:
		str.Empty();
		if(bPal)
			str += mDstTitle + ".pal.bin   ";
		if(bGfx)
			str += mDstTitle + ".img.bin   ";
		if(bMap)
			str += mDstTitle + ".map.bin   ";
	case FMT_GBFS:
		str= mDstTitle + ".gbfs   ";
	}

	sFiles= "files:  ";

	if(mbHeader)
		sFiles += mDstTitle + ".h   ";
	sFiles += str;

	mSummary.Format("%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s", sGfx, sArea, 
		sMeta, sMap, sPal, sFiles);
	GetDlgItem(IDC_SUMMARY)->SetWindowText(mSummary);
}


void CxpGbaDlg::UpdateOptString()
{
	// anti-bounce code (trust me, you need this)
	if(!mbBusy)
		UpdateData(TRUE);

	//DWORD dw;
	CString sPal, sGfx, sArea, sMeta, sMap, sFile;
	CString str;
	BOOL bPal, bGfx, bMeta, bMap, bArea;

	ASSERT(moMapFormat<3);

	bPal= mbPal;
	bGfx= mbGfx;
	bArea= mbGfx || mbMap;
	bMeta= GetDlgItem(IDC_OBJ_CUSTOM)->IsWindowEnabled();
	bMap= mbMap && IsTiled();


	// --- Output options ---
	sFile.Format(" -o [dir]/%s.%s", mDstTitle, cFileTypes[mFileType]);
	if(mbSymChk)
		sFile += " -s " + mSymName;
	if(!mbHeader)
		sFile += " -fh!";
	if(mbAppend)
		sFile += " -fa";
	if(mbMap && mbTileset)
	{
		CFileFilter::GetFileName(mTilesetPath, str);
		sFile += " -fx [dir]/" + str;
	}

	// TODO: add rest of options


	// --- Image ---

	// --- Area ---

	// --- Mapping ---

	// --- Meta ---

	// --- Palette ---

	// --- Rest ---

}


BOOL CxpGbaDlg::UpdateGritRec(BOOL b2gr)
{
	DWORD dw;
	char str[MAXPATHLEN];

	// TODO: al/gfx trans ; img modes ; tileset

	if(b2gr)	// data -> gr
	{
		UpdateData(TRUE);

		SetDstPath(mDstPath);

		// clear previous gr data
		grit_clear(mgr);
		grs_clear(mgr->shared);

		mgr->bExport= true;

		// Yes, yes, very wasteful
		mgr->srcDib= dib_clone(mpDib);

		mgr->bHeader= mbHeader==TRUE;
		mgr->bAppend= mbAppend==TRUE;
		mgr->fileType= mFileType;

		// TODO check whether this is all OK!!
		if(mbSymChk)
			mgr->symName= strdup(mSymName);
		else
			mgr->symName= strdup(mDstTitle);

		// make sure it's a valid C varname
		str_fix_ident(mgr->symName, mgr->symName, 
			strlen(mgr->symName));

		sprintf(str, "%s/%s.%s", mDstDir, mDstTitle, cFileTypes[mFileType]);
		mgr->dstPath= strdup(str);

		// --- palette ---
		if(mbPal)
		{
			mgr->palProcMode= GRIT_EXPORT;

			mgr->palStart= mPalStart;
			mgr->palEnd= mPalStart+mPalCount;
			if(mgr->palEnd > 256)
				mgr->palEnd= 256;

			if(mPalTrans != 0)
			{
				mgr->palHasAlpha= true;
				mgr->palAlphaId= mPalTrans;
			}
		}

		// --- image ---
		// NOTE: we should probably always process the image, 
		//   just not necessarily export
		if(1)
		{
			if(mbGfx)
				mgr->gfxProcMode= GRIT_EXPORT;

			switch(mGfxMode)
			{
			case GFX_MODE_TILE:
				mgr->gfxMode= GRIT_GFX_TILE;
				break;
			case GFX_MODE_BMP:
				mgr->gfxMode= GRIT_GFX_BMP;
				break;
			case GFX_MODE_BMP_A:
				mgr->gfxMode= GRIT_GFX_BMP_A;
				break;
			case GFX_MODE_BMP_T:
				mgr->gfxMode= GRIT_GFX_BMP;

				// Empty color && non-zero pal-trans -> use pal-trans
				// Empty color otherwise: use FF00FF
				// non-empty: use non-empty
				dw= strlen(mGfxTransStr);

				if( dw != 0 || !mgr->palHasAlpha )
				{
					if(dw==0)
						mGfxTransStr= "FF00FF";
					mgr->gfxAlphaColor= str2rgb(mGfxTransStr);
					mgr->gfxHasAlpha= true;
				}
				break;				
			}

			mgr->gfxOffset= 0;
			mgr->gfxBpp= 1<<mGfxBpp;
			mgr->gfxCompression= mGfxCprs;

		}
		// --- map ---
		if(mbMap)
		{
			mgr->mapProcMode= GRIT_EXPORT;	
			mgr->mapCompression= mMapCprs;

			if(mbMapRdx)
			{
				mgr->mapRedux |= GRIT_RDX_TILE;
				if(mbMapRdxFlip)
					mgr->mapRedux |= GRIT_RDX_FLIP;
				if(mbMapRdxPal)
					mgr->mapRedux |= GRIT_RDX_PAL;
			}

			if(mbMetaPal)
				mgr->mapRedux |= GRIT_META_PAL;

			mgr->mapLayout= moMapFormat;
			mgr->mapOffset= mMapOffset;

			// Add external tileset stuff
			if(mbTileset)
			{
				if(mTilesetPath.IsEmpty())
					mTilesetPath= mDstDir + mDstTitle + "tiles.bmp";
				mgr->shared->tilePath= strdup(mTilesetPath);
				mgr->gfxIsShared= true;
			}
		}

		if(mbObjCustom)
		{
			mgr->metaWidth= mObjHorz;
			mgr->metaHeight= mObjVert;
		}
		else
		{
			dw= moObjShape*4 + moObjSize;
			mgr->metaWidth= cObjSizes[dw][0];
			mgr->metaHeight= cObjSizes[dw][1];
		}
		// area
		dw= moAreaSize+IDC_AREA_CSM;
		if(dw == IDC_AREA_CSM)
		{
			mgr->areaLeft  = mAreaLeft;
			mgr->areaTop   = mAreaTop;
			mgr->areaRight = mAreaLeft+mAreaWidth;
			mgr->areaBottom= mAreaTop+mAreaHeight;
		}
		else
		{
			mgr->areaLeft  = 0;
			mgr->areaTop   = 0;
			mgr->areaRight = dib_get_width(mpDib);
			mgr->areaBottom= dib_get_height(mpDib);
		}

		mgr->gfxDataType= moVarChunk;
		mgr->mapDataType= moVarChunk;
		mgr->palDataType= moVarChunk;

		// RIFF overrides
		if(IsRiffed())
		{
			mgr->bRiff= true;
			if(mgr->gfxCompression==GRIT_CPRS_OFF)
				mgr->gfxCompression= GRIT_CPRS_HEADER;

			if(mgr->mapCompression==GRIT_CPRS_OFF)
				mgr->mapCompression= GRIT_CPRS_HEADER;

			if(mgr->palCompression==GRIT_CPRS_OFF)
				mgr->palCompression= GRIT_CPRS_HEADER;
		}
	}
	else		// gr -> data
	{
		// --- file ---
		mbHeader = mgr->bHeader;
		mbAppend = mgr->bAppend;
		
		// --- palette ---
		mPalStart= mgr->palStart;
		mPalCount= mgr->palEnd-mgr->palStart;
		mPalTrans= mgr->palAlphaId;

		// --- image ---
		if(mgr->gfxHasAlpha)
		{
			RGBQUAD *rgb= &mgr->gfxAlphaColor;
			mGfxMode= GFX_MODE_BMP_T;
			mGfxTransStr.Format("%02X%02X%02X", rgb->rgbRed, 
				rgb->rgbGreen, rgb->rgbBlue);
		}
		else if(mgr->gfxMode == GRIT_GFX_BMP_A)
			mGfxMode= GFX_MODE_BMP_T;			
		else if(mgr->gfxMode == GRIT_GFX_BMP)
			mGfxMode= GFX_MODE_BMP;			
		else
			mGfxMode= GFX_MODE_TILE;			

		//mgr->gfx_ofs;
		//mgr->gfxBpp;

		// map
		if(mbMap)
		{
			moMapFormat= mgr->mapLayout;

			if(mgr->mapRedux & GRIT_RDX_TILE)
			{	
				mbMapRdx= TRUE;
				mbMapRdxFlip= mbMapRdxPal= FALSE;
				if(mgr->mapRedux & GRIT_RDX_FLIP)
					mbMapRdxFlip= TRUE;
				if(mgr->mapRedux & GRIT_RDX_PAL)
					mbMapRdxPal= TRUE;
			}
			mMapOffset= mgr->mapOffset;
		}
		// meta
		if(mbObjCustom)
		{
			mObjHorz= mgr->metaWidth;
			mObjVert= mgr->metaHeight;
		}
		// area
		mAreaLeft= mgr->areaLeft;
		mAreaTop= mgr->areaTop;
		mAreaWidth= mgr->areaRight-mgr->areaLeft;
		mAreaHeight= mgr->areaBottom-mgr->areaTop;

		UpdateData(FALSE);
	}

	return TRUE;
}


BOOL CxpGbaDlg::Validate()
{
	UpdateGritRec(TRUE);
	if(!grit_validate(mgr))
	{
		int res= MessageBox("Validation encountered problems, "
			"accept alterations?", "Validation", MB_YESNO | MB_ICONEXCLAMATION);
		if(res == IDYES)
			UpdateGritRec(FALSE);
		return FALSE;
	}
	else
		return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CxpGbaDlg message handlers


BOOL CxpGbaDlg::OnInitDialog() 
{
	ASSERT(mpDib);
	
	int nclrs= dib_get_nclrs(mpDib);
	if(nclrs > 0 && mPalStart+mPalCount>nclrs)
	{
		mPalStart= 0;
		mPalCount= nclrs;
	}
	if(moAreaSize != 0)
	{
		mAreaLeft= 0;	mAreaWidth= dib_get_width(mpDib);
		mAreaTop=0;		mAreaHeight= dib_get_height(mpDib);
	}
	if(mbSymChk == FALSE)
		mSymName= mDstTitle;

	CDialog::OnInitDialog();
	OnPalChk();
	OnGfxChk();
	OnMapChk();
	UpdateObj();
	UpdateMap();
	UpdateArea();

	GetDlgItem(IDC_VAR_NAME)->EnableWindow(mbSymChk);

	//UpdateSummary();

	return TRUE;
}

void CxpGbaDlg::OnOK() 
{
	CString logpath;
	
	GetRootDir(logpath);
	logpath += "\\gxplog.txt";


	FILE *fp= fopen(logpath, "w");
	if(fp)
		log_init(LOG_STATUS, fp);

	if(Validate() == FALSE)
	{
		if(fp)
		{
			log_exit();
			fclose(fp);
		}		
		return;
	}

	GritShared *grs= mgr->shared;

	// Read external tileset if required
	// PONDER: move inside grit_run?
	if(mgr->gfxIsShared)
	{
		// read file
		grs->dib= dib_load(grs->tilePath, NULL);

		if(grs->dib)
		{
			if( dib_get_bpp(grs->dib) != 8 )
			{
				lprintf(LOG_WARNING, "  External tileset must be 8bpp. Converting.\n");
				dib_convert(grs->dib, 8, 0);
			}

			if( dib_get_width(grs->dib) != 8 )
			{
				lprintf(LOG_WARNING, "  External tileset not tiled yet. Doing so now.\n");
				dib_redim(grs->dib, 8, 8, 0);
			}
		}
		else
			lprintf(LOG_WARNING, "  Couldn't load external tileset from \n    %s.\n", 
				grs->tilePath);

		// PONDER: reduce here too?
	}

	int res= grit_run(mgr);

	// Save external tileset if required
	// PONDER: move inside grit_run?
	if(mgr->gfxIsShared)
	{
		if( !dib_save(grs->dib, grs->tilePath, NULL) )
			lprintf(LOG_WARNING, "  Couldn't save external tileset to \n    %s.\n", 
				grs->tilePath);
	}


	if(fp)
	{
		log_exit();
		fclose(fp);
	}

	if(res == TRUE)
	{
		// PONDER: ask to see log?
		res= MessageBox("Export succeeded. Show log?", NULL, 
			MB_ICONINFORMATION | MB_YESNO | MB_DEFBUTTON2);	
		if(res == IDYES)
		{
			CLogDlg dlg;
			dlg.SetTextFromFile(logpath);
			dlg.DoModal();
		}
		CDialog::OnOK();
	}
	else
	{
		// PONDER: ask to see log?
		res= MessageBox("Export failed. Show Log?", NULL, 
			MB_ICONEXCLAMATION | MB_YESNO);	
		if(res == IDYES)
		{
			CLogDlg dlg;
			dlg.SetTextFromFile(logpath);
			dlg.DoModal();
		}	
	}
}

void CxpGbaDlg::OnValidate() 
{
	Validate();	
}


void CxpGbaDlg::OnGfxChk() 
{
	UpdateData(TRUE);
	UpdateGfx();
}

void CxpGbaDlg::OnSelendokGfxMode() 
{
	UpdateData(TRUE);
	UpdateGfx();
	UpdateObj();
	UpdateMap();
}

void CxpGbaDlg::OnMapChk() 
{
	UpdateData(TRUE);
	UpdateMap();
}

void CxpGbaDlg::OnMapRdx() 
{
	UpdateData(TRUE);
	UpdateRdx();
}


void CxpGbaDlg::OnObjCustom() 
{
	UpdateData(TRUE);
	UpdateObj();	
}

void CxpGbaDlg::OnPalChk() 
{
	UpdateData(TRUE);
	UpdatePal();
}


void CxpGbaDlg::OnAreaFormat(int nID)
{
	UpdateData(TRUE);
	UpdateArea();
}


void CxpGbaDlg::OnFileBrowse() 
{
	CString str;
	str.LoadString(IDS_FLTR_GBA);
	CFileDialog fdlg(TRUE, NULL, NULL, 
		OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY, str);

	if(mDstDir == "")
	{
		char str[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, str);
		mDstDir= str;
		//::GetRootDir(mDstDir);
	}
	
	fdlg.m_ofn.lpstrInitialDir= mDstDir;

	fdlg.m_ofn.lpstrTitle= "Get File Path";

	if(fdlg.DoModal() == IDOK)
	{
		SetDstPath(fdlg.GetPathName());
		UpdateRiff();
		UpdateData(FALSE);
	}	
}

void CxpGbaDlg::OnSelendokFileType() 
{
	UpdateData();

	char str[MAX_PATH];
	mDstDir= path_get_dir(str, mDstPath, MAX_PATH);
	mDstTitle= path_get_title(str, mDstPath, MAX_PATH);
	//- CFileFilter::GetFileDir(mDstPath, mDstDir);
	//- CFileFilter::GetFileTitle(mDstPath, mDstTitle);
	mDstPath= mDstDir + "\\" + mDstTitle + "." + cFileTypes[mFileType];

	UpdateRiff();
	UpdateData(FALSE);
}


void CxpGbaDlg::OnRiffChk() 
{
	UpdateData(TRUE);
	UpdateRiff();
	UpdateData(FALSE);
}

void CxpGbaDlg::OnVarChk() 
{
	UpdateData(TRUE);
	GetDlgItem(IDC_VAR_NAME)->EnableWindow(mbSymChk);
}

void CxpGbaDlg::OnTilesetChk() 
{
	UpdateData(TRUE);
	UpdateMap();
}


void CxpGbaDlg::OnTilesetBrowse() 
{
	CString str;

	const int NFILTERS=5;
	FREE_IMAGE_FORMAT iFilters[NFILTERS]= 
	{	FIF_BMP, FIF_GIF, FIF_PCX, FIF_PNG, FIF_TARGA	};

	// Get full list
	int fif_count;
	char buffy[1024];
		
	fif_count= fiFillOfnFilter(buffy, FIF_MODE_EXP_8BPP, iFilters, 5);

	CFileDialog fdlg(TRUE, NULL, NULL, 
		OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY, buffy);

	if(mDstDir == "")
	{
		char str[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, str);
		mDstDir= str;
		//::GetRootDir(mDstDir);
	}
	
	fdlg.m_ofn.lpstrInitialDir= mDstDir;
	fdlg.m_ofn.lpstrTitle= "Get Tileset Path";

	if(fdlg.DoModal() == IDOK)
	{
		mTilesetPath= fdlg.GetPathName();
		UpdateData(FALSE);
	}
}


BOOL CxpGbaDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	BOOL bRes= CDialog::OnCommand(wParam, lParam);
	//TRACE("ON_COMMAND: %d:%d, %d\n", HIWORD(wParam), LOWORD(wParam), lParam);

	//if(HIWORD(wParam) == EN_UPDATE) && LOWORD(wParam) != IDC_SUMMARY);
	if(LOWORD(wParam) != IDC_SUMMARY)
		UpdateSummary();

	return bRes;
}

//-
/*
void CxpGbaDlg::SetSrcPath(const CString &fname)
{
	char str[MAX_PATH];

	//CString str(""), fdir, ftitle;
	mSrcPath= fname;

	CFileFilter::GetFileDir(fname, fdir);
	CFileFilter::GetFileTitle(fname, ftitle);
	if(!fdir.IsEmpty())
		str= fdir + "\\";
	if(!ftitle.IsEmpty())
		str += ftitle;
	SetDstPath(str);
}
*/

//! Set the destination path, dir and title
/*!
	\param path Full destination path. 
*/
void CxpGbaDlg::SetDstPath(const char *path)
{
	char str[MAX_PATH], ext[_MAX_EXT];
	mDstDir= path_get_dir(str, path, MAX_PATH);

	char *pext= path_get_ext(path);
	if(pext != NULL)
	{
		strcpy(ext, pext);
		strlwr(ext);
		path_get_title(str, path, MAX_PATH);

		// binary could have multiple exts; skip last
		if(strcmp(ext, "bin")==0)
			path_get_title(str, str, MAX_PATH);
		mDstTitle= str;

		int ii;
		for(ii=0; ii<FMT_END; ii++)
			if(strcmp(ext, cFileTypes[ii])==0)
				break;

		int old= mFileType;
		if(ii != FMT_END)	// known filetype, so change
			mFileType= ii;
	}

	mDstPath= mDstDir + "\\" + mDstTitle + "." + cFileTypes[mFileType];
	
	//if(mFileType != old && !mBusy)
	//	UpdateData(FALSE);
}
