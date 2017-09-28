#ifndef _GFUNCTION_H
#define _GFUNCTION_H

#include <string>
#include <stdarg.h> // va_list
#include <iostream>		// cout, cin
#include "datatypedef.h"

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// 字符串相关函数--------------------------------------------------------------- 
// 是否是整形数据 
bool IsInt(const char *pStr);
// 字符串转换成整形 
int StrToInt(const char *pStr, int nDefault = 0);
// 格式化字符串 
void FormatStringV(string& strResult, const char *pFormatString, va_list argList);
void FormatString(string& strResult, const char *pFormatString, ...);
void FormatStringWV(wstring& strResult, const wchar_t *pFormatString, va_list argList);
void FormatStringW(wstring& strResult, const wchar_t *pFormatString, ...);
// 整形转字符串 
string IntToStr(int nValue);
// 字符串替换 
int StringReplace(char *pStr, int nSize, char *pFrom, char *pTo);
// 分割字符串
int StringSplitToInt(const char *pStr, const char *pSplitter, int pIntList[], int nListSize, int *nCount);
// 删除指定字符
void EraseChar(string& s, char ch);
// 跟据指定字符分割字符串
void ParseStringBySpecChar(const string &strSource, string &strLeft, string &strRight, char ch = PROTOCOL_COMMON_SPLIT_CHAR);
// 转换UTF8到本地编码
string Utf8ToLocal(const string &strSource);
wstring Utf8ToWideChar(const string &strSource);
// 把char *转换成wstring
wstring MultCharToWideCharA(const char *pStr, int nLen);
// 把wchar_t *转换成string  
string WideCharToMultiCharW(const wchar_t *pStr, int nLen);
// 版本比较
// nRet的值：
// >0 strVer1 > strVer2
// =0 strVer1 > strVer2
// <0 strVer1 < strVer2
bool CompareVersion(const string &cstrVer1, const string &cstrVer2, int &nRet);

////////////////////////////////////////////////////////////////////////////////
//文件和目录--------------------------------------------------------------------
bool FileExists(const string& strDir);
bool DirectoryExists(const string& strDir);
bool CreateDir(const string& strDir);
string ExtractFilePath(const string& strFileName);
bool ForceDirectories(string strDir);
// 从路径中获取文件名
string GetFileNameByPath(string strDir);
// 把文件读入内存
char *GetFileMemBuf(string strLocalPath, int &nLen);
//网络函数
string IpToString(int nIp);
int StringToIp(const string& strString);
string GetLocalIp();

////////////////////////////////////////////////////////////////////////////////
// 系统相关函数----------------------------------------------------------------- 
// 获取可执行文件路径(带/)
string &GetModulePath();
// 获取可执行文件名
wstring &GetAppName();
// 获取文件版本
wstring GetFileVersionEx(const wstring &strFileName);
string GetFileVersionEx(const string &strFileName);
string GetFileVersionEx();
// 获取全局的报文序号
int GetCurPacketNumber();
// 生成全局的报文序号
int AllocCurPacketNumber();

#ifdef _XP_TEST
#define WGetTickCount() ::GetTickCount()
#else
#define WGetTickCount() ::GetTickCount64()
#endif
#endif
