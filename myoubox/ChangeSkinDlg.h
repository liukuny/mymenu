#pragma once
#include "..\..\..\..\common\LKComponent\GDI\LKMaskDialog.h"
#include "..\..\..\..\common\LKComponent\GDI\LKBtnListBox.h"

#include "resource.h"
struct SkinItem{
	CString		strPath;
	CLKImage	*pImg;
};
// CChangeSkinDlg �Ի���

class CChangeSkinDlg : public CLKMaskDialog
{
	DECLARE_DYNAMIC(CChangeSkinDlg)

public:
	CChangeSkinDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChangeSkinDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_CHANGESKIN };
protected:
	// ��ʼ��ͼƬ�б�
	//virtual void InitImageList();

protected:
	LRESULT OnLoadMsg(WPARAM wParam, LPARAM lParam);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual LRESULT OnCommonMsg(WPARAM wParam, LPARAM lParam);
	// ����Ƥ��ͼƬ��ť����¼�
	void OnBtnAddSkin();
	// ����Ƥ��ͼƬ��ť����¼�
	void OnBtnResetSkin();

	DECLARE_MESSAGE_MAP()
private:
	// ��ʼ��Ƥ���Ƿ����
	bool			m_bInitSkin;
	CLKBtnListBox	m_ltSkin;

	// ����Ƥ��
	CLKButton		m_btnAdd;
	// ����Ƥ��
	CLKButton		m_btnReset;
	// ����Ƥ����ť
	void LoadSkinBtn();
	// ����Ƥ����ť�̺߳���
	static UINT LoadSkinBtnThread(LPVOID pParam);
public:
	virtual BOOL OnInitDialog();
	
};
