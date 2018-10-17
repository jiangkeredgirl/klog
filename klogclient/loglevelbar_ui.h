#pragma once

#include <QObject>
#include "qtstandard.h"
#include "cstandard.h"

class LogLevelBarui : public QObject
{
	Q_OBJECT

public:
	LogLevelBarui();
	~LogLevelBarui();

public:
	void setupUi(QWidget* hostWidget);

public:
	QWidget*  m_hostWidget = nullptr;
	vector<QCheckBox*> m_checkboxs;

};
