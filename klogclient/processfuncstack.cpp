#include "processfuncstack.h"

ProcessFuncStack::ProcessFuncStack(QWidget *parent)
	: QWidget(parent)
{
	m_ui.setupUi(this);
}

ProcessFuncStack::~ProcessFuncStack()
{
}

void ProcessFuncStack::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}