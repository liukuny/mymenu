
// myoubox.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "..\..\..\..\common\res\resource1.h"


// CmyouboxApp: 
// �йش����ʵ�֣������ myoubox.cpp
//

class CmyouboxApp : public CWinApp
{
public:
	CmyouboxApp();
	~CmyouboxApp(){ FreeSingle(); }

// ��д
public:
	virtual BOOL InitInstance();
private:
	// �ͷ�ϵͳ����
	void FreeSingle();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CmyouboxApp theApp;