// SetCaretBackGroundColorDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include <IME.h>
#include <IMM.h>

#include "SetCaretBackGroundColor.h"
#include "SetCaretBackGroundColorDlg.h"
#include "ConfigDialog.h"

#include "IgnoreDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetCaretBackGroundColorDlg ダイアログ

CSetCaretBackGroundColorDlg::CSetCaretBackGroundColorDlg( StConfig& i_refConfig, CWnd* pParent /*=NULL*/)
	: CDialog(CSetCaretBackGroundColorDlg::IDD, pParent), m_refConfig( i_refConfig )
{
	//{{AFX_DATA_INIT(CSetCaretBackGroundColorDlg)
		// メモ: この位置に ClassWizard によってメンバの初期化が追加されます。
	//}}AFX_DATA_INIT
	// メモ: LoadIcon は Win32 の DestroyIcon のサブシーケンスを要求しません。
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	this->m_boExisted = FALSE;
	this->m_boTransparent = FALSE;
	this->m_AnimationFrame = 0;
	this->m_BlinkCount = 0;

	this->m_hWndTarget = NULL;

	this->m_pConfigDlg = NULL;
	this->m_pIgnoreDlg = NULL;
}

CSetCaretBackGroundColorDlg::~CSetCaretBackGroundColorDlg()
{
	if ( this->m_pConfigDlg )
	{
		this->m_pConfigDlg = NULL;
	}
	if ( this->m_pIgnoreDlg )
	{
		this->m_pIgnoreDlg = NULL;
	}
}

void CSetCaretBackGroundColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetCaretBackGroundColorDlg)
		// メモ: この場所には ClassWizard によって DDX と DDV の呼び出しが追加されます。
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSetCaretBackGroundColorDlg, CDialog)
	//{{AFX_MSG_MAP(CSetCaretBackGroundColorDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_MESSAGE( WM_USER_NTFYICON, OnNotifyIconEvents )		// タスクトレイアイコンメッセージをハンドラと関連づけ
	ON_COMMAND(ID_MENUITEM_TRAY_EXIT, OnMenuitemTrayExit)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_COMMAND(ID_MENUITEM_TRAY_CANCEL, OnMenuitemTrayCancel)
	ON_COMMAND(ID_MENUITEM_TRAY_CONFIG, OnMenuitemTrayConfig)
	ON_COMMAND(ID_MENUITEM_TRAY_RESTART, OnMenuitemTrayRestart)
	ON_COMMAND(ID_MENUITEM_TRAY_IGNORE, OnMenuitemTrayIgnore)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetCaretBackGroundColorDlg メッセージ ハンドラ

BOOL CSetCaretBackGroundColorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// このダイアログ用のアイコンを設定します。フレームワークはアプリケーションのメイン
	// ウィンドウがダイアログでない時は自動的に設定しません。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定

	this->m_pConfigDlg = new CConfigDialog( this->m_refConfig, this );
	if ( this->m_pConfigDlg == NULL )
	{
		return FALSE;
	}

	this->m_pIgnoreDlg = new CIgnoreDialog( this->m_refConfig, this );
	if ( this->m_pIgnoreDlg == NULL )
	{
		return FALSE;
	}
	
	this->SetWindowText( "SetCaretBackGroundColor" );

	// TODO: 特別な初期化を行う時はこの場所に追加してください。
	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

int CSetCaretBackGroundColorDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}
	
	/* ------------------------------------------------------ */
	//タスクトレイアイコンの追加設定
	{
		m_stNtfyIcon.cbSize = sizeof( NOTIFYICONDATA );					//構造体のサイズ
		m_stNtfyIcon.uID = 0;											//アイコンの識別ナンバー
		m_stNtfyIcon.hWnd = m_hWnd;										//メッセージを送らせるウィンドウのハンドル
		m_stNtfyIcon.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;			//各種設定
		m_stNtfyIcon.hIcon = AfxGetApp()->LoadIcon( IDI_TRAYICON );		//アプリケーションのアイコン
		m_stNtfyIcon.uCallbackMessage = WM_USER_NTFYICON;				//送ってもらうメッセージ
		lstrcpy( m_stNtfyIcon.szTip, _T( "SetCaretBackGroundColor" ) );	//チップの文字列
	}
	::Shell_NotifyIcon( NIM_ADD, &m_stNtfyIcon );	//タスクトレイに表示します。
	this->m_boExisted = TRUE;

	this->ShowWindow( SW_SHOW );

