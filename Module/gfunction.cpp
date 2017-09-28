#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fstream>
//#include <unistd.h>
//#include <net/if.h>     // struct ifreq
//#include <sys/ioctl.h>  // ioctl
//#include <netinet/in.h> // struct sockaddr_in

#include <windows.h>	// MultiByteToWideChar
#include "gfunction.h"

//----------------------------------------------------------------------------
// ����: �ж�һ���ַ����ǲ���һ������#include<ctype.h>
//----------------------------------------------------------------------------
bool IsInt(const char *pStr)
{
    if (!pStr || !pStr[0]) return false;

    if (!isdigit(pStr[0]) && (pStr[0] != '-' || strlen(pStr) == 1)) return false;

    for (int i = 1; pStr[i]; i++)
        if (!isdigit(pStr[i])) return false;

    return true;
}

//----------------------------------------------------------------------------
// ����: �ַ���ת��������(���pSrc�Ƿ�ΪNULL�����򷵻�nDefault)#include <stdlib.h>
//----------------------------------------------------------------------------
int StrToInt(const char *pStr, int nDefault)
{
    if (IsInt(pStr))
    {
        return atoi((char*)pStr);
    }
    else
        return nDefault;
}

//----------------------------------------------------------------------------
// ����: ��ʽ���ַ��� (��FormatString��������)
//----------------------------------------------------------------------------
void FormatStringV(string& strResult, const char *pFormatString, va_list argList)
{
    //int nSize = 1024;
    int nSize = 2048;
    char *pBuffer = (char *)malloc(nSize);

    while (pBuffer)
    {
        int nChars;
		nChars = vsnprintf_s(pBuffer, nSize, _TRUNCATE, pFormatString, argList);
        if (nChars > -1 && nChars < nSize)
            break;
        if (nChars > -1)
            nSize = nChars + 1;
        else
            nSize *= 2;
        pBuffer = (char *)realloc(pBuffer, nSize);
    }

    if (pBuffer)
    {
        strResult = pBuffer;
        free(pBuffer);
    }
    else
        strResult = "";
}

//----------------------------------------------------------------------------
// ����: ��ʽ���ַ���
// ����:
//   strResult      - ��Ž����
//   pFormatString  - ��ʽ���ַ���
//   ...            - ��ʽ������
// ʾ��: 
//   FormatString(strResult, "ABC%sDEF%d", strTemp, nTemp);
//----------------------------------------------------------------------------
void FormatString(string& strResult, const char *pFormatString, ...)
{
    va_list argList;
    va_start(argList, pFormatString);
    FormatStringV(strResult, pFormatString, argList);
    va_end(argList);
}

void FormatStringWV(wstring& strResult, const wchar_t *pFormatString, va_list argList)
{
	int nSize = 2048;
	wchar_t *pBuffer = (wchar_t *)malloc(nSize * sizeof(wchar_t));
	int nChars(0);
	while (pBuffer)
	{
		nChars = _vsnwprintf_s(pBuffer, nSize, _TRUNCATE, pFormatString, argList);
		if (nChars > -1 && nChars < nSize)
		{
			break;
		}
		if (nChars > -1)
		{
			nSize = nChars + 1;
		}
		else
		{
			nSize *= 2;
		}
		pBuffer = (wchar_t *)realloc(pBuffer, nSize * sizeof(wchar_t));
	}

	if (pBuffer)
	{
		pBuffer[nChars] = 0;
		strResult = wstring(pBuffer, nChars);
		free(pBuffer);
	}
	else
		strResult = L"";
}

void FormatStringW(wstring& strResult, const wchar_t *pFormatString, ...)
{
	va_list argList;
	va_start(argList, pFormatString);
	FormatStringWV(strResult, pFormatString, argList);
	va_end(argList);
}

//----------------------------------------------------------------------------
// ����: ����ת�����ַ���
//----------------------------------------------------------------------------
string IntToStr(int nValue)
{
    char sTemp[64];
    sprintf_s(sTemp, 64, "%d", nValue);
    return sTemp;
}

