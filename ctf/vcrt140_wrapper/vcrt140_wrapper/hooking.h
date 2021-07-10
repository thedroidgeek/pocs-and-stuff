#pragma once


constexpr auto ProcessDebugPort = 0x07;
constexpr auto ProcessDebugObjectHandle = 0x1E;
constexpr auto ThreadHideFromDebugger = 0x11;

#define STATUS_PORT_NOT_SET 0xC0000353


static NTSTATUS(WINAPI* NtQueryInformationProcess_orig)(
    HANDLE  ProcessHandle,
    DWORD   ProcessInformationClass,
    PVOID   ProcessInformation,
    ULONG   ProcessInformationLength,
    PULONG  ReturnLength
);
static NTSTATUS(WINAPI* NtSetInformationThread_orig)(
    HANDLE  ThreadHandle,
    DWORD   ThreadInformationClass,
    PVOID   ThreadInformation,
    ULONG   ThreadInformationLength
);

static DWORD(__cdecl* crc32_orig)(BYTE* pbData, DWORD dwDataLen);
static BOOL(__cdecl* md5_orig)(BYTE* pbData, DWORD dwDataLen, LPVOID lpHashResult);
static BOOL(__cdecl* sha256_orig)(BYTE* pbData, DWORD dwDataLen, LPVOID lpHashResult);


struct ApiHookDefinition {
    const wchar_t* moduleName;
    const char* procName;
    LPVOID pWrapFunc;
    LPVOID ppOrigFunc;
};

struct ExeHookDefinition {
    DWORD offset;
    const char* name;
    LPVOID pWrapFunc;
    LPVOID ppOrigFunc;
};

struct HookedFunc {
    LPVOID address;
    const char* name;
};

bool hookFunctions();
bool unhookFunctions();
