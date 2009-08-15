// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "wingrit.h"

#include "MainFrm.h"
#include "wingritdoc.h"
#include "wingritview.h"

#include "palviewdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static CPalViewDlg *gPalViewDlg= NULL;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(IDM_DOC_UPDATE, OnDocUpdate)
	ON_COMMAND(ID_VIEW_PAL, OnViewPal)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	mpText= NULL;	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	LoadBarState("Bar Settings");

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	WINDOWPLACEMENT *wp=NULL;
	UINT len;

	AfxGetApp()->GetProfileBinary("MainFrame", "WP", (BYTE**)&wp, &len);
	if(wp != NULL)
	{
		if(wp->showCmd == SW_SHOWMAXIMIZED)
			AfxGetApp()->m_nCmdShow= SW_SHOWMAXIMIZED;

		CRect rc(wp->rcNormalPosition);
		cs.x= rc.left;
		cs.y= rc.top;
		cs.cx= rc.Width();
		cs.cy= rc.Height();

		delete[] wp;
	}
	return CFrameWnd::PreCreateWindow(cs);
}

void CMainFrame::OnDestroy() 
{
	WINDOWPLACEMENT wp;
	GetWindowPlacement(&wp);

	AfxGetApp()->WriteProfileBinary("MainFrame", "WP", (LPBYTE)&wp, sizeof(wp));

	CFrameWnd::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnDocUpdate()
{
	if(gPalViewDlg != NULL)
		gPalViewDlg->Update();
}

void CMainFrame::OnViewPal() 
{
	if(gPalViewDlg == NULL)
	{
		gPalViewDlg= new CPalViewDlg;
		if(!gPalViewDlg->Create(this, GetActiveDocument()))
		{
			::AfxMessageBox("Can't create Pal Viewer");
			if(gPalViewDlg)
			{	delete gPalViewDlg; gPalViewDlg= NULL;	}
			return;
		}
	}
	gPalViewDlg->Show(TRUE);
}

/*
	// Bleh. Maybe later.

// http://www.codeproject.com/debug/mfcconsole.asp

// This function dynamically creates a "Console" window and points stdout and stderr to it.
// It also hooks stdin to the window
// You must free it later with FreeConsole
void RedirectIOToConsole()
{
    int                        hConHandle;
    long                       lStdHandle;
    CONSOLE_SCREEN_BUFFER_INFO coninfo;
    FILE                       *fp;

    // allocate a console for this app
    AllocConsole();

    // set the screen buffer to be big enough to let us scroll text
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), 
                               &coninfo);
    coninfo.dwSize.Y = MAX_CONSOLE_LINES;  // How many lines do you want to have in the console buffer
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), 
                               coninfo.dwSize);

    // redirect unbuffered STDOUT to the console
    g_hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
    fp = _fdopen( hConHandle, "w" );
    *stdout = *fp;
    setvbuf( stdout, NULL, _IONBF, 0 );

    // redirect unbuffered STDIN to the console
    lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
    fp = _fdopen( hConHandle, "r" );
    *stdin = *fp;
    setvbuf( stdin, NULL, _IONBF, 0 );

    // redirect unbuffered STDERR to the console
    lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
    fp = _fdopen( hConHandle, "w" );
    *stderr = *fp;
    setvbuf( stderr, NULL, _IONBF, 0 );	
	SetConsoleTitle("The Console Titlebar Text");   
	
    // make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog 
    // point to console as well  Uncomment the next line if you are using c++ cio or comment if you don't
    //ios::sync_with_stdio();
}


UINT ProcLaunch( )
{
	STARTUPINFO si = {sizeof si};
	PROCESS_INFO pi;

	HANDLE stdOut = NULL;
	HANDLE stdIn = NULL;

	CreatePipe( &stdOut, &stdIn, NULL, NULL );

	si.hStdOutput = stdOut;
	si.hStdInput = stdIn;

	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	BOOL procCreate =
	CreateProcess( (LPCTSTR)"som_prog_name", (LPWSTR)"some_prog_cmd",
	NULL, NULL, true, CREATE_NO_WINDOW, NULL,
	NULL, &si, &pi );
	if( procCreate != TRUE )
	{
		//handle error
	}

	wchar_t * buff = new wchar_t[1024];
	int mxSz = 1024;
	DWORD bRead = 0;

	BOOL readSuccess = NULL;
	do
	{
		readSuccess = ReadFile( si.hStdOutput, buff, mxSz, &bRead );
	}while(readSuccess == TRUE);

	return S_OK;
}

*/
