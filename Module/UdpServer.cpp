#include "UdpServer.h"

#include "ConfigFile.h"
#include "log.h"
//#include "packetbuf.h"
//#include "BarInfo.h"
//#include "UserOnlineInfo.h"
//#include "UserInfoList.h"
//#include "JsonCode.h"
//#include "GameInfo.h"

template <> CUdpServer *CSingle<CUdpServer>::m_pInstance = 0;

void testPacket()
{
	//CNetAddr addr;
	//addr.SetAddr("192.168.102.177", 5050);
	//string strInfo = "adsfasdfasdfasdf";
	//int nLen = strInfo.size() + sizeof(CPacketHeader);
	//char *p = new char[nLen];
	//memset(p, 0, nLen);
	//memcpy(p + sizeof(CPacketHeader), strInfo.c_str(), strInfo.size());
	//((CPacketHeader *)p)->InitHeader(100, 1, nLen);
	//CUdpServer::GetInstance()->SendPacket(addr, p, nLen);
}

CUdpServer::CUdpServer()
{
	InitializeCriticalSection(&m_lkSendPacket);
	m_nPort = CConfigFile::GetInstance()->GetLocalUDPListenPort();
	int nRet = CCommInterface::StartUdpServer(m_nPort, ProcUdpConnect, this);
	CLogSocket::WriteLog("CUdpServer::SendPacket bgn action: 4-%d", nRet);
	if (nRet <= 0)
	{
		// 
	}
}

CUdpServer::~CUdpServer()
{
	Stop(); 
	CCommInterface::StopUdpServer();
	DeleteCriticalSection(&m_lkSendPacket);
}

// ���ͱ���
int CUdpServer::SendPacket(const char *pRemoteIP, int nRemotePort, void *p, int nLen)
{
	int nRet = -1;
	CLogSocket::WriteLog("CUdpServer::SendPacket bgn action: %d--%s-%d", *((word *)p), pRemoteIP, nRemotePort);
	nRet = CCommInterface::SendUdpDataByServer((char *)pRemoteIP, nRemotePort, p, nLen);
	return nRet;
}

int CUdpServer::LoginServer(const CNetAddr& stToAddr, void *p, int nLen)
{
	int nRet = -1;
	CLogSocket::WriteLog("CUdpServer::LoginServer bgn action: %d--%s", *((word *)p), stToAddr.GetIpPortString());
	nRet = CCommInterface::SendUdpDataByServer((char *)stToAddr.GetIpString().c_str(), stToAddr.GetPort(), p, nLen);
	return nRet;
}

void CUdpServer::ProcUdpConnect(void *pCallbackParam, char *pRecvBuf, int nBufLen, const char *pRemoteIp, int nRemotePort)
{
	CLogSocket::WriteLog("CUdpServer::ProcUdpConnect recv packet bgn: %d, from : %s-%d", *((word *)pRecvBuf), pRemoteIp, nRemotePort);
	CUdpServer::GetInstance()->RecvPacket(pCallbackParam, pRecvBuf, nBufLen, pRemoteIp, nRemotePort);
	//CLogSocket::WriteLog("CUdpServer::ProcUdpConnect recv packet end");
}
void CUdpServer::RecvPacket(void *pCallbackParam, char *pRecvBuf, int nBufLen, const char *pRemoteIp, int nRemotePort)
{
	//// ����
	//CNetAddr addr(pRemoteIp, nRemotePort);
	//CPacketHeader *p = (CPacketHeader *)pRecvBuf;
	////if (p->nActionCode == 8)
	////{
	////	// ���� 
	////	return;
	////}
	//if (p->CheckHeaderIsValid())
	//{
	//	if (p->nActionCode == SC_LOGINSERVER)
	//	{
	//		ProcReSCLoginServer(addr, p);
	//	}
	//	if (p->nActionCode == CC_GAMEINFOEX || p->nActionCode == CCN_LOGINSERVER || p->nActionCode == CN_LOGINSERVER || p->nActionCode == CN_LOGINSERVER || p->nActionCode == NC_LOGINSERVER)
	//	{
	//		DefaultProcPacket(addr, pRecvBuf, nBufLen);
	//	}
	//	CSafeLock<CUdpServer> lk(this); // ���ܲ�������
	//	if (m_pHeader)
	//	{
	//		if (!m_pHeader->RecvPacket(addr, pRecvBuf, nBufLen))
	//		{
	//			DefaultProcPacket(addr, pRecvBuf, nBufLen);
	//		}
	//	}
	//}
}

