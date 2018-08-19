#include "funcstaticstackui.h"

FuncStaticStackui::FuncStaticStackui()
	: QObject()
{
}

FuncStaticStackui::~FuncStaticStackui()
{
}

void FuncStaticStackui::setupUi(QDialog* hostDialog)
{
	m_hostDialog = hostDialog;
	if (m_hostDialog)
	{
		m_hostDialog->setWindowTitle(tr(u8"函数调用静态图"));
		Qt::WindowFlags flags = Qt::Dialog;
		flags |= Qt::WindowMinMaxButtonsHint;
		flags |= Qt::WindowCloseButtonHint;
		m_hostDialog->setWindowFlags(flags);
		m_hostDialog->resize(1280, 720);
		m_hostDialog->setStyleSheet("FuncStaticStack{border:1px solid red;}");

		QHBoxLayout* layout = new QHBoxLayout;
		m_hostDialog->setLayout(layout);
		layout->setContentsMargins(1, 0, 1, 0);
		layout->setSpacing(10);

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
		m_tableLogInfo = new QTableWidget(0, headerTags.size(), m_hostDialog);
		layout->addWidget(m_tableLogInfo);
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