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
	uintptr_t goldAddr = 0;
	uintptr_t zCoordAddr = 0;

	bool bMoney = false;
	const int newMoney = 1337;
	int oldMoney = 666666;

	bool bTele = false;
	float xCoord = 0;
	float yCoord = 0;
	float zCoord = 0;

	DWORD dwProcId = GetProcId(L"FSD-Win64-Shipping.exe");

	if (dwProcId)
	{
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, dwProcId);

		moduleBase = GetModuleBaseAddress(dwProcId, L"FSD-Win64-Shipping.exe");

		if (0 == moduleBase)
		{
			puts("Can't get module base\n");
			return 0;
		}

		localPlayerPtr = FindDMAAddy(hProcess, moduleBase + 0x061E0F00, { 0x18, 0x6D8 });

		goldAddr = FindDMAAddy(hProcess, moduleBase + 0x061EAA10, { 0x320, 0x20, 0x20, 0x6D8, 0x518 });

		printf("goldAddr: %p\n", goldAddr);

		zCoordAddr = FindDMAAddy(hProcess, moduleBase + 0x05DA4870, { 0x788, 0x90, 0x0, 0xC0, 0x1D8 });

		printf("zCoordAddr: %p\n", zCoordAddr);

	}
	else
	{
		puts("Process not found, press enter to exit");
		(void)getchar();
		return 0;
	}

	DWORD dwExit = 0;

	mem::ReadEx((BYTE*)goldAddr, (BYTE*)&oldMoney, sizeof(oldMoney), hProcess);

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

		if (GetAsyncKeyState(VK_F4) & 1) {
			break;
		}

		if (bMoney) {
			mem::PatchEx((BYTE*)goldAddr, (BYTE*)&newMoney, sizeof(newMoney), hProcess);
		}
		
	}

}