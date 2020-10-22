//Download by http://www.NewXing.com
//***************************************************************************
//	Description		: Valid Function Class
//  File Name		: ValidFunction.h
//  Created			: 
//	Email			: 
//***************************************************************************

#if !defined(AFX_VALIDFUNCTION_H__F23994E6_9038_47E3_8716_9E907ADEC71E__INCLUDED_)
#define AFX_VALIDFUNCTION_H__F23994E6_9038_47E3_8716_9E907ADEC71E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace CValidFunction  
{
	CString ShortPathToLong(LPCTSTR strPath);
	CString LongPathToShort(LPCTSTR strPath);
	void GetProgramFileDir(CString& strDir);
	void GetWindowDir(CString& strDir);
	void GetWindowDisk(CString& strDisk);
	int IsInStringArrayNoCase(const CStringArray &strArr, const CString &str);
	int IsInStringArray(const CStringArray & strArr,const CString& str);
	void SetStaticText(CDialog* pDlg,UINT nID,LPCTSTR strText);
	BOOL CreatePath(LPCTSTR strPath);
	void GetWorkPath(CString& strPath);
	BOOL IsPathExist(LPCTSTR strPath);
	BOOL IsFileExist(LPCTSTR strFileName);
	CString GetLONGLONGString(LONGLONG llValue);
	CString CombineFilePath(LPCTSTR lpszPathName, LPCTSTR lpszFileName);
};
using namespace CValidFunction;

#endif // !defined(AFX_VALIDFUNCTION_H__F23994E6_9038_47E3_8716_9E907ADEC71E__INCLUDED_)
