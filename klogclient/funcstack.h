#pragma once

#include <QDialog>
#include "cstandard.h"
#include "funcstackui.h"
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

private:
	FuncStackui m_ui;
	map<string/*process_name*/, map<string/*threadid*/, list<pair<__int64/*logindex*/,string/*func_path*/>>>> m_stacks;
};
