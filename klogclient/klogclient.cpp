#include "klogclient.h"

klogclient::klogclient(QWidget *parent)
	: QMainWindow(parent)
{
	m_ui.setupUi(this);
	Init();	
}

void klogclient::Init()
{
	// menubar
	m_menuBar = new MenuBar(this);
	this->setMenuBar(m_menuBar);

	// log level bar
	m_logLevelBar = new LogLevelBar(this->centralWidget());		
	m_ui.m_mainLayout->addWidget(m_logLevelBar);
}