// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include <iostream>
#include <cstdio>
#include <TlHelp32.h>
#include <time.h>
#include <sstream>
#include <string>

#include "Display.h"
#include "Player.h"
#include "Hack.h"


typedef void (*tShoot)(Weapon*);

tShoot Shoot = nullptr; // Modulebase + 1514AA0

uintptr_t moduleBase = (uintptr_t)GetModuleHandle(NULL);

DWORD WINAPI HackThread(HMODULE hModule) {
	// Create console.

	// AllocConsole - Allocates new console for colling process.
	AllocConsole();
	FILE* fp = NULL;

	// Securely open file stream.
	freopen_s(&fp, "CONOUT$", "w", stdout);

	MyPlayer Player;

	Player.Start();

	while (!GetAsyncKeyState(VK_END) & 1) {


		//if (PlayerHealth->BaseHealth == 0)
		//{
		//	// At base
		//	Display.Print(&Display.sLocation, "Base");
		//	continue;
		//}

		//Display.Print(&Display.sLocation, "Cave");



		//if (Display.sGameStatus == "Waiting")
		//{
		//	std::stringstream ss;
		//	ss << Player;
		//	std::string s = ss.str();
		//	Display.Print(&Display.sGameStatus, s.c_str());
		//}


		Player.UpdateValues();

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