//----------------------------------------------------------------------------
// ����: �ַ����滻
// ����:
//   pStr   - Դ�ַ���
//   nSize  - Դ�ַ�����������С
//   pFrom  - Ҫ���滻�����ַ���
//   pTo    - Ҫ�滻�ɵ��ַ���
// ����:
//   >=0    - ���ַ�����Դ���е�λ��(0-based)
//   -1     - ���ַ���û�ҵ�
//----------------------------------------------------------------------------
int StringReplace(char *pStr, int nSize, char *pFrom, char *pTo)
{
    char *p;
    int nFromLen, nToLen, nMaxLen;

    p = strstr(pStr, pFrom);
    if (!p) return -1;

    nFromLen = strlen(pFrom);
    nToLen = strlen(pTo);
    nMaxLen = ((nFromLen > nToLen)? nFromLen : nToLen);

    memmove(p + nToLen, p + nFromLen, nSize - (p - pStr) - nMaxLen);
    memmove(p, pTo, nToLen);
    pStr[nSize - 1] = 0;

    return p - pStr;
}

//----------------------------------------------------------------------------
// ����: �ָ��ַ���
// ����:
//   pStr       - string which will be splited
//   pSplitter  - pSplitter string
//   pStrList   - store split results
//   nListSize  - specify the nSize of pStrList
//   nCount     - split result string nCount
// ����:
//   = (*nCount)
//----------------------------------------------------------------------------
int StringSplit(const char *pStr, const char *pSplitter, char *pStrList[], 
    int nListSize, int *nCount)
{
    const char *p;
    int nSpLen;

    if (!pStr || strlen(pStr) == 0 || strlen(pSplitter) == 0)
    {
        *nCount = 0;
        return *nCount;
    }

    nSpLen = strlen(pSplitter);
    *nCount = 1;

    while (*nCount - 1 < nListSize)
    {
        pStrList[*nCount - 1] = (char*)pStr;
        p = strstr(pStr, pSplitter);
        if (p)
        {
            pStr = p + nSpLen;
            (*nCount)++;
        }
        else 
        {
            break;
        }
    }

    if (*nCount > nListSize) *nCount = nListSize;
    return *nCount;
}

//----------------------------------------------------------------------------
// ����: split string pTo integer numbers
// ����:
//   pStr       - string that will be splited
//   pSplitter  - pSplitter string
//   pIntList   - store split results
//   nListSize  - specify the nSize of pIntList
//   nCount     - split result string nCount
// ����:
//   = (*nCount)
// ��ע: 
//   max nSize of integer list is 128.
//----------------------------------------------------------------------------
int StringSplitToInt(const char *pStr, const char *pSplitter, int pIntList[], 
    int nListSize, int *nCount)
{
    char *pStrList[128];
    int i;
    
    StringSplit(pStr, pSplitter, pStrList, 128, nCount);
    
    for (i = 0; i < *nCount && i < nListSize; i++)
        pIntList[i] = atoi(pStrList[i]);

    if (*nCount > nListSize) *nCount = nListSize;
    return *nCount;
}


////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
// ����: ����ļ��Ƿ����
//----------------------------------------------------------------------------
bool FileExists(const string& strDir)
{
    bool bResult;
    struct _stat st;
	memset(&st, 0, sizeof(st));

    if (_stat(strDir.c_str(), &st) == 0)
        bResult = ((st.st_mode & S_IFREG) == S_IFREG);
    else
        bResult = false;

    return bResult;
}


//----------------------------------------------------------------------------
// ����: ���Ŀ¼�Ƿ����
//----------------------------------------------------------------------------
bool DirectoryExists(const string& strDir)
{
	bool bResult;
	struct _stat st;
	memset(&st, 0, sizeof(st));

    if (_stat(strDir.c_str(), &st) == 0)
        bResult = ((st.st_mode & S_IFDIR) == S_IFDIR);
    else
        bResult = false;

    return bResult;
}

