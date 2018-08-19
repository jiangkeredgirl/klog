#pragma once

#include <QObject>
#include "qtstandard.h"

class FuncFlowui : public QObject
{
	Q_OBJECT

public:
	FuncFlowui();
	~FuncFlowui();

public:
	void setupUi(QDialog* hostDialog);

public:
	QDialog*  m_hostDialog = nullptr;
	QTableWidget* m_tableLogInfo = nullptr;
};
