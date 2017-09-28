/******************************************************************************
* ��Ȩ���� (C)2012, Sandongcun������
*
* �ļ����ƣ�configfile.h
* ����ժҪ������ģ��
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

typedef struct tag_MEM_CONFIG_INFO_STRUCT
{
	// clientId
	char clientId[20];
	// ����Ip
	char localIp[16];
	// �������
	char agencyId[40];
	// �ϴ�URL
	char szUploadUrl[512];            
	// �˵�����
	char szMenuName[40];
}CLIENT_CONFIG_INFO, *LP_CLIENT_CONFIG_INFO, *P_CLIENT_CONFIG_INFO;

class CConfigFile :
	public CSafeSingle<CConfigFile>
{
public:
	// ��ȡ����ƽ̨�ļ�ȫ��
	string GetDownloadPlatformPathNameA(){ return m_strDownloadPlatformPathName; }
	wstring GetDownloadPlatformPathName(){ return MultCharToWideCharA(m_strDownloadPlatformPathName.c_str(), m_strDownloadPlatformPathName.size()); }
	// ��ȡ��ǰƽ̨�ļ�ȫ��
	wstring GetCurPlatformPathName(){ return MultCharToWideCharA(m_strPlatformPathName.c_str(), m_strPlatformPathName.size()); }
	// ��ȡ��ǰƽ̨�ļ��汾
	wstring GetCurPlatformVer(){ return MultCharToWideCharA(m_strPlatformFileVer.c_str(), m_strPlatformFileVer.size()); }
	// ��ȡ��ǰƽ̨�ļ��汾
	string GetCurPlatformVerA(){ return m_strPlatformFileVer; }
	// ��ȡ��Ϸ��
	string GetGameDbPathNameA(){ return m_strGameDbPathName; }
	// ��Ϸ���Ϳ�
	string GetGameTypeDbPathNameA(){ return m_strTypeDbPathName; }
	// ��ȡ��λ��
	string GetIndexDbPathNameA(){ return m_strIndexDbPathName; }
	// ��ȡ����Id
	string GetAgencyId() { return m_strAgencyId; }
	// ��ȡClientId
	string GetClientId() { return m_strClientId; }
	// ��ȡ����IP
	string GetLocalIp() { return m_strIp; }
	// ��ȡ�ϴ�URL
	string GetUploadUrl() { return m_strUploadUrl; }
	// ��ȡ�˵�����
	string GetMenuName(){ return m_strMenuName; }

	// ��ȡƤ���б�
	bool GetClientSkinNameList(list<wstring> &ltSkin);
	// ��ȡƤ���б�·��
	string GetSkinPath();
	wstring GetSkinPathW();
	// ��ȡ��ǰƤ��·��
	std::wstring GetCurSkin(){ return m_strCurSkin; }
	// ���õ�ǰƤ��·��
	void SetCurSkin(const wchar_t *strSkin);

	// ����Ƥ��
	void AddSkin(const wchar_t *szSkin);
	// ɾ��Ƥ��
	void DeleteSkin(const wchar_t *szSkin);
public:
	// ת��Ϊ����·��
	static void SwitchAbsPath(string &strPath);
public:
	//// ���ݿ���������Ip��
	//string GetDbIp(){ return m_strHostName; }
	//// ���ݿ��û���
	//string GetDbUserName(){ return m_strUserName; }
	////���ݿ��û�����
	//string GetDbUserPass(){ return m_strPassword; }
	//// ���ݿ���
	//string GetDbName(){ return m_strDbName; }

	// ���ɷ�������˿�
	int GetServerUdpPort(){ return atoi(m_strServerUdpPort.c_str()); }
	string GetServerUdpPortStr(){ return m_strServerUdpPort; }
	//// ���ɷ�������˿�
	//int GetServerTcpPort(){ return atoi(m_strServerTcpPort.c_str()); }
	//string GetServerTcpPortStr(){ return m_strServerTcpPort; }
	//// ע��ӿ�URL
	//string GetRegeditAddr(){ return m_strRegeditAddr; }
	// ����˰汾
	string GetServerVer(){ return m_strServerVer; }
	void SetServerVer(string &strServerVer){ m_strServerVer = strServerVer; }
	// �ͻ��˰汾
	string GetClientVer(){ return m_strClientVer; }
	void SetClientVer(string &strClientVer){ m_strClientVer = strClientVer; }
	// �˵��汾
	string GetMenuVer() { return m_strMenuVer; }

	// ��ȡ��ͼ��Դ�ļ�·��
	string GetImageFilePath(){ return m_strImagePath; }
	wstring GetImageFilePathW(){ return MultCharToWideCharA(m_strImagePath.c_str(), m_strImagePath.size()); }
	// ��ȡLOGO��Դ�ļ�·��
	string GetLogoFilePath(){ return m_strLogoPath; }
	wstring GetLogoFilePathW(){ return MultCharToWideCharA(m_strLogoPath.c_str(), m_strLogoPath.size()); }
	// �������������ļ�
	void LoadUpdateConfig(const string &strUpdateFileName);

	// ��ȡ����UDP�����˿�
	word GetLocalUDPListenPort(){ return m_nLocalUdpPort; }
	// ��ȡ������
	string GetLocalMachineName(){ return m_strMachineName; }
private:
	void	LoadConfig();

	// ����ȫ·����
	std::string CreateFullPathName(std::string strFileName);
	std::wstring CreateFullPathNameW(std::wstring strFileName);
	// ȡMAC,Ip
	void GetSysMacAndIp();
	// ȡӲ�̱��
	void GetSysDiskNum();
private:
	// ���ɷ�������˿�
	string m_strServerUdpPort;
	string m_strServerTcpPort;
private:
	// ��ǰƤ��·��
	std::wstring m_strCurSkin;
	// Ƥ��·���б�
	list<wstring> m_ltSkin;
	// �ϴ�URL
	string m_strUploadUrl;
	// �˵�����
	string m_strMenuName;
	// ClientID
	string m_strClientId;
	// Ip��ַ
	string m_strIp;
	// ����Id
	string  m_strAgencyId;
	// ���ݿ���������Ip��
	string m_strHostName;
	// ���ݿ��û���
	string m_strUserName;
	//���ݿ��û�����
	string m_strPassword;
	// ���ݿ���
	string m_strDbName;

	// MAC��ַ
	string	m_strMac; 
	// Ӳ�̱��
	string	m_strDiskNum; 
	// ����˰汾
	string  m_strServerVer;
	// �ͻ��˰汾
	string  m_strClientVer;
	// ͼƬ�ļ�·��
	string  m_strImagePath; 
	// LOGO��Դ�ļ�·��
	string  m_strLogoPath; 
	// ����UDP�����˿�
	word m_nLocalUdpPort;
	// ������
	string m_strMachineName; 
	// ����ƽ̨�ļ�ȫ��
	string m_strDownloadPlatformPathName; 
	// ƽ̨�ļ�ȫ��
	string m_strPlatformPathName; 
	// ƽ̨�ļ��汾
	string m_strPlatformFileVer;
	// �˵��汾
	string m_strMenuVer;
	// ��Ϸ��
	string m_strGameDbPathName;
	// ��Ϸ���Ϳ�
	string m_strTypeDbPathName;
	// ��λ��
	string m_strIndexDbPathName;
	// ����Ƥ��
	void SaveSkin();
private:
	CConfigFile();
	~CConfigFile();
	friend class CSingle<CConfigFile>;
};