//----------------------------------------------------------------------------
// ����: ����Ŀ¼
// ʾ��: CreateDir("/home/test");
//----------------------------------------------------------------------------
bool CreateDir(const string& strDir)
{
	//MakeSureDirectoryPathExists();
	SECURITY_ATTRIBUTES attrib;
	attrib.bInheritHandle = FALSE;
	attrib.lpSecurityDescriptor = NULL;
	attrib.nLength = sizeof(SECURITY_ATTRIBUTES);
	return !!CreateDirectoryA(strDir.c_str(), &attrib);
}

//----------------------------------------------------------------------------
// ����: ���ļ�����ȡ���ļ�·��
// ����:
//   strFileName - ����·�����ļ���
// ����:
//   �ļ���·��
// ʾ��:
//   ExtractFilePath("/home/user1/data/test.c");
//   ������: "/home/user1/data/"
//----------------------------------------------------------------------------
string ExtractFilePath(const string& strFileName)
{
    int nLen, nPos;
    string strResult;

    nLen = strFileName.length();
    nPos = -1;
    for (int i = nLen - 1; i >= 0; i--)
    {
        if (strFileName[i] == '/')
        {
            nPos = i;
            break;
        }
    }

    if (nPos != -1)
        strResult = strFileName.substr(0, nPos + 1);
    else
        strResult = "";

    return strResult;
}

//----------------------------------------------------------------------------
// ����: ǿ�ƴ���Ŀ¼
// ����: 
//   strDir - ��������Ŀ¼ (�����Ƕ༶Ŀ¼)
// ����:
//   true   - �ɹ�
//   false  - ʧ��
// ʾ��:
//   ForceDirectories("/home/user1/data");
//----------------------------------------------------------------------------
bool ForceDirectories(string strDir)
{
	if (strDir.rfind('.') == strDir.size() - 4)
	{
		int n = strDir.rfind('/');
		if (n < 0) n = strDir.rfind('\\');
		strDir.resize(n);
	}
	if (DirectoryExists(strDir))
	{
		return true;
	}
    int nLen = strDir.rfind('/');
	if (nLen < 0) nLen = strDir.rfind('\\');

	if (strDir.empty() || nLen < 0)
	{
		return false;
	}
	string strSub(strDir);
	strSub.resize(nLen);

	if (DirectoryExists(strSub))
	{
		return CreateDir(strDir);
	}
	else
	{
		return ForceDirectories(strSub);
	}

	return true;
}


// ����: ��·���л�ȡ�ļ���
// ����:
//   strFileName - ����·�����ļ���
// ����:
//   �ļ���·��
// ʾ��:
//   ExtractFilePath("/home/user1/data/test.c");
//   ������: "test.c"
string GetFileNameByPath(string strDir)
{
	int nLen, nPos;
	string strResult;

	nLen = strDir.length();
	nPos = -1;
	for (int i = nLen - 1; i >= 0; i--)
	{
		if (strDir[i] == '/' || strDir[i] == '\\')
		{
			nPos = i;
			break;
		}
	}

	if (nPos != -1)
		strResult = strDir.substr(nPos + 1);
	else
		strResult = "";

	return strResult;
}

// ���ļ������ڴ�
char *GetFileMemBuf(string strLocalPath, int &nLen)
{
	char *pRet(0);
	ifstream inf(strLocalPath.c_str(), ios_base::in | ios_base::binary);
	inf.seekg(0, inf.end);
	nLen = inf.tellg();
	if (nLen > 0)
	{
		pRet = new char[nLen];
		inf.seekg(0, inf.beg);
		inf.read(pRet, nLen);
	}
	return pRet;
}

//----------------------------------------------------------------------------
// ����: ����IP(�����ֽ�˳��) -> ����IPV4
//----------------------------------------------------------------------------
string IpToString(int nIp)
{
#pragma pack(1)
    union CIpUnion
    {
        int nValue;
        struct
        {
            unsigned char ch1;  //nValue������ֽ�
            unsigned char ch2;
            unsigned char ch3;
            unsigned char ch4;
        } Bytes;
    } IpUnion;
#pragma pack()
    char strString[64];

    IpUnion.nValue = nIp;
    sprintf_s(strString, 64, "%u.%u.%u.%u", IpUnion.Bytes.ch4, IpUnion.Bytes.ch3, IpUnion.Bytes.ch2, IpUnion.Bytes.ch1);
    return strString;
}

