#include "stdafx.h"
int G::MapName = NULL;
bool G::d3dinit = false;
float G::CurTime;
float  G::KillStopDelay = 0.f;
matrix3x4 G::localPlayerLbyBones[128];
MsgFn oMsg;
LineGoesThroughSmokeFn G::LineToSmoke = NULL;
int G::AimbotID = NULL;
float G::viewMatrix[4][4] = { 0 };
bool G::pressedKeys[256];

CBaseEntity* G::LocalPlayer = NULL;
void __cdecl G::Msg(char const* msg, ...)
{
	//DOES NOT CRASH
	if (!oMsg)
		oMsg = (MsgFn)GetProcAddress(GetModuleHandle(("tier0.dll")), ("Msg"));

	char buffer[989];
	va_list list;
	va_start(list, msg);
	vsprintf_s(buffer, msg, list);
	va_end(list);
	oMsg(buffer, list);
}