#include "logdisplay.h"
#include "kutility.h"

LogDisplay::LogDisplay(QWidget *parent)
	: QWidget(parent)
{
	m_ui.setupUi(this);
	m_color_log_level[TRACE_TRACk]    = QColor(0, 0, 0);
	m_color_log_level[TRACE_ERROR]    = QColor(255, 0, 0);
	m_color_log_level[TRACE_WARNING]  = QColor(255, 201, 14);
	m_color_log_level[TRACE_OK]       = QColor(0, 255, 0);
	m_color_log_level[TRACE_NOTICE]   = QColor(0, 255, 255);
	m_color_log_level[TRACE_INFO]     = QColor(0, 0, 0);
	m_color_log_level[TRACE_DEBUG]    = QColor(0, 0, 0);
	m_color_log_level[TRACE_TEMP]     = QColor(0, 0, 0);

}

LogDisplay::~LogDisplay()
{
}

int LogDisplay::ClearTrace()
{
	m_ui.m_tableLogInfo->clearContents();
	m_ui.m_tableLogInfo->setRowCount(0);
	return 0;
}

int LogDisplay::SlotAddTrace(shared_ptr<TraceEntry> trace_entry)
{
	if (m_color_log_level.count(trace_entry->level))
	{
		m_color_row = m_color_log_level[trace_entry->level];
	}
	else
	{
		m_color_row = QColor(0, 0, 0);
	}
	int rowCount = m_ui.m_tableLogInfo->rowCount();
	m_ui.m_tableLogInfo->setRowCount(rowCount + 1);
	SetCellText(rowCount, 0, to_string(trace_entry->index));
	if (!trace_entry->func_track.empty())
	{
		SetCellText(rowCount, 1, trace_entry->func_track);
		if (trace_entry->func_track == "<<")
		{
			SetCellText(rowCount, 2, to_string(trace_entry->func_time) + "ms");
		}
	}
	SetCellText(rowCount, 3, LogFile::instance().LevelToStr(trace_entry->level));
	SetCellText(rowCount, 4, trace_entry->label);
	SetCellText(rowCount, 5, trace_entry->thread_id);
	SetCellText(rowCount, 6, trace_entry->process_name);
	SetCellText(rowCount, 7, trace_entry->module_name);
	SetCellText(rowCount, 8, trace_entry->file_name);
	SetCellText(rowCount, 9, trace_entry->func_name);
	SetCellText(rowCount, 10, to_string(trace_entry->line));
	SetCellText(rowCount, 11, kk::Utility::GetDateTimeStr(trace_entry->datetime));
	SetCellText(rowCount, 12, kk::Utility::GetRunTimeStr(trace_entry->runtime));
	SetCellText(rowCount, 13, trace_entry->async ? "true" : "false");
	SetCellText(rowCount, 14, trace_entry->sync_lock ? "true" : "false");
	SetCellText(rowCount, 15, trace_entry->content);
	m_ui.m_tableLogInfo->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
	m_ui.m_tableLogInfo->verticalHeader()->resizeSections(QHeaderView::ResizeToContents);
	m_ui.m_tableLogInfo->scrollToBottom();
	return 0;
}

int LogDisplay::SetCellText(int row, int col, const string& text)
{
#if 1
	QLabel *label = new QLabel(text.c_str());
	label->setAlignment(Qt::AlignCenter);
	label->setContentsMargins(3, 0, 3, 0);
	label->setStyleSheet("color:"+ m_color_row.name());
	m_ui.m_tableLogInfo->setCellWidget(row, col, label);
#else
	m_ui.m_tableLogInfo->setItem(row, col, new QTableWidgetItem(text.c_str()));
#endif
	return 0;
}

void LogDisplay::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}