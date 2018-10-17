#include "logsearchbar_ui.h"

LogSearchBarui::LogSearchBarui()
{
}

LogSearchBarui::~LogSearchBarui()
{
}

void LogSearchBarui::setupUi(QWidget* hostWidget)
{
	m_hostWidget = hostWidget;
	if (m_hostWidget)
	{
		m_hostWidget->setFixedHeight(26);
		m_hostWidget->setStyleSheet("LogSearchBar{border:1px solid red;}");

		QHBoxLayout* layout = new QHBoxLayout;
		m_hostWidget->setLayout(layout);
		layout->setContentsMargins(1, 0, 0, 0);
		layout->setSpacing(10);

		QLabel* labelTag = new QLabel;
		labelTag->setText(tr("log search"));
		layout->addWidget(labelTag);
		labelTag->setStyleSheet("QLabel{border:1px solid red;}");

		QLabel* labelLogKeywordTag = new QLabel;
		labelLogKeywordTag->setText(tr(u8"log关键词"));
		layout->addWidget(labelLogKeywordTag);
		labelLogKeywordTag->setStyleSheet("QLabel{border:1px solid red; padding:0px;}");

		QLineEdit* editLogKeyword = new QLineEdit;
		editLogKeyword->setPlaceholderText(tr(""));
		layout->addWidget(editLogKeyword);
		editLogKeyword->setStyleSheet("QLineEdit{border:1px solid red; padding:4px;}");
		editLogKeyword->setFixedWidth(150);

		layout->addStretch();
	}
}