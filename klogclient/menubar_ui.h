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
	void setupUi(QMenuBar* hostWidget);

public:
	QMenuBar*  m_hostWidget = nullptr;
	QMenu*     m_viewMenu = nullptr;

};
