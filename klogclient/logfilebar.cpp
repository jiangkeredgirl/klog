﻿#include "logfilebar.h"
#include "kutility.h"

LogFileBar::LogFileBar(QWidget *parent)
	: QWidget(parent)
{
	m_ui.setupUi(this);
	connect(m_ui.m_buttonLocalFile, &QPushButton::clicked, this, &LogFileBar::SlotButtonLocalFile);
	connect(m_ui.m_buttonConnect, &QPushButton::clicked, this, &LogFileBar::SlotButtonRemoteMessage);
}

LogFileBar::~LogFileBar()
{
}

void LogFileBar::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void LogFileBar::SlotButtonLocalFile()
{
	QString	defultLogDir = QDir::currentPath();
	if (!m_ui.m_labelFileName->text().isEmpty())
	{
		defultLogDir = kk::Utility::GetDirectoryName(m_ui.m_labelFileName->text().toStdString()).c_str();
	}
	QString logFilePath = QFileDialog::getOpenFileName(this, tr(u8"本地log文件"), defultLogDir, "*.log");
	if (!logFilePath.isEmpty())
	{
		m_ui.m_labelFileName->setText(logFilePath);
		m_ui.m_labelFileName->setToolTip(logFilePath);
		emit SignalOpenLocalLogFile(logFilePath.toStdString());
	}
}

void LogFileBar::SlotButtonRemoteMessage()
{
	if (!m_ui.m_editIP->text().isEmpty() && !m_ui.m_editPort->text().isEmpty())
	{
		emit SignalOpenRemoteLogMessage(m_ui.m_editIP->text().toStdString(), m_ui.m_editPort->text().toInt());
	}
}