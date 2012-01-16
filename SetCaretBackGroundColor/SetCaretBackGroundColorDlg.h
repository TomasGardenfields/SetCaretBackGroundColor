// SetCaretBackGroundColorDlg.h : ヘッダー ファイル
//

#if !defined(AFX_SETCARETBACKGROUNDCOLORDLG_H__929F7845_1E5B_48FB_95BF_87429E1CD129__INCLUDED_)
#define AFX_SETCARETBACKGROUNDCOLORDLG_H__929F7845_1E5B_48FB_95BF_87429E1CD129__INCLUDED_

#include "../MsgHook/StdHead.h"
#include "../MsgHook/Hook.h"

#include "WindowState.h"
#include "stConfig.h"

// 半透明ウィンドウ用定義
#define WS_EX_LAYERED	0x80000
#define LWA_COLORKEY	1
#define LWA_ALPHA		2

// IME状態設定/取得メッセージ
#define IMC_GETOPENSTATUS 0x0005
#define IMC_SETOPENSTATUS 0x0006


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CConfigDialog;
class CIgnoreDialog;

/////////////////////////////////////////////////////////////////////////////
// CSetCaretBackGroundColorDlg ダイアログ

class CSetCaretBackGroundColorDlg : public CDialog
{
// 構築
public:
	CSetCaretBackGroundColorDlg( StConfig& i_refConfig, CWnd* pParent = NULL );	// 標準のコンストラクタ
	virtual ~CSetCaretBackGroundColorDlg();	// デストラクタ
	BOOL IsExisted();

	enum {
		ID_TIMER_FADEIN = 1,
		ID_TIMER_FADEOUT = 2,
	};

// ダイアログ データ
	//{{AFX_DATA(CSetCaretBackGroundColorDlg)
	enum { IDD = IDD_SETCARETBACKGROUNDCOLOR_DIALOG };
		// メモ: この位置に ClassWizard によってデータ メンバが追加されます。
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CSetCaretBackGroundColorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

	CConfigDialog*	m_pConfigDlg;
	CIgnoreDialog*	m_pIgnoreDlg;

// インプリメンテーション
protected:
	HICON m_hIcon;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CSetCaretBackGroundColorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg LRESULT OnNotifyIconEvents( WPARAM wParam, LPARAM lParam );
	afx_msg void OnMenuitemTrayExit();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMenuitemTrayCancel();
	afx_msg void OnMenuitemTrayConfig();
	afx_msg void OnMenuitemTrayRestart();
	afx_msg void OnMenuitemTrayIgnore();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL IsOffspringWindow( HWND i_hWndParent, HWND i_hWndTarget );
	BOOL UpdateWindowBrush();
	BOOL EnableAlpha( DWORD i_dwExStyle, COLORREF i_color, BYTE i_alpha, DWORD i_flag );
	BOOL DisableAlpha( void );
	BOOL ResizeMainWindow( HWND i_hWndCurrent );

	BOOL UpdateWindow( StWindowState i_WindowState );
	BOOL SetTarget( HWND i_hWndTarget, BYTE i_Transparency, UINT i_nIDEvent );
	BOOL TerminateAnimation();

	BOOL m_boTransparent;
	BOOL m_boExisted;
	NOTIFYICONDATA	m_stNtfyIcon;
	
	CHook m_Hook;

	HWND			m_hWndTarget;
	CBrush			m_BackGroundBrushOpen;
	CBrush			m_BackGroundBrushClose;

	StConfig&		m_refConfig;
	StWindowState	m_CurrentState;
	StWindowState	m_PreviousState;
	StWindowState	m_NextState;

	int			m_AnimationFrame;
	int			m_BlinkCount;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SETCARETBACKGROUNDCOLORDLG_H__929F7845_1E5B_48FB_95BF_87429E1CD129__INCLUDED_)
