//Download by http://www.NewXing.com
// ValidFunction.cpp: implementation of the CValidFunction class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ValidFunction.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// CValidFunction
namespace CValidFunction
{

BOOL IsFileExist(LPCTSTR strFileName)
{
	if(strFileName == NULL)
		return FALSE;

	DWORD dwAttr = ::GetFileAttributes(strFileName);
	return (dwAttr!=-1 && !(dwAttr&FILE_ATTRIBUTE_DIRECTORY) );
}

BOOL IsPathExist(LPCTSTR strPath)
{
	if(strPath == NULL)
		return FALSE;

	CString t_PathName = strPath;
	t_PathName.Replace('/','\\');
	DWORD dwAttr = ::GetFileAttributes(t_PathName);

	return (dwAttr!=-1 && (dwAttr&FILE_ATTRIBUTE_DIRECTORY) );
}

void GetWorkPath(CString &strPath)
{
	char FilePath[_MAX_PATH];
	DWORD dwSize = GetModuleFileName(NULL,FilePath,_MAX_PATH);
	strPath = FilePath;
	strPath = strPath.Left(strPath.ReverseFind('\\'));//ȥ���ַ������"\\"
}

BOOL CreatePath(LPCTSTR lpszDir)
{
	if(lpszDir==NULL || _tcslen(lpszDir)==0)
		return FALSE;
	
	// base case . . .if directory exists
	if(IsPathExist(lpszDir))
		return TRUE;

	CString strDir(lpszDir);
	if(strDir.Right(1) == "\\")
		strDir = strDir.Left(strDir.GetLength()-1); 

	 // recursive call, one less directory
	int nFound = strDir.ReverseFind('\\');
	CString strSubDir = strDir.Left(nFound);

	if(! CreatePath(strSubDir) )
		return FALSE;

	return ::CreateDirectory(strDir,NULL);
 }


int IsInStringArray(const CStringArray &strArr, const CString &str)
{
	int nIndex = -1;
	for (int i=0; i< strArr.GetSize(); i++)
	{
		if (str.Compare(strArr[i]) == 0)
		{
			nIndex = i;
			break;
		}
	}
	return nIndex;
}

int IsInStringArrayNoCase(const CStringArray &strArr, const CString &str)
{
	int nIndex = -1;
	for (int i=0; i< strArr.GetSize(); i++)
	{
		if (str.CompareNoCase(strArr[i]) == 0)
		{
			nIndex = i;
			break;
		}
	}
	return nIndex;
}

void GetWindowDisk(CString &strDisk)
{
	CString strExe;
	TCHAR pBuf[MAX_PATH];
	::GetWindowsDirectory(pBuf,MAX_PATH);
	strExe = pBuf;
	strDisk = strExe.Left(3);	
}

void GetWindowDir(CString &strDir)
{
	CString strExe;
	TCHAR pBuf[MAX_PATH];
	::GetWindowsDirectory(pBuf,MAX_PATH);
	strExe = pBuf;
	strDir = strExe;
}

void GetProgramFileDir(CString &strDir)
{
	CString strExe;
	TCHAR pBuf[MAX_PATH];
	::GetWindowsDirectory(pBuf,MAX_PATH);
	strExe = pBuf;
	strExe = strExe.Left(3);
	strDir = strExe + _T("Program Files");
}

CString LongPathToShort(LPCTSTR strPath)
{
	CString strShort;
	TCHAR  pBuf[MAX_PATH];
	DWORD dwLen = ::GetShortPathName(strPath,pBuf,MAX_PATH);
	if (dwLen > 0)
		strShort = pBuf;
	return strShort;
}

CString ShortPathToLong(LPCTSTR strPath)
{
	CString strLong;
	TCHAR pBuf[MAX_PATH];
	DWORD dwLen = ::GetLongPathName(strPath,pBuf,MAX_PATH);
	if (dwLen > 0)
		strLong = pBuf;
	return strLong;
}

CString GetLONGLONGString(LONGLONG llValue)
{
	CString strRes = "";
	char strTemp[_MAX_PATH];
	LONGLONG llTemp = llValue;
	CString strValue = "";
	BYTE bTemp = 0;
	while(llTemp > 0)
	{
		bTemp = (BYTE)(llTemp % 10);
		llTemp = llTemp / 10;
		sprintf(strTemp, "%x", bTemp);
		strValue = strTemp;
		strRes = strValue + strRes;
	}
	return strRes;
}

CString CombineFilePath(LPCTSTR lpszPathName, LPCTSTR lpszFileName)
{
	CString str(lpszPathName);
	if(str.Right(1) != '\\' && *lpszFileName!='\\')
		str += '\\';
	str += lpszFileName;
	return str;
}
}
