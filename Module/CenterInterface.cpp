#include "CenterInterface.h"

#include "ConfigFile.h"
#include "CommInterface.h"
#include "UdpServer.h"
//#include "csprotocol.h"
//#include "BarInfo.h"
//#include "UserOnlineInfo.h"
//#include "Jsoncode.h"
#include "log.h"
//#include "GameInfo.h"

const int TCP_TMPRECV_BUFLEN = 2 * 1024;
int g_nSeriNumber = 1;
CCenterInterface::CCenterInterface()
{
}


CCenterInterface::~CCenterInterface()
{
}

// 上传启动数据 
string CCenterInterface::UploadInfo()
{
	CLogInterface::WriteLog("上传启动数据 beg");
	map<string, string> mapParam;
	mapParam["clientId"] = CConfigFile::GetInstance()->GetClientId();
	mapParam["lanIp"] = CConfigFile::GetInstance()->GetLocalIp();
	mapParam["agencyId"] = CConfigFile::GetInstance()->GetAgencyId();
	mapParam["action"] = "1";
	mapParam["ver1"] = CConfigFile::GetInstance()->GetCurPlatformVerA();
	mapParam["ver2"] = CConfigFile::GetInstance()->GetMenuVer();
	string strUrl = CConfigFile::GetInstance()->GetUploadUrl();
	strUrl += "talking/start";
	//string strUrl = GetHttpDataUrl("/talking/start");
	string strRet = GetHttpData(strUrl, mapParam);
	CLogInterface::WriteLog("上传启动数据 end");
	return strRet;
}
// 上传游戏数据
string CCenterInterface::UploadGameInfo(string strGameId, string strGameName)
{
	CLogInterface::WriteLog("上传游戏数据 beg");
	map<string, string> mapParam;
	mapParam["clientId"] = CConfigFile::GetInstance()->GetClientId();
	mapParam["lanIp"] = CConfigFile::GetInstance()->GetLocalIp();
	mapParam["agencyId"] = CConfigFile::GetInstance()->GetAgencyId();
	mapParam["gameId"] = strGameId;
	mapParam["gameName"] = strGameName;
	string strUrl = CConfigFile::GetInstance()->GetUploadUrl();
	strUrl += "talking/launch";
	string strRet = GetHttpData(strUrl, mapParam);
	CLogInterface::WriteLog("上传游戏数据 end");
	return strRet;
}


//// 下载资源文件到本地
//string CCenterInterface::DownloadFile(const string &strUrl, const string &strFileName)
//{
//	CLogInterface::WriteLog("下载资源文件到本地 beg");
//	map<string, string> mapParam;
//	string strRet = GetHttpData(strUrl, mapParam, true);
//	CLogInterface::WriteLog("下载资源文件到本地 end");
//	return strRet;
//}
//

// 获取Http数据
string CCenterInterface::GetHttpData(const string &strUrl, map<string, string>mapParam, bool bBigRet, bool bIsPost)
{
	CLogInterface::WriteLog("获取Http数据 beg");
	string strRet;
	string sUrl(strUrl);
	string sParam;
	for (auto it : mapParam)
	{
		if (!it.first.empty())
		{
			sParam += it.first;
			sParam += "=";
			sParam += it.second;
			sParam += "&";
		}
	}
	if (!sParam.empty())
	{
		sParam = sParam.substr(0, sParam.size() - 1);
		sUrl += "?";
		sUrl += sParam;
	}
	if (bBigRet)
	{
		const int nRetLen = 10 * 1024 * 1024;
		char *szRet = new char[nRetLen];
		memset(szRet, 0, nRetLen);
		int nState(0);
		CLogInterface::WriteLog("获取Http数据 URL: %s", sUrl.c_str());
		int nRet = 0;
		if (bIsPost)
		{
			int nPos = sUrl.find("?");
			if (string::npos != nPos)
			{
				string strUrl = sUrl.substr(0, nPos);
				string strSource = sUrl.substr(nPos + 1);
				nRet = CCommInterface::PostHttpData(strUrl.c_str(), strSource.c_str(), strSource.size(), szRet, nRetLen, nState);
			}
		}
		else
		{
			nRet = CCommInterface::GetHttpData(sUrl.c_str(), szRet, nRetLen, nState);
		}
		CLogInterface::WriteLog("获取Http数据 Result: %s", szRet);
		if (nRet > 0)
		{
			strRet = szRet;
		}
		delete[] szRet;
	}
	else
	{
		int nRet = 0;
		const int nRetLen = 2 * 1024;
		char szRet[nRetLen] = { 0 };
		int nState(0);
		CLogInterface::WriteLog("获取Http数据 URL: %s", sUrl.c_str());
		if (bIsPost)
		{
			int nPos = sUrl.find("?");
			if (string::npos != nPos)
			{
				string strUrl = sUrl.substr(0, nPos);
				string strSource = sUrl.substr(nPos + 1);
				nRet = CCommInterface::PostHttpData(strUrl.c_str(), strSource.c_str(), strSource.size(), szRet, nRetLen, nState);
			}
		}
		else
		{
			nRet = CCommInterface::GetHttpData(sUrl.c_str(), szRet, nRetLen, nState);
		}
		CLogInterface::WriteLog("获取Http数据 Result: %s", szRet);
		if (nRet > 0)
		{
			strRet = szRet;
		}
	}
	CLogInterface::WriteLog("获取Http数据 end");
	return strRet;
}