// ɨ�账�� 
bool CUdpServer::Proc(bool &bContinue)
{
	Sleep(100);
	bContinue = false;

	return true;
}

// ע��Ӧ�÷���
void CUdpServer::RegeditServer(CNetServer *pServer)
{
	CSafeLock<CUdpServer> lk(this);
	if (!m_pHeader)
	{
		m_pHeader = pServer;
	}
	else
	{
		m_pHeader->AppendServer(pServer);
	}
}

void CUdpServer::UnRegeditServer(CNetServer *pServer)
{
	CSafeLock<CUdpServer> lk(this);
	if (m_pHeader)
	{
		if (m_pHeader == pServer)
		{
			m_pHeader = pServer->GetNext();
		}else
		{
			m_pHeader->RemoveServer(pServer);
		}
	}
}

//// �����¼����Ӧ��
//void CUdpServer::ProcReSCLoginServer(const CNetAddr &addrFrom, CPacketHeader *p)
//{
//	CLogSocket::WriteLog("CUdpServer::ProcReSCLoginServer bgn");
//	if (!CUserOnlineInfo::GetInstance()->IsLoginServer() && !CUserOnlineInfo::GetInstance()->GetIsControl())
//	{
//		COperatePacket *p1 = COperatePacket::GetPacketFromBuf(p, p->nPacketLen);
//		CUserOnlineInfo::GetInstance()->ProcReSCLoginServer(addrFrom, p1, true);
//		delete p1;
//		CUserOnlineInfo::GetInstance()->GetBarConfig();
//	}
//
//}

// ����û��Ӧ�ô����ҵ��
void CUdpServer::DefaultProcPacket(const CNetAddr &addFrom, void *pPacket, int nPacketLen)
{
	//COperatePacket *p = COperatePacket::GetPacketFromBuf(pPacket, nPacketLen);
	//if (CConfigFile::GetInstance()->GetLocalMachineName().compare(p->GetMachineName()) != 0)
	//{
	//	if (p->GetHeader()->nActionCode == CC_GAMEINFOEX)
	//	{
	//		ProcDefaultCallGameInfoEx(addFrom, p);
	//	}
	//	else if (p->GetHeader()->nActionCode == CCN_LOGINSERVER)
	//	{
	//		ProcControlLSByNet(addFrom, p);
	//	}
	//	else if (p->GetHeader()->nActionCode == CN_LOGINSERVER)
	//	{
	//		ProcLoginLSByNet(addFrom, p);
	//	}
	//	else if (p->GetHeader()->nActionCode == CN_LOGINSERVER)
	//	{
	//		ProcLoginServerNotify(addFrom, p);
	//	}
	//	else if (p->GetHeader()->nActionCode == NC_LOGINSERVER)
	//	{
	//		ProcReLoginServerNotify(addFrom, p);
	//	}
	//}
	//delete p;
}

