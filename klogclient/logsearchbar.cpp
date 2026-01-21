#include "logsearchbar.h"

LogSearchBar::LogSearchBar(QWidget *parent)
	: QWidget(parent)
{
	m_ui.setupUi(this);
}

LogSearchBar::~LogSearchBar()
{
}

void LogSearchBar::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	//opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}