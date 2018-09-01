#pragma once

#include <QDialog>
#include "cstandard.h"
#include "funcflowui.h"
#include "logfile.h"
#include "funcstack.h"

class FuncTree
{
public:
	shared_ptr<TraceEntry> func_path;
	list<shared_ptr<FuncTree>> branchs;
};

class FuncFlow : public QDialog
{
	Q_OBJECT

public:
	FuncFlow(QWidget *parent);
	~FuncFlow();

signals:
	void SignalCloseDialog(const string& title);

public:
	virtual void closeEvent(QCloseEvent *e) override;

	public slots:
	void SlotReceiveTrack(shared_ptr<TraceEntry> track_entry, LogFileStatus status);

private:
	void FuncStacksAddInTrees(const string& process_name, const string& threadid, list<shared_ptr<TraceEntry>>& func_stacks);
	void FuncStacksAddInTree(list<shared_ptr<TraceEntry>>& func_stacks, list<shared_ptr<FuncTree>>& func_trees);

private:
	FuncFlowui m_ui;
	map<string/*process_name*/, map<string/*threadid*/, list<shared_ptr<TraceEntry>>>> m_stacks;
	map<string/*process_name*/, map<string/*threadid*/, bool>> m_stacks_end;
	map<string/*process_name*/, map<string/*threadid*/, list<shared_ptr<FuncTree>>>> m_func_trees;
};
