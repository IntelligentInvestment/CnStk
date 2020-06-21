// CnStkDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "CnStkDemo.h"

#include "MainFrm.h"
#include "CnStkDemoDoc.h"
#include "CnStkDemoView.h"
#include "StkDemo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCnStkDemoApp

BEGIN_MESSAGE_MAP(CCnStkDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CCnStkDemoApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_APP_ASKDAYALL, OnAppAskdayall)
	ON_COMMAND(ID_APP_ASKDAYONE, OnAppAskdayone)
	ON_COMMAND(ID_APP_ASKMN5ALL, OnAppAskmn5all)
	ON_COMMAND(ID_APP_ASKMN5ONE, OnAppAskmn5one)
	ON_COMMAND(ID_APP_ASKBASE, OnAppAskbase)
	ON_COMMAND(ID_APP_ASKNEWS, OnAppAsknews)
	ON_COMMAND(ID_APP_ASKHALT, OnAppAskhalt)
	ON_COMMAND(ID_APP_ASKMIN, OnAppAskmin)
	ON_COMMAND(ID_APP_ASKPRP, OnAppAskprp)
	ON_COMMAND(ID_APP_ASKPWR, OnAppAskpwr)
	ON_COMMAND(ID_APP_ASKFIN, OnAppAskfin)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCnStkDemoApp construction

CCnStkDemoApp::CCnStkDemoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCnStkDemoApp object

CCnStkDemoApp theApp;

CStkDemo	pStkDemo;

/////////////////////////////////////////////////////////////////////////////
// CCnStkDemoApp initialization

BOOL CCnStkDemoApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CCnStkDemoDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CCnStkDemoView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	pStkDemo.MyCreate( (CWnd*) m_pMainWnd );

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CCnStkDemoApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CCnStkDemoApp message handlers


void CCnStkDemoApp::OnAppAskdayall() 
{
	// TODO: Add your command handler code here
	AfxMessageBox("补充日线数据(全部)");
	CStkDemo StockDrv;
	StockDrv.TmpAskStockDay("",2);	
}

void CCnStkDemoApp::OnAppAskdayone() 
{
	// TODO: Add your command handler code here
	AfxMessageBox("补充日线数据(个股)");
	CStkDemo StockDrv;
	StockDrv.TmpAskStockDay("SH600026",2);
}

void CCnStkDemoApp::OnAppAskmn5all() 
{
	// TODO: Add your command handler code here
	AfxMessageBox("补充五分钟数据(全部)");
	CStkDemo StockDrv;
	StockDrv.TmpAskStockMn5("",2);
}

void CCnStkDemoApp::OnAppAskmn5one() 
{
	// TODO: Add your command handler code here
	AfxMessageBox("补充五分钟数据(个股)");
	CStkDemo StockDrv;
	StockDrv.TmpAskStockMn5("SH600026",2);
}

void CCnStkDemoApp::OnAppAskbase() 
{
	// TODO: Add your command handler code here
	AfxMessageBox("补充个股资料(F10)");
	CStkDemo StockDrv;
	StockDrv.TmpAskStockBase("");	
}

void CCnStkDemoApp::OnAppAsknews() 
{
	// TODO: Add your command handler code here
	AfxMessageBox("补充财经新闻评论");
	CStkDemo StockDrv;
	StockDrv.TmpAskStockNews();
}

void CCnStkDemoApp::OnAppAskhalt() 
{
	// TODO: Add your command handler code here
	AfxMessageBox("停止补数");
	CStkDemo StockDrv;
	StockDrv.TmpAskStockHalt();	
}

void CCnStkDemoApp::OnAppAskmin() 
{
	// TODO: Add your command handler code here
	AfxMessageBox("补充分时数据");
	CStkDemo StockDrv;
	StockDrv.TmpAskStockMin("");		
}

void CCnStkDemoApp::OnAppAskprp() 
{
	// TODO: Add your command handler code here
	AfxMessageBox("补充分笔数据");
	CStkDemo StockDrv;
	StockDrv.TmpAskStockPRP("");
}

void CCnStkDemoApp::OnAppAskpwr() 
{
	// TODO: Add your command handler code here
	AfxMessageBox("获取除权数据");
	CStkDemo StockDrv;
	StockDrv.TmpAskStockPwr();	
}

void CCnStkDemoApp::OnAppAskfin() 
{
	// TODO: Add your command handler code here
	AfxMessageBox("获取财务数据");
	CStkDemo StockDrv;
	StockDrv.TmpAskStockFin();
}
