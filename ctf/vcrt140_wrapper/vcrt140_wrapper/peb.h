#pragma once

#include "stdafx.h"

//
// stolen from:
// https://github.com/x64dbg/ScyllaHide/blob/2276f1477132e99c96f31552bce7b4d2925fb918/Scylla/Peb.h
// https://github.com/x64dbg/ScyllaHide/blob/2276f1477132e99c96f31552bce7b4d2925fb918/Scylla/NtApiShim.h
//


#define HEAP_VALIDATE_ALL_ENABLED           0x20000000
#define HEAP_SKIP_VALIDATION_CHECKS         0x10000000
#define HEAP_VALIDATE_PARAMETERS_ENABLED    0x40000000
#define HEAP_CAPTURE_STACK_BACKTRACES       0x08000000

// Flags set by RtlDebugCreateHeap
#define RTLDEBUGCREATEHEAP_HEAP_FLAGS   (HEAP_TAIL_CHECKING_ENABLED | HEAP_FREE_CHECKING_ENABLED | HEAP_SKIP_VALIDATION_CHECKS)

// Additional debug flags that may be set depending on NtGlobalFlags
#define NTGLOBALFLAGS_HEAP_FLAGS        (HEAP_DISABLE_COALESCE_ON_FREE | HEAP_FREE_CHECKING_ENABLED | HEAP_TAIL_CHECKING_ENABLED | \
                                        HEAP_VALIDATE_ALL_ENABLED | HEAP_VALIDATE_PARAMETERS_ENABLED | HEAP_CAPTURE_STACK_BACKTRACES)

// The set of heap flags to clear is the union of flags set by RtlDebugCreateHeap and NtGlobalFlags
#define HEAP_CLEARABLE_FLAGS            (RTLDEBUGCREATEHEAP_HEAP_FLAGS | NTGLOBALFLAGS_HEAP_FLAGS)

// Only a subset of possible flags passed to RtlCreateHeap persists into force flags
#define HEAP_VALID_FORCE_FLAGS          (HEAP_NO_SERIALIZE | HEAP_GENERATE_EXCEPTIONS | HEAP_ZERO_MEMORY | HEAP_REALLOC_IN_PLACE_ONLY | \
                                        HEAP_VALIDATE_PARAMETERS_ENABLED | HEAP_VALIDATE_ALL_ENABLED | HEAP_TAIL_CHECKING_ENABLED | \
                                        HEAP_CREATE_ALIGN_16 | HEAP_FREE_CHECKING_ENABLED)

// The set of force flags to clear is the intersection of valid force flags and the debug flags
#define HEAP_CLEARABLE_FORCE_FLAGS      (HEAP_CLEARABLE_FLAGS & HEAP_VALID_FORCE_FLAGS)


#define HEAP_FLAGS_OFFSET 0x40
#define HEAP_FORCE_FLAGS_OFFSET 0x44
#define HEAP_FLAGS_OFFSET_64 0x70
#define HEAP_FORCE_FLAGS_OFFSET_64 0x74


template <typename PTR>
struct UNICODE_STRING
{
    union
    {
        struct
        {
            WORD Length;
            WORD MaximumLength;
        };
        PTR dummy;
    };
    PTR _Buffer;
};

template<typename PTR>
struct CURDIR {
    UNICODE_STRING<PTR> DosPath;
    PTR Handle;
};

template<typename PTR>
struct RTL_USER_PROCESS_PARAMETERS {
    ULONG MaximumLength;
    ULONG Length;

    ULONG Flags;
    ULONG DebugFlags;

    PTR ConsoleHandle;
    ULONG  ConsoleFlags;
    PTR StandardInput;
    PTR StandardOutput;
    PTR StandardError;

    CURDIR<PTR> CurrentDirectory;
    UNICODE_STRING<PTR> DllPath;
    UNICODE_STRING<PTR> ImagePathName;
    UNICODE_STRING<PTR> CommandLine;
    PTR Environment;

    ULONG StartingX;
    ULONG StartingY;
    ULONG CountX;
    ULONG CountY;
    ULONG CountCharsX;
    ULONG CountCharsY;
    ULONG FillAttribute;

    ULONG WindowFlags;
    ULONG ShowWindowFlags;
    UNICODE_STRING<PTR> WindowTitle;
    UNICODE_STRING<PTR> DesktopInfo;
    UNICODE_STRING<PTR> ShellInfo;
    UNICODE_STRING<PTR> RuntimeData;
};

template <typename T, typename NGF, int A>
struct _PEB_T
{
    union
    {
        struct
        {
            BYTE InheritedAddressSpace;
            BYTE ReadImageFileExecOptions;
            BYTE BeingDebugged;
            BYTE _SYSTEM_DEPENDENT_01;
        };
        T dummy01;
    };
    T Mutant;
    T ImageBaseAddress;
    T Ldr;
    T ProcessParameters;
    T SubSystemData;
    T ProcessHeap;
    T FastPebLock;
    T _SYSTEM_DEPENDENT_02;
    T _SYSTEM_DEPENDENT_03;
    T _SYSTEM_DEPENDENT_04;
    union
    {
        T KernelCallbackTable;
        T UserSharedInfoPtr;
    };
    DWORD SystemReserved;
    DWORD _SYSTEM_DEPENDENT_05;
    T _SYSTEM_DEPENDENT_06;
    T TlsExpansionCounter;
    T TlsBitmap;
    DWORD TlsBitmapBits[2];
    T ReadOnlySharedMemoryBase;
    T _SYSTEM_DEPENDENT_07;
    T ReadOnlyStaticServerData;
    T AnsiCodePageData;
    T OemCodePageData;
    T UnicodeCaseTableData;
    DWORD NumberOfProcessors;
    union
    {
        DWORD NtGlobalFlag;
        NGF dummy02;
    };
    LARGE_INTEGER CriticalSectionTimeout;
    T HeapSegmentReserve;
    T HeapSegmentCommit;
    T HeapDeCommitTotalFreeThreshold;
    T HeapDeCommitFreeBlockThreshold;
    DWORD NumberOfHeaps;
    DWORD MaximumNumberOfHeaps;
    T ProcessHeaps;
    T GdiSharedHandleTable;
    T ProcessStarterHelper;
    T GdiDCAttributeList;
    T LoaderLock;
    DWORD OSMajorVersion;
    DWORD OSMinorVersion;
    WORD OSBuildNumber;
    WORD OSCSDVersion;
    DWORD OSPlatformId;
    DWORD ImageSubsystem;
    DWORD ImageSubsystemMajorVersion;
    T ImageSubsystemMinorVersion;
    union
    {
        T ImageProcessAffinityMask;
        T ActiveProcessAffinityMask;
    };
    T GdiHandleBuffer[A];
    T PostProcessInitRoutine;
    T TlsExpansionBitmap;
    DWORD TlsExpansionBitmapBits[32];
    T SessionId;
    ULARGE_INTEGER AppCompatFlags;
    ULARGE_INTEGER AppCompatFlagsUser;
    T pShimData;
    T AppCompatInfo;
    UNICODE_STRING<T> CSDVersion;
    T ActivationContextData;
    T ProcessAssemblyStorageMap;
    T SystemDefaultActivationContextData;
    T SystemAssemblyStorageMap;
    T MinimumStackCommit;
};

typedef _PEB_T<DWORD, DWORD64, 34> PEB32;
typedef _PEB_T<DWORD64, DWORD, 30> PEB64;

void doPEBPatches();