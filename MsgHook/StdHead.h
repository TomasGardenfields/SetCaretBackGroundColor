#ifndef __STDHEAD_H__
#define __STDHEAD_H__

// ���C�u�����t�@�C����ǂݍ��݂܂��B
//#pragma comment(lib, "Test.lib")
#ifdef _DEBUG
	#pragma comment(lib, "../MsgHook/Debug/MsgHook.lib")
#else
	#pragma comment(lib, "../MsgHook/Release/MsgHook.lib")
#endif

//�@�w�b�_�[�t�@�C����ǂݍ��݂܂��B
#include "Defs.h"	//�}�N���p�t�@�C���B
#include "Hook.h"	//�֐��̃v���g�^�C�v�錾���������t�@�C���B

#endif	//__STDHEAD_H__