#include <windows.h>

#include "CommInterface.h"


HMODULE CCommInterface::m_hdll = 0;
// ����UDP����
PStartUdpServer CCommInterface::m_pStartUdpServer = 0;
// ֹͣUDP����
PStopUdpServer CCommInterface::m_pStopUdpServer = 0;
// ����UDP����
PSendUdpData CCommInterface::m_pSendUdpData = 0;
// ����UDP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
PSendUdpDataByServer CCommInterface::m_pSendUdpDataByServer = 0;

// ����TCP����
PStartTcpServer CCommInterface::m_pStartTcpServer = 0;
// ֹͣTCP����
PStopTcpServer CCommInterface::m_pStopTcpServer = 0;
// ͨ������˷���TCP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
PSendTcpDataByServerConnection CCommInterface::m_pSendTcpDataByServerConnection = 0;
// ͨ������˽���TCP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
PRecvTcpDataByServerConnection CCommInterface::m_pRecvTcpDataByServerConnection = 0;
// ͨ���ͻ��˷���TCP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
PSendTcpDataByClient CCommInterface::m_pSendTcpDataByClient = 0;
// ͨ���ͻ��˷���TCP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
PSendTcpDataByClientConnection CCommInterface::m_pSendTcpDataByClientConnection = 0;
// ͨ���ͻ��˽���TCP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
PRecvTcpDataByClientConnection CCommInterface::m_pRecvTcpDataByClientConnection = 0;

// �ϴ�Http/Https����
PPostHttpData CCommInterface::m_pPostHttpData = 0;
// ����HttpЭ������
PGetHttpData CCommInterface::m_pGetHttpData = 0;
// ����Http��Https���ļ�����
PDownloadDataFromServer CCommInterface::m_pDownloadDataFromServer = 0;

// WebSock�ͻ���
PCreateWebSockClient CCommInterface::m_pCreateWebSockClient = 0;
// ����WebSock�ͻ�������(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
PSendDataByWebSockClient CCommInterface::m_pSendDataByWebSockClient = 0;
// �ر�WebSock
PCloseWebSockClient CCommInterface::m_pCloseWebSockClient = 0;

// �������ѹ���ļ�
PUnzipFile CCommInterface::m_pUnzipFile = 0;
// ���ļ���ѹ���ļ���
PUnzipFileToPath CCommInterface::m_pUnzipFileToPath = 0;

CCommInterface::CCommInterface()
{
}


CCommInterface::~CCommInterface()
{
}

// ��װ�ײ�ͨѶ�ӿ�ģ��
void CCommInterface::InstallCommModule()
{
	//FreeAdmodule();
	if (m_hdll)
	{
		return;
	}
	m_hdll = LoadLibrary(COMMMODULE_INTERFACEDLL_NAME);
	if (!m_hdll)
	{
		int nErr = ::GetLastError();
		return;
	}
	// ����UDP����
	m_pStartUdpServer = (PStartUdpServer)GetProcAddress(m_hdll, "StartUdpServer");
	// ֹͣUDP����
	m_pStopUdpServer = (PStopUdpServer)GetProcAddress(m_hdll, "StopUdpServer");
	// ����UDP����
	m_pSendUdpData = (PSendUdpData)GetProcAddress(m_hdll, "SendUdpData");
	// ����UDP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
	m_pSendUdpDataByServer = (PSendUdpDataByServer)GetProcAddress(m_hdll, "SendUdpDataByServer");

	// ����TCP����
	m_pStartTcpServer = (PStartTcpServer)GetProcAddress(m_hdll, "StartTcpServer");
	// ֹͣTCP����
	m_pStopTcpServer = (PStopTcpServer)GetProcAddress(m_hdll, "StopTcpServer");
	// ͨ������˷���TCP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
	m_pSendTcpDataByServerConnection = (PSendTcpDataByServerConnection)GetProcAddress(m_hdll, "SendTcpDataByServerConnection");
	// ͨ������˽���TCP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
	m_pRecvTcpDataByServerConnection = (PRecvTcpDataByServerConnection)GetProcAddress(m_hdll, "RecvTcpDataByServerConnection");
	// ͨ���ͻ��˷���TCP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
	m_pSendTcpDataByClient = (PSendTcpDataByClient)GetProcAddress(m_hdll, "SendTcpDataByClient");
	// ͨ���ͻ��˷���TCP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
	m_pSendTcpDataByClientConnection = (PSendTcpDataByClientConnection)GetProcAddress(m_hdll, "SendTcpDataByClientConnection");
	// ͨ���ͻ��˽���TCP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
	m_pRecvTcpDataByClientConnection = (PRecvTcpDataByClientConnection)GetProcAddress(m_hdll, "RecvTcpDataByClientConnection");

	// �ϴ�Http/Https���� 
	//m_pPostHttpData = (PPostHttpData)GetProcAddress(m_hdll, "PostHttpData");
	m_pPostHttpData = (PPostHttpData)GetProcAddress(m_hdll, "PostDataToServer");
	// ����HttpЭ������
	m_pGetHttpData = (PGetHttpData)GetProcAddress(m_hdll, "GetHttpDataFromUtf8");
	// ����Http��Https���ļ�����
	m_pDownloadDataFromServer = (PDownloadDataFromServer)GetProcAddress(m_hdll, "DownloadDataFromServer");

	// WebSock�ͻ���
	m_pCreateWebSockClient = (PCreateWebSockClient)GetProcAddress(m_hdll, "CreateWebSockClient");
	// ����WebSock�ͻ�������(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
	m_pSendDataByWebSockClient = (PSendDataByWebSockClient)GetProcAddress(m_hdll, "SendDataByWebSockClient");
	// ����WebSock�ͻ�������(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
	m_pCloseWebSockClient = (PCloseWebSockClient)GetProcAddress(m_hdll, "CloseWebSockClient");

	// �������ѹ���ļ�
	m_pUnzipFile = (PUnzipFile)GetProcAddress(m_hdll, "UnzipFile");
	// ���ļ���ѹ���ļ���
	m_pUnzipFileToPath = (PUnzipFileToPath)GetProcAddress(m_hdll, "UnzipFileToPath");

}