//	this->EnableAlpha( WS_EX_LAYERED, RGB(255,128,64), 64, LWA_ALPHA );	// 見た目のみ透過
	this->EnableAlpha( WS_EX_LAYERED | WS_EX_TRANSPARENT, NULL, 0, LWA_ALPHA );	// マウスメッセージ透過
	// ウィンドウを最善面に配置
	this->SetWindowPos( &CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );

	m_BackGroundBrushOpen.CreateSolidBrush( this->m_refConfig.m_BackGroundColorOpen );
	m_BackGroundBrushClose.CreateSolidBrush( this->m_refConfig.m_BackGroundColorClose );

	this->m_hWndTarget = NULL;
	this->m_Hook.Set( this->m_hWnd );
	TRACE1( "CSetCaretBackGroundColorDlg::m_hWnd : %08X\n", (DWORD)this->m_hWnd );

	return 0;
}

void CSetCaretBackGroundColorDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	this->m_pIgnoreDlg = NULL;

	this->m_BackGroundBrushOpen.DeleteObject();
	this->m_BackGroundBrushClose.DeleteObject();

	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
	this->m_Hook.Release();
	this->m_hWndTarget = NULL;

	this->m_boExisted = FALSE;

	/* ------------------------------------------------------ */
	// タスクトレイアイコン削除
	::Shell_NotifyIcon( NIM_DELETE, &m_stNtfyIcon );
}


// もしダイアログボックスに最小化ボタンを追加するならば、アイコンを描画する
// コードを以下に記述する必要があります。MFC アプリケーションは document/view
// モデルを使っているので、この処理はフレームワークにより自動的に処理されます。

void CSetCaretBackGroundColorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画用のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// クライアントの矩形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンを描画します。
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

/* ////////////////////////////////////////////////////// */
//
HBRUSH CSetCaretBackGroundColorDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: この位置で DC のアトリビュートを変更してください
	
	// TODO: デフォルトのブラシが望みのものでない場合には、違うブラシを返してください

	// ダイアログの色変更
	if ( nCtlColor == CTLCOLOR_DLG )
	{
		if ( pWnd == this )
		{
			if ( this->m_NextState.m_Color == this->m_refConfig.m_BackGroundColorOpen )
			{
				hbr = this->m_BackGroundBrushOpen;
			}
			else if ( this->m_NextState.m_Color == this->m_refConfig.m_BackGroundColorClose )
			{
				hbr = this->m_BackGroundBrushClose;
			}
		}
	}

	return hbr;
}

BOOL CSetCaretBackGroundColorDlg::UpdateWindow( StWindowState i_WindowState )
{
	// 透明度を更新
	this->EnableAlpha( WS_EX_LAYERED | WS_EX_TRANSPARENT, 0, i_WindowState.m_Transparency, LWA_ALPHA );

	return TRUE;
}

void CSetCaretBackGroundColorDlg::OnTimer(UINT nIDEvent) 
{
//	TRACE0( "OnTimer" );
	if( nIDEvent == ID_TIMER_FADEOUT )
	{
		this->m_AnimationFrame++;
		float rate = this->m_AnimationFrame / (float)this->m_refConfig.m_FrameLength;
//		TRACE1( "OnTimer/ID_TIMER_FADEOUT: %08f \n", rate );

		this->m_CurrentState = StWindowState::Interpolate( this->m_NextState, this->m_PreviousState, rate );
		UpdateWindow( this->m_CurrentState );

		// 目的の状態に達したらタイマを止める
		if ( (int)this->m_refConfig.m_FrameLength <= (int)this->m_AnimationFrame )
		{
			this->m_BlinkCount++;

			if ( this->m_refConfig.m_BlinkCount <= this->m_BlinkCount )
			{
				TRACE0( "OnTimer/ID_TIMER_FADEOUT/END\n" );
				this->TerminateAnimation();
			}
			else
			{
				this->m_AnimationFrame = 0;
			}
		}
	}

	CDialog::OnTimer(nIDEvent);
}

