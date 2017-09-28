
// myouboxDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "myoubox.h"
#include "myouboxDlg.h"
#include "afxdialogex.h"
#include "ConfigFile.h"
#include "log.h"
#include "CenterInterface.h"
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

// ������ID
#define MAINDLG_EDITID_SEARCH	100
// ������ť
#define LOGINDLG_BUTTONID_SEARCH 101
// ��ĸ��ť��ʼID
#define LOGINDLG_BUTTONID_ABEG	102


const int g_nTopHeight = 95;
// ���οؼ����
const int g_nTreeWidth = 161;
// ������Ϸ����ؼ��߶�
const int g_nLGameTypeHeight = 154;
// Tab��ҳ�ؼ��߶�
const int g_nTabHeight = 22;
// Tab��ҳ�ؼ���ƫ��
const int g_nTabLeftOffset = 15;

// �������URL
#define TOP_AD_URL	L"http://res-youtop.stnts.com/bd/v2/space/extm-001-top/frame.html"
//#define TOP_AD_URL	L"http://cn.bing.com/?mkt=zh-CN&mkt=zh-CN&mkt=zh-CN" //L"http://xxxxxasdfasdadf.com"//

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

//#ifdef _DEBUG
//// ������
//void CmyouboxDlg::TestInitLGameList()
//{
//	CLKImage *pImg = new CLKImage;
//	CString strImg = CConfigFile::GetInstance()->GetImageFilePathW().c_str();
//	strImg += L"\\1.jpg";
//	if (pImg->LoadEx(strImg, false))
//	{
//		m_LContainer.InsertItem(0, L"", 0, pImg, 0, false);
//	}
//
//	pImg = new CLKImage;
//	strImg = CConfigFile::GetInstance()->GetImageFilePathW().c_str();
//	strImg += L"\\2.jpg";
//	if (pImg->LoadEx(strImg, false))
//	{
//		m_LContainer.InsertItem(0, L"", 0, pImg, 0, false);
//	}
//
//	pImg = new CLKImage;
//	strImg = CConfigFile::GetInstance()->GetImageFilePathW().c_str();
//	strImg += L"\\3.jpg";
//	if (pImg->LoadEx(strImg, false))
//	{
//		m_LContainer.InsertItem(0, L"", 0, pImg, 0, false);
//	}
//
//	pImg = new CLKImage;
//	strImg = CConfigFile::GetInstance()->GetImageFilePathW().c_str();
//	strImg += L"\\4.jpg";
//	if (pImg->LoadEx(strImg, false))
//	{
//		m_LContainer.InsertItem(0, L"", 0, pImg, 0, false);
//	}
//
//	pImg = new CLKImage;
//	strImg = CConfigFile::GetInstance()->GetImageFilePathW().c_str();
//	strImg += L"\\5.jpg";
//	if (pImg->LoadEx(strImg, false))
//	{
//		m_LContainer.InsertItem(0, L"", 0, pImg, 0, false);
//	}
//
//	pImg = new CLKImage;
//	strImg = CConfigFile::GetInstance()->GetImageFilePathW().c_str();
//	strImg += L"\\6.jpg";
//	if (pImg->LoadEx(strImg, false))
//	{
//		m_LContainer.InsertItem(0, L"", 0, pImg, 0, false);
//	}
//
//	pImg = new CLKImage;
//	strImg = CConfigFile::GetInstance()->GetImageFilePathW().c_str();
//	strImg += L"\\7.jpg";
//	if (pImg->LoadEx(strImg, false))
//	{
//		m_LContainer.InsertItem(0, L"", 0, pImg, 0, false);
//	}
//
//	pImg = new CLKImage;
//	strImg = CConfigFile::GetInstance()->GetImageFilePathW().c_str();
//	strImg += L"\\8.jpg";
//	if (pImg->LoadEx(strImg, false))
//	{
//		m_LContainer.InsertItem(0, L"", 0, pImg, 0, false);
//	}
//
//	pImg = new CLKImage;
//	strImg = CConfigFile::GetInstance()->GetImageFilePathW().c_str();
//	strImg += L"\\9.jpg";
//	if (pImg->LoadEx(strImg, false))
//	{
//		m_LContainer.InsertItem(0, L"", 0, pImg, 0, false);
//	}
//
//	pImg = new CLKImage;
//	strImg = CConfigFile::GetInstance()->GetImageFilePathW().c_str();
//	strImg += L"\\10.jpg";
//	if (pImg->LoadEx(strImg, false))
//	{
//		m_LContainer.InsertItem(0, L"", 0, pImg, 0, false);
//	}
//
//	pImg = new CLKImage;
//	strImg = CConfigFile::GetInstance()->GetImageFilePathW().c_str();
//	strImg += L"\\11.jpg";
//	if (pImg->LoadEx(strImg, false))
//	{
//		m_LContainer.InsertItem(0, L"", 0, pImg, 0, false);
//	}
//
//	m_LContainer.CalcVisibleCtrl();
//}
//#endif

