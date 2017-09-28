#pragma once
#include "..\..\..\common\LKComponent\GDI\LKConst.h" 


// ����ͼ��
#define LKIMAGEBUTTONINDEX_ICONHELP			LKPROJECT_INDEX_BEGIN + 0
// ϵͳ����
#define LKIMAGEBUTTONINDEX_MENUITEM_SYSCONFIG	LKPROJECT_INDEX_BEGIN + 1
// ϵͳ����
#define LKIMAGEBUTTONINDEX_MENUITEM_UPDATE	    LKPROJECT_INDEX_BEGIN + 2
// ����
#define LKIMAGEBUTTONINDEX_MENUITEM_ABOUT	    LKPROJECT_INDEX_BEGIN + 3
// �˳� 
#define LKIMAGEBUTTONINDEX_MENUITEM_EXIT	    LKPROJECT_INDEX_BEGIN + 4
// �����
#define LKIMAGEBUTTONINDEX_OPENMAINPANEL        LKPROJECT_INDEX_BEGIN + 5
// ��������ͼ��
#define LKIMAGEBUTTONINDEX_BUTTON_SEARCH        LKPROJECT_INDEX_BEGIN + 6
// ͷ������
#define LKIMAMYOUBOX_DIALOG_HEAD				LKPROJECT_INDEX_BEGIN + 7
// ͷ����ǩ 
#define LKIMAMYOUBOX_DIALOG_HEADLABEL			LKPROJECT_INDEX_BEGIN + 8
// ͷ���ָ��� 
#define LKIMAGELISTINDEX_COMMON_SPLIT			LKPROJECT_INDEX_BEGIN + 9
// �༭��ťͼƬ
#define LKIMAGEBUTTONINDEX_EDITBUTTON			LKPROJECT_INDEX_BEGIN + 10
// ���οؼ�����ͼƬ
#define LKIMGMYOUBOX_TREE_BG					LKPROJECT_INDEX_BEGIN + 11
// ���οؼ��ָ���ͼƬ
#define LKIMGMYOUBOX_TREE_SPLIT					LKPROJECT_INDEX_BEGIN + 12
// ��������˵�������ͼƬ1 - ������Ϸ
#define LKIMAMYOUBOX_TOPHOTGAMEITEM				LKPROJECT_INDEX_BEGIN + 13
// ��������˵�������ͼƬ2 - ����Ϸ
#define LKIMAMYOUBOX_TOPPLAYGAMEITEM			LKPROJECT_INDEX_BEGIN + 14
// ��������˵�������ͼƬ3 - Ӱ������
#define LKIMAMYOUBOX_TOPMOVEITEM				LKPROJECT_INDEX_BEGIN + 15
// ��������˵�������ͼƬ4 - ���콻��
#define LKIMAMYOUBOX_TOPCHATITEM				LKPROJECT_INDEX_BEGIN + 16
// ��������˵�������ͼƬ5 - С��Ϸ
#define LKIMAMYOUBOX_TOPSMALLGAMEITEM			LKPROJECT_INDEX_BEGIN + 17
// ��������˵�������ͼƬ6 - ���ù���
#define LKIMAMYOUBOX_TOPTOOLSITEM				LKPROJECT_INDEX_BEGIN + 18
/*��������˵�������ʾ��*/\
#define LKIMAMYOUBOX_TOPGAMEFOCUS				LKPROJECT_INDEX_BEGIN + 19
/*�������˵�������ʾ��*/\
#define LKIMAMYOUBOX_GAMEFOCUS					LKPROJECT_INDEX_BEGIN + 20

// ����0
#define LKPROJECTHEADIMAGE_INDEX_0				LKPROJECTHEADIMAGE_INDEX_BEGIN + 0

