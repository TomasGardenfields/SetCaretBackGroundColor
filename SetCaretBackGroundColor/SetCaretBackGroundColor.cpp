// SetCaretBackGroundColor.cpp : �A�v���P�[�V�����p�N���X�̒�`���s���܂��B
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
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetCaretBackGroundColorApp �N���X�̍\�z

CSetCaretBackGroundColorApp::CSetCaretBackGroundColorApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�̃R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B

	/* ------------------------------------------------------ */
	g_pMainDlg = NULL;

	this->m_hEvent = NULL;

	// ����m_pszProfileName��ۑ�
	this->m_pProfileName = NULL;
	this->m_pszProfileName_bk = this->m_pszProfileName;
}


CSetCaretBackGroundColorApp::~CSetCaretBackGroundColorApp()
{
	/* ------------------------------------------------------ */
	// �ۑ����Ă�����m_pszProfileName�����ɖ߂����쐬�����̈�J��
	this->m_pszProfileName = this->m_pszProfileName_bk;
}

/////////////////////////////////////////////////////////////////////////////
// �B��� CSetCaretBackGroundColorApp �I�u�W�F�N�g

CSetCaretBackGroundColorApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSetCaretBackGroundColorApp �N���X�̏�����

BOOL CSetCaretBackGroundColorApp::InitInstance()
{
	/* ------------------------------------------------------ */
	// �N���X���̐ݒ�
	WNDCLASS wc;

	// �N���X�����擾����
	// ��#32770�̓_�C�A���O�N���X�̃f�t�H���g�̃N���X��
	::GetClassInfo(AfxGetInstanceHandle(), DEF_DEFAULT_CLASS_NAME, &wc);

	// �N���X����ύX����
	wc.lpszClassName = DEF_CLASS_NAME;

	// MFC�����p�ł���悤�A�N���X��o�^����
	AfxRegisterClass(&wc);	

	/* ------------------------------------------------------ */	
	// �R�}���h���C���I�v�V�����̃`�F�b�N
	DWORD dwOppositeProcessID = 0;
	StCommandLineOption a_CommandLineOption;
	{
		a_CommandLineOption.m_Restart = FALSE;
	}
	int i;
	for ( i = 1 ; i < __argc ; i++ )
	{
		TRACE2( "Cmd : %02d : %s\n", __argc, __argv[i] );
		// ���X�^�[�g�t���O(���v���Z�XID�l)�`�F�b�N
		if ( ( strncmp( __argv[i], "/restart", 255 ) == 0 ) && ( i + 1 < __argc ) )
		{
			a_CommandLineOption.m_Restart = TRUE;
			dwOppositeProcessID = (DWORD)strtoul( __argv[i+1], NULL, 16 ); 
		}
	}

	/* ------------------------------------------------------ */
	// �ʒm�p�C�x���g�쐬
	this->m_hEvent = CreateEvent( NULL, FALSE, FALSE, this->m_pszAppName );
	DWORD dwError = GetLastError();
	if ( dwError == ERROR_ALREADY_EXISTS )
	{
		// �C�x���g�쐬�ς�(=��d�N����)�̏ꍇ�̓C�x���g���V�O�i����Ԃɂ��A�����A�v���P�[�V�������I��������
		SetEvent( this->m_hEvent );

		// �ċN���t���O��ON�̏ꍇ�͊����A�v���P�[�V�����̏I����҂��ċN��
		// OFF�̏ꍇ�͂Ȃɂ������I��
		if ( a_CommandLineOption.m_Restart )
		{
			HANDLE hOppositeProcess = ::OpenProcess( SYNCHRONIZE, FALSE, dwOppositeProcessID );
			if ( hOppositeProcess != NULL )
			{
				// 10�b�҂��Ă��I�����Ȃ���΂�������I��
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
	//������ini�t�@�C����(�t�@�C�����̂�.ini)���Aexe�t�@�C���̃f�B���N�g���Ɠ����p�X(��΃p�X.ini)�ɂ���
	CString		str;
	GetModulePathFileName( this->m_pszProfileName, str );
	
	this->m_pProfileName=new TCHAR[str.GetLength()+1];	// �擾�����p�X�̌^�ϊ�(CString��TCHAR*)
	strcpy( this->m_pProfileName, str );
	this->m_pszProfileName	= this->m_pProfileName;

	/* ------------------------------------------------------ */

	ReadIniFile();

	g_pMainDlg = new CSetCaretBackGroundColorDlg( this->m_Config );
	if ( !g_pMainDlg )
	{
		// �������s�����ꍇ�͏I��
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
// �A�v���P�[�V�������C�����[�v
int CSetCaretBackGroundColorApp::Run() 
{
	MSG a_Msg;

	while( true )
	{
		// �E�B���h�E���b�Z�[�W����
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
			// ���C���E�B���h�E�������烋�[�v�𔲂���
			if( !g_pMainDlg->IsExisted() )
			{
				break;
			}

			// �V�O�i����ԂɂȂ����烋�[�v�𔲂���
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
	//exe�t�@�C���̃t���p�X���擾
	TCHAR path[_MAX_PATH];
	::GetModuleFileName( NULL, path, sizeof(path) );

	//exe�t�@�C���̃p�X�𕪉�
	TCHAR drive[_MAX_DRIVE];
	TCHAR dir[_MAX_DIR];
	TCHAR fname[_MAX_FNAME];
	TCHAR ext[_MAX_EXT];
	_splitpath( path, drive, dir, fname, ext );

	//�����̃t�@�C������exe�t�@�C���̃p�X�Ńt���p�X��
	_makepath( path, drive, dir, i_pName, "");

	o_pStrPath = path ;
	return TRUE;

}

// �R���t�B�O�f�[�^�̓ǂݏo��
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

	// �����N���X�����X�g�t�@�C��
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
			// �󔒂̍��ڂ𖳎�����
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

	// �����N���X�����X�g�t�@�C��
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

			// �󔒂̍��ڂ𖳎�����
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
