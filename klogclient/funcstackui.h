#pragma once

#include <QObject>
#include "qtstandard.h"

class FuncStackui : public QObject
{
	Q_OBJECT

public:
	FuncStackui();
	~FuncStackui();

public:
	void setupUi(QDialog* hostDialog);

public:
	QDialog*  m_hostDialog = nullptr;
	QTableWidget* m_tableFuncStacks = nullptr;
};
