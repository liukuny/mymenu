#pragma once

#include <tchar.h>
#include <map>

#include "..\..\..\Communication\Communication\Communication.h"

// �ײ�ͨѶ�ӿ�ģ��
//#define COMMMODULE_INTERFACEDLL_NAME _T("D:\\personalproject\\bar\\source\\Communication\\x64\\Debug\\Communication.dll")
#define COMMMODULE_INTERFACEDLL_NAME _T("..\\Communication.dll")
//#define COMMMODULE_INTERFACEDLL_NAME _T("D:\\personalproject\\bar\\source\\Communication\\Release\\Communication.dll")

// ����UDP����
typedef int(WINAPI *PStartUdpServer)(int nPort, PSTARTUDPSERVERCALLBACKFUN pFun, void *pCallbackParam);
// ֹͣUDP����
typedef void (WINAPI *PStopUdpServer)();
// ����UDP����
typedef int (WINAPI *PSendUdpData)(char *sRemoteIp, int nRemotePort, void *pBuf, int nBufLen);
// ����UDP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
typedef int (WINAPI *PSendUdpDataByServer)(char *sRemoteIp, int nRemotePort, void *pBuf, int nBufLen);

// ����TCP����
typedef int (WINAPI *PStartTcpServer)(int nPort, PSTARTTCPSERVERCALLBACKFUN pFun, void *pCallbackParam);
// ֹͣTCP����
typedef void (WINAPI *PStopTcpServer)();
// ͨ������˷���TCP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
typedef int (WINAPI *PSendTcpDataByServerConnection)(void *pConnect, void *pBuf, int nBufLen);
// ͨ������˽���TCP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
typedef int (WINAPI *PRecvTcpDataByServerConnection)(void *pConnect, void *pBuf, int nBufLen);
// ͨ���ͻ��˷���TCP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
typedef int (WINAPI *PSendTcpDataByClient)(void *pCallbackParam, char *pRemoteIp, int nRemotePort, PSTARTTCPCLIENTCALLBACKFUN pFun, void *pBuf, int nBufLen);
// ͨ���ͻ��˷���TCP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
typedef int (WINAPI *PSendTcpDataByClientConnection)(void *pSreamSocket, void *pBuf, int nBufLen);
// ͨ���ͻ��˽���TCP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
typedef int (WINAPI *PRecvTcpDataByClientConnection)(void *pSreamSocket, void *pBuf, int nBufLen);


// �ϴ�Http/Https����
typedef int (WINAPI *PPostHttpData)(const char *sUrl, const char *strSource, int nSourceLen, const char *strContentType, char *strRet, int nSize, int &nState);
// ����Http����
typedef int (WINAPI *PGetHttpData)(const char *sUrl, char *strRet, int nSize, int &nState);
// ����Http��Https���ļ�����
typedef int (WINAPI *PDownloadDataFromServer)(const char *sUrl, char *strFileName, int &nState);

// WebSock�ͻ���
typedef int (WINAPI *PCreateWebSockClient)(const char *sUrl, const void *pCallbackParam, PWEBSOCKCLIENTCALLBACKFUN pFun, PWEBSOCKCLIENTONRECV pOnRecv, PWEBSOCKCLIENTCALLBACKFUN pOnClose, PWEBSOCKCLIENTCALLBACKFUN pOnFail);
// ����WebSock�ͻ�������(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
typedef int (WINAPI *PSendDataByWebSockClient)(const void *pWebSock, const void *pBuf, int nBufLen);
// ����WebSock�ͻ�������(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
typedef void (WINAPI *PCloseWebSockClient)();

// �������ѹ���ļ�
typedef int (WINAPI *PUnzipFile)(const char *szBuf, int nBufLen, const char *szFileName, char *szDestFileName, int nDestFileLen);
// ���ļ���ѹ���ļ���
typedef int (WINAPI *PUnzipFileToPath)(const char *szZipName, const char *szPathName);

class CCommInterface
{
public:
	CCommInterface();
	~CCommInterface();
	// ��װ�ײ�ͨѶ�ӿ�ģ��
	static void InstallCommModule();
	// �ͷŵײ�ͨѶ�ӿ�ģ��
	static void FreeCommModule();

	// ����UDP����
	static int StartUdpServer(int nPort, PSTARTUDPSERVERCALLBACKFUN pFun, void *pCallbackParam);
	// ֹͣUDP����
	static void StopUdpServer();
	// ����UDP����
	static int SendUdpData(char *sRemoteIp, int nRemotePort, void *pBuf, int nBufLen);
	// ����UDP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
	static int SendUdpDataByServer(char *sRemoteIp, int nRemotePort, void *pBuf, int nBufLen);