CmyouboxDlg::CmyouboxDlg(CWnd* pParent /*=NULL*/)
	//: CDialogEx(CmyouboxDlg::IDD, pParent)
	: CLKMainDialog(CmyouboxDlg::IDD, pParent)
	, m_ctlSearch(1)
	, m_treeMain(0)
	// ��Ϸ�б�
	//, m_LContainer(1)
	, m_Container(1)
	//, m_BtnSearch(0)
{
	m_pSkinImg = new CLKImage;
	int nS = sizeof(CLKImage);
	////CString sw = L"��";
	//char sw[10] = { "��" };
	////std::string s = xm2m_utf8(sw.c_str(), sw.size());
	//word *p = (word *)sw;
	//int n1 = htons(*p);
	//int n2 = *(p + 1);

	//CString strName = L"xx";
	//GetProcessidFromName(strName);
	//test();
	//SetTopOffset(0);
	//SetRightOffset(10);
	m_bMinSize = CPoint(1530, 900);
	//m_bMinSize = CPoint(600, 380);
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//m_hSmallIcon = (HICON)::LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDR_MAINFRAME), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	InitImageList();
	CRect rt(0, 0, 0, 0);
	SetNCClientRect(rt);
	SetFillet(false);
	SetIsDrawDlgFram(false);
	//SetIsFillDlgByImg(true);
	g_nScreenWidth = SCREEN_WIDTH;



	HKEY hkey;
	DWORD dwOption = 0;
	LPCTSTR lpszSubKey = _T("SOFTWARE\\Wow6432Node\\Microsoft\\Internet Explorer\\Main\\FeatureControl\\FEATURE_BROWSER_EMULATION");
	if (ERROR_SUCCESS == RegCreateKeyEx(HKEY_LOCAL_MACHINE, lpszSubKey, NULL, NULL, NULL, KEY_ALL_ACCESS, NULL, &hkey, &dwOption))
	{
		if (dwOption == REG_OPENED_EXISTING_KEY)
		{
			DWORD dwValue = 0;
			const int BUFSIZE = 1024;
			wchar_t szBuf[BUFSIZE] = { 0 };
			wchar_t exec_name[BUFSIZE] = { 0 };
			DWORD dwCount = 1024;
			DWORD szType = REG_DWORD;
			::GetModuleFileName(0, exec_name, BUFSIZE - 1);
			CString strName = exec_name;
			strName = strName.Right(strName.GetLength() - strName.ReverseFind(L'\\') - 1);
			if (RegQueryValueEx(hkey, strName, NULL, &szType, (LPBYTE)&dwValue, &dwCount) == ERROR_SUCCESS)
			{
				//dwValue = _ttoi(szBuf);
			}
			if (dwValue < 10000)
			{
				dwValue = 10000;
				RegSetValueEx(hkey, strName, NULL, REG_DWORD, (BYTE*)&dwValue, sizeof(dwValue));
				RegCloseKey(hkey);
			}
		}
	}

}

CmyouboxDlg::~CmyouboxDlg()
{
	if (m_hSmallIcon)
	{
		::DestroyIcon(m_hSmallIcon);
		m_hSmallIcon = 0;
	}
	CLocalDataInfo::FreeInstance();
	if (m_pSkinImg)
	{
		delete m_pSkinImg;
		m_pSkinImg = 0;
	}
}

void CmyouboxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

// ��ʼ��ͼƬ�б�
void CmyouboxDlg::InitImageList()
{
	// ��ʼ��ͼƬ�б�
	CLKDialog::InitImageList();
	m_arrImage[LKGDIBASEDIALOG_IMAGEINDEX_MAX] = 0;
	m_arrImage[LKGDIBASEDIALOG_IMAGEINDEX_RESTORE] = 0;


	CString strImg = CConfigFile::GetInstance()->GetCurSkin().c_str();
	if (!strImg.IsEmpty())
	{
		if (m_pSkinImg->LoadEx(strImg))
		{
			m_arrImage[LKGDIBASEDIALOG_IMAGEINDEX_BG] = m_pSkinImg;
		}
	}
	
	//CLKImageMgr::GetInstance()->SetJPGImage(LKGDIBASEDIALOG_IMAGEINDEX_BG + LKIMAGELISTINDEX_DIALOG_BEGIN, IDR_JPG_MAINBG);
	////m_pBGImg = CLKImageMgr::GetImageS(LOGINBG_IMAGE);
	////if (m_pBGImg)
	////{
	////	m_bMinSize.x = m_pBGImg->GetWidth();
	////	m_bMinSize.y = m_pBGImg->GetHeight();
	////}
}

