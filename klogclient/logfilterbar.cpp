#include "logfilterbar.h"

LogFilterBar::LogFilterBar(QWidget *parent)
	: QWidget(parent)
{
	m_ui.setupUi(this);
}

LogFilterBar::~LogFilterBar()
{
}

void LogFilterBar::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}