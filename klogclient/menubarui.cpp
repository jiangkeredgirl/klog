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
		m_hostWidget->setStyleSheet("MenuBar{border:1px solid red;}");
		m_viewMenu = m_hostWidget->addMenu(tr("&view"));
		m_viewMenu->addAction(tr("log file"));
		m_viewMenu->addAction(tr("log level"));
		m_viewMenu->addAction(tr("log head"));
		m_viewMenu->addAction(tr("log filter"));
		m_viewMenu->addAction(tr("log search"));
		m_viewMenu->addAction(tr(u8"重置默认配置"));
		m_viewMenu->addAction(tr(u8"清空log"));
		m_viewMenu->addAction(tr(u8"函数调用栈"));
		m_viewMenu->addAction(tr(u8"函数调用流"));
		m_viewMenu->addAction(tr(u8"函数执行时间靶点图"));
		QList<QAction*> actions = m_viewMenu->actions();
		int i = 0;
		for (auto item : actions)
		{
			item->setCheckable(true);
			if (i++ < 5)
			{
				item->setChecked(true);
			}
		}
	}
}