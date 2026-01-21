#include "stdafx.h"
#include "funcstack_ui.h"

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
		m_hostDialog->setWindowTitle(tr(u8"函数调用栈"));
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
		m_stacks_list->setWindowTitle("stacks");
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
		qDebug() << "m_stacks_list->contentsRect() = " << m_stacks_list->contentsRect() << ", m_stacks_list->count() = " << m_stacks_list->count();
		item->setSizeHint(QSize(m_stacks_list->contentsRect().width(), m_stacks_list->contentsRect().height() / m_stacks_list->count()));
		QTableWidget* process_stacks = new QTableWidget(3, 1);
		process_stacks->setStyleSheet("QTableWidget{border:1px solid red; margin:0px;}");
		process_stacks->setStyleSheet("QTableWidget::item{border:1px solid red; margin:0px}");
		m_stacks_list->setItemWidget(item, process_stacks);
		process_stacks->setItem(0, 0, new QTableWidgetItem(process_name.c_str()));
		process_stacks->item(0, 0)->setTextAlignment(Qt::AlignCenter);
		process_stacks->horizontalHeader()->setVisible(false);
		process_stacks->verticalHeader()->setVisible(false);
		qDebug() << "item->sizeHint() = " << item->sizeHint();
		process_stacks->resize(item->sizeHint());
		//process_stacks->setRowHeight(0, 30);
		process_stacks->setRowHeight(2, process_stacks->contentsRect().height() - process_stacks->rowHeight(0) - process_stacks->rowHeight(1));
	}
	QTableWidget* process_stacks = qobject_cast<QTableWidget*>(m_stacks_list->itemWidget(m_stacks_list->item(process_row)));
	int thread_column = 0;
	for (; thread_column < process_stacks->columnCount(); thread_column++)
	{
		QTableWidgetItem* threadidItem = process_stacks->item(1, thread_column);
		if (threadidItem == nullptr || threadidItem->text().toStdString() == threadid)
		{
			break;
		}
	}
	if (thread_column == process_stacks->columnCount())
	{
		process_stacks->insertColumn(thread_column);
	}
	QListWidget* thread_stacks = qobject_cast<QListWidget*>(process_stacks->cellWidget(2, thread_column));
	// 添加线程
	if (thread_stacks == nullptr)
	{
		process_stacks->setItem(1, 0, new QTableWidgetItem(threadid.c_str()));
		process_stacks->item(1, 0)->setTextAlignment(Qt::AlignCenter);
		thread_stacks = new QListWidget();
		thread_stacks->setStyleSheet("QListWidget{border:1px solid red; margin:0px;}");
		process_stacks->setCellWidget(2, thread_column, thread_stacks);
		process_stacks->setColumnWidth(thread_column, process_stacks->contentsRect().width() / process_stacks->columnCount());
	}
	thread_stacks->addItem(func_name.c_str());
	thread_stacks->item(thread_stacks->count() - 1)->setTextAlignment(Qt::AlignCenter);
}

void FuncStackui::PopStack(const string& process_name, const string& threadid, const string& func_name)
{
	do
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
		if (process_row == m_stacks_list->count())
		{
			break;
		}
		QTableWidget* process_stacks = qobject_cast<QTableWidget*>(m_stacks_list->itemWidget(m_stacks_list->item(process_row)));
		int thread_column = 0;
		for (; thread_column < process_stacks->columnCount(); thread_column++)
		{
			QTableWidgetItem* threadidItem = process_stacks->item(1, thread_column);
			if (threadidItem && threadidItem->text().toStdString() == threadid)
			{
				break;
			}
		}
		if (thread_column == process_stacks->columnCount())
		{
			break;
		}
		QListWidget* thread_stacks = qobject_cast<QListWidget*>(process_stacks->cellWidget(2, thread_column));
		if (thread_stacks == nullptr)
		{
			break;
		}
		if (thread_stacks->item(thread_stacks->count() - 1)->text().toStdString() != func_name)
		{
			break;
		}
		thread_stacks->takeItem(thread_stacks->count() - 1);
	} while (false);
}

bool FuncStackui::eventFilter(QObject *target, QEvent *event)
{
	if (target == m_stacks_list && (event->type() == QEvent::Resize || event->type() == QEvent::Show))
	{
		for (int i = 0; i < m_stacks_list->count(); i++)
		{
			m_stacks_list->item(i)->setSizeHint(QSize(m_stacks_list->contentsRect().width(), m_stacks_list->contentsRect().height() / m_stacks_list->count()));
			QTableWidget* process_stacks = qobject_cast<QTableWidget*>(m_stacks_list->itemWidget(m_stacks_list->item(i)));
			if (process_stacks)
			{
				process_stacks->resize(m_stacks_list->item(i)->sizeHint());
				process_stacks->setRowHeight(2, process_stacks->contentsRect().height() - process_stacks->rowHeight(0) - process_stacks->rowHeight(1));
			}
		}
	}
	return QObject::eventFilter(target, event);
}