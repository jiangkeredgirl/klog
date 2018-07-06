#include "logheadbarui.h"
#include "cstandard.h"

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
		m_hostWidget->setStyleSheet("LogHeadBar{border:1px solid red;}");

		QHBoxLayout* layout = new QHBoxLayout;
		m_hostWidget->setLayout(layout);
		layout->setContentsMargins(1, 0, 0, 0);
		layout->setSpacing(10);

		QLabel* labelTag = new QLabel;
		labelTag->setText(tr("log head"));
		layout->addWidget(labelTag);
		labelTag->setStyleSheet("QLabel{border:1px solid red;}");
			
		vector<string> checkTags = {
			"head",
			"index",
			"functrack",
			"functime",
			"level",
			"label",
			"threadid",
			"processname",
			"modulename",
			"filename",
			"funcname",
			"line",
			"datetime",
			"runtime",
			"async",
			"synclock",
		};
		for (auto item : checkTags)
		{
			QCheckBox* checkBox = new QCheckBox(m_hostWidget);
			checkBox->setText(tr(item.c_str()));
			layout->addWidget(checkBox);
			checkBox->setChecked(true);
			checkBox->setStyleSheet("QCheckBox{border:1px solid red; padding:4px;}");
		}

		layout->addStretch();
	}
}