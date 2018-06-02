#include "logheadbarui.h"

LogHeadBarui::LogHeadBarui()
{
}

LogHeadBarui::~LogHeadBarui()
{
}

void LogHeadBarui::setupUi(QWidget* hostWidget)
{
	m_hostWidget = hostWidget;
	if (m_hostWidget)
	{
		m_hostWidget->setFixedHeight(26);
		m_hostWidget->setStyleSheet("LogHeadBar{border: 1px solid red; }");

		QHBoxLayout* layout = new QHBoxLayout;
		m_hostWidget->setLayout(layout);
		layout->setContentsMargins(1, 0, 0, 0);
		layout->setSpacing(1);

		QLabel* labelTag = new QLabel;
		labelTag->setText(tr("log head"));
		layout->addWidget(labelTag);
	}
}