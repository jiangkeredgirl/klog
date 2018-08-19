#include "funcstack.h"

FuncStack::FuncStack(QWidget *parent)
	: QDialog(parent)
{
	m_ui.setupUi(this);
}

FuncStack::~FuncStack()
{
}

void FuncStack::closeEvent(QCloseEvent *e)
{
	emit SignalCloseDialog(tr(u8"函数调用实时图").toStdString());
}