#include "SisRecevice.h"

#include <QIcon>
#include <QCoreApplication>


SisRecevice::SisRecevice(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	setWindowIcon(QIcon(QString("%1%2").arg(QCoreApplication::applicationDirPath()).arg("/logo.ico")));

	connect(ui.pushButton, &QPushButton::clicked, this, &SisRecevice::on_pushButton_clicked);
	connect(ui.pushButton_2, &QPushButton::clicked, this, &SisRecevice::on_pushButton_2_clicked);
}

void SisRecevice::on_pushButton_clicked()
{
	char c[100];
	//int rel = read(STDIN_FILENO,c,100);
	ui.textEdit->setText(c);
}

void SisRecevice::on_pushButton_2_clicked()
{
	ui.textEdit->setText("aaaa");
}

bool SisRecevice::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
	MSG *param = static_cast<MSG *>(message);

	switch (param->message)
	{
	case WM_COPYDATA:
	{
		COPYDATASTRUCT *cds = reinterpret_cast<COPYDATASTRUCT*>(param->lParam);
		if (cds->dwData == CUSTOM_TYPE)
		{
			QString strMessage = QString::fromUtf8(reinterpret_cast<char*>(cds->lpData), cds->cbData);
			ui.textEdit->setText(strMessage);
			*result = 1;
			return true;
		}
	}
	}

	return QWidget::nativeEvent(eventType, message, result);
}
