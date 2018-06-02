#include "logfilebarui.h"

LogFileBarui::LogFileBarui()
{
}

LogFileBarui::~LogFileBarui()
{
}

void LogFileBarui::setupUi(QWidget* hostWidget)
{
	m_hostWidget = hostWidget;
	if (m_hostWidget)
	{
		m_hostWidget->setFixedHeight(26);
		m_hostWidget->setStyleSheet("LogFileBar{border: 1px solid red;}");

		QHBoxLayout* layout = new QHBoxLayout;
		m_hostWidget->setLayout(layout);
		layout->setContentsMargins(1, 0, 0, 0);
		layout->setSpacing(10);

		QLabel* labelTag = new QLabel;
		labelTag->setText(tr("log file"));
		layout->addWidget(labelTag);
		labelTag->setStyleSheet("QLabel{border: 1px solid red;}");

		QPushButton* localFileButton = new QPushButton;
		localFileButton->setText(tr(u8"本地log文件..."));
		layout->addWidget(localFileButton);
		localFileButton->setStyleSheet("QPushButton{border: 1px solid red;}");

		layout->addStretch();
	}
}