#include "logfilebar.h"

LogFileBar::LogFileBar(QWidget *parent)
	: QWidget(parent)
{
	m_ui.setupUi(this);
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