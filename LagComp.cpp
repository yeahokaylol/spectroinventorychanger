#include "LagComp.h"
#include "RebuildMoveMent.h"

void LagRecordNew::SaveRecord(CBaseEntity *player)
{
	m_flSimulationTime = player->GetSimulationTime();
	m_arrflPoseParameters = player->m_flPoseParameter();
	m_nFlags = player->GetFlags();
	m_vecVelocity = player->GetVecVelocity();
	m_iTickCount = Interfaces.pGlobalVars->tickcount;
	m_vecOrigin = player->GetAbsOrigin();
	m_angAngles = player->GetEyeAngles();
	m_angEye = player->GetBonePos(8);
	int layerCount = player->GetNumAnimOverlaysAARec();
	for (int i = 0; i < layerCount; i++)
	{
		CAnimationLayer *currentLayer = player->GetAnimOverlayAARec(i);
		m_LayerRecords[i].m_nOrder = currentLayer->m_nOrder;
		m_LayerRecords[i].m_nSequence = currentLayer->m_nSequence;
		m_LayerRecords[i].m_flWeight = currentLayer->m_flWeight;
		m_LayerRecords[i].m_flCycle = currentLayer->m_flCycle;
	}


}
void CMBacktracking::CacheInfo(CBaseEntity* player)
{
	LagRecordNew cur_lagrecord;
	RemoveBadRecords(player->GetIndex(), this->m_LagRecordNew[player->GetIndex()]);

	// Should probably extrapolate position aswell... If we had p choked ticks I would with 1 fcall.

	if (cur_lagrecord.m_flSimulationTime == player->GetSimulationTime() && !GetPriorityLevel(player, &cur_lagrecord))
	{
		return;
	}

	cur_lagrecord.m_iPriority = GetPriorityLevel(player, &cur_lagrecord);
	cur_lagrecord.SaveRecord(player);

	this->m_LagRecordNew[player->GetIndex()].emplace_back(cur_lagrecord);
}
#define TIME_TO_TICKSZ( dt )		( (int)( 0.5f + (float)(dt) /  Interfaces.pGlobalVars->interval_per_tick ) )
void CMBacktracking::ProcessCMD(int iTargetIdx, CUserCmd *usercmd)
{
	LagRecordNew recentLR = m_RestoreLagRecordNew[iTargetIdx].first;
	if (!IsTickValid(TIME_TO_TICKSZ(recentLR.m_flSimulationTime)))
	{
		usercmd->tick_count = TIME_TO_TICKSZ(Interfaces.pEntList->GetClientEntity(iTargetIdx)->GetSimulationTime() + GetLerpTime());
	}
	else
	{
		usercmd->tick_count = TIME_TO_TICKSZ(recentLR.m_flSimulationTime + GetLerpTime());
	}
}


bool CMBacktracking::FindViableRecord(CBaseEntity *player, LagRecordNew* record)
{
	auto& m_LagRecords = this->m_LagRecordNew[player->GetIndex()];

	// Ran out of records to check. Go back.
	if (backtrack_records.empty())
	{
		return false;
	}

	LagRecordNew
		recentLR = *backtrack_records.begin(),
		prevLR;

	// Should still use m_LagRecords because we're checking for LC break.
	auto iter = std::find(m_LagRecords.begin(), m_LagRecords.end(), recentLR);
	auto idx = std::distance(m_LagRecords.begin(), iter);
	if (0 != idx) prevLR = *std::prev(iter);

	// Saving first record for processcmd.
	m_RestoreLagRecordNew[player->GetIndex()].first = recentLR;

	if (!IsTickValid(TIME_TO_TICKSZ(recentLR.m_flSimulationTime)))
	{
		backtrack_records.pop_front();
		return backtrack_records.size() > 0; // RET_NO_RECORDS true false
	}

	// Remove a record...
	backtrack_records.pop_front();

	if ((0 != idx) && (recentLR.m_vecOrigin - prevLR.m_vecOrigin).LengthSqr() > 4096.f)
	{
		float simulationTimeDelta = recentLR.m_flSimulationTime - prevLR.m_flSimulationTime;

		int simulationTickDelta = clamp(TIME_TO_TICKSZ(simulationTimeDelta), 1, 15);

		for (; simulationTickDelta > 0; simulationTickDelta--)
			RebuildGameMovement::Get().FullWalkMove(player);

		// Bandage fix so we "restore" to the lagfixed player.
		m_RestoreLagRecordNew[player->GetIndex()].second.SaveRecord(player);
		*record = m_RestoreLagRecordNew[player->GetIndex()].second;

		// Clear so we don't try to bt shit we can't
		backtrack_records.clear();

		return true; // Return true so we still try to aimbot.
	}
	else
	{
		player->InvalidateBoneCache();
		player->m_flPoseParameter() = recentLR.m_arrflPoseParameters;

		int layerCount = player->GetNumAnimOverlaysAARec();
		for (int i = 0; i < layerCount; ++i)
		{
			CAnimationLayer *currentLayer = player->GetAnimOverlayAARec(i);
			currentLayer->m_nOrder = recentLR.m_LayerRecords[i].m_nOrder;
			currentLayer->m_nSequence = recentLR.m_LayerRecords[i].m_nSequence;
			currentLayer->m_flWeight = recentLR.m_LayerRecords[i].m_flWeight;
			currentLayer->m_flCycle = recentLR.m_LayerRecords[i].m_flCycle;
		}

		player->m_angRotation() = Vector(0, 0, 0);
		player->SetPoseAngles(recentLR.m_angAngles.y, recentLR.m_angAngles.x);

		player->SetAbsAngles(Vector(0, recentLR.m_angAngles.y, 0));
		player->SetAbsOrigin(recentLR.m_vecOrigin);

		//player->UpdateClientSideAnimation();

		*record = recentLR;
		return true;
	}
}
void CMBacktracking::RemoveBadRecords(int Idx, std::deque<LagRecordNew>& records)
{
	auto& m_LagRecordNews = records;
	if (!m_LagRecordNews.empty())
	{
		for (auto lag_record = m_LagRecordNews.begin(); lag_record != m_LagRecordNews.end(); lag_record++)
		{
			if (!IsTickValid(TIME_TO_TICKSZ(lag_record->m_flSimulationTime)))
			{
				m_LagRecordNews.erase(lag_record);
				if (!m_LagRecordNews.empty())
					lag_record = m_LagRecordNews.begin();
				else break;
			}
		}
	}
}

