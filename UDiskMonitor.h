//Download by http://www.NewXing.com
// UDiskMonitor.h : main header file for the UDISKMONITOR application
//

#if !defined(AFX_UDISKMONITOR_H__D4F5E2E0_6365_4182_8FA2_9A42DA3EA040__INCLUDED_)
#define AFX_UDISKMONITOR_H__D4F5E2E0_6365_4182_8FA2_9A42DA3EA040__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CUDiskMonitorApp:
// See UDiskMonitor.cpp for the implementation of this class
//

class CUDiskMonitorApp : public CWinApp
{
public:
	CUDiskMonitorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUDiskMonitorApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUDiskMonitorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	HANDLE		m_hAppMutex;	// App Mutex

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UDISKMONITOR_H__D4F5E2E0_6365_4182_8FA2_9A42DA3EA040__INCLUDED_)
