#include "SisRecevice.h"

#include <QIcon>
#include <QCoreApplication>


SisRecevice::SisRecevice(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	setWindowIcon(QIcon(QString("%1%2").arg(QCoreApplication::applicationDirPath()).arg("/logo.ico")));

}
