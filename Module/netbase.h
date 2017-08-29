// netbase.h
#ifndef _NETBASE_H
#define _NETBASE_H
//#include <sys/socket.h>
//#include <netinet/in.h>

#include "datatypedef.h"
#include "gfunction.h"

// �����ַ�� NetAddr��װ
//////////////////////////////////////////////////////////////////////////////
// class CInetAddress - �����ַ��(�����ֽ�˳��)

class CNetAddr : public NetAddr
{
public:
    CNetAddr(){}
    CNetAddr(const NetAddr& stNetAddr) : NetAddr(stNetAddr.sIp, stNetAddr.nPort){}
    CNetAddr(const CNetAddr& stNetAddr) : NetAddr(stNetAddr.sIp, stNetAddr.nPort){}
	CNetAddr(const char* sIp, word wPort) : NetAddr(sIp, wPort){}
	CNetAddr(const char* sIpAndPort){ SetIpPortString(sIpAndPort); }
	// ����: ����port
	int GetPort() const{ return nPort; }// ntohs(nPort); linux����ת��
    // ����: �����ַ�����IP(��"127.0.0.1") ��ע: �˴�����ʹ��inet_ntoaת����������Ϊ���ǲ�������ġ�
	string GetIpString() const { return sIp; }
	string GetIpPortString() const { string strRet(sIp); strRet += ":"; strRet += IntToStr(nPort); return strRet; }
	void SetIpPortString(const string& strIpAndPort) 
	{ 
		memset(this, 0, sizeof(*this));
		if (strIpAndPort.size() > 9)
		{
			int nIndex = strIpAndPort.find(":"); 
			if (string::npos != nIndex && nIndex <= 15)
			{
				memcpy(sIp, strIpAndPort.c_str(), nIndex);
				nPort = StrToInt(strIpAndPort.substr(nIndex + 1).c_str());
			}
		}
	}

    // ����: ���ַ�����IP(��"127.0.0.1")�����Լ�
	void SetIp(const string& strIpString){ memcpy(sIp, strIpString.c_str(), 15); sIp[15] = 0; }
	void SetPort(word wPort){ nPort = wPort; }
	void SetAddr(const string& strIpString){ SetAddr(strIpString, 0); }
	void SetAddr(const string& strIpString, word wPort){ memcpy(sIp, strIpString.c_str(), 15); sIp[15] = 0;  nPort = wPort; }
	void operator =(const CNetAddr &r)
	{
		memcpy(sIp, r.sIp, 16);
		nPort = r.nPort;
	}
	bool operator ==(const CNetAddr &r) const
	{
		string strIp = sIp;
		if (strIp.compare(r.sIp) == 0 && nPort == r.nPort)
		{
			return true;
		}
		return false;
	}
	bool operator !=(const CNetAddr &r) const
	{
		string strIp = sIp;
		if (strIp.compare(r.sIp) == 0 && nPort == r.nPort)
		{
			return false;
		}
		return true;
	}
	bool IsValidAddr()
	{
		string strIp = sIp;
		if (strIp.size() < 7)
		{
			return false;
		}
		if (nPort == 0)
		{
			return false;
		}
		return true;
	}
	//// ����: ��in_addr��IP�����Լ�
	//void SetAddr(const struct sockaddr_in& stInetAddr);
	//bool CNetAddr::GetAddr(sockaddr_in &Addr) const;
	//CNetAddr& operator=(const struct sockaddr_in& stInetAddr){SetAddr(stInetAddr); return *this;}
};

// �Ƿ����Լ��ı���
typedef bool(__stdcall *PIsSelfPacket)(void *pPacket, void *pCallbackParam);
// �Ƿ����Լ��ı���
typedef bool(__stdcall *PProcPacket)(const CNetAddr &addFrom, void *pPacket, int nPacketLen, void *pCallbackParam);

class CNetServer
{
public:
	CNetServer(void *pOwner, PIsSelfPacket pIsSelfPacket, PProcPacket pProcPacket){ m_pOwner = pOwner; m_pIsSelfPacket = pIsSelfPacket; m_pProcPacket = pProcPacket; }
	CNetServer *GetNext(){ return m_pNext; }
	bool RecvPacket(const CNetAddr &addFrom, void *pPacket, int nPacketLen)
	{
		if(ProcPacket(addFrom, pPacket, nPacketLen))
		{
			return true;
		}
		if (m_pNext)
		{
			return m_pNext->RecvPacket(addFrom, pPacket, nPacketLen);
		}
		return false; 
	}
	void AppendServer(CNetServer *pServer){ if (m_pNext){ m_pNext->AppendServer(pServer); } else { m_pNext = pServer; }; }
	void RemoveServer(CNetServer *pServer){ if (m_pNext){ if (pServer == m_pNext){ m_pNext = m_pNext->GetNext(); } else{ m_pNext->RemoveServer(pServer); } } }
protected:
	bool IsSelfPacket(void *pPacket){ if (m_pIsSelfPacket){ return m_pIsSelfPacket(pPacket, m_pOwner); }return false; }
	bool ProcPacket(const CNetAddr &addFrom, void *pPacket, int nPacketLen)
	{ 
		if (m_pProcPacket)
		{ 
			if (IsSelfPacket(pPacket))
			{
				return m_pProcPacket(addFrom, pPacket, nPacketLen, m_pOwner); 
			}
		}
		return false; 
	}
private:
	CNetServer *m_pNext = 0;
	PIsSelfPacket m_pIsSelfPacket = 0;
	PProcPacket m_pProcPacket = 0;
	void *m_pOwner = 0;
};

#endif
