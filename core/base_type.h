#ifndef _BASE_TYPE_H
#define _BASE_TYPE_H

/////////////////////////////////////////////////////////////////////////////////
//当前包含的系统头文件引用
/////////////////////////////////////////////////////////////////////////////////
#if defined(__WINDOWS__)
#pragma warning ( disable : 4786 )
#include <Windows.h>
#include "crtdbg.h"
#elif defined(__LINUX__)
#include <sys/types.h>
#include <execinfo.h>
#include <signal.h>
#include <exception>
#include <setjmp.h>
#include <sys/epoll.h>
#endif

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <math.h>
#include <stdarg.h>

///////////////////////////////////////////////////////////////////////
//标准数据类型定义
///////////////////////////////////////////////////////////////////////
#define VOID			void			//标准空
typedef unsigned char	UCHAR;			//标准无符号CHAR
typedef char			CHAR;			//标准CHAR
typedef unsigned int	UINT;			//标准无符号INT
typedef int				INT;			//标准INT
typedef unsigned short	USHORT;			//标准无符号short
typedef short			SHORT;			//标准short
typedef unsigned long	ULONG;			//标准无符号LONG(不推荐使用)
typedef long			LONG;			//标准LONG(不推荐使用)
typedef float			FLOAT;			//标准float

typedef UCHAR			uchar;
typedef USHORT			ushort;
typedef UINT			uint;
typedef ULONG			ulong;
typedef INT				BOOL;
typedef UCHAR			BYTE;

#define INVALID_HANDLE	-1				//无效的句柄
#define INVALID_ID		-1				//无效的ID值

#ifndef TRUE							//真
#define TRUE 1
#endif

#ifndef FALSE							//假
#define FALSE 0
#endif

#if defined(NDEBUG)
#define _OX_TRY try
#define _OX_CATCH catch(...)
#else
#define _OX_TRY try
#define _OX_CATCH catch(...)
#endif

//根据指针值删除内存
#ifndef SAFE_DELETE
#define SAFE_DELETE(x)	if( (x)!=NULL ) { delete (x); (x)=NULL; }
#endif
//根据指针值删除数组类型内存
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x)	if( (x)!=NULL ) { delete[] (x); (x)=NULL; }
#endif
//根据指针调用free接口
#ifndef SAFE_FREE
#define SAFE_FREE(x)	if( (x)!=NULL ) { free(x); (x)=NULL; }
#endif
//根据指针调用Release接口
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x)	if( (x)!=NULL ) { (x)->Release(); (x)=NULL; }
#endif

#define IP_SIZE			24    //IP地址的字符最大长度

#endif