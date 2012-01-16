#if !defined(AFX_IGNOREDIALOG_H__1ED3B4EB_E686_4D40_94B4_31E210A75EB2__INCLUDED_)
#define AFX_IGNOREDIALOG_H__1ED3B4EB_E686_4D40_94B4_31E210A75EB2__INCLUDED_

#include "stConfig.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IgnoreDialog.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CIgnoreDialog ダイアログ

class CIgnoreDialog : public CDialog
{
// コンストラクション
public:
	BOOL AddHistory( HWND i_hWnd );
	CIgnoreDialog( StConfig& i_refConfig, CWnd* pParent );   // 標準のコンストラクタ
	virtual ~CIgnoreDialog();

// ダイアログ データ
	//{{AFX_DATA(CIgnoreDialog)
	enum { IDD = IDD_DIALOG_IGNORE };
	CListBox	m_listboxIgnoreClassNameHistory;
	CButton	m_btnClassnameRemove;
	CButton	m_btnClassnameAdd;
	CListBox	m_listboxIgnoreClassName;
	CString	m_strIgnoreClassName;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CIgnoreDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CIgnoreDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSelchangeListIgnoreClassnameHistory();
	afx_msg void OnButtonIgnoreClose();
	afx_msg void OnButtonClassnameAdd();
	afx_msg void OnButtonClassnameRemove();
	afx_msg void OnSelchangeListIgnoreClassname();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	StConfig&	m_refConfig;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_IGNOREDIALOG_H__1ED3B4EB_E686_4D40_94B4_31E210A75EB2__INCLUDED_)
