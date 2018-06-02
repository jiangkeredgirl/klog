#include "klogclientui.h"

Klogclientui::Klogclientui()
{
}

Klogclientui::~Klogclientui()
{
}

void Klogclientui::setupUi(QMainWindow* hostWidget)
{
	m_hostWidget = hostWidget;
	if (m_hostWidget)
	{
		m_hostWidget->resize(1280, 720);
		QWidget *layoutWidget = new QWidget(m_hostWidget);
		m_hostWidget->setCentralWidget(layoutWidget);
		m_mainLayout = new QVBoxLayout;
		layoutWidget->setLayout(m_mainLayout);
		m_mainLayout->setSpacing(1);
		m_mainLayout->setContentsMargins(0, 1, 0, 0);
	}
}