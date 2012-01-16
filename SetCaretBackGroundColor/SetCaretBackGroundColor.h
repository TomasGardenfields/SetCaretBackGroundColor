// SetCaretBackGroundColor.h : SETCARETBACKGROUNDCOLOR �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_SETCARETBACKGROUNDCOLOR_H__DA5F0F1E_4144_49B9_A7DB_540DD122816D__INCLUDED_)
#define AFX_SETCARETBACKGROUNDCOLOR_H__DA5F0F1E_4144_49B9_A7DB_540DD122816D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��
#include "stConfig.h"

/////////////////////////////////////////////////////////////////////////////
// CSetCaretBackGroundColorApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� SetCaretBackGroundColor.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CSetCaretBackGroundColorApp : public CWinApp
{
public:
	CSetCaretBackGroundColorApp();
	virtual ~CSetCaretBackGroundColorApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CSetCaretBackGroundColorApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����

	//{{AFX_MSG(CSetCaretBackGroundColorApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

	typedef struct tagStCommandLineOption
	{
		BOOL	m_Restart;	// �ċN���t���O
	}StCommandLineOption;

	BOOL GetModulePathFileName(LPCTSTR i_pName, CString& o_pStrPath);
	BOOL ReadIniFile();
	BOOL WriteIniFile();


	HANDLE		m_hEvent;

	TCHAR*		m_pProfileName;
	const char*	m_pszProfileName_bk;

	StConfig	m_Config;

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SETCARETBACKGROUNDCOLOR_H__DA5F0F1E_4144_49B9_A7DB_540DD122816D__INCLUDED_)
