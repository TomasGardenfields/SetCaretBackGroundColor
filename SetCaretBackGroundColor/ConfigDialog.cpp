// ConfigDialog.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "SetCaretBackGroundColor.h"
#include "ConfigDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigDialog ダイアログ


CConfigDialog::CConfigDialog( StConfig& i_refConfig, CWnd* pParent /*=NULL*/)
	: CDialog(CConfigDialog::IDD, pParent), m_refConfig( i_refConfig )
{
	//{{AFX_DATA_INIT(CConfigDialog)
	m_strBlinkCount = _T("");
	m_strFrameLength = _T("");
	m_strColorClose = _T("");
	m_strColorOpen = _T("");
	//}}AFX_DATA_INIT

	this->Create( IDD, pParent );
}

CConfigDialog::~CConfigDialog()
{
	this->DestroyWindow();
	CDialog::~CDialog();
}

void CConfigDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigDialog)
	DDX_Control(pDX, IDC_SLIDER_BLINK_FADE_LENGTH, m_SliderBlinkFrameLength);
	DDX_Control(pDX, IDC_STATIC_PICTURE_COLOR_CLOSE, m_StaticColorClose);
	DDX_Control(pDX, IDC_STATIC_PICTURE_COLOR_OPEN, m_StaticColorOpen);
	DDX_Control(pDX, IDC_BUTTON_COLOR_OPEN, m_ButtonColorOpen);
	DDX_Control(pDX, IDC_BUTTON_COLOR_CLOSE, m_ButtonColorClose);
	DDX_Control(pDX, IDC_SLIDER_TRANSPARENT_OPEN, m_SliderTransparentOpen);
	DDX_Control(pDX, IDC_SLIDER_TRANSPARENT_CLOSE, m_SliderTransparentClose);
	DDX_Control(pDX, IDC_SLIDER_BLINK_COUNT, m_SliderBlinkCount);
	DDX_Text(pDX, IDC_EDIT_BLINK_COUNT, m_strBlinkCount);
	DDX_Text(pDX, IDC_EDIT_BLINK_FRAMELENGTH, m_strFrameLength);
	DDX_Text(pDX, IDC_EDIT_COLOR_CLOSE, m_strColorClose);
	DDX_Text(pDX, IDC_EDIT_COLOR_OPEN, m_strColorOpen);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigDialog, CDialog)
	//{{AFX_MSG_MAP(CConfigDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_COLOR_OPEN, OnButtonColorOpen)
	ON_BN_CLICKED(IDC_BUTTON_COLOR_CLOSE, OnButtonColorClose)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_TRANSPARENT_OPEN, OnReleasedcaptureSliderTransparentOpen)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_TRANSPARENT_CLOSE, OnReleasedcaptureSliderTransparentClose)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_BLINK_FADE_LENGTH, OnReleasedcaptureSliderBlinkFadeLength)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_BLINK_COUNT, OnReleasedcaptureSliderBlinkCount)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigDialog メッセージ ハンドラ

BOOL CConfigDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// ダイアログ内コントロールの初期化
	this->m_SliderTransparentOpen.SetRange( 1, 255, FALSE );
	this->m_SliderTransparentOpen.SetPageSize( 10 );
	this->m_SliderTransparentClose.SetRange( 1, 255, FALSE );
	this->m_SliderTransparentOpen.SetPageSize( 10 );

	this->m_SliderBlinkFrameLength.SetRange( 1, 255, FALSE );
	this->m_SliderBlinkFrameLength.SetPageSize( 10 );
	this->m_SliderBlinkCount.SetRange( 1, 16, FALSE );
	this->m_SliderBlinkCount.SetPageSize( 1 );

	this->m_SliderBlinkFrameLength.SetPos( this->m_refConfig.m_FrameLength );
	this->m_strFrameLength.Format( "%d", this->m_refConfig.m_FrameLength );

	this->m_SliderBlinkCount.SetPos( (BYTE)this->m_refConfig.m_BlinkCount );
	this->m_strBlinkCount.Format( "%d", this->m_refConfig.m_BlinkCount );
	
	this->m_SliderTransparentOpen.SetPos( (BYTE)this->m_refConfig.m_TransparencyOpen );
	this->m_strColorOpen.Format( "%d", this->m_refConfig.m_TransparencyOpen );
	this->m_ColorBrushOpen.CreateSolidBrush( this->m_refConfig.m_BackGroundColorOpen );

	this->m_SliderTransparentClose.SetPos( (BYTE)this->m_refConfig.m_TransparencyClose );
	this->m_strColorClose.Format( "%d", this->m_refConfig.m_TransparencyClose );
	this->m_ColorBrushClose.CreateSolidBrush( this->m_refConfig.m_BackGroundColorClose );

	this->UpdateData( FALSE );
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CConfigDialog::PostNcDestroy() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	delete this;	
	CDialog::PostNcDestroy();
}

HBRUSH CConfigDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: この位置で DC のアトリビュートを変更してください
	
	if ( nCtlColor =  CTLCOLOR_STATIC )
	{
		if ( pWnd->m_hWnd == this->m_StaticColorOpen.m_hWnd )
		{
			hbr = this->m_ColorBrushOpen;
		}
		else if ( pWnd->m_hWnd == this->m_StaticColorClose.m_hWnd )
		{
			hbr = this->m_ColorBrushClose;
		}
	}

	// TODO: デフォルトのブラシが望みのものでない場合には、違うブラシを返してください
	return hbr;
}

