#include "funcdynamicstack.h"

FuncDynamicStack::FuncDynamicStack(QWidget *parent)
	: QDialog(parent)
{
	m_ui.setupUi(this);
}

FuncDynamicStack::~FuncDynamicStack()
{
}

void FuncDynamicStack::closeEvent(QCloseEvent *e)
{
	emit SignalCloseDialog(tr(u8"函数调用实时图").toStdString());
}