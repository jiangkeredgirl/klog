#include "logdisplay.h"
#include "kutility.h"

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
	int rowCount = m_ui.m_tableLogInfo->rowCount();
	m_ui.m_tableLogInfo->setRowCount(rowCount + 1);

	SetCellText(rowCount, 0, trace_entry->func_track);
	SetCellText(rowCount, 1, to_string(trace_entry->function_time) + "ms");
	SetCellText(rowCount, 2, to_string(trace_entry->index));
	SetCellText(rowCount, 3, to_string(trace_entry->level));
	SetCellText(rowCount, 4, trace_entry->label);
	SetCellText(rowCount, 5, trace_entry->thread_id);
	SetCellText(rowCount, 6, kk::Utility::GetDateTimeStr(trace_entry->datetime));
	SetCellText(rowCount, 7, kk::Utility::GetRunTimeStr(trace_entry->runtime));
	SetCellText(rowCount, 8, trace_entry->process_name);
	SetCellText(rowCount, 9, trace_entry->module_name);
	SetCellText(rowCount, 10, trace_entry->file_name);
	SetCellText(rowCount, 11, trace_entry->function_name);
	SetCellText(rowCount, 12, to_string(trace_entry->line));
	SetCellText(rowCount, 13, trace_entry->async ? "true" : "false");
	SetCellText(rowCount, 14, trace_entry->sync_lock ? "true" : "false");
	SetCellText(rowCount, 15, trace_entry->content);
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