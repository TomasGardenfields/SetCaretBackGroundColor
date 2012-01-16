// MsgHook.cpp : DLL �p�̏����������̒�`���s���܂��B
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

	// lpReserved ���g���ꍇ�͂������폜���Ă�������
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("MSGHOOK.DLL Initializing!\n");
		
		// �g�� DLL ���P�񂾂����������܂��B
		if (!AfxInitExtensionModule(MsgHookDLL, hInstance))
			return 0;

		// ���� DLL �����\�[�X �`�F�C���֑}�����܂��B
		// ����: �g�� DLL �� MFC �A�v���P�[�V�����ł͂Ȃ�
		//   MFC �W�� DLL (ActiveX �R���g���[���̂悤��)
		//   �ɈÖٓI�Ƀ����N�����ꍇ�A���̍s�� DllMain
		//   ����폜���āA���̊g�� DLL ����G�N�X�|�[�g
		//   ���ꂽ�ʂ̊֐����֒ǉ����Ă��������B  
		//   ���̊g�� DLL ���g�p����W�� DLL �͂��̊g�� DLL
		//   �����������邽�߂ɖ����I�ɂ��̊֐����Ăяo���܂��B 
		//   ����ȊO�̏ꍇ�́ACDynLinkLibrary �I�u�W�F�N�g��
		//   �W�� DLL �̃��\�[�X �`�F�C���փA�^�b�`���ꂸ�A
		//   ���̌��ʏd��Ȗ��ƂȂ�܂��B

		new CDynLinkLibrary(MsgHookDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("MSGHOOK.DLL Terminating!\n");
		// �f�X�g���N�^���Ăяo�����O�Ƀ��C�u�������I�����܂�
		AfxTermExtensionModule(MsgHookDLL);
	}
	return 1;   // ok
}
