#pragma once

#include <QWidget>
#include "logsearchbarui.h"

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
