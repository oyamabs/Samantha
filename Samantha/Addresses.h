#pragma once
#include "pch.h"

uintptr_t moduleBaseAddress = (uintptr_t)GetModuleHandle(NULL);

namespace Player {
	int* points = (int*)(moduleBaseAddress + 0x180a6c8);
	int* health = (int*)(moduleBaseAddress + 0x167987C);
	int* kills = (int*)0x01C0A6CC;
	int* headshots = (int*)(moduleBaseAddress + 0x180A6EC);
}