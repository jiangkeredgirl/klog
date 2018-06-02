#include "loglevelbarui.h"

LogLevelBarui::LogLevelBarui()
{
}

LogLevelBarui::~LogLevelBarui()
{
}

void LogLevelBarui::setupUi(QWidget* hostWidget)
{
	m_hostWidget = hostWidget;
	if (m_hostWidget)
	{
		m_hostWidget->setFixedHeight(26);
		m_hostWidget->setStyleSheet("LogLevelBar{border: 1px solid red; }");

		QHBoxLayout* layout = new QHBoxLayout;
		m_hostWidget->setLayout(layout);
		layout->setContentsMargins(1, 0, 0, 0);
		layout->setSpacing(1);

		QLabel* labelTag = new QLabel;
		labelTag->setText(tr("log level"));
		layout->addWidget(labelTag);
	}
}