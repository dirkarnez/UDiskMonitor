// UDiskMonitorDlg.cpp : implementation file
// Download by http://www.NewXing.com

#include "stdafx.h"
#include "UDiskMonitor.h"
#include "UDiskMonitorDlg.h"
#include <dbt.h>
#include <process.h>  

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

WINDOWPLACEMENT g_wndhwp;

#define TIMER_HIDE		2009
#define TIMER_SHOW		2008
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CXPButton		m_btnOk;
	CHyperLink		m_linkEmail;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
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
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDC_LINK_EMAIL, m_linkEmail);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString strHyperLink;
	strHyperLink.LoadString(IDS_HYPERLINK_EMAIL);
	strHyperLink.Insert(0, _T("mailto:"));
	m_linkEmail.SetURL(strHyperLink);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
/////////////////////////////////////////////////////////////////////////////
// CUDiskMonitorDlg dialog

CUDiskMonitorDlg::CUDiskMonitorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUDiskMonitorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUDiskMonitorDlg)
	m_bAutoRun			= FALSE;
	m_strDstPath		= _T("C:\\UDiskMonitor");
	m_bHideWindow = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon				= AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hThreadCopy		= NULL;
	m_bHideWindow		= TRUE;
	m_strSrcPath.Empty();

	if(!CValidFunction::IsPathExist(m_strDstPath))
	{
		CValidFunction::CreatePath(m_strDstPath);
	}

	m_hBkBrush		= CreateSolidBrush(FRAME_BK_COLOR);
}

void CUDiskMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUDiskMonitorDlg)
	DDX_Control(pDX, IDC_BTN_HIDE, m_btnHide);
	DDX_Control(pDX, IDC_BTN_EXIT, m_btnExit);
	DDX_Control(pDX, IDC_BTN_ABOUT, m_btnAbout);
	DDX_Control(pDX, IDC_BTN_VIEW, m_btnView);
	DDX_Control(pDX, IDC_BTN_OPEN, m_btnOpen);
	DDX_Check(pDX, IDC_CHECK_AUTORUN, m_bAutoRun);
	DDX_Check(pDX, IDC_CHECK_HIDE, m_bHideWindow);
	DDX_Text(pDX, IDC_EDIT_DEST, m_strDstPath);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUDiskMonitorDlg, CDialog)
	//{{AFX_MSG_MAP(CUDiskMonitorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPEN, OnBtnOpen)
	ON_BN_CLICKED(IDC_BTN_VIEW, OnBtnView)
	ON_BN_CLICKED(IDC_CHECK_AUTORUN, OnCheckAutorun)
	ON_WM_CTLCOLOR()
	ON_WM_NCHITTEST()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_HIDE, OnCheckHide)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_ABOUT, OnBtnAbout)
	ON_BN_CLICKED(IDC_BTN_HIDE, OnBtnHide)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_HOTKEY,OnHotKey)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUDiskMonitorDlg message handlers

BOOL CUDiskMonitorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	InitTitle();

	if(!RegisterHotKey(m_hWnd,0xA000,MOD_CONTROL | MOD_ALT,'U') ||
		!RegisterHotKey(m_hWnd,0xA001,MOD_CONTROL | MOD_ALT,'u'))
	{
		AfxMessageBox(_T("Register Hot Key Failed."));
	}
	
	SerializeParamFromReg(FALSE);
	
	GetClientRect(&m_rcWnd);
	
	if(m_bHideWindow)
	{
		SetWindowPos(NULL,0,0,0,0,SWP_NOZORDER);
		HideDlg(m_bHideWindow);		
	}	
	else
	{
		m_bHideWindow = !m_bHideWindow;
	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUDiskMonitorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUDiskMonitorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUDiskMonitorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CUDiskMonitorDlg::InitTitle()
{
	CString strTitle;
	strTitle.LoadString(IDS_STRING_TITLE);
	SetWindowText(strTitle);
}

LRESULT CUDiskMonitorDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(message == WM_DEVICECHANGE)
	{
		DealDeviceChange(wParam,lParam);
	}

	return CDialog::WindowProc(message, wParam, lParam);
}

