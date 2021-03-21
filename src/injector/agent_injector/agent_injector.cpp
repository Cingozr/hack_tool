// agent_injector.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <string>
#include <cstdarg>


int main(int argc, char* argv[])
{

	char* dllPath;
	char szDestPath[MAX_PATH];
	char* pszFileName = NULL;
	LPTSTR pFilePart;
	HANDLE hProc, hTread;
	DWORD pid = 0;
	PVOID address;
	SIZE_T lpnByteWritten;

	pid = (DWORD)atoi(argv[1]);
	dllPath = argv[2];


	GetFullPathName(dllPath, sizeof(szDestPath), szDestPath, &pszFileName);


	hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	if (hProc == NULL)
	{
		std::cout << GetLastError() << std::endl;
		return -1;
	}

	const SIZE_T dllPathSize = strlen(szDestPath) + 1;
	LPVOID aa;

	address = VirtualAllocEx(hProc, NULL, dllPathSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (address == NULL)
	{
		std::cout << GetLastError() << std::endl;
		return -1;
	}
	if (!WriteProcessMemory(hProc, address, szDestPath, dllPathSize, &lpnByteWritten))
	{
		std::cout << GetLastError() << std::endl;
		return -1;
	}


	hTread = CreateRemoteThread(hProc, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, address, 0, NULL);
	if (hTread == NULL)
	{
		std::cout << GetLastError() << std::endl;
		return -1;
	}
}