//// �����û���Ϸ��Ϣ
//void CUdpServer::ProcDefaultCallGameInfoEx(const CNetAddr &addrFrom, COperatePacket *p)
//{
//}
//
//// �����̨��¼
//void CUdpServer::ProcControlLSByNet(const CNetAddr &addrFrom, COperatePacket *p)
//{
//	CLogSocket::WriteLog("CUdpServer::ProcControlLSByNet bgn");
//	CBarInfo::GetInstance()->SetAddrControl(addrFrom);
//	string strInfo = CGameInfo::GetInstance()->GetGameUserInfoA();
//	if (!strInfo.empty())
//	{
//		CLogSocket::WriteLog("��ȡ��Ϸ��Ϣ���͵���̨��Ŀ���ַ�� %s", addrFrom.GetIpPortString().c_str());
//		string strGameType = "0";
//		string strGameState = CGameInfo::GetInstance()->GetUserGameState();
//		CCGameInfoExPacket packet;
//		CPacketHeader *pHeader = packet.CreateSendBuf(CConfigFile::GetInstance()->GetLocalMachineName(), CUserOnlineInfo::GetInstance()->GetUserId(), strGameType, strGameState, strInfo);
//		CUdpServer::GetInstance()->SendPacket(addrFrom, pHeader, pHeader->nPacketLen);
//	}
//	CLogSocket::WriteLog("CUdpServer::ProcControlLSByNet end");
//}
//
//// �����¼����Ӧ��
//void CUdpServer::ProcLoginLSByNet(const CNetAddr &addrFrom, COperatePacket *p)
//{
//	CLogSocket::WriteLog("CUdpServer::ProcLoginLSByNet bgn");
//	CBarInfo::GetInstance()->SetAddrControl(addrFrom);
//	string strInfo = CGameInfo::GetInstance()->GetGameUserInfoA();
//	if (!strInfo.empty())
//	{
//		CLogSocket::WriteLog("��ȡ��Ϸ��Ϣ���͵��Է���Ŀ���ַ�� %s", addrFrom.GetIpPortString().c_str());
//		string strGameType = "0";
//		string strGameState = CGameInfo::GetInstance()->GetUserGameState();
//		CCGameInfoExPacket packet;
//		CPacketHeader *pHeader = packet.CreateSendBuf(CConfigFile::GetInstance()->GetLocalMachineName(), CUserOnlineInfo::GetInstance()->GetUserId(), strGameType, strGameState, strInfo);
//		CUdpServer::GetInstance()->SendPacket(addrFrom, pHeader, pHeader->nPacketLen);
//	}
//	CLogSocket::WriteLog("CUdpServer::ProcLoginLSByNet end");
//}
//
//// �����¼����֪ͨ
//void CUdpServer::ProcLoginServerNotify(const CNetAddr &addrFrom, COperatePacket *p)
//{
//	CLogSocket::WriteLog("�����¼����֪ͨ beg");
//	CLoginServerNotifyPacket *pPacket = (CLoginServerNotifyPacket *)p;
//	CUserInfo info;
//	info.strMachineName = p->GetMachineName();// CMatrix::GetInstance()->GetMachineName(addrFrom);
//	info.strUserId = pPacket->GetUserId();
//	info.nMoney1 = pPacket->GetMoney1();
//	info.nMoney2 = pPacket->GetMoney2();
//	info.nVirtualItem1 = pPacket->GetVirtualItem1();
//	info.nVirtualItem2 = pPacket->GetVirtualItem2();
//	info.strUserSex = pPacket->GetUserSex();
//	CUserInfoList::GetInstance()->InsertUserInfo(addrFrom, info);
//	if (CUserOnlineInfo::GetInstance()->IsLoginServer())
//	{
//		CReLoginServerPacket RePacket;
//		CUserOnlineInfo::GetInstance()->GetUserInfo(info);
//		CPacketHeader *pHeader = RePacket.CreateSendBuf(info.strMachineName, info);
//		SendPacket(addrFrom, pHeader, pHeader->nPacketLen);
//	}
//	CLogSocket::WriteLog("�����¼����֪ͨ end");
//}
//
//// �����¼����֪ͨӦ��
//void CUdpServer::ProcReLoginServerNotify(const CNetAddr &addrFrom, COperatePacket *p)
//{
//	CLogSocket::WriteLog("�����¼����֪ͨӦ�� bgn");
//	CReLoginServerPacket *pPacket = (CReLoginServerPacket *)p;
//	CUserInfo info;
//	info.strMachineName = p->GetMachineName();// CMatrix::GetInstance()->GetMachineName(addrFrom);
//	info.strUserId = pPacket->GetUserId();
//	info.nMoney1 = pPacket->GetMoney1();
//	info.nMoney2 = pPacket->GetMoney2();
//	info.nVirtualItem1 = pPacket->GetVirtualItem1();
//	info.nVirtualItem2 = pPacket->GetVirtualItem2();
//	info.strUserSex = pPacket->GetUserSex();
//	CUserInfoList::GetInstance()->InsertUserInfo(addrFrom, info);
//	CLogSocket::WriteLog("�����¼����֪ͨӦ�� end");
//}
