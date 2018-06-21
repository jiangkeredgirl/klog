#pragma once

#include <QObject>
#include "qtstandard.h"

class LogDisplayui : public QObject
{
	Q_OBJECT

public:
	LogDisplayui();
	~LogDisplayui();

public:
	void setupUi(QWidget* hostWidget);

public:
	QWidget*  m_hostWidget = nullptr;
	QTableWidget* m_tableLogInfo = nullptr;
};
