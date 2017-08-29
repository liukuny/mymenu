#include "StdAfx.h"
#include "TrayMainMenu.h"
#include "..\..\..\common\LKComponent\GDI\LKImageMgr.h"
#include "..\..\..\common\LKComponent\GDI\LKDialog.h"
#include "myouboxConst.h"

CTrayMainMenu::CTrayMainMenu(void)
{
    // �����
    AddMenuItem(TRAYMAINMENUITEM_ID_OPENMAINPANEL, _T("��������"), CLKImageMgr::GetImageS(LKIMAGEBUTTONINDEX_OPENMAINPANEL));
    //// ������Ϣ
    //AddMenuItem(SELFMENUITEM_ID_USERINFO, _T("������Ϣ"), CLKImageMgr::GetImageS(LKIMAGEBUTTONINDEX_MENUITEM_SYSCONFIG));
    //// ����ͬ��
    //AddMenuItem(TRAYMAINMENUITEM_ID_SYNDATA, _T("����ͬ��"), CLKImageMgr::GetImageS(LKIMAGEBUTTONINDEX_MENUITEM_SYNDATA));
    // ϵͳ����
    //AddMenuItem(TRAYMAINMENUITEM_ID_UPDATE, _T("ϵͳ����"), CLKImageMgr::GetImageS(LKIMAGEBUTTONINDEX_MENUITEM_UPDATE));
    //// ���߳�ֵ
    //AddMenuItem(TRAYMAINMENUITEM_ID_ADDMONEY, _T("���߳�ֵ"), CLKImageMgr::GetImageS(LKIMAGEBUTTONINDEX_MENUITEM_ADDMONEY));
    //// ����ϵͳ
    //AddMenuItem(TRAYMAINMENUITEM_ID_LOCKSYS, _T("����ϵͳ"), CLKImageMgr::GetImageS(LKIMAGEBUTTONINDEX_MENUITEM_LOCK));
 //   // ����
	//AddMenuItem(TRAYMAINMENUITEM_ID_HELP, _T("����"), CLKImageMgr::GetImageS(LKIMAGEBUTTONINDEX_ICONHELP));
 //   // ����
 //   AddMenuItem(TRAYMAINMENUITEM_ID_ABOUT, _T("����..."), CLKImageMgr::GetImageS(LKIMAGEBUTTONINDEX_MENUITEM_ABOUT));
    // �˳�
    AddMenuItem(TRAYMAINMENUITEM_ID_EXIT, _T("�˳�"), CLKImageMgr::GetImageS(LKIMAGEBUTTONINDEX_MENUITEM_EXIT));
}

CTrayMainMenu::~CTrayMainMenu(void)
{
}

// ��ʾ��������
void CTrayMainMenu::Show(CWnd *pParent)
{
    //DWORD dwPos = GetMessagePos();
    CPoint point;
    ::GetCursorPos(&point);
    CLKDialog *pDlg = (CLKDialog *)pParent;
    //CRect rtWnd;
    //pDlg->GetSelfRectByScreen(&rtWnd);

    if(CSystemInfo::GetSystemVer() > WINDOWS_XP)
    {
        CRect rtDesk;
        SystemParametersInfo(SPI_GETWORKAREA, 0, &rtDesk, 0);
        if(point.x > rtDesk.Width() + GetSystemMetrics(SM_CXFRAME) - 128)
        {
            point.x -= 122; 
        }
    }
    TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, pParent);
}

void CTrayMainMenu::OnMeasureItem(LPMEASUREITEMSTRUCT lpms)
{
	lpms->itemWidth = 100;
	lpms->itemHeight = 21;
}
