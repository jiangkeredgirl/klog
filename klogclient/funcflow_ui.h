#pragma once

#include <QObject>
#include "qtstandard.h"
#include "cstandard.h"

class FuncFlowui : public QObject
{
	Q_OBJECT

public:
	FuncFlowui();
	~FuncFlowui();

public:
	void setupUi(QDialog* hostDialog);

public:
	void FuncStacksAddInTrees(const string& process_name, const string& threadid, list<string>& func_stacks);
	void FuncStacksAddInTree(list<string>& func_stacks, QTreeWidget* thread_tree);
	void AddItem(QTreeWidget* thread_tree, QTreeWidgetItem* parentItem, list<string>& func_stacks);

public:
	QDialog*  m_hostDialog = nullptr;
	QListWidget* m_trees_list = nullptr;
};
