#include "SisSend.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SisSend w;
	w.show();
	return a.exec();
}
