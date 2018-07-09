#include "logfilterbar.h"

LogFilterBar::LogFilterBar(QWidget *parent)
	: QWidget(parent)
{
	m_ui.setupUi(this);
	connect(m_ui.m_buttonFilter, &QPushButton::clicked, this, &LogFilterBar::SlotButtonFilter);
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

void LogFilterBar::SlotButtonFilter()
{
	if (!m_ui.m_editExecuteTime->text().isEmpty()
		|| (!m_ui.m_editLogBeginTime->text().isEmpty() && !m_ui.m_editLogEndTime->text().isEmpty()))
	{
		FilterCondition filter_condition;
		filter_condition.func_time = m_ui.m_editExecuteTime->text().toInt();
		filter_condition.datetime_begin = m_ui.m_editLogBeginTime->text().toStdString();
		filter_condition.datetime_end = m_ui.m_editLogEndTime->text().toStdString();
		emit SignalFilter(filter_condition);
	}
}