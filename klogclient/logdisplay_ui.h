#pragma once

#include <QObject>
#include "qtstandard.h"

class LogDisplayui : public QObject
{
	Q_OBJECT
public:
		enum ColumIndex
	{
		INDEX,
		FUNCTRACK,
		FUNCTIME,
		LEVEL,
		LABEL,
		THREADID,
		PROCESSNAME,
		MODULENAME,
		FILENAME,
		FUNCNAME,
		LINE,
		DATETIME,
		RUNTIME,
		ASYNC,
		SYNCLOCK,
		CONTENT
	};

public:
	LogDisplayui();
	~LogDisplayui();

public:
	void setupUi(QWidget* hostWidget);

public:
	QWidget*  m_hostWidget = nullptr;
	QTableWidget* m_tableLogInfo = nullptr;
	QTreeWidget*  m_treeSourceNames = nullptr;
	QLabel*       m_label_loading = nullptr;
};
