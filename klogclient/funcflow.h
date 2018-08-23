#pragma once

#include <QDialog>
#include "cstandard.h"
#include "funcflowui.h"
#include "logfile.h"
#include "funcstack.h"

struct FuncTree
{
	FuncPath func_path;
	list<FuncTree> branchs;
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
	void FuncStacksAddInTrees(const string& process_name, const string& threadid, list<FuncPath>& func_stacks);
	void FuncStacksAddInTree(list<FuncPath>& func_stacks, list<FuncTree>& func_trees);

private:
	FuncFlowui m_ui;
	map<string/*process_name*/, map<string/*threadid*/, list<FuncPath/*func_path*/>>> m_stacks;
	map<string/*process_name*/, map<string/*threadid*/, bool>> m_stacks_end;
	map<string/*process_name*/, map<string/*threadid*/, list<FuncTree>>> m_func_trees;
};
