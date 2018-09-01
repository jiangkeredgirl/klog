﻿#pragma once

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

public:
	void PushStack(const string& proccess_name, const string& threadid, const string& func_name);
	void PopStack(const string& proccess_name, const string& threadid, const string& func_name);

public:
	QDialog*  m_hostDialog = nullptr;
	QTableWidget* m_tableStacks = nullptr;

};
