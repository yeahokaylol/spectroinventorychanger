#include "stdafx.h"
#include "PredSys.h"

CPredictionSystem* g_PredictionSystem = new CPredictionSystem;
void CPredictionSystem::StartPrediction() {


	CBaseEntity *pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
	static bool bInit = false;
	if (!bInit) {
		m_pPredictionRandomSeed = *(int**)(Utils.FindPatternIDA("client_panorama.dll", "8B 0D ? ? ? ? BA ? ? ? ? E8 ? ? ? ? 83 C4 04") + 2);
		bInit = true;
	}


	*m_pPredictionRandomSeed = Hacks.CurrentCmd->random_seed;


	m_flOldCurtime = Interfaces.pGlobalVars->curtime;
	m_flOldFrametime = Interfaces.pGlobalVars->frametime;

	Interfaces.pGlobalVars->curtime = pLocal->GetTickBase() * Interfaces.pGlobalVars->interval_per_tick;
	Interfaces.pGlobalVars->frametime = Interfaces.pGlobalVars->interval_per_tick;

	Interfaces.g_pGameMovement->StartTrackPredictionErrors(pLocal);

	memset(&m_MoveData, 0, sizeof(m_MoveData));
	Interfaces.g_pMoveHelper->SetHost(pLocal);
	Interfaces.g_pPred->SetupMove(pLocal, Hacks.CurrentCmd, Interfaces.g_pMoveHelper, &m_MoveData);
	Interfaces.g_pGameMovement->ProcessMovement(pLocal, &m_MoveData);
	Interfaces.g_pPred->FinishMove(pLocal, Hacks.CurrentCmd, &m_MoveData);

}

void CPredictionSystem::EndPrediction() {

	CBaseEntity *pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
	Interfaces.g_pGameMovement->FinishTrackPredictionErrors(pLocal);
	Interfaces.g_pMoveHelper->SetHost(0);

	*m_pPredictionRandomSeed = -1;

	Interfaces.pGlobalVars->curtime = m_flOldCurtime;
	Interfaces.pGlobalVars->frametime = m_flOldFrametime;
}