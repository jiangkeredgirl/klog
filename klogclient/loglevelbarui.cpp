#include "loglevelbarui.h"

LogLevelBarui::LogLevelBarui()
{
}

LogLevelBarui::~LogLevelBarui()
{
}

void LogLevelBarui::setupUi(QWidget* myselfWidget)
{
	m_myselfWidget = myselfWidget;
	if (m_myselfWidget)
	{
		m_myselfWidget->setStyleSheet("LogLevelBar{border: 1px solid red; }");
	}
}