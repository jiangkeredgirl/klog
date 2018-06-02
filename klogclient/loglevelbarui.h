#pragma once

#include <QObject>
#include "qtstandard.h"

class LogLevelBarui : public QObject
{
	Q_OBJECT

public:
	LogLevelBarui();
	~LogLevelBarui();

public:
	void setupUi(QWidget* myselfWidget);

public:
	QWidget*  m_myselfWidget = nullptr;

};