// 处理设备改变消息
BOOL CUDiskMonitorDlg::DealDeviceChange(WPARAM wParam,LPARAM lParam)
{
	BOOL bRes = TRUE;
	
	PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)lParam;

	switch(wParam)
	{
	case DBT_DEVICEARRIVAL:
		if (lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME)
		{
            PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
			
			// 获取当前插入设备对应磁盘编号 A--Z
			char chDisk = FirstDriveFromMask(lpdbv->dbcv_unitmask);

			CString strDisk;
			strDisk.Format("%c:\\",chDisk);	
			if(CValidFunction::IsPathExist(strDisk))
			{
				UINT nDriveType = GetDriveType ((LPCTSTR) strDisk);
				if(nDriveType == DRIVE_REMOVABLE)
				{
					Sleep(500);
					// 插入设备为可移动设备(U盘或Mp3等)
					StartCopyThread(strDisk);
				}
			}
		}
		break;
		
	case DBT_DEVICEREMOVECOMPLETE:
		
		// 停止拷贝线程
		StopCopyThread();

		break;
		
	default:
		break;
	}
	
	return bRes;
}

// 获取磁盘盘符
char CUDiskMonitorDlg::FirstDriveFromMask (ULONG unitmask)
{
	char i;
	
	for (i = 0; i < 26; ++i)
	{
		if (unitmask & 0x1)
			break;

		unitmask = unitmask >> 1;
	}
	
	return (i + 'A');
}

// 拷贝文件及目录
BOOL CUDiskMonitorDlg::CopyFileEx(CString strFromPath,CString strToPath)
{
	TCHAR chSplitter = '*';
	strFromPath		+= chSplitter;
	strToPath		+= chSplitter;
	
	int len = strFromPath.GetLength();
	TCHAR* pszSrcPath = strFromPath.GetBuffer(0);
	for(int i = _tcslen(pszSrcPath) - 1; i >= 0; i --)
	{
		if(pszSrcPath[i] == chSplitter)
			pszSrcPath[i] = '\0';
	}
	
	len = strToPath.GetLength();
	TCHAR* pszDstPath = strToPath.GetBuffer(0);
	for(i = _tcslen(pszDstPath) - 1; i >= 0; i --)
	{
		if(pszDstPath[i] == chSplitter)
			pszDstPath[i] = '\0';
	}

	
    SHFILEOPSTRUCT FileOp; 
    ZeroMemory((void*)&FileOp,sizeof(SHFILEOPSTRUCT));
    
    FileOp.fFlags				= FOF_NOCONFIRMATION | FOF_SILENT; 
    FileOp.hNameMappings		= NULL; 
    FileOp.hwnd					= NULL; 
    FileOp.lpszProgressTitle	= NULL; 
    FileOp.pFrom				= pszSrcPath; 
    FileOp.pTo					= pszDstPath; 
    FileOp.wFunc				= FO_COPY; 
    
	int nRes = SHFileOperation(&FileOp);

    return (nRes == 0);
}

void CUDiskMonitorDlg::StopCopyThread()
{
	if(m_hThreadCopy)
	{
		CloseHandle(m_hThreadCopy);
		m_hThreadCopy = NULL;
	}
}

