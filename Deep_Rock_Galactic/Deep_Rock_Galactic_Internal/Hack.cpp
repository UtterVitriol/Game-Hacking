#include "Hack.h"

namespace Hack {
	// Patch memory with bytes.
	void Patch(BYTE* dst, BYTE* src, unsigned int size)
	{

		DWORD oldprotect;

		// Change proctection of memory and store old protections in oldprotect.
		VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);

		// Write bytes to memory.
		memcpy(dst, src, size);

		// Restore old protections with oldprotect.
		VirtualProtect(dst, size, oldprotect, &oldprotect);
	}

	// Same as PatchEx, except the just writes  NOPs.
	void Nop(BYTE* dst, unsigned int size)
	{

		DWORD oldprotect;

		// Change proctection of memory and store old protections in oldprotect.
		VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);

		// Write bytes to memory.
		memset(dst, 0x90, size);

		// Restore old protections with oldprotect.
		VirtualProtect(dst, size, oldprotect, &oldprotect);
	}

	// Find Dynamic Memory Allocation Address (multi-level pointer).
	uintptr_t FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets)
	{

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
}