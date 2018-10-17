#pragma once

#include <QWidget>
#include "logfilterbar_ui.h"
#include "cstandard.h"

struct FilterCondition
{
	//string  only_show_content;
	//string  not_show_content;
	int     func_time = 0;
	string  datetime_begin;
	string  datetime_end;
};

class LogFilterBar : public QWidget
{
	Q_OBJECT

public:
	LogFilterBar(QWidget *parent);
	~LogFilterBar();

protected:
	virtual void paintEvent(QPaintEvent *) override;

signals:
	void SignalFilter(FilterCondition filter_condition);

	public slots:
	void SlotButtonFilter();

private:
	LogFilterBarui m_ui;
};
