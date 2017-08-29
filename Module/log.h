//******************************************************************************
// ��־�ļ����մ洢 
//******************************************************************************
#ifndef _LOG_H_
#define _LOG_H_

#include <string>
#include <fstream>
#include <fcntl.h>
#include <sys/types.h>
#include <windows.h>

#include "gfunction.h"
#include "datetime.h"

//#include <sys/file.h>
//#include <pthread.h>
//
//#include <sys/syscall.h>	// syscall(__NR_gettid)
//
//#define gettid() syscall(__NR_gettid)
//


//#include "exception.h"
//
#include <iostream>		// cout, cin
using namespace std; 

// ��־�ļ���Կ�ִ���ļ���·��
#define IM_LOG_FILENAME_SOCKET        "socket.log"
#define IM_LOG_FILENAME_INTERFACE     "interface.log"
#define IM_LOG_FILENAME_WORK          "work.log"
#define IM_LOG_FILENAME_CONTROL       "control.log"
#define IM_LOG_FILENAME_CLIENT        "client.log"
#define IM_LOG_FILENAME_ONLINELIST    "onlinelist.log"
#define IM_LOG_FILENAME_TCPSERVER	  "tcpserver.log"
#define IM_LOG_FILENAME_PINGSERVER	  "ping.log"
#define IM_LOG_FILENAME_SCANSERVER	  "scan.log"
#define IM_LOG_FILENAME_DOWNLOADRES	  "download.log"
#define IM_LOG_FILENAME_DB			  "db.log"
#define IM_LOG_FILENAME_MSG			  "msg.log"
#define IM_LOG_FILENAME_CHANNEL		  "d_channel.log"
#define IM_LOG_ERROR				  "error.log"

////////////////////////////////////////////////////////////////////////////////
// class CLogStream - ��־�ļ�����

template<class T>
class CLogStream : public ofstream
{
public:
	static T *GetInstance()
	{
		if (!T::m_pInstance)
		{
			T::m_pInstance = new T;
		}
		return T::m_pInstance;
	}
	static void FreeInstance()
	{
		if (T::m_pInstance)
		{
			delete T::m_pInstance;
			T::m_pInstance = 0;
		}
	}
	static void WriteLog(const char *pFormatString, ...)
	{
		T *p = GetInstance();
		p->Lock();
		try
		{
			p->ConnectFile();
			string strText;

			va_list argList;
			va_start(argList, pFormatString);
			FormatStringV(strText, pFormatString, argList);
			va_end(argList);

			p->WriteTimeStamp();
			p->WriteTid();
			*p << "<" << strText.c_str() << ">\r\n" << endl;
			p->close();
			p->m_bOpen = false;

		}
		catch (...){}
		p->UnLock();
	}

	static void WriteLog(const string &strLog)
	{
		T *p = GetInstance();
		string s = strLog;
		s += "%s";
		p->WriteLog(s.c_str(), "");
	}

