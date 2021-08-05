#include "ProcessManagement.hpp"

namespace Engine
{
	void ProcessManagement::Display()
	{
		this->processes[pid]->Display();
	}

	void ProcessManagement::Special(int key, int x,  int y)
	{
		this->processes[pid]->Special(key, x, y);
	}

	void ProcessManagement::OnKeyDown(unsigned char key, int x, int y)
	{
		this->processes[pid]->OnKeyDown(key, x, y);
	}

	void ProcessManagement::OnMouseClick(int button, int state, int x, int y)
	{
		this->processes[pid]->OnMouseClick(button, state, x, y);
	}

	void ProcessManagement::Time(int t)
	{
		this->processes[pid]->Time(t);
	}

	void ProcessManagement::setProcess(size_t pid)
	{
		this->pid = pid;
	}

	void ProcessManagement::deleteProcess(size_t pid)
	{
		this->processes[pid].reset();
	}

	void ProcessManagement::resetProcess()
	{
		for (auto& i : this->processes)
			i.reset();
		this->createProcess(this);
	}

	void ProcessManagement::Next()
	{
		if (this->processes.size() >= this->pid)
			this->pid++;
	}

}