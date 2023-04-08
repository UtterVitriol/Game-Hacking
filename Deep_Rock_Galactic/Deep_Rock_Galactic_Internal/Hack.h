#pragma once

#include <Windows.h>
#include <vector>
#include <TlHelp32.h>

#include "Player.h"

namespace Hack{
	void Patch(BYTE* dst, BYTE* src, unsigned int size);
	void Nop(BYTE* dst, unsigned int size);
	uintptr_t FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets);
};

