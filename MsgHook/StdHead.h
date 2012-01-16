#ifndef __STDHEAD_H__
#define __STDHEAD_H__

// ライブラリファイルを読み込みます。
//#pragma comment(lib, "Test.lib")
#ifdef _DEBUG
	#pragma comment(lib, "../MsgHook/Debug/MsgHook.lib")
#else
	#pragma comment(lib, "../MsgHook/Release/MsgHook.lib")
#endif

//　ヘッダーファイルを読み込みます。
#include "Defs.h"	//マクロ用ファイル。
#include "Hook.h"	//関数のプロトタイプ宣言が入ったファイル。

#endif	//__STDHEAD_H__