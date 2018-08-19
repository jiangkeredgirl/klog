#pragma once

#include <QWidget>
#include "cstandard.h"
#include "processfuncstackui.h"

class ProcessFuncStack : public QWidget
{
	Q_OBJECT

public:
	ProcessFuncStack(QWidget *parent);
	~ProcessFuncStack();

public:
	void InitStack(const string& process_name, map<string/*threadid*/, list<string/*func_name*/>>);

protected:
	virtual void paintEvent(QPaintEvent *) override;

private:
	ProcessFuncStackui m_ui;
	string  m_process_name;
	map<string/*threadid*/, list<string/*func_name*/>> m_stacks;
};
