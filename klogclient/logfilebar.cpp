#include "logfilebar.h"

LogFileBar::LogFileBar(QWidget *parent)
	: QWidget(parent)
{
	m_ui.setupUi(this);
	connect(m_ui.m_buttonLocalFile, &QPushButton::clicked, this
		, [this]() { this->HandleButtonLocalFile(); });
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

void LogFileBar::HandleButtonLocalFile()
{
	QString logFilePath = QFileDialog::getOpenFileName(this, tr(u8"本地log文件"), QDir::currentPath(), "*.log");
	m_ui.m_labelFileName->setText(logFilePath);
}