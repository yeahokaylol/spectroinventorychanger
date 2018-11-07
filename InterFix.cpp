#include "InterFix.h"

bool Meme = false;

namespace InterpFix {
	IsPlayingTimeDemo_t g_fnOriginalPlayingTimeDemo;
	bool __fastcall HookedIsPlayingTimeDemo(void* thisptr, void* edx) {
		bool bResult = g_fnOriginalPlayingTimeDemo(thisptr);
		if (Meme) {
			CBaseEntity *pLocalPlayer = Hacks.LocalPlayer;

			if (Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected())
				if (pLocalPlayer->isAlive() /*&& !pLocalPlayer->InBuyZone()*/)
					return true;
		}
		return bResult;
	}
}