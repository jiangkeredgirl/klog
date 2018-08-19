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
				string func_path = track_entry->modulename + track_entry->filename + track_entry->funcname + to_string(track_entry->line);
				m_stacks[track_entry->processname][track_entry->threadid].push_back(make_pair(track_entry->index, func_path));
			}
			else if (track_entry->functrack == "<<")
			{
				if (m_stacks[track_entry->processname][track_entry->threadid].empty())
				{
					break;
				}
				string func_path = track_entry->modulename + track_entry->filename + track_entry->funcname + to_string(track_entry->line);
				list<pair<__int64/*logindex*/, string/*func_path*/>>::iterator pop_iter = --m_stacks[track_entry->processname][track_entry->threadid].end();
				if (track_entry->index != pop_iter->first)
				{
					break;
				}
				if (func_path != pop_iter->second)
				{
					break;
				}
				m_stacks[track_entry->processname][track_entry->threadid].erase(pop_iter);
			}
		} while (false);
	}
}