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

	m_funcDynamicStack = new FuncDynamicStack(this->centralWidget());
	m_funcStaticStack = new FuncStaticStack(this->centralWidget());


	connect(m_logFileBar, &LogFileBar::SignalOpenLocalLogFile, this, &KlogClient::SlotOpenLocalLogFile);
	connect(&LogFile::instance(), &LogFile::SignalAddTrace, m_logDisplay, &LogDisplay::SlotAddTrace, Qt::BlockingQueuedConnection);
	connect(m_logLevelBar, &LogLevelBar::SignalStateChanged, m_logDisplay, &LogDisplay::SlotLevelChange);
	connect(m_logHeadBar, &LogHeadBar::SignalStateChanged, m_logDisplay, &LogDisplay::SlotHeadChange);
	connect(m_logFilterBar, &LogFilterBar::SignalFilter, m_logDisplay, &LogDisplay::SlotFilter);
	connect(m_menuBar, &MenuBar::SignalActionTriggered, this, &KlogClient::SlotActionTriggered);
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

void KlogClient::SlotActionTriggered(QAction * action)
{
	if (action->text() == tr("log file"))
	{
		if (action->isChecked())
		{
			m_logFileBar->show();
		}
		else
		{
			m_logFileBar->hide();
		}
	}
	else if (action->text() == tr("log level"))
	{
		if (action->isChecked())
		{
			m_logLevelBar->show();
		}
		else
		{
			m_logLevelBar->hide();
		}
	}
	else if (action->text() == tr("log head"))
	{
		if (action->isChecked())
		{
			m_logHeadBar->show();
		}
		else
		{
			m_logHeadBar->hide();
		}
	}
	else if (action->text() == tr("log filter"))
	{
		if (action->isChecked())
		{
			m_logFilterBar->show();
		}
		else
		{
			m_logFilterBar->hide();
		}
	}
	else if (action->text() == tr("log search"))
	{
		if (action->isChecked())
		{
			m_logSearchBar->show();
		}
		else
		{
			m_logSearchBar->hide();
		}
	}
	else if (action->text() == tr(u8"函数调用实时图"))
	{
		if (action->isChecked())
		{
			m_funcDynamicStack->show();
		}
		else
		{
			m_funcDynamicStack->hide();
		}
	}
	else if (action->text() == tr(u8"函数调用静态图"))
	{
		if (action->isChecked())
		{
			m_funcStaticStack->show();
		}
		else
		{
			m_funcStaticStack->hide();
		}
	}
}