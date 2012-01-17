#if !defined(AFX_CONFIGDIALOG_H__D31BC462_D071_4A03_AB40_6AEAE2601DA4__INCLUDED_)
#define AFX_CONFIGDIALOG_H__D31BC462_D071_4A03_AB40_6AEAE2601DA4__INCLUDED_

#include "stConfig.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigDialog.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CConfigDialog ダイアログ

class CConfigDialog : public CDialog
{
// コンストラクション
public:
	CConfigDialog( StConfig& i_refConfig, CWnd* pParent );   // 標準のコンストラクタ
	~CConfigDialog();

// ダイアログ データ
	//{{AFX_DATA(CConfigDialog)
	enum { IDD = IDD_CONFIGDIALOG };
	CHotKeyCtrl	m_hkCtrlManualBlink;
	CSliderCtrl	m_SliderBlinkFrameLength;
	CStatic	m_StaticColorClose;
	CStatic	m_StaticColorOpen;
	CButton	m_ButtonColorOpen;
	CButton	m_ButtonColorClose;
	CSliderCtrl	m_SliderTransparentOpen;
	CSliderCtrl	m_SliderTransparentClose;
	CSliderCtrl	m_SliderBlinkCount;
	CString	m_strBlinkCount;
	CString	m_strFrameLength;
	CString	m_strColorClose;
	CString	m_strColorOpen;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CConfigDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CConfigDialog)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonColorOpen();
	afx_msg void OnButtonColorClose();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnReleasedcaptureSliderTransparentOpen(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderTransparentClose(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderBlinkFadeLength(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderBlinkCount(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonClose();
	afx_msg void OnButtonConfigManualBlinkSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	StConfig&	m_refConfig;

	CBrush		m_ColorBrushOpen;
	CBrush		m_ColorBrushClose;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_CONFIGDIALOG_H__D31BC462_D071_4A03_AB40_6AEAE2601DA4__INCLUDED_)
