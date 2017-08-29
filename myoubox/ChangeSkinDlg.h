#pragma once
#include "..\..\..\..\common\LKComponent\GDI\LKMaskDialog.h"
#include "..\..\..\..\common\LKComponent\GDI\LKBtnListBox.h"

#include "resource.h"
struct SkinItem{
	CString		strPath;
	CLKImage	*pImg;
};
// CChangeSkinDlg 对话框

class CChangeSkinDlg : public CLKMaskDialog
{
	DECLARE_DYNAMIC(CChangeSkinDlg)

public:
	CChangeSkinDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChangeSkinDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_CHANGESKIN };
protected:
	// 初始化图片列表
	//virtual void InitImageList();

protected:
	LRESULT OnLoadMsg(WPARAM wParam, LPARAM lParam);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual LRESULT OnCommonMsg(WPARAM wParam, LPARAM lParam);
	// 增加皮肤图片按钮点击事件
	void OnBtnAddSkin();
	// 重置皮肤图片按钮点击事件
	void OnBtnResetSkin();

	DECLARE_MESSAGE_MAP()
private:
	// 初始化皮肤是否完成
	bool			m_bInitSkin;
	CLKBtnListBox	m_ltSkin;

	// 增加皮肤
	CLKButton		m_btnAdd;
	// 重置皮肤
	CLKButton		m_btnReset;
	// 加载皮肤按钮
	void LoadSkinBtn();
	// 加载皮肤按钮线程函数
	static UINT LoadSkinBtnThread(LPVOID pParam);
public:
	virtual BOOL OnInitDialog();
	
};
