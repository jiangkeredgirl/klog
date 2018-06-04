﻿#include "menubarui.h"

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
		m_hostWidget->setStyleSheet("MenuBar{border:1px solid red;}");
		m_viewMenu = m_hostWidget->addMenu(tr("&view"));
		m_viewMenu->addAction(tr("log file"));
		m_viewMenu->addAction(tr("log level"));
		m_viewMenu->addAction(tr("log head"));
		m_viewMenu->addAction(tr("log filter"));
		m_viewMenu->addAction(tr("log search"));
		m_viewMenu->addAction(tr(u8"重置默认配置"));
		m_viewMenu->addAction(tr(u8"清空log"));
		m_viewMenu->addAction(tr(u8"函数调用实时图"));
		m_viewMenu->addAction(tr(u8"函数调用静态图"));
	}
}