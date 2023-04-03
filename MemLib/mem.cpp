#include "mem.h"
#include <vector>

// Patch memory with bytes.
void mem::PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess) {

	DWORD oldprotect;
	
	/* VirtualProtectEx - Change the protection on a region of committed pages in the vitrual address space of a process.
	*  PAGE_EXECUTE_READWRITE - Enables execute or read-write access to committed region of pages.
	*/

	// Change proctection of memory and store old protections in oldprotect.
	VirtualProtectEx(hProcess, dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);

	// Write bytes to memory.
	WriteProcessMemory(hProcess, dst, src, size, nullptr);

	// Restore old protections with oldprotect.
	VirtualProtectEx(hProcess, dst, size, oldprotect, &oldprotect);
}

// Same as PatchEx, except the just writes  NOPs.
void mem::NopEx(BYTE* dst, unsigned int size, HANDLE hProcess) {
	BYTE* nopArray = new BYTE[size];
	memset(nopArray, 0x90, size);

	PatchEx(dst, nopArray, size, hProcess);
	delete[] nopArray;
}

// Find Dynamic Memory Allocation Address (multi-level pointer).
uintptr_t mem::FindDMAAddyEx(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets) {

	uintptr_t addr = ptr;

	/* Read memory at address (addr) and store value in addr.
	*  Move offset (offsets[i]).
	*  Repeat for all offsets.
	*/

	for (unsigned int i = 0; i < offsets.size(); ++i) {
		ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), 0);
		addr += offsets[i];
	}

	return addr;
}


// Patch memory with bytes.
void mem::Patch(BYTE* dst, BYTE* src, unsigned int size) {

	DWORD oldprotect;

	/* VirtualProtectEx - Change the protection on a region of committed pages in the vitrual address space of a process.
	*  PAGE_EXECUTE_READWRITE - Enables execute or read-write access to committed region of pages.
	*/

	// Change proctection of memory and store old protections in oldprotect.
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);

	// Write bytes to memory.
	memcpy(dst, src, size);

	// Restore old protections with oldprotect.
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

// Same as PatchEx, except the just writes  NOPs.
void mem::Nop(BYTE* dst, unsigned int size) {

	DWORD oldprotect;

	// Change proctection of memory and store old protections in oldprotect.
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);

	// Write bytes to memory.
	memset(dst, 0x90, size);

	// Restore old protections with oldprotect.
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

// Find Dynamic Memory Allocation Address (multi-level pointer).
uintptr_t mem::FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets) {

	uintptr_t addr = ptr;

	/* Read memory at address (addr) and store value in addr.
	*  Move offset (offsets[i]).
	*  Repeat for all offsets.
	*/

	for (unsigned int i = 0; i < offsets.size(); ++i) {
		addr = *(uintptr_t*)addr;
		addr += offsets[i];
	}

	return addr;
}