#pragma once

#include <QWidget>
#include "loglevelbar_ui.h"

class LogLevelBar : public QWidget
{
	Q_OBJECT

public:
	LogLevelBar(QWidget *parent);
	~LogLevelBar();

signals:
	void SignalStateChanged(const string& name, Qt::CheckState state);

	public slots:
	void SlotStateChanged(int state);

protected:
	virtual void paintEvent(QPaintEvent *) override;

private:
	LogLevelBarui m_ui;
};
