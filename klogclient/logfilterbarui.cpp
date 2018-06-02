#include "logfilterbarui.h"

LogFilterBarui::LogFilterBarui()
{
}

LogFilterBarui::~LogFilterBarui()
{
}

void LogFilterBarui::setupUi(QWidget* hostWidget)
{
	m_hostWidget = hostWidget;
	if (m_hostWidget)
	{
		m_hostWidget->setFixedHeight(26);
		m_hostWidget->setStyleSheet("LogFilterBar{border:1px solid red;}");

		QHBoxLayout* layout = new QHBoxLayout;
		m_hostWidget->setLayout(layout);
		layout->setContentsMargins(1, 0, 0, 0);
		layout->setSpacing(1);

		QLabel* labelTag = new QLabel;
		labelTag->setText(tr("log filter"));
		layout->addWidget(labelTag);
	}
}