//----------------------------------------------------------------------------
// ����: ����IP -> ����IP(�����ֽ�˳��)
//----------------------------------------------------------------------------
int StringToIp(const string& strString)
{
#pragma pack(1)
    union CIpUnion
    {
        int nValue;
        struct
        {
            unsigned char ch1;
            unsigned char ch2;
            unsigned char ch3;
            unsigned char ch4;
        } Bytes;
    } IpUnion;
#pragma pack()
    int nValues[4];
    int nCount;

    StringSplitToInt(strString.c_str(), ".", nValues, 4, &nCount);
    if (nCount == 4)
    {
        IpUnion.Bytes.ch1 = nValues[3];
        IpUnion.Bytes.ch2 = nValues[2];
        IpUnion.Bytes.ch3 = nValues[1];
        IpUnion.Bytes.ch4 = nValues[0];
        return IpUnion.nValue;
    }
    else
        return 0;
}

//----------------------------------------------------------------------------
// ����: ��ȡ����IP
//----------------------------------------------------------------------------
string GetLocalIp()
{
	return "";
}


//----------------------------------------------------------------------------
// ��  ��: ��ȡ��ִ���ļ�·��(��/)
// ��  ��:
// ����ֵ: 
//   strResult - ��Ž����
//----------------------------------------------------------------------------
string &GetModulePath()
{
    static string strName;
    if(strName.empty())
    {
        const int BUFSIZE = 1024;
        char exec_name[BUFSIZE];
		::GetModuleFileNameA(0, exec_name, BUFSIZE - 1);
        strName = exec_name;
        strName = strName.substr(0, strName.rfind('\\') + 1);
    }
    return strName;
} 

// ��ȡ��ִ���ļ���
wstring &GetAppName()
{
	static wstring strName;
	if (strName.empty())
	{
		const int BUFSIZE = 1024;
		wchar_t exec_name[BUFSIZE];
		::GetModuleFileName(0, exec_name, BUFSIZE - 1);
		strName = exec_name;
		strName = strName.substr(strName.rfind(L'\\') + 1);
		strName = strName.substr(0, strName.rfind(L'.'));
	}
	return strName;
}

wstring GetFileVersionEx(const wstring &strFileName)
{
	BYTE byteInfo[2048];
	int nSize = 2048;
	LPVOID lpData;
	UINT nDataSize;
	wstring	strFileVer;
	//wstring	strFileVerW;
	int nPos;

	if (GetFileVersionInfo(strFileName.c_str(), NULL, nSize, byteInfo) != 0)
	{
		VS_FIXEDFILEINFO *pInfo;
		if (VerQueryValue(byteInfo, L"\\", (void **)&pInfo, &nDataSize))
		//if (VerQueryValue(byteInfo, L"\\StringFileInfo\\080404b0\\FileVersion", &lpData, &nDataSize))
		{
			//pInfo->dwFileVersionMS = 1;
			FormatStringW(strFileVer, L"%d.%d.%d.%d", HIWORD(pInfo->dwFileVersionMS), LOWORD(pInfo->dwFileVersionMS), HIWORD(pInfo->dwFileVersionLS), LOWORD(pInfo->dwFileVersionLS));
			//strFileVer = (wchar_t *)lpData;
		}
	}
	return strFileVer;
}

string GetFileVersionEx(const string &strFileName)
{
	BYTE byteInfo[2048];
	int nSize = 2048;
	LPVOID lpData;
	UINT nDataSize;
	string	strFileVer;
	wstring	strFileVerW;
	int nPos;

	if (GetFileVersionInfoA(strFileName.c_str(), NULL, nSize, byteInfo) != 0)
	{
		VS_FIXEDFILEINFO *pInfo;
		if (VerQueryValue(byteInfo, L"\\", (void **)&pInfo, &nDataSize))
		{
			FormatString(strFileVer, "%d.%d.%d.%d", HIWORD(pInfo->dwFileVersionMS), LOWORD(pInfo->dwFileVersionMS), HIWORD(pInfo->dwFileVersionLS), LOWORD(pInfo->dwFileVersionLS));
		}
		//if (VerQueryValue(byteInfo, L"\\StringFileInfo\\080404b0\\FileVersion", &lpData, &nDataSize))
		//{
		//	strFileVerW = (wchar_t *)lpData;
		//	strFileVer = WideCharToMultiCharW(strFileVerW.c_str(), strFileVerW.size());
		//	//while ((nPos = strFileVer.find(',')) != string::npos)
		//	//{
		//	//	strFileVer.SetAt(nPos, '.');
		//	//	strFileVer.Delete(nPos + 1);
		//	//}
		//}
	}
	return strFileVer;
}

