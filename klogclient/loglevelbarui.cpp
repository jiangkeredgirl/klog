#include "loglevelbarui.h"

LogLevelBarui::LogLevelBarui()
{
}

LogLevelBarui::~LogLevelBarui()
{
}

void LogLevelBarui::setupUi(QWidget* hostWidget)
{
	m_hostWidget = hostWidget;
	if (m_hostWidget)
	{
		m_hostWidget->setFixedHeight(26);
		m_hostWidget->setStyleSheet("LogLevelBar{border: 1px solid red; }");

		QHBoxLayout* layout = new QHBoxLayout;
		m_hostWidget->setLayout(layout);
		layout->setContentsMargins(1, 0, 0, 0);
		layout->setSpacing(1);

		QLabel* labelTag = new QLabel(m_hostWidget);
		labelTag->setText(tr("log level"));
		layout->addWidget(labelTag);

		QCheckBox* checkBox1 = new QCheckBox(m_hostWidget);
		checkBox1->setText(tr("box1"));
		checkBox1->setCheckState(Qt::CheckState::Unchecked);
		layout->addWidget(checkBox1);

		QCheckBox* checkBox2 = new QCheckBox;
		checkBox2->setText(tr("box2"));
		checkBox2->setCheckState(Qt::CheckState::PartiallyChecked);
		layout->addWidget(checkBox2);

		QCheckBox* checkBox3 = new QCheckBox;
		checkBox3->setText(tr("box3"));
		checkBox3->setCheckState(Qt::CheckState::Checked);
		layout->addWidget(checkBox3);
	}
}