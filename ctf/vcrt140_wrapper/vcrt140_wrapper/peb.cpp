
#include "peb.h"
#include "utils.h"


void doPEBPatches()
{
    // get Process Execution Block
    auto pPeb = (PEB32*)__readfsdword(0x30);

    // get 64-bit process PEB also, since we're in WoW64 mode
    auto pTeb = (BYTE*)__readfsdword(0x18) - 0x2000;
    auto pPeb64 = (PEB64*)*(DWORD64*)(pTeb + 0x60);

    // check and clear BeingDebugged flag
    if (pPeb->BeingDebugged) {
        log_info("Clearing BeingDebugged PEB32 flag");
        pPeb->BeingDebugged = FALSE;
    }
    if (pPeb64->BeingDebugged) {
        log_info("Clearing BeingDebugged PEB64 flag");
        pPeb64->BeingDebugged = FALSE;
    }

    // check and clear NtGlobalFlag flag
    log_info("dwNtGlobalFlag: 0x%X", pPeb->NtGlobalFlag);
    log_info("dwNtGlobalFlag (64): 0x%X", pPeb64->NtGlobalFlag);
    if (pPeb->NtGlobalFlag) {
        log_info("Clearing NtGlobalFlag PEB32 flag");
        pPeb->NtGlobalFlag = 0;
    }
    if (pPeb64->NtGlobalFlag) {
        log_info("Clearing NtGlobalFlag PEB64 flag");
        pPeb64->NtGlobalFlag = 0;
    }

    // get heap pointer array
    auto heaps = (DWORD*)pPeb->ProcessHeaps;

    log_info("NumberOfHeaps = %d", pPeb->NumberOfHeaps);

    // iterate through heaps to patch their flags
    for (DWORD i = 0; i < pPeb->NumberOfHeaps; i++)
    {
        // get pointers to flags
        auto flags = (DWORD*)(heaps[i] + HEAP_FLAGS_OFFSET);
        auto force_flags = (DWORD*)(heaps[i] + HEAP_FORCE_FLAGS_OFFSET);

        log_info("heap %d: HeapFlagsOffset = 0x%X, HeapForceFlagsOffset = 0x%X", i + 1, *flags, *force_flags);

        // clear incriminating flaqs
        *flags &= ~HEAP_CLEARABLE_FLAGS;
        *force_flags &= ~HEAP_CLEARABLE_FORCE_FLAGS;
    }

    // WoW64 read/write functions to access 64-bit process address space

    NTSTATUS(__stdcall * pNtWow64ReadVirtualMemory64)(HANDLE ProcessHandle, PVOID64 BaseAddress, PVOID Buffer, ULONGLONG BufferSize, PULONGLONG NumberOfBytesRead);
    NTSTATUS(__stdcall * pNtWow64WriteVirtualMemory64)(HANDLE ProcessHandle, PVOID64 BaseAddress, PVOID Buffer, ULONGLONG BufferSize, PULONGLONG NumberOfBytesWritten);

    pNtWow64ReadVirtualMemory64 = reinterpret_cast<decltype(pNtWow64ReadVirtualMemory64)>(GetProcAddress(GetModuleHandleW(L"ntdll.dll"), "NtWow64ReadVirtualMemory64"));
    if (!pNtWow64ReadVirtualMemory64)
    {
        log_notify("Failed to get NtWow64ReadVirtualMemory64 address!");
        return;
    }
    pNtWow64WriteVirtualMemory64 = reinterpret_cast<decltype(pNtWow64WriteVirtualMemory64)>(GetProcAddress(GetModuleHandleW(L"ntdll.dll"), "NtWow64WriteVirtualMemory64"));
    if (!pNtWow64WriteVirtualMemory64)
    {
        log_notify("Failed to get NtWow64WriteVirtualMemory64 address!");
        return;
    }

    log_info("NumberOfHeaps (64) = %d", pPeb64->NumberOfHeaps);

    // allocate array for 64 heap addresses
    DWORD64* heaps64 = new DWORD64[pPeb64->NumberOfHeaps];

    // get a real process handle as WoW64 functions seem to have a bug where pseudo handles aren't sign extended to 64-bit, which means we can't use them
    HANDLE hcurrProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, GetCurrentProcessId());

    // read 64 heap addresses
    pNtWow64ReadVirtualMemory64(hcurrProcess, (PVOID64)pPeb64->ProcessHeaps, heaps64, pPeb64->NumberOfHeaps * sizeof(DWORD64), nullptr);
    
    // iterate through 64 heaps to patch flags
    for (DWORD i = 0; i < pPeb64->NumberOfHeaps; i++)
    {
        DWORD64 flags = 0;
        DWORD64 force_flags = 0;

        // read flags
        pNtWow64ReadVirtualMemory64(hcurrProcess, (PVOID64)(heaps64[i] + HEAP_FLAGS_OFFSET_64), &flags, sizeof(DWORD64), nullptr);
        pNtWow64ReadVirtualMemory64(hcurrProcess, (PVOID64)(heaps64[i] + HEAP_FORCE_FLAGS_OFFSET_64), &force_flags, sizeof(DWORD64), nullptr);

        log_info("heap %d (64): HeapFlagsOffset = 0x%X, HeapForceFlagsOffset = 0x%X", i + 1, flags, force_flags);

        // clear incriminating flags
        flags &= ~HEAP_CLEARABLE_FLAGS;
        force_flags &= ~HEAP_CLEARABLE_FORCE_FLAGS;

        // write them back
        pNtWow64WriteVirtualMemory64(hcurrProcess, (PVOID64)(heaps64[i] + HEAP_FLAGS_OFFSET_64), &flags, sizeof(DWORD64), nullptr);
        pNtWow64WriteVirtualMemory64(hcurrProcess, (PVOID64)(heaps64[i] + HEAP_FORCE_FLAGS_OFFSET_64), &force_flags, sizeof(DWORD64), nullptr);
    }

    CloseHandle(hcurrProcess);
}