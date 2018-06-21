#include "klogclient.h"

KlogClient::KlogClient(QWidget *parent)
	: QMainWindow(parent)
{
	m_ui.setupUi(this);
	Init();	
}

KlogClient::~KlogClient()
{
	Uninit();
}

void KlogClient::Init()
{
	// menubar
	m_menuBar = new MenuBar(this);
	this->setMenuBar(m_menuBar);

	// log file bar
	m_logFileBar = new LogFileBar(this->centralWidget());
	m_ui.m_mainLayout->addWidget(m_logFileBar);	

	// log level bar
	m_logLevelBar = new LogLevelBar(this->centralWidget());
	m_ui.m_mainLayout->addWidget(m_logLevelBar);

	// log head bar
	m_logHeadBar = new LogHeadBar(this->centralWidget());
	m_ui.m_mainLayout->addWidget(m_logHeadBar);

	// log filter bar
	m_logFilterBar = new LogFilterBar(this->centralWidget());
	m_ui.m_mainLayout->addWidget(m_logFilterBar);

	// log search bar
	m_logSearchBar = new LogSearchBar(this->centralWidget());
	m_ui.m_mainLayout->addWidget(m_logSearchBar);

	// log display
	m_logDisplay = new LogDisplay(this->centralWidget());
	m_ui.m_mainLayout->addWidget(m_logDisplay);

	connect(m_logFileBar, &LogFileBar::SignalOpenLocalLogFile, this, &KlogClient::SlotOpenLocalLogFile);
	connect(this, &KlogClient::SignalAddTrace, m_logDisplay, &LogDisplay::SlotAddTrace);
}

void KlogClient::Uninit()
{
	LogFile::instance().StopRead();
}

void KlogClient::SlotOpenLocalLogFile(const string& filename)
{
	LogFile::instance().ReadTraceEntry(filename, std::bind(&KlogClient::ReadLocalLogFileCallBack
		, this, std::placeholders::_1, std::placeholders::_2));
}

int KlogClient::ReadLocalLogFileCallBack(const TraceEntry& trace_entry, int status)
{
	emit SignalAddTrace(trace_entry);
	return 0;
}