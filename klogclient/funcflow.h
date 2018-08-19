#pragma once

#include <QDialog>
#include "cstandard.h"
#include "funcstaticstackui.h"

class FuncStaticStack : public QDialog
{
	Q_OBJECT

public:
	FuncStaticStack(QWidget *parent);
	~FuncStaticStack();

signals:
	void SignalCloseDialog(const string& title);

public:
	virtual void closeEvent(QCloseEvent *e) override;

private:
	FuncStaticStackui m_ui;
};
