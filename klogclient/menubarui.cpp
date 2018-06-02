#include "menubarui.h"

MenuBarui::MenuBarui()
{
}

MenuBarui::~MenuBarui()
{
}

void MenuBarui::setupUi(QMenuBar* myselfWidget)
{
	m_myselfWidget = myselfWidget;
	if (m_myselfWidget)
	{
		m_myselfWidget->setStyleSheet("MenuBar{border: 1px solid red; }");
		m_viewMenu = m_myselfWidget->addMenu(tr("&view"));
		m_viewMenu->addAction(tr("log file"));
		m_viewMenu->addAction(tr("log level"));
		m_viewMenu->addAction(tr("log head"));
		m_viewMenu->addAction(tr("log filter"));
		m_viewMenu->addAction(tr("log search"));
	}
}