string GetFileVersionEx()
{
	BYTE byteInfo[2048];
	int nSize = 2048;
	LPVOID lpData;
	UINT nDataSize;
	string	strFileVer;
	wstring	strFileVerW;
	int nPos;
	const int BUFSIZE = 1024;
	char exec_name[BUFSIZE];
	::GetModuleFileNameA(0, exec_name, BUFSIZE - 1);

	if (GetFileVersionInfoA(exec_name, NULL, nSize, byteInfo) != 0)
	{
		VS_FIXEDFILEINFO *pInfo;
		if (VerQueryValue(byteInfo, L"\\", (void **)&pInfo, &nDataSize))
		{
			FormatString(strFileVer, "%d.%d.%d.%d", HIWORD(pInfo->dwFileVersionMS), LOWORD(pInfo->dwFileVersionMS), HIWORD(pInfo->dwFileVersionLS), LOWORD(pInfo->dwFileVersionLS));
		}
	}
	return strFileVer;
}

static int g_nCurPacketNumber = 0;
//----------------------------------------------------------------------------
// ��  ��: ��ȡȫ�ֵı������
// ��  ��:
// ����ֵ: 
//   nResult - ȫ�ֵı������
//----------------------------------------------------------------------------
int GetCurPacketNumber()
{
    return g_nCurPacketNumber;
}

//----------------------------------------------------------------------------
// ��  ��: ����ȫ�ֵı������
// ��  ��:
// ����ֵ: 
//   nResult - ȫ�ֵı������
//----------------------------------------------------------------------------
int AllocCurPacketNumber()
{
    return ++g_nCurPacketNumber;
}

//----------------------------------------------------------------------------
// ��  ��: ɾ��ָ���ַ�
// ��  ��:
//   s  - �������ַ���
//   ch - ��ɾ���ַ�
//----------------------------------------------------------------------------
void EraseChar(string& s, char ch)
{
	int index = s.find(ch);
	while (index != std::string::npos)
	{
		s.erase(index, 1);
		index = s.find(ch);
	}
}

// 
//----------------------------------------------------------------------------
// ��  ��: ����ָ���ַ��ָ��ַ���
// ��  ��:
//   strSource  - �������ַ���
//   strLeft	- �ָ�������ַ���(��������ڷָ�������strSource)
//   strRight	- �ָ����ұ��ַ���(�ָ���ߺ�ʣ�µ�)
//   ch			- �ָ���
//----------------------------------------------------------------------------
void ParseStringBySpecChar(const string &strSource, string &strLeft, string &strRight, char ch)
{
	int nIndex = strSource.find(ch);
	if (nIndex >= 0)
	{
		strLeft = strSource.substr(0, nIndex);
		strRight = strSource.substr(nIndex + 1, strSource.size() - nIndex - 1);
	}
	else
	{
		strLeft = strSource;
		strRight = "";
	}
}

