
// myouboxDlg.h : 头文件
//

#pragma once

#include "..\..\..\..\common\LKComponent\GDI\LKMainDialog.h"
#include "..\..\..\..\common\LKComponent\GDI\LKButton.h"
#include "..\..\..\..\common\LKComponent\GDI\LKEdit.h"
#include "..\..\..\..\common\LKComponent\GDI\LKTreeCtrl.h"
#include "..\..\..\..\common\LKComponent\GDI\LKTab.h"
#include "..\..\..\..\common\LKComponent\GDI\LKContainer.h"



// CmyouboxDlg 对话框
class CmyouboxDlg : public CLKMainDialog
{
// 构造
public:
	CmyouboxDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CmyouboxDlg();
	// 杀指定进程
	static bool KillProcessByProcessName(const CString& csAppName, bool& bIsProcessExist);

// 对话框数据
	enum { IDD = IDD_MYOUBOX_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	// 初始化图片列表
	virtual void InitImageList();
	// 初始化窗口前景图片
	virtual void OnInitMemImg();
	virtual LRESULT OnCommonMsg(WPARAM wParam, LPARAM lParam);
	// 自定义菜单按钮被按下
	virtual void OnMenuClick();
	// 判断鼠标是否在其它自定义区域范围内
	virtual bool IsInOther(CPoint point);
	// 左键按下
	virtual void OnTrayLButtonDown();
	// 右键处理
	virtual void OnTrayRButtonUp();
	// 最小化按钮被按下
	virtual void OnMinClick();
	//// 托盘双击消息
	//virtual void OnTrayLDBClick();
	// 事件
	virtual BOOL OnEnterPress(HWND hCrtl, LPARAM lparam);
private:
	// 启动器句柄
	HANDLE m_hStartProcess = 0;
	// 主程序全路径
	CString m_strMainProcess;
	HICON m_hSmallIcon = 0;
	// 搜索框
	CLKEdit		m_ctlSearch;
	// 搜索按钮
	CLKButton	m_BtnSearch;
	//// 皮肤按钮
	//CLKButton	m_BtnSkin;
	//// 最小化按钮
	//CLKButton	m_BtnSkin;
	//// 最大化按钮
	//CLKButton	m_BtnSkin;
	//// 关闭按钮
	//CLKButton	m_BtnSkin;
	// 热门游戏分类
	CLKTreeCtrl m_treeMain;
	// 顶部主分面标签
	CLKTab			m_tabMain;
	// 游戏列表
	CLKContainer m_Container;

private:
	// 调整子控件的位置
	void AdjustChildCtrl();
	// 加载游戏数据
	void LoadGameInfo();
	// 加载游戏类型数据
	void LoadGameTypeInfo();
	// 处理树形控件选择项改变
	void OnTreeCtrlSelectedChanged(PLKTREEITEM pOldItem);
	// 处理TAB控件选择项改变
	void OnTabCtrlSelectedChanged();
	// 更新其它窗口
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
