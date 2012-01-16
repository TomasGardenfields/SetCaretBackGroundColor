
#pragma once
#include <afxcoll.h>

#define WM_APP_UPDATECOLOR	(WM_APP + 0x0100)

/* ////////////////////////////////////////////////////// */
// コンフィグ設定情報
class StConfig
{
public:
	StConfig();
	~StConfig();
	StConfig( const StConfig& i_refConfig );
//	void Copy( const StConfig& i_refConfig );

	BOOL IsIgnoreClassName( const CString& strClassName );
	int FindClassName( CString i_strClassName );

	DWORD	m_BackGroundColorOpen;	// 背景の色(IME ON)
//	CBrush	m_BackGroundBrushOpen;	// 描画用ブラシ(IME ON)
	DWORD	m_BackGroundColorClose;	// 背景の色(IME OFF)
//	CBrush	m_BackGroundBrushClose;	// 描画用ブラシ(IME OFF)

//	DWORD	m_FrameColor;			// 枠の色
	BYTE	m_TransparencyOpen;		// 透明度(IME ON)
	BYTE	m_TransparencyClose;	// 透明度(IME OFF)

	DWORD	m_FrameLength;			// フェード効果のフレーム(時間)の長さ
	BYTE	m_BlinkCount;			// フェード効果の点滅回数

	CStringArray m_IgnoreClassName;	// 無視するクラス名リスト

};
