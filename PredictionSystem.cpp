#include "stdafx.h"
#include "PredictionSystem.h"
#include "SDK\SDK Headers\Valve\checksum.h"
CPredictionSystem* PredictionSystem = new CPredictionSystem;

void CPredictionSystem::StartPrediction()
{
	static bool bInit = false;
	if (!bInit) {
		m_pPredictionRandomSeed = *(int**)(Utils.PatternScan("client.dll", "8B 0D ? ? ? ? BA ? ? ? ? E8 ? ? ? ? 83 C4 04") + 2);
		bInit = true;
	}

	*m_pPredictionRandomSeed = Hacks.CurrentCmd->command_number & 0x7FFFFFFF;//Hacks.CurrentCmd->random_seed;

	m_flOldCurtime = Interfaces.pGlobalVars->curtime;
	m_flOldFrametime = Interfaces.pGlobalVars->frametime;

	Interfaces.pGlobalVars->curtime = Hacks.LocalPlayer->GetTickBase() * Interfaces.pGlobalVars->interval_per_tick;
	Interfaces.pGlobalVars->frametime = Interfaces.pGlobalVars->interval_per_tick;

	Interfaces.g_pGameMovement->StartTrackPredictionErrors(Hacks.LocalPlayer);

	memset(&m_MoveData, 0, sizeof(m_MoveData));
	Interfaces.g_pMoveHelper->SetHost(Hacks.LocalPlayer);
	Interfaces.g_pPred->SetupMove(Hacks.LocalPlayer, Hacks.CurrentCmd, Interfaces.g_pMoveHelper, &m_MoveData);
	Interfaces.g_pGameMovement->ProcessMovement(Hacks.LocalPlayer, &m_MoveData);
	Interfaces.g_pPred->FinishMove(Hacks.LocalPlayer, Hacks.CurrentCmd, &m_MoveData);
}

void CPredictionSystem::EndPrediction()
{
	Interfaces.g_pGameMovement->FinishTrackPredictionErrors(Hacks.LocalPlayer);
	Interfaces.g_pMoveHelper->SetHost(0);

	*m_pPredictionRandomSeed = -1;
	Interfaces.pGlobalVars->curtime = m_flOldCurtime;
	Interfaces.pGlobalVars->frametime = m_flOldFrametime;
}