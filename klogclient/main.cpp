#include "stdafx.h"
#include "klogclient.h"
#include <QtWidgets/QApplication>
#include "kloglib.h"

int main(int argc, char *argv[])
{
	KlogCreateStdout;
	KlogGenerateDump;
	KlogTrackCout;
	QApplication a(argc, argv);
	KlogClient w;
	w.show();
	return a.exec();
	KlogWaitAsyncEnd;
}
