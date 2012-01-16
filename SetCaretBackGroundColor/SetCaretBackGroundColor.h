// SetCaretBackGroundColor.h : SETCARETBACKGROUNDCOLOR アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_SETCARETBACKGROUNDCOLOR_H__DA5F0F1E_4144_49B9_A7DB_540DD122816D__INCLUDED_)
#define AFX_SETCARETBACKGROUNDCOLOR_H__DA5F0F1E_4144_49B9_A7DB_540DD122816D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル
#include "stConfig.h"

/////////////////////////////////////////////////////////////////////////////
// CSetCaretBackGroundColorApp:
// このクラスの動作の定義に関しては SetCaretBackGroundColor.cpp ファイルを参照してください。
//

class CSetCaretBackGroundColorApp : public CWinApp
{
public:
	CSetCaretBackGroundColorApp();
	virtual ~CSetCaretBackGroundColorApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CSetCaretBackGroundColorApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CSetCaretBackGroundColorApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

	typedef struct tagStCommandLineOption
	{
		BOOL	m_Restart;	// 再起動フラグ
	}StCommandLineOption;

	BOOL GetModulePathFileName(LPCTSTR i_pName, CString& o_pStrPath);
	BOOL ReadIniFile();
	BOOL WriteIniFile();


	HANDLE		m_hEvent;

	TCHAR*		m_pProfileName;
	const char*	m_pszProfileName_bk;

	StConfig	m_Config;

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SETCARETBACKGROUNDCOLOR_H__DA5F0F1E_4144_49B9_A7DB_540DD122816D__INCLUDED_)
