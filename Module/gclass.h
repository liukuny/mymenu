#ifndef _GCLASS_H
#define _GCLASS_H
#include <string>
#include <queue>
#include <deque>
#include <list>
#include <windows.h>
#include <process.h>    /* _beginthread, _endthread */

#include "gfunction.h"
#include "log.h"

using namespace std;
////////////////////////////////////////////////////////////////////////////////
#ifndef _SINGLE_H

template <class T>
class CSingle
{
public:
	static T *GetInstance()
	{
		if(!m_pInstance)
		{
			m_pInstance =  new T;
		}
		return m_pInstance;
	}

	static void FreeInstance()
	{
		if(m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = 0;
		}
	}
protected:
	CSingle(void){}
	~CSingle(void){}
//private:
	static T *m_pInstance;
};

#else
#include "..\..\..\..\common\single.h"
#endif
////////////////////////////////////////////////////////////////////////////////
// ��װ�������İ�ȫ������
template<class T>
class CSafeSingle : public CSingle<T>
{
public:
	void Lock(){ EnterCriticalSection(&m_lock); }
	void UnLock(){ LeaveCriticalSection(&m_lock); }
protected:
	CSafeSingle(){ InitializeCriticalSection(&m_lock); }
	~CSafeSingle(){ DeleteCriticalSection(&m_lock); }
private:
	// SRWLock��Ч�ʸ��ߣ���ֻ��win7����֧��
	CRITICAL_SECTION m_lock;
};

////////////////////////////////////////////////////////////////////////////////
// ��װ�������İ�ȫ������
template<class T>
class CSafeLock
{
public:
	CSafeLock(T *pLock){ m_pLock = pLock; m_pLock->Lock(); }
	~CSafeLock(){ m_pLock->UnLock(); }
private:
	T *m_pLock;
};

////////////////////////////////////////////////////////////////////////////////
// ��װһ�̵߳ĵ���������
template<class T>
class CSingleServer : public CSafeSingle<T>
{
public:
    // ����UDP������
    void Run()
    {
        m_bStop = false;
		m_hThread = (HANDLE)_beginthreadex(NULL, 0, &ThreadRun, this, 0, &m_pid);
    }
    // ֹͣUDP������
    void Stop()
    {
        if(!m_bStop)
        {
            m_bStop = true;
			WaitForSingleObject(m_hThread, INFINITE);
			CloseHandle(m_hThread);
		}
    }
protected:
    // �Ƿ�ֹͣ
    volatile bool m_bStop; 
	CSingleServer(): m_bStop(true){}
    ~CSingleServer(){/*Stop();�������Stop������*/}
private:
    // �����̱߳�ʶ 
	unsigned m_pid;
	HANDLE m_hThread;
	static unsigned __stdcall ThreadRun(void* ptr)
    {
        T *pThis = reinterpret_cast<T *>(ptr);
		bool bContinue(true);
		while(!pThis->m_bStop)
        {
			pThis->Proc(bContinue);
			if (!bContinue) break;
        }
		_endthreadex(0);
        return 0;
    }
}; 

////////////////////////////////////////////////////////////////////////////////
//
template <class T, class P>
class CQueueBuf : public CSafeSingle<T>
{
public:
    // ��ȡ���ݸ���
    uint GetCount(){return m_queue.size();} 
protected:
    // ���뻺�� 
    bool EnterBuf(P *pItem)
    {
        if(m_queue.size() >= m_nMaxPacket) return false;
        this->Lock();
        try{
            //P *p = new P(*pItem);
            m_queue.push(pItem);
        }catch(...){}
        this->UnLock();
        return true;
    }
    // �ӻ�����ȡ�� 
    P *LeaveBuf()    
    {
        P *p(0);
        this->Lock();
		try{
			//if (m_queue.size() != 0) //����Ϊ�յ������size()���ܲ�Ϊ��,ԭ��δ��������(��������������ת�����⣬size()��������uint)�Ѳ������ֽڶ�������
			if (!m_queue.empty())
			{
				p = m_queue.front();
				m_queue.pop();
			}
		}catch(...){}
        this->UnLock();
        return p;
    }  
	CQueueBuf() : m_nMaxPacket(100 * 2048)
	{
		//int nCount = m_queue.size();
		//CLogInnerServer::WriteLog("CQueueBuf init queue size : %d", nCount);
	}
    ~CQueueBuf(){FreeBuf();}
private:
    queue<P *> m_queue;
    // ��󻺴�ı��ĸ��� 
    uint m_nMaxPacket;
    void FreeBuf()
    {
         this->Lock();
         try{
             while(!m_queue.empty())
             {
                 P *p = (P *)m_queue.front();
                 delete p;
                 m_queue.pop();
             }
         }catch(...){}
         this->UnLock();
    }
};


