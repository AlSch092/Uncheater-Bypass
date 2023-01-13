#pragma once
//#include "PacketParsing.hpp"
#include <windows.h>
#include <stdint.h>

extern std::queue<PacketWriter*> SendPacketQueue;

//Anticheat functions
extern "C" void GetWindowHook_Init(UINT64 ReturnAddress);
extern "C" void GetWindowHook(HWND hwnd, UINT ucmd);

extern "C" void PostMessageWHook_Init(UINT64 ReturnAddress);
extern "C" void PostMessageWHook(HWND hwnd, UINT Msg, WPARAM wparam, LPARAM lparam);

extern "C" void GetModuleHandleWHook_Init(UINT64 ReturnAddress);
extern "C" void GetModuleHandleWHook(LPCWSTR name);

extern "C" void GetClassNameWHook_Init(UINT64 ReturnAddress);
extern "C" void GetClassNameWHook(HWND hwnd, LPWSTR lpClassName, int nMaxCount);

extern "C" void GetWindowThreadProcessId_Init(UINT64 ReturnAddress);
extern "C" void GetWindowThreadProcess_Hook();

extern "C" void OpenProcessHook_Init(UINT64 Return);
extern "C" void OpenProcessHook(DWORD desiredAccess, BOOL binherit, DWORD dwProcessId);

extern "C" void GetVolumeInformationWHook();
extern "C" void GetVolumeInformationWHook_Init(UINT64 returnAddr);

//Ingame functions
extern "C" void SetSendBuffer_HookInitialize(UINT64 _ReturnAddr, UINT64 _Callback);
extern "C" void SetSendBuffer_Hook();

extern "C" void SetPositionHook_Init(UINT64 _ReturnAddr, UINT64 _Callback);
extern "C" void PlayerPosition_Hook();

extern "C" void ClientDebugLog_Init(UINT64 _ReturnAddr, UINT64 _Callback);
extern "C" void ClientDebugLog_Hook();

namespace Hooks
{
	VOID InstallHook(void* func2hook, void* payloadFunction);
	VOID WriteAbsoluteJump64(void* absJumpMemory, void* addrToJumpTo);
	VOID RemoveHook(UINT64 HookAddress, INT ByteLength, BYTE* OriginalBytes);
	VOID* AllocatePageNearAddress(void* targetAddr);

	//BOOL hk_SetSendBuffer(BYTE* data, INT Length); //
	//VOID ClientDebugLogCallback(LPVOID message);
}
