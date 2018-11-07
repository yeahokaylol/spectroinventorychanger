
#include "RankReveal.h"
#include "stdafx.h"
ServerRankRevealAllFn G::ServerRankRevealAllEx;

void G::ServerRankRevealAll()
{
	if (Settings.GetSetting(Tab_Visuals, Visuals_ShowRanks) && GetAsyncKeyState(VK_TAB))
	{
		static float fArray[3] = { 0.f, 0.f, 0.f };
		static int RanksEnable = Utils.FindPattern("client.dll", "55 8B EC 8B 0D ? ? ? ? 68 ? ? ? ? ");
		G::ServerRankRevealAllEx = (ServerRankRevealAllFn)(RanksEnable);
		G::ServerRankRevealAllEx(fArray);
	}
}
