#pragma once

#include <QtWidgets/QMainWindow>
#include "klogclient_ui.h"
#include "menubar.h"
#include "logfilebar.h"
#include "loglevelbar.h"
#include "logheadbar.h"
#include "logfilterbar.h"
#include "logsearchbar.h"
#include "logdisplay.h"
#include "cstandard.h"
#include "logfile.h"
#include "funcstack.h"
#include "funcflow.h"

class KlogClient : public QMainWindow
{
	Q_OBJECT

public:
	KlogClient(QWidget *parent = Q_NULLPTR);
	~KlogClient();

	void Init();
	void Uninit();

public slots:
	void SlotOpenLocalLogFile(const string& filename);
	void SlotOpenRemoteLogMessage(const string& ip, int control_port, int sync_trace_port, int async_trace_port);
	void SlotActionTriggered(QAction * action);
	void SlotCloseStackDialog(const string& title);

private:
	KlogClientui   m_ui;

	MenuBar*       m_menuBar = nullptr;
	LogFileBar*    m_logFileBar = nullptr;
	LogLevelBar*   m_logLevelBar = nullptr;
	LogHeadBar*    m_logHeadBar = nullptr;
	LogFilterBar*  m_logFilterBar = nullptr;
	LogSearchBar*  m_logSearchBar = nullptr;
	LogDisplay*    m_logDisplay = nullptr;
	FuncStack* m_funcStack = nullptr;
	FuncFlow*  m_funcFlow = nullptr;
};
