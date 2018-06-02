#pragma once

#include <QWidget>
#include "logheadbarui.h"

class LogHeadBar : public QWidget
{
	Q_OBJECT

public:
	LogHeadBar(QWidget *parent);
	~LogHeadBar();

protected:
	virtual void paintEvent(QPaintEvent *) override;

private:
	LogHeadBarui m_ui;
};
