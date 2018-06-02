#include "logdisplayui.h"

LogDisplayui::LogDisplayui()
{
}

LogDisplayui::~LogDisplayui()
{
}

void LogDisplayui::setupUi(QWidget* hostWidget)
{
	m_hostWidget = hostWidget;
	if (m_hostWidget)
	{
		m_hostWidget->setStyleSheet("LogDisplay{border:1px solid red;}");
	}
}