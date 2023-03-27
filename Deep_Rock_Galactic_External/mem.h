#pragma once

#include <Windows.h>
#include <TlHelp32.h>

namespace mem {

	void ReadEx(BYTE* dst, BYTE* toWrite, unsigned int size, HANDLE hProcess);
	void PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess);
	void NopEx(BYTE* dst, unsigned int size, HANDLE hProcess);

}
