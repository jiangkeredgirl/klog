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
		m_stacks_ui = new QTableWidget(0, headerTags.size(), m_hostDialog);
		layout->addWidget(m_stacks_ui);
		m_stacks_ui->setHorizontalHeaderLabels(headerTags);
		m_stacks_ui->horizontalHeader()->setFixedHeight(30);
		m_stacks_ui->horizontalHeader()->setVisible(false);
		m_stacks_ui->verticalHeader()->setVisible(false);
		m_stacks_ui->setStyleSheet("QTableWidget{border:1px solid red; margin:0px;}");
		m_stacks_ui->horizontalHeader()->setStyleSheet("QHeaderView{border:none; border-bottom:1px solid red;}");
		m_stacks_ui->setEditTriggers(QAbstractItemView::NoEditTriggers);
		m_stacks_ui->setSelectionBehavior(QAbstractItemView::SelectRows);
		m_stacks_ui->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
		m_stacks_ui->horizontalHeader()->setSectionsMovable(true);
		m_stacks_ui->horizontalHeader()->setHighlightSections(false);
		m_stacks_ui->horizontalHeader()->setStretchLastSection(true);
	}
}

void FuncStackui::PushStack(const string& proccess_name, const string& threadid, const string& func_name)
{
	size_t i = 0;
	for (; i < m_stacks_ui->rowCount(); i++)
	{
		QTableWidget* proccess_stacks = qobject_cast<QTableWidget*>(m_stacks_ui->cellWidget(i, 0));
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