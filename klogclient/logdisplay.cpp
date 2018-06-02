#include "logdisplay.h"

LogDisplay::LogDisplay(QWidget *parent)
	: QWidget(parent)
{
	m_ui.setupUi(this);
}

LogDisplay::~LogDisplay()
{
}

void LogDisplay::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}