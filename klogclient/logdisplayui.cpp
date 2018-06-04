#include "logdisplayui.h"
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

		QTableWidget* tableLogInfo = new QTableWidget(10, 15, m_hostWidget);
		layout->addWidget(tableLogInfo);
		tableLogInfo->setStyleSheet("QTableWidget{border:1px solid red; margin:0px;}");

		tableLogInfo->horizontalHeader()->setStyleSheet("QHeaderView{border:none; border-bottom:1px solid red;}");
	 	tableLogInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
   		tableLogInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
		tableLogInfo->verticalHeader()->setVisible(false);
		tableLogInfo->horizontalHeader()->setFixedHeight(30);

		//QSizePolicy tableSizePolicy = tableLogInfo->sizePolicy();
		//tableSizePolicy.setHorizontalPolicy(QSizePolicy::MinimumExpanding);
		//tableLogInfo->horizontalHeader()->setSizePolicy(tableSizePolicy);

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
		tableLogInfo->setHorizontalHeaderLabels(headerTags);
	}
}