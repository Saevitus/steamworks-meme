#pragma once

#include "Utilities.h"
#include <Windows.h>
#include <TlHelp32.h>

namespace Memory
{

	// basic module structure, used to store the size of the module
	// the base address of the module, and also some simple getters
	// for both
	struct Module
	{
	protected: // protected because I might access it in a sub struct
		// m_ prefix because it's a MEMBER of the Module struct
		DWORD m_dwBase, m_dwSize;

	public: // public because we wanna use these outside of this struct
		// initializing m_dwBase and m_dwSize as NULL, for safety purposes
		Module() { m_dwSize = m_dwBase = 0x0; }

		// used to return modBaseAddr and modBaseSize from the MODULEENTRY32 struct
		// into this struct, so we can access it and use it
		Module(DWORD dwBase, DWORD dwSize) { this->m_dwBase = dwBase; this->m_dwSize = dwSize; }

		// simple accessors incase we want to view/use either of m_dwBase or m_dwSize
		// outside of this structure
		DWORD GetBase() { return this->m_dwBase; }
		DWORD GetSize() { return this->m_dwSize; }

	};

	// process class, used to attach, find modules, read memory, etc.
	class Process
	{
	protected: // protected because I might access it in a sub class
		// m_ prefix because it's a MEMBER of the Process class
		DWORD m_dwProcessID;
		HANDLE m_hProcess;

	public: // public because we wanna use these outside of this struct
		// empty constructor idk
		Process() {  }

		// simple constructor that works in conjunction with AttachToProcess()
		Process(std::string strName) { this->AttachToProcess(strName); }

		// uses FindProcess() to get the processID of said process, then proceeds
		// to open and store a handle in m_hProcess, for later use
		void AttachToProcess(std::string strName);

		// find the processID of the input process name, which can be used later
		// to open handles, etc.
		bool FindProcess(std::string strName);

		// uses the processID from FindProcess() to take a snapshot of the process,
		// and then proceeds to search for the module, once found it will return
		// the needed information back to the Module structure
		Module FindModule(std::string strName);

		// simple accessors for m_dwProcessID and m_hProcess
		DWORD GetPID() { return this->m_dwProcessID; }
		HANDLE GetHandle() { return this->m_hProcess; }

		// simple wrappers for ReadProcessMemory and WriteProcessMemory
		bool ReadMemory(DWORD dwAddress, PVOID pvDestination, DWORD dwSize);
		bool WriteMemory(DWORD dwAddress, PVOID pvData, DWORD dwSize);

		// using templates to make it easier with reading different types,
		// due to the different sizes
		template <typename T> 
		T ReadMemory(DWORD dwAddress)
		{
			T tData;
			ReadMemory(dwAddress, &tData, sizeof(T));
			return tData;
		}
		
		// using templates to make it easier with reading different types,
		// due to the different sizes
		template <typename T>
		T WriteMemory(DWORD dwAddress, T tData)
		{
			WriteMemory(dwAddress, &tData, sizeof(T));
			return tData;
		}

	};
}