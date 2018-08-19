#pragma once

#include <QDialog>
#include "cstandard.h"
#include "funcflowui.h"
#include "logfile.h"
#include "funcstack.h"

struct FuncTree
{
	list<FuncPath> funcs;
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
	FuncFlowui m_ui;
	map<string/*process_name*/, map<string/*threadid*/, list<pair<__int64/*logindex*/, FuncPath/*func_path*/>>>> m_stacks;
	map<string/*process_name*/, map<string/*threadid*/, list<pair<__int64/*logindex*/, FuncPath/*func_path*/>>>> m_return_stacks;
	map<string/*process_name*/, map<string/*threadid*/, FuncTree>> m_func_trees;

};
