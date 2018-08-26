#include "funcstackui.h"

FuncStackui::FuncStackui()
	: QObject()
{
}

FuncStackui::~FuncStackui()
{
}

void FuncStackui::setupUi(QDialog* hostDialog)
{
	m_hostDialog = hostDialog;
	if (m_hostDialog)
	{
		m_hostDialog->setWindowTitle(tr(u8"函数调用实时图"));
		Qt::WindowFlags flags = Qt::Dialog;
		flags |= Qt::WindowMinMaxButtonsHint;
		flags |= Qt::WindowCloseButtonHint;
		m_hostDialog->setWindowFlags(flags);
		m_hostDialog->resize(1280, 720);
		m_hostDialog->setStyleSheet("FuncStack{border:1px solid red;}");

		QHBoxLayout* layout = new QHBoxLayout;
		m_hostDialog->setLayout(layout);
		layout->setContentsMargins(1, 0, 1, 0);
		layout->setSpacing(10);

		QStringList headerTags = {"function stacks"};
		m_tableFuncStacks = new QTableWidget(0, headerTags.size(), m_hostDialog);
		layout->addWidget(m_tableFuncStacks);
		m_tableFuncStacks->setHorizontalHeaderLabels(headerTags);
		m_tableFuncStacks->horizontalHeader()->setFixedHeight(30);
		m_tableFuncStacks->horizontalHeader()->setVisible(false);
		m_tableFuncStacks->verticalHeader()->setVisible(false);
		m_tableFuncStacks->setStyleSheet("QTableWidget{border:1px solid red; margin:0px;}");
		m_tableFuncStacks->horizontalHeader()->setStyleSheet("QHeaderView{border:none; border-bottom:1px solid red;}");
		m_tableFuncStacks->setEditTriggers(QAbstractItemView::NoEditTriggers);
		m_tableFuncStacks->setSelectionBehavior(QAbstractItemView::SelectRows);
		m_tableFuncStacks->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
		m_tableFuncStacks->horizontalHeader()->setSectionsMovable(true);
		m_tableFuncStacks->horizontalHeader()->setHighlightSections(false);
		m_tableFuncStacks->horizontalHeader()->setStretchLastSection(true);
	}
}