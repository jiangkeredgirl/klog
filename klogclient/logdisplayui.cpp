﻿#include "logdisplayui.h"
#include "cstandard.h"

LogDisplayui::LogDisplayui()
{
}

LogDisplayui::~LogDisplayui()
{
}

void LogDisplayui::setupUi(QWidget* hostWidget)
{
	m_hostWidget = hostWidget;
	if (m_hostWidget)
	{
		m_hostWidget->setStyleSheet("LogDisplay{border:1px solid red;}");

		QHBoxLayout* layout = new QHBoxLayout;
		m_hostWidget->setLayout(layout);
		layout->setContentsMargins(1, 0, 1, 0);
		layout->setSpacing(10);

		QTreeWidget* treeSourceFiles = new QTreeWidget(m_hostWidget);
		layout->addWidget(treeSourceFiles);
		treeSourceFiles->setStyleSheet("QTreeWidget{border:1px solid red;}");
		treeSourceFiles->setFixedWidth(200);
		for (size_t i = 0; i < 5; i++)
		{
			QTreeWidgetItem* pItem = new QTreeWidgetItem();
			pItem->setText(0, u8"程序名");
			pItem->setCheckState(0, Qt::PartiallyChecked);
			for (size_t i = 0; i < 5; i++)
			{
				QTreeWidgetItem* pItem1 = new QTreeWidgetItem();
				pItem1->setText(0, u8"模块名");
				pItem1->setCheckState(0, Qt::Checked);
				pItem->addChild(pItem1);
			}
			treeSourceFiles->addTopLevelItem(pItem);
		}

		m_tableLogInfo = new QTableWidget(10, 15, m_hostWidget);
		layout->addWidget(m_tableLogInfo);
		m_tableLogInfo->setStyleSheet("QTableWidget{border:1px solid red; margin:0px;}");

		m_tableLogInfo->horizontalHeader()->setStyleSheet("QHeaderView{border:none; border-bottom:1px solid red;}");
	 	m_tableLogInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
   		m_tableLogInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
		//m_tableLogInfo->horizontalHeader()->setStretchLastSection(true);
		//m_tableLogInfo->resizeColumnsToContents();		
		m_tableLogInfo->verticalHeader()->setVisible(false);
		m_tableLogInfo->horizontalHeader()->setFixedHeight(30);

		//QSizePolicy tableSizePolicy = m_tableLogInfo->sizePolicy();
		//tableSizePolicy.setHorizontalPolicy(QSizePolicy::MinimumExpanding);
		//m_tableLogInfo->horizontalHeader()->setSizePolicy(tableSizePolicy);

		QStringList headerTags = {
			"index",
			"level",
			"label",
			"threadid",
			"datetime",
			"runtime",
			"functiontime",
			"processname",
			"modulename",
			"filename",
			"functionname",
			"line",
			"async",
			"synclock",
			"logbody"
		};
		m_tableLogInfo->setHorizontalHeaderLabels(headerTags);
	}
}