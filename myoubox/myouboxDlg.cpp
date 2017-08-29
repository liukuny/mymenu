
// myouboxDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "myoubox.h"
#include "myouboxDlg.h"
#include "afxdialogex.h"
#include "ConfigFile.h"
#include "log.h"
#include "CenterInterface.h"
#include "LocalDataInfo.h"
#include "ChangeSkinDlg.h"
#include "TrayMainMenu.h"
#include "myouboxConst.h"
#include <TlHelp32.h>

#include "..\..\..\..\common\LKComponent\GDI\LKImage.h"
#include "..\..\..\..\common\LKComponent\GDI\LKImageMgr.h"
#include "..\..\..\..\common\LKComponent\GDI\LKFontMgr.h"
#include "..\..\..\..\common\LKComponent\GDI\LKBalloonDialog.h"
#include "..\..\..\..\common\LKComponent\GDI\LKBalloonWnd.h"
#include "..\..\..\..\common\LKComponent\GDI\LKMessageBox.h"
#include "..\..\..\..\common\LKComponent\GDI\LKToolTipCtrl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 搜索框ID
#define MAINDLG_EDITID_SEARCH	100
// 搜索按钮
#define LOGINDLG_BUTTONID_SEARCH 101
// 字母按钮起始ID
#define LOGINDLG_BUTTONID_ABEG	102


const int g_nTopHeight = 70;
// 树形控件宽度
const int g_nTreeWidth = 161;
// Tab分页控件高度
const int g_nTabHeight = 22;
// Tab分页控件左偏移
const int g_nTabLeftOffset = 10;

int g_nScreenWidth = 0;

void test()
{
	CLKImage img(160, 210, 32);
	CLKImage  img2;
	img2.Load(L"d:\\yfq2.bmp");
	img2.DrawToImage(&img);
	img.Save(L"d:\\yfq.jpg", Gdiplus::ImageFormatJPEG);

	char *pBuf = new char[25 * 1024];

	fstream f("d:\\yfq.jpg", ios::in | ios_base::binary);
	if (f.is_open())
	{
		f.seekg(0, std::ios::end);
		int nLen = f.tellg();
		f.seekg(0, std::ios::beg);
		//char *pBuf = new char[nLen];
		f.read(pBuf, nLen);

		f.close();
	}

	ofstream of("d:\\yfq2.jpg", ios_base::out | ios_base::binary);
	of.write(pBuf, 25 * 1024);
	of.close();
		delete[]pBuf;

	exit(0);
}

CmyouboxDlg::CmyouboxDlg(CWnd* pParent /*=NULL*/)
	//: CDialogEx(CmyouboxDlg::IDD, pParent)
	: CLKMainDialog(CmyouboxDlg::IDD, pParent)
	, m_ctlSearch(2)
	, m_treeMain(0)
	// 游戏列表
	, m_Container(1)
	, m_BtnSearch(0)
{
	int nS = sizeof(CLKImage);
	////CString sw = L"中";
	//char sw[10] = { "我" };
	////std::string s = xm2m_utf8(sw.c_str(), sw.size());
	//word *p = (word *)sw;
	//int n1 = htons(*p);
	//int n2 = *(p + 1);

	//CString strName = L"xx";
	//GetProcessidFromName(strName);
	//test();
	SetTopOffset(22);
	SetRightOffset(10);
	m_bMinSize = CPoint(1200, 780);
	//m_bMinSize = CPoint(600, 380);
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//m_hSmallIcon = (HICON)::LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDR_MAINFRAME), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	InitImageList();
	CRect rt(2, 2, 2, 2);
	SetNCClientRect(rt);

	g_nScreenWidth = SCREEN_WIDTH;
}

CmyouboxDlg::~CmyouboxDlg()
{
	if (m_hSmallIcon)
	{
		::DestroyIcon(m_hSmallIcon);
		m_hSmallIcon = 0;
	}
	CLocalDataInfo::FreeInstance();
}

void CmyouboxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

// 初始化图片列表
void CmyouboxDlg::InitImageList()
{
	// 初始化图片列表
	CLKDialog::InitImageList();
	//m_arrImage[LKGDIBASEDIALOG_IMAGEINDEX_MAX] = 0;
	//m_arrImage[LKGDIBASEDIALOG_IMAGEINDEX_MIN] = 0;
	//m_arrImage[LKGDIBASEDIALOG_IMAGEINDEX_RESTORE] = 0;
	m_arrImage[LKGDIBASEDIALOG_IMAGEINDEX_SELF] = 0;
	////m_pBGImg = CLKImageMgr::GetImageS(LOGINBG_IMAGE);
	////if (m_pBGImg)
	////{
	////	m_bMinSize.x = m_pBGImg->GetWidth();
	////	m_bMinSize.y = m_pBGImg->GetHeight();
	////}
}

// 初始化窗口前景图片
void CmyouboxDlg::OnInitMemImg()
{
	//CLKImage *pImg = GetMemImage();
	//if (pImg && pImg->IsValid())
	//{
	//	CRect rtText(0, 0, 80, 24);
	//	UINT uFormat = DT_LEFT | DT_VCENTER | DT_SINGLELINE;
	//	COLORREF crText = RGB(255, 255, 255);
	//	rtText.OffsetRect(178, 28);
	//	pImg->DrawText(_T("按字母查找："), rtText, CLKFontMgr::GetST90(), uFormat, crText);
	//}
	//// 6像素高顶部通用蒙板 
	////#define LKIMAGELISTINDEX_COMMON_TOPMASK6		2
	//CLKImage *pImgMask = CLKImageMgr::GetImageS(LKIMAGELISTINDEX_COMMON_TOPMASK6);
	//CLKImage *pImg = GetMemImage();
	//if (pImgMask && pImg)
	//{
	//	CRect rt;
	//	GetWindowRect(&rt);
	//	rt.MoveToXY(0, 0);
	//	CRect rtMask(0, GetTitleBarHeight() + g_nTopHeight - pImgMask->GetHeight() - 2, rt.right, GetTitleBarHeight() + g_nTopHeight - 2);
	//	pImgMask->DrawToImage(pImg, rtMask);
	//}
	// 头部背景
	CLKImage *pImgHBG = CLKImageMgr::GetImageS(LKIMAMYOUBOX_DIALOG_HEAD);
	CLKImage *pImg = GetMemImage();
	if (pImgHBG && pImg)
	{
		CRect rtHBG(2, 2, m_rtWnd.Width() - 4, pImgHBG->GetHeight());
		pImgHBG->DrawToImage(pImg, rtHBG);
	}
	// 头部标签
	CLKImage *pImgHL = CLKImageMgr::GetImageS(LKIMAMYOUBOX_DIALOG_HEADLABEL);
	if (pImgHL && pImg)
	{
		CRect rtHL(0, 0, pImgHL->GetWidth(), pImgHL->GetHeight());
		rtHL.MoveToXY(20, 10);
		pImgHL->DrawToImage(pImg, rtHL);
	}
	// 分隔条
	CLKImage *pImgSplit = CLKImageMgr::GetImageS(LKIMAGELISTINDEX_COMMON_SPLIT);
	if (pImgSplit && pImg)
	{
		CRect rtS(0, 67, m_rtWnd.Width(), pImgSplit->GetHeight() + 67);
		//pImgSplit->DrawToImageLR(pImg, rtS);
		//CLKImage img(rtS.Width(), rtS.Height());
		//pImgSplit->StretchBilinear(&img, rtS.Width(), rtS.Height(), pImgSplit->GetWidth(), pImgSplit->GetHeight());
		pImgSplit->DrawToImage(pImg, rtS);
	}
}

