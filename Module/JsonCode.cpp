#include "JsonCode.h"
#include "log.h"
#include "ConfigFile.h"
#include "atlenc.h"
#include "BarInfo.h"
#include "GameInfo.h"
#include "UserOnlineInfo.h"
template <> CJsonEncode *CSingle<CJsonEncode>::m_pInstance = 0;

CJsonEncode::CJsonEncode()
{
}

CJsonEncode::~CJsonEncode()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <> CJsonDecode *CSingle<CJsonDecode>::m_pInstance = 0;

CJsonDecode::CJsonDecode()
{
}

CJsonDecode::~CJsonDecode()
{
}


// 解析配置数据
bool CJsonDecode::DeCodeConfigData(const string &strData, ConfigDataItem &Item)
{
	//{ "data":[{"date":"2016-12-05", "games" : [{"game_name":"英雄联盟", "icon" : "http://static.myoubox.com/6e/e6/10001.6ee6ea10846f2bb4dc5de3d6fbbe6bde.png", "rank" : 900, "game_id" : 10001, "launcher" : "http://static.myoubox.com/d5/95/lol_launcher.d595837d74f28b3713e50a1597a4208f.zip"}, { "game_name":"守望先锋", "icon" : "http://static.myoubox.com/89/c4/10002.89c48d77026d5b50178ed0bdad2705ab.png", "rank" : 800, "game_id" : 10002, "launcher" : "http://static.myoubox.com/7a/54/lol_launcher.7a544390b9535f23fa3d87077b083692.zip" }], "update_packs" : [{"ver":"20161101000000", "size" : 115679, "type" : 1, "url" : "http://static.myoubox.com/d5/95/update_test1.d595837d74f28b3713e50a1597a4208f.zip"}], "programs" : [{"size":115679, "type" : 1, "url" : "http://static.myoubox.com/54/f1/sm1_test.54f1f58401a8a1abf67d408961e43b67.zip"}]}], "retCode" : 0, "retMsg" : "success" }	// 获取配置
	CLogJsonCode::WriteLog("DeCodeConfigData beg, src: %s", strData.c_str());
	bool bRet(false);
	auto vl = json::Deserialize(strData);
	if (vl.GetType() == json::ValueType::NULLVal)
	{
		CLogJsonCode::WriteLog("no json obj, src: %s", strData.c_str());
		return bRet;
	}
	if (!vl.HasKey("retCode") || !vl.HasKey("retMsg") || !vl.HasKey("data"))
	{
		// 失败
		CLogJsonCode::WriteLog("不完整的json, src: %s", strData.c_str());
		return bRet;
	}

	if (vl["data"].GetType() != json::ValueType::ArrayVal)
	{
		// 失败
		CLogJsonCode::WriteLog("不符合格式的json, src: %s", strData.c_str());
		return bRet;
	}
	//成员ID列表
	json::Array arrData = vl["data"].ToArray();
	for (auto it : arrData)
	{
		SortDataItem item;
		if (!it.HasKey("date"))
		{
			// 失败
			CLogJsonCode::WriteLog("没有date字段, src: %s", strData.c_str());
			continue;
		}
		if (it["date"].GetType() == json::ValueType::StringVal)
		{
			item.strDate = it["date"].ToString();
		}

		if (it.HasKey("games"))
		{
			// 排位库数据
			json::Array arrSData = it["games"].ToArray();
			for (auto its : arrSData)
			{
				SortGameItem items;
				if (its.HasKey("game_id"))
				{
					if (its["game_id"].GetType() == json::ValueType::Int64Val || its["game_id"].GetType() == json::ValueType::IntVal)
					{
						items.game_id = its["game_id"].ToInt64();
					}
				}
				if (its.HasKey("game_name"))
				{
					if (its["game_name"].GetType() == json::ValueType::StringVal)
					{
						items.game_name = its["game_name"].ToString();
					}
				}
				if (its.HasKey("icon"))
				{
					if (its["icon"].GetType() == json::ValueType::StringVal)
					{
						items.icon = its["icon"].ToString();
					}
				}
				if (its.HasKey("launcher"))
				{
					if (its["launcher"].GetType() == json::ValueType::StringVal)
					{
						items.launcher = its["launcher"].ToString();
					}
				}
				if (its.HasKey("rank"))
				{
					if (its["rank"].GetType() == json::ValueType::IntVal)
					{
						items.rank = its["rank"].ToInt();
					}
				}
				item.ltGame.push_back(items);
			}
		}
		Item.ltSD.push_back(item);
	}

	if (vl.HasKey("config"))
	{
		if (vl["config"].HasKey("update_packs"))
		{
			list<UpLevelDataItem> ltUD;
			// 升级包数据
			json::Array arrUData = vl["config"]["update_packs"].ToArray();
			for (auto itu : arrUData)
			{
				UpLevelDataItem itemu;
				if (itu.HasKey("size"))
				{
					if (itu["size"].GetType() == json::ValueType::IntVal)
					{
						itemu.size = itu["size"].ToInt();
					}
				}
				if (itu.HasKey("type"))
				{
					if (itu["type"].GetType() == json::ValueType::IntVal)
					{
						itemu.type = itu["type"].ToInt();
					}
				}
				if (itu.HasKey("url"))
				{
					if (itu["url"].GetType() == json::ValueType::StringVal)
					{
						itemu.url = itu["url"].ToString();
					}
				}
				if (itu.HasKey("ver"))
				{
					if (itu["ver"].GetType() == json::ValueType::StringVal)
					{
						itemu.ver = itu["ver"].ToString();
					}
				}
				Item.ltUD.push_back(itemu);
			}
		}
		if (vl["config"].HasKey("programs"))
		{
			// 小程序数据
			json::Array arrPData = vl["config"]["programs"].ToArray();
			for (auto itp : arrPData)
			{
				ProgramDataItem itemp;
				if (itp.HasKey("size"))
				{
					if (itp["size"].GetType() == json::ValueType::IntVal)
					{
						itemp.size = itp["size"].ToInt();
					}
				}
				if (itp.HasKey("type"))
				{
					if (itp["type"].GetType() == json::ValueType::IntVal)
					{
						itemp.type = itp["type"].ToInt();
					}
				}
				if (itp.HasKey("url"))
				{
					if (itp["url"].GetType() == json::ValueType::StringVal)
					{
						itemp.url = itp["url"].ToString();
					}
				}
				Item.ltPD.push_back(itemp);
			}
		}
		if (vl["config"].HasKey("talking_url"))
		{
			if (vl["config"]["talking_url"].GetType() == json::ValueType::StringVal)
			{
				Item.talking_url = vl["config"]["talking_url"].ToString();
			}
		}
	}
	CLogJsonCode::WriteLog("DeCodeConfigData end");
	return true;
}

