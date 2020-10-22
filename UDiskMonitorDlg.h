//Download by http://www.NewXing.com
// UDiskMonitorDlg.h : header file
//

#if !defined(AFX_UDISKMONITORDLG_H__4906E3D2_F687_431A_A262_1BFA511862D6__INCLUDED_)
#define AFX_UDISKMONITORDLG_H__4906E3D2_F687_431A_A262_1BFA511862D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CUDiskMonitorDlg dialog

class CUDiskMonitorDlg : public CDialog
{
// Construction
public:
	CUDiskMonitorDlg(CWnd* pParent = NULL);	// standard constructor

	void StartCopyThread(CString strSrcPath);
	void StopCopyThread();
	BOOL CopyFileEx(CString strFromPath,CString strToPath);
	
protected:
	void HideDlg(BOOL bHide);
	void SerializeParamFromReg(BOOL bSave);
	BOOL DealDeviceChange(WPARAM wParam,LPARAM lParam);
	char FirstDriveFromMask (ULONG unitmask);	
	void InitTitle();

	// Dialog Data
	//{{AFX_DATA(CUDiskMonitorDlg)
	enum { IDD = IDD_UDISKMONITOR_DIALOG };
	CXPButton	m_btnHide;
	CXPButton	m_btnExit;
	CXPButton	m_btnAbout;
	CXPButton	m_btnView;
	CXPButton	m_btnOpen;
	BOOL		m_bAutoRun;
	BOOL		m_bHideWindow;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUDiskMonitorDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
	LRESULT OnHotKey(WPARAM wParam,LPARAM lParam); 

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CUDiskMonitorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnOpen();
	afx_msg void OnBtnView();
	afx_msg void OnCheckAutorun();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCheckHide();
	afx_msg void OnBtnExit();
	afx_msg void OnClose();
	afx_msg void OnBtnAbout();
	afx_msg void OnBtnHide();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CString		m_strSrcPath;		// UÅÌ»òMP3Ä¿Â¼
	CString		m_strDstPath;
	
protected:
	HANDLE		m_hThreadCopy;
	HBRUSH		m_hBkBrush;	

	CRect		m_rcWnd;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UDISKMONITORDLG_H__4906E3D2_F687_431A_A262_1BFA511862D6__INCLUDED_)
