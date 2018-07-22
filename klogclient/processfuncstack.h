#pragma once

#include <QWidget>
#include "processfuncstackui.h"

class ProcessFuncStack : public QWidget
{
	Q_OBJECT

public:
	ProcessFuncStack(QWidget *parent);
	~ProcessFuncStack();

protected:
	virtual void paintEvent(QPaintEvent *) override;

private:
	ProcessFuncStackui m_ui;

};
