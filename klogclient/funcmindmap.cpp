#include "funcmindmap.h"

// 获取最后一个元素的迭代器（通用版本）
template<typename List>
auto getLastIterator(List& lst) -> decltype(lst.end()) {
	static_assert(std::is_same<typename List::value_type,
		typename std::decay<decltype(*lst.begin())>::type>::value,
		"Container must support bidirectional iteration");

	if (lst.empty()) {
		return lst.end();
	}
	return std::prev(lst.end());
}

// 常量版本
template<typename List>
auto getLastConstIterator(const List& lst) -> decltype(lst.cend()) {
	if (lst.empty()) {
		return lst.cend();
	}
	return std::prev(lst.cend());
}

FuncMindMap::FuncMindMap(QWidget *parent)
	: QDialog(parent)
{
	m_ui.setupUi(this);
}

FuncMindMap::~FuncMindMap()
{
}

void FuncMindMap::closeEvent(QCloseEvent *e)
{
	emit SignalCloseDialog(tr("函数思维图").toStdString());
}

void FuncMindMap::SlotReceiveTrack(shared_ptr<TraceEntry> track_entry, LogFileStatus status)
{
	if (status == LogFileStatus::LogFileReadBegin)
	{
		m_func_stacks.clear();
		m_func_trees.clear();
	}
	else if (status == LogFileStatus::LogFileReadEnd)
	{
	}
	else if (status == LogFileStatus::LogFileReading)
	{
		do
		{
			if (track_entry == nullptr)
			{
				break;
			}
			if (!track_entry->is_track)
			{
				break;
			}
			if (track_entry->processname.empty())
			{
				break;
			}
			if (track_entry->threadid.empty())
			{
				break;
			}
			if (track_entry->index < 0)
			{
				break;
			}
			AddFuncStack(track_entry);
			AddFuncTree(track_entry);
		} while (false);
	}
}

void FuncMindMap::AddFuncStack(shared_ptr<TraceEntry> track_entry)
{
	do
	{
		if (track_entry->functrack == ">>")
		{
			m_func_stacks[track_entry->processname][track_entry->threadid].push_back(track_entry);
		}
		else if (track_entry->functrack == "<<")
		{
			auto last_ptr = GetPairTrack(track_entry, m_func_stacks[track_entry->processname][track_entry->threadid]);
			if (last_ptr)
			{
				m_func_stacks[track_entry->processname][track_entry->threadid].pop_back();
			}			
		}
	} while (false);
}

void FuncMindMap::AddFuncTree(shared_ptr<TraceEntry> track_entry)
{
	do
	{
		if (track_entry->functrack == ">>")
		{
			std::shared_ptr<FuncTreeNode> func_node = std::make_shared<FuncTreeNode>();
			func_node->func_trace = track_entry;
			func_node->is_calling = true;
			auto calling_ptr = GetCallingTrack(m_func_trees[track_entry->processname][track_entry->threadid]);
			if (calling_ptr)
			{
				func_node->parent = &(*calling_ptr);
				calling_ptr->branchs.push_back(func_node);
				m_ui.addFuncTreeNodeBranch(calling_ptr, func_node);
			}
			else
			{
				func_node->parent = nullptr;
				m_func_trees[track_entry->processname][track_entry->threadid].push_back(func_node);
				m_ui.addRootFuncTreeNodes(func_node);
			}
		}
		else if (track_entry->functrack == "<<")
		{
			auto last_ptr = GetPairTrack(track_entry, m_func_trees[track_entry->processname][track_entry->threadid]);
			if (last_ptr)
			{
				last_ptr->is_calling = false;
				m_ui.updateFuncTreeNodeWidgetItem(last_ptr);
			}			
		}
	} while (false);
	//FuncStacksAddInTrees(track_entry->processname, track_entry->threadid, m_stacks[track_entry->processname][track_entry->threadid]);
}

void FuncMindMap::FuncStacksAddInTrees(const string& process_name, const string& threadid, list<shared_ptr<TraceEntry>>& func_stacks)
{
	FuncStacksAddInTree(func_stacks, m_func_trees[process_name][threadid]);
	list<string> stacks;
	for (auto item : func_stacks)
	{
		stacks.push_back(item->funcname);
	}
	m_ui.FuncStacksAddInTrees(process_name, threadid, stacks);
}

void FuncMindMap::FuncStacksAddInTree(list<shared_ptr<TraceEntry>>& func_stacks, list<shared_ptr<FuncTreeNode>>& _func_trees)
{
	list<shared_ptr<FuncTreeNode>>* func_trees = &_func_trees;
	for (auto & func_node : func_stacks)
	{
		bool exist = false;
		for (auto & tree : *func_trees)
		{
			if (FuncStack::IsExistTrack(tree->func_trace, func_node))
			{
				func_trees = &tree->branchs;
				exist = true;
				break;
			}
		}
		if (exist == false)
		{
			shared_ptr<FuncTreeNode> tree(new FuncTreeNode());
			tree->func_trace = func_node;
			func_trees->push_back(tree);
			func_trees = &tree->branchs;
		}
	}
}

shared_ptr<TraceEntry> FuncMindMap::GetPairTrack(shared_ptr<TraceEntry> track_entry, list<shared_ptr<TraceEntry>>& track_stacks)
{
	shared_ptr<TraceEntry> pair_ptr = nullptr;
	do
	{
		if (track_stacks.empty())
		{
			break;
		}
		auto last_iter = track_stacks.rbegin();
		if (!FuncStack::IsPairTrack(*last_iter, track_entry))
		{
			break;
		}
		pair_ptr = *last_iter;
	} while (false);
	return pair_ptr;
}

shared_ptr<FuncTreeNode>   FuncMindMap::GetPairTrack(shared_ptr<TraceEntry> track_entry, list<shared_ptr<FuncTreeNode>>& track_trees)
{
	shared_ptr<FuncTreeNode> pair_ptr = nullptr;
	do
	{
		if (track_trees.empty())
		{
			break;
		}
		// 反向迭代器遍历
		for (auto it = track_trees.rbegin(); it != track_trees.rend(); ++it)
		{
			auto branch_pair_ptr = GetPairTrack(track_entry, (*it)->branchs);
			if (branch_pair_ptr)
			{
				pair_ptr = branch_pair_ptr;
				break;
			}
			if (FuncStack::IsPairTrack((*it)->func_trace, track_entry) && (*it)->is_calling)
			{
				pair_ptr = *it;
				break;
			}
		}
	} while (false);
	return pair_ptr;
}

shared_ptr<FuncTreeNode>   FuncMindMap::GetCallingTrack(list<shared_ptr<FuncTreeNode>>& track_trees)
{
	shared_ptr<FuncTreeNode> calling_ptr = nullptr;
	do
	{
		if (track_trees.empty())
		{
			break;
		}
		// 反向迭代器遍历
		for (auto it = track_trees.rbegin(); it != track_trees.rend(); ++it)
		{
			auto branch_calling_ptr = GetCallingTrack((*it)->branchs);
			if (branch_calling_ptr)
			{
				calling_ptr = branch_calling_ptr;
				break;
			}
			if ((*it)->is_calling)
			{
				calling_ptr = *it;
				break;
			}
		}
	} while (false);
	return calling_ptr;
}
