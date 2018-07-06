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
	qRegisterMetaType<shared_ptr<TraceEntry>>("shared_ptr<TraceEntry>");
	qRegisterMetaType<LogFileStatus>("LogFileStatus");
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
	connect(&LogFile::instance(), &LogFile::SignalAddTrace, m_logDisplay, &LogDisplay::SlotAddTrace, Qt::BlockingQueuedConnection);
}

void KlogClient::Uninit()
{
	disconnect(&LogFile::instance(), &LogFile::SignalAddTrace, m_logDisplay, &LogDisplay::SlotAddTrace);
	LogFile::instance().StopRead();
}

void KlogClient::SlotOpenLocalLogFile(const string& filename)
{
	std::thread t([this, filename]() {
		LogFile::instance().ReadTraceEntry(filename);
	});
	t.detach();
}