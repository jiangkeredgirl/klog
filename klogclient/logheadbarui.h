#pragma once

#include <QObject>
#include "qtstandard.h"

class LogHeadBarui : public QObject
{
	Q_OBJECT

public:
	LogHeadBarui();
	~LogHeadBarui();

public:
	void setupUi(QWidget* hostWidget);

public:
	QWidget*  m_hostWidget = nullptr;
};
