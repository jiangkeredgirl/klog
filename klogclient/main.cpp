#include "klogclient.h"
#include <QtWidgets/QApplication>
#include "kloglib.h"

int main(int argc, char *argv[])
{
	//CreateConsole;
	GenerateDump;
	TrackCout;	
	QApplication a(argc, argv);
	KlogClient w;
	w.show();
	return a.exec();
	WaitTrace;
}
