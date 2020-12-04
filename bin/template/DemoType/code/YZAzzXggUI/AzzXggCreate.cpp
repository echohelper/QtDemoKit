#pragma execution_character_set("utf-8")
#include "AzzXggCreate.h"

#include <QLineEdit>
#include <QPushButton>

#include <YZPublicFun/YZGlobalSetting.h>
#include <YZCommonCtrl/DetailWidgetUI.h>
#include <YZCommonCtrl/YZProgressBar.h>
#include <YZCommonCtrl/YZMessageBox.h>
#include <YZAzzXggData/YZAzzXggHeader.h>
#include <YZAzzXggData/YZAzzXggData.h>

AzzXggCreate::AzzXggCreate(QWidget *parent)
	: QWidget(parent)
{
	setWindowTitle(tr("XXXX"));

	setAttribute(Qt::WA_DeleteOnClose, true);
	setWindowModality(Qt::ApplicationModal);

	setupUi();

	connect(ui->btnOK, &QPushButton::clicked, this, &AzzXggCreate::onOK);
	connect(ui->btnCancel, &QPushButton::clicked, this, &AzzXggCreate::close);
	
	//文件内字段测试
	//void TestKeyAaa();
	//void TestKeyBbb(QString &str);
	//TestKeyCcc
	//TestKey222
	//TestKey--
	//TestKey222

}

AzzXggCreate::~AzzXggCreate()
{
	delete ui;
}

void AzzXggCreate::initData(const QString &azzxggId)
{
	m_strAzzXggId = azzxggId;
	YZProgressBarAuto progressBar(NULL, RoundBar);

	//

	loadData();
}

void AzzXggCreate::setupUi()
{
	ui = new DetailWidgetUI();
	ui->setupUi(this);

	m_lineEditName = new QLineEdit();
	ui->addLineWidget(tr("姓名"), m_lineEditName, true);
	connect(m_lineEditName, &QLineEdit::textChanged, this, &AzzXggCreate::testOK);
	//

	ui->addStretch();

	ui->btnOK->setEnabled(false);
}

void AzzXggCreate::testOK()
{
	bool bEnabled(true);

	QString name = m_lineEditName->text();
	bEnabled &= !name.isEmpty();

	ui->btnOK->setEnabled(bEnabled);
}

void AzzXggCreate::loadData()
{
	if (m_strAzzXggId.isEmpty())
	{
		return;
	}

	YZProgressBarAuto progressBar(NULL, RoundBar);
	YZAzzXgg azzxgg;
	YZAzzXggDataPtr()->getAzzXgg(m_strAzzXggId, azzxgg);

	m_lineEditName->setText(azzxgg.name);

	//

	testOK();
}

void AzzXggCreate::onOK()
{
	YZProgressBarAuto progressBar(NULL, RoundBar, m_strAzzXggId.isEmpty() ? ProgressCreate : ProgressUpdate);

	YZAzzXgg azzxgg;
	azzxgg.name = m_lineEditName->text();

	//

	if (m_strAzzXggId.isEmpty())//新增
	{
		if (!YZAzzXggDataPtr()->createAzzXgg(azzxgg))
		{
			YZMessageBox::information(tr("添加XXXX失败"));
			return;
		}

		progressBar.stopProgressBar();

		emit azzxggCreated(azzxgg);
	}
	else//编辑、更新
	{
		azzxgg._id = m_strAzzXggId;
		if (!YZAzzXggDataPtr()->updateAzzXgg(azzxgg))
		{
			YZMessageBox::information(tr("更新信息失败"));
			return;
		}

		progressBar.stopProgressBar();

		emit azzxggChanged(azzxgg);
	}

	close();
}