// 获取Http数据请求链接
string CCenterInterface::GetHttpDataUrl(const string &strPath)
{
	const int nBufLen(200);
	char szBuf[nBufLen] = { 0 };
	//sprintf_s(szBuf, nBufLen, "http://%s%s", CConfigFile::GetInstance()->GetServerHttpIpPort().c_str(), strPath.c_str());
	string strUrl(szBuf);
	return strUrl;
}

// 回调函数指针类型
// 参数：
//   pCallbackParam - 传给回调函数的上层参数；
//   pSreamSocket	- 此连接SreamSocket对象指针；
//   pRemoteIp		- 此连接中的远程Ip；
//   nRemotePort	- 此连接中的远程端口；
void WINAPI CCenterInterface::ClientProcTcpConnect(void *pCallbackParam, void *pSreamSocket, char *pSendBuf, int nBufLen)
{
	CCommonTCPPacket *p = (CCommonTCPPacket *)pSendBuf;
	int nSendLen = p->_data_len + sizeof(CCommonTCPPacket);
	p->_command_id = ::htonl(p->_command_id);
	p->_head_flag = ::htonl(p->_head_flag);
	p->_data_len = ::htonl(p->_data_len);
	p->_seq_no = ::htonl(p->_seq_no);
	CCommonTCPPacket ReHeader;
	int nRet = CCommInterface::SendTcpDataByClientConnection(pSreamSocket, p, nSendLen);
	if (nRet <= 0)
	{
		CLogInterface::WriteLog("CCenterInterface::ClientProcTcpConnect send header action: %d, false： %d", p->_command_id, ::GetLastError());
		return;
	}
	nRet = CCommInterface::RecvTcpDataByClientConnection(pSreamSocket, &ReHeader, sizeof(ReHeader));
	if (nRet <= 0)
	{
		CLogInterface::WriteLog("CCenterInterface::ClientProcTcpConnect recv header action: %d, false： %d", p->_command_id, ::GetLastError());
		return;
	}

	int nR = ::ntohl(ReHeader._data_len);
	if (nR <= 0)
	{
		CLogInterface::WriteLog("CCenterInterface::ClientProcTcpConnect recv Data len: %d -- %d", p->_data_len, nR);
		return;
	}
	// 接受数据
	char *pRecv = new char[nR + 1];
	nRet = CCommInterface::RecvTcpDataByClientConnection(pSreamSocket, pRecv, nR);
	if (nRet <= 0)
	{
		CLogInterface::WriteLog("CCenterInterface::ClientProcTcpConnect recv header action: %d, 接受文件名长度 false： %d", p->_command_id, ::GetLastError());
		delete []pRecv;
		return;
	}

	if (pCallbackParam)
	{
		if (nR > TCP_TMPRECV_BUFLEN){ nR = TCP_TMPRECV_BUFLEN; }
		memcpy(pCallbackParam, pRecv, nR);
	}
	delete []pRecv;
}

