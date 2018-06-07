#pragma once

#include <QWidget>
#include "logfilebarui.h"

class LogFileBar : public QWidget
{
	Q_OBJECT

public:
	LogFileBar(QWidget *parent);
	~LogFileBar();

protected:
	virtual void paintEvent(QPaintEvent *) override;

public slots:
	void SlotButtonLocalFile();

private:
	LogFileBarui m_ui;
};
