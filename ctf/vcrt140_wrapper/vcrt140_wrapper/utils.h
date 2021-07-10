#pragma once

void enterAsciiLineToStdin(char* string);
void pauseConsole();
bool isLaunchedFromExplorer();

void log_init();
void log_deinit();

void log(const bool silently, const char* fmt, ...);
void log_write(const char* info);

#define log_notify(...) log(false, __VA_ARGS__)
#define log_info(...) log(true, __VA_ARGS__)

template <typename T = void>
T* getExeAddress(DWORD offset = 0)
{
    static DWORD baseAddress = 0;
    if (!baseAddress) {
        baseAddress = (DWORD)GetModuleHandleA(NULL);
    }
    return reinterpret_cast<T*>(baseAddress + offset);
}
