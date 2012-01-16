// MouseHook.cpp: CMouseHook クラスのインプリメンテーション
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
// 構築/消滅
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
// ウィンドウのアクティブ化、作成、破棄、最小化、最大化、移動、サイズ変更のいずれかを行う前、
// システムコマンドを完了する前、システムメッセージキューからマウスイベントやキーボードイベントを削除する前、
// キーボードフォーカスを設定する前、またはシステムメッセージキューを同期させる前に、この関数を呼び出します。
LRESULT CALLBACK CHook::CBTProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	long result;
//	TRACE0( "CHook::CBTProc begin\n" );

	if( nCode < 0  || nCode == HC_NOREMOVE )
	{
		TRACE0( "CHook::CBTProc nCode < 0  || nCode == HC_NOREMOVE \n" );
		return ::CallNextHookEx( s_hCBTHook, nCode, wParam, lParam );
	}

	// ポーズ中でない場合のみメッセージ処理を行う
	if ( s_boPause == FALSE )
	{
		switch ( nCode )
		{
			// 1 個のウィンドウがキーボードフォーカスを受け取ろうとしています
		case HCBT_SETFOCUS:
			TRACE3( "HCBT_SETFOCUS : To %08X : %08X / %08X\n", s_hWndDestination, wParam, lParam );
//			HWND hWndCurrent = (HWND)wParam;	// キーボードフォーカスを受け取るウィンドウのハンドルを指定します
//			HWND hWndPrevious = (HWND)lParam;	// キーボードフォーカスを失うウィンドウのハンドルを指定します
			PostMessage( s_hWndDestination, WM_APP_HCBT_SETFOCUS, wParam, lParam );
			break;

			// 1 個のウィンドウの移動またはサイズ変更が行われようとしています
		case HCBT_MOVESIZE:
			TRACE3( "HCBT_MOVESIZE : To %08X : %08X / %08X\n", s_hWndDestination, wParam, lParam );
//			HWND hWndMoveSize = (HWND)wParam;	// 移動またはサイズ変更しようとしているウィンドウのハンドルを指定します
//			RECT *rect = (RECT*)lParam;			// ウィンドウの座標を保持している 1 個の 構造体へのロングポインタを指定します
//												// CBTProc フックプロシージャは、この構造体内の値を変更することにより
//												// ウィンドウの最終的な座標を設定できます
			PostMessage( s_hWndDestination, WM_APP_HCBT_MOVESIZE, wParam, lParam );
			break;
		default:
			break;
		}
	}

	// 次のフックへ処理を渡す
	result = ::CallNextHookEx( s_hCBTHook, nCode, wParam, lParam );
//	TRACE1( "CHook::CBTProc return: %08X\n", result );
	return result;
}

/* ////////////////////////////////////////////////////// */
// キーボードメッセージを処理する場合、システムは必ずこのフックプロシージャを呼び出します。
LRESULT CALLBACK CHook::KeyboardProc( int nCode, WPARAM wParam, LPARAM lParam )
{
	long result;
	TRACE0( "CHook::KeyboardProc begin\n" );

	if( nCode < 0  || nCode == HC_NOREMOVE )
	{
		TRACE0( "CHook::KeyboardProc nCode < 0  || nCode == HC_NOREMOVE \n" );
		return ::CallNextHookEx( s_hKeyboardHook, nCode, wParam, lParam );
	}

	// ポーズ中でない場合のみメッセージ処理を行う
	if ( s_boPause == FALSE )
	{
		if ( nCode == HC_ACTION )
		{
			PostMessage( s_hWndDestination, WM_APP_HKEYBOARD, wParam, lParam );
		}
	}

	// 次のフックへ処理を渡す
	result = ::CallNextHookEx( s_hKeyboardHook, nCode, wParam, lParam );
	TRACE1( "CHook::KeyboardProc return: %08X\n", result );
	return result;
}
