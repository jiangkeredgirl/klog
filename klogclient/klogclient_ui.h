#pragma once

#include <QObject>
#include "qstandard.h"

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
