#ifndef __DEFS_H__
#define __DEFS_H__

#ifdef DLL_EXPORT_DO		//����� StdAfx.h �Œ�`����Ă��܂��B
   #define DLL_EXPORT	__declspec(dllexport)
#else
   #define DLL_EXPORT	__declspec(dllimport)
#endif

#endif	//__DEFS_H__