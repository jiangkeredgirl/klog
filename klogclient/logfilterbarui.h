#pragma once

#include <QObject>
#include "qtstandard.h"

class LogFilterBarui : public QObject
{
	Q_OBJECT

public:
	LogFilterBarui();
	~LogFilterBarui();

public:
	void setupUi(QWidget* hostWidget);

public:
	QWidget*  m_hostWidget = nullptr;
};
