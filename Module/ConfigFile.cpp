#include "ConfigFile.h"
#include "gfunction.h"

//#include "diskseri.h"
//#include <atlutil.h>
#include <iphlpapi.h>
#pragma comment(lib, "IPHLPAPI.lib")
#pragma comment(lib, "ws2_32")

// 服务器端配置文件名
#define CONFIG_FILENAME					"config.ini"
// 本地配置
#define CONFIG_LOCALAPP					"local"
// 本地配置
#define CONFIG_SKIN						"skin"
// 取出控制端版本
#define CONFIG_LOCAL_CONTROLVER			"1.0.0.1"
// 取出客户端版本
#define CONFIG_LOCAL_CLIENTVER			"1.0.0.1"
// tcp服务监听端口
#define CONFIG_LOCAL_TCPLISTENKEY		"tcpport"
// udp服务监听端口
#define CONFIG_LOCAL_UDPLISTENKEY		"udpport"
// 图片文件路径
#define CONFIG_LOCAL_IMAGEPATH		    "imagepath"
// 本地UDP监听端口
#define CONFIG_LOCAL_LOCALUDPLISTENPORT "udplistenport"
// 机器编号
#define CONFIG_LOCAL_MACHINENAME		"machinename"
//// 网吧注册号
//#define CONFIG_LOCAL_BARIDKEY			"barid"
//// 密码
//#define CONFIG_LOCAL_PASSKEY			"password"
//// 增值目录
//#define CONFIG_LOCAL_ADDVLAUEPATH		"addvaluepath"
//// 广告目录
//#define CONFIG_LOCAL_ADPATH 			"adpath"
//// 小程序目录
//#define CONFIG_LOCAL_MINPROGRAMPATH		"minprogrampath"
//// 升级目录
//#define CONFIG_LOCAL_UPDTAEPROGRAMPATH  "updatepath"
//// 客户端退出密码
//#define CONFIG_CENTER_CLIENTEXITPASSKEY	"clientexitpass"
// 游戏库
#define CONFIG_GAMEMENU_GAMEFILE	"gamedb"
// 游戏类型库
#define CONFIG_GAMETYPE_INDEXFILE	"typedb"
// 排位库
#define CONFIG_GAMEMENU_INDEXFILE	"indexdb"

// 皮肤个数
#define CONFIG_SKIN_COUNT			"count"
// 皮肤路径
#define CONFIG_SKIN_PATH			"path"

// 服务端版本
const char *g_constServerVer = "1.0.0.0";

template <> CConfigFile *CSingle<CConfigFile>::m_pInstance = 0;

CConfigFile::CConfigFile()
{
	LoadConfig();
}


CConfigFile::~CConfigFile()
{
}

std::string GetIpFromUrl(const std::string &strUrl)
{
	std::string strRet;
	return strRet;
}

// 转换为绝对路径
void CConfigFile::SwitchAbsPath(string &strPath)
{
	string s(strPath);
	strPath = CConfigFile::GetInstance()->CreateFullPathName(s);
}

// 获取皮肤列表
bool CConfigFile::GetClientSkinNameList(list<wstring> &ltSkin)
{
	if (m_ltSkin.empty())
	{
		char szTemp[MAX_PATH] = { 0 };
		string strFileName = CreateFullPathName(CONFIG_FILENAME);
		// 获取皮肤个数
		int nCount = GetPrivateProfileIntA(CONFIG_SKIN, CONFIG_SKIN_COUNT, 0, strFileName.c_str());
		string strSkinName = "skin";
		for (int i = 0; i < nCount; i++)
		{
			string strKey(strSkinName);
			strKey += IntToStr(i);
			GetPrivateProfileStringA(CONFIG_SKIN, strKey.c_str(), "", szTemp, MAX_PATH - 1, strFileName.c_str());
			string strValue = szTemp;
			strValue = CreateFullPathName(strValue);
			m_ltSkin.push_back(MultCharToWideCharA(strValue.c_str(), strValue.size()));
		}
	}
	ltSkin = m_ltSkin;
	return true;
}

// 获取皮肤列表路径
string CConfigFile::GetSkinPath()
{
	char szTemp[MAX_PATH] = { 0 };
	string strFileName = CreateFullPathName(CONFIG_FILENAME);
	// 获取皮肤路径
	GetPrivateProfileStringA(CONFIG_SKIN, CONFIG_SKIN_PATH, "\\Skin", szTemp, MAX_PATH - 1, strFileName.c_str());
	string strPath = szTemp;
	return CreateFullPathName(strPath);
}
wstring CConfigFile::GetSkinPathW()
{
	string strPath = GetSkinPath();
	return MultCharToWideCharA(strPath.c_str(), strPath.size());
}

