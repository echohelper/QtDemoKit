#include "ToolTemplate.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ToolTemplate w;
	w.show();
	return a.exec();
}
