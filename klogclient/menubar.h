#pragma once

#include <QWidget>
#include "menubarui.h"

class MenuBar : public QMenuBar
{
	Q_OBJECT

public:
	MenuBar(QWidget *parent);
	~MenuBar();

//protected:
//	virtual void paintEvent(QPaintEvent *) override;

private:
	MenuBarui m_ui;
};
