#if !defined(AFX_IGNOREDIALOG_H__1ED3B4EB_E686_4D40_94B4_31E210A75EB2__INCLUDED_)
#define AFX_IGNOREDIALOG_H__1ED3B4EB_E686_4D40_94B4_31E210A75EB2__INCLUDED_

#include "stConfig.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IgnoreDialog.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CIgnoreDialog �_�C�A���O

class CIgnoreDialog : public CDialog
{
// �R���X�g���N�V����
public:
	BOOL AddHistory( HWND i_hWnd );
	CIgnoreDialog( StConfig& i_refConfig, CWnd* pParent );   // �W���̃R���X�g���N�^
	virtual ~CIgnoreDialog();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CIgnoreDialog)
	enum { IDD = IDD_DIALOG_IGNORE };
	CListBox	m_listboxIgnoreClassNameHistory;
	CButton	m_btnClassnameRemove;
	CButton	m_btnClassnameAdd;
	CListBox	m_listboxIgnoreClassName;
	CString	m_strIgnoreClassName;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CIgnoreDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CIgnoreDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSelchangeListIgnoreClassnameHistory();
	afx_msg void OnButtonIgnoreClose();
	afx_msg void OnButtonClassnameAdd();
	afx_msg void OnButtonClassnameRemove();
	afx_msg void OnSelchangeListIgnoreClassname();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	StConfig&	m_refConfig;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_IGNOREDIALOG_H__1ED3B4EB_E686_4D40_94B4_31E210A75EB2__INCLUDED_)
