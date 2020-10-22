//Download by http://www.NewXing.com
// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__682CCD86_2D58_4C53_8EC0_EAEC773373A9__INCLUDED_)
#define AFX_STDAFX_H__682CCD86_2D58_4C53_8EC0_EAEC773373A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "FolderDialog.h"
#include "RegisterKey.h"
#include "XPButton.h"
#include "HyperLink.H"
#include "ValidFunction.h"

#ifndef FALSE_RETURN
#define FALSE_RETURN(bRes,hr){if(bRes == FALSE) return hr;};
#endif

#ifndef CheckPointer
#define CheckPointer(pointer,hr){if(pointer == NULL) return hr;};
#endif

#define FRAME_BK_COLOR		RGB(218,230,245)

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__682CCD86_2D58_4C53_8EC0_EAEC773373A9__INCLUDED_)
