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
	m_level_state["trace_track"] = Qt::CheckState::Checked;
	m_level_state["trace_error"] = Qt::CheckState::Checked;
	m_level_state["trace_warning"] = Qt::CheckState::Checked;
	m_level_state["trace_ok"] = Qt::CheckState::Checked;
	m_level_state["trace_notice"] = Qt::CheckState::Checked;
	m_level_state["trace_info"] = Qt::CheckState::Checked;
	m_level_state["trace_debug"] = Qt::CheckState::Checked;
	m_level_state["trace_temp"] = Qt::CheckState::Checked;
	m_level_state["trace_customer"] = Qt::CheckState::Checked;
	connect(m_ui.m_treeSourceNames, &QTreeWidget::itemChanged, this, &LogDisplay::SlotCheckStateChanged);
}

LogDisplay::~LogDisplay()
{
}


void LogDisplay::SlotAddTrace(shared_ptr<TraceEntry> trace_entry, LogFileStatus status)
{
	if (status == LogFileStatus::LogFileReadBegin)
	{
		m_ui.m_tableLogInfo->clearContents();
		m_ui.m_tableLogInfo->setRowCount(0);
		m_ui.m_treeSourceNames->clear();
	}
	else if (status == LogFileStatus::LogFileReading && trace_entry)
	{
		AddNames(trace_entry);
		bool hide = CheckHide(trace_entry);
		if (m_color_log_level.count(trace_entry->level))
		{
			m_cur_row_color = m_color_log_level[trace_entry->level];
		}
		else
		{
			m_cur_row_color = QColor(0, 0, 0);
		}
		m_cur_row = m_ui.m_tableLogInfo->rowCount();
		m_ui.m_tableLogInfo->insertRow(m_cur_row);
		if (hide)
		{
			m_ui.m_tableLogInfo->hideRow(m_cur_row);
		}
		SetCellText(0, to_string(trace_entry->index));
		if (!trace_entry->functrack.empty())
		{
			SetCellText(1, trace_entry->functrack);
			if (trace_entry->functrack == "<<")
			{
				SetCellText(2, to_string(trace_entry->functime) + "ms");
			}
		}
		SetCellText(3, LogFile::instance().LevelToStr(trace_entry->level));
		SetCellText(4, trace_entry->label);
		SetCellText(5, to_string(trace_entry->threadid));
		SetCellText(6, trace_entry->processname);
		SetCellText(7, trace_entry->modulename);
		SetCellText(8, trace_entry->filename);
		SetCellText(9, trace_entry->funcname);
		SetCellText(10, to_string(trace_entry->line));
		SetCellText(11, kk::Utility::GetDateTimeStr(trace_entry->datetime));
		SetCellText(12, kk::Utility::GetRunTimeStr(trace_entry->runtime));
		SetCellText(13, trace_entry->async ? "true" : "false");
		SetCellText(14, trace_entry->synclock ? "true" : "false");
		SetCellText(15, trace_entry->content);
		m_ui.m_tableLogInfo->resizeRowToContents(m_cur_row);
		m_ui.m_tableLogInfo->scrollToBottom();
	}
	else if (status == LogFileStatus::LogFileReadEnd)
	{
		//m_ui.m_tableLogInfo->resizeRowsToContents();
		m_ui.m_tableLogInfo->resizeColumnsToContents();
	}
}

int LogDisplay::SetCellText(int col, const string& text)
{
#if 0
	QLabel *label = new QLabel(text.c_str());
	label->setAlignment(Qt::AlignCenter);
	label->setContentsMargins(3, 0, 3, 0);
	label->setStyleSheet("color:"+ m_color_row.name());
	m_ui.m_tableLogInfo->setCellWidget(row, col, label);
#else
	QTableWidgetItem* item = new QTableWidgetItem(text.c_str());
	item->setTextColor(m_cur_row_color);
	m_ui.m_tableLogInfo->setItem(m_cur_row, col, item);
#endif
	return 0;
}

int LogDisplay::AddNames(shared_ptr<TraceEntry> trace_entry)
{
	/// 进程名
	int processCount = m_ui.m_treeSourceNames->topLevelItemCount();
	int processItemIndex = 0;
	for (processItemIndex = 0; processItemIndex < processCount; processItemIndex++)
	{
		if (m_ui.m_treeSourceNames->topLevelItem(processItemIndex)->text(0).toStdString() == trace_entry->processname)
		{
			break;
		}
	}
	if (processItemIndex == processCount)
	{
		QTreeWidgetItem* pItem = new QTreeWidgetItem();
		pItem->setText(0, trace_entry->processname.c_str());
		pItem->setCheckState(0, Qt::Checked);
		m_ui.m_treeSourceNames->addTopLevelItem(pItem);
	}
	///	模块名
	QTreeWidgetItem* moduleItem = AddItem(m_ui.m_treeSourceNames->topLevelItem(processItemIndex), trace_entry->modulename);
	///	文件名
	QTreeWidgetItem* fileItem = AddItem(moduleItem, trace_entry->filename);
	///	函数名
	QTreeWidgetItem* funcItem = AddItem(fileItem, trace_entry->funcname);
	return 0;
}