// �ͷŵײ�ͨѶ�ӿ�ģ��
void CCommInterface::FreeCommModule()
{
	if (m_hdll) FreeLibrary(m_hdll);
	m_hdll = 0;
	// ����UDP����
	m_pStartUdpServer = 0;
	// ֹͣUDP����
	m_pStopUdpServer = 0;
	// ����UDP����
	m_pSendUdpData = 0;
	// ����UDP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
	m_pSendUdpDataByServer = 0;

	// ����TCP����
	m_pStartTcpServer = 0;
	// ֹͣTCP����
	m_pStopTcpServer = 0;
	// ͨ������˷���TCP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
	m_pSendTcpDataByServerConnection = 0;
	// ͨ������˽���TCP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
	m_pRecvTcpDataByServerConnection = 0;

	// �ϴ�Http/Https����
	m_pPostHttpData = 0;
	// ����HttpЭ������
	m_pGetHttpData = 0;

	// WebSock�ͻ���
	m_pCreateWebSockClient = 0;
	// ����WebSock�ͻ�������(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
	m_pSendDataByWebSockClient = 0;
	// ����WebSock�ͻ�������(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
	m_pCloseWebSockClient = 0;
}


// ����UDP����
int CCommInterface::StartUdpServer(int nPort, PSTARTUDPSERVERCALLBACKFUN pFun, void *pCallbackParam)
{
	if (!m_hdll)
	{
		InstallCommModule();
	}
	if (m_pStartUdpServer)
	{
		return m_pStartUdpServer(nPort, pFun, pCallbackParam);
	}
	return -1;
}

// ֹͣUDP����
void CCommInterface::StopUdpServer()
{
	if (!m_hdll)
	{
		InstallCommModule();
	}
	if (m_pStopUdpServer)
	{
		m_pStopUdpServer();
	}
}

// ����UDP����
int CCommInterface::SendUdpData(char *sRemoteIp, int nRemotePort, void *pBuf, int nBufLen)
{
	if (!m_hdll)
	{
		InstallCommModule();
	}
	if (m_pSendUdpData)
	{
		return m_pSendUdpData(sRemoteIp, nRemotePort, pBuf, nBufLen);
	}
	return -1;
}

// ����UDP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
int CCommInterface::SendUdpDataByServer(char *sRemoteIp, int nRemotePort, void *pBuf, int nBufLen)
{
	if (!m_hdll)
	{
		InstallCommModule();
	}
	if (m_pSendUdpDataByServer)
	{
		return m_pSendUdpDataByServer(sRemoteIp, nRemotePort, pBuf, nBufLen);
	}
	return -1;
}

// ����TCP����
int CCommInterface::StartTcpServer(int nPort, PSTARTTCPSERVERCALLBACKFUN pFun, void *pCallbackParam)
{
	if (!m_hdll)
	{
		InstallCommModule();
	}
	if (m_pStartTcpServer)
	{
		return m_pStartTcpServer(nPort, pFun, pCallbackParam);
	}
	return -1;
}

// ֹͣTCP����
void CCommInterface::StopTcpServer()
{
	if (!m_hdll)
	{
		InstallCommModule();
	}
	if (m_pStopTcpServer)
	{
		return m_pStopTcpServer();
	}
}

// ͨ������˷���TCP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
int CCommInterface::SendTcpDataByServerConnection(void *pConnect, void *pBuf, int nBufLen)
{
	if (!m_hdll)
	{
		InstallCommModule();
	}
	if (m_pSendTcpDataByServerConnection)
	{
		return m_pSendTcpDataByServerConnection(pConnect, pBuf, nBufLen);
	}
	return -1;
}

// ͨ������˽���TCP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
int CCommInterface::RecvTcpDataByServerConnection(void *pConnect, void *pBuf, int nBufLen)
{
	if (!m_hdll)
	{
		InstallCommModule();
	}
	if (m_pRecvTcpDataByServerConnection)
	{
		return m_pRecvTcpDataByServerConnection(pConnect, pBuf, nBufLen);
	}
	return -1;
}

