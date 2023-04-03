// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include "mem.h"
#include "proc.h"

DWORD WINAPI HackThread(HMODULE hModule) {
	// Create console.

	// AllocConsole - Allocates new console for colling process.
	AllocConsole();
	FILE* fp = NULL;

	// Securely open file stream.
	freopen_s(&fp, "CONOUT$", "w", stdout);

	std::cout << "OG for a fee, stay sippin' fam\n";


	// Get module base.
	uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"ac_client.exe");




	bool bHealth = false, bAmmo = false, bRecoil = false;

	// Hack loop.

	for (;;) {
		// Key input.

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


		// Continuous write/freeze
		PlayerEnt* localPlayer = *(PlayerEnt**)(moduleBase + 0x10f4f4);

		if (localPlayer) {
			if (bHealth) {
				localPlayer->Health = 1337;
				localPlayer->Armor = 1337;
			}

			if (bAmmo) {
				*localPlayer->CurWeapon->AmmoPtr = 1337;
				*localPlayer->CurWeapon->ResAmmoPtr = 1337;
			}

		}

		Sleep(5);
	}



	// Cleanup & Eject.
	fclose(fp);

	// FreeConsole - Detaches calling process from its console.
	FreeConsole();

	// FreeLibraryAndExitThread - Decrements the reference count of a loaded DLL and calls ExitThread.
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:

		/* CreateThread - Creates a thread and returns a HANDLE.
		*  CloseHandle - Cloases handle.
		*/
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

