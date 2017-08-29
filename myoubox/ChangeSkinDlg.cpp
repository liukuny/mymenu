// ChangeSkinDlg.cpp : ʵ���ļ�
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
// ���ؼ���ʶ
// Ƥ���б�ؼ�
#define CHANGESKINDLG_CTRLID_SKINLISTID		100
// ����Ƥ����ť
#define CHANGESKINDLG_CTRLID_ADDID			101
// ����Ĭ��Ƥ����ť
#define CHANGESKINDLG_CTRLID_RESETID		102

// ��Ϣ
// ���ص���Ƥ��
#define WPARAM_LOAD_SINGLE_SKIN			1
// ���ص���Ƥ��ʧ��
#define WPARAM_LOAD_SINGLE_SKIN_FAIL	2
// ����Ƥ�����
#define WPARAM_LOAD_SKIN_FINISH			3

// CChangeSkinDlg �Ի���

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

// ��ʼ��ͼƬ�б�
//void CChangeSkinDlg::InitImageList()
//{
//	// ��ʼ��ͼƬ�б�
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


// CChangeSkinDlg ��Ϣ�������
// ����Ƥ��ͼƬ��ť����¼�
void CChangeSkinDlg::OnBtnAddSkin() 
{
	TCHAR szFilters[] = _T("ͼƬ�ļ�(*.bmp, *.jpg, *.jpeg, *.png)|*.bmp; *.jpg; *.jpeg; *.png;||");

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
				MessageBox(_T("���ر���ͼƬʧ�ܣ�����"));
				//::SendMessage(pThis->GetSafeHwnd(), LKSELFOTHER_MSG, WPARAM_LOAD_SINGLE_SKIN_FAIL, (LPARAM)&item);
			}
			//m_ltSkin.AddItem(strNewFileName, true);
		}else
		{
			// ʧ��
		}
	}
}

// ����Ƥ��ͼƬ��ť����¼�
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
		// ���ѡ��״̬
		m_ltSkin.ClearSelectItem();

		// �����廻Ƥ��
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
	CString strCaption(_T("����Ƥ��"));
	SetWindowText(strCaption);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CRect rtClient;
	GetClientRect(&rtClient);
	// Ƥ���б�
	CRect rtSkin(rtClient);
	rtSkin.top += 6;
	rtSkin.bottom -= 27;
	m_ltSkin.Create(rtSkin, this, CHANGESKINDLG_CTRLID_SKINLISTID);

	// ����Ƥ����ť
	LoadSkinBtn();

	// ��ť
	CRect rtBtn(15, rtClient.bottom - 22, 15 + 64, rtClient.bottom);
	m_btnAdd.Create(_T("����Ƥ��"), rtBtn, this, CHANGESKINDLG_CTRLID_ADDID);
	rtBtn.OffsetRect(80, 0);
	m_btnReset.Create(_T("����Ƥ��"), rtBtn, this, CHANGESKINDLG_CTRLID_RESETID);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
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

	            //// ���µ�ǰƤ��
	            //CUserConfigFile *pConfig = CUserConfigFile::GetInstance();
	            //pConfig->ModifyCurSkin(*pFileName);
			}
		}
	}else if(LKBUTTONEX_MSG_WPARAM_DELETE == wParam)
	{
        if(CLKMessageBox::Show(IDD_LKMESSAGEBOX, _T("��ȷ��Ҫɾ�����Ƥ����"), _T("ɾ��Ƥ��")) == IDOK)
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

// ����Ƥ����ť�̺߳���
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
	//		// ���·��
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

// ����Ƥ����ť
void CChangeSkinDlg::LoadSkinBtn()
{
	m_bInitSkin = false;
	CWinThread *hThread = ::AfxBeginThread(LoadSkinBtnThread, this);
	
}

