#pragma once
#include "..\..\..\common\LKComponent\GDI\LKMenu.h"

// �˵���ID
// �����
#define TRAYMAINMENUITEM_ID_OPENMAINPANEL   200
//// ����ͬ��
//#define TRAYMAINMENUITEM_ID_SYNDATA         101
//// ϵͳ����
//#define TRAYMAINMENUITEM_ID_UPDATE          102
//// ���߳�ֵ
//#define TRAYMAINMENUITEM_ID_ADDMONEY        103
//// ����ϵͳ
//#define TRAYMAINMENUITEM_ID_LOCKSYS         104
// ����
#define TRAYMAINMENUITEM_ID_HELP            105
// ����
#define TRAYMAINMENUITEM_ID_ABOUT           106
// �˳�
#define TRAYMAINMENUITEM_ID_EXIT            1


class CTrayMainMenu :
    public CLKMenu
{
public:
    CTrayMainMenu(void);
    virtual ~CTrayMainMenu(void);
    // ��ʾ��������
    void Show(CWnd *pParent);
protected:
    virtual void OnMeasureItem(LPMEASUREITEMSTRUCT lpms);
};
