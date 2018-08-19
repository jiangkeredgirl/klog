#pragma once

#include <QWidget>
#include "logdisplayui.h"
#include "logfile.h"
#include "cstandard.h"
#include "logfilterbar.h"

class LogDisplay : public QWidget
{
	Q_OBJECT

public:
	LogDisplay(QWidget *parent);
	~LogDisplay();


public slots:
	void SlotReceiveTrace(shared_ptr<TraceEntry> trace_entry, LogFileStatus status);
	void SlotCheckStateChanged(QTreeWidgetItem *item, int column);
	void SlotCheckDisplayChange(vector<string> names, Qt::CheckState state);
	void SlotLevelChange(const string& level, Qt::CheckState state);
	void SlotHeadChange(const string& head, Qt::CheckState state);
	void SlotFilter(FilterCondition filter_condition);

protected:
	virtual void paintEvent(QPaintEvent *) override;

private:
	int SetCellText(int col, const string& text);
	int AddNames(shared_ptr<TraceEntry> trace_entry);
	QTreeWidgetItem* AddItem(QTreeWidgetItem* parentItem, const string& name);
	bool IsTopItem(QTreeWidgetItem* item);
	void SetChildCheckState(QTreeWidgetItem *item, Qt::CheckState state);
	void SetParentCheckState(QTreeWidgetItem *item);
	bool CheckHide(int row);
	bool CheckNameHide(vector<string> trace_names);
	bool CheckNameHide(vector<string> trace_names, QTreeWidgetItem* item);
	bool CheckLevelHide(int level);
	bool CheckFilterHide(int fun_time, const string& date_time);

private:
	LogDisplayui m_ui;
	map<int, QColor>  m_color_log_level;
	int               m_cur_row = 0;
	QColor            m_cur_row_color;
	QTreeWidgetItem*  m_tree_cur_item = nullptr;
	map<string, Qt::CheckState>	m_level_state;
	FilterCondition   m_filter_condition;
};