// 
//----------------------------------------------------------------------------
// ��  ��: ת��UTF8�����ر���
// ��  ��:
//   strSource  - ��ת���ַ���
// ����ֵ��
//   string - ת�����ַ���
//----------------------------------------------------------------------------
string Utf8ToLocal(const string &strSource)
{
	string strRet;
	int len = MultiByteToWideChar(CP_UTF8, 0, strSource.c_str(), -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	if (wstr)
	{
		memset(wstr, 0, sizeof(wchar_t)* (len + 1));
		MultiByteToWideChar(CP_UTF8, 0, strSource.c_str(), -1, wstr, len);

		int len2 = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
		char *szRet = new char[len2 + 1];
		if (szRet)
		{
			//memset(strRet, 0, len2);
			WideCharToMultiByte(CP_ACP, 0, wstr, len, szRet, len2, NULL, NULL);
			szRet[len2] = 0;
			strRet = szRet;
			delete szRet;
		}
		delete[] wstr;
	}
	return strRet;
}
wstring Utf8ToWideChar(const string &strSource)
{
	wstring strRet;
	int len = MultiByteToWideChar(CP_UTF8, 0, strSource.c_str(), -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	if (wstr)
	{
		memset(wstr, 0, sizeof(wchar_t)* (len + 1));
		MultiByteToWideChar(CP_UTF8, 0, strSource.c_str(), -1, wstr, len);
		strRet = wstr;
		delete[] wstr;
	}
	return strRet;
}

// ��char *ת����wstring
std::wstring MultCharToWideCharA(const char *pStr, int nLen)
{
	//��ȡ�������Ĵ�С��������ռ䣬��������С�ǰ��ַ������
	int len = MultiByteToWideChar(CP_ACP, 0, pStr, static_cast<int>(nLen), NULL, 0);
	wchar_t *buffer = new wchar_t[len + 1];
	//���ֽڱ���ת���ɿ��ֽڱ���
	MultiByteToWideChar(CP_ACP, 0, pStr, static_cast<int>(nLen), buffer, len);
	buffer[len] = L'\0';//����ַ�����β
	//ɾ��������������ֵ
	std::wstring return_value;
	return_value.append(buffer);
	delete[]buffer;
	return return_value;
}

// ��wchar_t *ת����string  
std::string WideCharToMultiCharW(const wchar_t *pStr, int nLen)
{
	std::string return_value;
	//��ȡ�������Ĵ�С��������ռ䣬��������С�ǰ��ֽڼ����
	int len = WideCharToMultiByte(CP_ACP, 0, pStr, static_cast<int>(nLen), NULL, 0, NULL, NULL);
	char *buffer = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, pStr, static_cast<int>(nLen), buffer, len, NULL, NULL);
	buffer[len] = '\0';
	//ɾ��������������ֵ
	return_value.append(buffer);
	delete[]buffer;
	return return_value;
}

// �汾�Ƚ�
// >0 strVer1 > strVer2
// =0 strVer1 > strVer2
// <0 strVer1 < strVer2
bool CompareVersion(const string &cstrVer1, const string &cstrVer2, int &nRet)
{
	string strVer1(cstrVer1);
	string strVer2(cstrVer2);
	int bRet = false;
	nRet = 0;
	char cSplit1 = '.';
	int nIndex1 = strVer1.find(cSplit1);
	if (nIndex1 < 0)
	{
		cSplit1 = ',';
		nIndex1 = strVer1.find(cSplit1);
	}

	char cSplit2 = '.';
	int nIndex2 = strVer1.find(cSplit2);
	if (nIndex2 < 0)
	{
		cSplit2 = ',';
		nIndex2 = strVer1.find(cSplit2);
	}

	int nVer1(0);
	int nVer2(0);
	string strTemp;
	for (int i = 0; i < 4; i++)
	{
		//if (nIndex1 < 0 || nIndex2 < 0)
		//{
		//	return false;
		//}
		strTemp = strVer1.substr(0, nIndex1);
		nVer1 = atoi(strTemp.c_str());
		strTemp = strVer2.substr(0, nIndex2);
		nVer2 = atoi(strTemp.c_str());
		if (nVer1 > nVer2)
		{
			nRet = 1;
			return true;
		}
		else if (nVer1 > nVer2)
		{
			nRet = -1;
			return true;
		}
		strVer1 = strVer1.substr(nIndex1 + 1, strVer1.size() - nIndex1 - 1);
		nIndex1 = strVer1.find(cSplit1);
		strVer2 = strVer2.substr(nIndex2 + 1, strVer2.size() - nIndex2 - 1);
		nIndex2 = strVer2.find(cSplit2);

	}
	return true;

}