// 拷贝函数处理过程
unsigned WINAPI _CopyEntry(LPVOID pParam)
{
	CUDiskMonitorDlg * pUDiskDlg = (CUDiskMonitorDlg *)pParam;
	CheckPointer(pUDiskDlg,-1);
	FALSE_RETURN(!pUDiskDlg->m_strSrcPath.IsEmpty(),-1);
	
	try
	{	
		CString strDstFolder;
		strDstFolder = pUDiskDlg->m_strDstPath + _T("\\") + CTime::GetCurrentTime().Format("%Y-%m-%d %H %M %S");

		if(!CValidFunction::IsPathExist(strDstFolder))
		{
			CValidFunction::CreatePath(strDstFolder);
		}
		
		CFileFind fileFind;
		char szFileFind[MAX_PATH];
		sprintf(szFileFind,"%s\\*.*",pUDiskDlg->m_strSrcPath);

		BOOL bFinded = fileFind.FindFile(szFileFind);
		while(bFinded)
		{
			bFinded = fileFind.FindNextFile();
			if(!fileFind.IsDots())
			{
				char szFileName[MAX_PATH];
				strcpy(szFileName,fileFind.GetFileName().GetBuffer(MAX_PATH));

				if(fileFind.IsDirectory())
				{
					char szDir[MAX_PATH];
					sprintf(szDir,"%s\\%s",pUDiskDlg->m_strSrcPath,szFileName);
				
					pUDiskDlg->CopyFileEx(szDir,strDstFolder);

					Sleep(20);
				}
				else
				{
					char NewFileName[MAX_PATH],ExistFileName[MAX_PATH];
					sprintf(ExistFileName,"%s\\%s",pUDiskDlg->m_strSrcPath,szFileName);
					sprintf(NewFileName,"%s\\%s",strDstFolder,szFileName);

					CopyFile(ExistFileName,NewFileName,FALSE);

					Sleep(20);
				}
			}
		}

		fileFind.Close();
		
		pUDiskDlg->StopCopyThread();

		pUDiskDlg->m_strSrcPath.Empty();
	}
	catch(...)
	{
		pUDiskDlg->StopCopyThread();
		pUDiskDlg->m_strSrcPath.Empty();

		return -1;
	}
	
	return 0;
}

// 开启拷贝文件线程
void CUDiskMonitorDlg::StartCopyThread(CString strSrcPath)
{
	m_strSrcPath = strSrcPath;
	
	StopCopyThread();

	UINT nThreadID = 0;
	m_hThreadCopy  = (HANDLE)_beginthreadex(NULL,
		0,
		_CopyEntry,
		this,
		0,
		&nThreadID);
}

// 选择保存文件目录
void CUDiskMonitorDlg::OnBtnOpen() 
{
	// TODO: Add your control notification handler code here
	CFolderDialog dlg(m_strDstPath,NULL,this,_T("选择保存文件目录"),_T("当前目录"));
	if(dlg.DoModal() == IDOK)
	{
		m_strDstPath = dlg.GetPathName();
		
		if(!CValidFunction::IsPathExist(m_strDstPath))
		{
			CValidFunction::CreatePath(m_strDstPath);
		}
		
		UpdateData(FALSE);
	}
}

// 浏览保存文件目录
void CUDiskMonitorDlg::OnBtnView() 
{
	// TODO: Add your control notification handler code here
	TCHAR szCmdLine[MAX_PATH];
	_stprintf(szCmdLine, _T("Explorer.exe %s"), m_strDstPath);
#ifdef _UNICODE
	USES_CONVERSION;
	::WinExec(W2A(szCmdLine), SW_SHOW);
#else
	::WinExec(szCmdLine, SW_SHOW);
#endif
}

#define REG_LOCAL_AUTORUN	_T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run")
#define REG_UDISK_SECTION	_T("SOFTWARE\\UDiskMonitor")
#define REG_KEY_DESTDIR		_T("DestDir")
#define REG_KEY_AUTORUN		_T("AutoRun")
#define REG_KEY_RUN			_T("UDiskMonitor")
#define REG_KEY_HIDE		_T("AutoHide")

