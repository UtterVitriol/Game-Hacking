#include <cstdio>
#include <iostream>

#include "Windows.h"

#include "../MemLib/mem.h"
#include "../ProcLib/proc.h"


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

	bool bHealth = false, bAmmo = false, bRecoil = false;



	while (GetExitCodeProcess(hProcess, &dwExit) && STILL_ACTIVE)
	{

		if (GetAsyncKeyState(VK_END) & 1) {
			break;
		}

		if (GetAsyncKeyState(VK_F1) & 1) {
			bHealth = !bHealth;
		}

		if (GetAsyncKeyState(VK_F2) & 1) {
			bAmmo = !bAmmo;
		}

		if (GetAsyncKeyState(VK_F3) & 1) {
			bRecoil = !bRecoil;

			if (bRecoil) {
				// NOP instructions.
				mem::Nop((BYTE*)(moduleBase + 0x63786), 10);
			}
			else {
				// Restore instructions.
				mem::Patch((BYTE*)(moduleBase + 0x63786), (BYTE*)"\x50\x8d\x4c\x24\x1c\x51\x8b\xce\xff\xd2", 10);
			}

		}


		
	}

}