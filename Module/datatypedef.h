#ifndef _DATATYPEDEF_H
#define _DATATYPEDEF_H

#include <map>
#include <time.h>
#include <string>
#include <list>
#include <queue>

#include "gconst.h"

using namespace std;


//////////////////////////////////////////////////////////////////////////////
// 类型定义

typedef unsigned char       byte;
typedef unsigned short      word;
typedef unsigned int        dword;
typedef unsigned int        uint;
#ifdef _WINDOWS
	typedef __int64				int64;
	typedef unsigned __int64	uint64;
#else
	typedef long long			int64;
	typedef unsigned long long	uint64;
#endif

#pragma pack(1)     //1字节对齐
// IP - Port 结构
struct NetAddr
{
    char sIp[16];           // 服务器的IP地址 (网络字节顺序)
    word nPort;             // 服务器的UDP端口
	NetAddr() :nPort(0){ memset(sIp, 0, 16); }
	NetAddr(const char *ip, word wport) :nPort(wport){ memcpy(sIp, ip, 15); sIp[15] = 0; }
}; 

#pragma pack()     //1字节对齐


#endif
