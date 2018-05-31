#include "klogclient.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	klogclient w;
	w.show();
	return a.exec();
}
