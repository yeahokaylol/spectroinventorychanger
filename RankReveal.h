#pragma once


using ServerRankRevealAllFn = bool(__cdecl*)(float*);
namespace Ranks
{
	extern ServerRankRevealAllFn ServerRankRevealAllEx = NULL;
	extern void ServerRankRevealAll();
}
