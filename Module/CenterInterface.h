/******************************************************************************
* ��Ȩ���� (C)2012, Sandongcun������
*
* �ļ����ƣ�centerinterface.h
* ����ժҪ�����Ľӿ�
* ����˵����
* ��ǰ�汾��v1.0
* ��    �ߣ�����
* ������ڣ�2014.7.28
* �޸ļ�¼��
* 1.
* �޸����ڣ�
* �� �� �ţ�
* �� �� �ˣ�
* �޸����ݣ�
******************************************************************************/
#pragma once
#include "gclass.h"
#include "WebSocket.h"
#include "CommonStruct.h"

#pragma pack(1)
typedef struct tag_WY_COMMU_HEAD
{
	UINT32	_head_flag;			//��ͷ
	INT32	_seq_no;			//�������ɣ���Ӧ��ԭֵ����  ������������ģ��������Ƿ�����ֱ������
	UINT32	_command_id;		// ָ��ID
	UINT32	_data_len;			//������ͷ���ȣ�����Ϣ��ʱ������Ϊ0
	UINT32	_checksum;			//Ԥ��checksum���Ժ�У��
}CCommonTCPPacket;

#pragma pack()	//	end #pragma pack(1)



class CCenterInterface
{
public:
	///////////////////////////////////////////////////////////////////////////////////////////////////
	// ��ȡ��Դ�ӿ�
	///////////////////////////////////////////////////////////////////////////////////////////////////
	// �ϴ���������
	static string UploadInfo();
	// �ϴ���Ϸ����
	static string UploadGameInfo(string strGameId, string strGameName);
	//// ������Դ�ļ�������
	//static string DownloadFile(const string &strUrl, const string &strFileName);

public:
	CCenterInterface();
	~CCenterInterface();
private:
	// ��ȡWebSocket����URL�Ͳ���
	static string GetWSUrlParam();
	// ��ȡHttp����
	static string GetHttpData(const string &strUrl, map<string, string>mapParam, bool bBigRet = false, bool bIsPost = false);
	// ��ȡHttp������������
	static string GetHttpDataUrl(const string &strPath);
	// �ص�����ָ������
	// ������
	//   pCallbackParam - �����ص��������ϲ������
	//   pSreamSocket	- ������SreamSocket����ָ�룻
	//   pRemoteIp		- �������е�Զ��Ip��
	//   nRemotePort	- �������е�Զ�̶˿ڣ�
	static void WINAPI ClientProcTcpConnect(void *pCallbackParam, void *pSreamSocket, char *pSendBuf, int nBufLen);
};