bool CMBacktracking::StartLagCompensation(CBaseEntity *player)
{
	backtrack_records.clear();

	enum
	{
		// Only try to awall the "best" records, otherwise fail.
		TYPE_BEST_RECORDS,
		// Only try to awall the newest and the absolute best record.
		TYPE_BEST_AND_NEWEST,
		// Awall everything (fps killer)
		TYPE_ALL_RECORDS,
		// ONLY LAST TICK
		TYPE_LAST_TICKS,
	};

	auto& m_LagRecords = this->m_LagRecordNew[player->GetIndex()];
	m_RestoreLagRecordNew[player->GetIndex()].second.SaveRecord(player);

	switch (g_Options.Ragebot.LagCompType)
	{
	case TYPE_BEST_RECORDS:
	{
		for (auto it : m_LagRecords)
		{
			if (it.m_iPriority >= 1)
				backtrack_records.emplace_back(it);
			
		}
		break;
	}
	case TYPE_BEST_AND_NEWEST:
	{
		LagRecordNew newest_record = LagRecordNew();
		for (auto it : m_LagRecords)
		{
			if (it.m_flSimulationTime > newest_record.m_flSimulationTime)
				newest_record = it;

			if (it.m_iPriority >= 1 && !(it.m_nFlags & FL_ONGROUND) && it.m_vecVelocity.Length2D() > 150)
				backtrack_records.emplace_back(it);
		}
		backtrack_records.emplace_back(newest_record);
		break;
	}
	case TYPE_ALL_RECORDS:
		// Ouch, the fps drop will be H U G E.
		backtrack_records = m_LagRecords;
		break;

	}

	std::sort(backtrack_records.begin(), backtrack_records.end(), [](LagRecordNew const &a, LagRecordNew const &b) { return a.m_iPriority > b.m_iPriority; });
	return backtrack_records.size() > 0;
}
void CMBacktracking::AnimationFix(ClientFrameStage_t stage)
{
	if (!g_Options.Ragebot.Ragebot_AimbotEnabled || !g_Options.Ragebot.LagComp || !G::LocalPlayer)
		return;

	static int userId[64];
	static CAnimationLayer
		backupLayersUpdate[64][15],
		backupLayersInterp[64][15];

	for (int i = 1; i < Interfaces.pEngine->GetMaxClients(); i++)
	{
		auto player = Interfaces.pEntList->GetClientEntity(i);
		if (!player ||
			player == G::LocalPlayer || !player->isAlive() ||
			player->GetTeam() == G::LocalPlayer->GetTeam() ||
			player->IsDormant() ||
			player->HasGunGameImmunity() )
			continue;

		player_info_t player_info;
		if(!Interfaces.pEngine->GetPlayerInfo(i, &player_info))continue;

		switch (stage)
		{
		case ClientFrameStage_t::FRAME_NET_UPDATE_START: // Copy new, server layers to use when drawing.
			userId[i] = player_info.userID;
			memcpy(&backupLayersUpdate[i], player->GetAnimOverlaysAARec(), (sizeof CAnimationLayer) * player->GetNumAnimOverlaysAARec());
			break;
		case ClientFrameStage_t::FRAME_RENDER_START: // Render started, don't use inaccurately extrapolated layers but save them to not mess shit up either.
			if (userId[i] != player_info.userID) continue;
			memcpy(&backupLayersInterp[i], player->GetAnimOverlaysAARec(), (sizeof CAnimationLayer) * player->GetNumAnimOverlaysAARec());
			memcpy(player->GetAnimOverlaysAARec(), &backupLayersUpdate[i], (sizeof CAnimationLayer) * player->GetNumAnimOverlaysAARec());
			break;
		case ClientFrameStage_t::FRAME_RENDER_END: // Restore layers to keep being accurate when backtracking.
			if (userId[i] != player_info.userID) continue;
			memcpy(player->GetAnimOverlaysAARec(), &backupLayersInterp[i], (sizeof CAnimationLayer) * player->GetNumAnimOverlaysAARec());
			break;
		default:
			return;
		}
	}
}


