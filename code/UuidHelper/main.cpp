#include "UuidHelper.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	UuidHelper w;
	w.show();
	return a.exec();
}
