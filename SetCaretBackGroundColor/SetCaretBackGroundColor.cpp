// SetCaretBackGroundColor.cpp : アプリケーション用クラスの定義を行います。
//

#ifdef _DEBUG
	#pragma comment( lib, "..\\MsgHook\\Debug\\MsgHook.lib")
#else
	#pragma comment( lib, "..\\MsgHook\\Release\\MsgHook.lib")
#endif

#include "stdafx.h"
#include "SetCaretBackGroundColor.h"
#include "SetCaretBackGroundColorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DEF_DEFAULT_CLASS_NAME "#32770"
#define DEF_CLASS_NAME "SetCaretbackGroundColor_class"
CSetCaretBackGroundColorDlg* g_pMainDlg;

/////////////////////////////////////////////////////////////////////////////
// CSetCaretBackGroundColorApp

BEGIN_MESSAGE_MAP(CSetCaretBackGroundColorApp, CWinApp)
	//{{AFX_MSG_MAP(CSetCaretBackGroundColorApp)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetCaretBackGroundColorApp クラスの構築

CSetCaretBackGroundColorApp::CSetCaretBackGroundColorApp()
{
	// TODO: この位置に構築用のコードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。

	/* ------------------------------------------------------ */
	g_pMainDlg = NULL;

	this->m_hEvent = NULL;

	// 元のm_pszProfileNameを保存
	this->m_pProfileName = NULL;
	this->m_pszProfileName_bk = this->m_pszProfileName;
}


