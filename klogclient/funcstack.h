#pragma once

#include <QDialog>
#include "cstandard.h"
#include "funcstackui.h"

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

private:
	FuncStackui m_ui;
	map<string/*process_name*/, map<string/*threadid*/, list<string/*func_name*/>>> m_stacks;
};
