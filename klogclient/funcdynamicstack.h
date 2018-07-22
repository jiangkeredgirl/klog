#pragma once

#include <QDialog>
#include "cstandard.h"
#include "funcdynamicstackui.h"

class FuncDynamicStack : public QDialog
{
	Q_OBJECT

public:
	FuncDynamicStack(QWidget *parent);
	~FuncDynamicStack();

signals:
	void SignalCloseDialog(const string& title);

public:
	virtual void closeEvent(QCloseEvent *e) override;

private:
	FuncDynamicStackui m_ui;
};