CSetCaretBackGroundColorApp::~CSetCaretBackGroundColorApp()
{
	/* ------------------------------------------------------ */
	// 保存しておいたm_pszProfileNameを元に戻す＆作成した領域開放
	this->m_pszProfileName = this->m_pszProfileName_bk;
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CSetCaretBackGroundColorApp オブジェクト

CSetCaretBackGroundColorApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSetCaretBackGroundColorApp クラスの初期化

BOOL CSetCaretBackGroundColorApp::InitInstance()
{
	/* ------------------------------------------------------ */
	// クラス名の設定
	WNDCLASS wc;

	// クラス情報を取得する
	// ※#32770はダイアログクラスのデフォルトのクラス名
	::GetClassInfo(AfxGetInstanceHandle(), DEF_DEFAULT_CLASS_NAME, &wc);

	// クラス名を変更する
	wc.lpszClassName = DEF_CLASS_NAME;

	// MFCが利用できるよう、クラスを登録する
	AfxRegisterClass(&wc);	

	/* ------------------------------------------------------ */	
	// コマンドラインオプションのチェック
	DWORD dwOppositeProcessID = 0;
	StCommandLineOption a_CommandLineOption;
	{
		a_CommandLineOption.m_Restart = FALSE;
	}
	int i;
	for ( i = 1 ; i < __argc ; i++ )
	{
		TRACE2( "Cmd : %02d : %s\n", __argc, __argv[i] );
		// リスタートフラグ(＆プロセスID値)チェック
		if ( ( strncmp( __argv[i], "/restart", 255 ) == 0 ) && ( i + 1 < __argc ) )
		{
			a_CommandLineOption.m_Restart = TRUE;
			dwOppositeProcessID = (DWORD)strtoul( __argv[i+1], NULL, 16 ); 
		}
	}

	/* ------------------------------------------------------ */
	// 通知用イベント作成
	this->m_hEvent = CreateEvent( NULL, FALSE, FALSE, this->m_pszAppName );
	DWORD dwError = GetLastError();
	if ( dwError == ERROR_ALREADY_EXISTS )
	{
		// イベント作成済み(=二重起動時)の場合はイベントをシグナル状態にし、既存アプリケーションを終了させる
		SetEvent( this->m_hEvent );

		// 再起動フラグがONの場合は既存アプリケーションの終了を待って起動
		// OFFの場合はなにもせず終了
		if ( a_CommandLineOption.m_Restart )
		{
			HANDLE hOppositeProcess = ::OpenProcess( SYNCHRONIZE, FALSE, dwOppositeProcessID );
			if ( hOppositeProcess != NULL )
			{
				// 10秒待っても終了しなければこちらも終了
				DWORD dwWaitResult = WaitForSingleObject( hOppositeProcess, 1000 * 10 );
				if ( dwWaitResult == WAIT_TIMEOUT )
				{
					return FALSE;			
				}
			}
		}
		else
		{
			return FALSE;
		}
	}

	/* ------------------------------------------------------ */
	//既存のiniファイル名(ファイル名のみ.ini)を、exeファイルのディレクトリと同じパス(絶対パス.ini)にする
	CString		str;
	GetModulePathFileName( this->m_pszProfileName, str );
	
	this->m_pProfileName=new TCHAR[str.GetLength()+1];	// 取得したパスの型変換(CString→TCHAR*)
	strcpy( this->m_pProfileName, str );
	this->m_pszProfileName	= this->m_pProfileName;

	/* ------------------------------------------------------ */

	ReadIniFile();

	g_pMainDlg = new CSetCaretBackGroundColorDlg( this->m_Config );
	if ( !g_pMainDlg )
	{
		// 生成失敗した場合は終了
		return FALSE;
	}

	this->m_pMainWnd = g_pMainDlg;
	g_pMainDlg->Create( IDD_SETCARETBACKGROUNDCOLOR_DIALOG, NULL );

	return TRUE;
}

int CSetCaretBackGroundColorApp::ExitInstance() 
{
	
	if ( g_pMainDlg )
	{
		WriteIniFile();

		g_pMainDlg->ShowWindow( SW_HIDE );
		g_pMainDlg->DestroyWindow();
		delete g_pMainDlg;
		g_pMainDlg = NULL;
	}

	delete[] m_pProfileName;

	if ( this->m_hEvent )
	{
		CloseHandle( this->m_hEvent );
		this->m_hEvent = NULL;
	}
	
	return CWinApp::ExitInstance();
}

/* ****************************************************** */
// アプリケーションメインループ
int CSetCaretBackGroundColorApp::Run() 
{
	MSG a_Msg;

	while( true )
	{
		// ウィンドウメッセージ処理
		BOOL retPeekMsg = PeekMessage( &a_Msg, NULL, 0, 0, PM_NOREMOVE );
		if ( retPeekMsg != 0 )
		{
			BOOL retGetMsg = GetMessage( &a_Msg, NULL, 0, 0 );
			if ( !retGetMsg )
			{
				return a_Msg.wParam ;
			}
			if( a_Msg.message == WM_QUIT )
			{
				break;
			}

			TranslateMessage( &a_Msg );
			DispatchMessage( &a_Msg );
		}
		else
		{
			// メインウィンドウが閉じたらループを抜ける
			if( !g_pMainDlg->IsExisted() )
			{
				break;
			}

			// シグナル状態になったらループを抜ける
			DWORD dwWaitResult = WaitForSingleObject( this->m_hEvent, 0 );
			if ( dwWaitResult == WAIT_OBJECT_0 )
			{
				break;
			}

			Sleep( 1 );
		}		
	}

	this->ExitInstance();
	return 0;
}

BOOL CSetCaretBackGroundColorApp::GetModulePathFileName(LPCTSTR i_pName, CString &o_pStrPath)
{
	//exeファイルのフルパスを取得
	TCHAR path[_MAX_PATH];
	::GetModuleFileName( NULL, path, sizeof(path) );

	//exeファイルのパスを分解
	TCHAR drive[_MAX_DRIVE];
	TCHAR dir[_MAX_DIR];
	TCHAR fname[_MAX_FNAME];
	TCHAR ext[_MAX_EXT];
	_splitpath( path, drive, dir, fname, ext );

	//引数のファイル名をexeファイルのパスでフルパス化
	_makepath( path, drive, dir, i_pName, "");

	o_pStrPath = path ;
	return TRUE;

}

// コンフィグデータの読み出し
BOOL CSetCaretBackGroundColorApp::ReadIniFile()
{
	CWinApp* theApp = ::AfxGetApp();
	BYTE a, r, g, b;
	
	a = ( theApp->GetProfileInt( "Open", "a", 128 ) & 0xFF );
	r = ( theApp->GetProfileInt( "Open", "r", 128 ) & 0xFF );
	g = ( theApp->GetProfileInt( "Open", "g", 128 ) & 0xFF );
	b = ( theApp->GetProfileInt( "Open", "b", 128 ) & 0xFF );
	this->m_Config.m_BackGroundColorOpen = RGB( r, g, b );
	this->m_Config.m_TransparencyOpen = a;

	a = ( theApp->GetProfileInt( "Close", "a", 128 ) & 0xFF );
	r = ( theApp->GetProfileInt( "Close", "r", 128 ) & 0xFF );
	g = ( theApp->GetProfileInt( "Close", "g", 128 ) & 0xFF );
	b = ( theApp->GetProfileInt( "Close", "b", 128 ) & 0xFF );
	this->m_Config.m_BackGroundColorClose = RGB( r, g, b );
	this->m_Config.m_TransparencyClose = a;

	this->m_Config.m_FrameLength = ( theApp->GetProfileInt( "General", "FrameLength", 10 ) );
	this->m_Config.m_BlinkCount = ( theApp->GetProfileInt( "General", "BlinkCount", 1 ) );

	// 無視クラス名リストファイル
	CString strIgnoreClassNameList;
	strIgnoreClassNameList = theApp->GetProfileString( "Ignore", "ClassNameList", "IgnoreClassNameList.txt" );

	CString		strPath;
	GetModulePathFileName( strIgnoreClassNameList, strPath );

	CStdioFile a_IgnoreClassNameListFile;
	BOOL boResult = a_IgnoreClassNameListFile.Open( strPath, CFile::modeRead | CFile::shareDenyNone | CFile::typeText, NULL );
	if ( boResult )
	{
		CString strLine;
		BOOL boReadResult;

		while( NULL != ( boReadResult = a_IgnoreClassNameListFile.ReadString( strLine ) ) )
		{
			// 空白の項目を無視する
			if ( strLine == "" )
			{
				continue;
			}
			this->m_Config.m_IgnoreClassName.Add( strLine );
		}
		
		a_IgnoreClassNameListFile.Close();
	}

	return TRUE;
}

BOOL CSetCaretBackGroundColorApp::WriteIniFile()
{
	CWinApp* theApp = ::AfxGetApp();
	BYTE a, r, g, b;

	a = (BYTE)( this->m_Config.m_TransparencyOpen );
	r = GetRValue( this->m_Config.m_BackGroundColorOpen );
	g = GetGValue( this->m_Config.m_BackGroundColorOpen );
	b = GetBValue( this->m_Config.m_BackGroundColorOpen );
	theApp->WriteProfileInt( "Open", "a", a );
	theApp->WriteProfileInt( "Open", "r", r );
	theApp->WriteProfileInt( "Open", "g", g );
	theApp->WriteProfileInt( "Open", "b", b );

	a = (BYTE)( this->m_Config.m_TransparencyClose );
	r = GetRValue( this->m_Config.m_BackGroundColorClose );
	g = GetGValue( this->m_Config.m_BackGroundColorClose );
	b = GetBValue( this->m_Config.m_BackGroundColorClose );
	theApp->WriteProfileInt( "Close", "a", a );
	theApp->WriteProfileInt( "Close", "r", r );
	theApp->WriteProfileInt( "Close", "g", g );
	theApp->WriteProfileInt( "Close", "b", b );
	
	theApp->WriteProfileInt( "General", "FrameLength", this->m_Config.m_FrameLength );
	theApp->WriteProfileInt( "General", "BlinkCount", this->m_Config.m_BlinkCount );

	// 無視クラス名リストファイル
	CString strIgnoreClassNameList;
	strIgnoreClassNameList = theApp->GetProfileString( "Ignore", "ClassNameList", "IgnoreClassNameList.txt" );

	CString		strPath;
	GetModulePathFileName( strIgnoreClassNameList, strPath );

	CStdioFile a_IgnoreClassNameListFile;
	BOOL boResult = a_IgnoreClassNameListFile.Open( strPath, CFile::modeWrite | CFile::modeCreate | CFile::shareDenyNone | CFile::typeText, NULL );
	if ( boResult )
	{
		int iCount = this->m_Config.m_IgnoreClassName.GetSize();
		for ( int i = 0 ; i < iCount ; i++ )
		{
			CString strClassName = this->m_Config.m_IgnoreClassName.GetAt( i ) + "\n";

			// 空白の項目を無視する
			if ( strClassName == "\n" )
			{
				continue;
			}
			a_IgnoreClassNameListFile.WriteString( strClassName );
		}

		a_IgnoreClassNameListFile.Close();
	}
	

	return TRUE;
}
