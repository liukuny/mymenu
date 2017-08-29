
// myoubox.cpp : ����Ӧ�ó��������Ϊ��
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


// CmyouboxApp ����

CmyouboxApp::CmyouboxApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
	InitLogs();
}


// Ψһ��һ�� CmyouboxApp ����

CmyouboxApp theApp;


// CmyouboxApp ��ʼ��

BOOL CmyouboxApp::InitInstance()
{
	// ��ֹ�ظ����г���
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
			HWND h = FindWindow(NULL, L"Myoubox��Ϸ�˵�");
			::PostMessage(h, WM_COMMAND, MAKELPARAM(TRAYMAINMENUITEM_ID_OPENMAINPANEL, BN_CLICKED), 0);
			return FALSE;
		}
	}
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO:  Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CLKImageMgr *pImageMgr = CLKImageMgr::GetInstance();
	//LoadAllResourceImageToImageArray(pImageMgr)
	AppLoadAllResourceImageToImageArray(pImageMgr)

	CmyouboxDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO:  �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO:  �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// �ͷ�ͼƬ�б�
	CLKImageMgr::FreeInstance();
	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

// �ͷ�ϵͳ����
void CmyouboxApp::FreeSingle()
{
	//// �ͷŽӿ�
	//CMiscMgr::FreeInstance();
	//// �ͷ�ͼƬ�б�
	//CLKImageMgr::FreeInstance();
	// �ͷ�����
	CLKFontMgr::FreeInstance();
	CConfigFile::FreeInstance();
	FreeLogs();
}
