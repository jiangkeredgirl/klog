#include "logheadbar.h"

LogHeadBar::LogHeadBar(QWidget *parent)
	: QWidget(parent)
{
	m_ui.setupUi(this);
	for (size_t i = 0; i < m_ui.m_checkboxs.size(); i++)
	{
		connect(m_ui.m_checkboxs[i], &QCheckBox::stateChanged, this, &LogHeadBar::SlotStateChanged);
	}
}

LogHeadBar::~LogHeadBar()
{
}

void LogHeadBar::SlotStateChanged(int state)
{
	QCheckBox* check = qobject_cast<QCheckBox*>(sender());
	emit SignalStateChanged(check->text().toStdString(), static_cast<Qt::CheckState>(state));
}

void LogHeadBar::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}