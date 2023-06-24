#include "pch.h"
#include "proc.h"


void Patch(BYTE* dest, BYTE* src, size_t size) {
	DWORD dOldProtection;
	VirtualProtect(dest, size, PAGE_EXECUTE_READWRITE, &dOldProtection);
	memcpy(dest, src, size);
	VirtualProtect(dest, size, dOldProtection, &dOldProtection);
}

void Nop(BYTE* dest, size_t size) {
	DWORD dOldProtection;
	VirtualProtect(dest, size, PAGE_EXECUTE_READWRITE, &dOldProtection);
	memset(dest, 0x90, size);
	VirtualProtect(dest, size, dOldProtection, &dOldProtection);
}


uintptr_t FindDynamicAddress(uintptr_t base, std::vector<int> offsets) {
	uintptr_t ptr = base;

	for (int i = 0; i < offsets.size(); i++) {
		ptr = *(uintptr_t*)ptr;
		ptr += offsets[i];
	}

	return ptr;
}