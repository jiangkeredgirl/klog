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

class klogclient : public QMainWindow
{
	Q_OBJECT

public:
	klogclient(QWidget *parent = Q_NULLPTR);

	void Init();

private:
	Klogclientui   m_ui;

	MenuBar*       m_menuBar = nullptr;
	LogFileBar*    m_logFileBar = nullptr;
	LogLevelBar*   m_logLevelBar = nullptr;
	LogHeadBar*    m_logHeadBar = nullptr;
	LogFilterBar*  m_logFilterBar = nullptr;
	LogSearchBar*  m_logSearchBar = nullptr;
	LogDisplay*    m_logDisplay = nullptr;
};
