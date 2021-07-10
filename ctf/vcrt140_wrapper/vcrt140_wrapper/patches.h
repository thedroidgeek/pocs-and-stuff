#pragma once

#include "utils.h"

template <typename T>
void nopPtr(T address, size_t count)
{
    DWORD oldProtect;
    VirtualProtect((LPVOID)address, count, PAGE_EXECUTE_READWRITE, &oldProtect);

    memset((LPVOID)address, 0x90, count);

    VirtualProtect((LPVOID)address, count, oldProtect, &oldProtect);
}

void nopExe(DWORD offset, size_t count);

template <typename T, typename U>
void patchPtr(T address, U value)
{
    DWORD oldProtect;
    VirtualProtect((LPVOID)address, sizeof(U), PAGE_EXECUTE_READWRITE, &oldProtect);

    *(U*)address = value;

    VirtualProtect((LPVOID)address, sizeof(U), oldProtect, &oldProtect);
}

template <typename T>
void patchExe(DWORD offset, T value)
{
    patchPtr(getExeAddress(offset), value);
}

void applySEHPatches();
void removeDebugChecks();