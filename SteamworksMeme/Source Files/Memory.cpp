#include "../Header Files/Memory.h"

using namespace Memory;

void Process::AttachToProcess(std::string strName)
{
	if (FindProcess(strName))
	{
		this->m_hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, this->m_dwProcessID);
	} else { Utilities::Log("Unable to attach to process: %s", strName.c_str()); }
}

bool Process::FindProcess(std::string strName)
{
	HANDLE hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	PROCESSENTRY32 procEntry;
	procEntry.dwSize = sizeof(PROCESSENTRY32);

	do if (strcmp(procEntry.szExeFile, strName.c_str()) == 0)
	{
		Utilities::Log("Found %s", strName.c_str());
		if (!this->m_dwProcessID)
		{
			this->m_dwProcessID = procEntry.th32ProcessID;
			Utilities::Log("Set Process ID");
		} else { Utilities::Log("Unable to set Process ID"); }

		CloseHandle(hProcess);
		return true;
	} while (Process32Next(hProcess, &procEntry));

	Utilities::Log("Unable to find process: %s", strName.c_str());

	return false;
}

Module Process::FindModule(std::string strName)
{
	HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, this->m_dwProcessID);
	MODULEENTRY32 modEntry;
	modEntry.dwSize = sizeof(MODULEENTRY32);

	do if (strcmp(modEntry.szModule, strName.c_str()) == 0)
	{
		CloseHandle(hModule);
		return Module(reinterpret_cast<DWORD>(modEntry.modBaseAddr), modEntry.modBaseSize);
	} while (Module32Next(hModule, &modEntry));

	return Module();
}

bool Process::ReadMemory(DWORD dwAddress, PVOID pvDestination, DWORD dwSize)
{
	return ReadProcessMemory(this->m_hProcess, (PVOID)dwAddress, pvDestination, dwSize, NULL);
}

bool Process::WriteMemory(DWORD dwAddress, PVOID pvData, DWORD dwSize)
{
	return WriteProcessMemory(this->m_hProcess, (PVOID)dwAddress, pvData, dwSize, NULL);
}
