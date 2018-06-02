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
	void setupUi(QMainWindow* hostWidget);

public:
	QMainWindow*  m_hostWidget = nullptr;
	QVBoxLayout*  m_mainLayout = nullptr;

};
