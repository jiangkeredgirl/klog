#include "logfilterbar_ui.h"

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
#if 0
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
#endif
		QLabel* labelExecuteTimeTag = new QLabel;
		labelExecuteTimeTag->setText(tr(u8"执行时间>="));
		layout->addWidget(labelExecuteTimeTag);
		labelExecuteTimeTag->setStyleSheet("QLabel{border:1px solid red; padding:0px;}");

		layout->addSpacing(-9);

		m_editExecuteTime = new QLineEdit;
		m_editExecuteTime->setPlaceholderText(tr(""));
		layout->addWidget(m_editExecuteTime);
		m_editExecuteTime->setStyleSheet("QLineEdit{border:1px solid red; padding:4px;}");
		m_editExecuteTime->setFixedWidth(150);

		layout->addSpacing(-9);

		QLabel* labelExecuteTimeTagEnd = new QLabel;
		labelExecuteTimeTagEnd->setText(tr(u8"毫秒的函数"));
		layout->addWidget(labelExecuteTimeTagEnd);
		labelExecuteTimeTagEnd->setStyleSheet("QLabel{border:1px solid red; padding:0px;}");

		layout->addSpacing(10);

		QLabel* labelLogTimeTag = new QLabel;
		labelLogTimeTag->setText(tr(u8"log时间"));
		layout->addWidget(labelLogTimeTag);
		labelLogTimeTag->setStyleSheet("QLabel{border:1px solid red; padding:0px;}");

		m_editLogBeginTime = new QLineEdit;
		m_editLogBeginTime->setPlaceholderText(tr(""));
		layout->addWidget(m_editLogBeginTime);
		m_editLogBeginTime->setStyleSheet("QLineEdit{border:1px solid red; padding:4px;}");
		m_editLogBeginTime->setFixedWidth(150);
		m_editLogBeginTime->setPlaceholderText("yyyy-MM-dd_hh-mm-ss");
		//QRegExp rx("[0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9] [0-9][0-9]\:[0-9][0-9]\:[0-9][0-9]");
		//QRegExpValidator* ipValidator = new QRegExpValidator(rx, this);
		//editLogBeginTime->setValidator(ipValidator);

		QLabel* labelToTag = new QLabel;
		labelToTag->setText(tr(u8"到"));
		layout->addWidget(labelToTag);
		labelToTag->setStyleSheet("QLabel{border:1px solid red; padding:0px;}");

		m_editLogEndTime = new QLineEdit;
		m_editLogEndTime->setPlaceholderText(tr(""));
		layout->addWidget(m_editLogEndTime);
		m_editLogEndTime->setStyleSheet("QLineEdit{border:1px solid red; padding:4px;}");
		m_editLogEndTime->setFixedWidth(150);
		m_editLogEndTime->setPlaceholderText("yyyy-MM-dd_hh-mm-ss");
		//editLogEndTime->setValidator(ipValidator);

		m_buttonFilter = new QPushButton;
		m_buttonFilter->setText(tr(u8"确认"));
		layout->addWidget(m_buttonFilter);
		m_buttonFilter->setStyleSheet("QPushButton{border:1px solid red; padding:4px;}");

		m_checkBoxAbortFun = new QCheckBox;
		m_checkBoxAbortFun->setText(tr(u8"crash的函数"));
		layout->addWidget(m_checkBoxAbortFun);
		m_checkBoxAbortFun->setChecked(false);
		m_checkBoxAbortFun->setStyleSheet("QCheckBox{border:1px solid red; padding:4px;}");

		layout->addStretch();
	}
}