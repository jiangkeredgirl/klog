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
		m_tableStacks = new QTableWidget(0, headerTags.size(), m_hostDialog);
		layout->addWidget(m_tableStacks);
		m_tableStacks->setHorizontalHeaderLabels(headerTags);
		m_tableStacks->horizontalHeader()->setFixedHeight(30);
		m_tableStacks->horizontalHeader()->setVisible(false);
		m_tableStacks->verticalHeader()->setVisible(false);
		m_tableStacks->setStyleSheet("QTableWidget{border:1px solid red; margin:0px;}");
		m_tableStacks->horizontalHeader()->setStyleSheet("QHeaderView{border:none; border-bottom:1px solid red;}");
		m_tableStacks->setEditTriggers(QAbstractItemView::NoEditTriggers);
		m_tableStacks->setSelectionBehavior(QAbstractItemView::SelectRows);
		m_tableStacks->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
		m_tableStacks->horizontalHeader()->setSectionsMovable(true);
		m_tableStacks->horizontalHeader()->setHighlightSections(false);
		m_tableStacks->horizontalHeader()->setStretchLastSection(true);
	}
}

void FuncStackui::PushStack(const string& proccess_name, const string& threadid, const string& func_name)
{
	size_t i = 0;
	for (; i < m_tableStacks->rowCount(); i++)
	{
		QTableWidget* proccess_stacks = qobject_cast<QTableWidget*>(m_tableStacks->cellWidget(i, 0));
		if (proccess_stacks->item(0, 0)->text().toStdString() == proccess_name)
		{
			size_t j = 0;
			for (; j < proccess_stacks->columnCount(); j++)
			{
				QListWidget* thread_stacks = qobject_cast<QListWidget*>(proccess_stacks->cellWidget(1, j));
				if (thread_stacks->windowTitle().toStdString() == threadid)
				{
					thread_stacks->addItem(func_name.c_str());
				}
			}
		}
	}
}

void FuncStackui::PopStack(const string& proccess_name, const string& threadid, const string& func_name)
{

}