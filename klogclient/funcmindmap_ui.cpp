#include "funcmindmap_ui.h"

FuncMindMapui::FuncMindMapui()
	: QObject()
{
}

FuncMindMapui::~FuncMindMapui()
{
}

void FuncMindMapui::setupUi(QDialog* hostDialog)
{
	m_hostDialog = hostDialog;
	if (m_hostDialog)
	{
		m_hostDialog->setWindowTitle(tr(u8"函数调用流"));
		Qt::WindowFlags flags = Qt::Dialog;
		flags |= Qt::WindowMinMaxButtonsHint;
		flags |= Qt::WindowCloseButtonHint;
		m_hostDialog->setWindowFlags(flags);
		m_hostDialog->resize(1280, 720);
		m_hostDialog->setStyleSheet("FuncMindMap{border:1px solid red;}");

		QHBoxLayout* layout = new QHBoxLayout;
		m_hostDialog->setLayout(layout);
		layout->setContentsMargins(1, 0, 1, 0);
		layout->setSpacing(10);

		m_trees_list = new QListWidget();
		layout->addWidget(m_trees_list);
		m_trees_list->setStyleSheet("QListWidget{border:1px solid red; margin:0px;}");
		m_trees_list->setResizeMode(QListWidget::Adjust);
		m_trees_list->setWindowTitle("trees");
		m_trees_list->installEventFilter(this);
	}
}

void FuncMindMapui::FuncStacksAddInTrees(const string& process_name, const string& threadid, list<string>& func_stacks)
{
	int process_row = 0;
	for (; process_row < m_trees_list->count(); process_row++)
	{
		QTableWidget* process_stacks = qobject_cast<QTableWidget*>(m_trees_list->itemWidget(m_trees_list->item(process_row)));
		if (process_stacks->item(0, 0)->text().toStdString() == process_name)
		{
			break;
		}
	}
	// 添加进程
	if (process_row == m_trees_list->count())
	{
		QListWidgetItem *item = new QListWidgetItem();
		m_trees_list->addItem(item);
		qDebug() << "m_trees_list->contentsRect() = " << m_trees_list->contentsRect();
		item->setSizeHint(QSize(m_trees_list->contentsRect().width(), m_trees_list->contentsRect().height() / m_trees_list->count()));
		QTableWidget* process_stacks = new QTableWidget(3, 1);
		process_stacks->setStyleSheet("QTableWidget{border:1px solid red; margin:0px;}");
		process_stacks->setStyleSheet("QTableWidget::item{border:1px solid red; margin:0px}");
		m_trees_list->setItemWidget(item, process_stacks);
		process_stacks->setItem(0, 0, new QTableWidgetItem(process_name.c_str()));
		process_stacks->item(0, 0)->setTextAlignment(Qt::AlignCenter);
		process_stacks->horizontalHeader()->setVisible(false);
		process_stacks->verticalHeader()->setVisible(false);
		qDebug() << "item->sizeHint() = " << item->sizeHint();
		process_stacks->resize(item->sizeHint());
		process_stacks->setRowHeight(2, process_stacks->contentsRect().height() - process_stacks->rowHeight(0) - process_stacks->rowHeight(1));
	}
	QTableWidget* process_stacks = qobject_cast<QTableWidget*>(m_trees_list->itemWidget(m_trees_list->item(process_row)));
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
	QTreeWidget* thread_tree = qobject_cast<QTreeWidget*>(process_stacks->cellWidget(2, thread_column));
	// 添加线程
	if (thread_tree == nullptr)
	{
		process_stacks->setItem(1, 0, new QTableWidgetItem(threadid.c_str()));
		process_stacks->item(1, 0)->setTextAlignment(Qt::AlignCenter);
		thread_tree = new QTreeWidget();
		thread_tree->setStyleSheet("QTreeWidget{border:1px solid red; margin:0px;}");
		thread_tree->setHeaderLabel(u8"函数流");
		thread_tree->setHeaderHidden(true);
		process_stacks->setCellWidget(2, thread_column, thread_tree);
		process_stacks->setColumnWidth(thread_column, process_stacks->contentsRect().width() / process_stacks->columnCount());
	}
	FuncStacksAddInTree(func_stacks, thread_tree);
}

void FuncMindMapui::FuncStacksAddInTree(list<string>& func_stacks, QTreeWidget* thread_tree)
{
	int treeCount = thread_tree->topLevelItemCount();
	int treeIndex = 0;
	for (treeIndex = 0; treeIndex < treeCount; treeIndex++)
	{
		if (thread_tree->topLevelItem(treeIndex)->text(0).toStdString() == *func_stacks.begin())
		{
			break;
		}
	}
	if (treeIndex == treeCount)
	{
		QTreeWidgetItem* pItem = new QTreeWidgetItem();
		pItem->setText(0, func_stacks.begin()->c_str());
		thread_tree->addTopLevelItem(pItem);
	}
	func_stacks.pop_front();
	AddItem(thread_tree, thread_tree->topLevelItem(treeIndex), func_stacks);
}

void FuncMindMapui::AddItem(QTreeWidget* thread_tree, QTreeWidgetItem* parentItem, list<string>& func_stacks)
{
	if (!func_stacks.empty())
	{
		int childIndex = 0;
		for (childIndex = 0; childIndex < parentItem->childCount(); childIndex++)
		{
			if (parentItem->child(childIndex)->text(0).toStdString() == *func_stacks.begin())
			{
				break;
			}
		}
		if (childIndex == parentItem->childCount())
		{
			QTreeWidgetItem* pItem = new QTreeWidgetItem();
			pItem->setText(0, func_stacks.begin()->c_str());
			parentItem->addChild(pItem);
			thread_tree->resizeColumnToContents(0);
		}
		func_stacks.pop_front();
		AddItem(thread_tree, parentItem->child(childIndex), func_stacks);		
	}
}