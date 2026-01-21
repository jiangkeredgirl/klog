#include "stdafx.h"
#include "logfilebar_ui.h"

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

		m_buttonLocalFile = new QPushButton;
		m_buttonLocalFile->setText(tr(u8"本地log文件..."));
		layout->addWidget(m_buttonLocalFile);
		m_buttonLocalFile->setStyleSheet("QPushButton{border:1px solid red; padding:4px;}");

		m_labelFileName = new QLabel;
		m_labelFileName->setText(tr("log file path"));
		layout->addWidget(m_labelFileName);
		m_labelFileName->setStyleSheet("QLabel{border:1px solid red; padding:0px;}");
		m_labelFileName->setDisabled(true);
		m_labelFileName->setMaximumWidth(600);
		m_labelFileName->setAlignment(Qt::AlignRight);

		layout->addSpacing(10);

		QLabel* labelIPTag = new QLabel;
		labelIPTag->setText(tr("ip"));
		layout->addWidget(labelIPTag);
		labelIPTag->setStyleSheet("QLabel{border:1px solid red; padding:0px;}");

		m_editIP = new QLineEdit;
		m_editIP->setPlaceholderText("127.0.0.1");
		layout->addWidget(m_editIP);
		m_editIP->setStyleSheet("QLineEdit{border:1px solid red; padding:4px;}");
		m_editIP->setFixedWidth(150);
		//editIP->setInputMask("000.000.000.000");
		QRegularExpression  rx("^((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)$");
		QRegularExpressionValidator* ipValidator = new QRegularExpressionValidator(rx, this);
		m_editIP->setValidator(ipValidator);

		QLabel* labelPortTag = new QLabel;
		labelPortTag->setText(tr("port"));
		layout->addWidget(labelPortTag);
		labelPortTag->setStyleSheet("QLabel{border:1px solid red; padding:0px;}");

		m_editPort = new QLineEdit;
		m_editPort->setPlaceholderText(tr("port"));
		layout->addWidget(m_editPort);
		m_editPort->setStyleSheet("QLineEdit{border:1px solid red; padding:4px;}");
		m_editPort->setFixedWidth(100);

		m_buttonConnect = new QPushButton;
		m_buttonConnect->setText(tr(u8"连接"));
		layout->addWidget(m_buttonConnect);
		m_buttonConnect->setStyleSheet("QPushButton{border:1px solid red; padding:4px;}");

		layout->addStretch();
	}
}