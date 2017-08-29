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
// ���Ͷ���

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

#pragma pack(1)     //1�ֽڶ���
// IP - Port �ṹ
struct NetAddr
{
    char sIp[16];           // ��������IP��ַ (�����ֽ�˳��)
    word nPort;             // ��������UDP�˿�
	NetAddr() :nPort(0){ memset(sIp, 0, 16); }
	NetAddr(const char *ip, word wport) :nPort(wport){ memcpy(sIp, ip, 15); sIp[15] = 0; }
}; 

#pragma pack()     //1�ֽڶ���


#endif
