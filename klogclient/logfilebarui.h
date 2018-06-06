#pragma once

#include <QObject>
#include "qtstandard.h"

class LogFileBarui : public QObject
{
	Q_OBJECT

public:
	LogFileBarui();
	~LogFileBarui();

public:
	void setupUi(QWidget* hostWidget);

public:
	QWidget*  m_hostWidget = nullptr;
	QPushButton* m_buttonLocalFile = nullptr;
	QLabel* m_labelFileName = nullptr;
};