// システムは、ユーザーが最小化ウィンドウをドラッグしている間、
// カーソルを表示するためにここを呼び出します。
HCURSOR CSetCaretBackGroundColorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// タスクトレイアイコンへの操作イベントハンドラ
LRESULT CSetCaretBackGroundColorDlg::OnNotifyIconEvents( WPARAM wParam, LPARAM lParam )
{
	//
	switch( lParam )
	{
	case WM_LBUTTONDOWN:
		// 左クリックしたときの処理
		break;

	case WM_RBUTTONDOWN:
		// 右クリックしたときの処理
	
//		this->m_Hook.Pause( TRUE );
		this->TerminateAnimation();

		// タスクトレイメニュー表示
		CMenu a_TaskTrayMenu;
		POINT a_CursorPos;

		VERIFY( a_TaskTrayMenu.LoadMenu( IDR_TRAYMENU ) );
		CMenu*  a_pPopupMenu = a_TaskTrayMenu.GetSubMenu( 0 );
		ASSERT( a_pPopupMenu != NULL );

		SetFocus();					// これをしないと、メニューが消えなくなります。

		::GetCursorPos( &a_CursorPos );
		a_pPopupMenu->TrackPopupMenu(
			NULL,
			a_CursorPos.x, a_CursorPos.y,
			this );

		PostMessage( WM_NULL );

//		this->m_Hook.Pause( FALSE );

		break;
	}

	return 0;
}

BOOL CSetCaretBackGroundColorDlg::IsExisted()
{
	return this->m_boExisted;
}

/* ****************************************************** */
// メインウィンドウの透過/非透過設定
BOOL CSetCaretBackGroundColorDlg::EnableAlpha( DWORD i_dwExStyle, COLORREF i_color, BYTE i_alpha, DWORD i_flag )
{
	// 拡張ウィンドウスタイル変更
	DWORD dwExStyle = ::GetWindowLong( this->m_hWnd, GWL_EXSTYLE );
	dwExStyle |= i_dwExStyle;
	::SetWindowLong( this->m_hWnd, GWL_EXSTYLE, dwExStyle );

	// 透過ウィンドウ設定(ライブラリから呼び出し)
	typedef DWORD ( WINAPI *PSETLAYEREDWINDOWATTRIBUTES )( HWND, COLORREF, BYTE, DWORD );
	PSETLAYEREDWINDOWATTRIBUTES pSetLayeredWindowAttributes;

	HMODULE hDLL = ::LoadLibrary( "user32" );
	if ( hDLL )
	{
		pSetLayeredWindowAttributes = (PSETLAYEREDWINDOWATTRIBUTES)::GetProcAddress( hDLL, "SetLayeredWindowAttributes" );
		// 読み込みに成功したら、関数を実行します。
		if( pSetLayeredWindowAttributes )
		{
			pSetLayeredWindowAttributes( this->m_hWnd, i_color, i_alpha, i_flag );
		}
		FreeLibrary( hDLL );
	}
	else
	{
		return FALSE;
	}
	
	return TRUE;
}

BOOL CSetCaretBackGroundColorDlg::DisableAlpha( void )
{
	// 拡張ウィンドウスタイル変更
	DWORD dwExStyle = ::GetWindowLong( this->m_hWnd, GWL_EXSTYLE );
	dwExStyle ^= WS_EX_LAYERED;
	dwExStyle ^= WS_EX_TRANSPARENT;
	::SetWindowLong( this->m_hWnd, GWL_EXSTYLE, dwExStyle );
	// 再描画
	this->Invalidate();

	return TRUE;
}

/* ****************************************************** */
// タスクトレイメニュー選択時
void CSetCaretBackGroundColorDlg::OnMenuitemTrayExit() 
{
	this->TerminateAnimation();

	// ウィンドウを閉じる
	this->m_boExisted = false;
}

void CSetCaretBackGroundColorDlg::OnMenuitemTrayCancel() 
{
	// なにもしない	(メニューを閉じるだけ)
}

void CSetCaretBackGroundColorDlg::OnMenuitemTrayConfig() 
{
	this->m_pConfigDlg->ShowWindow( SW_SHOW );
}

void CSetCaretBackGroundColorDlg::OnMenuitemTrayIgnore() 
{
	this->m_pIgnoreDlg->ShowWindow( SW_SHOW );	
}

void CSetCaretBackGroundColorDlg::OnMenuitemTrayRestart() 
{
	// アプリケーションを再起動
	TCHAR strPath[MAX_PATH];
	TCHAR strCurDir[MAX_PATH];

	::GetModuleFileName( ::AfxGetInstanceHandle(), strPath, sizeof(strPath) / sizeof(TCHAR) );
	::GetCurrentDirectory( sizeof(strCurDir) / sizeof(TCHAR), strCurDir );

	DWORD dwProcess = ::GetCurrentProcessId();
	CString strCmdLine;
	strCmdLine.Format("/restart %x", dwProcess );

	::ShellExecute( NULL, NULL, strPath, strCmdLine, strCurDir, SW_SHOWNORMAL );

	// 自分自身は終了(再起動側が終了の為シグナル操作してくれるのでこちら側はなにもしない)
}

