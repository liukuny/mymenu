#pragma once
//#include "D:\personalproject\��Ϸ�˵�\code\myoubox\Module\gclass.h"
#include "gclass.h"
#include "..\..\..\..\common\LKComponent\GDI\LKImage.h"


//��Ϸ��ţ���Ϸ���ƣ���Ϸ����������Ϸͼ�꣨��ѡ��,����ֵ
//gameId, gameName, launcher, icon, dp
// ��Ϸ����ṹ
typedef struct GameItem
{
	//��Ϸ���
	CString strGameId;
	//��Ϸ����
	CString strGameName;
	//��Ϸ��������
	CString strGameStartProgram;
	//��Ϸͼ�꣨��ѡ��
	CString strGameIcon;
	//����ֵ
	CString strGameIndex;
	//��־ֵ(�Ƿ���˸)
	CString strGameFlag;
	// ��̬ͼ���־ֵ
	CString strGameGifFlag;
	// �����־ֵ
	CString strNewDlgFlag;
	// ��Ϸ���ͱ���б�
	list<int> ltGameType;
	//��Ϸ��ƴ��
	CString strGameNamePY;
	//��Ϸ������ȫ·����
	CString strGameMainProcessName;
	// �����Ӧ�����ļ���
	CString strPopPathname;

	// ���ļ������������ֶ�
	CLKImage *pImg = 0;
	bool operator < (GameItem &Item)
	{
		return StrToInt(strGameIndex) < StrToInt(Item.strGameIndex);
	}
}*PGameItem;

// ��Ϸ���Ϳ���ṹ
typedef struct GameTypeItem
{
	// ��Ϸ���ͱ��
	int nId;
	// ��Ϸ��������
	CString strName;
	// ��Ϸ���͸�����б�
	list<int> ltParentName;
}*PGameTypeItem;

// ��λ����ṹ
typedef struct IndexItem
{
	//��Ϸ���
	CString strGameId;
	//��Ϸ����
	CString strGameName;
	//��Ϸ��������
	CString strGameStartProgram;
	//��Ϸͼ�꣨��ѡ��
	CString strGameIcon;
	//����ֵ
	CString strGameIndex;
	//��־
	CString strFlag;
	//��Ϸ��ƴ��
	CString strGameNamePY;
	// �����Ӧ�����ļ���
	CString strPopPathname;
}*PIndexItem;

// �����ϱ���Ϸ����
typedef struct UploadGameItem
{
	//��Ϸ���
	CString strGameId;
	//��Ϸ����
	CString strGameName;
	//��Ϸ��������
	CString strGameStartProgram;
}*PUploadGameItem;

class CLocalDataInfo : public CSafeSingle<CLocalDataInfo>
{
public:
	// ��ʼ����Ϸ�б�
	void InitGameList();
	// ��ȡ��Ϸ����
	PGameItem GetGameByName(CString &strGameName);
	// ��ȡ��Ϸ�����б�
	void GetGameList(list<PGameItem> &lt){ lt = m_ltGame; }
	// ��ȡ��Ϸ���������б�
	void GetGameTypeList(list<PGameTypeItem> &lt){ lt = m_ltGameType; }
	// ��ȡ��Ϸ��λ�����б�
	void GetGameSortList(list<PIndexItem> &lt){ lt = m_ltIndex; }

	// ��ȡ��Ϸ���͵�һ�������б�
	void GetGameTypeFirstLevelList(list<PGameTypeItem> &lt);
	// ��ȡ��Ϸ���͵ڶ��������б�
	void GetGameTypeSecondLevelList(list<PGameTypeItem> &lt);
	// ��ȡ��Ϸ���͵ڶ��������б�
	void GetGameTypeSecondLevelList(int nParentId, list<PGameTypeItem> &lt);
	// ��ȡָ������ID��Ϸ�����б�
	void GetGameList(int nId, list<PGameItem> &lt, int nParentId = 0);
	// ��ȡָ����Ϸ�������б�
	void GetGameListBySearch(CString &strKey, list<PGameItem> &lt);
	// ��ȡ�����ϱ���Ϸ����
	void GetUploadGameItem(PUploadGameItem pItem);
	void GetUploadGameItem(CString &strId, CString &strName, CString &strPath){ UploadGameItem Item; GetUploadGameItem(&Item); strId = Item.strGameId; strName = Item.strGameName; strPath = Item.strGameStartProgram; }
	// ���������ϱ���Ϸ����
	void SetUploadGameItem(PUploadGameItem pItem);
	void SetUploadGameItem(const CString &strId, const CString &strName, const CString &strPath){ UploadGameItem Item; Item.strGameId = strId; Item.strGameName = strName; Item.strGameStartProgram = strPath; SetUploadGameItem(&Item); }
private:
	// �����ϱ���Ϸ����
	UploadGameItem m_ugItem;
	//
	list<PGameItem> m_ltGame;
	list<PGameTypeItem> m_ltGameType;
	list<PIndexItem> m_ltIndex;
	// ����һ����Ϸ����
	void ProcSingleGameData(const CStringA &s);
	// ����һ����Ϸ��������
	void ProcSingleGameTypeData(const CStringA &s);
	// ����һ����λ����
	void ProcSingleIndexData(const CStringA &s);
	// �������ݵ��б�
	void ParseDataToArr(const CString &sP, CStringArray &arr, TCHAR cSplit = L'|');
	// �ϲ���Ϸ���������
	void CombinGameIndexList();
private:
	CLocalDataInfo();
	~CLocalDataInfo();
	friend class CSingle<CLocalDataInfo>;
};

