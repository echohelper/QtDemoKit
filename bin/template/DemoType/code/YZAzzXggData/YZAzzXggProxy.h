#pragma once

#include <QList>

class QJsonObject;

struct YZCraft;
struct YZAzzXgg;
struct YZAzzXggCondition;


	
	//文件内字段测试
	//void TestKeyAaa();
	//void TestKeyBbb(QString &str);
	//TestKeyCcc
	//TestKey222
	//TestKey--
	//TestKey222

namespace YZAzzXggProxy
{
	bool createAzzXgg(YZAzzXgg &azzxgg);
	bool deleteAzzXgg(const QString &azzxggId);
	bool updateAzzXgg(const YZAzzXgg &azzxggOld, YZAzzXgg &azzxgg);
	bool getAzzXggRangeCount(const YZAzzXggCondition &condition, int &count);
	bool getAzzXggRangeData(const YZAzzXggCondition &condition, int skip, int limit, QList<YZAzzXgg> &azzxggs);
	bool getAzzXgg(const QString &azzxggId, YZAzzXgg &azzxgg);
	void azzxggToJsonObject(const YZAzzXgg &azzxgg, QJsonObject &jsonObject);
	void jsonObjectToAzzXgg(const QJsonObject &jsonObject, YZAzzXgg &azzxgg);

	//bool getCraft(QList<YZCraft> &crafts);
	//void jsonObjectToCraft(const QJsonObject &jsonObject, YZCraft &craft);
};