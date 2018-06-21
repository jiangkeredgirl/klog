#include "logdisplay.h"

LogDisplay::LogDisplay(QWidget *parent)
	: QWidget(parent)
{
	m_ui.setupUi(this);
}

LogDisplay::~LogDisplay()
{
}

int LogDisplay::SlotAddTrace(shared_ptr<TraceEntry> trace_entry)
{
	int currentRow = m_ui.m_tableLogInfo->rowCount();	
	m_ui.m_tableLogInfo->setRowCount(++currentRow);
	SetCellText(currentRow - 1, 5, trace_entry->content);
	return 0;
}

int LogDisplay::SetCellText(int row, int col, const string& text)
{
	QLabel *label = new QLabel(text.c_str());
	m_ui.m_tableLogInfo->setCellWidget(row, col, label);
	return 0;
}

void LogDisplay::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}