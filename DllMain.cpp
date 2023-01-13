// dllmain.cpp : Defines the entry point for the DLL application.
#define _CRT_SECURE_NO_WARNINGS 1
#include "framework.hpp"

extern "C" void Initialize_CreateAudioReverb(UINT64 address);
extern "C" void Initialize_CreateAudioVolumeMeter(UINT64 address);
extern "C" void Initialize_XAudio2Create(UINT64 address);
extern "C" void Initialize_X3DAudioInitialize(UINT64 address);
extern "C" void Initialize_X3DAudioCalculate(UINT64 address);
extern "C" void Initialize_CreateFX(UINT64 address);

VOID PlaceHooks() //ANTI-CHEAT BYPASS
{
    HMODULE user32 = GetModuleHandleW(L"USER32.dll");
    
    if (user32)
    {
        UINT64 PostMessageW_Addr = (UINT64)GetProcAddress(user32, "PostMessageW");

        if (PostMessageW_Addr)
        {
			       printf("Setting hook at: %llX\n", PostMessageW_Addr);
			       PostMessageWHook_Init(PostMessageW_Addr + 5);
			       Hooks::InstallHook((void*)PostMessageW_Addr, PostMessageWHook);
        }

		UINT64 GetClassNameW_Addr = (UINT64)GetProcAddress(user32, "GetClassNameW");

		if (GetClassNameW_Addr)
		{
			printf("Setting hook at: %llX\n", GetClassNameW_Addr);
			GetClassNameWHook_Init(GetClassNameW_Addr + 5);
			Hooks::InstallHook((void*)GetClassNameW_Addr, GetClassNameWHook); //somehow this was working with postmessagew hook? wtf
		}
      
	HMODULE k32 = GetModuleHandleW(L"kernel32.dll");

	if (k32)
	{
		HMODULE kernelbase = GetModuleHandleW(L"KERNELBASE.dll");

		if (kernelbase)
		{
			UINT64 OpenProcess_Addr = (UINT64)GetProcAddress(kernelbase, "OpenProcess");

			if (OpenProcess_Addr)
			{
				printf("Setting hook at: %llX\n", OpenProcess_Addr);
				OpenProcessHook_Init(OpenProcess_Addr + 7);
				Hooks::InstallHook((void*)OpenProcess_Addr, OpenProcessHook);
			}

			UINT64 GetVolumeInfoW_Addr = (UINT64)GetProcAddress(kernelbase, "GetVolumeInformationW");
			if (GetVolumeInfoW_Addr)
			{
				printf("Setting hook at: %llX (GetVolumeInfoW)\n", GetVolumeInfoW_Addr);
				
				GetVolumeInformationWHook_Init(GetVolumeInfoW_Addr + 7);
				Hooks::InstallHook((void*)GetVolumeInfoW_Addr, GetVolumeInformationWHook);
			}
		}
	}
}


BOOL APIENTRY DllMain( HMODULE hModule,  DWORD  ul_reason_for_call,  LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
	case DLL_PROCESS_ATTACH:
	{
		//string hwid = GetHardwareID();

		//if (strcmp(hwid.c_str(), "ADMINPC-115632346") == 0) //initialize dll stuff if hwid is fine
		//{
			HMODULE xaudio9 = LoadLibraryA("XAudio2_9redist_REAL.dll"); //SPOOF DLL, ORIGINAL FILE TO RE-DIRECT FUNCTIONS TO

			if (xaudio9)
			{
				UINT64 CreateAudioReverb_Addr = (UINT64)GetProcAddress(xaudio9, "CreateAudioReverb");

				if (CreateAudioReverb_Addr)
				{
					printf("Initialize_CreateAudioReverb\n");
					Initialize_CreateAudioReverb(CreateAudioReverb_Addr);
				}

				UINT64 CreateFX_Addr = (UINT64)GetProcAddress(xaudio9, "CreateFX");

				if (CreateFX_Addr)
				{
					printf("CreateFX\n");
					Initialize_CreateFX(CreateFX_Addr);
				}

				UINT64 X3DAudioCalculate_Addr = (UINT64)GetProcAddress(xaudio9, "X3DAudioCalculate");

				if (X3DAudioCalculate_Addr)
				{
					printf("X3DAudioCalculate\n");
					Initialize_X3DAudioCalculate(X3DAudioCalculate_Addr);
				}

				UINT64 X3DAudioInitialize_Addr = (UINT64)GetProcAddress(xaudio9, "X3DAudioInitialize");

				if (X3DAudioInitialize_Addr)
				{
					printf("X3DAudioInitialize\n");
					Initialize_X3DAudioInitialize(X3DAudioInitialize_Addr);
				}

				UINT64 CreateAudioVolumeMeter_Addr = (UINT64)GetProcAddress(xaudio9, "CreateAudioVolumeMeter");

				if (CreateAudioVolumeMeter_Addr)
				{
					printf("CreateAudioVolumeMeter\n");
					Initialize_CreateAudioVolumeMeter(CreateAudioVolumeMeter_Addr);
				}

				UINT64 XAudio2Create_Addr = (UINT64)GetProcAddress(xaudio9, "XAudio2Create");

				if (XAudio2Create_Addr)
				{
					printf("XAudio2Create\n");
					Initialize_XAudio2Create(XAudio2Create_Addr);
				}
			}

			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&PlaceHooks, 0, 0, 0);
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&InitializeGUIs, 0, 0, 0);
		//}
		//else
		//{
		//	FreeLibraryAndExitThread(GetModuleHandleA("XAudio2_9redist.dll"), 0);
		//	TerminateProcess(GetCurrentProcess(), 0);
		//}

		AllocConsole();
		freopen("CON", "w", stdout);
		freopen("CON", "r", stdin);	
	}break;
          
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
