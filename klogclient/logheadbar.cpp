#include "logheadbar.h"

LogHeadBar::LogHeadBar(QWidget *parent)
	: QWidget(parent)
{
	m_ui.setupUi(this);
}

LogHeadBar::~LogHeadBar()
{
}

void LogHeadBar::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}