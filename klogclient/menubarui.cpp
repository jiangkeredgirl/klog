#include "menubarui.h"

MenuBarui::MenuBarui()
{
}

MenuBarui::~MenuBarui()
{
}

void MenuBarui::setupUi(QMenuBar* hostWidget)
{
	m_hostWidget = hostWidget;
	if (m_hostWidget)
	{
		m_hostWidget->setStyleSheet("MenuBar{border: 1px solid red; }");
		m_viewMenu = m_hostWidget->addMenu(tr("&view"));
		m_viewMenu->addAction(tr("log file"));
		m_viewMenu->addAction(tr("log level"));
		m_viewMenu->addAction(tr("log head"));
		m_viewMenu->addAction(tr("log filter"));
		m_viewMenu->addAction(tr("log search"));
	}
}