#include "netbase.h"
#include "log.h"

#include <errno.h>
#include <fcntl.h>        // _GETFL 


//
////////////////////////////////////////////////////////////////////////////////
//// class CNetAddr
//// ����: ����IP(in_addr)
//bool CNetAddr::GetAddr(sockaddr_in &Addr) const 
//{ 
//    memset(&Addr, 0, sizeof(sockaddr_in));
//    Addr.sin_family = AF_INET;
//    Addr.sin_addr.s_addr = nIp; 
//    Addr.sin_port = nPort; 
//    return true; 
//}
//
////----------------------------------------------------------------------------
//// ����: ���ַ�����IP(��"127.0.0.1")�����Լ�
////----------------------------------------------------------------------------
//void CNetAddr::SetAddr(const struct sockaddr_in& stInetAddr)
//{
//	sprintf_s(sIp, 15, "%s.%s.%s.%s", stInetAddr.sin_addr.s_addr.);
//	nPort = stInetAddr.sin_port; 
//}
//

