#pragma once

#include <QDialog>
#include "cstandard.h"
#include "funcflowui.h"

class FuncFlow : public QDialog
{
	Q_OBJECT

public:
	FuncFlow(QWidget *parent);
	~FuncFlow();

signals:
	void SignalCloseDialog(const string& title);

public:
	virtual void closeEvent(QCloseEvent *e) override;

private:
	FuncFlowui m_ui;
};
