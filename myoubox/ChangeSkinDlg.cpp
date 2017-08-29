// ChangeSkinDlg.cpp : 实现文件
//

#include "stdafx.h"
//#include "Trip.h"
#include "ChangeSkinDlg.h"
//#include "MiscMgr.h"
#include "ConfigFile.h"
//#include "UserConfigFile.h"
#include "..\..\..\..\common\LKComponent\GDI\LKMessageBox.h"
#include "..\..\..\..\common\res\resource1.h"
//#include "..\..\..\common\res\resource1.h"
// 各控件标识
// 皮肤列表控件
#define CHANGESKINDLG_CTRLID_SKINLISTID		100
// 增加皮肤按钮
#define CHANGESKINDLG_CTRLID_ADDID			101
// 重置默认皮肤按钮
#define CHANGESKINDLG_CTRLID_RESETID		102

// 消息
// 加载单个皮肤
#define WPARAM_LOAD_SINGLE_SKIN			1
// 加载单个皮肤失败
#define WPARAM_LOAD_SINGLE_SKIN_FAIL	2
// 加载皮肤完成
#define WPARAM_LOAD_SKIN_FINISH			3

// CChangeSkinDlg 对话框

IMPLEMENT_DYNAMIC(CChangeSkinDlg, CLKMaskDialog)

CChangeSkinDlg::CChangeSkinDlg(CWnd* pParent /*=NULL*/)
: CLKMaskDialog(CChangeSkinDlg::IDD, pParent)
, m_bInitSkin(false)
, m_btnAdd(2)
, m_btnReset(2)
{
	InitImageList();
}

CChangeSkinDlg::~CChangeSkinDlg()
{
    //CUserConfigFile *pConfig = CUserConfigFile::GetInstance();
    //pConfig->SaveToFile();
}

void CChangeSkinDlg::DoDataExchange(CDataExchange* pDX)
{
	CLKMaskDialog::DoDataExchange(pDX);
}

// 初始化图片列表
//void CChangeSkinDlg::InitImageList()
//{
//	// 初始化图片列表
//	CLKDialog::InitImageList();
//	m_arrImage[LKGDIBASEDIALOG_IMAGEINDEX_MAX] = 0;
//	m_arrImage[LKGDIBASEDIALOG_IMAGEINDEX_MIN] = 0;
//	m_arrImage[LKGDIBASEDIALOG_IMAGEINDEX_RESTORE] = 0;
//	m_arrImage[LKGDIBASEDIALOG_IMAGEINDEX_SELF] = 0;
//}


BEGIN_MESSAGE_MAP(CChangeSkinDlg, CLKMaskDialog)
	ON_MESSAGE(LKSELFOTHER_MSG, OnLoadMsg)
	ON_BN_CLICKED(CHANGESKINDLG_CTRLID_ADDID, OnBtnAddSkin)
	ON_BN_CLICKED(CHANGESKINDLG_CTRLID_RESETID, OnBtnResetSkin)
END_MESSAGE_MAP()


// CChangeSkinDlg 消息处理程序
// 增加皮肤图片按钮点击事件
void CChangeSkinDlg::OnBtnAddSkin() 
{
	TCHAR szFilters[] = _T("图片文件(*.bmp, *.jpg, *.jpeg, *.png)|*.bmp; *.jpg; *.jpeg; *.png;||");

	CFileDialog dlg(true, 0, 0, 4 | 2, szFilters);
	if(dlg.DoModal() == IDOK)
	{
		CString strFileName = dlg.GetPathName();
		CString strFileExt = dlg.GetFileExt();
		CConfigFile *pConfig = CConfigFile::GetInstance();

		CString strNewFileName = pConfig->GetSkinPathW().c_str();
		CTime tm = CTime::GetCurrentTime();
		CString strTm  = _T("\\");
		strTm		   += tm.Format(_T("%Y%m%d%H%M%S."));
		strTm		   += strFileExt;
		strNewFileName += strTm;
		if(::CopyFile(strFileName, strNewFileName, TRUE))
		{
			//strNewFileName = pConfig->GetSkinPath(false);
			//strNewFileName += strTm;

			SkinItem item;
			item.strPath = strNewFileName;
			CLKImage img;
			if (img.Load(item.strPath) != E_FAIL)
			{
				item.pImg = new CLKImage(77, 50);
				img.StretchToImage(item.pImg);
				::SendMessage(GetSafeHwnd(), LKSELFOTHER_MSG, WPARAM_LOAD_SINGLE_SKIN, (LPARAM)&item);
				img.Destroy();
				pConfig->AddSkin(strNewFileName);
			}else
			{
				MessageBox(_T("加载背景图片失败！！！"));
				//::SendMessage(pThis->GetSafeHwnd(), LKSELFOTHER_MSG, WPARAM_LOAD_SINGLE_SKIN_FAIL, (LPARAM)&item);
			}
			//m_ltSkin.AddItem(strNewFileName, true);
		}else
		{
			// 失败
		}
	}
}

