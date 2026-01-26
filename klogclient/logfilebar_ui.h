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
	QLabel* m_labelFileName = nullptr;
	QPushButton* m_buttonLocalFile = nullptr;
	QLineEdit* m_editIP = nullptr;
	QLineEdit* m_editControlPort = nullptr;
	QLineEdit* m_editSyncTracePort = nullptr;
	QLineEdit* m_editAsyncTracePort = nullptr;
	QPushButton* m_buttonConnect = nullptr;
};