/* ****************************************************** */
// 
LRESULT CSetCaretBackGroundColorDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	
	switch ( message )
	{
	case WM_APP_HCBT_SETFOCUS:
		{
			TRACE2( "WM_APP_HCBT_SETFOCUS wParam / lParam: %08X / %08X\n", wParam, lParam );
			HWND hWndCurrent = (HWND)wParam;
			//HWND hWndPrevious = (HWND)lParam;

			this->ResizeMainWindow( hWndCurrent );
		}
		break;

	case WM_APP_HCBT_MOVESIZE:
		{
			TRACE2( "WM_APP_HCBT_MOVESIZE wParam / lParam: %08X / %08X\n", wParam, lParam );
			HWND hWndCurrent = (HWND)wParam;
			//RECT *rect = (RECT*)lParam;

			this->ResizeMainWindow( hWndCurrent );
		}
		break;

	case WM_APP_HKEYBOARD:
		{
			TRACE2( "WM_APP_HKEYBOARD wParam / lParam: %08X / %08X\n", wParam, lParam );
			if (
				( wParam == (WPARAM)VK_DBE_SBCSCHAR ) ||						// 全角/半角
				( wParam == (WPARAM)VK_DBE_DBCSCHAR ) ||						// 同上
				( ( wParam == (WPARAM)VK_KANJI ) || ( lParam & 0x2000000 ) ) )	// Alt+全角/半角
			{
				ResizeMainWindow( this->m_hWndTarget );
			}
		}
		break;

	case WM_APP_UPDATECOLOR:
		{
			TRACE0( "WM_APP_UPDATECOLOR" );
			this->UpdateWindowBrush();
		}
		break;

	default:
		break;
	}

	return CDialog::WindowProc(message, wParam, lParam);
}

/* ////////////////////////////////////////////////////// */
// 
BOOL CSetCaretBackGroundColorDlg::ResizeMainWindow( HWND i_hWndCurrent )
{
	TRACE1( "ResizeMainWindow: %08X \n", i_hWndCurrent );

	/* ------------------------------------------------------ */
	// 自ウィンドウ/子ウィンドウを除外
	BOOL boResult = this->IsOffspringWindow( this->m_hWnd, i_hWndCurrent );
	if ( boResult )
	{
		TRACE0( "ResizeMainWindow Excluded(Offspring)\n" );
		return FALSE;
	}
	else
	{
		TRACE0( "ResizeMainWindow Not Excluded(Offspring)\n" );
	}

	/* ------------------------------------------------------ */
	// 無視対象クラス名のウィンドウを除外
	CString strClassName;
	::GetClassName( i_hWndCurrent, strClassName.GetBuffer( 256 ), 256 );
	strClassName.ReleaseBuffer();

	if ( FALSE == this->m_refConfig.IsIgnoreClassName( strClassName ) )
	{
		TRACE1( "ResizeMainWindow Excluded(ClassName): %s\n", strClassName );
		return FALSE;
	}
	else
	{
		TRACE1( "ResizeMainWindow Not Excluded(ClassName): %s\n", strClassName );
	}

	CWnd* pWndCurrent = CWnd::FromHandle( i_hWndCurrent );
	if ( pWndCurrent == NULL )
	{
		TRACE0( "ResizeMainWindow Failed\n" );
		return FALSE;
	}

	this->SetTarget( i_hWndCurrent, 0, ID_TIMER_FADEOUT );

	return TRUE;
}

