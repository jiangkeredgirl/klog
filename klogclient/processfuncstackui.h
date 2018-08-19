#pragma once

#include <QObject>
#include "qtstandard.h"

class ProcessFuncStackui : public QObject
{
	Q_OBJECT

public:
	ProcessFuncStackui();
	~ProcessFuncStackui();

public:
	void setupUi(QWidget* hostWidget);

public:
	QWidget*  m_hostWidget = nullptr;
	QTableWidget* m_tableStack = nullptr;
	QLabel*  m_labelProcessName = nullptr;
};
