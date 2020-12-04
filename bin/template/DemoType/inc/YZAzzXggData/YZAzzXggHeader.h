#pragma once
#include <YZPrimaryData/YZCondition.h>
#include <YZPrimaryData/YZPicture.h>
#include <YZPrimaryData/YZDocumentLite.h>

	//文件内字段测试
	//void TestKeyAaa();
	//void TestKeyBbb(QString &str);
	//TestKeyCcc
	//TestKey222
	//TestKey--
	//TestKey222


//XXXX
struct YZAzzXgg
{
	QString _id;
	QString qrCode;//二维码链接

	QString name;//姓名
	QString ID;//身份证号
	QString unitId;//单位id
	QString craftId;//工种id
	QString checkRuleId;//考勤规则
	QString number;//工号
	QString card;//考勤卡号
	QString place;//籍贯
	QString address;//地址
	QString level;//学历
	QString remark;//备注

	enum SexType{ Male = 1, Female = 2};
	SexType sex = SexType::Male;

	enum StatusType { Inservice = 1,/*在职*/ Dimission = 2,/*离职*/ };
	StatusType status = StatusType::Inservice;

	int age = 0;//年龄
	int workLife = 0;//工作年限
	QDateTime enterDate;//进场日期

	YZPicture avatar;//头像
	QStringList documentIds;//附件
	QList<YZDocumentLite> documents;

	QDateTime createdAt;
	QString createdBy;

	QDateTime updatedAt;
	QString updatedBy;
};

struct YZAzzXggCondition : public BaseQueryCondition
{
	bool bAllCraft = true;
	QStringList craftIds;
	bool bAllUnit = true;
	QStringList unitIds;
	bool bAllStatus = true;
	QList<int> status;

	QString getConditionJson() const
	{
		QJsonObject jsonObject;

		if (!anyTime)
		{
			jsonObject.insert("updatedAt", getDateTimeObject());
		}

		if (!keyWords.isEmpty())
		{
			jsonObject.insert("name", getKeywordObject());
		}

		if (!bAllCraft)
		{
			jsonObject.insert("craftId", getIdListObject(craftIds));
		}

		if (!bAllUnit)
		{
			jsonObject.insert("unitId", getIdListObject(unitIds));
		}

		if (!bAllStatus)
		{
			jsonObject.insert("status", getIntListObject(status));
		}

		QJsonDocument jsonDocument(jsonObject);
		QString strCondition(jsonDocument.toJson(QJsonDocument::Compact));
		return strCondition;
	}
};