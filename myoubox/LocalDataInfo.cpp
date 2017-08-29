#include "stdafx.h"
#include "LocalDataInfo.h"
#include "ConfigFile.h"

template <> CLocalDataInfo *CSingle<CLocalDataInfo>::m_pInstance = 0;

CLocalDataInfo::CLocalDataInfo()
{
}


CLocalDataInfo::~CLocalDataInfo()
{
	for (list<PIndexItem>::iterator it = m_ltIndex.begin(); it != m_ltIndex.end(); it++)
	{
		PIndexItem p = *it;
		delete p;
	}
	for (list<PGameTypeItem>::iterator it = m_ltGameType.begin(); it != m_ltGameType.end(); it++)
	{
		PGameTypeItem p = *it;
		delete p;
	}
	for (list<PGameItem>::iterator itG = m_ltGame.begin(); itG != m_ltGame.end(); itG++)
	{
		PGameItem pG = *itG;
		if (pG->pImg)
		{
			delete pG->pImg;
		}
		delete pG;
	}
}

// 处理一条游戏数据
void CLocalDataInfo::ProcSingleGameData(const CStringA &s)
{
	CString sw;
	sw = s;
	CStringArray arr;
	ParseDataToArr(sw, arr);
	if (arr.GetCount() > 4)
	{
		PGameItem pItem = new GameItem;
		pItem->strGameId = arr[0];
		pItem->strGameName = arr[1];
		pItem->strGameStartProgram = arr[2];
		pItem->strGameIcon = arr[3];
		pItem->strGameIndex = arr[4];
		if (arr.GetCount() > 5)
		{
			CStringArray arr2;
			CString sw2 = arr[5];
			ParseDataToArr(sw2, arr2, L',');
			for (int i = 0; i < arr2.GetCount(); i++)
			{
				pItem->ltGameType.push_back(StrToInt(arr2[i]));
			}
		}
		if (arr.GetCount() > 6)
		{
			pItem->strGameNamePY = arr[6];
		}
		if (arr.GetCount() > 7)
		{
			pItem->strGameMainProcessName = arr[7];
			if (pItem->strGameStartProgram.Find('\\') < 0 && !pItem->strGameStartProgram.IsEmpty() && !pItem->strGameMainProcessName.IsEmpty())
			{
				int nPos = pItem->strGameMainProcessName.ReverseFind('\\');
				if (nPos > 0)
				{
					pItem->strGameStartProgram = pItem->strGameMainProcessName.Left(nPos + 1) + pItem->strGameStartProgram;
				}
			}
		}
		m_ltGame.push_back(pItem);
	}
}

// 处理一条游戏类型数据
void CLocalDataInfo::ProcSingleGameTypeData(const CStringA &s)
{
	CString sw;
	sw = s;
	CStringArray arr;
	ParseDataToArr(sw, arr);
	if (arr.GetCount() > 1)
	{
		PGameTypeItem pItem = new GameTypeItem;
		pItem->nId = StrToInt(arr[0]);
		pItem->strName = arr[1];
		if (arr.GetCount() > 2)
		{
			CStringArray arr2;
			CString sw2 = arr[2];
			ParseDataToArr(sw2, arr2, L',');
			for (int i = 0; i < arr2.GetCount(); i++)
			{
				pItem->ltParentName.push_back(StrToInt(arr2[i]));
			}
		}
		m_ltGameType.push_back(pItem);
	}
}

// 处理一条排位数据
void CLocalDataInfo::ProcSingleIndexData(const CStringA &s)
{
	CString sw;
	sw = s;
	CStringArray arr;
	ParseDataToArr(sw, arr);
	if (arr.GetCount() > 4)
	{
		PIndexItem pItem = new IndexItem;
		pItem->strGameId = arr[0];
		pItem->strGameName = arr[1];
		pItem->strGameStartProgram = arr[2];
		pItem->strGameIcon = arr[3];
		pItem->strGameIndex = arr[4];
		if (arr.GetCount() > 5)
		{
			pItem->strFlag = arr[5];
		}
		//if (arr.GetCount() > 6)
		//{
		//	pItem->strGameNamePY = arr[6];
		//}
		if (arr.GetCount() > 6)
		{
			pItem->strPopPathname = arr[6];
		}
		m_ltIndex.push_back(pItem);
	}
}

// 解析数据到列表
void CLocalDataInfo::ParseDataToArr(const CString &sP, CStringArray &arr, TCHAR cSplit)
{
	if (sP.IsEmpty()) return;
	//char cSplit = 3;
	arr.RemoveAll();
	CString s = sP;
	int nPos = s.Find(cSplit);
	while (nPos >= 0)
	{
		CString sL = s.Left(nPos);
		arr.Add(sL);
		s = s.Right(s.GetLength() - nPos - 1);
		nPos = s.Find(cSplit);
	}
	arr.Add(s);
}

