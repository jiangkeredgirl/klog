#pragma once

#include <QObject>
#include "qtstandard.h"

class Klogclientui : public QObject
{
	Q_OBJECT

public:
	Klogclientui();
	~Klogclientui();

public:
	void setupUi(QMainWindow* myselfWidget);

public:
	QMainWindow*  m_myselfWidget = nullptr;
	QVBoxLayout*  m_mainLayout = nullptr;

};
