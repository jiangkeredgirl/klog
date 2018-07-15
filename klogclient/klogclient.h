#pragma once

#include <QtWidgets/QMainWindow>
#include "klogclientui.h"
#include "menubar.h"
#include "logfilebar.h"
#include "loglevelbar.h"
#include "logheadbar.h"
#include "logfilterbar.h"
#include "logsearchbar.h"
#include "logdisplay.h"
#include "cstandard.h"
#include "logfile.h"

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
	void SlotActionTriggered(QAction * action);

private:
	KlogClientui   m_ui;

	MenuBar*       m_menuBar = nullptr;
	LogFileBar*    m_logFileBar = nullptr;
	LogLevelBar*   m_logLevelBar = nullptr;
	LogHeadBar*    m_logHeadBar = nullptr;
	LogFilterBar*  m_logFilterBar = nullptr;
	LogSearchBar*  m_logSearchBar = nullptr;
	LogDisplay*    m_logDisplay = nullptr;
};
