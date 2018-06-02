#pragma once

#include <QObject>
#include "qtstandard.h"

class MenuBarui : public QObject
{
	Q_OBJECT

public:
	MenuBarui();
	~MenuBarui();

public:
	void setupUi(QMenuBar* myselfWidget);

public:
	QMenuBar*  m_myselfWidget = nullptr;
	QMenu*     m_viewMenu = nullptr;

};