LRESULT CmyouboxDlg::OnCommonMsg(WPARAM wParam, LPARAM lParam)
{
	if (LKBUTTONEX_MSG_WPARAM_SELECTED == wParam)
	{
		m_bChangeSkin = true;
		CLKImage *pImg = (CLKImage *)lParam;
		ChangeBGImg(pImg);
		// 更新其它窗口
		UpdateAllDlgBGImg();
		// 更新其它控件 
		SendMessage(LKCOMMON_MSG, LKCOMMON_MSG_WPARAM_RESETMEM, 0);
	}
	else if (LKCONTAINER_MSG_WPARAM_ITEMBTNCLICKED == wParam)
	{
		//MessageBeep(100);
		CLogClient::WriteLog("图标被点击");
		PGameItem p = (PGameItem)lParam;
		if (!p->strGameStartProgram.IsEmpty())
		{
			int nIndex = p->strGameStartProgram.ReverseFind(L'\\');
			CString strPath = p->strGameStartProgram.Left(nIndex);
			::SetCurrentDirectory(strPath);

			STARTUPINFO si;
			PROCESS_INFORMATION pi;
			ZeroMemory(&si, sizeof(si));
			si.cb = sizeof(si);
			ZeroMemory(&pi, sizeof(pi));
			// Start the child process. 
			//if (CreateProcess(NULL,   // No module name (use command line)
			//	p->strGameStartProgram.GetBuffer(),        // Command line
			//	NULL,           // Process handle not inheritable
			//	NULL,           // Thread handle not inheritable
			//	FALSE,          // Set handle inheritance to FALSE
			//	0,              // No creation flags
			//	NULL,           // Use parent's environment block
			//	NULL,           // Use parent's starting directory 
			//	&si,            // Pointer to STARTUPINFO structure
			//	&pi)           // Pointer to PROCESS_INFORMATION structure
			//	)
			//{
			//	//ShowWindow(SW_MINIMIZE);
			//	//if (p->strGameStartProgram.CompareNoCase(p->strGameMainProcessName) != 0)
			//	//{
			//	//	CloseHandle(pi.hProcess);
			//	//	pi.hProcess = 0;
			//	//	m_strMainProcess = p->strGameMainProcessName;
			//	//}
			//	//else
			//	//{
			//	//	m_strMainProcess = L"";
			//	//	m_hStartProcess = pi.hProcess;
			//	//}
			//	//SetTimer(10000, 1000, 0);
			//	//CloseHandle(pi.hThread);
			//	//pi.hThread = 0;
			//	CLogClient::WriteLog("程序运行成功。");
			//}
			//else
			//{
			UploadGameItem ugItem;
			CLocalDataInfo::GetInstance()->GetUploadGameItem(&ugItem);
			//if (ugItem.strGameId.IsEmpty())
			if (ugItem.strGameId.CompareNoCase(p->strGameId) != 0)
			{
				CLocalDataInfo::GetInstance()->SetUploadGameItem(p->strGameId, p->strGameName, p->strGameStartProgram);
				::AfxBeginThread(RunGame, NULL);
			}
			else
			{
				//SetTimer(10002, 5 * 1000, 0);
				CLogClient::WriteLog("游戏程序正在运行，请等待。");
			}
			//	HINSTANCE h = ShellExecute(NULL, L"open", p->strGameStartProgram.GetBuffer(), NULL, NULL, SW_SHOWNORMAL);
			//	CLogClient::WriteLogW(L"执行程序: %d -- %s", (int)h, p->strGameStartProgram.GetBuffer());
			//	if ((int)h < 32)
			//	{
			//		CStringA s; 
			//		s = p->strGameStartProgram;
			//		CLogError::WriteLog("执行程序%s失败: %d", s.GetBuffer(), (int)h);
			//	}
			//	else
			//	{
			//		//ShowWindow(SW_MINIMIZE);
			//		CLogClient::WriteLog("程序运行成功2。");
			//	}
			////}
			//// 上传游戏数据
			//CStringA sId, sName;
			//sId = p->strGameId;
			//sName = p->strGameName;
			//CCenterInterface::UploadGameInfo(sId.GetBuffer(), sName.GetBuffer());
		}
		//CRect rt(0, 0, 200, 100);
		//GetClientRect(&rt);
		//rt.OffsetRect(4, rt.Height() - 6);
	}
	else if (LKTREECTRL_MSG_WPARAM_ITEMCHANGED == wParam)
	{
		// 处理树形控件选择项改变
		OnTreeCtrlSelectedChanged((PLKTREEITEM)lParam);
		//CRect rt(0, 0, 200, 100);
		//CLKBalloonWnd::Show(&m_treeMain, rt, _T("大写锁定已打开"));
	}
	else if (LKTAP_MSG_WPARAM_ITEMCHANGED == wParam)
	{
		// 处理TAB控件选择项改变
		OnTabCtrlSelectedChanged();
	}
	else if (106 == wParam)
	{
		////CLogClient::WriteLog("从全屏游戏中恢复2：%d, %d", wParam, lParam);
		//OnTreeCtrlSelectedChanged(0);
		//m_Container.CalcVisibleCtrl();
		//m_Container.Invalidate();
		PostMessage(LKCOMMON_MSG, LKCOMMON_MSG_WPARAM_RESETMEM);
		//OnTreeCtrlSelectedChanged(0);
		CLogClient::WriteLog("从全屏游戏中恢复3");
		//SetTimer(10001, 300, 0);
	}
	else
	{
		CLKDialog::OnCommonMsg(wParam, lParam);
	}
	return 1; 
}

