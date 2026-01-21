#include "stdafx.h"
#include "funcflow.h"

FuncFlow::FuncFlow(QWidget *parent)
	: QDialog(parent)
{
	m_ui.setupUi(this);
}

FuncFlow::~FuncFlow()
{
}

void FuncFlow::closeEvent(QCloseEvent *e)
{
	emit SignalCloseDialog(tr(u8"函数调用流").toStdString());
}

void FuncFlow::SlotReceiveTrack(shared_ptr<TraceEntry> track_entry, LogFileStatus status)
{
	if (status == LogFileStatus::LogFileReadBegin)
	{
		m_stacks.clear();
		m_stacks_end.clear();
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
			if (track_entry->functrack == ">>")
			{
				m_stacks[track_entry->processname][track_entry->threadid].push_back(track_entry);
				m_stacks_end[track_entry->processname][track_entry->threadid] = false;
			}
			else if (track_entry->functrack == "<<")
			{
				if (m_stacks[track_entry->processname][track_entry->threadid].empty())
				{
					break;
				}
				list<shared_ptr<TraceEntry>/*func_path*/>::iterator pop_iter = --m_stacks[track_entry->processname][track_entry->threadid].end();
				if (!FuncStack::IsPairTrack(*pop_iter, track_entry))
				{
					break;
				}
				if (m_stacks_end[track_entry->processname][track_entry->threadid] == false)
				{
					m_stacks_end[track_entry->processname][track_entry->threadid] = true;
					FuncStacksAddInTrees(track_entry->processname, track_entry->threadid, m_stacks[track_entry->processname][track_entry->threadid]);
				}
				m_stacks[track_entry->processname][track_entry->threadid].erase(pop_iter);
			}
		} while (false);
	}
}

void FuncFlow::FuncStacksAddInTrees(const string& process_name, const string& threadid, list<shared_ptr<TraceEntry>>& func_stacks)
{
	FuncStacksAddInTree(func_stacks, m_func_trees[process_name][threadid]);
	list<string> stacks;
	for (auto item : func_stacks)
	{
		stacks.push_back(item->funcname);
	}
	m_ui.FuncStacksAddInTrees(process_name, threadid, stacks);
}

void FuncFlow::FuncStacksAddInTree(list<shared_ptr<TraceEntry>>& func_stacks, list<shared_ptr<FuncTree>>& _func_trees)
{
	list<shared_ptr<FuncTree>>* func_trees = &_func_trees;
	for (auto & func_path : func_stacks)
	{
		bool exist = false;
		for (auto & tree : *func_trees)
		{
			if (FuncStack::IsExistTrack(tree->func_path, func_path))
			{
				func_trees = &tree->branchs;
				exist = true;
				break;
			}
		}
		if (exist == false)
		{
			shared_ptr<FuncTree> tree(new FuncTree());
			tree->func_path = func_path;
			func_trees->push_back(tree);
			func_trees = &tree->branchs;
		}
	}
}