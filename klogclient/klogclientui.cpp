#include "klogclientui.h"

Klogclientui::Klogclientui()
{
}

Klogclientui::~Klogclientui()
{
}

void Klogclientui::setupUi(QMainWindow* myselfWidget)
{
	m_myselfWidget = myselfWidget;
	if (m_myselfWidget)
	{
		m_myselfWidget->resize(1280, 720);
		QWidget *layoutWidget = new QWidget(m_myselfWidget);
		m_myselfWidget->setCentralWidget(layoutWidget);
		m_mainLayout = new QVBoxLayout;
		layoutWidget->setLayout(m_mainLayout);
	}
}