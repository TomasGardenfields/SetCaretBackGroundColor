
#pragma once
#include "stConfig.h"

// �f�t�H���g�R���X�g���N�^
StConfig::StConfig()
{
	this->m_BackGroundColorOpen = 0;
	this->m_BackGroundColorClose = 0;

	this->m_TransparencyOpen = 128;
	this->m_TransparencyClose = 128;

	this->m_FrameLength = 10;
	this->m_BlinkCount = 1;
	
	this->m_IgnoreClassName.RemoveAll();
}

StConfig::~StConfig()
{
	this->m_IgnoreClassName.RemoveAll();
}

// �R�s�[�R���X�g���N�^
StConfig::StConfig( const StConfig& i_refConfig )
{
	this->m_BackGroundColorOpen = i_refConfig.m_BackGroundColorOpen;
	this->m_BackGroundColorClose = i_refConfig.m_BackGroundColorClose;

	this->m_TransparencyOpen = i_refConfig.m_TransparencyOpen;
	this->m_TransparencyClose = i_refConfig.m_TransparencyClose;

	this->m_FrameLength = i_refConfig.m_FrameLength;
	this->m_BlinkCount = i_refConfig.m_BlinkCount;

	this->m_IgnoreClassName.RemoveAll();
	this->m_IgnoreClassName.SetSize( i_refConfig.m_IgnoreClassName.GetSize() );
	//this->m_IgnoreClassName.Copy( i_refConfig.m_IgnoreClassName );
}

// ������Z�q
/*
void StConfig::Copy( const StConfig& i_refConfig )
{
	this->m_BackGroundColorOpen = i_refConfig.m_BackGroundColorOpen;
	this->m_BackGroundColorClose = i_refConfig.m_BackGroundColorClose;

	this->m_TransparencyOpen = i_refConfig.m_TransparencyOpen;
	this->m_TransparencyClose = i_refConfig.m_TransparencyClose;

	this->m_FrameLength = i_refConfig.m_FrameLength;
	this->m_BlinkCount = i_refConfig.m_BlinkCount;

	this->m_IgnoreClassName.RemoveAll();
	this->m_IgnoreClassName.SetSize( i_refConfig.m_IgnoreClassName.GetSize() );
//	this->m_IgnoreClassName.Copy( i_refConfig.m_IgnoreClassName );
//	for ( int i = 0 ; i < i_refConfig.m_IgnoreClassName.GetSize() ; i++ )
//	{
//		this->m_IgnoreClassName.Add( i_refConfig.m_IgnoreClassName.GetAt( i ) );
//	}

	return;
}
*/
BOOL StConfig::IsIgnoreClassName( const CString& strClassName )
{
	// ��s�͖������Ŗ������Ȃ�
	if ( strClassName == "" )
	{
		return TRUE;
	}

	for ( int i = 0 ; i < this->m_IgnoreClassName.GetSize() ; i++ )
	{
		CString strIgnoreClassName = this->m_IgnoreClassName.GetAt( i );
		if ( strIgnoreClassName.Find( strClassName ) != -1 )
		{
			// �ꕔ����v�����疳������
			return FALSE;
		}
	}

	// �Ō�܂Ō�����Ȃ������疳�����Ȃ�
	return TRUE;
}

int StConfig::FindClassName( CString i_strClassName )
{
	for ( int i = 0 ; i < this->m_IgnoreClassName.GetSize() ; i++ )
	{
		if ( i_strClassName == this->m_IgnoreClassName.GetAt( i ) )
		{
			return i;
		}
	}
	return -1;
}