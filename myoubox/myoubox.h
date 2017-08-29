
// myoubox.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "..\..\..\..\common\res\resource1.h"


// CmyouboxApp: 
// 有关此类的实现，请参阅 myoubox.cpp
//

class CmyouboxApp : public CWinApp
{
public:
	CmyouboxApp();
	~CmyouboxApp(){ FreeSingle(); }

// 重写
public:
	virtual BOOL InitInstance();
private:
	// 释放系统单件
	void FreeSingle();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CmyouboxApp theApp;