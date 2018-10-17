#pragma once

#include <QDialog>
#include "cstandard.h"
#include "funcstack_ui.h"
#include "logfile.h"

class FuncStack : public QDialog
{
	Q_OBJECT

public:
	FuncStack(QWidget *parent);
	~FuncStack();

signals:
	void SignalCloseDialog(const string& title);

public:
	virtual void closeEvent(QCloseEvent *e) override;

public slots:
	void SlotReceiveTrack(shared_ptr<TraceEntry> track_entry, LogFileStatus status);

public:
	void PushStack(shared_ptr<TraceEntry> track_entry);
	void PopStack(shared_ptr<TraceEntry> track_entry);
	static bool IsPairTrack(shared_ptr<TraceEntry> push_track_entry, shared_ptr<TraceEntry> pop_track_entry);
	static bool IsExistTrack(shared_ptr<TraceEntry> old_track_entry, shared_ptr<TraceEntry> new_track_entry);

private:
	FuncStackui m_ui;
	map<string/*process_name*/, map<string/*threadid*/, list<shared_ptr<TraceEntry>>>> m_stacks;
};
