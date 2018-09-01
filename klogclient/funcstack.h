#pragma once

#include <QDialog>
#include "cstandard.h"
#include "funcstackui.h"
#include "logfile.h"

class FuncPath
{
public:
	__int64 logindex = 0;
	string modulename;
	string filename;
	string funcname;
	int    line = 0;
	bool operator == (const FuncPath& other) const
	{
		if (logindex == other.logindex
			&& modulename == other.modulename
			&& filename == other.filename
			&& funcname == other.funcname
			&& line == other.line)
		{
			return true;
		}
		return false;
	}
	bool operator != (const FuncPath& other) const
	{
		return !(operator == (other));
	}
};

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

private:
	FuncStackui m_ui;
	map<string/*process_name*/, map<string/*threadid*/, list<shared_ptr<FuncPath>/*func_path*/>>> m_stacks;
};