// 增加皮肤
void CConfigFile::AddSkin(const wchar_t *szSkin)
{
	wstring strSkin = szSkin;
	m_ltSkin.push_back(strSkin);
	if (strSkin.empty())
	{
		return;
	}
	// 保存皮肤
	SaveSkin();
}

// 删除皮肤
void CConfigFile::DeleteSkin(const wchar_t *szSkin)
{
	wstring s = szSkin;
	m_ltSkin.remove(s);
	// 保存皮肤
	SaveSkin();
}

// 保存皮肤
void CConfigFile::SaveSkin()
{
	string strFileName = CreateFullPathName(CONFIG_FILENAME);
	::WritePrivateProfileStringA(CONFIG_SKIN, CONFIG_SKIN_COUNT, IntToStr(m_ltSkin.size()).c_str(), strFileName.c_str());
	int i = 0;
	for (auto it : m_ltSkin)
	{
		string strKey = "skin";
		strKey += IntToStr(i++);
		string strSkinA = WideCharToMultiCharW(it.c_str(), it.size());
		::WritePrivateProfileStringA(CONFIG_SKIN, strKey.c_str(), strSkinA.c_str(), strFileName.c_str());
	}
}

void CConfigFile::LoadConfig()
{
	char szTemp[MAX_PATH] = { 0 };
	string strFileName = CreateFullPathName(CONFIG_FILENAME);
	// 获取机器名
	GetPrivateProfileStringA(CONFIG_LOCALAPP, CONFIG_LOCAL_MACHINENAME, "", szTemp, MAX_PATH - 1, strFileName.c_str());
	m_strMachineName = szTemp;
	if (m_strMachineName.empty())
	{
		// 机器名
		std::string strName;
		char szComputerName[51] = { 0 };
		DWORD dwSize = 50;
		::GetComputerNameA(szComputerName, &dwSize);
		m_strMachineName = szComputerName;
	}
	// 下载平台文件全名
	m_strDownloadPlatformPathName = GetModulePath();
	m_strDownloadPlatformPathName += "BarPlatform.exe";


	m_strPlatformPathName = GetModulePath();
	m_strPlatformPathName = m_strPlatformPathName.substr(0, m_strPlatformPathName.size() - 1);
	int nF = m_strPlatformPathName.rfind('\\');
	if (nF != string::npos)
	{
		m_strPlatformPathName = m_strPlatformPathName.substr(0, nF + 1);
		m_strPlatformPathName += "BarPlatform.exe";
		m_strPlatformFileVer = GetFileVersionEx(m_strPlatformPathName);
	}
	m_strMenuVer = GetFileVersionEx();

	// 获取本地UDP监听端口
	GetPrivateProfileStringA(CONFIG_LOCALAPP, CONFIG_LOCAL_LOCALUDPLISTENPORT, "7000", szTemp, MAX_PATH - 1, strFileName.c_str());
	m_nLocalUdpPort = StrToInt(szTemp, 7000);
	// 取出客户端版本
	GetPrivateProfileStringA(CONFIG_LOCALAPP, CONFIG_LOCAL_CLIENTVER, "1.0.0.1", szTemp, MAX_PATH - 1, strFileName.c_str());
	 m_strClientVer = szTemp;
	// 取出tcp服务监听端口
	GetPrivateProfileStringA(CONFIG_LOCALAPP, CONFIG_LOCAL_TCPLISTENKEY, "7070", szTemp, MAX_PATH - 1, strFileName.c_str());
	m_strServerTcpPort = szTemp;
	// 取出udp服务监听端口
	GetPrivateProfileStringA(CONFIG_LOCALAPP, CONFIG_LOCAL_UDPLISTENKEY, "7070", szTemp, MAX_PATH - 1, strFileName.c_str());
	m_strServerUdpPort = szTemp;
	// 图片文件路径
	GetPrivateProfileStringA(CONFIG_LOCALAPP, CONFIG_LOCAL_IMAGEPATH, "", szTemp, MAX_PATH - 1, strFileName.c_str());
	m_strImagePath = szTemp;

	if (m_strImagePath.empty())
	{
		m_strImagePath = "\\image";
		m_strImagePath = CreateFullPathName(m_strImagePath);
	}
	// 取硬盘编号
	GetSysDiskNum();

	// 游戏库
	GetPrivateProfileStringA(CONFIG_LOCALAPP, CONFIG_GAMEMENU_GAMEFILE, "\\Game\\game.txt", szTemp, MAX_PATH - 1, strFileName.c_str());
	m_strGameDbPathName = szTemp;

	if (m_strGameDbPathName.empty())
	{
		m_strGameDbPathName = "\\dbpath";
		m_strGameDbPathName = CreateFullPathName(m_strGameDbPathName);
		m_strGameDbPathName += "\\gamedbpath.txt";
	}
	else
	{
		m_strGameDbPathName = CreateFullPathName(m_strGameDbPathName);
	}
	// 游戏类型库
	GetPrivateProfileStringA(CONFIG_LOCALAPP, CONFIG_GAMETYPE_INDEXFILE, "\\Game\\type.txt", szTemp, MAX_PATH - 1, strFileName.c_str());
	m_strTypeDbPathName = szTemp;

	if (m_strTypeDbPathName.empty())
	{
		m_strTypeDbPathName = "\\dbpath";
		m_strTypeDbPathName = CreateFullPathName(m_strTypeDbPathName);
		m_strTypeDbPathName += "\\type.txt";
	}
	else
	{
		m_strTypeDbPathName = CreateFullPathName(m_strTypeDbPathName);
	}

	// 排位库
	GetPrivateProfileStringA(CONFIG_LOCALAPP, CONFIG_GAMEMENU_INDEXFILE, "\\Game\\index.txt", szTemp, MAX_PATH - 1, strFileName.c_str());
	m_strIndexDbPathName = szTemp;
	if (m_strIndexDbPathName.empty())
	{
		m_strIndexDbPathName = "\\dbpath";
		m_strIndexDbPathName = CreateFullPathName(m_strIndexDbPathName);
		m_strIndexDbPathName += "\\indexdbpath.txt";
	}
	else
	{
		m_strIndexDbPathName = CreateFullPathName(m_strIndexDbPathName);
	}


	HANDLE h = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, L"BarPlatform Config Struct Map");
	if (h)
	{
		CLIENT_CONFIG_INFO *pBuf = (CLIENT_CONFIG_INFO *)MapViewOfFile(h, // handle to map object
			FILE_MAP_ALL_ACCESS,  // read/write permission
			0,
			0,
			512);

		string strTemp;
		if (pBuf)
		{
			m_strClientId = pBuf->clientId;
			m_strIp = pBuf->localIp;
			m_strAgencyId = pBuf->agencyId;
			// 菜单名称
			m_strMenuName = pBuf->szMenuName;
			m_strUploadUrl = pBuf->szUploadUrl;
		}
		CloseHandle(h);
	}
	if (m_strClientId.empty())
	{
		string strPFileName = CreateFullPathName("param.ini");
		GetPrivateProfileStringA("platform", "clientid", "", szTemp, MAX_PATH - 1, strPFileName.c_str());
		m_strClientId = szTemp;
	}
	if (m_strIp.empty())
	{
		string strPFileName = CreateFullPathName("param.ini");
		GetPrivateProfileStringA("platform", "localip", "", szTemp, MAX_PATH - 1, strPFileName.c_str());
		m_strIp = szTemp;
	}
	if (m_strAgencyId.empty())
	{
		string strPFileName = CreateFullPathName("param.ini");
		GetPrivateProfileStringA("platform", "agencyid", "", szTemp, MAX_PATH - 1, strPFileName.c_str());
		m_strAgencyId = szTemp;
	}
	if (m_strUploadUrl.empty())
	{
		string strPFileName = CreateFullPathName("param.ini");
		GetPrivateProfileStringA("platform", "uploadurl", "", szTemp, MAX_PATH - 1, strPFileName.c_str());
		m_strUploadUrl = szTemp;
	}
	if (m_strMenuName.empty())
	{
		string strPFileName = CreateFullPathName("param.ini");
		GetPrivateProfileStringA("platform", "menuname", "", szTemp, MAX_PATH - 1, strPFileName.c_str());
		m_strMenuName = szTemp;
	}

	if (m_strUploadUrl.empty())
	{
		m_strUploadUrl = "https://106.14.45.195:8443/";
		// 取MAC,Ip
		GetSysMacAndIp();
		m_strClientId = m_strMac;
	}
	if (m_strMenuName.empty())
	{
		m_strMenuName = "Myoubox游戏菜单";
	}
}