QTreeWidgetItem* LogDisplay::AddItem(QTreeWidgetItem* parentItem, const string& name)
{
	int childIndex = 0;
	for (childIndex = 0; childIndex < parentItem->childCount(); childIndex++)
	{
		if (parentItem->child(childIndex)->text(0).toStdString() == name)
		{
			break;
		}
	}
	if (childIndex == parentItem->childCount())
	{
		QTreeWidgetItem* pItem = new QTreeWidgetItem();
		pItem->setText(0, name.c_str());
		pItem->setCheckState(0, Qt::Checked);
		parentItem->addChild(pItem);
		m_ui.m_treeSourceNames->resizeColumnToContents(0);
	}
	return parentItem->child(childIndex);
}

void LogDisplay::SlotCheckStateChanged(QTreeWidgetItem *item, int column)
{
	disconnect(m_ui.m_treeSourceNames, &QTreeWidget::itemChanged, this, &LogDisplay::SlotCheckStateChanged);
	if (item)
	{
		SetChildCheckState(item, item->checkState(column));
		if (!IsTopItem(item))
		{
			SetParentCheckState(item->parent());
		}
		if (m_tree_cur_item)
		{
			m_tree_cur_item->setTextColor(0, qRgb(0, 0, 0));
		}
		m_tree_cur_item = item;
		m_tree_cur_item->setTextColor(0, qRgb(255, 0, 0));
		Qt::CheckState state = item->checkState(column);
		vector<string> check_names;
		do
		{
			check_names.insert(check_names.begin(), item->text(0).toStdString());
			item = item->parent();
		} while (item);
		SlotCheckDisplayChange(check_names, state);
	}
	connect(m_ui.m_treeSourceNames, &QTreeWidget::itemChanged, this, &LogDisplay::SlotCheckStateChanged);
}

void LogDisplay::SlotCheckDisplayChange(vector<string> names, Qt::CheckState state)
{
	if ((names.size() > 0) && (names.size() < 5))
	{
		for (size_t i = 0; i < m_ui.m_tableLogInfo->rowCount(); i++)
		{
			size_t j = 0;
			for (j = 0; j < names.size(); j++)
			{
				if (m_ui.m_tableLogInfo->item(i, 6 + j)->text().toStdString() != names[j])
				{
					break;
				}
			}
			if (j == names.size())
			{
				if (state == Qt::CheckState::Checked)
				{
					m_ui.m_tableLogInfo->showRow(i);
				}
				else if (state == Qt::CheckState::Unchecked)
				{
					m_ui.m_tableLogInfo->hideRow(i);
				}
			}
		}
	}
}

void LogDisplay::SlotLevelChange(const string& level, Qt::CheckState state)
{
	m_level_state[("trace_" + level)] = state;
	for (size_t i = 0; i < m_ui.m_tableLogInfo->rowCount(); i++)
	{
		if (("trace_" + level) == m_ui.m_tableLogInfo->item(i, 3)->text().toStdString())
		{
			if (state == Qt::CheckState::Checked)
			{
				m_ui.m_tableLogInfo->showRow(i);
			}
			else if (state == Qt::CheckState::Unchecked)
			{
				m_ui.m_tableLogInfo->hideRow(i);
			}
		}
	}
}

void LogDisplay::SlotHeadChange(const string& head, Qt::CheckState state)
{
	if (head == "head")
	{
		for (size_t i = 0; i < m_ui.m_tableLogInfo->horizontalHeader()->count() - 1; i++)
		{
			if (state == Qt::CheckState::Checked)
			{
				m_ui.m_tableLogInfo->showColumn(i);
			}
			else if (state == Qt::CheckState::Unchecked)
			{
				m_ui.m_tableLogInfo->hideColumn(i);
			}
		}
	}
	else
	{
		for (size_t i = 0; i < m_ui.m_tableLogInfo->horizontalHeader()->count() - 1; i++)
		{
			if (head == m_ui.m_tableLogInfo->horizontalHeaderItem(i)->text().toStdString())
			{
				if (state == Qt::CheckState::Checked)
				{
					m_ui.m_tableLogInfo->showColumn(i);
				}
				else if (state == Qt::CheckState::Unchecked)
				{
					m_ui.m_tableLogInfo->hideColumn(i);
				}
				break;
			}
		}
	}
}

void LogDisplay::SlotFilter(FilterCondition filter_condition)
{
	if (filter_condition.func_time != m_filter_condition.func_time
		|| filter_condition.datetime_begin != m_filter_condition.datetime_begin
		|| filter_condition.datetime_end != m_filter_condition.datetime_end)
	{
		m_filter_condition = filter_condition;
		for (size_t i = 0; i < m_ui.m_tableLogInfo->rowCount(); i++)
		{
			//if (m_filter_condition.func_time <= m_ui.m_tableLogInfo->item(i, 2)->text().toInt())
			//{
			//	if (state == Qt::CheckState::Checked)
			//	{
			//		m_ui.m_tableLogInfo->showRow(i);
			//	}
			//	else if (state == Qt::CheckState::Unchecked)
			//	{
			//		m_ui.m_tableLogInfo->hideRow(i);
			//	}
			//}
		}
	}
	
}