// 自定义菜单按钮被按下
void CmyouboxDlg::OnMenuClick()
{
	CChangeSkinDlg dlg;
	dlg.DoModal();
	Invalidate();
}
// 判断鼠标是否在其它自定义区域范围内
bool CmyouboxDlg::IsInOther(CPoint point)
{
	CRect rtWindow(m_rtWnd);
	rtWindow.MoveToXY(0, 0);
	rtWindow.DeflateRect(2, 70, 2, 4);
	if (rtWindow.PtInRect(point))
	{
		return true;
	}
	return false;
}

BEGIN_MESSAGE_MAP(CmyouboxDlg, CLKMainDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_BN_CLICKED(MAINDLG_EDITID_SEARCH, &CmyouboxDlg::OnEBnClickedButtonSearch)
	ON_EN_CHANGE(MAINDLG_EDITID_SEARCH, &CmyouboxDlg::OnEnChangeEdit)

	ON_BN_CLICKED(LOGINDLG_BUTTONID_SEARCH, &CmyouboxDlg::OnBnClickedButtonSearch)
	// 打开面板
	ON_COMMAND(TRAYMAINMENUITEM_ID_OPENMAINPANEL, OnOpenMainPanel)
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_WM_MOUSEHWHEEL()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOVING()
	ON_WM_MOVE()
	ON_WM_ACTIVATEAPP()
END_MESSAGE_MAP()


// CmyouboxDlg 消息处理程序

BOOL CmyouboxDlg::OnInitDialog()
{
	//CDialogEx::OnInitDialog();
	//SetIcon(m_hIcon, TRUE);			// 设置大图标
	//SetIcon(m_hIcon, FALSE);		// 设置小图标

	//// TODO:  在此添加额外的初始化代码
	CLKDialog::OnInitDialog();
	CStringA strTextA = CConfigFile::GetInstance()->GetMenuName().c_str();
	CString strText; strText = strTextA;
	SetWindowText(strText);
	CRect rt;
	GetClientRect(&rt);

	//const int nLeftMargin = 5;
	//// 搜索框
	//CRect rtSearch(0, 14, 250, 53);
	//rtSearch.left = rt.Width() / 2 - 130;
	//rtSearch.right = rtSearch.left + 360;
	//m_ctlSearch.SetClientOffset(CRect(0, 0, 0, 0));
	//m_ctlSearch.SetClientEdge(CRect(12, 8, 82, 8));
	//m_ctlSearch.SetTextFont(CLKFontMgr::GetMSYH13px());
	//m_ctlSearch.SetTextBGCol(RGB(68, 71, 73));
	//m_ctlSearch.SetTextColor(RGB(255, 255, 255));
	//// 编辑框按钮图片
	//m_ctlSearch.SetBtnImage(CLKImageMgr::GetImageS(LKIMAGEBUTTONINDEX_EDITBUTTON));
	//m_ctlSearch.Create(WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_WANTRETURN, rtSearch, this, MAINDLG_EDITID_SEARCH);
	//m_ctlSearch.SetHintText(_T("游戏名/拼音"));

	EnableToolTips();
	m_pToolTip = &m_ToolTip;// new CLKToolTipCtrl;
	m_pToolTip->Create(this);
	m_pToolTip->Activate(TRUE);
	m_pToolTip->AddTool(this, _T(""));//添加tip

	m_pChildToolTip = &m_ChildToolTip;// new CLKToolTipCtrl;
	m_pChildToolTip->Create(this);
	m_pChildToolTip->Activate(TRUE);

	// 搜索框
	CRect rtSearch(0, 76, 250, 115);
	rtSearch.right = rt.right - 60;
	rtSearch.left = rtSearch.right - 360;
	m_ctlSearch.SetClientOffset(CRect(0, 0, 0, 0));
	//m_ctlSearch.SetClientEdge(CRect(12, 8, 82, 8));
	m_ctlSearch.SetClientEdge(CRect(12, 8, 12, 8));
	m_ctlSearch.SetTextFont(CLKFontMgr::GetMSYH13px());
	m_ctlSearch.SetTextBGCol(RGB(68, 71, 73));
	m_ctlSearch.SetTextColor(RGB(255, 255, 255));
	// 编辑框按钮图片
	//m_ctlSearch.SetBtnImage(CLKImageMgr::GetImageS(LKIMAGEBUTTONINDEX_EDITBUTTON));
	m_ctlSearch.Create(WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_WANTRETURN, rtSearch, this, MAINDLG_EDITID_SEARCH);
	m_ctlSearch.ShowWindow(SW_HIDE);
	//m_ctlSearch.SetHintText(_T("游戏名/拼音"));

	// 搜索按钮
	//CRect rtBtn(152, 2, 172, 22);
	CRect rtBtn(rt.right - 60, rtSearch.top, rt.right, rtSearch.bottom);
	rtBtn.left += 3;
	rtBtn.top += 4;
	rtBtn.right = rtBtn.left + 32;
	rtBtn.bottom = rtBtn.top + 32;
	m_BtnSearch.SetIconWidthAndHeight(32, 32);
	m_BtnSearch.SetTextFont(CLKFontMgr::GetMSYH13px());
	m_BtnSearch.SetParseImage(LKIMAGEINDEX_COMMON_ICONDSEARCH);
	m_BtnSearch.Create(L"", rtBtn, this, LOGINDLG_BUTTONID_SEARCH); 
	//m_BtnSearch.SetImage(LKIMAGEINDEX_COMMON_ICONDSEARCH);
	m_BtnSearch.SetTextColor(RGB(255, 255, 255));

	CRect rtTree(0, g_nTopHeight, g_nTreeWidth, rt.bottom);
	m_treeMain.Create(_T(""), rtTree, this, 3000);
	m_treeMain.SetTextColor(RGB(255, 255, 255));
	m_treeMain.SetTextFont(CLKFontMgr::GetMSYHPoint13());
	// 获取根结点
	PLKTREEITEM pRootItem = m_treeMain.GetRootItem();
	PLKTREEITEM pGItem = m_treeMain.InsertItem(_T("所有游戏"), -1, pRootItem, 0, 0);
	//pGItem->
	m_treeMain.SetFirstItemToSelected();

	CRect rtTab(rtTree.right + g_nTabLeftOffset, g_nTopHeight + 10, rt.right, g_nTopHeight + 10 + g_nTabHeight);
	m_tabMain.Create(rtTab, this, 1003);
	m_tabMain.ShowWindow(SW_HIDE);
	m_tabMain.AddItem(_T("所有游戏"));
	m_tabMain.SetMargin(0);
	//m_tabMain.SetIsAdjustItmeSize();
	m_tabMain.SelectItem();
	m_tabMain.SetTextColor(RGB(176, 176, 176));
	m_tabMain.SetTextFont(CLKFontMgr::GetMSYH13px());

	//CRect rtContainer(rtTree.right, rtTab.bottom + 2, rt.right, rt.bottom);
	CRect rtContainer(rtTree.right, rtTab.bottom + 14, rt.right, rt.bottom);
	//m_Container.SetIsShowButton();
	//m_Container.SetSubItemsOffest(CRect(10, 10, 10, 10));
	m_Container.SetItemWidth(68);
	m_Container.SetItemHeight(108);
	m_Container.SetItemTextHeight(40);
	m_Container.Create(_T("游戏列表"), rtContainer, this, 3001, IDR_GIF_FOCUS, IDR_GIF_FOCUS2);
	m_Container.SetTextColor(RGB(255, 255, 255));
	m_Container.SetTextFont(CLKFontMgr::GetMSYHPoint10());
	//m_Container.SetTextFont(CLKFontMgr::GetMSYHPoint13());
	//m_pChildToolTip->AddTool(&m_Container, _T("财经日历"));//添加tip

	// 初始化游戏列表
	CLocalDataInfo::GetInstance()->InitGameList();
	// 加载游戏数据
	LoadGameInfo();
	// 加载游戏类型数据
	LoadGameTypeInfo();
	// 上传启动数据 
	CCenterInterface::UploadInfo();

	m_hSmallIcon = (HICON)::LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDR_MAINFRAME), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	m_hTrayIcon = m_hSmallIcon;
	m_hCurTrayIcon = m_hSmallIcon;
	InitTray();
	//UpdatTrayState();

//	string strDownloadPlatformFileNameA = CConfigFile::GetInstance()->GetDownloadPlatformPathNameA();
//	if (::FileExists(strDownloadPlatformFileNameA))
//	{
//		CLogClient::WriteLog("更新包存在。");
//		CString strCurPlatformVer = CConfigFile::GetInstance()->GetCurPlatformVer().c_str();
//		CString strDownloadPlatformVer = GetFileVersionEx(CConfigFile::GetInstance()->GetDownloadPlatformPathName()).c_str();
//		if (strCurPlatformVer.CompareNoCase(strDownloadPlatformVer) != 0)
//		{
//			// 杀死平台进程
//			CLogClient::WriteLog("本地不是最新版本的平台。");
//			CString strCurPlatformFileName = L"BarPlatForm.exe";
//			bool bIsProcessExist = false;
//			if (KillProcessByProcessName(strCurPlatformFileName, bIsProcessExist))
//			{
//				// 更新平台进程
//cpfile:			if (::CopyFile(CConfigFile::GetInstance()->GetDownloadPlatformPathName().c_str(), CConfigFile::GetInstance()->GetCurPlatformPathName().c_str(), FALSE))
//				{
//					CLogClient::WriteLog("更新平台进程。");
//					// 启动平台进程
//					HINSTANCE h = ShellExecute(NULL, L"open", CConfigFile::GetInstance()->GetCurPlatformPathName().c_str(), NULL, NULL, SW_HIDE);
//					if ((int)h < 32)
//					{
//						CLogError::WriteLogW(L"启动平台进程%s失败: %d", CConfigFile::GetInstance()->GetCurPlatformPathName().c_str(), (int)h);
//					}
//					else
//					{
//						//ShowWindow(SW_MINIMIZE);
//						CLogClient::WriteLog("启动平台进程成功。");
//						exit(1);
//					}
//				}
//				else
//				{
//					int nErr = ::GetLastError();
//					CLogError::WriteLogW(L"复制平台文件失败: %d, %s --> %s", nErr, CConfigFile::GetInstance()->GetDownloadPlatformPathName().c_str(), CConfigFile::GetInstance()->GetCurPlatformPathName().c_str());
//					if (nErr == 32)
//					{
//						Sleep(100);
//						goto cpfile;
//					}
//				}
//			}
//		}
//	}

	return TRUE;  // return TRUE unless you set the focus to a control 
}

