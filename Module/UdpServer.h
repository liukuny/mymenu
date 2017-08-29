#pragma once
#include "CommInterface.h"
#include "gclass.h"
#include "netbase.h"
//#include "csprotocol.h"
//#include "OperatePacket.h"

class CUdpServer : public CSingleServer<CUdpServer>
{
public:
	// ɨ�账�� 
	bool Proc(bool &bContinue);
	// ע��Ӧ�÷���
	void RegeditServer(CNetServer *pServer);
	void UnRegeditServer(CNetServer *pServer);
	// ���ͱ���
	int SendPacket(const char *pRemoteIP, int nRemotePort, void *p, int nLen);
	int SendPacket(const char *pRemoteIPAndPort, void *p, int nLen){ CNetAddr stToAddr(pRemoteIPAndPort); return SendPacket(stToAddr.GetIpString().c_str(), stToAddr.GetPort(), p, nLen); }
	int SendPacket(const CNetAddr& stToAddr, void *p, int nLen){ return SendPacket(stToAddr.GetIpString().c_str(), stToAddr.GetPort(), p, nLen); }
	int LoginServer(const CNetAddr& stToAddr, void *p, int nLen);
protected:
	CUdpServer();// {}
	~CUdpServer();// { Stop(); }
private:
	// ����Ӧ�÷���
	CNetServer *m_pHeader = 0;
	int m_nPort;
	static void __stdcall ProcUdpConnect(void *pCallbackParam, char *pRecvBuf, int nBufLen, const char *pRemoteIp, int nRemotePort);
	void RecvPacket(void *pCallbackParam, char *pRecvBuf, int nBufLen, const char *pRemoteIp, int nRemotePort);
	//// ������
	//bool ProcPacket(const CNetAddr &addrFrom, void *pPacket, int nPacketLen);
	//// �����¼����Ӧ��
	//void ProcReSCLoginServer(const CNetAddr &addrFrom, CPacketHeader *p);
private:
	// SRWLock��Ч�ʸ��ߣ���ֻ��win7����֧��
	CRITICAL_SECTION m_lkSendPacket;
	void LockSend(){ EnterCriticalSection(&m_lkSendPacket); }
	void UnLockSend(){ LeaveCriticalSection(&m_lkSendPacket); }
	// ����û��Ӧ�ô����ҵ��
	void DefaultProcPacket(const CNetAddr &addFrom, void *pPacket, int nPacketLen);
	//// �����û���Ϸ��Ϣ
	//void ProcDefaultCallGameInfoEx(const CNetAddr &addrFrom, COperatePacket *p);
	////�����̨��¼
	//void ProcControlLSByNet(const CNetAddr &addrFrom, COperatePacket *p);
	//// ����ͷ��˵�¼
	//void ProcLoginLSByNet(const CNetAddr &addrFrom, COperatePacket *p);
	//// �����¼����֪ͨ
	//void ProcLoginServerNotify(const CNetAddr &addrFrom, COperatePacket *p);
	//// �����¼����֪ͨӦ��
	//void ProcReLoginServerNotify(const CNetAddr &addrFrom, COperatePacket *p);

	friend class CSingle<CUdpServer>;

};

