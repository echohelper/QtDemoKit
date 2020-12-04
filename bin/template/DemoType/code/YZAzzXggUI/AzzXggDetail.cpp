#pragma execution_character_set("utf-8")
#include "AzzXggDetail.h"
#include "YZAzzXggUtils.h"

#include <QPushButton>

#include <YZPublicFun/YZGlobalSetting.h>
#include <YZCommonCtrl/QElidedLabel.h>
#include <YZCommonCtrl/DetailWidgetUI.h>
#include <YZCommonCtrl/YZProgressBar.h>
#include <YZAzzXggData/YZAzzXggData.h>
#include <YZAzzXggData/YZAzzXggHeader.h>


	
	//文件内字段测试
	//void TestKeyAaa();
	//void TestKeyBbb(QString &str);
	//TestKeyCcc
	//TestKey222
	//TestKey--
	//TestKey222

AzzXggDetail::AzzXggDetail(QWidget *parent)
	: QWidget(parent)
{
	setWindowTitle(tr("XXXX详情"));

	setupUi();

	QPushButton *btnModify = ui->addButton(tr("修改"));
	connect(btnModify, &QPushButton::clicked, this, &AzzXggDetail::onModify);
	ui->btnOK->setText(tr("删除"));
	connect(ui->btnOK, &QPushButton::clicked, this, &AzzXggDetail::onDelete);
	connect(ui->btnCancel, &QPushButton::clicked, this, &AzzXggDetail::close);
}

AzzXggDetail::~AzzXggDetail()
{
	delete ui;
}

void AzzXggDetail::initData(const QString &azzxggId)
{
	m_strAzzXggId = azzxggId;
	YZProgressBarAuto progressBar(NULL, RoundBar);
	YZAzzXgg azzxgg;
	YZAzzXggDataPtr()->getAzzXgg(azzxggId, azzxgg);

	m_labelName->setText(azzxgg.name);

	//
}

QString AzzXggDetail::getAzzXggId() const
{
	return m_strAzzXggId;
}

void AzzXggDetail::setupUi()
{
	ui = new DetailWidgetUI();
	ui->setupUi(this);

	m_labelName = new QElidedLabel();
	ui->addLineWidget(tr("姓名"), m_labelName);

	//

	ui->addStretch();
}

void AzzXggDetail::onModify()
{
	emit modifyAzzXgg(getAzzXggId());
}

void AzzXggDetail::onDelete()
{
	emit deleteAzzXgg(getAzzXggId());
}
