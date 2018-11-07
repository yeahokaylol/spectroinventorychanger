#pragma once
#include "stdafx.h"
#include <deque>

struct LayerRecord
{
	LayerRecord()
	{
		m_nOrder = 0;
		m_nSequence = 0;
		m_flWeight = 0.f;
		m_flCycle = 0.f;
	}

	LayerRecord(const LayerRecord &src)
	{
		m_nOrder = src.m_nOrder;
		m_nSequence = src.m_nSequence;
		m_flWeight = src.m_flWeight;
		m_flCycle = src.m_flCycle;
	}

	uint32_t m_nOrder;
	uint32_t m_nSequence;
	float_t m_flWeight;
	float_t m_flCycle;
};

struct LagRecordNew
{
	LagRecordNew()
	{
		m_iPriority = -1;

		m_flSimulationTime = -1.f;
		m_vecOrigin.Init();
		m_angAngles.Init();
		m_bMatrixBuilt = false;
	}

	bool operator==(const LagRecordNew &rec)
	{
		return (m_flSimulationTime == rec.m_flSimulationTime) &&
			(m_vecVelocity == m_vecVelocity);
	}

	void SaveRecord(CBaseEntity *player);

	matrix3x4	matrix[128];

	bool m_bMatrixBuilt;
	float m_iTickCount;

	// For priority/other checks
	int32_t m_iPriority;
	int32_t m_nFlags;
	Vector  m_vecVelocity;
	float_t m_flPrevLowerBodyYaw;
	Vector  m_vecLocalAimspot;
	bool    m_bNoGoodSpots;

	// For backtracking
	float_t m_flSimulationTime;
	Vector m_vecOrigin;	   // Server data, change to this for accuracy
	Vector m_angAngles;
	Vector m_angEye;
	std::array<float_t, 24> m_arrflPoseParameters;
	std::array<LayerRecord, 15> m_LayerRecords;

};

class CMBacktracking : public Singleton<CMBacktracking>
{
public:

	LagRecordNew m_PlayerSaveRecords[64];
	std::deque<LagRecordNew> m_LagRecordNew[64];
	std::pair<LagRecordNew, LagRecordNew> m_RestoreLagRecordNew[64];
	
	void CacheInfo(CBaseEntity *player);
	void ProcessCMD(int iTargetIdx, CUserCmd *usercmd);
	void AnimationFix(ClientFrameStage_t stage);
	void RemoveBadRecords(int Idx, std::deque<LagRecordNew>& records);
	bool FindViableRecord(CBaseEntity *player, LagRecordNew* record);
	bool StartLagCompensation(CBaseEntity *player);
	void FinishLagCompensation(CBaseEntity *player);

	int GetPriorityLevel(CBaseEntity *player, LagRecordNew* lag_record);

	
	bool IsTickValid(int tick);
	float GetLerpTime();

	bool m_bStartedLagCompensation = false;

	std::deque<LagRecordNew> backtrack_records;

	template<class T, class U>
	T clamp(T in, U low, U high);
};