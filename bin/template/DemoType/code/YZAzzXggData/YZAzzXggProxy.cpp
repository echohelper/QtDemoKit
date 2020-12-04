#include "YZAzzXggProxy.h"

#include <YZNetwork\NetworkHelper.h>
#include <YZNetwork\YZBaseProxy.h>
#include <YZAzzXggData\YZAzzXggHeader.h>

#define AzzXggServiceApi (BaseApiUrl + "personnel-service/")

	
	//文件内字段测试
	//void TestKeyAaa();
	//void TestKeyBbb(QString &str);
	//TestKeyCcc
	//TestKey222
	//TestKey--
	//TestKey222

bool YZAzzXggProxy::createAzzXgg(YZAzzXgg &azzxgg)
{
	QJsonObject jsonObject;
	azzxggToJsonObject(azzxgg, jsonObject);
	
	QString strUrl = AzzXggServiceApi + "azzxggs";

	WAIT_REPLY_POST_JSON(strUrl, jsonObject);

	jsonObject = loop.object();
	jsonObjectToAzzXgg(jsonObject, azzxgg);

	return loop.isSuccessful();
}

bool YZAzzXggProxy::deleteAzzXgg(const QString &azzxggId)
{
	QString strUrl = AzzXggServiceApi + "azzxggs/%1";
	strUrl = strUrl.arg(azzxggId);

	WAIT_REPLY_DELETE(strUrl);

	return loop.isSuccessful();
}

bool YZAzzXggProxy::updateAzzXgg(const YZAzzXgg &azzxggOld, YZAzzXgg &azzxgg)
{
	QJsonObject jsonObjectOld;
	azzxggToJsonObject(azzxggOld, jsonObjectOld);

	QJsonObject jsonObject;
	azzxggToJsonObject(azzxgg, jsonObject);

	SimplifyUpdateJson(jsonObjectOld, jsonObject);

	if (jsonObject.isEmpty())
	{
		return true;
	}

	QString strUrl = AzzXggServiceApi + "azzxggs/%1";
	strUrl = strUrl.arg(azzxgg._id);

	WAIT_REPLY_PUT_JSON(strUrl, jsonObject);

	jsonObject = loop.object();
	jsonObjectToAzzXgg(jsonObject, azzxgg);

	return loop.isSuccessful();
}

bool YZAzzXggProxy::getAzzXggRangeCount(const YZAzzXggCondition &condition, int &count)
{
	QString strUrl = AzzXggServiceApi + "projects/%1/azzxggs?where=%2&only_count=true";
	strUrl = strUrl.arg(CurrentProjectId).arg(condition.getConditionJson());

	WAIT_REPLY_GET(strUrl);

	count = GetRangeCount(loop.object());

	return loop.isSuccessful();
}

bool YZAzzXggProxy::getAzzXggRangeData(const YZAzzXggCondition &condition, int skip, int limit, QList<YZAzzXgg> &azzxggs)
{
	QString strUrl = AzzXggServiceApi + "projects/%1/azzxggs?where=%2&skip=%3&limit=%4";
	strUrl = strUrl.arg(CurrentProjectId).arg(condition.getConditionJson()).arg(skip).arg(limit);

	WAIT_REPLY_GET(strUrl);

	QJsonObjectList objectList = loop.objectList();
	for (const QJsonObject &jsonObject : objectList)
	{
		YZAzzXgg azzxgg;
		jsonObjectToAzzXgg(jsonObject, azzxgg);
		azzxggs.append(azzxgg);
	}
	return loop.isSuccessful();
}

bool YZAzzXggProxy::getAzzXgg(const QString &azzxggId, YZAzzXgg &azzxgg)
{
	QString strUrl = AzzXggServiceApi + "azzxggs/%1";
	strUrl = strUrl.arg(azzxggId);

	WAIT_REPLY_GET(strUrl);

	QJsonObject jsonObject = loop.object();
	jsonObjectToAzzXgg(jsonObject, azzxgg);

	return loop.isSuccessful();
}

void YZAzzXggProxy::azzxggToJsonObject(const YZAzzXgg &azzxgg, QJsonObject &jsonObject)
{
	jsonObject.insert("projectId", ObjectIdValue(CurrentProjectId));

	jsonObject.insert("name", azzxgg.name);
	jsonObject.insert("ID", azzxgg.ID);

	//
}

void YZAzzXggProxy::jsonObjectToAzzXgg(const QJsonObject &jsonObject, YZAzzXgg &azzxgg)
{
	azzxgg._id = jsonObject.value("_id").toString();
	azzxgg.name = jsonObject.value("name").toString();

	//

	azzxgg.createdAt = ParseDateTime(jsonObject.value("createdAt"));
	azzxgg.createdBy = jsonObject.value("createdBy").toString();

	azzxgg.updatedAt = ParseDateTime(jsonObject.value("updatedAt"));
	azzxgg.updatedBy = jsonObject.value("updatedBy").toString();
}

//bool YZAzzXggProxy::getCraft(QList<YZCraft> &crafts)
//{
//	QString strUrl = AzzXggServiceApi + "projects/%1/crafts";
//	strUrl = strUrl.arg(CurrentProjectId);
//
//	WAIT_REPLY_GET(strUrl);
//
//	QJsonObjectList objectList = loop.objectList();
//	for (const QJsonObject &jsonObject : objectList)
//	{
//		YZCraft craft;
//		jsonObjectToCraft(jsonObject, craft);
//		crafts.append(craft);
//	}
//
//	return loop.isSuccessful();
//}
//
//void YZAzzXggProxy::jsonObjectToCraft(const QJsonObject &jsonObject, YZCraft &craft)
//{
//	craft._id = jsonObject.value("_id").toString();
//	craft.name = jsonObject.value("name").toString();
//}