#include "processfuncstackui.h"

ProcessFuncStackui::ProcessFuncStackui()
	: QObject()
{
}

ProcessFuncStackui::~ProcessFuncStackui()
{
}

void ProcessFuncStackui::setupUi(QWidget* hostWidget)
{
	m_hostWidget = hostWidget;
	if (m_hostWidget)
	{
		m_hostWidget->setStyleSheet("ProcessFuncStack{border:1px solid red;}");

		QHBoxLayout* layout = new QHBoxLayout;
		m_hostWidget->setLayout(layout);
		layout->setContentsMargins(1, 0, 1, 0);
		layout->setSpacing(10);

		m_labelProcessName = new QLabel(m_hostWidget);
		layout->addWidget(m_labelProcessName);
		m_labelProcessName->setText(u8"进程名");
		m_labelProcessName->setStyleSheet("QLabel{border:1px solid red;}");
		//m_labelProcessName->setFixedWidth(200);
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
		m_tableStack = new QTableWidget(0, headerTags.size(), m_hostWidget);
		layout->addWidget(m_tableStack);
		m_tableStack->setHorizontalHeaderLabels(headerTags);
		m_tableStack->horizontalHeader()->setFixedHeight(30);
		//m_tableLogInfo->verticalHeader()->setVisible(false);
		m_tableStack->setStyleSheet("QTableWidget{border:1px solid red; margin:0px;}");
		m_tableStack->horizontalHeader()->setStyleSheet("QHeaderView{border:none; border-bottom:1px solid red;}");
		m_tableStack->setEditTriggers(QAbstractItemView::NoEditTriggers);
		m_tableStack->setSelectionBehavior(QAbstractItemView::SelectRows);
		m_tableStack->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
		m_tableStack->horizontalHeader()->setSectionsMovable(true);
		m_tableStack->horizontalHeader()->setHighlightSections(false);
		m_tableStack->horizontalHeader()->setStretchLastSection(true);
	}
}