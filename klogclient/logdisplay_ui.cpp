#include "stdafx.h"
#include "logdisplay_ui.h"
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

		m_treeSourceNames = new QTreeWidget(m_hostWidget);
		layout->addWidget(m_treeSourceNames);
		m_treeSourceNames->setHeaderLabel(u8"函数名");
		m_treeSourceNames->setStyleSheet("QTreeWidget{border:1px solid red;}");
		m_treeSourceNames->setFixedWidth(200);
		//for (size_t i = 0; i < 5; i++)
		//{
		//	QTreeWidgetItem* pItem = new QTreeWidgetItem();
		//	pItem->setText(0, u8"程序名");
		//	pItem->setCheckState(0, Qt::PartiallyChecked);
		//	for (size_t i = 0; i < 5; i++)
		//	{
		//		QTreeWidgetItem* pItem1 = new QTreeWidgetItem();
		//		pItem1->setText(0, u8"模块名");
		//		pItem1->setCheckState(0, Qt::Checked);
		//		pItem->addChild(pItem1);
		//	}
		//	treeSourceFiles->addTopLevelItem(pItem);
		//}

		QStringList headerTags = {
			"index",
			"functrack",
			"functime",
			"level",
			"label",
			"threadid",
			"processname",
			"modulename",
			"filename",
			"funcname",
			"line",
			"datetime",
			"runtime",
			"async",
			"synclock",
			"content"
		};
		m_label_loading = new QLabel(u8"正在加载log文件...", m_hostWidget);
		layout->addWidget(m_label_loading);
		QHBoxLayout* table_layout = new QHBoxLayout;
		m_label_loading->setLayout(table_layout);
		table_layout->setContentsMargins(0, 0, 0, 0);
		m_label_loading->setAlignment(Qt::AlignCenter);

		m_tableLogInfo = new QTableWidget(0, headerTags.size(), m_label_loading);
		table_layout->addWidget(m_tableLogInfo);
		m_tableLogInfo->setHorizontalHeaderLabels(headerTags);
		m_tableLogInfo->horizontalHeader()->setFixedHeight(30);
		//m_tableLogInfo->verticalHeader()->setVisible(false);
		m_tableLogInfo->setStyleSheet("QTableWidget{border:1px solid red; margin:0px;}");
		m_tableLogInfo->horizontalHeader()->setStyleSheet("QHeaderView{border:none; border-bottom:1px solid red;}");
		m_tableLogInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
		m_tableLogInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
		m_tableLogInfo->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
		m_tableLogInfo->horizontalHeader()->setSectionsMovable(true);
		m_tableLogInfo->horizontalHeader()->setHighlightSections(false);
		m_tableLogInfo->horizontalHeader()->setStretchLastSection(true);
	}
}