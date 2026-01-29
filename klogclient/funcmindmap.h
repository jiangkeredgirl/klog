#pragma once

#include <QDialog>
#include "cstandard.h"
#include "logfile.h"
#include "funcstack.h"
#include "funcflow.h"
#include "funcmindmap_ui.h"

class FuncMindMap : public QDialog
{
	Q_OBJECT

public:
	FuncMindMap(QWidget *parent);
	~FuncMindMap();

signals:
	void SignalCloseDialog(const string& title);

public:
	virtual void closeEvent(QCloseEvent *e) override;

	public slots:
	void SlotReceiveTrack(shared_ptr<TraceEntry> track_entry, LogFileStatus status);

private:
	void AddFuncStack(shared_ptr<TraceEntry> track_entry);
	void AddFuncTree(shared_ptr<TraceEntry> track_entry);

	void FuncStacksAddInTrees(const string& process_name, const string& threadid, list<shared_ptr<TraceEntry>>& func_stacks);
	void FuncStacksAddInTree(list<shared_ptr<TraceEntry>>& func_stacks, list<shared_ptr<FuncTreeNode>>& func_trees);

private:
	static shared_ptr<TraceEntry>   GetPairTrack(shared_ptr<TraceEntry> track_entry, list<shared_ptr<TraceEntry>>& track_stacks);
	static shared_ptr<FuncTreeNode> GetPairTrack(shared_ptr<TraceEntry> track_entry, list<shared_ptr<FuncTreeNode>>& track_trees);
	static shared_ptr<FuncTreeNode> GetCallingTrack(list<shared_ptr<FuncTreeNode>>& track_trees);

private:
	FuncMindMapui m_ui;
	map<string/*process_name*/, map<string/*threadid*/, list<shared_ptr<TraceEntry>>>> m_func_stacks;
	map<string/*process_name*/, map<string/*threadid*/, list<shared_ptr<FuncTreeNode>>>> m_func_trees;
};
