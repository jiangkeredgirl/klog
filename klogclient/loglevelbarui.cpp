#include "loglevelbarui.h"
#include "cstandard.h"

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
		m_hostWidget->setStyleSheet("LogLevelBar{border:1px solid red;}");

		QHBoxLayout* layout = new QHBoxLayout;
		m_hostWidget->setLayout(layout);
		layout->setContentsMargins(1, 0, 0, 0);
		layout->setSpacing(10);

		QLabel* labelTag = new QLabel(m_hostWidget);
		labelTag->setText(tr("log level"));
		layout->addWidget(labelTag);
		labelTag->setStyleSheet("QLabel{border:1px solid red;}");

		vector<string> checkTags = {
			"track",
			"error",
			"warning",
			"ok",
			"notice",
			"info",
			"debug",
			"temp",
			"customer"
		};
		for (auto item : checkTags)
		{
			QCheckBox* checkBox = new QCheckBox(m_hostWidget);
			checkBox->setText(tr(item.c_str()));
			layout->addWidget(checkBox);
			checkBox->setChecked(true);
			m_checkboxs.push_back(checkBox);
			checkBox->setStyleSheet("QCheckBox{border:1px solid red; padding:4px;}");
		}

		layout->addStretch();
	}
}