#include "FastCreator.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	FastCreator w;
	w.show();
	return a.exec();
}