#define AppLoadAllResourceImageToImageArray(pImgMgr)\
{\
	LoadAllResourceImageToImageArray(pImgMgr)\
	/*��Ŀ��ԴͼƬ*/\
	int i = LKPROJECT_INDEX_BEGIN; \
	/*����ͼ��*/\
	pImgMgr->SetPNGImage(i++, IDB_PNG_COMMON_ICON_HELP);\
	/*ϵͳ����*/\
	pImgMgr->SetPNGImage(i++, IDB_PNG_MENUITEM_SYSCONFIG);\
	/*ϵͳ����*/\
	pImgMgr->SetPNGImage(i++, IDB_PNG_MENUITEM_UPDATE);\
	/*����*/\
	pImgMgr->SetPNGImage(i++, IDB_PNG_MENUITEM_LOGOS);\
	/*�˳�*/\
	pImgMgr->SetPNGImage(i++, IDB_PNG_MENUITEM_EXIT);\
	/*�����*/\
	pImgMgr->SetPNGImage(i++, IDB_PNG_COMMON_ICON_MAINPANEL);\
	/*��������ͼ��*/\
	pImgMgr->SetPNGImage(i++, IDB_PNG_COMMON_SEARCH); \
	/*ͷ������*/\
	pImgMgr->SetPNGImage(i++, IDB_PNG_MYOUBOX_HEAD, CRect(0, 0, 0, 0), 1, false); \
	/*ͷ����ǩ*/\
	pImgMgr->SetPNGImage(i++, IDB_PNG_MYOUBOX_HEADLABEL); \
	/*ͷ���ָ���*/\
	pImgMgr->SetPNGImage(i++, IDB_PNG_MYOUBOX_HEADSPLIT, CRect(0, 0, 0, 0), 1); \
	/*�༭��ťͼƬ*/\
	pImgMgr->SetPNGImage(i++, IDB_PNG_MYOUBOX_EDITBUTTON, CRect(0, 0, 0, 0), 3); \
	/*���οؼ�����ͼƬ*/\
	pImgMgr->SetPNGImage(i++, IDB_PNG_MYOUBOX_TREEBG, CRect(0, 0, 0, 0), 1); \
	/*���οؼ��ָ���ͼƬ*/\
	pImgMgr->SetPNGImage(i++, IDB_PNG_MYOUBOX_TREESPLIT, CRect(0, 0, 0, 0), 1); \
	/*��������˵�������ͼƬ1 - ������Ϸ*/\
	pImgMgr->SetPNGImage(i++, IDB_PNG_MYOUBOX_TOPHOTGAMEITEM, CRect(0, 0, 0, 0), 1); \
	/*��������˵�������ͼƬ2 - ����Ϸ*/\
	pImgMgr->SetPNGImage(i++, IDB_PNG_MYOUBOX_TOPPLAYGAMEITEM, CRect(0, 0, 0, 0), 1); \
	/*��������˵�������ͼƬ3 - Ӱ������*/\
	pImgMgr->SetPNGImage(i++, IDB_PNG_MYOUBOX_TOPMOVEITEM, CRect(0, 0, 0, 0), 1); \
	/*��������˵�������ͼƬ4 - ���콻��*/\
	pImgMgr->SetPNGImage(i++, IDB_PNG_MYOUBOX_TOPCHATITEM, CRect(0, 0, 0, 0), 1); \
	/*��������˵�������ͼƬ5 - С��Ϸ*/\
	pImgMgr->SetPNGImage(i++, IDB_PNG_MYOUBOX_TOPSMALLGAMEITEM, CRect(0, 0, 0, 0), 1); \
	/*��������˵�������ͼƬ6 - ���ù���*/\
	pImgMgr->SetPNGImage(i++, IDB_PNG_MYOUBOX_TOPTOOLSITEM, CRect(0, 0, 0, 0), 1); \
	/*��������˵�������ʾ��*/\
	pImgMgr->SetPNGImage(i++, IDB_PNG_MYOUBOX_TOPGAMEFOCUS, CRect(0, 0, 0, 0), 1); \
	/*�������˵�������ʾ��*/\
	pImgMgr->SetPNGImage(i++, IDB_PNG_MYOUBOX_GAMEFOCUS, CRect(0, 0, 0, 0), 1); \
	/*�༭��ǰ��ͼƬ*/\
	pImgMgr->SetPNGImage(LKIMAGELISTINDEX_EDIT_BEGIN + 1, IDB_PNG_MYOUBOX_EDITIMG, CRect(10, 4, 30, 4), 2); \
	/*Ĭ�ϵ�TAB�ؼ�ͼƬ*/\
	pImgMgr->SetPNGImage(LKIMAGELISTINDEX_TAB_BEGIN + 1, IDB_PNG_MYOUBOX_TABHEADER, CRect(6, 0, 6, 0), 3); \
	/*Ĭ�ϵĶԻ�����ͼƬ*/\
	pImgMgr->SetPNGImage(LKIMAGELISTINDEX_DIALOG_BEGIN, IDB_PNG_DLG_MYOUBOX_CLOSE); \
	pImgMgr->SetPNGImage(LKIMAGELISTINDEX_DIALOG_BEGIN + 1, IDB_PNG_DLG_MYOUBOX_MIN); \
	pImgMgr->SetPNGImage(LKIMAGELISTINDEX_DIALOG_BEGIN + 5, IDB_PNG_DLG_MYOUBOX_SELF); \
	pImgMgr->SetJPGImage(LKIMAGELISTINDEX_DIALOG_BEGIN + 6, IDR_JPG_MAINBG); \
	pImgMgr->SetImage(LKIMAGELISTINDEX_DIALOG_BEGIN + 7); \
	pImgMgr->SetImage(LKIMAGELISTINDEX_DIALOG_BEGIN + 8); \
}

