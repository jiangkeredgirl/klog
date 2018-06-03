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
		m_hostWidget->setStyleSheet("LogFileBar{border:1px solid red;}");

		QHBoxLayout* layout = new QHBoxLayout;
		m_hostWidget->setLayout(layout);
		layout->setContentsMargins(1, 0, 0, 0);
		layout->setSpacing(10);

		QLabel* labelTag = new QLabel;
		labelTag->setText(tr("log file"));
		layout->addWidget(labelTag);
		labelTag->setStyleSheet("QLabel{border:1px solid red; padding:0px;}");

		QPushButton* buttonLocalFile = new QPushButton;
		buttonLocalFile->setText(tr(u8"本地log文件..."));
		layout->addWidget(buttonLocalFile);
		buttonLocalFile->setStyleSheet("QPushButton{border:1px solid red; padding:4px;}");

		QLabel* labelFileName = new QLabel;
		labelFileName->setText(tr("log file path"));
		layout->addWidget(labelFileName);
		labelFileName->setStyleSheet("QLabel{border:1px solid red; padding:0px;}");
		labelFileName->setDisabled(true);

		layout->addSpacing(10);

		QLabel* labelIPTag = new QLabel;
		labelIPTag->setText(tr("ip"));
		layout->addWidget(labelIPTag);
		labelIPTag->setStyleSheet("QLabel{border:1px solid red; padding:0px;}");

		QLineEdit* editIP = new QLineEdit;
		editIP->setPlaceholderText(tr("ip"));
		layout->addWidget(editIP);
		editIP->setStyleSheet("QLineEdit{border:1px solid red; padding:4px;}");
		editIP->setFixedWidth(150);

		QLabel* labelPortTag = new QLabel;
		labelPortTag->setText(tr("port"));
		layout->addWidget(labelPortTag);
		labelPortTag->setStyleSheet("QLabel{border:1px solid red; padding:0px;}");

		QLineEdit* editPort = new QLineEdit;
		editPort->setPlaceholderText(tr("port"));
		layout->addWidget(editPort);
		editPort->setStyleSheet("QLineEdit{border:1px solid red; padding:4px;}");
		editPort->setFixedWidth(100);

		QPushButton* buttonConnect = new QPushButton;
		buttonConnect->setText(tr(u8"连接"));
		layout->addWidget(buttonConnect);
		buttonConnect->setStyleSheet("QPushButton{border:1px solid red; padding:4px;}");	

		layout->addStretch();
	}
}