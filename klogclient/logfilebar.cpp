#include "logfilebar.h"
#include "kutility.h"

LogFileBar::LogFileBar(QWidget *parent)
	: QWidget(parent)
{
	m_ui.setupUi(this);
	connect(m_ui.m_buttonLocalFile, &QPushButton::clicked, this, &LogFileBar::SlotButtonLocalFile);
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
	m_ui.m_labelFileName->setText(logFilePath);
}