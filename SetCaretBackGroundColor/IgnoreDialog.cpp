// IgnoreDialog.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "SetCaretBackGroundColor.h"
#include "IgnoreDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DEF_LIST_CLASSNAME_HISTORY_MAX 256

/////////////////////////////////////////////////////////////////////////////
// CIgnoreDialog ダイアログ


CIgnoreDialog::CIgnoreDialog( StConfig& i_refConfig, CWnd* pParent /*=NULL*/)
	: CDialog(CIgnoreDialog::IDD, pParent), m_refConfig( i_refConfig )
{
	//{{AFX_DATA_INIT(CIgnoreDialog)
	m_strIgnoreClassName = _T("");
	//}}AFX_DATA_INIT

	this->Create( IDD, pParent );
}

CIgnoreDialog::~CIgnoreDialog()
{
	this->DestroyWindow();
	CDialog::~CDialog();
}

void CIgnoreDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIgnoreDialog)
	DDX_Control(pDX, IDC_LIST_IGNORE_CLASSNAME_HISTORY, m_listboxIgnoreClassNameHistory);
	DDX_Control(pDX, IDC_BUTTON_CLASSNAME_REMOVE, m_btnClassnameRemove);
	DDX_Control(pDX, IDC_BUTTON_CLASSNAME_ADD, m_btnClassnameAdd);
	DDX_Control(pDX, IDC_LIST_IGNORE_CLASSNAME, m_listboxIgnoreClassName);
	DDX_Text(pDX, IDC_EDIT_IGNORE_CLASSNAME, m_strIgnoreClassName);
	//}}AFX_DATA_MAP

	BOOL boAdd = ( "" != this->m_strIgnoreClassName );
	this->m_btnClassnameAdd.EnableWindow( boAdd );

	BOOL boRemove = ( LB_ERR != this->m_listboxIgnoreClassName.GetCurSel() );
	this->m_btnClassnameRemove.EnableWindow( boRemove );
}


BEGIN_MESSAGE_MAP(CIgnoreDialog, CDialog)
	//{{AFX_MSG_MAP(CIgnoreDialog)
	ON_LBN_SELCHANGE(IDC_LIST_IGNORE_CLASSNAME_HISTORY, OnSelchangeListIgnoreClassnameHistory)
	ON_BN_CLICKED(IDC_BUTTON_IGNORE_CLOSE, OnButtonIgnoreClose)
	ON_BN_CLICKED(IDC_BUTTON_CLASSNAME_ADD, OnButtonClassnameAdd)
	ON_BN_CLICKED(IDC_BUTTON_CLASSNAME_REMOVE, OnButtonClassnameRemove)
	ON_LBN_SELCHANGE(IDC_LIST_IGNORE_CLASSNAME, OnSelchangeListIgnoreClassname)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIgnoreDialog メッセージ ハンドラ

BOOL CIgnoreDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください

	this->UpdateData( TRUE );

	this->m_listboxIgnoreClassName.ResetContent();

	for ( int i = 0 ; i < this->m_refConfig.m_IgnoreClassName.GetSize() ; i++ )
	{
		this->m_listboxIgnoreClassName.AddString( this->m_refConfig.m_IgnoreClassName.GetAt( i ) );
	}

	this->m_strIgnoreClassName = "";

	this->UpdateData( FALSE );
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CIgnoreDialog::PostNcDestroy() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	delete this;
	CDialog::PostNcDestroy();
}

void CIgnoreDialog::OnOK() 
{
	//CDialog::OnOK();
	this->ShowWindow( SW_HIDE );
}

void CIgnoreDialog::OnCancel() 
{
	//CDialog::OnCancel();
	this->ShowWindow( SW_HIDE );
}

void CIgnoreDialog::OnButtonIgnoreClose() 
{
	this->ShowWindow( SW_HIDE );
}

void CIgnoreDialog::OnSelchangeListIgnoreClassname() 
{
	this->UpdateData( TRUE );
	this->UpdateData( FALSE );
}

void CIgnoreDialog::OnButtonClassnameAdd() 
{
	// 追加済みクラス名が指定された場合は何もしない
	if ( LB_ERR != this->m_listboxIgnoreClassName.FindString( 0, this->m_strIgnoreClassName ) )
	{
		return;
	}
	// リスト/コンフィグへクラス名を追加
	this->m_listboxIgnoreClassName.AddString( this->m_strIgnoreClassName );
	this->m_refConfig.m_IgnoreClassName.Add( this->m_strIgnoreClassName );
}

void CIgnoreDialog::OnButtonClassnameRemove() 
{
	// 選択した項目をリスト/コンフィグから削除

	int iListIndex;
	int iArrayIndex;
	CString strClassName;

	iListIndex = this->m_listboxIgnoreClassName.GetCurSel();
	this->m_listboxIgnoreClassName.GetText( iListIndex, strClassName );
	iArrayIndex = this->m_refConfig.FindClassName( strClassName );

	this->m_listboxIgnoreClassName.DeleteString( iListIndex );
	this->m_refConfig.m_IgnoreClassName.RemoveAt( iArrayIndex, 1 );
}

void CIgnoreDialog::OnSelchangeListIgnoreClassnameHistory() 
{
	// ヒストリから選択した項目をエディットボックスへ反映する
	this->UpdateData( TRUE );

	int iListIndex = this->m_listboxIgnoreClassNameHistory.GetCurSel();
	if ( iListIndex != LB_ERR )
	{
		this->m_listboxIgnoreClassNameHistory.GetText( iListIndex, this->m_strIgnoreClassName );
	}

	this->UpdateData( FALSE );
}

BOOL CIgnoreDialog::AddHistory( HWND i_hWnd )
{
	this->UpdateData( TRUE );

	// リストの先頭にクラス名を追加
	CString strClassName;
	::GetClassName( i_hWnd, strClassName.GetBuffer( 256 ), 256 );
	strClassName.ReleaseBuffer();

	this->m_listboxIgnoreClassNameHistory.InsertString( 0, strClassName );
//	this->m_refConfig.m_IgnoreClassName.Add( strClassName );

	// 項目数が最大値に達したら下から順に削除する
	int iCount = this->m_listboxIgnoreClassNameHistory.GetCount();
	if ( DEF_LIST_CLASSNAME_HISTORY_MAX < iCount )
	{
		for ( int i = iCount-1 ; DEF_LIST_CLASSNAME_HISTORY_MAX <= i ; i-- )
		{
			this->m_listboxIgnoreClassNameHistory.DeleteString( i );
		}
	}

	this->UpdateData( FALSE );

	return TRUE;
}


