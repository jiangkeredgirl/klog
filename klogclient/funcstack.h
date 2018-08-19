#pragma once

#include <QDialog>
#include "cstandard.h"
#include "funcstackui.h"
#include "logfile.h"

struct FuncPath
{
	string modulename;
	string filename;
	string funcname;
	int    line = 0;
	bool operator == (const FuncPath& other)
	{
		if (modulename == other.modulename
			&& filename == other.filename
			&& funcname == other.funcname
			&& line == other.line)
		{
			return true;
		}
		return false;
	}
	bool operator != (const FuncPath& other)
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

private:
	FuncStackui m_ui;
	map<string/*process_name*/, map<string/*threadid*/, list<pair<__int64/*logindex*/, FuncPath/*func_path*/>>>> m_stacks;
};