// 生成全路径名
std::string CConfigFile::CreateFullPathName(std::string strFileName)
{
	std::string strPath = strFileName;
	if (strPath.find(':') == string::npos)
	{
		// 相对路径
		int nOff(0);
		if (strFileName[0] != '\\' && strFileName[0] != '/')
		{
			nOff = 1;
		}
		char szName[MAX_PATH] = { 0 };
		::GetModuleFileNameA(0, szName, MAX_PATH - 1);
		strPath = szName;
		int nIndex = strPath.rfind('\\');
		if (nIndex < 0) nIndex = strPath.rfind('/');
		strPath = strPath.substr(0, nIndex + nOff);
		strPath += strFileName;
	}
	if (strPath.size() > 0)
	{
		if (strPath[strPath.size() - 1] == '\\' || strPath[strPath.size() - 1] == '/')
		{
			strPath = strPath.substr(0, strPath.size() - 1);
		}
	}
	return strPath;
}
std::wstring CConfigFile::CreateFullPathNameW(std::wstring strFileName)
{
	std::wstring strPath = strFileName;
	if (strPath.find(L':') != 0)
	{
		// 相对路径
		int nOff(0);
		if (strFileName[0] != L'\\' && strFileName[0] != L'/')
		{
			nOff = 1;
		}
		wchar_t szName[MAX_PATH] = { 0 };
		::GetModuleFileName(0, szName, MAX_PATH - 1);
		strPath = szName;
		int nIndex = strPath.rfind(L'\\');
		if (nIndex < 0) nIndex = strPath.rfind(L'/');
		strPath = strPath.substr(0, nIndex + nOff);
		strPath += strFileName;
	}
	if (strPath.size() > 0)
	{
		if (strPath[strPath.size() - 1] == L'\\' || strPath[strPath.size() - 1] == L'/')
		{
			strPath = strPath.substr(0, strPath.size() - 1);
		}
	}
	return strPath;
}

