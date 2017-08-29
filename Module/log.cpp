#include "gfunction.h"
#include "log.h"

#include <stdarg.h> // va_list
////


//////////////////////////////////////////////////////////////////////////////
// class CLogSocket - Socket日志类
CLogSocket *CLogStream<CLogSocket>::m_pInstance = 0;

//////////////////////////////////////////////////////////////////////////////
// class CLogInterface - CLogInterface日志类
CLogInterface *CLogStream<CLogInterface>::m_pInstance = 0;

//////////////////////////////////////////////////////////////////////////////
// class CLogWork - Work日志类
CLogWork *CLogStream<CLogWork>::m_pInstance = 0;

//////////////////////////////////////////////////////////////////////////////
// class CLogControl - Control日志类
CLogControl *CLogStream<CLogControl>::m_pInstance = 0;

//////////////////////////////////////////////////////////////////////////////
// class CLogClient - Client日志类
CLogClient *CLogStream<CLogClient>::m_pInstance = 0;

////////////////////////////////////////////////////////////////////////////////
// class CLogOnlineList - CLogOnlineList日志类
CLogOnlineList *CLogStream<CLogOnlineList>::m_pInstance = 0;

////////////////////////////////////////////////////////////////////////////////
// class CLogTcpServer - CLogTcpServer日志类
CLogTcpServer *CLogStream<CLogTcpServer>::m_pInstance = 0;

////////////////////////////////////////////////////////////////////////////////
// class CLogPingServer - CLogPingServer扫描日志类
CLogPingServer *CLogStream<CLogPingServer>::m_pInstance = 0;

////////////////////////////////////////////////////////////////////////////////
// class CLogScanServer - CLogScanServer扫描日志类
CLogScanServer *CLogStream<CLogScanServer>::m_pInstance = 0;

////////////////////////////////////////////////////////////////////////////////
// class CLogDownloadRes - CLogDownloadRes扫描日志类
CLogDownloadRes *CLogStream<CLogDownloadRes>::m_pInstance = 0;

////////////////////////////////////////////////////////////////////////////////
// class CLogDb - CLogDb数据库操作日志类
CLogDb *CLogStream<CLogDb>::m_pInstance = 0;

////////////////////////////////////////////////////////////////////////////////
// class CLogMsg - CLogMsg日志类
CLogMsg *CLogStream<CLogMsg>::m_pInstance = 0;

////////////////////////////////////////////////////////////////////////////////
// class CLogChannel - CLogChannel日志类
CLogChannel *CLogStream<CLogChannel>::m_pInstance = 0;

//////////////////////////////////////////////////////////////////////////////
// class CLogThread - CLogThread日志类
CLogThread *CLogStream<CLogThread>::m_pInstance = 0;
CLogThread::CLogThread()
: CLogStream<CLogThread>((GetThreadId() + ".log").c_str())
{
}

void CLogThread::WriteLog(const char *pFormatString, ...)
{
    CLogThread *p = CLogThread::GetInstance();
    p->Lock();
    try
    {
		p->m_strLogName = p->GetThreadId() + ".log";
		p->ConnectFile(true);
		string strText;

		va_list argList;
		va_start(argList, pFormatString);
		FormatStringV(strText, pFormatString, argList);
		va_end(argList);

		p->WriteTimeStamp();
		p->WriteTid();
		*p << "<" << strText.c_str() << ">\r\n" << endl;
    }catch(...){}
    p->UnLock();
}

void CLogThread::WriteLog(const string &strLog)
{
    CLogThread *p = CLogThread::GetInstance();
	p->m_strLogName = p->GetThreadId() + ".log";
	string s = strLog;
	s += "%s";
	p->WriteLog(s.c_str(), "");
}

string CLogThread::GetThreadId()
{
	string strRet;
	char sBuf[50] = {0};
	sprintf_s(sBuf, 50, "%d", GetCurrentThreadId());
	strRet = sBuf;
	return strRet;
}

//////////////////////////////////////////////////////////////////////////////
// class CLogError - CLogError日志类
CLogError *CLogStream<CLogError>::m_pInstance = 0;


void InitLogs()
{
	//CLogSocket::GetInstance();
	CLogInterface::GetInstance();
	CLogError::GetInstance();
	CLogClient::GetInstance();
	//CLogChannel::GetInstance();
	//CLogControl::GetInstance();
	//CLogWork::GetInstance();
	//CLogThread::GetInstance();
	//CLogPingServer::GetInstance();
	//CLogScanServer::GetInstance();
	//CLogDownloadRes::GetInstance();
	//CLogDb::GetInstance();
	//CLogMsg::GetInstance();
}

void FreeLogs()
{
	//CLogMsg::FreeInstance();
	//CLogDb::FreeInstance();
	//CLogPingServer::FreeInstance();
	//CLogScanServer::FreeInstance();
	//CLogDownloadRes::FreeInstance();
	//CLogThread::FreeInstance();
	//CLogWork::FreeInstance();
	//CLogControl::FreeInstance();
	//CLogChannel::FreeInstance();
	CLogClient::FreeInstance();
	CLogError::FreeInstance();
	CLogInterface::FreeInstance();
	//CLogSocket::FreeInstance();
}
