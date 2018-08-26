#include "processfuncstack.h"

ProcessFuncStack::ProcessFuncStack(QWidget *parent, const string& process_name)
	: QWidget(parent)
{
	m_process_name = process_name;
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