#pragma once

#include <QWidget>
#include "logfilterbarui.h"

class LogFilterBar : public QWidget
{
	Q_OBJECT

public:
	LogFilterBar(QWidget *parent);
	~LogFilterBar();

protected:
	virtual void paintEvent(QPaintEvent *) override;

private:
	LogFilterBarui m_ui;
};
