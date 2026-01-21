#include "stdafx.h"
#include "funcstack.h"

FuncStack::FuncStack(QWidget *parent)
	: QDialog(parent)
{
	m_ui.setupUi(this);
}

FuncStack::~FuncStack()
{
}

void FuncStack::closeEvent(QCloseEvent *e)
{
	emit SignalCloseDialog(tr(u8"函数调用栈").toStdString());
}

void FuncStack::SlotReceiveTrack(shared_ptr<TraceEntry> track_entry, LogFileStatus status)
{
	if (status == LogFileStatus::LogFileReadBegin)
	{
		m_stacks.clear();
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
				PushStack(track_entry);
			}
			else if (track_entry->functrack == "<<")
			{
				if (m_stacks[track_entry->processname][track_entry->threadid].empty())
				{
					break;
				}
				list<shared_ptr<TraceEntry>>::iterator pop_iter = --m_stacks[track_entry->processname][track_entry->threadid].end();
				if (!IsPairTrack(*pop_iter, track_entry))
				{
					break;
				}
				m_stacks[track_entry->processname][track_entry->threadid].erase(pop_iter);
				PopStack(track_entry);
			}
		} while (false);
	}
}

void FuncStack::PushStack(shared_ptr<TraceEntry> track_entry)
{
	if (track_entry)
	{
		m_ui.PushStack(track_entry->processname, track_entry->threadid, track_entry->funcname);
	}
}

void FuncStack::PopStack(shared_ptr<TraceEntry> track_entry)
{
	if (track_entry)
	{
		m_ui.PopStack(track_entry->processname, track_entry->threadid, track_entry->funcname);
	}
}

bool FuncStack::IsPairTrack(shared_ptr<TraceEntry> push_track_entry, shared_ptr<TraceEntry> pop_track_entry)
{
	bool is_pair = false;
	if (push_track_entry
		&& pop_track_entry
		&& push_track_entry->index == pop_track_entry->index
		&& push_track_entry->modulename == pop_track_entry->modulename
		&& push_track_entry->filename == pop_track_entry->filename
		&& push_track_entry->funcname == pop_track_entry->funcname
		&& push_track_entry->line == pop_track_entry->line)
	{
		is_pair = true;
	}
	return is_pair;
}

bool FuncStack::IsExistTrack(shared_ptr<TraceEntry> old_track_entry, shared_ptr<TraceEntry> new_track_entry)
{
	bool is_exist = false;
	if (old_track_entry
		&& new_track_entry
		//&& push_track_entry->index == pop_track_entry->index
		&& old_track_entry->modulename == new_track_entry->modulename
		&& old_track_entry->filename == new_track_entry->filename
		&& old_track_entry->funcname == new_track_entry->funcname
		&& old_track_entry->line == new_track_entry->line)
	{
		is_exist = true;
	}
	return is_exist;
}