// 取MAC
void CConfigFile::GetSysMacAndIp()
{
	PIP_ADAPTER_INFO pAdapterInfo, pAdapt;
	DWORD AdapterInfoSize;
	int nResult;
	AdapterInfoSize = 0;
	if ((nResult = GetAdaptersInfo(NULL, &AdapterInfoSize)) != 0)
	{
		if (nResult != ERROR_BUFFER_OVERFLOW)
		{
			return;
		}
	}
	if ((pAdapterInfo = (PIP_ADAPTER_INFO)GlobalAlloc(GPTR, AdapterInfoSize)) == NULL)
	{
		return;
	}
	if ((nResult = GetAdaptersInfo(pAdapterInfo, &AdapterInfoSize)) != 0)
	{
		GlobalFree(pAdapterInfo);
		return;
	}
	pAdapt = pAdapterInfo;
	while (pAdapt)
	{
		std::string strIpTemp = pAdapt->IpAddressList.IpAddress.String;
		if (strIpTemp.compare("0.0.0.0") == 0)
		{
			pAdapt = pAdapt->Next;
			continue;
		}
		if (pAdapt->Type == MIB_IF_TYPE_ETHERNET)
		{
			//处理虚拟网卡
			std::string strDescription;
			strDescription = pAdapt->Description;
			std::transform(strDescription.begin(), strDescription.end(), strDescription.begin(), tolower);
			if ((strDescription.find("virtual") != std::string::npos) && MIB_IF_TYPE_ETHERNET != pAdapt->Type)
			{
				pAdapt = pAdapt->Next;
				continue;
			}
			int nFindIndex = strDescription.find("vmware");
			if (nFindIndex >= 0)
			{
				pAdapt = pAdapt->Next;
				continue;
			}
			std::string strLocalIP = pAdapt->IpAddressList.IpAddress.String;
			if (strLocalIP == "0.0.0.0")
			{
				pAdapt = pAdapt->Next;
				continue;
			}
			//摄像头虚拟网卡MAC为0
			BYTE btBuffer[6] = { 0 };
			if (memcmp(pAdapt->Address, btBuffer, 6) == 0)
			{
				pAdapt = pAdapt->Next;
				continue;
			}

			int iAddressLength = min(pAdapt->AddressLength, 6);
			for (int j = 0; j < iAddressLength; j++)
			{
				btBuffer[j] = pAdapt->Address[j];
			}
			char szMac[13] = { 0 };
			sprintf_s(szMac, 13, "%02x%02x%02x%02x%02x%02x", pAdapt->Address[0], pAdapt->Address[1], pAdapt->Address[2], pAdapt->Address[3], pAdapt->Address[4], pAdapt->Address[5]);
			m_strMac = szMac;
			m_strIp = pAdapt->IpAddressList.IpAddress.String;
			break;
		}
		else if (71 == pAdapt->Type)
		{
			char szMac[13] = { 0 };
			sprintf_s(szMac, 13, "%02x%02x%02x%02x%02x%02x", pAdapt->Address[0], pAdapt->Address[1], pAdapt->Address[2], pAdapt->Address[3], pAdapt->Address[4], pAdapt->Address[5]);
			m_strMac = szMac;
			m_strIp = pAdapt->IpAddressList.IpAddress.String;
			break;
		}
		pAdapt = pAdapt->Next;
	}
	GlobalFree(pAdapterInfo);
}

// 取硬盘编号
void CConfigFile::GetSysDiskNum()
{
}


