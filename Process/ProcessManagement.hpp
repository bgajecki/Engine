#pragma once

#include "Process.hpp"

namespace Engine
{
	typedef std::array<std::unique_ptr<Process>, constants::Engine::SIZE_OF_PROCESS_ARRAY> ProcessArray;

	class ProcessManagement final // Process manager class
	{
	public:
		ProcessManagement() = default;
		~ProcessManagement() = default;

		void Display();
		void Special(int, int, int);
		void OnKeyDown(unsigned char, int, int);
		void OnMouseClick(int, int, int, int);
		void Time(int);

		template<typename T>
		int addProcess()
		{
			for (unsigned i = 0; i < this->processes.size(); i++)
			{
				if (!this->processes[i])
				{
					this->processes[i].reset(new T(this));
					return static_cast<int>(i);
				}
			}
			return -1;
		}

		void setProcess(size_t);
		void deleteProcess(size_t);

		void resetProcess();
		std::function<void(ProcessManagement*)> createProcess; // Create processes after reset

		void Next();
		
	private:
		size_t pid;
		ProcessArray processes;
	};

	class ProcessWithPointer : public Process // Process with pointer to the process managment class
	{
	public:
		ProcessWithPointer(void* ptr)
			: processManagement(reinterpret_cast<ProcessManagement*>(ptr))
		{}
		ProcessManagement* processManagement;
	};
}