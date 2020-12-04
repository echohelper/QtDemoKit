#include "YZAzzXggProxy.h"

#include <YZAzzXggData/YZAzzXggData.h>

YZAzzXggData::YZAzzXggData()
{
	
	//文件内字段测试
	//void TestKeyAaa();
	//void TestKeyBbb(QString &str);
	//TestKeyCcc
	//TestKey222
	//TestKey--
	//TestKey222

}

YZAzzXggData::~YZAzzXggData()
{

}

YZAzzXggData * YZAzzXggData::instance()
{
	static YZAzzXggData data;
	return &data;
}

void YZAzzXggData::clear()
{
	//m_bFlagCraft = false;
	//m_crafts.clear();
}

bool YZAzzXggData::createAzzXgg(YZAzzXgg &azzxgg)
{
	bool bTmp = YZAzzXggProxy::createAzzXgg(azzxgg);
	if (bTmp)
	{
		m_mapAzzXgg.insert(azzxgg._id, azzxgg);
	}
	return bTmp;
}

bool YZAzzXggData::deleteAzzXgg(const QString &azzxggId)
{
	bool bTmp = YZAzzXggProxy::deleteAzzXgg(azzxggId);
	if (bTmp)
	{
		m_mapAzzXgg.remove(azzxggId);
	}
	return bTmp;
}

bool YZAzzXggData::updateAzzXgg(YZAzzXgg &azzxgg)
{
	const YZAzzXgg &azzxggOld = m_mapAzzXgg[azzxgg._id];
	bool bTmp = YZAzzXggProxy::updateAzzXgg(azzxggOld, azzxgg);
	if (bTmp)
	{
		m_mapAzzXgg.insert(azzxgg._id, azzxgg);
	}
	return bTmp;
}

bool YZAzzXggData::getAzzXggRangeCount(const YZAzzXggCondition &condition, int &count)
{
	return YZAzzXggProxy::getAzzXggRangeCount(condition, count);
}

bool YZAzzXggData::getAzzXggRangeData(const YZAzzXggCondition &condition, int skip, int limit, QList<YZAzzXgg> &azzxggs)
{
	bool bTmp = YZAzzXggProxy::getAzzXggRangeData(condition, skip, limit, azzxggs);
	if (bTmp)
	{
		m_mapAzzXgg.clear();
		for (const YZAzzXgg &azzxgg : azzxggs)
		{
			m_mapAzzXgg.insert(azzxgg._id, azzxgg);
		}
	}
	return true;
}

bool YZAzzXggData::getAzzXgg(const QString &id, YZAzzXgg &azzxgg, bool bCache)
{
	if (bCache && m_mapAzzXgg.contains(id))
	{
		azzxgg = m_mapAzzXgg[id];
		return true;
	}

	bool bTmp = YZAzzXggProxy::getAzzXgg(id, azzxgg);
	if (bTmp)
	{
		m_mapAzzXgg.insert(id, azzxgg);
	}
	return bTmp;
}

QString YZAzzXggData::getAzzXggName(const QString &azzxggId)
{
	if (m_mapAzzXgg.contains(azzxggId))
	{
		const YZAzzXgg &azzxgg = m_mapAzzXgg[azzxggId];
		return azzxgg.name;
	}

	return QString();
}
//
//QString YZAzzXggData::getCraftName(const QString &craftId)
//{
//	if (craftId.isEmpty())
//	{
//		return QString();
//	}
//
//	if (!m_bFlagCraft)
//	{
//		QList<YZCraft> crafts;
//		getCraft(crafts);
//	}
//
//	auto iter = std::find_if(m_crafts.begin(), m_crafts.end(), [&](const YZCraft &craft)
//	{
//		return (craft._id == craftId);
//	});
//	if (iter != m_crafts.end())
//	{
//		return (*iter).name;
//	}
//
//	return QString();
//}
//
//QString YZAzzXggData::getCraftIdByName(const QString &craftName)
//{
//	if (craftName.isEmpty())
//	{
//		return QString();
//	}
//
//	if (!m_bFlagCraft)
//	{
//		QList<YZCraft> crafts;
//		getCraft(crafts);
//	}
//
//	auto iter = std::find_if(m_crafts.begin(), m_crafts.end(), [&](const YZCraft &craft)
//	{
//		return (craft.name == craftName);
//	});
//	if (iter != m_crafts.end())
//	{
//		return (*iter)._id;
//	}
//
//	return QString();
//}
//
//bool YZAzzXggData::getCraft(QList<YZCraft> &crafts)
//{
//	if (m_bFlagCraft)
//	{
//		crafts = m_crafts;
//		return m_bFlagCraft;
//	}
//
//	m_bFlagCraft = YZAzzXggProxy::getCraft(crafts);
//	m_crafts = crafts;
//	return m_bFlagCraft;
//}