// 加载游戏数据
void CmyouboxDlg::LoadGameInfo()
{
	list<PGameItem> lt;
	CLocalDataInfo::GetInstance()->GetGameList(lt);
	for (list<PGameItem>::iterator itG = lt.begin(); itG != lt.end(); itG++)
	{
		PGameItem p = *itG;
		//p->strGameIcon = L"D:\\12\\game(3).ico";
		if (!p->pImg)
		{
			p->pImg = new CLKImage;
			if (::FileExists(WideCharToMultiCharW(p->strGameIcon.GetBuffer(), p->strGameIcon.GetLength())))
			{
				if (!p->pImg->LoadEx(p->strGameIcon))
				{
					delete p->pImg;
					p->pImg = 0;
				}
			}
			else
			{
				CString s = p->strGameStartProgram;
				//CLogClient::WriteLogW(L"程序图标路径： %s", s.GetBuffer());
				int nPos = s.ReverseFind(L'\\');
				if (nPos > 0)
				{
					s = p->strGameStartProgram.Left(nPos + 1);
					s += L"game48.ico";
					if (::FileExists(WideCharToMultiCharW(s.GetBuffer(), s.GetLength())))
					{
						if (!p->pImg->LoadEx(s))
						{
							delete p->pImg;
							p->pImg = 0;
						}
					}
					else
					{
						s = p->strGameStartProgram.Left(nPos + 1);
						s += L"game.ico";
						//CLogClient::WriteLogW(L"程序图标路径2： %s", s.GetBuffer());
						if (::FileExists(WideCharToMultiCharW(s.GetBuffer(), s.GetLength())))
						{
							if (!p->pImg->LoadEx(s))
							{
								delete p->pImg;
								p->pImg = 0;
							}
						}
						else
						{
							s = p->strGameMainProcessName;
							s += L"\\game.ico";
							//CLogClient::WriteLogW(L"程序图标路径3： %s", s.GetBuffer());
							if (::FileExists(WideCharToMultiCharW(s.GetBuffer(), s.GetLength())))
							{
								if (!p->pImg->LoadEx(s))
								{
									delete p->pImg;
									p->pImg = 0;
								}
							}
							else
							{
								s = p->strGameMainProcessName;
								int nPos = s.ReverseFind(L'\\');
								if (nPos > 0)
								{
									s = s.Left(nPos + 1);
									s += L"game48.ico";
									if (!p->pImg->LoadEx(s))
									{
										delete p->pImg;
										p->pImg = 0;
									}
								}
							}
						}
					}
				}
			}
			//p->pImg = pImg;
		}
		list<PGameItem>::iterator itNext = itG;

		m_Container.InsertItem(StrToInt(p->strGameId), p->strGameName, p->strGameFlag, p->pImg, p, (++itNext == lt.end() ? true : false), p->strPopPathname);
	}
	m_Container.CalcVisibleCtrl();
	CLogClient::WriteLogW(L"实际加载游戏个数：%d", m_Container.GetItemCount());
}

