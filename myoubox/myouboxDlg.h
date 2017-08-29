
// myouboxDlg.h : ͷ�ļ�
//

#pragma once

#include "..\..\..\..\common\LKComponent\GDI\LKMainDialog.h"
#include "..\..\..\..\common\LKComponent\GDI\LKButton.h"
#include "..\..\..\..\common\LKComponent\GDI\LKEdit.h"
#include "..\..\..\..\common\LKComponent\GDI\LKTreeCtrl.h"
#include "..\..\..\..\common\LKComponent\GDI\LKTab.h"
#include "..\..\..\..\common\LKComponent\GDI\LKContainer.h"



// CmyouboxDlg �Ի���
class CmyouboxDlg : public CLKMainDialog
{
// ����
public:
	CmyouboxDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CmyouboxDlg();
	// ɱָ������
	static bool KillProcessByProcessName(const CString& csAppName, bool& bIsProcessExist);

// �Ի�������
	enum { IDD = IDD_MYOUBOX_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnEnChangeEdit();
	afx_msg void OnEBnClickedButtonSearch(); 
	DECLARE_MESSAGE_MAP()
protected:
	// ��ʼ��ͼƬ�б�
	virtual void InitImageList();
	// ��ʼ������ǰ��ͼƬ
	virtual void OnInitMemImg();
	virtual LRESULT OnCommonMsg(WPARAM wParam, LPARAM lParam);
	// �Զ���˵���ť������
	virtual void OnMenuClick();
	// �ж�����Ƿ��������Զ�������Χ��
	virtual bool IsInOther(CPoint point);
	// �������
	virtual void OnTrayLButtonDown();
	// �Ҽ�����
	virtual void OnTrayRButtonUp();
	// ��С����ť������
	virtual void OnMinClick();
	//// ����˫����Ϣ
	//virtual void OnTrayLDBClick();
	// �¼�
	virtual BOOL OnEnterPress(HWND hCrtl, LPARAM lparam);
private:
	// ���������
	HANDLE m_hStartProcess = 0;
	// ������ȫ·��
	CString m_strMainProcess;
	HICON m_hSmallIcon = 0;
	// ������
	CLKEdit		m_ctlSearch;
	// ������ť
	CLKButton	m_BtnSearch;
	//// Ƥ����ť
	//CLKButton	m_BtnSkin;
	//// ��С����ť
	//CLKButton	m_BtnSkin;
	//// ��󻯰�ť
	//CLKButton	m_BtnSkin;
	//// �رհ�ť
	//CLKButton	m_BtnSkin;
	// ������Ϸ����
	CLKTreeCtrl m_treeMain;
	// �����������ǩ
	CLKTab			m_tabMain;
	// ��Ϸ�б�
	CLKContainer m_Container;

private:
	// �����ӿؼ���λ��
	void AdjustChildCtrl();
	// ������Ϸ����
	void LoadGameInfo();
	// ������Ϸ��������
	void LoadGameTypeInfo();
	// �������οؼ�ѡ����ı�
	void OnTreeCtrlSelectedChanged(PLKTREEITEM pOldItem);
	// ����TAB�ؼ�ѡ����ı�
	void OnTabCtrlSelectedChanged();
	// ������������
	void UpdateAllDlgBGImg();
	void OnOpenMainPanel();
	void OnEBnClickedButtonSearchI();
	bool GetProcessidFromName(CString &strName);
	static UINT RunGame(LPVOID lParam);
	static UINT RunTimer(LPVOID lParam);
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnActivateApp(BOOL bActive, DWORD dwThreadID);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL DestroyWindow();
};
