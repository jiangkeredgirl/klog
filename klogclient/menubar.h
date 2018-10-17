#pragma once

#include <QWidget>
#include "menubar_ui.h"

class MenuBar : public QMenuBar
{
	Q_OBJECT

public:
	MenuBar(QWidget *parent);
	~MenuBar();

signals:
	void SignalActionTriggered(QAction * action);

public slots:
	void SlotTriggered(QAction * action);

//protected:
//	virtual void paintEvent(QPaintEvent *) override;

public:
	MenuBarui m_ui;
};