// 初始化游戏列表
void CLocalDataInfo::InitGameList()
{
	CLogClient::WriteLogW(L"初始化游戏列表");
	string sGame = CConfigFile::GetInstance()->GetGameDbPathNameA();
	string sType = CConfigFile::GetInstance()->GetGameTypeDbPathNameA();
	string sIndex = CConfigFile::GetInstance()->GetIndexDbPathNameA();
	{
		fstream f(sGame.c_str(), ios::in);
		if (f.is_open())
		{
			const int nBufLen = 10 * 1024;
			char *pBuf = new char[nBufLen];
			while (!f.eof())
			{
				memset(pBuf, 0, nBufLen);
				f.getline(pBuf, nBufLen);
				CStringA s = pBuf;
				if (!s.IsEmpty())
				{
					// 处理一条游戏数据
					ProcSingleGameData(s);
					//break;
				}
			}
			delete[]pBuf;
		}
		f.close();
	}

	{
		fstream f(sType.c_str(), ios::in);
		if (f.is_open())
		{
			const int nBufLen = 10 * 1024;
			char *pBuf = new char[nBufLen];
			while (!f.eof())
			{
				memset(pBuf, 0, nBufLen);
				f.getline(pBuf, nBufLen);
				CStringA s = pBuf;
				if (!s.IsEmpty())
				{
					// 处理一条游戏类型数据
					ProcSingleGameTypeData(s);
					//break;
				}
			}
			delete[]pBuf;
		}
		f.close();
	}

	CLogClient::WriteLogW(L"初始化游戏列表, 游戏类型个数：%d", m_ltGameType.size());

	fstream f2(sIndex.c_str(), ios::in);
	if (f2.is_open())
	{
		const int nBufLen = 10 * 1024;
		char *pBuf = new char[nBufLen];
		while (!f2.eof())
		{
			memset(pBuf, 0, nBufLen);
			f2.getline(pBuf, nBufLen);
			CStringA s = pBuf;
			if (!s.IsEmpty())
			{
				// 处理一条游戏数据
				ProcSingleIndexData(s);
				//break;
			}
		}
		delete[]pBuf;
	}
	f2.close();
	CLogClient::WriteLogW(L"初始化游戏列表, 游戏个数：%d", m_ltGame.size());

	// 合并游戏库和索引库
	CombinGameIndexList();

	//// 加载游戏数据
	//LoadGameInfo();

}
//
//bool LessSecond(const PGameItem p1, const PGameItem p2)
//{
//	return StrToInt(p1->strGameIndex) < StrToInt(p2->strGameIndex);
//}


// 合并游戏库和索引库
void CLocalDataInfo::CombinGameIndexList()
{
	for (list<PIndexItem>::iterator it = m_ltIndex.begin(); it != m_ltIndex.end(); it++)
	{
		PIndexItem p = *it;
		bool bFind(false);
		for (list<PGameItem>::iterator itG = m_ltGame.begin(); itG != m_ltGame.end(); itG++)
		{
			PGameItem pG = *itG;
			if (pG->strGameId.Compare(p->strGameId) == 0)
			{
				bFind = true;
				//pG->strGameIndex += p->strGameIndex;
				pG->strGameIndex.Format(L"%d", StrToInt(pG->strGameIndex) + StrToInt(p->strGameIndex));
				pG->strGameFlag = p->strFlag;
				if (!p->strGameName.IsEmpty())
				{
					pG->strGameName = p->strGameName;
				}
				if (!p->strGameNamePY.IsEmpty())
				{
					pG->strGameNamePY = p->strGameNamePY;
				}
				if (!p->strGameStartProgram.IsEmpty())
				{
					if (!pG->strGameStartProgram.IsEmpty())
					{
						CString strDest = pG->strGameStartProgram;
						int nIndex = strDest.ReverseFind(L'\\');
						if (nIndex > 0)
						{
							strDest = strDest.Left(nIndex + 1);
							nIndex = p->strGameStartProgram.ReverseFind(L'\\');
							if (nIndex > 0)
							{
								strDest += p->strGameStartProgram.Right(p->strGameStartProgram.GetLength() - nIndex - 1);
								if (::CopyFile(p->strGameStartProgram, strDest, FALSE))
								{
									pG->strGameStartProgram = strDest;
								}
								else
								{
									CLogError::WriteLogW(L"复制文件失败： %d from %s, to %s", ::GetLastError(), p->strGameStartProgram.GetBuffer(), strDest.GetBuffer());
								}
							}
						}
					}
				}
				if (!p->strGameIcon.IsEmpty())
				{
					pG->strGameIcon = p->strGameIcon;
				}
				if (!p->strPopPathname.IsEmpty())
				{
					pG->strPopPathname = p->strPopPathname;
				}
			}
		}
		if (!bFind)
		{
			PGameItem pItem = new GameItem;
			pItem->strGameId = p->strGameId;
			pItem->strGameName = p->strGameName;
			pItem->strGameStartProgram = p->strGameStartProgram;
			pItem->strGameIcon = p->strGameIcon;
			pItem->strGameIndex.Format(L"%d", StrToInt(pItem->strGameIndex) + StrToInt(p->strGameIndex));
			pItem->strGameFlag = p->strFlag;
			pItem->strGameNamePY = p->strGameNamePY;
			pItem->strPopPathname = p->strPopPathname;
			CLKImage *pImg = new CLKImage;
			if (!pImg->LoadEx(pItem->strGameIcon))
			{
				delete pImg;
				pImg = 0;
			}
			pItem->pImg = pImg;
			m_ltGame.push_back(pItem);
		}
	}

	// 安索引排序
	//std::sort(m_ltGame.begin(), m_ltGame.end());
	//sort(m_ltGame.begin(), m_ltGame.end(), );
	m_ltGame.sort([](PGameItem p1, PGameItem p2) { return StrToInt(p1->strGameIndex) > StrToInt(p2->strGameIndex); });
}