// 加载游戏类型数据
void CmyouboxDlg::LoadGameTypeInfo()
{
	// 获取游戏类型第一级数据列表
	CLogClient::WriteLogW(L"加载游戏类型数据");
	list<PGameTypeItem> lt;
	CLocalDataInfo::GetInstance()->GetGameTypeFirstLevelList(lt);
	for (auto it : lt)
	{
		//PGameTypeItem p = *itG;
		PLKTREEITEM pRootItem = m_treeMain.GetRootItem();
		PLKTREEITEM pItem = 0;
		if (pRootItem->arrItem.GetCount() > 0)
		{
			pItem = pRootItem->arrItem[pRootItem->arrItem.GetCount() - 1];
		}
		PLKTREEITEM pGItem = m_treeMain.InsertItem(it->strName, -1, pRootItem, pItem, (void *)it->nId);
	}
	//// 获取游戏类型第二级数据列表
	//lt.clear();
	//CLocalDataInfo::GetInstance()->GetGameTypeSecondLevelList(lt);
	//for (auto it : lt)
	//{
	//	PLKTREEITEM pRootItem = m_treeMain.GetRootItem();
	//	for (int i = 0; i < pRootItem->arrItem.GetCount(); i++)
	//	{
	//		bool bFind = false;
	//		int nId = (int)pRootItem->arrItem[i]->pData;
	//		for (auto it2 : it->ltParentName)
	//		{
	//			if (nId == it2)
	//			{
	//				bFind = true;
	//			}
	//		}
	//		if (bFind)
	//		{
	//			PLKTREEITEM pItem = 0;
	//			if (pRootItem->arrItem[i]->arrItem.GetCount() > 0)
	//			{
	//				pItem = pRootItem->arrItem[i]->arrItem[pRootItem->arrItem[i]->arrItem.GetCount() - 1];
	//			}
	//			PLKTREEITEM pGItem = m_treeMain.InsertItem(it->strName, 2, pRootItem->arrItem[i], pItem, (void *)it->nId);
	//		}
	//	}
	//}
}

// 处理树形控件选择项改变
void CmyouboxDlg::OnTreeCtrlSelectedChanged(PLKTREEITEM pOldItem)
{
	// 获取当前选中项
	PLKTREEITEM pItem = m_treeMain.GetCurSelected();
	if (pItem)
	{
		m_tabMain.DelAllItem();
		int nId = (int)pItem->pData;
		list<PGameTypeItem> lt;
		if (nId == 0)
		{
			CLocalDataInfo::GetInstance()->GetGameTypeSecondLevelList(lt);
			m_tabMain.AddItem(_T("所有游戏"));
		}
		else
		{
			CLocalDataInfo::GetInstance()->GetGameTypeSecondLevelList(nId, lt);
			for (auto it : lt)
			{
				m_tabMain.AddItem(it->strName, -1, 0, (void *)it->nId);
			}
		}
		m_tabMain.SelectItem();
		m_tabMain.Invalidate();
	}
}

// 处理TAB控件选择项改变
void CmyouboxDlg::OnTabCtrlSelectedChanged()
{
	//// 获取当前选中项
	m_Container.DeleteAllItem();
	int nId = (int)m_tabMain.GetSelectedItemData();

	list<PGameItem> lt;
	if (nId == 0)
	{
		CLocalDataInfo::GetInstance()->GetGameList(lt);
	}
	else
	{
		int nParentId = 0;
		PLKTREEITEM pItem = m_treeMain.GetCurSelected();
		if (pItem)
		{
			nParentId = (int)pItem->pData;
		}
		CLocalDataInfo::GetInstance()->GetGameList(nId, lt, nParentId);
	}
	for (list<PGameItem>::iterator itG = lt.begin(); itG != lt.end(); itG++)
	{
		PGameItem p = *itG;
		//CLKImage *pImg = p->pImg;
		if (!p->pImg)
		{
			p->pImg = new CLKImage;
			if (!p->pImg->LoadEx(p->strGameIcon))
			{
				delete p->pImg;
				p->pImg = 0;
			}
			//p->pImg = pImg;
		}
		list<PGameItem>::iterator itNext = itG;

		m_Container.InsertItem(StrToInt(p->strGameId), p->strGameName, p->strGameFlag, p->pImg, p, (++itNext == lt.end() ? true : false), p->strPopPathname);
	}
	m_Container.CalcVisibleCtrl();
	m_Container.Invalidate();

	//m_Container.DeleteAllItem();
	//PLKTREEITEM pItem = m_treeMain.GetCurSelected();
	//if (pItem)
	//{
	//	int nId = (int)pItem->pData;
	//	list<PGameItem> lt;
	//	if (nId == 0)
	//	{
	//		CLocalDataInfo::GetInstance()->GetGameList(lt);
	//	}
	//	else
	//	{
	//		CLocalDataInfo::GetInstance()->GetGameList(nId, lt);
	//	}
	//	for (list<PGameItem>::iterator itG = lt.begin(); itG != lt.end(); itG++)
	//	{
	//		PGameItem p = *itG;
	//		//CLKImage *pImg = p->pImg;
	//		if (!p->pImg)
	//		{
	//			p->pImg = new CLKImage;
	//			if (!p->pImg->LoadEx(p->strGameIcon))
	//			{
	//				delete p->pImg;
	//				p->pImg = 0;
	//			}
	//			//p->pImg = pImg;
	//		}
	//		list<PGameItem>::iterator itNext = itG;

	//		m_Container.InsertItem(StrToInt(p->strGameId), p->strGameName, p->pImg, p, (++itNext == lt.end() ? true : false), p->strPopPathname);
	//	}
	//}
	//m_Container.Invalidate();
}

void CmyouboxDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		//CAboutDlg dlgAbout;
		//dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CmyouboxDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CmyouboxDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CmyouboxDlg::OnSize(UINT nType, int cx, int cy)
{
	CLKMainDialog::OnSize(nType, cx, cy);
	AdjustChildCtrl();
}

// 调整子控件的位置
void CmyouboxDlg::AdjustChildCtrl()
{
	CRect rt;
	GetClientRect(&rt);
	if (m_treeMain.GetSafeHwnd())
	{
		// 搜索框
		//CRect rtSearch(0, 14, 250, 53);
		//rtSearch.left = rt.Width() / 2 - 130;
		//rtSearch.right = rtSearch.left + 360;
		CRect rtSearch(0, 76, 250, 115);
		rtSearch.right = rt.right - 60;
		rtSearch.left = rtSearch.right - 360;
		m_ctlSearch.MoveWindow(rtSearch);

		// 搜索按钮
		CRect rtBtn(rt.right - 60, rtSearch.top, rt.right, rtSearch.bottom);
		rtBtn.left += 3;
		rtBtn.top += 4;
		rtBtn.right = rtBtn.left + 32;
		rtBtn.bottom = rtBtn.top + 32;
		m_BtnSearch.MoveWindow(rtBtn);

		CRect rtTree(0, g_nTopHeight, g_nTreeWidth, rt.bottom);
		m_treeMain.MoveWindow(rtTree);

		CRect rtTab(rtTree.right + g_nTabLeftOffset, g_nTopHeight + 10, rt.right, g_nTopHeight + 10 + g_nTabHeight);
		m_tabMain.MoveWindow(rtTab);

		//CRect rtContainer(rtTree.right, rtTab.bottom + 2, rt.right, rt.bottom);
		CRect rtContainer(rtTree.right, rtTab.bottom + 14, rt.right, rt.bottom);
		m_Container.MoveWindow(rtContainer);
		Invalidate();
	}
}

// 更新其它窗口
void CmyouboxDlg::UpdateAllDlgBGImg()
{
	m_ctlSearch.SendMessage(LKCOMMON_MSG, LKCOMMON_MSG_WPARAM_RESETMEM, 0);

	// 皮肤窗口
	//
	// 
}

void CmyouboxDlg::OnBnClickedButtonSearch()
{
	//m_BtnSearch.ShowWindow(SW_HIDE);
	if (m_ctlSearch.IsWindowVisible())
	{
		m_ctlSearch.SetWindowText(L"");
	}
	m_ctlSearch.ShowWindow(m_ctlSearch.IsWindowVisible() ? SW_HIDE : SW_SHOW);
}
void CmyouboxDlg::OnEnChangeEdit()
{
	if (!m_ctlSearch.IsWindowVisible())
	{
		//m_BtnSearch.ShowWindow(SW_HIDE);
		m_ctlSearch.ShowWindow(SW_SHOW);
		//CString s = m_ctlSearch.GetText();
		//s = s.Right(1); 
		//m_ctlSearch.SetWindowText(s);
	}
	OnEBnClickedButtonSearchI();
}

void CmyouboxDlg::OnEBnClickedButtonSearch()
{
	//OnEBnClickedButtonSearchI();
	//m_ctlSearch.SetWindowText(L"");
	//m_ctlSearch.ShowWindow(SW_HIDE);
	//m_BtnSearch.ShowWindow(SW_SHOW);
}
void CmyouboxDlg::OnEBnClickedButtonSearchI()
{
	m_tabMain.DelAllItem();
	list<PGameItem> lt;
	CString strKey = m_ctlSearch.GetText();
	strKey.Trim();
	if (!strKey.IsEmpty())
	{
		CLocalDataInfo::GetInstance()->GetGameListBySearch(strKey, lt);
		m_tabMain.AddItem(_T("搜索游戏"));

		m_Container.DeleteAllItem();
		for (list<PGameItem>::iterator itG = lt.begin(); itG != lt.end(); itG++)
		{
			PGameItem p = *itG;
			if (!p->pImg)
			{
				p->pImg = new CLKImage;
				if (!p->pImg->LoadEx(p->strGameIcon))
				{
					delete p->pImg;
					p->pImg = 0;
				}
			}
			list<PGameItem>::iterator itNext = itG;

			m_Container.InsertItem(StrToInt(p->strGameId), p->strGameName, p->strGameFlag, p->pImg, p, (++itNext == lt.end() ? true : false), p->strPopPathname);
		}
		m_Container.CalcVisibleCtrl();
		m_Container.Invalidate();
		m_tabMain.Invalidate();

	}
}

// 右键处理
void CmyouboxDlg::OnTrayRButtonUp()
{
	CTrayMainMenu menu;
	menu.Show(this);
}

// 最小化按钮被按下
void CmyouboxDlg::OnMinClick()
{
	CLKDialog::OnMinClick();
}

// 事件
BOOL CmyouboxDlg::OnEnterPress(HWND hCrtl, LPARAM lparam)
{
	OnEBnClickedButtonSearch();
	return TRUE;
}

// 左键按下
void CmyouboxDlg::OnTrayLButtonDown()
{
	OnOpenMainPanel();
}

void CmyouboxDlg::OnOpenMainPanel()
{
	OpenMainPanel();
	//if (!IsWindowVisible())
	//{
	//	ShowWindow(SW_SHOW);
	//}
	//SetForegroundWindow();
}


void CmyouboxDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLKMainDialog::OnShowWindow(bShow, nStatus);

	if (!bShow)
	{
		m_Container.HideDlg();
	}
	// TODO:  在此处添加消息处理程序代码
}

void CmyouboxDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (10000 == nIDEvent)
	{
		KillTimer(nIDEvent);
		if (m_strMainProcess.IsEmpty())
		{
			DWORD dw = WaitForSingleObject(m_hStartProcess, 10);
			if (dw != WAIT_TIMEOUT)
			{
				ShowWindow(SW_RESTORE);
				CloseHandle(m_hStartProcess);
				m_hStartProcess = 0;
				CLogClient::WriteLog("程序退出。");
				return;
			}
			SetTimer(10000, 1000, 0);
		}
		else 
		{
			CString strName = m_strMainProcess.Right(m_strMainProcess.GetLength() - m_strMainProcess.ReverseFind(L'\\') - 1);
			if (GetProcessidFromName(strName))
			{
				SetTimer(10000, 3000, 0);
			}
			else
			{
				ShowWindow(SW_RESTORE);
				m_strMainProcess = L"";
				CLogClient::WriteLog("程序退出2。");
			}
		}
		return;
	}
	else if (nIDEvent == 10001)
	{
		KillTimer(nIDEvent);
		PostMessage(LKCOMMON_MSG, LKCOMMON_MSG_WPARAM_RESETMEM);
		CLogClient::WriteLog("从全屏游戏中恢复4");
		OnTreeCtrlSelectedChanged(0);
		//CString strInfo;
		//strInfo.Format(L"CLKContainer::OnTimer \r\n");
		//::OutputDebugString(strInfo);
	}
	else if (nIDEvent == 10002)
	{
		KillTimer(nIDEvent);
		CLocalDataInfo::GetInstance()->SetUploadGameItem(L"", L"", L"");
	}
	CLKMainDialog::OnTimer(nIDEvent);
}

bool CmyouboxDlg::GetProcessidFromName(CString &strName)
{
	PROCESSENTRY32 pe;
	bool bRet = false;
	DWORD id = 0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pe.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hSnapshot, &pe))
	{
		return 0;
	}
	while (1)
	{
		pe.dwSize = sizeof(PROCESSENTRY32);
		if (Process32Next(hSnapshot, &pe) == FALSE)
			break;
		if (strName.CollateNoCase(pe.szExeFile) == 0)
		{
			id = pe.th32ProcessID;
			bRet = true;
			break;
		}
	}
	CloseHandle(hSnapshot);
	return bRet;
}

// 杀指定进程
bool CmyouboxDlg::KillProcessByProcessName(const CString& csAppName, bool& bIsProcessExist)
{
	//
	bool bResult = true;
	bIsProcessExist = false;

	//
	PROCESSENTRY32 pe;
	memset(&pe, 0, sizeof(PROCESSENTRY32));

	//
	try
	{
		HANDLE hShot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (!hShot)
		{
			DWORD dwErrorCode = ::GetLastError();
			CLogError::WriteLog("杀进程  失败，获取系统进程快照失败(%d)", dwErrorCode);
			return false;
		}

		pe.dwSize = sizeof(PROCESSENTRY32);	//	一定要先为dwSize赋值
		if (::Process32First(hShot, &pe))
		{
			do
			{
				CString csAppNameTmp = pe.szExeFile;
				CString csAppNameP = csAppName;
				csAppNameTmp.MakeLower();
				csAppNameP.MakeLower();

				int nAt = csAppNameP.ReverseFind('.');
				csAppNameP = csAppNameP.Left(nAt);
				int nNameLen = csAppNameP.GetLength();
				//
				if (csAppNameTmp.Left(nNameLen) == csAppNameP)
				{
					//
					bIsProcessExist = TRUE;
					//
					HANDLE hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe.th32ProcessID);
					if (!hProcess)
					{
						DWORD dwErrorCode = ::GetLastError();
						CLogError::WriteLog("杀进程  失败，打开指定进程失败(%d)", dwErrorCode);
					}
					else
					{
						bResult = !!::TerminateProcess(hProcess, 0);
						CLogError::WriteLog("杀进程  TerminateProcess end: %d", bResult);
						if (!bResult)
						{
							DWORD dwErrorCode = ::GetLastError();
						}
						::CloseHandle(hProcess);
					}
					break;
				}
			} while (::Process32Next(hShot, &pe));
		}
		else
		{
			DWORD dwErrorCode = ::GetLastError();
			CLogError::WriteLog("杀进程  失败，获取快照中首进程失败(%d)", dwErrorCode);
		}
		//
		::CloseHandle(hShot);
	}
	catch (...)
	{
	}

	//
	return bResult;
}

UINT CmyouboxDlg::RunGame(LPVOID lParam)
{
	//if (!p->strGameStartProgram.IsEmpty())
	//{
	//	int nIndex = p->strGameStartProgram.ReverseFind(L'\\');
	//	CString strPath = p->strGameStartProgram.Left(nIndex);
	//	::SetCurrentDirectory(strPath);

	//	STARTUPINFO si;
	//	PROCESS_INFORMATION pi;
	//	ZeroMemory(&si, sizeof(si));
	//	si.cb = sizeof(si);
	//	ZeroMemory(&pi, sizeof(pi));
		// Start the child process. 
		//if (CreateProcess(NULL,   // No module name (use command line)
		//	p->strGameStartProgram.GetBuffer(),        // Command line
		//	NULL,           // Process handle not inheritable
		//	NULL,           // Thread handle not inheritable
		//	FALSE,          // Set handle inheritance to FALSE
		//	0,              // No creation flags
		//	NULL,           // Use parent's environment block
		//	NULL,           // Use parent's starting directory 
		//	&si,            // Pointer to STARTUPINFO structure
		//	&pi)           // Pointer to PROCESS_INFORMATION structure
		//	)
		//{
		//	//ShowWindow(SW_MINIMIZE);
		//	//if (p->strGameStartProgram.CompareNoCase(p->strGameMainProcessName) != 0)
		//	//{
		//	//	CloseHandle(pi.hProcess);
		//	//	pi.hProcess = 0;
		//	//	m_strMainProcess = p->strGameMainProcessName;
		//	//}
		//	//else
		//	//{
		//	//	m_strMainProcess = L"";
		//	//	m_hStartProcess = pi.hProcess;
		//	//}
		//	//SetTimer(10000, 1000, 0);
		//	//CloseHandle(pi.hThread);
		//	//pi.hThread = 0;
		//	CLogClient::WriteLog("程序运行成功。");
		//}
		//else
		//{
	DWORD dwTime = ::GetTickCount64();
	CString strId;
	CString strName;
	CString strPath;
	CLocalDataInfo::GetInstance()->GetUploadGameItem(strId, strName, strPath);
	HINSTANCE h = ShellExecute(NULL, L"open", strPath.GetBuffer(), NULL, NULL, SW_SHOWNORMAL);
	CLogClient::WriteLogW(L"执行程序: %d -- %s", (int)h, strPath.GetBuffer());
	if ((int)h < 32)
	{
		CStringA s; 
		s = strPath;
		CLogError::WriteLog("执行程序%s失败: %d", s.GetBuffer(), (int)h);
	}
	else
	{
		//ShowWindow(SW_MINIMIZE);
		CLogClient::WriteLog("程序运行成功2。");
	}
		////}
		// 上传游戏数据
		CStringA sId, sName;
		sId = strId;
		sName = strName;
		CCenterInterface::UploadGameInfo(sId.GetBuffer(), sName.GetBuffer());
		DWORD dwDiff = ::GetTickCount64() - dwTime;
		if (dwDiff < 5 * 1000)
		{
			Sleep(5 * 1000 - dwDiff);
		}
		CLocalDataInfo::GetInstance()->SetUploadGameItem(L"", L"", L"");
		CLogClient::WriteLog("设置空的参数。");
		//}
		return 0;
}

