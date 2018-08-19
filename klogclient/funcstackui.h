#pragma once

#include <QObject>
#include "qtstandard.h"

class FuncDynamicStackui : public QObject
{
	Q_OBJECT

public:
	FuncDynamicStackui();
	~FuncDynamicStackui();

public:
	void setupUi(QDialog* hostDialog);

public:
	QDialog*  m_hostDialog = nullptr;
	QTableWidget* m_tableLogInfo = nullptr;
};
