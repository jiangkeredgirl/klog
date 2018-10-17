#pragma once

#include <QWidget>
#include "logheadbar_ui.h"

class LogHeadBar : public QWidget
{
	Q_OBJECT

public:
	LogHeadBar(QWidget *parent);
	~LogHeadBar();

signals:
	void SignalStateChanged(const string& name, Qt::CheckState state);

public slots:
	void SlotStateChanged(int state);

protected:
	virtual void paintEvent(QPaintEvent *) override;

private:
	LogHeadBarui m_ui;
};
