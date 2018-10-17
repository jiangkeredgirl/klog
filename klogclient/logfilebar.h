#pragma once

#include <QWidget>
#include "logfilebar_ui.h"
#include "cstandard.h"

class LogFileBar : public QWidget
{
	Q_OBJECT

public:
	LogFileBar(QWidget *parent);
	~LogFileBar();

protected:
	virtual void paintEvent(QPaintEvent *) override;

signals:
	void SignalOpenLocalLogFile(const string& filename);

public slots:
	void SlotButtonLocalFile();

private:
	LogFileBarui m_ui;
};
