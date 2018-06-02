#include "loglevelbar.h"

LogLevelBar::LogLevelBar(QWidget *parent)
	: QWidget(parent)
{
	m_ui.setupUi(this);
}

LogLevelBar::~LogLevelBar()
{
}

void LogLevelBar::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}