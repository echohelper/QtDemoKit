#include "SisRecevice.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SisRecevice w;
	w.show();
	return a.exec();
}
