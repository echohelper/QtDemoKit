#include "UuidHelper.h"

#include <QIcon>
#include <QCoreApplication>
#include <QUuid>


UuidHelper::UuidHelper(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	setWindowIcon(QIcon(QString("%1%2").arg(QCoreApplication::applicationDirPath()).arg("/logo.ico")));

	connect(ui.btnCopy, &QPushButton::clicked, this, &UuidHelper::onBtnCopy);
	connect(ui.btnSave, &QPushButton::clicked, this, &UuidHelper::onBtnSave);
	connect(ui.btnClear, &QPushButton::clicked, this, &UuidHelper::onBtnClear);
	connect(ui.btnGenerate, &QPushButton::clicked, this, &UuidHelper::onBtnGenerate);

	init();
}

void UuidHelper::initData()
{

}

void UuidHelper::init()
{
	ui.cbxFormat->addItem("Without Braces", FormatType::WithoutBraces);
	ui.cbxFormat->addItem("In Braces", FormatType::InBraces);
	ui.cbxFormat->addItem("In Parentheses", FormatType::InParentheses);
	ui.cbxFormat->addItem("Pure Hex Upper", FormatType::PureHexUpper);
	ui.cbxFormat->addItem("Pure Hex Lower", FormatType::PureHexLower);
	ui.cbxFormat->setCurrentIndex(0);
}

void UuidHelper::generateGuid()
{
	FormatType type = (FormatType)(ui.cbxFormat->currentData().toInt());

	int iCount = 0;
	iCount = ui.sbxCount->value();
	for (int i = 0; i < iCount; ++i)
		ui.textBrowser->append(getGuid(type));

	ui.textBrowser->append("");
}

QString UuidHelper::getGuid(FormatType type)
{
	QString strUuid;
	QUuid uuid = QUuid::createUuid();

	switch (type)
	{
	case UuidHelper::WithoutBraces:
	{
		strUuid = uuid.toString();
		strUuid.remove("{");
		strUuid.remove("}");
	}break;
	case UuidHelper::InBraces:
	{
		strUuid = uuid.toString();
	}break;
	case UuidHelper::InParentheses:
	{
		strUuid = uuid.toString();
		strUuid.replace("{", "(");
		strUuid.replace("}", ")");
	}break;
	case UuidHelper::PureHexUpper:
	{
		strUuid = uuid.toString();
		strUuid.remove("{");
		strUuid.remove("}");
		strUuid.remove("-");
		strUuid = strUuid.toUpper();
	}break;
	case UuidHelper::PureHexLower:
	{
		strUuid = uuid.toString();
		strUuid.remove("{");
		strUuid.remove("}");
		strUuid.remove("-");
		strUuid = strUuid.toLower();
	}break;
	default:
		break;
	}

	return strUuid;
}

void UuidHelper::onBtnCopy()
{
	statusBar()->showMessage("Copyed", 3000);
}

void UuidHelper::onBtnSave()
{
}

void UuidHelper::onBtnClear()
{
	ui.textBrowser->clear();
}

void UuidHelper::onBtnGenerate()
{
	generateGuid();
}