// ͨ���ͻ��˷���TCP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
int CCommInterface::SendTcpDataByClient(void *pCallbackParam, char *pRemoteIp, int nRemotePort, PSTARTTCPCLIENTCALLBACKFUN pFun, void *pBuf, int nBufLen)
{
	if (!m_hdll)
	{
		InstallCommModule();
	}
	if (m_pSendTcpDataByClient)
	{
		return m_pSendTcpDataByClient(pCallbackParam, pRemoteIp, nRemotePort, pFun, pBuf, nBufLen);
	}
	return -1;
}

// ͨ���ͻ��˷���TCP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
int CCommInterface::SendTcpDataByClientConnection(void *pSreamSocket, void *pBuf, int nBufLen)
{
	if (!m_hdll)
	{
		InstallCommModule();
	}
	if (m_pSendTcpDataByClientConnection)
	{
		return m_pSendTcpDataByClientConnection(pSreamSocket, pBuf, nBufLen);
	}
	return -1;
}

// ͨ���ͻ��˽���TCP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
int CCommInterface::RecvTcpDataByClientConnection(void *pSreamSocket, void *pBuf, int nBufLen)
{
	if (!m_hdll)
	{
		InstallCommModule();
	}
	if (m_pRecvTcpDataByClientConnection)
	{
		return m_pRecvTcpDataByClientConnection(pSreamSocket, pBuf, nBufLen);
	}
	return -1;
}

// �ϴ�Http����
int CCommInterface::PostHttpData(const char *sUrl, const char *strSource, int nSourceLen, char *strRet, int nSize, int &nState, const char *strContentType)
{
	if (!m_hdll)
	{
		InstallCommModule();
	}
	if (m_pPostHttpData)
	{
		std::string strC;
		if (strContentType)
		{
			strC = strContentType;
		}
		if (strC.empty())
		{
			strC = "text/html,application/xhtml+xml,*/*";
		}
		return m_pPostHttpData(sUrl, strSource, nSourceLen, strC.c_str(), strRet, nSize, nState);
	}
	return -1;
}

// ����Http����
int WINAPI CCommInterface::GetHttpData(const char *sUrl, char *strRet, int nSize, int &nState)
{
	if (!m_hdll)
	{
		InstallCommModule();
	}
	if (m_pGetHttpData)
	{
		return m_pGetHttpData(sUrl, strRet, nSize, nState);
	}
	return -1;
}

// ����Http��Https���ļ�����
int WINAPI CCommInterface::DownloadDataFromServer(const char *sUrl, char *strFileName, int &nState)
{
	if (!m_hdll)
	{
		InstallCommModule();
	}
	if (m_pDownloadDataFromServer)
	{
		return m_pDownloadDataFromServer(sUrl, strFileName, nState);
	}
	return -1;
}

// WebSock�ͻ���
// WebSock�ͻ���
int WINAPI CCommInterface::CreateWebSockClient(const char *sUrl, const void *pCallbackParam, PWEBSOCKCLIENTCALLBACKFUN pFun, PWEBSOCKCLIENTONRECV pOnRecv, PWEBSOCKCLIENTCALLBACKFUN pOnClose, PWEBSOCKCLIENTCALLBACKFUN pOnFail)
{
	if (!m_hdll)
	{
		InstallCommModule();
	}
	if (m_pCreateWebSockClient)
	{
		return m_pCreateWebSockClient(sUrl, pCallbackParam, pFun, pOnRecv, pOnClose, pOnFail);
	}
	return -1;
}
// ����WebSock�ͻ�������(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
int WINAPI CCommInterface::SendDataByWebSockClient(const void *pWebSock, const void *pBuf, int nBufLen)
{
	if (!m_hdll)
	{
		InstallCommModule();
	}
	if (m_pSendDataByWebSockClient)
	{
		return m_pSendDataByWebSockClient(pWebSock, pBuf, nBufLen);
	}
	return -1;
}

// ����WebSock�ͻ�������(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
void WINAPI CCommInterface::CloseWebSockClient()
{
	if (!m_hdll)
	{
		InstallCommModule();
	}
	if (m_pCloseWebSockClient)
	{
		m_pCloseWebSockClient();
	}
}

// �������ѹ���ļ�
int WINAPI CCommInterface::UnzipFile(const char *szBuf, int nBufLen, const char *szFileName, char *szDestFileName, int nDestFileLen)
{
	if (!m_hdll)
	{
		InstallCommModule();
	}
	if (m_pUnzipFile)
	{
		return m_pUnzipFile(szBuf, nBufLen, szFileName, szDestFileName, nDestFileLen);
	}
	return -1;
}
// ���ļ���ѹ���ļ���
int WINAPI CCommInterface::UnzipFileToPath(const char *szZipName, const char *szPathName)
{
	if (!m_hdll)
	{
		InstallCommModule();
	}
	if (m_pUnzipFileToPath)
	{
		return m_pUnzipFileToPath(szZipName, szPathName);
	}
	return -1;
}