/* ////////////////////////////////////////////////////// */
// 
BOOL CSetCaretBackGroundColorDlg::SetTarget( HWND i_hWndTarget, BYTE i_Transparency, UINT i_nIDEvent )
{
	TRACE0("SetTarget() begin ");

	// 一旦アニメーションを止める
	this->KillTimer( ID_TIMER_FADEOUT );

	StWindowState a_TempState;
	CRect rect;

	// ウィンドウ位置をターゲットへ移動
	if ( !::GetWindowRect( i_hWndTarget, &rect ) )
	{
		TRACE0( "SetTarget: Failed \n" );
		return FALSE;
	}
	this->m_hWndTarget = i_hWndTarget;
	this->m_pIgnoreDlg->AddHistory( i_hWndTarget );

	this->MoveWindow( &rect );

	// IMEのON/OF状態を取得
	BOOL boIMEOpen = FALSE;
	HWND hWndIME = ImmGetDefaultIMEWnd( this->m_hWndTarget );
	if ( hWndIME )
	{
		boIMEOpen = ::SendMessage( hWndIME, WM_IME_CONTROL, IMC_GETOPENSTATUS, NULL );
	}

	a_TempState.m_Transparency = i_Transparency;
	if ( boIMEOpen )
	{
		a_TempState.m_Color = this->m_refConfig.m_BackGroundColorOpen;

		this->m_CurrentState.m_Transparency = this->m_refConfig.m_TransparencyOpen;
		this->m_CurrentState.m_Color = this->m_refConfig.m_BackGroundColorOpen;
	}
	else
	{
		a_TempState.m_Color = this->m_refConfig.m_BackGroundColorClose;

		this->m_CurrentState.m_Transparency = this->m_refConfig.m_TransparencyClose;
		this->m_CurrentState.m_Color = this->m_refConfig.m_BackGroundColorClose;
	}
	TRACE1("TargetColor: %08X\n", (DWORD)a_TempState.m_Color );

	this->m_PreviousState = this->m_CurrentState;
	this->m_NextState = a_TempState;

	// アニメーション用フレームカウンタを初期化＆タイマ起動しアニメーション開始
	this->m_AnimationFrame = 0;
	this->m_BlinkCount = 0;

//	TRACE1( "SetTarget EventID: %08X \n", i_nIDEvent );
	this->SetTimer( i_nIDEvent, 50, NULL );

	this->Invalidate();
	::InvalidateRect( this->m_hWndTarget, NULL, TRUE );

	return TRUE;
}

BOOL CSetCaretBackGroundColorDlg::TerminateAnimation()
{
	this->KillTimer( ID_TIMER_FADEOUT );
	this->m_AnimationFrame = 0;
	this->m_BlinkCount = 0;
	this->m_CurrentState = this->m_NextState;
	UpdateWindow( this->m_CurrentState );

	this->Invalidate();
	::InvalidateRect( this->m_hWndTarget, NULL, TRUE );

	return TRUE;
}

/* ////////////////////////////////////////////////////// */
// 
BOOL CSetCaretBackGroundColorDlg::UpdateWindowBrush()
{
	this->TerminateAnimation();

	if ( this->m_BackGroundBrushOpen.m_hObject != NULL )
	{
		this->m_BackGroundBrushOpen.DeleteObject();
	}
	this->m_BackGroundBrushOpen.CreateSolidBrush( this->m_refConfig.m_BackGroundColorOpen );

	if ( this->m_BackGroundBrushClose.m_hObject != NULL )
	{
		this->m_BackGroundBrushClose.DeleteObject();
	}
	this->m_BackGroundBrushClose.CreateSolidBrush( this->m_refConfig.m_BackGroundColorClose );

	return true;
}

/* ////////////////////////////////////////////////////// */
// 第二引数のウィンドウが第一引数のウィンドウの子孫であるかどうかをチェックする
BOOL CSetCaretBackGroundColorDlg::IsOffspringWindow(HWND i_hWnd, HWND i_hWndTarget)
{
	TRACE2( "IsOffspringWindow Begin(Base/Target) %08X / %08X\n", i_hWnd, i_hWndTarget );

	const HWND hWndDesktop = ::GetDesktopWindow();

	// 親ウィンドウのチェック
	// ※無限ループ回避の為、255階層まで探査してヒットしなかった場合はFALSE扱いとする
	HWND hWndparent = ::GetParent( i_hWndTarget );
//	for ( int i = 0 ; ( i < 255 ) && ( hWndDesktop != hWndparent ) && ( NULL != hWndparent ) ; i++ )
	for ( int i = 0 ; ( i < 255 ) && ( NULL != hWndparent ) ; i++ )
	{
		TRACE2( "IsOffspringWindow(Parent)(%03d): %08X\n", i, hWndparent );
		if ( i_hWnd == hWndparent )
		{
			TRACE0( "IsOffspringWindow(Parent) Result: TRUE\n" );
			return TRUE;
		}

		hWndparent = ::GetParent( hWndparent );
	}

	// どれも異なる場合はFALSE
	TRACE0( "IsOffspringWindow Result: FALSE\n" );
	return FALSE;
}
