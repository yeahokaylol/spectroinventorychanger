// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "RenderD9.h"
#include "detours/detours.h"



VOID(WINAPI * OriginalSleep) (DWORD) = Sleep;
DWORD(WINAPI * OriginalSleepEx) (DWORD, BOOL) = SleepEx;

VOID WINAPI FakeSleep(DWORD dwMs)
{
	OriginalSleep(dwMs);
};

DWORD WINAPI FakeSleepEx(DWORD dwMs, BOOL bAlert)
{
	return OriginalSleepEx(dwMs, bAlert);
};


DWORD WINAPI DllMain( HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved )
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		
		::DisableThreadLibraryCalls(hModule);
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID &)OriginalSleep, FakeSleep);
		DetourAttach(&(PVOID &)OriginalSleepEx, FakeSleepEx);
		DetourTransactionCommit();
		INIT::Exit = false;
		INIT::Dll = hModule;

		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&CheatMain, hModule, 0, NULL);




		

	}
	else if (ul_reason_for_call == DLL_PROCESS_DETACH)
	{
		INIT::Exit = true;
	}
	else if (ul_reason_for_call == DLL_THREAD_ATTACH)
	{

	}
	else if (ul_reason_for_call == DLL_THREAD_DETACH)
	{

	}
	return 1;
}
