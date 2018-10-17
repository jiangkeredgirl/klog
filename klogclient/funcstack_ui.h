#pragma once

#include <QObject>
#include "qtstandard.h"
#include "cstandard.h"

class FuncStackui : public QObject
{
	Q_OBJECT

public:
	FuncStackui();
	~FuncStackui();

public:
	void setupUi(QDialog* hostDialog);
	bool eventFilter(QObject *target, QEvent *event);

public:
	void PushStack(const string& process_name, const string& threadid, const string& func_name);
	void PopStack(const string& process_name, const string& threadid, const string& func_name);

public:
	QDialog*  m_hostDialog = nullptr;
	QListWidget* m_stacks_list = nullptr;
};
