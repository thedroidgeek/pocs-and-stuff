
#include "stdafx.h"
#include "hooking.h"
#include "utils.h"

//
// https://forums.codeguru.com/showthread.php?556091-How-to-inject-input-text-into-a-running-console-application
//

void enterAsciiLineToStdin(char* string)
{
    HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
    HKL kbdLt = GetKeyboardLayout(NULL);

    for (size_t i = 0; i < strlen(string); i++)
    {
        char z = string[i];

        INPUT_RECORD ir[2] = { 0 };

        WORD wVkCodeRes = VkKeyScanEx(z, kbdLt);

        ir[0].Event.KeyEvent.uChar.AsciiChar = z;
        ir[0].Event.KeyEvent.wVirtualKeyCode = wVkCodeRes & 0xFF;

        BYTE byKState = (BYTE)((wVkCodeRes & 0xFF00) >> 8);

        ir[0].Event.KeyEvent.dwControlKeyState = byKState;

        ir[0].EventType = KEY_EVENT;
        ir[0].Event.KeyEvent.bKeyDown = TRUE;
        ir[0].Event.KeyEvent.wRepeatCount = 1;

        UINT uiScanCode = MapVirtualKeyEx(ir[0].Event.KeyEvent.wVirtualKeyCode & 0xFF, MAPVK_VK_TO_VSC, kbdLt);
        ir[0].Event.KeyEvent.wVirtualScanCode = (WORD)uiScanCode;

        ir[1] = ir[0];
        ir[1].Event.KeyEvent.bKeyDown = FALSE;

        DWORD dwNumWrtn = -1;
        WriteConsoleInput(hStdIn, ir, 2, &dwNumWrtn);
    }

    INPUT_RECORD ir[2] = { 0 };

    ir[0].EventType = KEY_EVENT;
    ir[0].Event.KeyEvent.bKeyDown = TRUE;
    ir[0].Event.KeyEvent.wRepeatCount = 1;
    ir[0].Event.KeyEvent.uChar.AsciiChar = VK_RETURN;
    ir[0].Event.KeyEvent.dwControlKeyState = 0;

    ir[1] = ir[0];
    ir[1].Event.KeyEvent.bKeyDown = FALSE;

    DWORD dwNumWrtn = -1;
    WriteConsoleInput(hStdIn, ir, 2, &dwNumWrtn);
}

bool isLaunchedFromExplorer()
{
    ULONG_PTR pbi[6];
    ULONG ulSize = 0;
    
    static decltype(NtQueryInformationProcess_orig) pNtQueryInformationProcess = nullptr;

    if (!pNtQueryInformationProcess) {
        pNtQueryInformationProcess = reinterpret_cast<decltype(NtQueryInformationProcess_orig)>(GetProcAddress(GetModuleHandle(L"ntdll.dll"), "NtQueryInformationProcess"));
    }
    
    if (!pNtQueryInformationProcess || pNtQueryInformationProcess((HANDLE)-1, 0, &pbi, sizeof(pbi), &ulSize) < 0 || ulSize != sizeof(pbi)) {
        return FALSE;
    }

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pbi[5]);

    CHAR szProcFileName[1024] = { 0 };
    if (!hProcess || !GetProcessImageFileNameA(hProcess, szProcFileName, sizeof(szProcFileName))) {
        return FALSE;
    }

    CloseHandle(hProcess);

    const char* szExplorerExe = "\\explorer.exe";

    auto nProcFileNameLen = strlen(szProcFileName);
    auto nExplorerExeLen = strlen(szExplorerExe);

    if (nProcFileNameLen > nExplorerExeLen) {
        if (strcmp(szProcFileName + nProcFileNameLen - nExplorerExeLen, szExplorerExe) == 0) {
            return TRUE;
        }
    }
    return FALSE;
}

void pauseConsole()
{
    printf("Press any key to continue . . . ");
    _getch();
}


FILE* hLogFile;

void log_init()
{
    hLogFile = _fsopen("./wew.log", "w", _SH_DENYNO);
}

void log_deinit()
{
    fclose(hLogFile);
}

void log(const bool silently, const char* fmt, ...)
{
    va_list va_alist;
    char chLogBuff[8192];
    char chParameters[7000];
    char szTimestamp[30];
    struct tm current_tm;
    time_t current_time = time(NULL);

    localtime_s(&current_tm, &current_time);
    sprintf_s(szTimestamp, "[%02d:%02d:%02d] %%s\n", current_tm.tm_hour, current_tm.tm_min, current_tm.tm_sec);

    va_start(va_alist, fmt);
    _vsnprintf_s(chParameters, sizeof(chParameters), fmt, va_alist);
    va_end(va_alist);

    sprintf_s(chLogBuff, szTimestamp, chParameters);
    if (hLogFile) {
        fprintf(hLogFile, "%s", chLogBuff);
    }
    fflush(hLogFile);
    if (!silently) {
        MessageBoxA(NULL, chParameters, ":o", 0);
    }
}

void log_write(const char* info)
{
    if (hLogFile) {
        fprintf(hLogFile, "%s\n", info);
        fflush(hLogFile);
    }
}
