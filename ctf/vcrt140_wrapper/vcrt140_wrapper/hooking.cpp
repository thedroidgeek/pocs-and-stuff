#include "MinHook.h"
#include "stdafx.h"
#include "hooking.h"
#include "utils.h"


NTSTATUS WINAPI NtQueryInformationProcess_wrap(
    HANDLE  ProcessHandle,
    DWORD   ProcessInformationClass,
    PVOID   ProcessInformation,
    ULONG   ProcessInformationLength,
    PULONG  ReturnLength
) {
    log_info("NtQueryInformationProcess(%d, 0x%X, 0x%p, %lu, 0x%p); // from: 0x%X", ProcessHandle, ProcessInformationClass, ProcessInformation, ProcessInformationLength, ReturnLength, _ReturnAddress());
    NTSTATUS status = NtQueryInformationProcess_orig(ProcessHandle, ProcessInformationClass, ProcessInformation, ProcessInformationLength, ReturnLength);
    if (ProcessHandle == (HANDLE)-1)
    {
        if (ProcessInformationClass == ProcessDebugObjectHandle)
        {
            if (status == 0) {
                log_info("=> Spoofing ProcessDebugObjectHandle anti-debug measure");
                *(DWORD*)ProcessInformation = 0;
                return STATUS_PORT_NOT_SET;
            }
        }
        else if (ProcessInformationClass == ProcessDebugPort)
        {
            if (status == 0 && *(DWORD*)ProcessInformation == -1) {
                log_info("=> Spoofing ProcessDebugPort anti-debug measure");
                *(DWORD*)ProcessInformation = 0;
            }
        }
    }
    return status;
}

NTSTATUS WINAPI NtSetInformationThread_wrap(
    HANDLE  ThreadHandle,
    DWORD   ThreadInformationClass,
    PVOID   ThreadInformation,
    ULONG   ThreadInformationLength
) {
    log_info("NtSetInformationThread(%d, 0x%X, 0x%p, %lu); // from: 0x%X", ThreadHandle, ThreadInformationClass, ThreadInformation, ThreadInformationLength, _ReturnAddress());
    if (ThreadHandle == (HANDLE)-2 && ThreadInformationClass == ThreadHideFromDebugger)
    {
        log_info("Skipping ThreadHideFromDebugger anti-debug measure");
        return 0;
    }
    return NtSetInformationThread_orig(ThreadHandle, ThreadInformationClass, ThreadInformation, ThreadInformationLength);
}

DWORD __cdecl crc32_wrap(BYTE* pbData, DWORD dwDataLen)
{
    auto retVal = crc32_orig(pbData, dwDataLen);

    log_info("crc32(0x%X, %d): 0x%X // from: 0x%X", pbData, dwDataLen, retVal, _ReturnAddress());

    if (retVal)
    {
        char* hexData = new char[dwDataLen * 3 + 1];
        for (DWORD i = 0; i < dwDataLen; i++)
            sprintf_s(&hexData[3 * i], 4, "%02hhX ", pbData[i]);
        log_info("pbData: %s", &hexData[0]);
        delete[] hexData;
    }

    return retVal;
}

BOOL __cdecl md5_wrap(BYTE* pbData, DWORD dwDataLen, LPVOID lpHashResult)
{
    auto retVal = md5_orig(pbData, dwDataLen, lpHashResult);

    log_info("md5(0x%X, %d, 0x%X): %s // from: 0x%X", pbData, dwDataLen, lpHashResult, retVal ? "true" : "false", _ReturnAddress());

    if (retVal)
    {
        char md5Hash[33] = { 0 };
        for (int i = 0; i < 16; i++)
            sprintf_s(&md5Hash[2 * i], 3, "%02hhX", ((uint8_t*)lpHashResult)[i]);
        log_info("lpHashResult: %s", &md5Hash[0]);

        char* hexData = new char[dwDataLen * 3 + 1];
        for (DWORD i = 0; i < dwDataLen; i++)
            sprintf_s(&hexData[3 * i], 4, "%02hhX ", pbData[i]);
        log_info("pbData: %s", &hexData[0]);
        delete[] hexData;
    }

    return retVal;
}

