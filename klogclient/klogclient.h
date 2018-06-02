#pragma once

#include <QtWidgets/QMainWindow>
#include "klogclientui.h"
#include "menubar.h"
#include "loglevelbar.h"

class klogclient : public QMainWindow
{
	Q_OBJECT

public:
	klogclient(QWidget *parent = Q_NULLPTR);

	void Init();

private:
	Klogclientui m_ui;

	MenuBar*     m_menuBar = nullptr;
	LogLevelBar* m_logLevelBar = nullptr;
};
