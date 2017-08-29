#pragma once
#include "..\..\..\common\LKComponent\GDI\LKMenu.h"

// 菜单项ID
// 打开面板
#define TRAYMAINMENUITEM_ID_OPENMAINPANEL   200
//// 资料同步
//#define TRAYMAINMENUITEM_ID_SYNDATA         101
//// 系统升级
//#define TRAYMAINMENUITEM_ID_UPDATE          102
//// 在线充值
//#define TRAYMAINMENUITEM_ID_ADDMONEY        103
//// 锁定系统
//#define TRAYMAINMENUITEM_ID_LOCKSYS         104
// 帮助
#define TRAYMAINMENUITEM_ID_HELP            105
// 关于
#define TRAYMAINMENUITEM_ID_ABOUT           106
// 退出
#define TRAYMAINMENUITEM_ID_EXIT            1


class CTrayMainMenu :
    public CLKMenu
{
public:
    CTrayMainMenu(void);
    virtual ~CTrayMainMenu(void);
    // 显示弹出窗口
    void Show(CWnd *pParent);
protected:
    virtual void OnMeasureItem(LPMEASUREITEMSTRUCT lpms);
};