bool LogDisplay::IsTopItem(QTreeWidgetItem* item)
{
	if (!item)
	{
		return false;
	}
	if (item->parent())
	{
		return false;
	}
	return true;
}

void LogDisplay::SetChildCheckState(QTreeWidgetItem *item, Qt::CheckState state)
{
	if (item)
	{
		for (int i = 0; i < item->childCount(); i++)
		{
			QTreeWidgetItem* child = item->child(i);
			if (child->checkState(0) != state)
			{
				child->setCheckState(0, state);
				SetChildCheckState(child, state);
			}
		}
	}
}

void LogDisplay::SetParentCheckState(QTreeWidgetItem *item)
{
	if (item)
	{
		Qt::CheckState childState;
		do
		{
			int i = 0;
			for (i = 0; i < item->childCount(); i++)
			{
				QTreeWidgetItem* child = item->child(i);
				if (child->checkState(0) != Qt::Checked)
				{
					break;
				}
			}
			if (i == item->childCount())
			{
				childState = Qt::Checked;
				break;
			}
			for (i = 0; i < item->childCount(); i++)
			{
				QTreeWidgetItem* child = item->child(i);
				if (child->checkState(0) != Qt::Unchecked)
				{
					break;
				}
			}
			if (i == item->childCount())
			{
				childState = Qt::Unchecked;
				break;
			}
			childState = Qt::PartiallyChecked;
		} while (false);
		item->setCheckState(0, childState);
		SetParentCheckState(item->parent());
	}
}

bool LogDisplay::CheckHide(shared_ptr<TraceEntry> trace_entry)
{
	bool hide = false;
	do
	{
		if (trace_entry == nullptr)
		{
			hide = true;
			break;
		}
		hide = CheckLevelHide(trace_entry->level);
		if (hide)
		{
			break;
		}
		size_t i = 0;
		for (i = 0; i < m_ui.m_treeSourceNames->topLevelItemCount(); i++)
		{
			if (m_ui.m_treeSourceNames->topLevelItem(i)->text(0).toStdString() == trace_entry->processname)
			{
				break;
			}
		}
		if (i == m_ui.m_treeSourceNames->topLevelItemCount())
		{
			break;
		}
		QTreeWidgetItem* topItem = m_ui.m_treeSourceNames->topLevelItem(i);
		if (topItem->checkState(0) == Qt::Checked)
		{
			break;
		}
		if (topItem->checkState(0) == Qt::Unchecked)
		{
			hide = true;
			break;
		}
		if (topItem->checkState(0) == Qt::PartiallyChecked)
		{
			vector<string> names;
			names.resize(3);
			names[0] = trace_entry->modulename;
			names[1] = trace_entry->filename;
			names[2] = trace_entry->funcname;
			hide = CheckNameHide(names, topItem);
			break;
		}
	} while (false);
	return hide;
}

bool LogDisplay::CheckNameHide(vector<string> names, QTreeWidgetItem* item)
{
	bool hide = false;
	do
	{
		if (names.empty())
		{ 
			break;
		}
		if (item == nullptr)
		{
			break;
		}
		size_t i = 0;
		for (i = 0; i < item->childCount(); i++)
		{
			if (item->child(i)->text(0).toStdString() == names[0])
			{
				break;
			}
		}
		if (i == item->childCount())
		{
			break;
		}
		QTreeWidgetItem* childItem = item->child(i);
		if (childItem->checkState(0) == Qt::Checked)
		{
			break;
		}
		if (childItem->checkState(0) == Qt::Unchecked)
		{
			hide = true;
			break;
		}
		if (childItem->checkState(0) == Qt::PartiallyChecked)
		{
			names.erase(names.begin());
			hide = CheckNameHide(names, childItem);
			break;
		}
	} while (false);
	return hide;
}

bool LogDisplay::CheckLevelHide(int level)
{
	bool hide = false;
	string strlevel = LogFile::instance().LevelToStr(level);
	if (m_level_state.count(strlevel))
	{
		if (m_level_state[strlevel] == Qt::CheckState::Checked)
		{
			hide = false;
		}
		else if (m_level_state[strlevel] == Qt::CheckState::Unchecked)
		{
			hide = true;
		}
	}
	return hide;
}

bool LogDisplay::CheckFilterHide(shared_ptr<TraceEntry> trace_entry)
{
	bool hide = false;
	do
	{
		if (trace_entry->functime < m_filter_condition.func_time)
		{
			hide = true;
			break;
		}
		if (kk::Utility::GetDateTimeStr(trace_entry->datetime) < m_filter_condition.datetime_begin
			|| kk::Utility::GetDateTimeStr(trace_entry->datetime) > m_filter_condition.datetime_end)
		{
			hide = true;
			break;
		}
	} while (false);

	return hide;
}

void LogDisplay::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}