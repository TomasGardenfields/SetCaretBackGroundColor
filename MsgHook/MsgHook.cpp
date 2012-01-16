// MsgHook.cpp : DLL 用の初期化処理の定義を行います。
//

#include "stdafx.h"
#include <afxdllx.h>

#include "defs.h"
#include "MsgHook.h"
#include "Hook.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static HINSTANCE g_hDllInst = NULL;

HINSTANCE GetThisHInst()
{
	return g_hDllInst;
}

static AFX_EXTENSION_MODULE MsgHookDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	g_hDllInst = hInstance;

	// lpReserved を使う場合はここを削除してください
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("MSGHOOK.DLL Initializing!\n");
		
		// 拡張 DLL を１回だけ初期化します。
		if (!AfxInitExtensionModule(MsgHookDLL, hInstance))
			return 0;

		// この DLL をリソース チェインへ挿入します。
		// メモ: 拡張 DLL が MFC アプリケーションではなく
		//   MFC 標準 DLL (ActiveX コントロールのような)
		//   に暗黙的にリンクされる場合、この行を DllMain
		//   から削除して、この拡張 DLL からエクスポート
		//   された別の関数内へ追加してください。  
		//   この拡張 DLL を使用する標準 DLL はこの拡張 DLL
		//   を初期化するために明示的にその関数を呼び出します。 
		//   それ以外の場合は、CDynLinkLibrary オブジェクトは
		//   標準 DLL のリソース チェインへアタッチされず、
		//   その結果重大な問題となります。

		new CDynLinkLibrary(MsgHookDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("MSGHOOK.DLL Terminating!\n");
		// デストラクタが呼び出される前にライブラリを終了します
		AfxTermExtensionModule(MsgHookDLL);
	}
	return 1;   // ok
}
