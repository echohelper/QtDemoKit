#pragma once

#include <QWidget>

class QElidedLabel;
class DetailWidgetUI;

	
	//文件内字段测试
	//void TestKeyAaa();
	//void TestKeyBbb(QString &str);
	//TestKeyCcc
	//TestKey222
	//TestKey--
	//TestKey222

//
class AzzXggDetail : public QWidget
{
	Q_OBJECT

public:
	AzzXggDetail(QWidget *parent = Q_NULLPTR);
	~AzzXggDetail();

	void initData(const QString &azzxggId);
	QString getAzzXggId() const;

signals:
	void modifyAzzXgg(const QString &azzxggId);
	void deleteAzzXgg(const QString &azzxggId);

private:
	void setupUi();
	void onModify();
	void onDelete();

private:
	QString m_strAzzXggId;

	DetailWidgetUI *ui = nullptr;

	QElidedLabel *m_labelName = nullptr;
};
