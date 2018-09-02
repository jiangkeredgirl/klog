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
	
		m_stacks_list = new QListWidget();
		layout->addWidget(m_stacks_list);
		m_stacks_list->setStyleSheet("QListWidget{border:1px solid red; margin:0px;}");
		m_stacks_list->setResizeMode(QListWidget::Adjust);
		m_stacks_list->installEventFilter(this);
	}
}

void FuncStackui::PushStack(const string& process_name, const string& threadid, const string& func_name)
{
	int process_row = 0;
	for (; process_row < m_stacks_list->count(); process_row++)
	{
		QTableWidget* process_stacks = qobject_cast<QTableWidget*>(m_stacks_list->itemWidget(m_stacks_list->item(process_row)));
		if (process_stacks->item(0, 0)->text().toStdString() == process_name)
		{
			break;
		}
	}
	// 添加进程
	if (process_row == m_stacks_list->count())
	{
		QListWidgetItem *item = new QListWidgetItem();
		m_stacks_list->addItem(item);
		item->setSizeHint(QSize(m_stacks_list->size().width(), m_stacks_list->size().height() / m_stacks_list->count()));
		QTableWidget* process_stacks = new QTableWidget(2, 1);
		m_stacks_list->setItemWidget(item, process_stacks);
		process_stacks->setItem(0, 0, new QTableWidgetItem(process_name.c_str()));
	}
	QTableWidget* process_stacks = qobject_cast<QTableWidget*>(m_stacks_list->itemWidget(m_stacks_list->item(process_row)));
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

bool FuncStackui::eventFilter(QObject *target, QEvent *event)
{
	if (target == m_stacks_list && event->type() == QEvent::Resize)
	{
		for (int i = 0; i < m_stacks_list->count(); i++)
		{
			m_stacks_list->item(i)->setSizeHint(QSize(m_stacks_list->size().width(), m_stacks_list->size().height() / m_stacks_list->count()));
		}
	}
	return QObject::eventFilter(target, event);
}