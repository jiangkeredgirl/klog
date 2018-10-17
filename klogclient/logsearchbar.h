#pragma once

#include <QWidget>
#include "logsearchbar_ui.h"

class LogSearchBar : public QWidget
{
	Q_OBJECT

public:
	LogSearchBar(QWidget *parent);
	~LogSearchBar();

protected:
	virtual void paintEvent(QPaintEvent *) override;

private:
	LogSearchBarui m_ui;
};
