#pragma once

#include <QWidget>
#include "loglevelbarui.h"

class LogLevelBar : public QWidget
{
	Q_OBJECT

public:
	LogLevelBar(QWidget *parent);
	~LogLevelBar();

protected:
	virtual void paintEvent(QPaintEvent *) override;

private:
	LogLevelBarui m_ui;
};
