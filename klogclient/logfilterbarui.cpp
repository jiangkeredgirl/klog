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
		layout->setSpacing(10);

		QLabel* labelTag = new QLabel;
		labelTag->setText(tr("log filter"));
		layout->addWidget(labelTag);
		labelTag->setStyleSheet("QLabel{border:1px solid red; padding:0px;}");

		QLabel* labelOnlyShowTag = new QLabel;
		labelOnlyShowTag->setText(tr(u8"只显示"));
		layout->addWidget(labelOnlyShowTag);
		labelOnlyShowTag->setStyleSheet("QLabel{border:1px solid red; padding:0px;}");

		QLineEdit* editOnlyShow = new QLineEdit;
		editOnlyShow->setPlaceholderText(tr(""));
		layout->addWidget(editOnlyShow);
		editOnlyShow->setStyleSheet("QLineEdit{border:1px solid red; padding:4px;}");
		editOnlyShow->setFixedWidth(150);

		QLabel* labelNotShowTag = new QLabel;
		labelNotShowTag->setText(tr(u8"不显示"));
		layout->addWidget(labelNotShowTag);
		labelNotShowTag->setStyleSheet("QLabel{border:1px solid red; padding:0px;}");

		QLineEdit* editNotShow = new QLineEdit;
		editNotShow->setPlaceholderText(tr(""));
		layout->addWidget(editNotShow);
		editNotShow->setStyleSheet("QLineEdit{border:1px solid red; padding:4px;}");
		editNotShow->setFixedWidth(150);

		QLabel* labelExecuteTimeTag = new QLabel;
		labelExecuteTimeTag->setText(tr(u8"执行时间大于（毫秒)"));
		layout->addWidget(labelExecuteTimeTag);
		labelExecuteTimeTag->setStyleSheet("QLabel{border:1px solid red; padding:0px;}");

		QLineEdit* editExecuteTime = new QLineEdit;
		editExecuteTime->setPlaceholderText(tr(""));
		layout->addWidget(editExecuteTime);
		editExecuteTime->setStyleSheet("QLineEdit{border:1px solid red; padding:4px;}");
		editExecuteTime->setFixedWidth(150);

		layout->addStretch();
	}
}