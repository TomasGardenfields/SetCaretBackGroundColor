
#pragma once
#include <afxcoll.h>

#define WM_APP_UPDATECOLOR	(WM_APP + 0x0100)

/* ////////////////////////////////////////////////////// */
// �R���t�B�O�ݒ���
class StConfig
{
public:
	StConfig();
	~StConfig();
	StConfig( const StConfig& i_refConfig );
//	void Copy( const StConfig& i_refConfig );

	BOOL IsIgnoreClassName( const CString& strClassName );
	int FindClassName( CString i_strClassName );

	DWORD	m_BackGroundColorOpen;	// �w�i�̐F(IME ON)
//	CBrush	m_BackGroundBrushOpen;	// �`��p�u���V(IME ON)
	DWORD	m_BackGroundColorClose;	// �w�i�̐F(IME OFF)
//	CBrush	m_BackGroundBrushClose;	// �`��p�u���V(IME OFF)

//	DWORD	m_FrameColor;			// �g�̐F
	BYTE	m_TransparencyOpen;		// �����x(IME ON)
	BYTE	m_TransparencyClose;	// �����x(IME OFF)

	DWORD	m_FrameLength;			// �t�F�[�h���ʂ̃t���[��(����)�̒���
	BYTE	m_BlinkCount;			// �t�F�[�h���ʂ̓_�ŉ�

	CStringArray m_IgnoreClassName;	// ��������N���X�����X�g

};
