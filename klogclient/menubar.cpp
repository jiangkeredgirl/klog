#include "stdafx.h"
#include "menubar.h"

MenuBar::MenuBar(QWidget *parent)
	: QMenuBar(parent)
{
	m_ui.setupUi(this);
	connect(m_ui.m_viewMenu, &QMenu::triggered, this, &MenuBar::SlotTriggered);
}

MenuBar::~MenuBar()
{
}

void MenuBar::SlotTriggered(QAction * action)
{
	emit SignalActionTriggered(action);
}

//void MenuBar::paintEvent(QPaintEvent *event)
//{
//	QStyleOption opt;
//	opt.init(this);
//	QPainter p(this);
//	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
//}