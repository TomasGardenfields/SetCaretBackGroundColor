// SetCaretBackGroundColorDlg.cpp : �C���v�������e�[�V���� �t�@�C��
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
// CSetCaretBackGroundColorDlg �_�C�A���O

CSetCaretBackGroundColorDlg::CSetCaretBackGroundColorDlg( StConfig& i_refConfig, CWnd* pParent /*=NULL*/)
	: CDialog(CSetCaretBackGroundColorDlg::IDD, pParent), m_refConfig( i_refConfig )
{
	//{{AFX_DATA_INIT(CSetCaretBackGroundColorDlg)
		// ����: ���̈ʒu�� ClassWizard �ɂ���ă����o�̏��������ǉ�����܂��B
	//}}AFX_DATA_INIT
	// ����: LoadIcon �� Win32 �� DestroyIcon �̃T�u�V�[�P���X��v�����܂���B
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
		// ����: ���̏ꏊ�ɂ� ClassWizard �ɂ���� DDX �� DDV �̌Ăяo�����ǉ�����܂��B
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSetCaretBackGroundColorDlg, CDialog)
	//{{AFX_MSG_MAP(CSetCaretBackGroundColorDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_MESSAGE( WM_USER_NTFYICON, OnNotifyIconEvents )		// �^�X�N�g���C�A�C�R�����b�Z�[�W���n���h���Ɗ֘A�Â�
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
// CSetCaretBackGroundColorDlg ���b�Z�[�W �n���h��

BOOL CSetCaretBackGroundColorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���̃_�C�A���O�p�̃A�C�R����ݒ肵�܂��B�t���[�����[�N�̓A�v���P�[�V�����̃��C��
	// �E�B���h�E���_�C�A���O�łȂ����͎����I�ɐݒ肵�܂���B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R����ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R����ݒ�

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

	// TODO: ���ʂȏ��������s�����͂��̏ꏊ�ɒǉ����Ă��������B
	return TRUE;  // TRUE ��Ԃ��ƃR���g���[���ɐݒ肵���t�H�[�J�X�͎����܂���B
}

int CSetCaretBackGroundColorDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}
	
	/* ------------------------------------------------------ */
	//�^�X�N�g���C�A�C�R���̒ǉ��ݒ�
	{
		m_stNtfyIcon.cbSize = sizeof( NOTIFYICONDATA );					//�\���̂̃T�C�Y
		m_stNtfyIcon.uID = 0;											//�A�C�R���̎��ʃi���o�[
		m_stNtfyIcon.hWnd = m_hWnd;										//���b�Z�[�W�𑗂点��E�B���h�E�̃n���h��
		m_stNtfyIcon.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;			//�e��ݒ�
		m_stNtfyIcon.hIcon = AfxGetApp()->LoadIcon( IDI_TRAYICON );		//�A�v���P�[�V�����̃A�C�R��
		m_stNtfyIcon.uCallbackMessage = WM_USER_NTFYICON;				//�����Ă��炤���b�Z�[�W
		lstrcpy( m_stNtfyIcon.szTip, _T( "SetCaretBackGroundColor" ) );	//�`�b�v�̕�����
	}
	::Shell_NotifyIcon( NIM_ADD, &m_stNtfyIcon );	//�^�X�N�g���C�ɕ\�����܂��B
	this->m_boExisted = TRUE;

	this->ShowWindow( SW_SHOW );

//	this->EnableAlpha( WS_EX_LAYERED, RGB(255,128,64), 64, LWA_ALPHA );	// �����ڂ̂ݓ���
	this->EnableAlpha( WS_EX_LAYERED | WS_EX_TRANSPARENT, NULL, 0, LWA_ALPHA );	// �}�E�X���b�Z�[�W����
	// �E�B���h�E���őP�ʂɔz�u
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

	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����Ă�������
	this->m_Hook.Release();
	this->m_hWndTarget = NULL;

	this->m_boExisted = FALSE;

	/* ------------------------------------------------------ */
	// �^�X�N�g���C�A�C�R���폜
	::Shell_NotifyIcon( NIM_DELETE, &m_stNtfyIcon );
}