// ��ʼ������ǰ��ͼƬ
void CmyouboxDlg::OnInitMemImg()
{
	// ͷ������
	CLKImage *pImgHBG = CLKImageMgr::GetImageS(LKIMAMYOUBOX_DIALOG_HEAD);
	CLKImage *pImg = GetMemImage();
	if (pImgHBG && pImg)
	{
		CRect rtHBG(0, 0, m_rtWnd.Width() - 0, pImgHBG->GetHeight());
		pImgHBG->DrawToImage(pImg, rtHBG);
	}
	// ͷ����ǩ
	CString strImg = CConfigFile::GetInstance()->GetLogoFilePathW().c_str();
	CLKImage img;
	CLKImage *pImgHL = 0;
	if (img.LoadEx(strImg))
	{
		pImgHL = &img;
	}
	else
	{
		pImgHL = CLKImageMgr::GetImageS(LKIMAMYOUBOX_DIALOG_HEADLABEL);
	}

	if (pImgHL && pImg)
	{
		CRect rtHL(0, 0, pImgHL->GetWidth(), pImgHL->GetHeight());
		rtHL.MoveToXY(30, (g_nTopHeight - pImgHL->GetHeight()) / 2);
		pImgHL->DrawToImage(pImg, rtHL);
	}

	//// ���ָ���
	//CLKImage *pImgSplit = CLKImageMgr::GetImageS(LKIMAGELISTINDEX_COMMON_SPLIT);
	//if (pImgSplit && pImg)
	//{
	//	CRect rt(g_nTreeWidth, g_nTopHeight + g_nLGameTypeHeight + 22, m_rtWnd.Width(), g_nTopHeight + g_nLGameTypeHeight + pImgSplit->GetHeight() + 22);
	//	pImgSplit->DrawToImage(pImg, rt);
	//}

	// ��������
	CStringA sMachineA = CConfigFile::GetInstance()->GetLocalMachineName().c_str();
	CString sMachine(L"�����ţ� ");
	sMachine += sMachineA;
	sMachine += L"    �Ʋ˵�";
	CRect rtText(m_rtWnd.Width() - 500, 4, m_rtWnd.Width() - 100, 22);
	pImg->DrawImgText(sMachine, rtText, CLKFontMgr::GetMSYHPoint12(), DT_RIGHT | DT_VCENTER | DT_SINGLELINE, RGB(255, 255, 255));
}