UINT CmyouboxDlg::RunTimer(LPVOID lParam)
{
	//Sleep(3000);
	//::PostMessage((HWND)lParam, LKCOMMON_MSG, 106, 0);
	//Sleep(3000);
	//::PostMessage((HWND)lParam, LKCOMMON_MSG, 106, 0);
	return 0;
}

void CmyouboxDlg::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// 此功能要求 Windows Vista 或更高版本。
	// _WIN32_WINNT 符号必须 >= 0x0600。
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CLKMainDialog::OnMouseHWheel(nFlags, zDelta, pt);
}


BOOL CmyouboxDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	//CRect rt;
	//GetClientRect(&rt);
	//CRect rtTree(0, g_nTopHeight, g_nTreeWidth, rt.bottom);

	//if (rtTree.PtInRect(pt))
	//{
	//	m_treeMain.OnMouseWheel(nFlags, zDelta, pt);
	//}
	//else
	//{
		m_Container.OnMouseWheel(nFlags, zDelta, pt);
	//}
	return CLKMainDialog::OnMouseWheel(nFlags, zDelta, pt);
}



void CmyouboxDlg::OnMoving(UINT fwSide, LPRECT pRect)
{
	//static CRect rt(0, 0, 0, 0);
	//if (rt.IsRectEmpty()) GetWindowRect(&rt);
	CLKMainDialog::OnMoving(fwSide, pRect);
	//int nX = pRect->left - rt.left;
	//int nY = pRect->top - rt.top;
	//m_Container.AdjustFlagDlg(nX, nY);
	//rt = *pRect;
	// TODO:  在此处添加消息处理程序代码
}


void CmyouboxDlg::OnMove(int x, int y)
{
	static CRect rt(0, 0, 0, 0);
	if (rt.IsRectEmpty()) GetWindowRect(&rt);
	CLKMainDialog::OnMove(x, y);
	m_Container.AdjustFlagDlg(x - rt.left, y - rt.top);
	rt.MoveToXY(x, y);

	// TODO:  在此处添加消息处理程序代码
}


void CmyouboxDlg::OnActivateApp(BOOL bActive, DWORD dwThreadID)
{
	CLKMainDialog::OnActivateApp(bActive, dwThreadID);
	//CLogClient::WriteLog("从全屏游戏中恢复5：%d", bActive);
	if (bActive)
	{
		//PostMessage(LKCOMMON_MSG, LKCOMMON_MSG_WPARAM_RESETMEM);
		//OnTreeCtrlSelectedChanged(0);
		this->SetActiveWindow();
	}
	//CString strInfo;
	//strInfo.Format(L"OnActivateApp %d\r\n", bActive);
	//::OutputDebugString(strInfo);

	//m_Container.FlashFocuDlg();
}


LRESULT CmyouboxDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (WM_SYNCPAINT == message)
	{
		CLogClient::WriteLog("从全屏游戏中恢复：%d, %d", wParam, lParam);
		//m_Container.FlashFocuDlg();
		//AdjustChildCtrl();
		//SetTimer(10001, 200, 0);
		OnTreeCtrlSelectedChanged(0);
		m_Container.CalcVisibleCtrl();
		m_Container.Invalidate();
		//CString strInfo;
		//strInfo.Format(L"WM_SYNCPAINT \r\n");
		//::OutputDebugString(strInfo);
		return 1;
	}
	if (WM_DISPLAYCHANGE == message)
	{
		static bool b = true;
		CString strInfo;
		strInfo.Format(L"WM_DISPLAYCHANGE: %d, %d, %d, %d, %d \r\n", b, LOWORD(lParam), HIWORD(lParam), SCREEN_WIDTH, SCREEN_HEIGHT);
		::OutputDebugString(strInfo);
		CLogClient::WriteLog("从全屏游戏中恢复：%d, %d", LOWORD(lParam), HIWORD(lParam));
		if (SCREEN_WIDTH == g_nScreenWidth)
		{
			::AfxBeginThread(RunTimer, GetSafeHwnd());
			ShowWindow(SW_SHOW);
		}
		else
		{
			ShowWindow(SW_HIDE);
		}
		//if (b)
		//{
		//	//ShowWindow(SW_MINIMIZE);
		//}
		//else
		//{
		//	CLogClient::WriteLog("从全屏游戏中恢复2");
			//PostMessage(LKCOMMON_MSG, 106);
		//}
		//b = !b;
		//LRESULT l = CLKMainDialog::WindowProc(message, wParam, lParam);
		//
		//PostMessage(LKCOMMON_MSG, 106);
		//////m_Container.FlashFocuDlg();
		//////AdjustChildCtrl();
		//////SetTimer(10001, 200, 0);
		////static int x = false;
		////if (x)
		////{
		////	CLogClient::WriteLog("从全屏游戏中恢复2：%d, %d", wParam, lParam);
		////	OnTreeCtrlSelectedChanged(0);
		////	m_Container.FlashFocuDlg();
		////	m_Container.Invalidate();
		////}
		////x = !x;
		//CString strInfo;
		//strInfo.Format(L"WM_DISPLAYCHANGE: %d, %d, %d, %d \r\n", LOWORD(lParam), HIWORD(lParam), SCREEN_WIDTH, SCREEN_HEIGHT);
		//::OutputDebugString(strInfo);
		//return l;
	}

	return CLKMainDialog::WindowProc(message, wParam, lParam);
}


BOOL CmyouboxDlg::DestroyWindow()
{
	// TODO:  在此添加专用代码和/或调用基类
	if (m_pToolTip)
	{
		m_pToolTip->DestroyWindow();
	}
	if (m_pChildToolTip)
	{
		m_pChildToolTip->DestroyWindow();
	}
	m_Container.DestroyWindow();
	return CLKMainDialog::DestroyWindow();
}