	static void WriteLogW(const wchar_t *pFormatString, ...)
	{
		T *p = GetInstance();
		p->Lock();
		try
		{
			p->ConnectFile();
			wstring strText;
			string strTextA;

			va_list argList;
			va_start(argList, pFormatString);
			FormatStringWV(strText, pFormatString, argList);
			va_end(argList);

			p->WriteTimeStamp();
			p->WriteTid();
			strTextA = WideCharToMultiCharW(strText.c_str(), strText.size());
			*p << "<" << strTextA.c_str() << ">\r\n" << endl;
			p->close();
			p->m_bOpen = false;

		}
		catch (...){}
		p->UnLock();
	}

protected:
	CLogStream(string &strLogName) : m_strLogName(strLogName), m_bOpen(false)
	{
		InitializeCriticalSection(&m_lock);
		ConnectFile();
		Write("======================begin==========================");
		Write("����ʱ�䣺%s %s", __DATE__, __TIME__);
	}
	CLogStream(const char *pLogFile) : m_strLogName(pLogFile), m_bOpen(false)
	{
		InitializeCriticalSection(&m_lock);
		ConnectFile();
		Write("======================begin==========================");
		Write("����ʱ�䣺%s %s", __DATE__, __TIME__);
	}
	~CLogStream(){ DeleteCriticalSection(&m_lock); }
	void Open(const char *pLogFile)
	{
		open(pLogFile, ios::out | ios::app);
		m_bOpen = true;
	}
	void Lock(){ EnterCriticalSection(&m_lock); }
	void UnLock(){ LeaveCriticalSection(&m_lock); }
	void WriteTimeStamp()
	{
		*this << "[" << CDateTime().LongDateTime() << "]";
	}
	void WriteTid()
	{
		*this << "(" << /*syscall(SYS_gettid)*/GetCurrentThreadId() << ")";
	}
	void Write(const string &strLog)
	{
		ConnectFile();

		WriteTimeStamp();
		WriteTid();
		*this << "<" << strLog.c_str() << ">\r\n" << endl;
	}
	void Write(const char *pFormatString, ...)
	{
		ConnectFile();
		string strText;

		va_list argList;
		va_start(argList, pFormatString);
		FormatStringV(strText, pFormatString, argList);
		va_end(argList);

		WriteTimeStamp();
		WriteTid();
		*this << "<" << strText.c_str() << ">\r\n" << endl;
	}
	// ���ļ�(�����Ҫ�򿪵ĵ�ǰ��־�ļ������򷵻�,���򴴽�����) 
	void ConnectFile(bool bForce = false)
	{
		string strCurDate = CDateTime().LongDate();
		string strName = GetModulePath();
		strName += "log";
		if (!DirectoryExists(strName))
		{
			if (!CreateDir(strName))
			{
				::MessageBox(0, L"������־�ļ�Ŀ¼ʧ�ܣ�", L"����", 0);
				exit(1);
			}
		}
		strName += "\\";
		strName += strCurDate;
		if (!DirectoryExists(strName))
		{
			if (!CreateDir(strName))
			{
				::MessageBox(0, L"������־�ļ�ʧ�ܣ�", L"����", 0);
				exit(1);
			}
		}
		strName += "\\";
		strName += m_strLogName;
		if (bForce)
		{
			close();
			Open(strName.c_str());
			m_bOpen = true;
		}
		else
		{
			if (!FileExists(strName) || !m_bOpen)
			{
				Open(strName.c_str());
				m_bOpen = true;
			}
		}
	}
protected:
	string m_strLogName;

private:
	// SRWLock��Ч�ʸ��ߣ���ֻ��win7����֧��
	CRITICAL_SECTION m_lock;

private:
	static T *m_pInstance;
	// �Ƿ���ļ�
	bool m_bOpen;
	CLogStream(){}
};

//////////////////////////////////////////////////////////////////////////////
// class CLogSocket - Socket��־��
class CLogSocket : public CLogStream<CLogSocket>
{
private:
	CLogSocket() : CLogStream<CLogSocket>(IM_LOG_FILENAME_SOCKET){}
	friend class CLogStream<CLogSocket>;
};

//////////////////////////////////////////////////////////////////////////////
// class CLogInterface - CLogInterface��־��
class CLogInterface : public CLogStream<CLogInterface>
{
private:
	CLogInterface() : CLogStream<CLogInterface>(IM_LOG_FILENAME_INTERFACE){}
	friend class CLogStream<CLogInterface>;
};

//////////////////////////////////////////////////////////////////////////////
// class CLogWork - Work��־��
class CLogWork : public CLogStream<CLogWork>
{
private:
	CLogWork() : CLogStream(IM_LOG_FILENAME_WORK){ }
	~CLogWork(){}
	friend class CLogStream<CLogWork>;
};

