#pragma once

#include "stdafx.h"
#include "utils.h"


UINT_PTR mProcs[81] = { 0 };

LPCSTR mImportNames[] = {
  "_CreateFrameInfo",
  "_CxxThrowException",
  "_EH_prolog",
  "_FindAndUnlinkFrame",
  "_IsExceptionObjectToBeDestroyed",
  "_NLG_Dispatch2",
  "_NLG_Return",
  "_NLG_Return2",
  "_SetWinRTOutOfMemoryExceptionCallback",
  "__AdjustPointer",
  "__BuildCatchObject",
  "__BuildCatchObjectHelper",
  "__CxxDetectRethrow",
  "__CxxExceptionFilter",
  "__CxxFrameHandler",
  "__CxxFrameHandler2",
  "__CxxFrameHandler3",
  "__CxxLongjmpUnwind",
  "__CxxQueryExceptionSize",
  "__CxxRegisterExceptionObject",
  "__CxxUnregisterExceptionObject",
  "__DestructExceptionObject",
  "__FrameUnwindFilter",
  "__GetPlatformExceptionInfo",
  "__RTCastToVoid",
  "__RTDynamicCast",
  "__RTtypeid",
  "__TypeMatch",
  "__current_exception",
  "__current_exception_context",
  "__intrinsic_setjmp",
  "__processing_throw",
  "__report_gsfailure",
  "__std_exception_copy",
  "__std_exception_destroy",
  "__std_terminate",
  "__std_type_info_compare",
  "__std_type_info_destroy_list",
  "__std_type_info_hash",
  "__std_type_info_name",
  "__telemetry_main_invoke_trigger",
  "__telemetry_main_return_trigger",
  "__unDName",
  "__unDNameEx",
  "__uncaught_exception",
  "__uncaught_exceptions",
  "__vcrt_GetModuleFileNameW",
  "__vcrt_GetModuleHandleW",
  "__vcrt_InitializeCriticalSectionEx",
  "__vcrt_LoadLibraryExW",
  "_chkesp",
  "_except_handler2",
  "_except_handler3",
  "_except_handler4_common",
  "_get_purecall_handler",
  "_get_unexpected",
  "_global_unwind2",
  "_is_exception_typeof",
  "_local_unwind2",
  "_local_unwind4",
  "_longjmpex",
  "_purecall",
  "_seh_longjmp_unwind",
  "_seh_longjmp_unwind4",
  "_set_purecall_handler",
  "_set_se_translator",
  "_setjmp3",
  "longjmp",
  "memchr",
  "memcmp",
  "memcpy",
  "memmove",
  "memset",
  "set_unexpected",
  "strchr",
  "strrchr",
  "strstr",
  "unexpected",
  "wcschr",
  "wcsrchr",
  "wcsstr",
};