// 重置皮肤图片按钮点击事件
void CChangeSkinDlg::OnBtnResetSkin() 
{
	if(m_ltSkin.GetSelectItem() != -1)
	{
		//CUserConfigFile *pConfig = CUserConfigFile::GetInstance();
		//CString strSkin = pConfig->GetCurSkin(false);
		//if(!strSkin.IsEmpty())
		//{
		//	pConfig->DeleteCurSkin(strSkin);
		//}
		// 清空选中状态
		m_ltSkin.ClearSelectItem();

		// 父窗体换皮肤
		CLKImage img;
		CRect rtFrame;
		if(false != img.LoadEx(IDB_JPG_DLG_BG, false, rtFrame, _T("JPG")))
		{
			::AfxGetMainWnd()->SendMessage(LKCOMMON_MSG, LKBUTTONEX_MSG_WPARAM_SELECTED, (LPARAM)&img);
			SendMessage(LKCOMMON_MSG, LKCOMMON_MSG_WPARAM_RESETMEM, 0);
		}
	}
}


BOOL CChangeSkinDlg::OnInitDialog()
{
	CLKMaskDialog::OnInitDialog();

	SetWindowPos(0, 0, 0, 361, 242, SWP_NOMOVE | SWP_NOZORDER);
	CString strCaption(_T("更换皮肤"));
	SetWindowText(strCaption);
	// TODO:  在此添加额外的初始化

	CRect rtClient;
	GetClientRect(&rtClient);
	// 皮肤列表
	CRect rtSkin(rtClient);
	rtSkin.top += 6;
	rtSkin.bottom -= 27;
	m_ltSkin.Create(rtSkin, this, CHANGESKINDLG_CTRLID_SKINLISTID);

	// 加载皮肤按钮
	LoadSkinBtn();

	// 按钮
	CRect rtBtn(15, rtClient.bottom - 22, 15 + 64, rtClient.bottom);
	m_btnAdd.Create(_T("增加皮肤"), rtBtn, this, CHANGESKINDLG_CTRLID_ADDID);
	rtBtn.OffsetRect(80, 0);
	m_btnReset.Create(_T("重置皮肤"), rtBtn, this, CHANGESKINDLG_CTRLID_RESETID);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

LRESULT CChangeSkinDlg::OnLoadMsg(WPARAM wParam, LPARAM lParam)
{
	if(WPARAM_LOAD_SINGLE_SKIN == wParam)
	{
		SkinItem *pItem = (SkinItem *)lParam;
		m_ltSkin.AddItem(pItem->pImg, pItem->strPath);
	}else if(WPARAM_LOAD_SINGLE_SKIN_FAIL == wParam)
	{
	}else if(WPARAM_LOAD_SKIN_FINISH == wParam)
	{
	    //CUserConfigFile *pConfig = CUserConfigFile::GetInstance();
	    //CString strSkin = pConfig->GetCurSkin(false);
	    //m_ltSkin.SetSelectItem(strSkin);
	}
	return 1;
}

LRESULT CChangeSkinDlg::OnCommonMsg(WPARAM wParam, LPARAM lParam)
{
	if(LKBUTTONEX_MSG_WPARAM_SELECTED == wParam)
	{
		// MessageBox(_T(""));
		CString *pFileName = (CString *)lParam;
		CString strFileName = *pFileName;// CConfigModule::GetAbsPath(*pFileName);
		if(!strFileName.IsEmpty())
		{
			CLKImage img;
			if(E_FAIL != img.Load(strFileName))
			{
				::AfxGetMainWnd()->SendMessage(LKCOMMON_MSG, wParam, (LPARAM)&img);
				SendMessage(LKCOMMON_MSG, LKCOMMON_MSG_WPARAM_RESETMEM, 0);

	            //// 记下当前皮肤
	            //CUserConfigFile *pConfig = CUserConfigFile::GetInstance();
	            //pConfig->ModifyCurSkin(*pFileName);
			}
		}
	}else if(LKBUTTONEX_MSG_WPARAM_DELETE == wParam)
	{
        if(CLKMessageBox::Show(IDD_LKMESSAGEBOX, _T("你确定要删除这个皮肤吗？"), _T("删除皮肤")) == IDOK)
        {
            DeleteItemParam *pPara = (DeleteItemParam *)lParam;
			CConfigFile *pConfig = CConfigFile::GetInstance();
		    int nCurIndex = m_ltSkin.GetSelectItem();
		    if(pPara)
		    {
			    pConfig->DeleteSkin(m_ltSkin.GetButtonImgPath(pPara->nIndex));
			    if(nCurIndex == pPara->nIndex)
			    {
				    OnBtnResetSkin();
			    }
		    }
            pPara->bDel = true;
        }
	}else 
	{
		CLKMaskDialog::OnCommonMsg(wParam, lParam);
	}
	return 1;
}

// 加载皮肤按钮线程函数
UINT CChangeSkinDlg::LoadSkinBtnThread(LPVOID pParam)
{
	CChangeSkinDlg *pThis = (CChangeSkinDlg *)pParam;
	if (!pThis || !pThis->GetSafeHwnd()) return 0;
	//CConfigFile *pConfig = CConfigFile::GetInstance();
	list<wstring> ltSkin;
	CConfigFile::GetInstance()->GetClientSkinNameList(ltSkin);
	for (auto it : ltSkin)
	{
		SkinItem item;
		item.strPath = it.c_str();
		CLKImage img;
		CString sTemp(it.c_str());
		if(img.Load(sTemp) != E_FAIL)
		{
			item.pImg = new CLKImage(77, 50);
			img.StretchToImage(item.pImg);
			::SendMessage(pThis->GetSafeHwnd(), LKSELFOTHER_MSG, WPARAM_LOAD_SINGLE_SKIN, (LPARAM)&item);
			img.Destroy();
		}else
		{
			::SendMessage(pThis->GetSafeHwnd(), LKSELFOTHER_MSG, WPARAM_LOAD_SINGLE_SKIN_FAIL, (LPARAM)&item);
		}
		Sleep(20);
	}
	pThis->m_bInitSkin = true;
	::PostMessage(pThis->GetSafeHwnd(), LKSELFOTHER_MSG, WPARAM_LOAD_SKIN_FINISH, 0);

	//for(POSITION pos = lt.GetHeadPosition(); pos; lt.GetNext(pos))
	//{
	//	if(!pThis->GetSafeHwnd()) return 0;
	//	SkinItem item;
	//	item.strPath = lt.GetAt(pos);
	//	CString sTemp(CConfigModule::GetAppPath());
	//	if (item.strPath.Find(_T(":")) < 0)
	//	{
	//		// 相对路径
	//		sTemp += item.strPath;
	//		//item.strPath = sTemp;
	//	}
	//	CLKImage img;
	//	if(img.Load(sTemp) != E_FAIL)
	//	{
	//		item.pImg = new CLKImage(77, 50);
	//		img.StretchToImage(item.pImg);
	//		::SendMessage(pThis->GetSafeHwnd(), LKSELFOTHER_MSG, WPARAM_LOAD_SINGLE_SKIN, (LPARAM)&item);
	//		img.Destroy();
	//	}else
	//	{
	//		::SendMessage(pThis->GetSafeHwnd(), LKSELFOTHER_MSG, WPARAM_LOAD_SINGLE_SKIN_FAIL, (LPARAM)&item);
	//	}
	//	Sleep(20);
	//}
	//pThis->m_bInitSkin = true;
	//::PostMessage(pThis->GetSafeHwnd(), LKSELFOTHER_MSG, WPARAM_LOAD_SKIN_FINISH, 0);
	return 0;
	//
}

// 加载皮肤按钮
void CChangeSkinDlg::LoadSkinBtn()
{
	m_bInitSkin = false;
	CWinThread *hThread = ::AfxBeginThread(LoadSkinBtnThread, this);
	
}

