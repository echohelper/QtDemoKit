#pragma once

#include <QWidget>
#include <QString>

class QLineEdit;
class DetailWidgetUI;

struct YZAzzXgg;

//
class AzzXggCreate : public QWidget
{
	Q_OBJECT

public:
	AzzXggCreate(QWidget *parent = Q_NULLPTR);
	~AzzXggCreate();

	void initData(const QString &azzxggId = QString());

signals:
	void azzxggCreated(const YZAzzXgg &azzxgg);
	void azzxggChanged(const YZAzzXgg &azzxgg);

private:
	void setupUi();
	void loadData();
	void testOK();
	void onOK();
	
	//文件内字段测试
	//void TestKeyAaa();
	//void TestKeyBbb(QString &str);
	//TestKeyCcc
	//TestKey222
	//TestKey--
	//TestKey222

private:
	QString m_strAzzXggId;

	DetailWidgetUI *ui = nullptr;
	
	QLineEdit *m_lineEditName = nullptr;
};
