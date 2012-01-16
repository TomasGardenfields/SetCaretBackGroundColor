// MouseHook.cpp: CMouseHook �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Defs.h"
#include "Hook.h"
#include "MsgHook.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

#pragma data_seg( ".CHookData" )
	HHOOK	CHook::s_hCBTHook = NULL;
	HHOOK	CHook::s_hKeyboardHook = NULL;
	HWND	CHook::s_hWndDestination = NULL;
#pragma data_seg()
BOOL	CHook::s_boPause = FALSE;

CHook::CHook()
{
	s_boPause = FALSE;
}

CHook::~CHook()
{
	this->Release();
}

BOOL CHook::Set( HWND i_hWndDestination )
{
	s_hCBTHook = ::SetWindowsHookEx(
		WH_CBT,
		(HOOKPROC)CHook::CBTProc,
		GetThisHInst(),
		0 );

	if( !s_hCBTHook )
	{
		TRACE1( "SetWindowsHookEx(WH_CBT) Fail hWnd : %08X\n", (DWORD)i_hWndDestination );
		return FALSE;
	}

	s_hKeyboardHook = ::SetWindowsHookEx(
		WH_KEYBOARD,
		(HOOKPROC)CHook::KeyboardProc,
		GetThisHInst(),
		0 );

	if( !s_hKeyboardHook )
	{
		TRACE1( "SetWindowsHookEx(WH_KEYBOARD) Fail hWnd : %08X\n", (DWORD)i_hWndDestination );
		return FALSE;
	}

	TRACE1( "SetWindowsHookEx Success hWnd : %08X\n", (DWORD)i_hWndDestination );
	this->s_hWndDestination = i_hWndDestination;

	return TRUE;
}

BOOL CHook::Release()
{
	BOOL bRes = 0;
	this->s_hWndDestination = NULL;

	if( s_hKeyboardHook )
	{
		bRes = ::UnhookWindowsHookEx( s_hKeyboardHook );
		s_hKeyboardHook = NULL;
		TRACE1( "UnhookWindowsHookEx result: %08X\n", bRes );
	}

	if( s_hCBTHook )
	{
		bRes = ::UnhookWindowsHookEx( s_hCBTHook );
		s_hCBTHook = NULL;
		TRACE1( "UnhookWindowsHookEx result: %08X\n", bRes );
	}

	TRACE1( "CHook::Release() End return: %08X\n", bRes );
	return bRes;
}

BOOL CHook::Pause( BOOL boPause )
{
	CHook::s_boPause = boPause;
	return CHook::s_boPause;
}

/* ////////////////////////////////////////////////////// */
// �E�B���h�E�̃A�N�e�B�u���A�쐬�A�j���A�ŏ����A�ő剻�A�ړ��A�T�C�Y�ύX�̂����ꂩ���s���O�A
// �V�X�e���R�}���h����������O�A�V�X�e�����b�Z�[�W�L���[����}�E�X�C�x���g��L�[�{�[�h�C�x���g���폜����O�A
// �L�[�{�[�h�t�H�[�J�X��ݒ肷��O�A�܂��̓V�X�e�����b�Z�[�W�L���[�𓯊�������O�ɁA���̊֐����Ăяo���܂��B
LRESULT CALLBACK CHook::CBTProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	long result;
//	TRACE0( "CHook::CBTProc begin\n" );

	if( nCode < 0  || nCode == HC_NOREMOVE )
	{
		TRACE0( "CHook::CBTProc nCode < 0  || nCode == HC_NOREMOVE \n" );
		return ::CallNextHookEx( s_hCBTHook, nCode, wParam, lParam );
	}

	// �|�[�Y���łȂ��ꍇ�̂݃��b�Z�[�W�������s��
	if ( s_boPause == FALSE )
	{
		switch ( nCode )
		{
			// 1 �̃E�B���h�E���L�[�{�[�h�t�H�[�J�X���󂯎�낤�Ƃ��Ă��܂�
		case HCBT_SETFOCUS:
			TRACE3( "HCBT_SETFOCUS : To %08X : %08X / %08X\n", s_hWndDestination, wParam, lParam );
//			HWND hWndCurrent = (HWND)wParam;	// �L�[�{�[�h�t�H�[�J�X���󂯎��E�B���h�E�̃n���h�����w�肵�܂�
//			HWND hWndPrevious = (HWND)lParam;	// �L�[�{�[�h�t�H�[�J�X�������E�B���h�E�̃n���h�����w�肵�܂�
			PostMessage( s_hWndDestination, WM_APP_HCBT_SETFOCUS, wParam, lParam );
			break;

			// 1 �̃E�B���h�E�̈ړ��܂��̓T�C�Y�ύX���s���悤�Ƃ��Ă��܂�
		case HCBT_MOVESIZE:
			TRACE3( "HCBT_MOVESIZE : To %08X : %08X / %08X\n", s_hWndDestination, wParam, lParam );
//			HWND hWndMoveSize = (HWND)wParam;	// �ړ��܂��̓T�C�Y�ύX���悤�Ƃ��Ă���E�B���h�E�̃n���h�����w�肵�܂�
//			RECT *rect = (RECT*)lParam;			// �E�B���h�E�̍��W��ێ����Ă��� 1 �� �\���̂ւ̃����O�|�C���^���w�肵�܂�
//												// CBTProc �t�b�N�v���V�[�W���́A���̍\���̓��̒l��ύX���邱�Ƃɂ��
//												// �E�B���h�E�̍ŏI�I�ȍ��W��ݒ�ł��܂�
			PostMessage( s_hWndDestination, WM_APP_HCBT_MOVESIZE, wParam, lParam );
			break;
		default:
			break;
		}
	}

	// ���̃t�b�N�֏�����n��
	result = ::CallNextHookEx( s_hCBTHook, nCode, wParam, lParam );
//	TRACE1( "CHook::CBTProc return: %08X\n", result );
	return result;
}

/* ////////////////////////////////////////////////////// */
// �L�[�{�[�h���b�Z�[�W����������ꍇ�A�V�X�e���͕K�����̃t�b�N�v���V�[�W�����Ăяo���܂��B
LRESULT CALLBACK CHook::KeyboardProc( int nCode, WPARAM wParam, LPARAM lParam )
{
	long result;
	TRACE0( "CHook::KeyboardProc begin\n" );

	if( nCode < 0  || nCode == HC_NOREMOVE )
	{
		TRACE0( "CHook::KeyboardProc nCode < 0  || nCode == HC_NOREMOVE \n" );
		return ::CallNextHookEx( s_hKeyboardHook, nCode, wParam, lParam );
	}

	// �|�[�Y���łȂ��ꍇ�̂݃��b�Z�[�W�������s��
	if ( s_boPause == FALSE )
	{
		if ( nCode == HC_ACTION )
		{
			PostMessage( s_hWndDestination, WM_APP_HKEYBOARD, wParam, lParam );
		}
	}

	// ���̃t�b�N�֏�����n��
	result = ::CallNextHookEx( s_hKeyboardHook, nCode, wParam, lParam );
	TRACE1( "CHook::KeyboardProc return: %08X\n", result );
	return result;
}