LRESULT CmyouboxDlg::OnCommonMsg(WPARAM wParam, LPARAM lParam)
{
	if (LKCONTAINER_MSG_WPARAM_ADDLGONCLICK == wParam)
	{
		ADClickInfo *pClickInfo = (ADClickInfo *)lParam;
		if (pClickInfo)
		{
			CLogClient::WriteLogW(L"TOP�����: %s", pClickInfo->strGame.GetBuffer());
			PGameItem p = CLocalDataInfo::GetInstance()->GetGameByName(pClickInfo->strGame);
			if (p)
			{
				OnProcRunGameReq(p);
			}
			else
			{
				HINSTANCE h = ShellExecute(NULL, L"open", pClickInfo->strLink.GetBuffer(), NULL, NULL, SW_SHOWNORMAL);
				if ((unsigned int)h < 0x1f)
				{
					CLogError::WriteLogW(L"Ĭ�����������%sʧ�ܣ����� Error: %d/%d", pClickInfo->strLink.GetBuffer(), (int)h, GetLastError());
					h = ShellExecute(NULL, L"open", L"IEXPLORE.EXE", pClickInfo->strLink.GetBuffer(), NULL, SW_SHOWMAXIMIZED);
					if ((unsigned int)h < 32)
					{
						CLogError::WriteLogW(L"IE����%sʧ�ܣ����� Error: %d", pClickInfo->strLink.GetBuffer(), GetLastError());
					}
				}
				else if ((unsigned int)h < 32)
				{
					CLogError::WriteLogW(L"Ĭ�����������%sʧ�ܣ����� Error: %d/%d", pClickInfo->strLink.GetBuffer(), (int)h, GetLastError());
				}
			}
		}
	}
	else if (LKBUTTONEX_MSG_WPARAM_SELECTED == wParam)
	{
		m_bChangeSkin = true;
		CLKImage *pImg = (CLKImage *)lParam;
		ChangeBGImg(pImg);
		// ������������
		UpdateAllDlgBGImg();
		// ���������ؼ� 
		SendMessage(LKCOMMON_MSG, LKCOMMON_MSG_WPARAM_RESETMEM, 0);
	}
	else if (LKCONTAINER_MSG_WPARAM_ITEMBTNCLICKED == wParam)
	{
		//MessageBeep(100);
		CLogClient::WriteLog("ͼ�걻���");
		PGameItem p = (PGameItem)lParam;
		OnProcRunGameReq(p);
	}
	else if (LKTREECTRL_MSG_WPARAM_ITEMCHANGED == wParam)
	{
		// �������οؼ�ѡ����ı�
		OnTreeCtrlSelectedChanged((PLKTREEITEM)lParam);
		//CRect rt(0, 0, 200, 100);
		//CLKBalloonWnd::Show(&m_treeMain, rt, _T("��д�����Ѵ�"));
	}
	else if (LKTAP_MSG_WPARAM_ITEMCHANGED == wParam)
	{
		// ����TAB�ؼ�ѡ����ı�
		OnTabCtrlSelectedChanged();
	}
	else if (106 == wParam)
	{
		////CLogClient::WriteLog("��ȫ����Ϸ�лָ�2��%d, %d", wParam, lParam);
		//OnTreeCtrlSelectedChanged(0);
		//m_Container.CalcVisibleCtrl();
		//m_Container.Invalidate();
		PostMessage(LKCOMMON_MSG, LKCOMMON_MSG_WPARAM_RESETMEM);
		//OnTreeCtrlSelectedChanged(0);
		CLogClient::WriteLog("��ȫ����Ϸ�лָ�3");
		//SetTimer(10001, 300, 0);
	}
	else if (LKADDLG_MSG_WPARAM_SUCCESS == wParam)
	{
		//CRect rtContainer(161, 277, 1530, 900);
		//m_Container.MoveWindow(rtContainer);
		SetTimer(20001, 1000, 0);
	}
	else
	{
		CLKDialog::OnCommonMsg(wParam, lParam);
	}
	if (LKCOMMON_MSG_WPARAM_RESETMEM == wParam)
	{
		//m_TopAd.Invalidate(true);
		//m_TopAd.UpdateWindow();
		//m_TopAd.ShowWindow(SW_HIDE);
		//m_TopAd.ShowWindow(SW_SHOW);
		//Invalidate(false);
		m_TopAd.SetWindowPos(0, 0, 0, 0, 0, SWP_HIDEWINDOW | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOREDRAW);
		m_TopAd.SetWindowPos(0, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
		//m_TopAd.PostMessage(WM_NCPAINT);
		//m_TopAd.PostMessage(WM_SYNCPAINT);
		//m_TopAd.RedrawWindow(0, 0, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_FRAME);
	}
	return 1; 
}

// �Զ���˵���ť������
void CmyouboxDlg::OnMenuClick()
{
	CChangeSkinDlg dlg;
	dlg.DoModal();
	//Invalidate();
	//m_TopAd.ShowWindow(SW_HIDE);
	//m_TopAd.ShowWindow(SW_SHOW);
}
// �ж�����Ƿ��������Զ�������Χ��
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
	//ON_BN_CLICKED(MAINDLG_EDITID_SEARCH, &CmyouboxDlg::OnEBnClickedButtonSearch)
	ON_EN_CHANGE(MAINDLG_EDITID_SEARCH, &CmyouboxDlg::OnEnChangeEdit)

	//ON_BN_CLICKED(MAINDLG_EDITID_SEARCH, &CmyouboxDlg::OnBnClickedButtonSearch)
	// �����
	ON_COMMAND(TRAYMAINMENUITEM_ID_OPENMAINPANEL, OnOpenMainPanel)
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_WM_MOUSEHWHEEL()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOVING()
	ON_WM_MOVE()
	ON_WM_ACTIVATEAPP()
END_MESSAGE_MAP()


// CmyouboxDlg ��Ϣ�������

BOOL CmyouboxDlg::OnInitDialog()
{
	//CDialogEx::OnInitDialog();
	//SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	//SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	//// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	CLKDialog::OnInitDialog();
	ModifyStyle(0, WS_MINIMIZEBOX);
	SetWindowPos(0, 0, 0, 1530, 900, SWP_NOMOVE | SWP_NOZORDER);

	CStringA strTextA = CConfigFile::GetInstance()->GetMenuName().c_str();
	CString strText; strText = strTextA;
	SetWindowText(strText);
	CRect rt;
	GetClientRect(&rt);

	EnableToolTips();
	m_pToolTip = &m_ToolTip;// new CLKToolTipCtrl;
	m_pToolTip->Create(this);
	m_pToolTip->Activate(TRUE);
	m_pToolTip->AddTool(this, _T(""));//���tip

	m_pChildToolTip = &m_ChildToolTip;// new CLKToolTipCtrl;
	m_pChildToolTip->Create(this);
	m_pChildToolTip->Activate(TRUE);

	int nTopTabLeft = rt.Width() / 2 - 300;
	//int nTopTabTop = 0;
	//CRect rtTopTab(nTopTabLeft, nTopTabTop, rt.Width() / 2 + 300, nTopTabTop + g_nTopHeight - 10);
	CRect rtTopTab(254, 0, 254 + 600, g_nTopHeight - 5);
	m_tabTop.Create(rtTopTab, this, 1013);
	m_tabTop.ShowWindow(SW_HIDE);
	m_tabTop.AddItem(CLKImageMgr::GetImageS(LKIMAMYOUBOX_TOPHOTGAMEITEM), 0, false);
	m_tabTop.AddItem(CLKImageMgr::GetImageS(LKIMAMYOUBOX_TOPPLAYGAMEITEM), 0, false);
	m_tabTop.AddItem(CLKImageMgr::GetImageS(LKIMAMYOUBOX_TOPMOVEITEM), 0, false);
	m_tabTop.AddItem(CLKImageMgr::GetImageS(LKIMAMYOUBOX_TOPCHATITEM), 0, false);
	m_tabTop.AddItem(CLKImageMgr::GetImageS(LKIMAMYOUBOX_TOPSMALLGAMEITEM), 0, false);
	m_tabTop.AddItem(CLKImageMgr::GetImageS(LKIMAMYOUBOX_TOPTOOLSITEM), 0, false);
	m_tabTop.SetMargin(0);

	// ������
	CRect rtSearch(0, 51, 250, 82);
	rtSearch.right = rt.right - 25;
	rtSearch.left = rtSearch.right - 360;
	//CLKImage *pE = CLKImageMgr::GetImageS(LKIMAGEBUTTONINDEX_EDITIMG);
	//m_ctlSearch.SetParseImg(pE);
	m_ctlSearch.SetClientOffset(CRect(0, 0, 0, 0));
	m_ctlSearch.SetClientEdge(CRect(12, 4, 12, 4));
	m_ctlSearch.SetTextFont(CLKFontMgr::GetMSYHPoint12());
	m_ctlSearch.SetTextBGCol(RGB(22, 25, 31));
	m_ctlSearch.SetTextColor(RGB(255, 255, 255));
	// �༭��ťͼƬ
	m_ctlSearch.SetBtnImage(CLKImageMgr::GetImageS(LKIMAGEBUTTONINDEX_EDITBUTTON));
	m_ctlSearch.Create(WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_WANTRETURN, rtSearch, this, MAINDLG_EDITID_SEARCH);
	//m_ctlSearch.ShowWindow(SW_HIDE);
	//m_ctlSearch.SetHintText(_T("��Ϸ��/ƴ��"));

	//// ������ť
	//CRect rtBtn(rtSearch.right, rtSearch.top, rt.right, rtSearch.bottom);
	//rtBtn.left += 3;
	//rtBtn.top += 4;
	//rtBtn.right = rtBtn.left + 18;
	//rtBtn.bottom = rtBtn.top + 18;
	//m_BtnSearch.SetIconWidthAndHeight(18, 18);
	//m_BtnSearch.SetTextFont(CLKFontMgr::GetMSYH13px());
	//m_BtnSearch.SetParseImage(LKIMAGEBUTTONINDEX_EDITBUTTON);
	//m_BtnSearch.Create(L"", rtBtn, this, LOGINDLG_BUTTONID_SEARCH); 
	////m_BtnSearch.SetImage(LKIMAGEBUTTONINDEX_EDITBUTTON);
	//m_BtnSearch.SetTextColor(RGB(255, 255, 255));

	CRect rtTree(0, g_nTopHeight, g_nTreeWidth, rt.bottom);
	m_treeMain.SetParseImg(CLKImageMgr::GetImageS(LKIMGMYOUBOX_TREE_BG));
	m_treeMain.SetSplitImg(CLKImageMgr::GetImageS(LKIMGMYOUBOX_TREE_SPLIT));
	m_treeMain.SetSelectMode(false);
	m_treeMain.SetItemHeight(44);
	m_treeMain.SetTopOffset(0);
	m_treeMain.Create(_T(""), rtTree, this, 3000);
	m_treeMain.SetTextColor(RGB(133, 143, 162));
	m_treeMain.SetTextFont(CLKFontMgr::GetMSYHPoint12());
	// ��ȡ�����
	PLKTREEITEM pRootItem = m_treeMain.GetRootItem();
	PLKTREEITEM pGItem = m_treeMain.InsertItem(_T("������Ϸ"), -1, pRootItem, 0, 0);
	m_treeMain.SetFirstItemToSelected();

	// ���б��
	CRect rtLContainer(rtTree.right + g_nTabLeftOffset, g_nTopHeight + 8, rt.right - 14, g_nTopHeight + 8 + g_nLGameTypeHeight);
	m_rtTopAd = rtLContainer;
	//m_LContainer.SetSubItemsOffest(CRect(0, 0, 0, 0)); 
	//m_LContainer.SetItemWidth(110);
	//m_LContainer.SetItemHeight(150);
	//m_LContainer.SetItemTextHeight(0);
	//m_LContainer.SetItemImgToCenter(true);
	//m_LContainer.SetItemSplit(13);
	//m_LContainer.SetFocusImage(CLKImageMgr::GetImageS(LKIMAMYOUBOX_TOPGAMEFOCUS));
	//m_LContainer.Create(_T("��Ϸ�б�"), rtLContainer, this, 3001, 0, IDR_GIF_FOCUS2);
	//m_LContainer.ShowWindow(SW_HIDE);
	//m_LContainer.SetTextColor(RGB(255, 255, 255));
	//m_LContainer.SetTextFont(CLKFontMgr::GetMSYHPoint10());
//#ifdef _DEBUG
//	TestInitLGameList();
//#endif

	//m_TopAd.Create(rtLContainer, this, 4002);
 //	m_TopAd.SetUrlString(IDD_DIALOG_TOPAD, TOP_AD_URL);
	m_TopAd.Create(IDD_DIALOG_TOPAD, this);
	m_rtTopAd.MoveToY(-2000);
	m_TopAd.MoveWindow(&m_rtTopAd);
	m_rtTopAd = rtLContainer;
	m_TopAd.m_pBrowserApp->put_Silent(VARIANT_TRUE);
	m_TopAd.Navigate(TOP_AD_URL);


	CRect rtTab(rtTree.right + g_nTabLeftOffset, rtLContainer.bottom + 8, rt.right, rtLContainer.bottom + 8 + g_nTabHeight);
	m_tabMain.Create(rtTab, this, 1003);
	m_tabMain.ShowWindow(SW_HIDE);
	m_tabMain.AddItem(_T("������Ϸ"));
	m_tabMain.SetMargin(0);
	//m_tabMain.SetIsAdjustItmeSize();
	m_tabMain.SelectItem();
	m_tabMain.SetTextColor(RGB(176, 176, 176));
	m_tabMain.SetTextFont(CLKFontMgr::GetMSYH13px());

	// С�б��
	int nBtnListTop = rtLContainer.top;
	CRect rtContainer(rtTree.right, nBtnListTop + 20, rt.right, rt.bottom);
	//m_Container.SetIsShowButton();
	m_Container.SetSubItemsOffest(CRect(10, 10, 0, 10));
	m_Container.SetItemWidth(70);
	m_Container.SetItemHeight(108);
	m_Container.SetItemTextHeight(40);
	//m_Container.SetFocusImage(CLKImageMgr::GetImageS(LKIMAMYOUBOX_TOPGAMEFOCUS));
	m_Container.SetFocusImage(CLKImageMgr::GetImageS(LKIMAMYOUBOX_GAMEFOCUS));
	m_Container.Create(_T("��Ϸ�б�"), rtContainer, this, 3002, 0, IDR_GIF_FOCUS2);
	//m_Container.Create(_T("��Ϸ�б�"), rtContainer, this, 3002, IDR_GIF_FOCUS, IDR_GIF_FOCUS2);
	m_Container.SetTextColor(RGB(255, 255, 255));
	m_Container.SetTextFont(CLKFontMgr::GetMSYHPoint10());
	//m_Container.SetTextFont(CLKFontMgr::GetMSYHPoint13());
	//m_pChildToolTip->AddTool(&m_Container, _T("�ƾ�����"));//���tip

	// ��ʼ����Ϸ�б�
	CLocalDataInfo::GetInstance()->InitGameList();
	// ������Ϸ����
	LoadGameInfo();
	// ������Ϸ��������
	LoadGameTypeInfo();
	// �ϴ��������� 
	CCenterInterface::UploadInfo();

	m_hSmallIcon = (HICON)::LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDR_MAINFRAME), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	m_hTrayIcon = m_hSmallIcon;
	m_hCurTrayIcon = m_hSmallIcon;
	InitTray();
	//UpdatTrayState();

	//CRgn rgn, rgn2;
	//CRect rc(m_rtWnd);
	//rc.MoveToXY(0, 0);
	//rgn.CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom); //����һ������
	//CRect rc2(m_rtTopAd);
	//rgn2.CreateRectRgn(rc2.left, rc2.top, rc2.right, rc2.bottom);
	//rgn.CombineRgn(&rgn, &rgn2, RGN_DIFF);
	//SetWindowRgn(rgn, TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control 
}

