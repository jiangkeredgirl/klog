#pragma once

#include <QObject>
#include "qtstandard.h"

class KlogClientui : public QObject
{
	Q_OBJECT

public:
	KlogClientui();
	~KlogClientui();

public:
	void setupUi(QMainWindow* hostWidget);

public:
	QMainWindow*  m_hostWidget = nullptr;
	QVBoxLayout*  m_mainLayout = nullptr;

};