void CMBacktracking::FinishLagCompensation(CBaseEntity *player)
{
	int idx = player->GetIndex();

	player->InvalidateBoneCache();
	player->m_flPoseParameter() = m_RestoreLagRecordNew[idx].second.m_arrflPoseParameters;

	int layerCount = player->GetNumAnimOverlaysAARec();
	for (int i = 0; i < layerCount; ++i)
	{
		CAnimationLayer *currentLayer = player->GetAnimOverlayAARec(i);
		currentLayer->m_nOrder = m_RestoreLagRecordNew[idx].second.m_LayerRecords[i].m_nOrder;
		currentLayer->m_nSequence = m_RestoreLagRecordNew[idx].second.m_LayerRecords[i].m_nSequence;
		currentLayer->m_flWeight = m_RestoreLagRecordNew[idx].second.m_LayerRecords[i].m_flWeight;
		currentLayer->m_flCycle = m_RestoreLagRecordNew[idx].second.m_LayerRecords[i].m_flCycle;
	}

	player->SetPoseAngles(m_RestoreLagRecordNew[idx].second.m_angAngles.y, m_RestoreLagRecordNew[idx].second.m_angAngles.x);

	player->SetAbsAngles(Vector(0, m_RestoreLagRecordNew[idx].second.m_angAngles.y, 0));
	player->SetAbsOrigin(m_RestoreLagRecordNew[idx].second.m_vecOrigin);
}

int CMBacktracking::GetPriorityLevel(CBaseEntity *player, LagRecordNew* lag_record)
{
	int priority = 0;

	if (lag_record->m_flPrevLowerBodyYaw != player->pelvisangs())
	{
		if (player->GetVecVelocity().Length() > 24.f)
		{
			lag_record->m_angAngles.y = player->pelvisangs();
			priority = 2;
		}
	}

	lag_record->m_flPrevLowerBodyYaw = player->pelvisangs();

	return priority;
}
#define TICKS_TO_TIME( dt )		( Interfaces.pGlobalVars->interval_per_tick * (float)(dt) )
bool CMBacktracking::IsTickValid(int tick)
{
	// better use polak's version than our old one, getting more accurate results
	INetChannelInfo *nci = Interfaces.pEngine->GetNetChannelInfo();

	if (!nci)
		return false;

	auto LerpTicks = TIME_TO_TICKSZ(GetLerpTime());

	int predCmdArrivTick = Interfaces.pGlobalVars->tickcount + 1 + TIME_TO_TICKSZ(nci->GetLatency(FLOW_INCOMING) + nci->GetLatency(FLOW_OUTGOING));

	float flCorrect = clamp(GetLerpTime() + nci->GetLatency(FLOW_OUTGOING), 0.f, 1.f) - TICKS_TO_TIME(predCmdArrivTick + LerpTicks - (tick + TIME_TO_TICKSZ(GetLerpTime())));

	return fabs(flCorrect) < 0.2f;

}

float CMBacktracking::GetLerpTime()
{
	int ud_rate = Interfaces.g_ICVars->FindVar("cl_updaterate")->GetInt();
	ConVar *min_ud_rate = Interfaces.g_ICVars->FindVar("sv_minupdaterate");
	ConVar *max_ud_rate = Interfaces.g_ICVars->FindVar("sv_maxupdaterate");

	if (min_ud_rate && max_ud_rate)
		ud_rate = max_ud_rate->GetInt();

	float ratio = Interfaces.g_ICVars->FindVar("cl_interp_ratio")->GetFloat();

	if (ratio == 0)
		ratio = 1.0f;

	float lerp = Interfaces.g_ICVars->FindVar("cl_interp")->GetFloat();
	ConVar *c_min_ratio = Interfaces.g_ICVars->FindVar("sv_client_min_interp_ratio");
	ConVar *c_max_ratio = Interfaces.g_ICVars->FindVar("sv_client_max_interp_ratio");

	if (c_min_ratio && c_max_ratio && c_min_ratio->GetFloat() != 1)
		ratio = clamp(ratio, c_min_ratio->GetFloat(), c_max_ratio->GetFloat());

	return max(lerp, (ratio / ud_rate));
}

template<class T, class U>
T CMBacktracking::clamp(T in, U low, U high)
{
	if (in <= low)
		return low;

	if (in >= high)
		return high;

	return in;
}