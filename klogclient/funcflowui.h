#pragma once

#include <QObject>
#include "qtstandard.h"

class FuncStaticStackui : public QObject
{
	Q_OBJECT

public:
	FuncStaticStackui();
	~FuncStaticStackui();

public:
	void setupUi(QDialog* hostDialog);

public:
	QDialog*  m_hostDialog = nullptr;
	QTableWidget* m_tableLogInfo = nullptr;
};
