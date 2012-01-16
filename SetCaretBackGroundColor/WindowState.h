// WindowState.h: CWindowState クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINDOWSTATE_H__14294025_0419_40E2_8865_1B4089AD0E33__INCLUDED_)
#define AFX_WINDOWSTATE_H__14294025_0419_40E2_8865_1B4089AD0E33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct StWindowState
{
public:
	StWindowState();
	
	bool operator ==( StWindowState& i_State )
	{
		return ( ( m_Transparency == i_State.m_Transparency ) );
	}

	static StWindowState Interpolate( StWindowState i_State1, StWindowState i_State2, float i_rate );

	COLORREF	m_Color;		// 色
	BYTE		m_Transparency; // 透明度
};

#endif // !defined(AFX_WINDOWSTATE_H__14294025_0419_40E2_8865_1B4089AD0E33__INCLUDED_)