	// ����TCP����
	static int WINAPI StartTcpServer(int nPort, PSTARTTCPSERVERCALLBACKFUN pFun, void *pCallbackParam);
	// ֹͣTCP����
	static void WINAPI StopTcpServer();
	// ͨ������˷���TCP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
	static int WINAPI SendTcpDataByServerConnection(void *pConnect, void *pBuf, int nBufLen);
	// ͨ������˽���TCP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
	static int WINAPI RecvTcpDataByServerConnection(void *pConnect, void *pBuf, int nBufLen);
	// ͨ���ͻ��˷���TCP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
	static int SendTcpDataByClient(void *pCallbackParam, char *pRemoteIp, int nRemotePort, PSTARTTCPCLIENTCALLBACKFUN pFun, void *pBuf, int nBufLen);
	// ͨ���ͻ��˷���TCP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
	static int SendTcpDataByClientConnection(void *pSreamSocket, void *pBuf, int nBufLen);
	// ͨ���ͻ��˽���TCP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
	static int RecvTcpDataByClientConnection(void *pSreamSocket, void *pBuf, int nBufLen);

	// �ϴ�Http����
	static int WINAPI PostHttpData(const char *sUrl, const char *strSource, int nSourceLen, char *strRet, int nSize, int &nState, const char *strContentType = 0);
	// ����Http����
	static int WINAPI GetHttpData(const char *sUrl, char *strRet, int nSize, int &nState);
	// ����Http��Https���ļ�����
	static int WINAPI DownloadDataFromServer(const char *sUrl, char *strFileName, int &nState);

	// WebSock�ͻ���
	static int WINAPI CreateWebSockClient(const char *sUrl, const void *pCallbackParam, PWEBSOCKCLIENTCALLBACKFUN pFun, PWEBSOCKCLIENTONRECV pOnRecv, PWEBSOCKCLIENTCALLBACKFUN pOnClose, PWEBSOCKCLIENTCALLBACKFUN pOnFail);
	// ����WebSock�ͻ�������(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
	static int WINAPI SendDataByWebSockClient(const void *pWebSock, const void *pBuf, int nBufLen);
	// ����WebSock�ͻ�������(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
	static void WINAPI CloseWebSockClient();

	// �������ѹ���ļ�
	static int WINAPI UnzipFile(const char *szBuf, int nBufLen, const char *szFileName, char *szDestFileName, int nDestFileLen);
	// ���ļ���ѹ���ļ���
	static int WINAPI UnzipFileToPath(const char *szZipName, const char *szPathName);

public:
	// �ײ�ͨѶ�ӿ�ģ��
	static HMODULE m_hdll;
	// ����UDP����
	static PStartUdpServer m_pStartUdpServer;
	// ֹͣUDP����
	static PStopUdpServer m_pStopUdpServer;
	// ����UDP����
	static PSendUdpData m_pSendUdpData;
	// ����UDP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
	static PSendUdpDataByServer m_pSendUdpDataByServer;

	// ����TCP����
	static PStartTcpServer m_pStartTcpServer;
	// ֹͣTCP����
	static PStopTcpServer m_pStopTcpServer;
	// ͨ������˷���TCP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
	static PSendTcpDataByServerConnection m_pSendTcpDataByServerConnection;
	// ͨ������˽���TCP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
	static PRecvTcpDataByServerConnection m_pRecvTcpDataByServerConnection;
	// ͨ���ͻ��˷���TCP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
	static PSendTcpDataByClient m_pSendTcpDataByClient;
	// ͨ���ͻ��˷���TCP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
	static PSendTcpDataByClientConnection m_pSendTcpDataByClientConnection;
	// ͨ���ͻ��˽���TCP����(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
	static PRecvTcpDataByClientConnection m_pRecvTcpDataByClientConnection;

	// �ϴ�Http/Https����
	static PPostHttpData m_pPostHttpData;
	// ����HttpЭ������
	static PGetHttpData m_pGetHttpData;
	// ����Http��Https���ļ�����
	static PDownloadDataFromServer m_pDownloadDataFromServer;

	// WebSock�ͻ���
	static PCreateWebSockClient m_pCreateWebSockClient;
	// ����WebSock�ͻ�������(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
	static PSendDataByWebSockClient m_pSendDataByWebSockClient;
	// ����WebSock�ͻ�������(���̰߳�ȫ��ע�ⲻҪ�ٲ�ͬ���߳������)
	static PCloseWebSockClient m_pCloseWebSockClient;

	// �������ѹ���ļ�
	static PUnzipFile m_pUnzipFile;
	// ���ļ���ѹ���ļ���
	static PUnzipFileToPath m_pUnzipFileToPath;

};

