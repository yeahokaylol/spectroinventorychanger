#pragma once
#include "stdafx.h"



typedef void(__cdecl *MsgFn)(char const* pMsg, va_list);

typedef bool(*LineGoesThroughSmokeFn) (Vector, Vector, int16_t);



namespace G
{
	extern LineGoesThroughSmokeFn LineToSmoke;
	extern float KillStopDelay;
	extern bool d3dinit;
	extern int MapName;
	extern void __cdecl Msg(char const* msg, ...);
	extern matrix3x4 localPlayerLbyBones[128];
	extern int AimbotID;
	extern float viewMatrix[4][4];
	extern bool pressedKeys[256];
	extern CBaseEntity* LocalPlayer;
	extern float CurTime;

}