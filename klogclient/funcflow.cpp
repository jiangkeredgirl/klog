#include "funcflow.h"

FuncFlow::FuncFlow(QWidget *parent)
	: QDialog(parent)
{
	m_ui.setupUi(this);
}

FuncFlow::~FuncFlow()
{
}

void FuncFlow::closeEvent(QCloseEvent *e)
{
	emit SignalCloseDialog(tr(u8"函数调用流").toStdString());
}