#pragma once

#include "stdafx.h"

class CPredictionSystem
{
public:
	void StartPrediction(CUserCmd *userCMD, CBaseEntity* player);
	void EndPrediction(CBaseEntity* player);

private:
	float m_flOldCurtime;
	float m_flOldFrametime;
	CMoveData m_MoveData;
	CBaseEntity *predictionPlayer;
	int* m_pPredictionRandomSeed;
};

extern CPredictionSystem* PredictionSystem;