void CUDiskMonitorDlg::SerializeParamFromReg(BOOL bSave)
{
	CRegisterKey	RegKey;
	
	if(RegKey.RegOpen(HKEY_LOCAL_MACHINE, REG_UDISK_SECTION) == ERROR_SUCCESS)
	{
		if(bSave)
		{
			UpdateData();
			
			RegKey.RegWrite(REG_KEY_DESTDIR, m_strDstPath);
			RegKey.RegWrite(REG_KEY_HIDE,(DWORD&)m_bHideWindow);
			RegKey.RegWrite(REG_KEY_AUTORUN, (DWORD&)m_bAutoRun);
		}
		else
		{
			RegKey.RegRead(REG_KEY_DESTDIR, m_strDstPath);
			RegKey.RegRead(REG_KEY_HIDE,(DWORD&)m_bHideWindow);
			RegKey.RegRead(REG_KEY_AUTORUN, (DWORD&)m_bAutoRun);

			if(!CValidFunction::IsPathExist(m_strDstPath))
			{
				CValidFunction::CreatePath(m_strDstPath);
			}
			
			UpdateData(FALSE);
		}
	}
	
	RegKey.RegClose();
}

void CUDiskMonitorDlg::OnCheckAutorun() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
	CRegisterKey	RegKey;
	if(RegKey.RegOpen(HKEY_LOCAL_MACHINE , REG_LOCAL_AUTORUN) == ERROR_SUCCESS)
	{
		if(m_bAutoRun)
		{
			CString strUDiskExe;
			GetModuleFileName(NULL,strUDiskExe.GetBuffer(MAX_PATH),MAX_PATH);
			strUDiskExe.ReleaseBuffer();

			RegKey.RegWrite(REG_KEY_RUN,strUDiskExe);
		}
		else
		{
			RegKey.RegDel(REG_KEY_RUN);
		}
	}
}

HBRUSH CUDiskMonitorDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	if (nCtlColor == CTLCOLOR_STATIC || nCtlColor == CTLCOLOR_EDIT)
	{
		pDC->SetBkColor(FRAME_BK_COLOR);
	}
	
	pDC->SetBkMode(TRANSPARENT);
	
	return m_hBkBrush;
}

//处理快捷键
LRESULT CUDiskMonitorDlg::OnHotKey(WPARAM wParam,LPARAM lParam) 
{
	if (wParam == 0xA000 || wParam == 0xA001) 
	{
		HideDlg(m_bHideWindow);
	}

	return 0; 
}

void CUDiskMonitorDlg::HideDlg(BOOL bHide)
{
	if(m_bHideWindow)
	{
		SetTimer(TIMER_HIDE,10,NULL);
	}
	else 
	{
		SetTimer(TIMER_SHOW,10,NULL);
	}

	m_bHideWindow = !bHide;
}

UINT CUDiskMonitorDlg::OnNcHitTest(CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	UINT nHitTest = CDialog::OnNcHitTest( point ); 
    return (nHitTest == HTCLIENT) ? HTCAPTION : nHitTest;
}

void CUDiskMonitorDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent == TIMER_SHOW)
	{
		SetWindowPos(NULL,m_rcWnd.left,m_rcWnd.top,m_rcWnd.right,m_rcWnd.bottom,SWP_NOZORDER);
		CenterWindow(GetDesktopWindow());
		ShowWindow(SW_SHOW);
		
		KillTimer(TIMER_SHOW);
	}
	else if(nIDEvent == TIMER_HIDE)
	{
		ShowWindow(SW_HIDE);
		KillTimer(TIMER_HIDE);
	}

	CDialog::OnTimer(nIDEvent);
}

void CUDiskMonitorDlg::OnCheckHide() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
}

BOOL CUDiskMonitorDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN))
	{
		return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CUDiskMonitorDlg::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	StopCopyThread();
	SerializeParamFromReg(TRUE);
	UnregisterHotKey(m_hWnd, 0xA000); 
	UnregisterHotKey(m_hWnd, 0xA001);
	
	CDialog::OnOK();
}

void CUDiskMonitorDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
}

void CUDiskMonitorDlg::OnBtnAbout() 
{
	// TODO: Add your control notification handler code here
	CAboutDlg dlg;
	dlg.DoModal();
}

void CUDiskMonitorDlg::OnBtnHide() 
{
	// TODO: Add your control notification handler code here
	HideDlg(TRUE);
}