// Ĭ�ϵ�ͷ�� 
// Ӧ�ó�����Ϣ����
// �Զ�����Ϣ
#define MSG_APPLICATION			WM_USER	+ 2000

// ��ģ���ڲ���Ϣ���峣��
// ����������Ϣ
#define LOCKDLG_MSG             WM_USER + 100
// �û�״̬�ı���Ϣ
#define USERSTATECHANGE_MSG     WM_USER + 101

// ����������ϢWPARAM����
// ����
#define LOCKDLGMSG_WPARAM_UNLOCK    1

// �û�״̬�ı���ϢWPARAM����
// ����
#define USERSTATECHANGEMSG_WPARAM_ONLINE    1
// ����
#define USERSTATECHANGEMSG_WPARAM_OFFLINE   2

// ���ر�����Ϣ
#define WPARAM_CFACEMAINDLG_LOADFACE		100
// ���ر�����Ϣ���
#define WPARAM_CFACEMAINDLG_LOADFACEFIN		101
// WEBSERVICE���յ�����֪ͨ���̴߳�����Ϣ
#define WPARAM_CWEBSERVICECLIENT_RECVDATA	200

// facedlgѡ�б���֪ͨ������Ϣ
#define WPARAM_FACEDLG_SELECTED				300

// ��ʾָ���û�������Ϣ
#define WPARAM_CHATRECORDDLG_SHOWUSER		310

// �ļ�������Ϣ
// �ļ����ַ��Ϳ�ʼ
#define WPARAM_TRANSFILE_SENDBEN			400
// �ļ����ַ������
#define WPARAM_TRANSFILE_SENDPART			401
// �ļ����ַ������
#define WPARAM_TRANSFILE_SENDEND			402
// �ļ�����ʧ��
#define WPARAM_TRANSFILE_SENDERR			403

// �ļ����ֽ��տ�ʼ
#define WPARAM_TRANSFILE_RECVBEN			405
// �ļ����ֽ������
#define WPARAM_TRANSFILE_RECVPART			406
// �ļ����ֽ������
#define WPARAM_TRANSFILE_RECVEND			407
// �ļ�����ʧ��
#define WPARAM_TRANSFILE_RECVERR			408

// ��������Ϣ
// �������
#define WPARAM_PROGRESSBAR_COMPLETESEND		410
// �������
#define WPARAM_PROGRESSBAR_COMPLETERECV		411
// ��ֹ����
#define WPARAM_PROGRESSBAR_BREAKSEND		412
// ��ֹ����
#define WPARAM_PROGRESSBAR_BREAKRECV		413
// ��ʼ����
#define WPARAM_PROGRESSBAR_BEGINSEND		414
// ��ʼ����
#define WPARAM_PROGRESSBAR_BEGINRECV		415
// �ܾ�����
#define WPARAM_PROGRESSBAR_REFUSERECV		416
// ���Ϊ
#define WPARAM_PROGRESSBAR_SAVEAS			417
// ���������ļ�
#define WPARAM_PROGRESSBAR_SENDOFFLINE		418
// ���������ļ�֪ͨ��Ϣ
#define WPARAM_PROGRESSBAR_SENDONLINE		419

// ��ҳ��ȡģʽ��Ϣ
// ���ճɹ�
#define WPARAM_WEBURLCLIENT_RECVSUCCESS		500


// ���������ļ����տ�ʼ
#define WPARAM_UPDATE_RECVBEGIN			600
// ���������ļ����ղ��ֳɹ�
#define WPARAM_UPDATE_RECVPART			601
// ���������ļ��������
#define WPARAM_UPDATE_RECVEND			602
// ���������ļ����մ���
#define WPARAM_UPDATE_RECVERR			603


// �и��µİ汾֪ͨ
#define WPARAM_HAVE_NEWVERSION			610

// ���°汾(0 �C ���°汾��1 �C �������°汾������ʹ�ã� 2 �C �������)
#define LPARAM_HAVE_LASTVERSION			0
// �������°汾������ʹ��
#define LPARAM_HAVE_NEWVERSION			1
// �������
#define LPARAM_HAVE_MUSTUPDATE			2


// Hessian�ͻ����յ��û���������
#define WPARAM_HESSIAN_RECVECONTACT		700
