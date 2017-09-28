#pragma once
//#include "D:\personalproject\游戏菜单\code\myoubox\Module\gclass.h"
#include "gclass.h"
#include "..\..\..\..\common\LKComponent\GDI\LKImage.h"


//游戏编号，游戏名称，游戏启动程序，游戏图标（可选）,排序值
//gameId, gameName, launcher, icon, dp
// 游戏库项结构
typedef struct GameItem
{
	//游戏编号
	CString strGameId;
	//游戏名称
	CString strGameName;
	//游戏启动程序
	CString strGameStartProgram;
	//游戏图标（可选）
	CString strGameIcon;
	//排序值
	CString strGameIndex;
	//标志值(是否闪烁)
	CString strGameFlag;
	// 动态图标标志值
	CString strGameGifFlag;
	// 浮层标志值
	CString strNewDlgFlag;
	// 游戏类型编号列表
	list<int> ltGameType;
	//游戏名拼音
	CString strGameNamePY;
	//游戏主进程全路径名
	CString strGameMainProcessName;
	// 浮层对应本地文件名
	CString strPopPathname;

	// 非文件解析出来的字段
	CLKImage *pImg = 0;
	bool operator < (GameItem &Item)
	{
		return StrToInt(strGameIndex) < StrToInt(Item.strGameIndex);
	}
}*PGameItem;

// 游戏类型库项结构
typedef struct GameTypeItem
{
	// 游戏类型编号
	int nId;
	// 游戏类型名称
	CString strName;
	// 游戏类型父编号列表
	list<int> ltParentName;
}*PGameTypeItem;

// 排位库项结构
typedef struct IndexItem
{
	//游戏编号
	CString strGameId;
	//游戏名称
	CString strGameName;
	//游戏启动程序
	CString strGameStartProgram;
	//游戏图标（可选）
	CString strGameIcon;
	//排序值
	CString strGameIndex;
	//标志
	CString strFlag;
	//游戏名拼音
	CString strGameNamePY;
	// 浮层对应本地文件名
	CString strPopPathname;
}*PIndexItem;

// 运行上报游戏参数
typedef struct UploadGameItem
{
	//游戏编号
	CString strGameId;
	//游戏名称
	CString strGameName;
	//游戏启动程序
	CString strGameStartProgram;
}*PUploadGameItem;

class CLocalDataInfo : public CSafeSingle<CLocalDataInfo>
{
public:
	// 初始化游戏列表
	void InitGameList();
	// 获取游戏数据
	PGameItem GetGameByName(CString &strGameName);
	// 获取游戏数据列表
	void GetGameList(list<PGameItem> &lt){ lt = m_ltGame; }
	// 获取游戏类型数据列表
	void GetGameTypeList(list<PGameTypeItem> &lt){ lt = m_ltGameType; }
	// 获取游戏排位数据列表
	void GetGameSortList(list<PIndexItem> &lt){ lt = m_ltIndex; }

	// 获取游戏类型第一级数据列表
	void GetGameTypeFirstLevelList(list<PGameTypeItem> &lt);
	// 获取游戏类型第二级数据列表
	void GetGameTypeSecondLevelList(list<PGameTypeItem> &lt);
	// 获取游戏类型第二级数据列表
	void GetGameTypeSecondLevelList(int nParentId, list<PGameTypeItem> &lt);
	// 获取指定类型ID游戏数据列表
	void GetGameList(int nId, list<PGameItem> &lt, int nParentId = 0);
	// 获取指定游戏名数据列表
	void GetGameListBySearch(CString &strKey, list<PGameItem> &lt);
	// 获取运行上报游戏参数
	void GetUploadGameItem(PUploadGameItem pItem);
	void GetUploadGameItem(CString &strId, CString &strName, CString &strPath){ UploadGameItem Item; GetUploadGameItem(&Item); strId = Item.strGameId; strName = Item.strGameName; strPath = Item.strGameStartProgram; }
	// 设置运行上报游戏参数
	void SetUploadGameItem(PUploadGameItem pItem);
	void SetUploadGameItem(const CString &strId, const CString &strName, const CString &strPath){ UploadGameItem Item; Item.strGameId = strId; Item.strGameName = strName; Item.strGameStartProgram = strPath; SetUploadGameItem(&Item); }
private:
	// 运行上报游戏参数
	UploadGameItem m_ugItem;
	//
	list<PGameItem> m_ltGame;
	list<PGameTypeItem> m_ltGameType;
	list<PIndexItem> m_ltIndex;
	// 处理一条游戏数据
	void ProcSingleGameData(const CStringA &s);
	// 处理一条游戏类型数据
	void ProcSingleGameTypeData(const CStringA &s);
	// 处理一条排位数据
	void ProcSingleIndexData(const CStringA &s);
	// 解析数据到列表
	void ParseDataToArr(const CString &sP, CStringArray &arr, TCHAR cSplit = L'|');
	// 合并游戏库和索引库
	void CombinGameIndexList();
private:
	CLocalDataInfo();
	~CLocalDataInfo();
	friend class CSingle<CLocalDataInfo>;
};

