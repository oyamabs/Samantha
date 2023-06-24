#pragma once
#include "pch.h"

namespace hooks {
	void Setup();
	void Destroy() noexcept;

	constexpr void* VirtualFucntion(void* currentPtr, size_t index) noexcept {
		return (*static_cast<void***>(currentPtr))[index];
	}

	using EndSceneFn = long(__thiscall*)(void*, IDirect3DDevice9*)
}