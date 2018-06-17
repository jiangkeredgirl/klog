#include "klogclient.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	KlogClient w;
	w.show();
	return a.exec();
}
