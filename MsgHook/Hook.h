// MouseHook.h: CMouseHook クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#undef AFX_DATA
#define AFX_DATA AFX_EXT_DATA

#if !defined(AFX_MOUSEHOOK_H__2C94E5A0_49BF_422E_B30B_E60BD311CD06__INCLUDED_)
#define AFX_MOUSEHOOK_H__2C94E5A0_49BF_422E_B30B_E60BD311CD06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// WM_APP(0x8000) ～ 0xBFFF
#define WM_APP_HCBT_SETFOCUS	(WM_APP + 0x0001)
#define WM_APP_HCBT_MOVESIZE	(WM_APP + 0x0002)
#define WM_APP_HKEYBOARD		(WM_APP + 0x0003)

class AFX_EXT_CLASS CHook  
{
public:
	BOOL Set( HWND i_hWndDestination );
	BOOL Release( void );
	BOOL Pause( BOOL boPause );
	CHook();
	virtual ~CHook();
private:
	static LRESULT CALLBACK CBTProc( int nCode, WPARAM wParam, LPARAM lParam );
	static LRESULT CALLBACK KeyboardProc( int nCode, WPARAM wParam, LPARAM lParam );

	static HHOOK s_hCBTHook;
	static HHOOK s_hKeyboardHook;
	static HWND	s_hWndDestination;
	static BOOL s_boPause;
};

#endif // !defined(AFX_MOUSEHOOK_H__2C94E5A0_49BF_422E_B30B_E60BD311CD06__INCLUDED_)

#undef AFX_DATA
#define AFX_DATA