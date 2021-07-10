
#include "stdafx.h"
#include "patches.h"
#include "utils.h"


void applySEHPatches() {

    //
    // 1) defuse icebp SEH trap
    //

    /*
        remove the try block containing icebp and set return value to false, as that's what the exception handler (catch) does
    */

    /*
        .text:00XX23C3 C7 45 FC 00 00 00 00    mov     [ebp+ms_exc.registration.TryLevel], 0          ; try begin
        .text:00XX23CA F1                      icebp
        .text:00XX23CB 90                      nop
        .text:00XX23CC C7 45 FC FE FF FF FF    mov     [ebp+ms_exc.registration.TryLevel], 0FFFFFFFEh ; try end
        .text:00XX23D3 B8 01 00 00 00          mov     eax, 1
    */

    // xor eax, eax
    patchExe<uint16_t>(0x23C3, 0xC033);

    // nop (x19)
    nopExe(0x23C5, 19);


    //
    // 2) defuse eflags SEH trap
    //

    /*
        skip writing the trap flag, and set return value to false:
    */

    /*
        .text:00XX218F 9C                      pushf
        .text:00XX2190 81 0C 24 00 01 00 00    or      [esp+2Ch+var_2C], 100h
        .text:00XX2197 9D                      popf
    */

    // xor eax, eax
    patchExe<uint16_t>(0x218F, 0xC033);

    // nop (x7)
    nopExe(0x2191, 7);


    //
    // 3) defuse INT3 SEH trap
    //

    /*
        skip INT3 setup and jump straight to exception handler:
    */

    /*
        .text:00XX1FC0 68 70 1F XX 00          push    offset sub_XX1F70
        .text:00XX1FC5 64 FF 35 00 00 00 00    push    large dword ptr fs:0
        .text:00XX1FCC 64 89 25 00 00 00 00    mov     large fs:0, esp
        .text:00XX1FD3 33 C0                   xor     eax, eax
        .text:00XX1FD5 CC                      int     3
    */

    // return right after pushing the exception handler (sub_XX1F70) (same effect as a jmp)
    patchExe<uint8_t>(0x1FC5, 0xC3);


    /*
        patch exception handler to act as a regular function:
    */

    /*
        .text:00XX1F70 55                   push    ebp
        .text:00XX1F71 8B EC                mov     ebp, esp
        .text:00XX1F73 56                   push    esi
        .text:00XX1F74 8B 75 10             mov     esi, [ebp+10h]  ; ContextRecord
        .text:00XX1F77 85 F6                test    esi, esi
        .text:00XX1F79 74 39                jz      short loc_XX1FB4
        ...
        .text:00XX1FA8 89 86 B0 00 00 00    mov     [esi+0B0h], eax ; ContextRecord.EAX
        .text:00XX1FAE FF 86 B8 00 00 00    inc     dword ptr [esi+0B8h] ; ContextRecord.EIP
        .text:00XX1FB4 33 C0                xor     eax, eax
    */


    /* remove ContextRecord null check */

    // nop (x7)
    nopExe(0x1F74, 7);


    /* skip storage of result in ContextRecord and skip clearing the return value */

    // nop (x14)
    nopExe(0x1FA8, 14);
}


void removeDebugChecks() {

    /* skip CheckRemoteDebuggerPresent call and spoof return value */

    // push (x2) -> nop (x3)
    nopExe(0x25F5, 3);

    // call eax -> xor eax, eax
    patchExe<uint16_t>(0x25F8, 0xC033);


    /* skip NtQueryInformationProcess call and spoof return value */

    // push (x2) -> nop (x4)
    nopExe(0x26AB, 4);

    // push (x3) -> nop (x5)
    nopExe(0x26B9, 5);

    // call eax -> xor eax, eax
    patchExe<uint16_t>(0x26BE, 0xC033);


    /* skip NtSetInformationThread call and spoof return value */

    // push (x4) -> nop (x8)
    nopExe(0x276E, 8);

    // call eax -> xor eax, eax
    patchExe<uint16_t>(0x2776, 0xC033);
}


void nopExe(DWORD offset, size_t count)
{
    nopPtr(getExeAddress(offset), count);
}
