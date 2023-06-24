#pragma once
#include "pch.h"

uintptr_t moduleBaseAddress = (uintptr_t)GetModuleHandle(NULL);

namespace Player {
	int* iPoints = (int*)(moduleBaseAddress + 0x180a6c8);
	int* iHealth = (int*)(moduleBaseAddress + 0x167987C);
	int* iKills = (int*)0x01C0A6CC;
	int* iHeadshots = (int*)(moduleBaseAddress + 0x180A6EC);
}