// �����_�C�A���O�{�b�N�X�ɍŏ����{�^����ǉ�����Ȃ�΁A�A�C�R����`�悷��
// �R�[�h���ȉ��ɋL�q����K�v������܂��BMFC �A�v���P�[�V������ document/view
// ���f�����g���Ă���̂ŁA���̏����̓t���[�����[�N�ɂ�莩���I�ɏ�������܂��B

void CSetCaretBackGroundColorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��p�̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// �N���C�A���g�̋�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R����`�悵�܂��B
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
	
	// TODO: ���̈ʒu�� DC �̃A�g���r���[�g��ύX���Ă�������
	
	// TODO: �f�t�H���g�̃u���V���]�݂̂��̂łȂ��ꍇ�ɂ́A�Ⴄ�u���V��Ԃ��Ă�������

	// �_�C�A���O�̐F�ύX
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
	// �����x���X�V
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

		// �ړI�̏�ԂɒB������^�C�}���~�߂�
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

// �V�X�e���́A���[�U�[���ŏ����E�B���h�E���h���b�O���Ă���ԁA
// �J�[�\����\�����邽�߂ɂ������Ăяo���܂��B
HCURSOR CSetCaretBackGroundColorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// �^�X�N�g���C�A�C�R���ւ̑���C�x���g�n���h��
LRESULT CSetCaretBackGroundColorDlg::OnNotifyIconEvents( WPARAM wParam, LPARAM lParam )
{
	//
	switch( lParam )
	{
	case WM_LBUTTONDOWN:
		// ���N���b�N�����Ƃ��̏���
		break;

	case WM_RBUTTONDOWN:
		// �E�N���b�N�����Ƃ��̏���
	
//		this->m_Hook.Pause( TRUE );
		this->TerminateAnimation();

		// �^�X�N�g���C���j���[�\��
		CMenu a_TaskTrayMenu;
		POINT a_CursorPos;

		VERIFY( a_TaskTrayMenu.LoadMenu( IDR_TRAYMENU ) );
		CMenu*  a_pPopupMenu = a_TaskTrayMenu.GetSubMenu( 0 );
		ASSERT( a_pPopupMenu != NULL );

		SetFocus();					// ��������Ȃ��ƁA���j���[�������Ȃ��Ȃ�܂��B

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
// ���C���E�B���h�E�̓���/�񓧉ߐݒ�
BOOL CSetCaretBackGroundColorDlg::EnableAlpha( DWORD i_dwExStyle, COLORREF i_color, BYTE i_alpha, DWORD i_flag )
{
	// �g���E�B���h�E�X�^�C���ύX
	DWORD dwExStyle = ::GetWindowLong( this->m_hWnd, GWL_EXSTYLE );
	dwExStyle |= i_dwExStyle;
	::SetWindowLong( this->m_hWnd, GWL_EXSTYLE, dwExStyle );

	// ���߃E�B���h�E�ݒ�(���C�u��������Ăяo��)
	typedef DWORD ( WINAPI *PSETLAYEREDWINDOWATTRIBUTES )( HWND, COLORREF, BYTE, DWORD );
	PSETLAYEREDWINDOWATTRIBUTES pSetLayeredWindowAttributes;

	HMODULE hDLL = ::LoadLibrary( "user32" );
	if ( hDLL )
	{
		pSetLayeredWindowAttributes = (PSETLAYEREDWINDOWATTRIBUTES)::GetProcAddress( hDLL, "SetLayeredWindowAttributes" );
		// �ǂݍ��݂ɐ���������A�֐������s���܂��B
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
	// �g���E�B���h�E�X�^�C���ύX
	DWORD dwExStyle = ::GetWindowLong( this->m_hWnd, GWL_EXSTYLE );
	dwExStyle ^= WS_EX_LAYERED;
	dwExStyle ^= WS_EX_TRANSPARENT;
	::SetWindowLong( this->m_hWnd, GWL_EXSTYLE, dwExStyle );
	// �ĕ`��
	this->Invalidate();

	return TRUE;
}

/* ****************************************************** */
// �^�X�N�g���C���j���[�I����
void CSetCaretBackGroundColorDlg::OnMenuitemTrayExit() 
{
	this->TerminateAnimation();

	// �E�B���h�E�����
	this->m_boExisted = false;
}

void CSetCaretBackGroundColorDlg::OnMenuitemTrayCancel() 
{
	// �Ȃɂ����Ȃ�	(���j���[����邾��)
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
	// �A�v���P�[�V�������ċN��
	TCHAR strPath[MAX_PATH];
	TCHAR strCurDir[MAX_PATH];

	::GetModuleFileName( ::AfxGetInstanceHandle(), strPath, sizeof(strPath) / sizeof(TCHAR) );
	::GetCurrentDirectory( sizeof(strCurDir) / sizeof(TCHAR), strCurDir );

	DWORD dwProcess = ::GetCurrentProcessId();
	CString strCmdLine;
	strCmdLine.Format("/restart %x", dwProcess );

	::ShellExecute( NULL, NULL, strPath, strCmdLine, strCurDir, SW_SHOWNORMAL );

	// �������g�͏I��(�ċN�������I���̈׃V�O�i�����삵�Ă����̂ł����瑤�͂Ȃɂ����Ȃ�)
}

/* ****************************************************** */
// 
LRESULT CSetCaretBackGroundColorDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	
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
				( wParam == (WPARAM)VK_DBE_SBCSCHAR ) ||						// �S�p/���p
				( wParam == (WPARAM)VK_DBE_DBCSCHAR ) ||						// ����
				( ( wParam == (WPARAM)VK_KANJI ) || ( lParam & 0x2000000 ) ) )	// Alt+�S�p/���p
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
	// ���E�B���h�E/�q�E�B���h�E�����O
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
	// �����ΏۃN���X���̃E�B���h�E�����O
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

	// ��U�A�j���[�V�������~�߂�
	this->KillTimer( ID_TIMER_FADEOUT );

	StWindowState a_TempState;
	CRect rect;

	// �E�B���h�E�ʒu���^�[�Q�b�g�ֈړ�
	if ( !::GetWindowRect( i_hWndTarget, &rect ) )
	{
		TRACE0( "SetTarget: Failed \n" );
		return FALSE;
	}
	this->m_hWndTarget = i_hWndTarget;
	this->m_pIgnoreDlg->AddHistory( i_hWndTarget );

	this->MoveWindow( &rect );

	// IME��ON/OF��Ԃ��擾
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

	// �A�j���[�V�����p�t���[���J�E���^�����������^�C�}�N�����A�j���[�V�����J�n
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
// �������̃E�B���h�E���������̃E�B���h�E�̎q���ł��邩�ǂ������`�F�b�N����
BOOL CSetCaretBackGroundColorDlg::IsOffspringWindow(HWND i_hWnd, HWND i_hWndTarget)
{
	TRACE2( "IsOffspringWindow Begin(Base/Target) %08X / %08X\n", i_hWnd, i_hWndTarget );

	const HWND hWndDesktop = ::GetDesktopWindow();

	// �e�E�B���h�E�̃`�F�b�N
	// ���������[�v����ׁ̈A255�K�w�܂ŒT�����ăq�b�g���Ȃ������ꍇ��FALSE�����Ƃ���
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

	// �ǂ���قȂ�ꍇ��FALSE
	TRACE0( "IsOffspringWindow Result: FALSE\n" );
	return FALSE;
}
