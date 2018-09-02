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
		m_stacks_ui->horizontalHeader()->setVisible(true);
		m_stacks_ui->verticalHeader()->setVisible(true);
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

void FuncStackui::PushStack(const string& process_name, const string& threadid, const string& func_name)
{
	int process_row = 0;
	for (; process_row < m_stacks_ui->rowCount(); process_row++)
	{
		QTableWidget* process_stacks = qobject_cast<QTableWidget*>(m_stacks_ui->cellWidget(process_row, 0));
		if (process_stacks->item(0, 0)->text().toStdString() == process_name)
		{
			break;
		}
	}
	// 添加进程
	if (process_row == m_stacks_ui->rowCount())
	{
		m_stacks_ui->insertRow(process_row);
		QTableWidget* process_stacks = new QTableWidget(2, 1);
		m_stacks_ui->setCellWidget(process_row, 0, process_stacks);
		QTableWidgetItem* item = new QTableWidgetItem(process_name.c_str());
		process_stacks->setItem(0, 0, item);
	}
	QTableWidget* process_stacks = qobject_cast<QTableWidget*>(m_stacks_ui->cellWidget(process_row, 0));
	int thread_column = 0;
	for (; thread_column < process_stacks->columnCount(); thread_column++)
	{
		QListWidget* thread_stacks = qobject_cast<QListWidget*>(process_stacks->cellWidget(1, thread_column));
		if (thread_stacks == nullptr || thread_stacks->windowTitle().toStdString() == threadid)
		{
			break;
		}
	}
	if (thread_column == process_stacks->columnCount())
	{
		process_stacks->insertColumn(thread_column);
	}
	QListWidget* thread_stacks = qobject_cast<QListWidget*>(process_stacks->cellWidget(1, thread_column));
	// 添加线程
	if (thread_stacks == nullptr)
	{
		thread_stacks = new QListWidget();
		process_stacks->setCellWidget(1, thread_column, thread_stacks);
		thread_stacks->setWindowTitle(threadid.c_str());
	}
	thread_stacks->addItem(func_name.c_str());
}

void FuncStackui::PopStack(const string& process_name, const string& threadid, const string& func_name)
{

}