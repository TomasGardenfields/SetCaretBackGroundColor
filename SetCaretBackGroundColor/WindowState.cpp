// WindowState.cpp: CWindowState クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SetCaretBackGroundColor.h"
#include "WindowState.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

StWindowState::StWindowState()
{
	this->m_Color = 0x00000000;
	this->m_Transparency = 0;
}

StWindowState StWindowState::Interpolate( StWindowState i_State1, StWindowState i_State2, float i_Rate1 )
{
	StWindowState a_Temp;

	float a_Rate2 = 1.0f - i_Rate1;

	/*
	BYTE r1, g1, b1;
	BYTE r2, g2, b2;

	r1 = GetRValue( i_State1.m_Color );
	g1 = GetGValue( i_State1.m_Color );
	b1 = GetBValue( i_State1.m_Color );

	r2 = GetRValue( i_State2.m_Color );
	g2 = GetGValue( i_State2.m_Color );
	b2 = GetBValue( i_State2.m_Color );

	// 補間した色
	a_Temp.m_Color = RGB( r1 * i_Rate1 + r2 * a_Rate2, g1 * i_Rate1 + g2 * a_Rate2, b1 * i_Rate1 + b2 * a_Rate2 );
	*/

	// 補間した透明度
	a_Temp.m_Transparency = (BYTE)( i_State1.m_Transparency * i_Rate1 + i_State2.m_Transparency * a_Rate2 );

	return a_Temp;
}