////////////////////////////////////////////////////////////////////////////////
//
template <class T, class P>
class CListBuf : public CSafeSingle<T>
{
public:
    // ��ȡ���ݸ���
    uint GetCount(){return m_list.size();} 
	// ��ȡ��
	int GetItem(const string &sUserNo, P *pItem)
	{
        int nFind(0);
        this->Lock();
		try{
			for(typename list<P *>::iterator it = m_list.begin(); it != m_list.end(); ++it)
			{
				if((*it)->IsEqual(sUserNo))
				{
					if(0 == nFind)
					{
						pItem->SetValue(*it);
					}
					nFind++;
					//break;
				}
			}
		}catch(...){}
        this->UnLock();
        return nFind;
	}
	// �Ƿ�����û������ļ�
	bool IsExistUserMsg(const string &sUserNo)
	{
        bool bFind(false);
        this->Lock();
		try{
			for(typename list<P *>::iterator it = m_list.begin(); it != m_list.end(); ++it)
			{
				if((*it)->IsEqual(sUserNo))
				{
					bFind = true;
					break;
				}
			}
		}catch(...){}
        this->UnLock();
        return bFind;
	}
protected:
    // ���뻺�� 
    bool EnterBuf(P *pItem)
    {
        if(m_list.size() >= m_nMaxPacket) return false;
        this->Lock();
        try{
            P *p = new P(*pItem);
            m_list.push_back(p);
        }catch(...){}
        this->UnLock();
        return true;
    }
    // �ӻ�����ȡ�� 
    P *LeaveBuf()    
    {
        P *p(0);
        this->Lock();
        if (!m_list.empty())
		{
			try{
				p = m_list.front();
				m_list.pop_front();
			}catch(...){}
		}
        this->UnLock();
        return p;
    }  
    // �ӻ�����ȡ�� 
    P *LeaveBuf(int nId)    
    {
        P *p(0);
		bool bFind(false);
        this->Lock();
		try{
			for(typename list<P *>::iterator it = m_list.begin(); it != m_list.end(); ++it)
			{
				p = *it;
				if(p->IsEqual(nId))
				{
					bFind = true;
					m_list.erase(it);
					break;
				}
			}
		}catch(...){}
        this->UnLock();
		if(bFind)
		{
			return p;
		}
		return 0;
    }  
    // �ӻ�����ȡ�� 
    P *LeaveBuf(const string &sUserNo)    
    {
        P *p(0);
		bool bFind(false);
        this->Lock();
		try{
			for(typename list<P *>::iterator it = m_list.begin(); it != m_list.end(); ++it)
			{
				p = *it;
				if(p->IsEqual(sUserNo))
				{
					bFind = true;
					m_list.erase(it);
					break;
				}
			}
		}catch(...){}
        this->UnLock();
		if(bFind)
		{
			return p;
		}
		return 0;
    }  
    // �ӻ�����ȡ�� 
    P *LeaveBuf(const string &sUserNo, const int &nId)    
    {
        P *p(0);
		bool bFind(false);
        this->Lock();
		try{
			for(typename list<P *>::iterator it = m_list.begin(); it != m_list.end(); ++it)
			{
				p = *it;
				if(p->IsEqual(sUserNo) && p->IsEqual(nId))
				{
					bFind = true;
					m_list.erase(it);
					break;
				}
			}
		}catch(...){}
        this->UnLock();
		if(bFind)
		{
			return p;
		}
		return 0;
    }  
	CListBuf() : m_nMaxPacket(10){}
    ~CListBuf(){FreeBuf();}
	// �����������Ԫ�صĸ���
	void SetMaxCount(int nCount){m_nMaxPacket = nCount;}
private:
    // ��󻺴�ı��ĸ��� 
    uint m_nMaxPacket;
    list<P *> m_list;
	//typename list<P *>::iterator m_listIt;
    void FreeBuf()
    {
         this->Lock();
         try{
             while(!m_list.empty())
             {
                 P *p = m_list.front();
                 delete p;
                 m_list.pop_front();
             }
         }catch(...){}
         this->UnLock();
    }
};

#endif
