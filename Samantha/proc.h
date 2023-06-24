#pragma once
#include "pch.h"

void Patch(BYTE* dest, BYTE* src, size_t size);
void Nop(BYTE* dest, size_t size);
uintptr_t FindDynamicAddress(uintptr_t base, std::vector<int> offsets);

