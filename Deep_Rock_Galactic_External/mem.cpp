#include "mem.h"

void mem::ReadEx(BYTE* dst, BYTE* toWrite, unsigned int size, HANDLE hProcess)
{
	DWORD oldprotect;
	/* VirtualProtectEx - Change the protection on a region of committed pages in the vitrual address space of a process.
	*  PAGE_EXECUTE_READWRITE - Enables execute or read-write access to committed region of pages.
	*/

	// Change proctection of memory and store old protections in oldprotect.
	VirtualProtectEx(hProcess, dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);

	// Write bytes to memory.
	ReadProcessMemory(hProcess, dst, toWrite, size, nullptr);

	// Restore old protections with oldprotect.
	VirtualProtectEx(hProcess, dst, size, oldprotect, &oldprotect);
}

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