BOOL __cdecl sha256_wrap(BYTE* pbData, DWORD dwDataLen, LPVOID lpHashResult)
{
    auto retVal = sha256_orig(pbData, dwDataLen, lpHashResult);

    log_info("sha256(0x%X, %d, 0x%X): %s // from: 0x%X", pbData, dwDataLen, lpHashResult, retVal ? "true" : "false", _ReturnAddress());

    if (retVal)
    {
        char shaHash[65] = { 0 };
        for (int i = 0; i < 32; i++)
            sprintf_s(&shaHash[2 * i], 3, "%02hhX", ((uint8_t*)lpHashResult)[i]);
        log_info("lpHashResult: %s", &shaHash[0]);

        char* hexData = new char[dwDataLen * 3 + 1];
        for (DWORD i = 0; i < dwDataLen; i++)
            sprintf_s(&hexData[3 * i], 4, "%02hhX ", pbData[i]);
        log_info("pbData: %s", &hexData[0]);
        delete[] hexData;
    }

    return retVal;
}

const ApiHookDefinition apiHooks[] = {
    { L"ntdll.dll", "NtQueryInformationProcess", &NtQueryInformationProcess_wrap, &NtQueryInformationProcess_orig },
    { L"ntdll.dll", "NtSetInformationThread", &NtSetInformationThread_wrap, &NtSetInformationThread_orig },
};

const ExeHookDefinition exeHooks[] = {
    { 0x1C70, "crc32", &crc32_wrap, &crc32_orig },
    { 0x1D30, "md5", &md5_wrap, &md5_orig },
    { 0x1E00, "sha256", &sha256_wrap, &sha256_orig },
};

HookedFunc hookedFunctions[sizeof(apiHooks) / sizeof(ApiHookDefinition) + sizeof(exeHooks) / sizeof(ExeHookDefinition)] = { {0, 0} };


bool hookFunctions()
{
    bool retVal = true;

    int hookedIdx = 0;
    for (auto hook : apiHooks)
    {
        auto moduleHandle = GetModuleHandle(hook.moduleName);
        if (!moduleHandle) {
            log_notify("Failed to find module for %s", hook.procName);
            retVal = false;
            continue;
        }
        auto procAddr = GetProcAddress(moduleHandle, hook.procName);
        if (!procAddr) {
            log_notify("Failed to find address for %s", hook.procName);
            retVal = false;
            continue;
        }
        if (MH_CreateHook(procAddr, hook.pWrapFunc, (LPVOID*)hook.ppOrigFunc) != MH_OK) {
            log_notify("Failed to create hook for %s!", hook.procName);
            retVal = false;
            continue;
        }
        if (MH_EnableHook(procAddr) != MH_OK) {
            log_notify("Failed to enable hook for %s!", hook.procName);
            retVal = false;
            continue;
        }
        hookedFunctions[hookedIdx] = { (LPVOID)procAddr, hook.procName };
        hookedIdx++;
    }

    for (auto hook : exeHooks)
    {
        auto addr = getExeAddress<LPVOID>(hook.offset);
        if (MH_CreateHook(addr, hook.pWrapFunc, (LPVOID*)hook.ppOrigFunc) != MH_OK) {
            log_notify("Failed to create hook for %s!", hook.name);
            retVal = false;
            continue;
        }
        if (MH_EnableHook(addr) != MH_OK) {
            log_notify("Failed to enable hook for %s!", hook.name);
            retVal = false;
            continue;
        }
        hookedFunctions[hookedIdx] = { (LPVOID)addr, hook.name };
        hookedIdx++;
    }

    return retVal;
}

bool unhookFunctions()
{
    bool retVal = true;

    for (auto& unhook : hookedFunctions)
    {
        if (!unhook.address) {
            continue;
        }
        if (MH_DisableHook(unhook.address) != MH_OK) {
            log_notify("Failed to disable hook for %s!", unhook.name);
            retVal = false;
        }
        else if (MH_RemoveHook(unhook.address) != MH_OK) {
            log_notify("Failed to remove hook for %s!", unhook.name);
            retVal = false;
        }
        unhook = { 0, 0 };
    }

    return retVal;
}