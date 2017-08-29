#include "StdAfx.h"
#include "TrayMainMenu.h"
#include "..\..\..\common\LKComponent\GDI\LKImageMgr.h"
#include "..\..\..\common\LKComponent\GDI\LKDialog.h"
#include "myouboxConst.h"

CTrayMainMenu::CTrayMainMenu(void)
{
    // 打开面板
    AddMenuItem(TRAYMAINMENUITEM_ID_OPENMAINPANEL, _T("打开主界面"), CLKImageMgr::GetImageS(LKIMAGEBUTTONINDEX_OPENMAINPANEL));
    //// 个人信息
    //AddMenuItem(SELFMENUITEM_ID_USERINFO, _T("个人信息"), CLKImageMgr::GetImageS(LKIMAGEBUTTONINDEX_MENUITEM_SYSCONFIG));
    //// 资料同步
    //AddMenuItem(TRAYMAINMENUITEM_ID_SYNDATA, _T("资料同步"), CLKImageMgr::GetImageS(LKIMAGEBUTTONINDEX_MENUITEM_SYNDATA));
    // 系统升级
    //AddMenuItem(TRAYMAINMENUITEM_ID_UPDATE, _T("系统升级"), CLKImageMgr::GetImageS(LKIMAGEBUTTONINDEX_MENUITEM_UPDATE));
    //// 在线充值
    //AddMenuItem(TRAYMAINMENUITEM_ID_ADDMONEY, _T("在线充值"), CLKImageMgr::GetImageS(LKIMAGEBUTTONINDEX_MENUITEM_ADDMONEY));
    //// 锁定系统
    //AddMenuItem(TRAYMAINMENUITEM_ID_LOCKSYS, _T("锁定系统"), CLKImageMgr::GetImageS(LKIMAGEBUTTONINDEX_MENUITEM_LOCK));
 //   // 帮助
	//AddMenuItem(TRAYMAINMENUITEM_ID_HELP, _T("帮助"), CLKImageMgr::GetImageS(LKIMAGEBUTTONINDEX_ICONHELP));
 //   // 关于
 //   AddMenuItem(TRAYMAINMENUITEM_ID_ABOUT, _T("关于..."), CLKImageMgr::GetImageS(LKIMAGEBUTTONINDEX_MENUITEM_ABOUT));
    // 退出
    AddMenuItem(TRAYMAINMENUITEM_ID_EXIT, _T("退出"), CLKImageMgr::GetImageS(LKIMAGEBUTTONINDEX_MENUITEM_EXIT));
}

CTrayMainMenu::~CTrayMainMenu(void)
{
}

// 显示弹出窗口
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
