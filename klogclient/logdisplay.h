#pragma once

#include <QWidget>
#include "logdisplayui.h"
#include "logfile.h"

class LogDisplay : public QWidget
{
	Q_OBJECT

public:
	LogDisplay(QWidget *parent);
	~LogDisplay();

public slots:
	int SlotAddTrace(shared_ptr<TraceEntry> trace_entry);

protected:
	virtual void paintEvent(QPaintEvent *) override;

private:
	int SetCellText(int row, int col, const string& text);

private:
	LogDisplayui m_ui;
};
