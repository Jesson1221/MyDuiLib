// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�:
#include <windows.h>

// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <objbase.h>
#include <zmouse.h>
#include <exdisp.h>
#include <comdef.h>
#include <vector>
#include <sstream>
// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�

#define  _CONSOLE
#define _VSOUTPUT

#include "LuaEntry.h"
using namespace DuiLib;
 #ifdef _DEBUG
 #   ifdef _UNICODE
 #       pragma comment(lib, "DuiLib_ud.lib")
 #   else
 #       pragma comment(lib, "DuiLib_d.lib")
 #   endif
 #else
 #   ifdef _UNICODE
 #       pragma comment(lib, "DuiLib_u.lib")
 #   else
 #       pragma comment(lib, "DuiLib.lib")
 #   endif
 #endif

//#ifdef _DEBUG
//#pragma comment( linker, "/subsystem:console /entry:wWinMainCRTStartup" )
//#endif
// ------------------------------------------------------------
// ---------------------- new and delete ----------------------
// ------------------------------------------------------------
// ---------------------------------------- operator new
inline void * operator new (size_t size, const char* file, const size_t line, const char* func)
{
	void *p = malloc(size);
	if (p == NULL) throw std::bad_alloc();

	DuiLib::DuiMemeryLooker::Instance()->_recordAlloc(p, size, file, line, func);

	return p;
}
// ---------------------------------------- operator new[]
inline void * operator new [](size_t size, const char* file, const size_t line, const char* func)
{
	void *p = malloc(size);
	if (p == NULL) throw std::bad_alloc();
	DuiLib::DuiMemeryLooker::Instance()->_recordAlloc(p, size, file, line, func);

	return p;
}
////inline void * operator new(size_t size)
////{
////	void *p = malloc(size);
////	if (p == NULL) throw std::bad_alloc();
////	DuiLib::DuiMemeryLooker::Instance()->_recordAlloc(p, size);
////
////	return p;
////}
////inline void * operator new[](size_t size)
////{
////	void *p = malloc(size);
////	if (p == NULL) throw std::bad_alloc();
////	DuiLib::DuiMemeryLooker::Instance()->_recordAlloc(p, size);
////
////	return p;
////}
// ---------------------------------------- operator delete
inline void operator delete (void * pointer, size_t size)
{
	DuiLib::DuiMemeryLooker::Instance()->_recordDealloc(pointer);
	free(pointer);
}
inline void operator delete(void* pointer)
{
	DuiLib::DuiMemeryLooker::Instance()->_recordDealloc(pointer);
	free(pointer);
}

inline void operator delete[](void* pointer)
{
	DuiLib::DuiMemeryLooker::Instance()->_recordDealloc(pointer);
	free(pointer);
}
// ---------------------------------------- operator delete[]
inline void operator delete[](void * pointer, size_t size)
{
	DuiLib::DuiMemeryLooker::Instance()->_recordDealloc(pointer);
	free(pointer);
}
inline void operator delete(void *p, size_t size, const char *file, const size_t line, const char* func)
{
	DuiLib::DuiMemeryLooker::Instance()->_recordDealloc(p);
	free(p);
}

inline void operator delete[](void *p, size_t size, const char *file, const size_t line, const char* func)
{
	DuiLib::DuiMemeryLooker::Instance()->_recordDealloc(p);
	free(p);
}


 #define MC_NEW  new(__FILE__, __LINE__,__FUNCTION__)
 #define new  MC_NEW