//////////////////////////////////////////////////////////////////////////////
// class CLogControl - Control��־��
class CLogControl : public CLogStream<CLogControl>
{
private:
	CLogControl() : CLogStream(IM_LOG_FILENAME_CONTROL){ }
	friend class CLogStream<CLogControl>;
};

//////////////////////////////////////////////////////////////////////////////
// class CLogClient - Client��־��
class CLogClient : public CLogStream<CLogClient>
{
private:
	CLogClient() : CLogStream(IM_LOG_FILENAME_CLIENT){ }
	friend class CLogStream<CLogClient>;
};

////////////////////////////////////////////////////////////////////////////////
// class CLogOnlineList - COnlineListɨ����־��
class CLogOnlineList : public CLogStream<CLogOnlineList>
{
private:
	CLogOnlineList() : CLogStream(IM_LOG_FILENAME_ONLINELIST){}
	friend class CLogStream<CLogOnlineList>;
};

////////////////////////////////////////////////////////////////////////////////
// class CLogTcpServer - CLogTcpServerɨ����־��
class CLogTcpServer : public CLogStream<CLogTcpServer>
{
private:
	CLogTcpServer() : CLogStream(IM_LOG_FILENAME_TCPSERVER){}
	friend class CLogStream<CLogTcpServer>;
};

////////////////////////////////////////////////////////////////////////////////
// class CLogPingServer - CLogPingServerɨ����־��
class CLogPingServer : public CLogStream<CLogPingServer>
{
private:
	CLogPingServer() : CLogStream(IM_LOG_FILENAME_PINGSERVER){}
	friend class CLogStream<CLogPingServer>;
};

////////////////////////////////////////////////////////////////////////////////
// class CLogScanServer - CLogScanServerɨ����־��
class CLogScanServer : public CLogStream<CLogScanServer>
{
private:
	CLogScanServer() : CLogStream(IM_LOG_FILENAME_SCANSERVER){}
	friend class CLogStream<CLogScanServer>;
};

////////////////////////////////////////////////////////////////////////////////
// class CLogDownloadRes - CLogDownloadResɨ����־��
class CLogDownloadRes : public CLogStream<CLogDownloadRes>
{
private:
	CLogDownloadRes() : CLogStream(IM_LOG_FILENAME_DOWNLOADRES){}
	friend class CLogStream<CLogDownloadRes>;
};

////////////////////////////////////////////////////////////////////////////////
// class CLogDb - CLogDbɨ����־��
class CLogDb : public CLogStream<CLogDb>
{
private:
	CLogDb() : CLogStream(IM_LOG_FILENAME_DB){}
	friend class CLogStream<CLogDb>;
};

////////////////////////////////////////////////////////////////////////////////
// class CLogMsg - CLogMsg��־��
class CLogMsg : public CLogStream<CLogMsg>
{
private:
	CLogMsg() : CLogStream(IM_LOG_FILENAME_MSG){}
	friend class CLogStream<CLogMsg>;
};

////////////////////////////////////////////////////////////////////////////////
// class CLogChannel - CLogChannel��־��
class CLogChannel : public CLogStream<CLogChannel>
{
private:
	CLogChannel() : CLogStream(IM_LOG_FILENAME_CHANNEL){}
	friend class CLogStream<CLogChannel>;
};

//////////////////////////////////////////////////////////////////////////////
// class CLogThread - �߳���־��
class CLogThread : public CLogStream<CLogThread>
{
public:
    static void WriteLog(const char *pFormatString, ...);
    static void WriteLog(const string &strLog);
private:
	string GetThreadId();
    CLogThread();
	friend class CLogStream<CLogThread>;
};

//////////////////////////////////////////////////////////////////////////////
// class CLogError - �쳣��־��
class CLogError : public CLogStream<CLogError>
{
private:
	CLogError() : CLogStream<CLogError>(IM_LOG_ERROR){}
	friend class CLogStream<CLogError>;
};

extern void InitLogs();
extern void FreeLogs();
#endif