extern "C" __declspec(naked) void __stdcall _CreateFrameInfo_wrapper() {
    log_write("calling _CreateFrameInfo");
    __asm {jmp mProcs[0 * 4]}
}
extern "C" __declspec(naked) void __stdcall _CxxThrowException_wrapper() {
    log_write("calling _CxxThrowException");
    __asm {jmp mProcs[1 * 4]}
}
extern "C" __declspec(naked) void __stdcall _EH_prolog_wrapper() {
    log_write("calling _EH_prolog");
    __asm {jmp mProcs[2 * 4]}
}
extern "C" __declspec(naked) void __stdcall _FindAndUnlinkFrame_wrapper() {
    log_write("calling _FindAndUnlinkFrame");
    __asm {jmp mProcs[3 * 4]}
}
extern "C" __declspec(naked) void __stdcall _IsExceptionObjectToBeDestroyed_wrapper() {
    log_write("calling _IsExceptionObjectToBeDestroyed");
    __asm {jmp mProcs[4 * 4]}
}
extern "C" __declspec(naked) void __stdcall _NLG_Dispatch2_wrapper() {
    log_write("calling _NLG_Dispatch2");
    __asm {jmp mProcs[5 * 4]}
}
extern "C" __declspec(naked) void __stdcall _NLG_Return_wrapper() {
    log_write("calling _NLG_Return");
    __asm {jmp mProcs[6 * 4]}
}
extern "C" __declspec(naked) void __stdcall _NLG_Return2_wrapper() {
    log_write("calling _NLG_Return2");
    __asm {jmp mProcs[7 * 4]}
}
extern "C" __declspec(naked) void __stdcall _SetWinRTOutOfMemoryExceptionCallback_wrapper() {
    log_write("calling _SetWinRTOutOfMemoryExceptionCallback");
    __asm {jmp mProcs[8 * 4]}
}
extern "C" __declspec(naked) void __stdcall __AdjustPointer_wrapper() {
    log_write("calling __AdjustPointer");
    __asm {jmp mProcs[9 * 4]}
}
extern "C" __declspec(naked) void __stdcall __BuildCatchObject_wrapper() {
    log_write("calling __BuildCatchObject");
    __asm {jmp mProcs[10 * 4]}
}
extern "C" __declspec(naked) void __stdcall __BuildCatchObjectHelper_wrapper() {
    log_write("calling __BuildCatchObjectHelper");
    __asm {jmp mProcs[11 * 4]}
}
extern "C" __declspec(naked) void __stdcall __CxxDetectRethrow_wrapper() {
    log_write("calling __CxxDetectRethrow");
    __asm {jmp mProcs[12 * 4]}
}
extern "C" __declspec(naked) void __stdcall __CxxExceptionFilter_wrapper() {
    log_write("calling __CxxExceptionFilter");
    __asm {jmp mProcs[13 * 4]}
}
extern "C" __declspec(naked) void __stdcall __CxxFrameHandler_wrapper() {
    log_write("calling __CxxFrameHandler");
    __asm {jmp mProcs[14 * 4]}
}
extern "C" __declspec(naked) void __stdcall __CxxFrameHandler2_wrapper() {
    log_write("calling __CxxFrameHandler2");
    __asm {jmp mProcs[15 * 4]}
}
extern "C" __declspec(naked) void __stdcall __CxxFrameHandler3_wrapper() {
    log_write("calling __CxxFrameHandler3");
    __asm {jmp mProcs[16 * 4]}
}
extern "C" __declspec(naked) void __stdcall __CxxLongjmpUnwind_wrapper() {
    log_write("calling __CxxLongjmpUnwind");
    __asm {jmp mProcs[17 * 4]}
}
extern "C" __declspec(naked) void __stdcall __CxxQueryExceptionSize_wrapper() {
    log_write("calling __CxxQueryExceptionSize");
    __asm {jmp mProcs[18 * 4]}
}
extern "C" __declspec(naked) void __stdcall __CxxRegisterExceptionObject_wrapper() {
    log_write("calling __CxxRegisterExceptionObject");
    __asm {jmp mProcs[19 * 4]}
}
extern "C" __declspec(naked) void __stdcall __CxxUnregisterExceptionObject_wrapper() {
    log_write("calling __CxxUnregisterExceptionObject");
    __asm {jmp mProcs[20 * 4]}
}
extern "C" __declspec(naked) void __stdcall __DestructExceptionObject_wrapper() {
    log_write("calling __DestructExceptionObject");
    __asm {jmp mProcs[21 * 4]}
}
extern "C" __declspec(naked) void __stdcall __FrameUnwindFilter_wrapper() {
    log_write("calling __FrameUnwindFilter");
    __asm {jmp mProcs[22 * 4]}
}
extern "C" __declspec(naked) void __stdcall __GetPlatformExceptionInfo_wrapper() {
    log_write("calling __GetPlatformExceptionInfo");
    __asm {jmp mProcs[23 * 4]}
}
extern "C" __declspec(naked) void __stdcall __RTCastToVoid_wrapper() {
    log_write("calling __RTCastToVoid");
    __asm {jmp mProcs[24 * 4]}
}
extern "C" __declspec(naked) void __stdcall __RTDynamicCast_wrapper() {
    log_write("calling __RTDynamicCast");
    __asm {jmp mProcs[25 * 4]}
}
extern "C" __declspec(naked) void __stdcall __RTtypeid_wrapper() {
    log_write("calling __RTtypeid");
    __asm {jmp mProcs[26 * 4]}
}
extern "C" __declspec(naked) void __stdcall __TypeMatch_wrapper() {
    log_write("calling __TypeMatch");
    __asm {jmp mProcs[27 * 4]}
}
extern "C" __declspec(naked) void __stdcall __current_exception_wrapper() {
    log_write("calling __current_exception");
    __asm {jmp mProcs[28 * 4]}
}
extern "C" __declspec(naked) void __stdcall __current_exception_context_wrapper() {
    log_write("calling __current_exception_context");
    __asm {jmp mProcs[29 * 4]}
}
extern "C" __declspec(naked) void __stdcall __intrinsic_setjmp_wrapper() {
    log_write("calling __intrinsic_setjmp");
    __asm {jmp mProcs[30 * 4]}
}
extern "C" __declspec(naked) void __stdcall __processing_throw_wrapper() {
    log_write("calling __processing_throw");
    __asm {jmp mProcs[31 * 4]}
}
extern "C" __declspec(naked) void __stdcall __report_gsfailure_wrapper() {
    log_write("calling __report_gsfailure");
    __asm {jmp mProcs[32 * 4]}
}
extern "C" __declspec(naked) void __stdcall __std_exception_copy_wrapper() {
    log_write("calling __std_exception_copy");
    __asm {jmp mProcs[33 * 4]}
}
extern "C" __declspec(naked) void __stdcall __std_exception_destroy_wrapper() {
    log_write("calling __std_exception_destroy");
    __asm {jmp mProcs[34 * 4]}
}
extern "C" __declspec(naked) void __stdcall __std_terminate_wrapper() {
    log_write("calling __std_terminate");
    __asm {jmp mProcs[35 * 4]}
}
extern "C" __declspec(naked) void __stdcall __std_type_info_compare_wrapper() {
    log_write("calling __std_type_info_compare");
    __asm {jmp mProcs[36 * 4]}
}
extern "C" __declspec(naked) void __stdcall __std_type_info_destroy_list_wrapper() {
    log_write("calling __std_type_info_destroy_list");
    __asm {jmp mProcs[37 * 4]}
}
extern "C" __declspec(naked) void __stdcall __std_type_info_hash_wrapper() {
    log_write("calling __std_type_info_hash");
    __asm {jmp mProcs[38 * 4]}
}
extern "C" __declspec(naked) void __stdcall __std_type_info_name_wrapper() {
    log_write("calling __std_type_info_name");
    __asm {jmp mProcs[39 * 4]}
}
extern "C" __declspec(naked) void __stdcall __telemetry_main_invoke_trigger_wrapper() {
    log_write("calling __telemetry_main_invoke_trigger");
    __asm {jmp mProcs[40 * 4]}
}
extern "C" __declspec(naked) void __stdcall __telemetry_main_return_trigger_wrapper() {
    log_write("calling __telemetry_main_return_trigger");
    __asm {jmp mProcs[41 * 4]}
}
extern "C" __declspec(naked) void __stdcall __unDName_wrapper() {
    log_write("calling __unDName");
    __asm {jmp mProcs[42 * 4]}
}
extern "C" __declspec(naked) void __stdcall __unDNameEx_wrapper() {
    log_write("calling __unDNameEx");
    __asm {jmp mProcs[43 * 4]}
}
extern "C" __declspec(naked) void __stdcall __uncaught_exception_wrapper() {
    log_write("calling __uncaught_exception");
    __asm {jmp mProcs[44 * 4]}
}
extern "C" __declspec(naked) void __stdcall __uncaught_exceptions_wrapper() {
    log_write("calling __uncaught_exceptions");
    __asm {jmp mProcs[45 * 4]}
}
extern "C" __declspec(naked) void __stdcall __vcrt_GetModuleFileNameW_wrapper() {
    log_write("calling __vcrt_GetModuleFileNameW");
    __asm {jmp mProcs[46 * 4]}
}
extern "C" __declspec(naked) void __stdcall __vcrt_GetModuleHandleW_wrapper() {
    log_write("calling __vcrt_GetModuleHandleW");
    __asm {jmp mProcs[47 * 4]}
}
extern "C" __declspec(naked) void __stdcall __vcrt_InitializeCriticalSectionEx_wrapper() {
    log_write("calling __vcrt_InitializeCriticalSectionEx");
    __asm {jmp mProcs[48 * 4]}
}
extern "C" __declspec(naked) void __stdcall __vcrt_LoadLibraryExW_wrapper() {
    log_write("calling __vcrt_LoadLibraryExW");
    __asm {jmp mProcs[49 * 4]}
}
extern "C" __declspec(naked) void __stdcall _chkesp_wrapper() {
    log_write("calling _chkesp");
    __asm {jmp mProcs[50 * 4]}
}
extern "C" __declspec(naked) void __stdcall _except_handler2_wrapper() {
    log_write("calling _except_handler2");
    __asm {jmp mProcs[51 * 4]}
}
extern "C" __declspec(naked) void __stdcall _except_handler3_wrapper() {
    log_write("calling _except_handler3");
    __asm {jmp mProcs[52 * 4]}
}
extern "C" __declspec(naked) void __stdcall _except_handler4_common_wrapper() {
    log_write("calling _except_handler4_common");
    __asm {jmp mProcs[53 * 4]}
}
extern "C" __declspec(naked) void __stdcall _get_purecall_handler_wrapper() {
    log_write("calling _get_purecall_handler");
    __asm {jmp mProcs[54 * 4]}
}
extern "C" __declspec(naked) void __stdcall _get_unexpected_wrapper() {
    log_write("calling _get_unexpected");
    __asm {jmp mProcs[55 * 4]}
}
extern "C" __declspec(naked) void __stdcall _global_unwind2_wrapper() {
    log_write("calling _global_unwind2");
    __asm {jmp mProcs[56 * 4]}
}
extern "C" __declspec(naked) void __stdcall _is_exception_typeof_wrapper() {
    log_write("calling _is_exception_typeof");
    __asm {jmp mProcs[57 * 4]}
}
extern "C" __declspec(naked) void __stdcall _local_unwind2_wrapper() {
    log_write("calling _local_unwind2");
    __asm {jmp mProcs[58 * 4]}
}
extern "C" __declspec(naked) void __stdcall _local_unwind4_wrapper() {
    log_write("calling _local_unwind4");
    __asm {jmp mProcs[59 * 4]}
}
extern "C" __declspec(naked) void __stdcall _longjmpex_wrapper() {
    log_write("calling _longjmpex");
    __asm {jmp mProcs[60 * 4]}
}
extern "C" __declspec(naked) void __stdcall _purecall_wrapper() {
    log_write("calling _purecall");
    __asm {jmp mProcs[61 * 4]}
}
extern "C" __declspec(naked) void __stdcall _seh_longjmp_unwind_wrapper() {
    log_write("calling _seh_longjmp_unwind");
    __asm {jmp mProcs[62 * 4]}
}
extern "C" __declspec(naked) void __stdcall _seh_longjmp_unwind4_wrapper() {
    log_write("calling _seh_longjmp_unwind4");
    __asm {jmp mProcs[63 * 4]}
}
extern "C" __declspec(naked) void __stdcall _set_purecall_handler_wrapper() {
    log_write("calling _set_purecall_handler");
    __asm {jmp mProcs[64 * 4]}
}
extern "C" __declspec(naked) void __stdcall _set_se_translator_wrapper() {
    log_write("calling _set_se_translator");
    __asm {jmp mProcs[65 * 4]}
}
extern "C" __declspec(naked) void __stdcall _setjmp3_wrapper() {
    log_write("calling _setjmp3");
    __asm {jmp mProcs[66 * 4]}
}
extern "C" __declspec(naked) void __stdcall longjmp_wrapper() {
    log_write("calling longjmp");
    __asm {jmp mProcs[67 * 4]}
}
extern "C" __declspec(naked) void __stdcall memchr_wrapper() {
    log_write("calling memchr");
    __asm {jmp mProcs[68 * 4]}
}
extern "C" __declspec(naked) void __stdcall memcmp_wrapper() {
    log_write("calling memcmp");
    __asm {jmp mProcs[69 * 4]}
}
extern "C" __declspec(naked) void __stdcall memcpy_wrapper() {
    log_write("calling memcpy");
    __asm {jmp mProcs[70 * 4]}
}
extern "C" __declspec(naked) void __stdcall memmove_wrapper() {
    log_write("calling memmove");
    __asm {jmp mProcs[71 * 4]}
}
extern "C" __declspec(naked) void __stdcall memset_wrapper() {
    log_write("calling memset");
    __asm {jmp mProcs[72 * 4]}
}
extern "C" __declspec(naked) void __stdcall set_unexpected_wrapper() {
    log_write("calling set_unexpected");
    __asm {jmp mProcs[73 * 4]}
}
extern "C" __declspec(naked) void __stdcall strchr_wrapper() {
    log_write("calling strchr");
    __asm {jmp mProcs[74 * 4]}
}
extern "C" __declspec(naked) void __stdcall strrchr_wrapper() {
    log_write("calling strrchr");
    __asm {jmp mProcs[75 * 4]}
}
extern "C" __declspec(naked) void __stdcall strstr_wrapper() {
    log_write("calling strstr");
    __asm {jmp mProcs[76 * 4]}
}
extern "C" __declspec(naked) void __stdcall unexpected_wrapper() {
    log_write("calling unexpected");
    __asm {jmp mProcs[77 * 4]}
}
extern "C" __declspec(naked) void __stdcall wcschr_wrapper() {
    log_write("calling wcschr");
    __asm {jmp mProcs[78 * 4]}
}
extern "C" __declspec(naked) void __stdcall wcsrchr_wrapper() {
    log_write("calling wcsrchr");
    __asm {jmp mProcs[79 * 4]}
}
extern "C" __declspec(naked) void __stdcall wcsstr_wrapper() {
    log_write("calling wcsstr");
    __asm {jmp mProcs[80 * 4]}
}