// ������Ϸ����
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
				//CLogClient::WriteLogW(L"����ͼ��·���� %s", s.GetBuffer());
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
						//CLogClient::WriteLogW(L"����ͼ��·��2�� %s", s.GetBuffer());
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
							//CLogClient::WriteLogW(L"����ͼ��·��3�� %s", s.GetBuffer());
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
	CLogClient::WriteLogW(L"ʵ�ʼ�����Ϸ������%d", m_Container.GetItemCount());
}

// ������Ϸ��������
void CmyouboxDlg::LoadGameTypeInfo()
{
	// ��ȡ��Ϸ���͵�һ�������б�
	CLogClient::WriteLogW(L"������Ϸ��������");
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
	//// ��ȡ��Ϸ���͵ڶ��������б�
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

// �������οؼ�ѡ����ı�
void CmyouboxDlg::OnTreeCtrlSelectedChanged(PLKTREEITEM pOldItem)
{
	// ��ȡ��ǰѡ����
	PLKTREEITEM pItem = m_treeMain.GetCurSelected();
	if (pItem)
	{
		m_tabMain.DelAllItem();
		int nId = (int)pItem->pData;
		list<PGameTypeItem> lt;
		if (nId == 0)
		{
			CLocalDataInfo::GetInstance()->GetGameTypeSecondLevelList(lt);
			m_tabMain.AddItem(_T("������Ϸ"));
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

// ����TAB�ؼ�ѡ����ı�
void CmyouboxDlg::OnTabCtrlSelectedChanged()
{
	//// ��ȡ��ǰѡ����
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CmyouboxDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CmyouboxDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CmyouboxDlg::OnSize(UINT nType, int cx, int cy)
{
	CLKMainDialog::OnSize(nType, cx, cy);
	AdjustChildCtrl();
}

// �����ӿؼ���λ��
void CmyouboxDlg::AdjustChildCtrl()
{
	return;
	CRect rt;
	GetClientRect(&rt);
	if (m_treeMain.GetSafeHwnd())
	{
		// ������
		CRect rtSearch(0, 51, 250, 82);
		//CRect rtSearch(0, 76, 250, 115);
		rtSearch.right = rt.right - 25;
		rtSearch.left = rtSearch.right - 360;
		//m_ctlSearch.MoveWindow(rtSearch);

		CRect rtTree(0, g_nTopHeight, g_nTreeWidth, rt.bottom);
		//m_treeMain.MoveWindow(rtTree);

		// ���б��
		CRect rtLContainer(rtTree.right + g_nTabLeftOffset, g_nTopHeight, rt.right, g_nTopHeight + g_nLGameTypeHeight);
		//m_LContainer.MoveWindow(rtLContainer);

		CRect rtTab(rtTree.right + g_nTabLeftOffset, rtLContainer.bottom + 10, rt.right, rtLContainer.bottom + 10 + g_nTabHeight);
		//m_tabMain.MoveWindow(rtTab);

		CRect rtContainer(rtTree.right, rtTab.bottom + 14, rt.right, rt.bottom);
		//m_Container.MoveWindow(rtContainer);
		//Invalidate();
	}
}

// ������������
void CmyouboxDlg::UpdateAllDlgBGImg()
{
	m_ctlSearch.SendMessage(LKCOMMON_MSG, LKCOMMON_MSG_WPARAM_RESETMEM, 0);

	// Ƥ������
	//
	// 
}

// ����������Ϸ����
void CmyouboxDlg::OnProcRunGameReq(PGameItem p)
{
	if (!p)
	{
		return;
	}
	if (!p->strGameStartProgram.IsEmpty())
	{
		int nIndex = p->strGameStartProgram.ReverseFind(L'\\');
		CString strPath = p->strGameStartProgram.Left(nIndex);
		::SetCurrentDirectory(strPath);

		UploadGameItem ugItem;
		CLocalDataInfo::GetInstance()->GetUploadGameItem(&ugItem);
		if (ugItem.strGameId.CompareNoCase(p->strGameId) != 0)
		{
			CLocalDataInfo::GetInstance()->SetUploadGameItem(p->strGameId, p->strGameName, p->strGameStartProgram);
			::AfxBeginThread(RunGame, NULL);
		}
		else
		{
			CLogClient::WriteLog("��Ϸ�����������У���ȴ���");
		}
	}
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
		m_tabMain.AddItem(_T("������Ϸ"));

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

// �Ҽ�����
void CmyouboxDlg::OnTrayRButtonUp()
{
	CTrayMainMenu menu;
	menu.Show(this);
}

// ��С����ť������
void CmyouboxDlg::OnMinClick()
{
	CLKDialog::OnMinClick();
}

// �¼�
BOOL CmyouboxDlg::OnEnterPress(HWND hCrtl, LPARAM lparam)
{
	OnEBnClickedButtonSearch();
	return TRUE;
}

// �������
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
	// TODO:  �ڴ˴������Ϣ����������
}

void CmyouboxDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	KillTimer(nIDEvent);
	if (10000 == nIDEvent)
	{
		if (m_strMainProcess.IsEmpty())
		{
			DWORD dw = WaitForSingleObject(m_hStartProcess, 10);
			if (dw != WAIT_TIMEOUT)
			{
				ShowWindow(SW_RESTORE);
				CloseHandle(m_hStartProcess);
				m_hStartProcess = 0;
				CLogClient::WriteLog("�����˳���");
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
				CLogClient::WriteLog("�����˳�2��");
			}
		}
		return;
	}
	else if (nIDEvent == 10001)
	{
		//KillTimer(nIDEvent);
		PostMessage(LKCOMMON_MSG, LKCOMMON_MSG_WPARAM_RESETMEM);
		CLogClient::WriteLog("��ȫ����Ϸ�лָ�4");
		OnTreeCtrlSelectedChanged(0);
		//CString strInfo;
		//strInfo.Format(L"CLKContainer::OnTimer \r\n");
		//::OutputDebugString(strInfo);
	}
	else if (nIDEvent == 10002)
	{
		//KillTimer(nIDEvent);
		CLocalDataInfo::GetInstance()->SetUploadGameItem(L"", L"", L"");
	}
	else if (20001 == nIDEvent)
	{
		m_TopAd.MoveWindow(&m_rtTopAd);
		m_TopAd.ShowWindow(SW_SHOW);
		CRect rtContainer(161, 277, 1530, 900);
		m_Container.MoveWindow(rtContainer);
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

// ɱָ������
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
			CLogError::WriteLog("ɱ����  ʧ�ܣ���ȡϵͳ���̿���ʧ��(%d)", dwErrorCode);
			return false;
		}

		pe.dwSize = sizeof(PROCESSENTRY32);	//	һ��Ҫ��ΪdwSize��ֵ
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
						CLogError::WriteLog("ɱ����  ʧ�ܣ���ָ������ʧ��(%d)", dwErrorCode);
					}
					else
					{
						bResult = !!::TerminateProcess(hProcess, 0);
						CLogError::WriteLog("ɱ����  TerminateProcess end: %d", bResult);
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
			CLogError::WriteLog("ɱ����  ʧ�ܣ���ȡ�������׽���ʧ��(%d)", dwErrorCode);
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
	DWORD dwTime = ::GetTickCount64();
	CString strId;
	CString strName;
	CString strPath;
	CLocalDataInfo::GetInstance()->GetUploadGameItem(strId, strName, strPath);
	HINSTANCE h = ShellExecute(NULL, L"open", strPath.GetBuffer(), NULL, NULL, SW_SHOWNORMAL);
	CLogClient::WriteLogW(L"ִ�г���: %d -- %s", (int)h, strPath.GetBuffer());
	if ((int)h < 32)
	{
		CStringA s; 
		s = strPath;
		CLogError::WriteLog("ִ�г���%sʧ��: %d", s.GetBuffer(), (int)h);
	}
	else
	{
		//ShowWindow(SW_MINIMIZE);
		CLogClient::WriteLog("�������гɹ�2��");
	}
	// �ϴ���Ϸ����
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
	CLogClient::WriteLog("���ÿյĲ�����");
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
	// �˹���Ҫ�� Windows Vista ����߰汾��
	// _WIN32_WINNT ���ű��� >= 0x0600��
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

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
	// TODO:  �ڴ˴������Ϣ����������
}


void CmyouboxDlg::OnMove(int x, int y)
{
	static CRect rt(0, 0, 0, 0);
	if (rt.IsRectEmpty()) GetWindowRect(&rt);
	CLKMainDialog::OnMove(x, y);
	m_Container.AdjustFlagDlg(x - rt.left, y - rt.top);
	rt.MoveToXY(x, y);

	// TODO:  �ڴ˴������Ϣ����������
}


void CmyouboxDlg::OnActivateApp(BOOL bActive, DWORD dwThreadID)
{
	CLKMainDialog::OnActivateApp(bActive, dwThreadID);
	//CLogClient::WriteLog("��ȫ����Ϸ�лָ�5��%d", bActive);
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
	// TODO:  �ڴ����ר�ô����/����û���
	if (WM_SYNCPAINT == message)
	{
		CLogClient::WriteLog("��ȫ����Ϸ�лָ���%d, %d", wParam, lParam);
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
		CLogClient::WriteLog("��ȫ����Ϸ�лָ���%d, %d", LOWORD(lParam), HIWORD(lParam));
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
		//	CLogClient::WriteLog("��ȫ����Ϸ�лָ�2");
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
		////	CLogClient::WriteLog("��ȫ����Ϸ�лָ�2��%d, %d", wParam, lParam);
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
	// TODO:  �ڴ����ר�ô����/����û���
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


//
//
//if (!p->strGameStartProgram.IsEmpty())
//{
//	int nIndex = p->strGameStartProgram.ReverseFind(L'\\');
//	CString strPath = p->strGameStartProgram.Left(nIndex);
//	::SetCurrentDirectory(strPath);
//
//	STARTUPINFO si;
//	PROCESS_INFORMATION pi;
//	ZeroMemory(&si, sizeof(si));
//	si.cb = sizeof(si);
//	ZeroMemory(&pi, sizeof(pi));
//	// Start the child process. 
//	//if (CreateProcess(NULL,   // No module name (use command line)
//	//	p->strGameStartProgram.GetBuffer(),        // Command line
//	//	NULL,           // Process handle not inheritable
//	//	NULL,           // Thread handle not inheritable
//	//	FALSE,          // Set handle inheritance to FALSE
//	//	0,              // No creation flags
//	//	NULL,           // Use parent's environment block
//	//	NULL,           // Use parent's starting directory 
//	//	&si,            // Pointer to STARTUPINFO structure
//	//	&pi)           // Pointer to PROCESS_INFORMATION structure
//	//	)
//	//{
//	//	//ShowWindow(SW_MINIMIZE);
//	//	//if (p->strGameStartProgram.CompareNoCase(p->strGameMainProcessName) != 0)
//	//	//{
//	//	//	CloseHandle(pi.hProcess);
//	//	//	pi.hProcess = 0;
//	//	//	m_strMainProcess = p->strGameMainProcessName;
//	//	//}
//	//	//else
//	//	//{
//	//	//	m_strMainProcess = L"";
//	//	//	m_hStartProcess = pi.hProcess;
//	//	//}
//	//	//SetTimer(10000, 1000, 0);
//	//	//CloseHandle(pi.hThread);
//	//	//pi.hThread = 0;
//	//	CLogClient::WriteLog("�������гɹ���");
//	//}
//	//else
//	//{
//	UploadGameItem ugItem;
//	CLocalDataInfo::GetInstance()->GetUploadGameItem(&ugItem);
//	//if (ugItem.strGameId.IsEmpty())
//	if (ugItem.strGameId.CompareNoCase(p->strGameId) != 0)
//	{
//		CLocalDataInfo::GetInstance()->SetUploadGameItem(p->strGameId, p->strGameName, p->strGameStartProgram);
//		::AfxBeginThread(RunGame, NULL);
//	}
//	else
//	{
//		//SetTimer(10002, 5 * 1000, 0);
//		CLogClient::WriteLog("��Ϸ�����������У���ȴ���");
//	}
//}
