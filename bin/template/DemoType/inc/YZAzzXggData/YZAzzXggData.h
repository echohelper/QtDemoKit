#pragma once

#include <QMap>

#include <YZAzzXggData/YZAzzXggHeader.h>
#include <YZAzzXggData/yzazzxggdata_global.h>

#define YZAzzXggDataPtr() (YZAzzXggData::instance())

class YZAZZXGGDATA_EXPORT YZAzzXggData
{
private:
	YZAzzXggData();
	~YZAzzXggData();

public:
	static YZAzzXggData *instance();

	void clear();

	bool createAzzXgg(YZAzzXgg &azzxgg);
	bool deleteAzzXgg(const QString &azzxggId);
	bool updateAzzXgg(YZAzzXgg &azzxgg);
	bool getAzzXggRangeCount(const YZAzzXggCondition &condition, int &count);
	bool getAzzXggRangeData(const YZAzzXggCondition &condition, int skip, int limit, QList<YZAzzXgg> &azzxggs);
	bool getAzzXgg(const QString &id, YZAzzXgg &azzxgg, bool bCache = false);
	QString getAzzXggName(const QString &azzxggId);

	//bool getCraft(QList<YZCraft> &crafts);
	//QString getCraftName(const QString &craftId);
	//QString getCraftIdByName(const QString &craftName);
	//文件内字段测试
	//void TestKeyAaa();
	//void TestKeyBbb(QString &str);
	//TestKeyCcc
	//TestKey222
	//TestKey--
	//TestKey222

private:
	QMap<QString, YZAzzXgg>  m_mapAzzXgg;

	//bool m_bFlagCraft = false;
	//QList<YZCraft> m_crafts;
};
