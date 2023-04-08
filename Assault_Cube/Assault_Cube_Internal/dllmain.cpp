#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include "../MemLib/mem.h"
#include "../ProcLib/proc.h"


struct vec3 {
	float x, y, z;
};

class PlayerEnt
{
public:
	vec3 PosHead; //0x0004
	char pad_0010[36]; //0x0010
	vec3 PosBody; //0x0034
	vec3 PosAim; //0x0040
	char pad_004C[172]; //0x004C
	int32_t Health; //0x00F8
	int32_t Armor; //0x00FC
	char pad_0100[88]; //0x0100
	int32_t Grenades; //0x0158
	char pad_015C[201]; //0x015C
	char Name[16]; //0x0225
	char pad_0235[319]; //0x0235
	class Weapon* CurWeapon; //0x0374
	char pad_0378[1264]; //0x0378

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
}; //Size: 0x0868
static_assert(sizeof(PlayerEnt) == 0x868);

class Weapon
{
public:
	char pad_0000[16]; //0x0000
	int32_t* ResAmmoPtr; //0x0010
	int32_t* AmmoPtr; //0x0014
	char pad_0018[44]; //0x0018
}; //Size: 0x0044
static_assert(sizeof(Weapon) == 0x44);



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

