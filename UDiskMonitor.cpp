// UDiskMonitor.cpp : Defines the class behaviors for the application.
// Download by http://www.NewXing.com

#include "stdafx.h"
#include "UDiskMonitor.h"
#include "UDiskMonitorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define APP_MUTEX							_T("U Disk Monitor Mutex")
/////////////////////////////////////////////////////////////////////////////
// CUDiskMonitorApp

BEGIN_MESSAGE_MAP(CUDiskMonitorApp, CWinApp)
	//{{AFX_MSG_MAP(CUDiskMonitorApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUDiskMonitorApp construction

CUDiskMonitorApp::CUDiskMonitorApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_hAppMutex	= NULL;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CUDiskMonitorApp object

CUDiskMonitorApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CUDiskMonitorApp initialization

BOOL CUDiskMonitorApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	// Mutex app
	m_hAppMutex = CreateMutex(NULL,TRUE,APP_MUTEX);
	if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(m_hAppMutex);
		m_hAppMutex = NULL;
		
		AfxMessageBox(_T("该软件已经运行,如果要设置参数请按Control + Alt + U 显示"));

		return FALSE;
	}

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CUDiskMonitorDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CUDiskMonitorApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CloseHandle (m_hAppMutex);
	m_hAppMutex = NULL;
	
	return CWinApp::ExitInstance();
}
