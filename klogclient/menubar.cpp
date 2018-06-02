#include "menubar.h"

MenuBar::MenuBar(QWidget *parent)
	: QMenuBar(parent)
{
	m_ui.setupUi(this);
}

MenuBar::~MenuBar()
{
}


//void MenuBar::paintEvent(QPaintEvent *event)
//{
//	QStyleOption opt;
//	opt.init(this);
//	QPainter p(this);
//	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
//}