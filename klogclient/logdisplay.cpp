﻿#include "logdisplay.h"
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
	connect(m_ui.m_treeSourceNames, &QTreeWidget::itemChanged, this, &LogDisplay::SlotCheckStateChanged);
}

LogDisplay::~LogDisplay()
{
}


int LogDisplay::SlotAddTrace(shared_ptr<TraceEntry> trace_entry, LogFileStatus status)
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
			m_color_row = m_color_log_level[trace_entry->level];
		}
		else
		{
			m_color_row = QColor(0, 0, 0);
		}
		int rowCount = m_ui.m_tableLogInfo->rowCount();
		m_ui.m_tableLogInfo->insertRow(rowCount);
		if (hide)
		{
			m_ui.m_tableLogInfo->hideRow(rowCount);
		}
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
		SetCellText(rowCount, 5, to_string(trace_entry->thread_id));
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
		m_ui.m_tableLogInfo->resizeRowToContents(rowCount);
		m_ui.m_tableLogInfo->scrollToBottom();
	}
	else if (status == LogFileStatus::LogFileReadEnd)
	{
		//m_ui.m_tableLogInfo->resizeRowsToContents();
		m_ui.m_tableLogInfo->resizeColumnsToContents();
	}
	return 0;
}

int LogDisplay::SetCellText(int row, int col, const string& text)
{
#if 0
	QLabel *label = new QLabel(text.c_str());
	label->setAlignment(Qt::AlignCenter);
	label->setContentsMargins(3, 0, 3, 0);
	label->setStyleSheet("color:"+ m_color_row.name());
	m_ui.m_tableLogInfo->setCellWidget(row, col, label);
#else
	QTableWidgetItem* item = new QTableWidgetItem(text.c_str());
	item->setTextColor(m_color_row);
	m_ui.m_tableLogInfo->setItem(row, col, item);
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
		if (m_ui.m_treeSourceNames->topLevelItem(processItemIndex)->text(0).toStdString() == trace_entry->process_name)
		{
			break;
		}
	}
	if (processItemIndex == processCount)
	{
		QTreeWidgetItem* pItem = new QTreeWidgetItem();
		pItem->setText(0, trace_entry->process_name.c_str());
		pItem->setCheckState(0, Qt::Checked);
		m_ui.m_treeSourceNames->addTopLevelItem(pItem);
	}
	///	模块名
	QTreeWidgetItem* moduleItem = AddItem(m_ui.m_treeSourceNames->topLevelItem(processItemIndex), trace_entry->module_name);
	///	文件名
	QTreeWidgetItem* fileItem = AddItem(moduleItem, trace_entry->file_name);
	///	函数名
	QTreeWidgetItem* funcItem = AddItem(fileItem, trace_entry->func_name);
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
		size_t i = 0;
		for (i = 0; i < m_ui.m_treeSourceNames->topLevelItemCount(); i++)
		{
			if (m_ui.m_treeSourceNames->topLevelItem(i)->text(0).toStdString() == trace_entry->process_name)
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
			names[0] = trace_entry->module_name;
			names[1] = trace_entry->file_name;
			names[2] = trace_entry->func_name;
			hide = CheckHide(names, topItem);
			break;
		}
	} while (false);
	return hide;
}

bool LogDisplay::CheckHide(vector<string> names, QTreeWidgetItem* item)
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
			hide = CheckHide(names, childItem);
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