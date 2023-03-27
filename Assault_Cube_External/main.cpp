#include <cstdio>
#include <iostream>

#include "Windows.h"

#include "proc.h"
#include "mem.h"


int main()
{
	HANDLE hProcess = 0;
	
	uintptr_t moduleBase = 0;
	uintptr_t localPlayerPtr = 0;

	DWORD dwProcId = GetProcId(L"ac_client.exe");


	if (dwProcId)
	{
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, dwProcId);

		moduleBase = GetModuleBaseAddress(dwProcId, L"ac_client.exe");

		if (0 == moduleBase)
		{
			puts("Can't get module base\n");
			return 0;
		}

		localPlayerPtr = moduleBase + 0x10f4f4;



	}
	else
	{
		puts("Process not found, press enter to exit");
		(void)getchar();
		return 0;
	}

	DWORD dwExit = 0;


	while (GetExitCodeProcess(hProcess, &dwExit) && STILL_ACTIVE)
	{
		if (GetAsyncKeyState(VK_F1) & 1) {
			bMoney = !bMoney;
			if (!bMoney) {
				mem::PatchEx((BYTE*)goldAddr, (BYTE*)&oldMoney, sizeof(oldMoney), hProcess);
			}

		}

		if (GetAsyncKeyState(VK_F2) & 1) {
			mem::ReadEx((BYTE*)zCoordAddr, (BYTE*)&zCoord, sizeof(zCoord), hProcess);
			mem::ReadEx((BYTE*)zCoordAddr - 4, (BYTE*)&yCoord, sizeof(yCoord), hProcess);
			mem::ReadEx((BYTE*)zCoordAddr - 8, (BYTE*)&xCoord, sizeof(xCoord), hProcess);
				
		}

		if (GetAsyncKeyState(VK_F3) & 1) {
			mem::PatchEx((BYTE*)zCoordAddr, (BYTE*)&zCoord, sizeof(zCoord), hProcess);
			mem::PatchEx((BYTE*)zCoordAddr - 4, (BYTE*)&yCoord, sizeof(yCoord), hProcess);
			mem::PatchEx((BYTE*)zCoordAddr - 8, (BYTE*)&xCoord, sizeof(xCoord), hProcess);
		}

		if (GetAsyncKeyState(VK_NUMPAD0) & 1)
		{
			puts("ahahaha");
		}


		
	}

}