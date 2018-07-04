#pragma once

#include <QWidget>
#include "logdisplayui.h"
#include "logfile.h"
#include "cstandard.h"

class LogDisplay : public QWidget
{
	Q_OBJECT

public:
	LogDisplay(QWidget *parent);
	~LogDisplay();


public slots:
	int SlotAddTrace(shared_ptr<TraceEntry> trace_entry, LogFileStatus status);
	void SlotCheckStateChanged(QTreeWidgetItem *item, int column);
	void SlotCheckDisplayChange(vector<string> names, Qt::CheckState state);

protected:
	virtual void paintEvent(QPaintEvent *) override;

private:
	int SetCellText(int row, int col, const string& text);
	int AddNames(shared_ptr<TraceEntry> trace_entry);
	QTreeWidgetItem* AddItem(QTreeWidgetItem* parentItem, const string& name);
	bool IsTopItem(QTreeWidgetItem* item);
	void SetChildCheckState(QTreeWidgetItem *item, Qt::CheckState state);
	void SetParentCheckState(QTreeWidgetItem *item);
	bool CheckHide(shared_ptr<TraceEntry> trace_entry);
	bool CheckHide(vector<string> names, QTreeWidgetItem* item);

private:
	LogDisplayui m_ui;
	map<int, QColor>  m_color_log_level;
	QColor            m_color_row;
	QTreeWidgetItem*  m_tree_cur_item = nullptr;
};
