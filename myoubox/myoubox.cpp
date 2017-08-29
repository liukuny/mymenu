
// myoubox.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "myoubox.h"
#include "myouboxDlg.h"
#include "myouboxConst.h"
#include "TrayMainMenu.h"

#include "..\..\..\..\common\FrameInterface.h"
#include "..\..\..\..\common\LKComponent\GDI\LKImage.h"
#include "..\..\..\..\common\LKComponent\Gdi\LKFontMgr.h"
#include "..\..\..\..\common\LKComponent\Gdi\LKImageMgr.h"
#include "..\..\..\..\common\LKComponent\GDI\LKConst.h" 

#include "ConfigFile.h"
#include "log.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmyouboxApp

BEGIN_MESSAGE_MAP(CmyouboxApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CmyouboxApp 构造

CmyouboxApp::CmyouboxApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
	InitLogs();
}


// 唯一的一个 CmyouboxApp 对象

CmyouboxApp theApp;


// CmyouboxApp 初始化

BOOL CmyouboxApp::InitInstance()
{
	// 防止重复运行程序
	CConfigFile::GetInstance();
	SECURITY_DESCRIPTOR sd;
	if (0 == InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION) || 0 == SetSecurityDescriptorDacl(&sd, TRUE, (PACL)0, FALSE))
	{
		return FALSE;
	}
	else
	{
		SECURITY_ATTRIBUTES sa;
		sa.nLength = sizeof(sa);
		sa.lpSecurityDescriptor = &sd;
		sa.bInheritHandle = FALSE;
		HANDLE hSem = CreateSemaphore(&sa, 1, 1, _T("Bar_Myoubox"));
		DWORD dwCheckThread = GetLastError();
		if (dwCheckThread == ERROR_ALREADY_EXISTS)
		{
			HWND h = FindWindow(NULL, L"Myoubox游戏菜单");
			::PostMessage(h, WM_COMMAND, MAKELPARAM(TRAYMAINMENUITEM_ID_OPENMAINPANEL, BN_CLICKED), 0);
			return FALSE;
		}
	}
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO:  应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CLKImageMgr *pImageMgr = CLKImageMgr::GetInstance();
	//LoadAllResourceImageToImageArray(pImageMgr)
	AppLoadAllResourceImageToImageArray(pImageMgr)

	CmyouboxDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO:  在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO:  在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 释放图片列表
	CLKImageMgr::FreeInstance();
	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

// 释放系统单件
void CmyouboxApp::FreeSingle()
{
	//// 释放接口
	//CMiscMgr::FreeInstance();
	//// 释放图片列表
	//CLKImageMgr::FreeInstance();
	// 释放字体
	CLKFontMgr::FreeInstance();
	CConfigFile::FreeInstance();
	FreeLogs();
}
