#pragma once

#include <QWidget>
#include "logdisplayui.h"

class LogDisplay : public QWidget
{
	Q_OBJECT

public:
	LogDisplay(QWidget *parent);
	~LogDisplay();

protected:
	virtual void paintEvent(QPaintEvent *) override;

private:
	LogDisplayui m_ui;
};