// 获取游戏类型第一级数据列表
void CLocalDataInfo::GetGameTypeFirstLevelList(list<PGameTypeItem> &lt)
{ 
	lt = m_ltGameType; 
	lt.remove_if([](PGameTypeItem p) 
	{ 
		if (p->ltParentName.size() > 0)
		{
			return (p->ltParentName.front() != 0 || p->ltParentName.size() != 1);
		}
		return false;
	});
}
// 获取游戏类型第二级数据列表
void CLocalDataInfo::GetGameTypeSecondLevelList(list<PGameTypeItem> &lt)
{
	lt = m_ltGameType;
	lt.remove_if([](PGameTypeItem p)
	{
		if (p->ltParentName.size() > 0)
		{
			if (p->ltParentName.size() != 1 || p->ltParentName.front() != 0)
			{
				return false;
			}
		}
		return true;
	});
}

// 获取游戏类型第二级数据列表
void CLocalDataInfo::GetGameTypeSecondLevelList(int nParentId, list<PGameTypeItem> &lt)
{
	lt = m_ltGameType;
	lt.remove_if([nParentId](PGameTypeItem p)
	{
		for (auto it : p->ltParentName)
		{
			if (it == nParentId)
			{
				return false;
			}
		}
		return true;
	});
}

// 获取指定类型ID游戏数据列表
void CLocalDataInfo::GetGameList(int nId, list<PGameItem> &lt, int nParentId)
{ 
	lt = m_ltGame;
	lt.remove_if([nId, nParentId](PGameItem p)
	{
		for (auto it:p->ltGameType)
		{
			if (it == nId)
			{
				return false;
			}
			if (nParentId != 0 && it == nParentId)
			{
				return false;
			}
		}
		return true;
	});
}

// 获取指定游戏名数据列表
void CLocalDataInfo::GetGameListBySearch(CString &strKey, list<PGameItem> &lt)
{
	lt = m_ltGame;
	CString sKey = strKey;
	sKey.MakeUpper();
	lt.remove_if([sKey](PGameItem p)
	{
		CString sTem = p->strGameName;
		sTem.MakeUpper();
		if (sTem.Find(sKey) >= 0)
		{
			return false;
		}
		if (p->strGameNamePY.Find(sKey) >= 0)
		{
			return false;
		}
		return true;
	});
}

// 获取运行上报游戏参数
void CLocalDataInfo::GetUploadGameItem(PUploadGameItem pItem)
{
	CSafeLock<CLocalDataInfo> lk(this);
	if (pItem)
	{
		pItem->strGameId = m_ugItem.strGameId;
		pItem->strGameName = m_ugItem.strGameName;
		pItem->strGameStartProgram = m_ugItem.strGameStartProgram;
	}
}

// 设置运行上报游戏参数
void CLocalDataInfo::SetUploadGameItem(PUploadGameItem pItem)
{
	CSafeLock<CLocalDataInfo> lk(this);
	if (pItem)
	{
		m_ugItem.strGameId = pItem->strGameId;
		m_ugItem.strGameName = pItem->strGameName;
		m_ugItem.strGameStartProgram = pItem->strGameStartProgram;
	}
}
