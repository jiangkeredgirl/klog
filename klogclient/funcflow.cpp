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
				FuncPath func_path;
				func_path.logindex = track_entry->index;
				func_path.modulename = track_entry->modulename;
				func_path.filename = track_entry->filename;
				func_path.funcname = track_entry->funcname;
				func_path.line = track_entry->line;
				m_stacks[track_entry->processname][track_entry->threadid].push_back(func_path);
				m_stacks_end[track_entry->processname][track_entry->threadid] = false;
			}
			else if (track_entry->functrack == "<<")
			{
				if (m_stacks[track_entry->processname][track_entry->threadid].empty())
				{
					break;
				}
				FuncPath func_path;
				func_path.logindex = track_entry->index;
				func_path.modulename = track_entry->modulename;
				func_path.filename = track_entry->filename;
				func_path.funcname = track_entry->funcname;
				func_path.line = track_entry->line;
				list<FuncPath/*func_path*/>::iterator pop_iter = --m_stacks[track_entry->processname][track_entry->threadid].end();
				if (func_path != *pop_iter)
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

void FuncFlow::FuncStacksAddInTrees(const string& process_name, const string& threadid, list<FuncPath>& func_stacks)
{
	FuncStacksAddInTree(func_stacks, m_func_trees[process_name][threadid]);
}

void FuncFlow::FuncStacksAddInTree(list<FuncPath>& func_stacks, list<FuncTree>& _func_trees)
{
	auto & func_trees = _func_trees;	
	for (auto & func_path : func_stacks)
	{
		bool exist = false;
		func_path.logindex = 0;		
		for (auto & tree : func_trees)
		{
			if (func_path == tree.func_path)
			{
				func_trees = tree.branchs;
				exist = true;
				break;
			}
		}
		if (exist == false)
		{
			FuncTree tree;
			tree.func_path = func_path;
			func_trees.push_back(tree);
			func_trees = tree.branchs;
		}
	}
}