void CConfigDialog::OnOK() 
{
	// OnOKを呼ばない(Enter押下時対応)
//	CDialog::OnOK();

	// ウィンドウを非表示にする(閉じない)
	this->ShowWindow( SW_HIDE );	
}

void CConfigDialog::OnCancel() 
{
	// コンフィグを変更前に戻す
//	this->m_CurrentConfig.Copy( this->m_PrevConfig );
	// OnCancelを呼ばない(Esc押下時対応)
//	CDialog::OnCancel();

	// ウィンドウを非表示にする(閉じない)
	this->ShowWindow( SW_HIDE );	
}

void CConfigDialog::OnButtonClose() 
{
	// ウィンドウを非表示にする(閉じない)
	this->ShowWindow( SW_HIDE );	
}

void CConfigDialog::OnButtonColorOpen() 
{
	/* ------------------------------------------------------ */
	DWORD dwCustomColors[16]; // 「作成した色」を表示する 16 個のボックス
	dwCustomColors[0] = this->m_refConfig.m_BackGroundColorOpen;
	dwCustomColors[1] = this->m_refConfig.m_BackGroundColorClose;
	int i;
	for( i = 2 ; i < 16 ; i++ )
	{
		dwCustomColors[i] = RGB( 255, 255, 255 );
	}

	CHOOSECOLOR cc;
	ZeroMemory( &cc, sizeof(CHOOSECOLOR) );
	cc.lStructSize = sizeof(cc);
	cc.hwndOwner = this->m_hWnd;
	cc.rgbResult = this->m_refConfig.m_BackGroundColorOpen;
	cc.lpCustColors = dwCustomColors;
	cc.Flags = CC_RGBINIT;

	int iResult = ChooseColor( &cc );
	if ( iResult == TRUE )
	{
		// 親ダイアログ側へ色変更通知
		this->m_refConfig.m_BackGroundColorOpen = cc.rgbResult;
		::PostMessage( this->GetParent()->m_hWnd, WM_APP_UPDATECOLOR, NULL, NULL );

		// 設定ダイアログ内の色(Open側)変更
		this->m_ColorBrushOpen.DeleteObject();
		this->m_ColorBrushOpen.CreateSolidBrush( this->m_refConfig.m_BackGroundColorOpen );
		this->m_StaticColorOpen.Invalidate();
	}
}

void CConfigDialog::OnReleasedcaptureSliderTransparentOpen(NMHDR* pNMHDR, LRESULT* pResult) 
{
	this->m_refConfig.m_TransparencyOpen = this->m_SliderTransparentOpen.GetPos();
	this->m_strColorOpen.Format( "%d", this->m_refConfig.m_TransparencyOpen );
	UpdateData( FALSE );
	*pResult = 0;
}

void CConfigDialog::OnButtonColorClose() 
{
	/* ------------------------------------------------------ */
	DWORD dwCustomColors[16]; // 「作成した色」を表示する 16 個のボックス
	dwCustomColors[0] = this->m_refConfig.m_BackGroundColorClose;
	dwCustomColors[1] = this->m_refConfig.m_BackGroundColorOpen;
	int i;
	for( i = 2 ; i < 16 ; i++ )
	{
		dwCustomColors[i] = RGB( 255, 255, 255 );
	}

	CHOOSECOLOR cc;
	ZeroMemory( &cc, sizeof(CHOOSECOLOR) );
	cc.lStructSize = sizeof(cc);
	cc.hwndOwner = this->m_hWnd;
	cc.rgbResult = this->m_refConfig.m_BackGroundColorClose;
	cc.lpCustColors = dwCustomColors;
	cc.Flags = CC_RGBINIT;

	int iResult = ChooseColor( &cc );
	if ( iResult == TRUE )
	{
		// 親ダイアログ側へ色変更通知
		this->m_refConfig.m_BackGroundColorClose = cc.rgbResult;
		::PostMessage( this->GetParent()->m_hWnd, WM_APP_UPDATECOLOR, NULL, NULL );

		// 設定ダイアログ内の色(Close側)変更
		this->m_ColorBrushClose.DeleteObject();
		this->m_ColorBrushClose.CreateSolidBrush( this->m_refConfig.m_BackGroundColorClose );
		this->m_StaticColorClose.Invalidate();
	}
}

void CConfigDialog::OnReleasedcaptureSliderTransparentClose(NMHDR* pNMHDR, LRESULT* pResult) 
{
	this->m_refConfig.m_TransparencyClose = this->m_SliderTransparentClose.GetPos();
	this->m_strColorClose.Format( "%d", this->m_refConfig.m_TransparencyClose );
	UpdateData( FALSE );
	*pResult = 0;
}

void CConfigDialog::OnReleasedcaptureSliderBlinkFadeLength(NMHDR* pNMHDR, LRESULT* pResult) 
{
	this->m_refConfig.m_FrameLength = this->m_SliderBlinkFrameLength.GetPos();
	this->m_strFrameLength.Format( "%d", this->m_refConfig.m_FrameLength );
	UpdateData( FALSE );
	*pResult = 0;
}

void CConfigDialog::OnReleasedcaptureSliderBlinkCount(NMHDR* pNMHDR, LRESULT* pResult) 
{
	this->m_refConfig.m_BlinkCount = this->m_SliderBlinkCount.GetPos();
	this->m_strBlinkCount.Format( "%d", this->m_refConfig.m_BlinkCount );
	UpdateData( FALSE );
	*pResult = 0;
}

