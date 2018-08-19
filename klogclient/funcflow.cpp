#include "funcstaticstack.h"

FuncStaticStack::FuncStaticStack(QWidget *parent)
	: QDialog(parent)
{
	m_ui.setupUi(this);
}

FuncStaticStack::~FuncStaticStack()
{
}

void FuncStaticStack::closeEvent(QCloseEvent *e)
{
	emit SignalCloseDialog(tr(u8"函数调用静态图").toStdString());
}