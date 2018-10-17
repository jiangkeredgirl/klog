#pragma once

#include <QObject>
#include "qtstandard.h"

class LogSearchBarui : public QObject
{
	Q_OBJECT

public:
	LogSearchBarui();
	~LogSearchBarui();

public:
	void setupUi(QWidget* hostWidget);

public:
	QWidget*  m_hostWidget = nullptr;
};
