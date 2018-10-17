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
	QLineEdit* m_editExecuteTime = nullptr;
	QLineEdit* m_editLogBeginTime = nullptr;
	QLineEdit* m_editLogEndTime = nullptr;
	QPushButton* m_buttonFilter = nullptr;
	QCheckBox* m_checkBoxAbortFun = nullptr;
};
