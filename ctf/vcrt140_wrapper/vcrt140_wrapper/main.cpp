
#include "stdafx.h"
#include "wrapper.h"
#include "MinHook.h"
#include "peb.h"
#include "utils.h"
#include "hooking.h"
#include "patches.h"
#include "solve.h"


HINSTANCE mHinst = 0, mHinstDLL = 0;


BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    mHinst = hinstDLL;
    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        log_init();

        // wrapper setup
        mHinstDLL = LoadLibrary(L"C:\\Windows\\System32\\vcruntime140.dll");
        if (!mHinstDLL) {
            log_notify("Failed to load original vcruntime140.dll!");
            return FALSE;
        }
        for (int i = 0; i < 81; ++i) {
            mProcs[i] = (UINT_PTR)GetProcAddress(mHinstDLL, mImportNames[i]);
        }

        // init minhook
        if (MH_Initialize() != MH_OK) {
            log_notify("MinHook failed to initialize!");
            return FALSE;
        }

        // anti-anti-debug
        {
            // clean up Process Execution Block debugger-incriminating flags
            doPEBPatches();

            // detour functions used for debugger checks
            hookFunctions();

            // patch out TlsCallback debugger checks (redundant if hooking is enabled)
            //removeDebugChecks();

            // remove SEH debugger traps
            applySEHPatches();
        }

        // retreive the credentials string and submit it to unlock the flag
        solve();

        // wait for input before exiting, if launched from explorer
        if (isLaunchedFromExplorer())
        {
            atexit(&pauseConsole);
        }
    }
    else if (fdwReason == DLL_PROCESS_DETACH)
    {
        // unhook the hooked functions for anti-anti-debug
        unhookFunctions();

        log_deinit();
        FreeLibrary(mHinstDLL);
    }
    return TRUE;
}
