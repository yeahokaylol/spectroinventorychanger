#include "LegitBackTracking.h"
#include "LegitMath.h"
#include "LagComp.h"
#define TICK_INTERVALZZZ			(Interfaces.pGlobalVars->interval_per_tick)

#define TIME_TO_TICKSZZZ( dt )		( (int)( 0.5f + (float)(dt) / TICK_INTERVALZZZ ) )

Vector Bones(CBaseEntity *Entity, CUserCmd* cmd)
{
	float BestDist = 100.f;
	Vector aimbone = Vector(0.f, 0.f, 0.f);

	matrix3x4 matrix[128];

	if (!Entity->SetupBones(matrix, 128, BONE_USED_BY_HITBOX, 0))
		return aimbone;

	studiohdr_t* pStudioModel = Interfaces.g_pModelInfo->GetStudioModel(Entity->GetModel());
	if (!pStudioModel)
		return aimbone;

	mstudiohitboxset_t* set = pStudioModel->GetHitboxSet(Entity->GetHitboxSet());
	if (!set)
		return aimbone;

	for (int i = 0; i < set->numhitboxes; i++)
	{
		mstudiobbox_t* hitbox = set->pHitbox(i);

		if (!hitbox)
			continue;
		Vector Check = Vector(matrix[hitbox->bone][0][3], matrix[hitbox->bone][1][3], matrix[hitbox->bone][2][3]);
		auto thisdist = LegitMath::GetFov(cmd->viewangles, LegitMath::CalcAngle(G::LocalPlayer->GetEyePosition(), Check));

		if (BestDist > thisdist)
		{
			BestDist = thisdist;
			aimbone = Check;
			continue;
		}

	}
	return aimbone;
}

void legitBackTrackClass::RageBackTrack(CUserCmd* cmd, CBaseEntity* pLocal)
{
		int bestTargetIndex = -1;
		float bestFov = 180.f;
		player_info_t info;
		if (!pLocal->isAlive())
			return;

		for (int i = 0; i < Interfaces.pEngine->GetMaxClients(); i++)
		{
			auto entity = (CBaseEntity*)Interfaces.pEntList->GetClientEntity(i);

			if (!entity || !pLocal)
				continue;

			if (entity == pLocal)
				continue;

			if (!Interfaces.pEngine->GetPlayerInfo(i, &info))
				continue;

			if (entity->IsDormant())
				continue;

			if (entity->GetTeam() == pLocal->GetTeam())
				continue;

			if (entity->isAlive())
			{

				float simtime = entity->GetSimulationTime();
				Vector hitboxPos = Bones(entity, cmd);

				headPositions[i][cmd->command_number % 13] = backtrackData{ simtime, hitboxPos };
				Vector ViewDir = angle_vector(cmd->viewangles + (pLocal->GetPunchAngle() * 2.f));
				float FOVDistance = distance_point_to_line(hitboxPos, pLocal->GetEyePosition(), ViewDir);

				if (bestFov > FOVDistance)
				{
					bestFov = FOVDistance;
					bestTargetIndex = i;
				}
			}
		}

		float bestTargetSimTime;
		if (bestTargetIndex != -1)
		{
			float tempFloat = 180.f;
			Vector ViewDir = angle_vector(cmd->viewangles + (pLocal->GetPunchAngle() * 2.f));
			for (int t = 0; t < 12; ++t)
			{
				float tempFOVDistance = distance_point_to_line(headPositions[bestTargetIndex][t].hitboxPos, pLocal->GetEyePosition(), ViewDir);
				if (tempFloat > tempFOVDistance && headPositions[bestTargetIndex][t].simtime > pLocal->GetSimulationTime() - 1)
				{
					tempFloat = tempFOVDistance;
					bestTargetSimTime = headPositions[bestTargetIndex][t].simtime;
				}
			}

			if (cmd->buttons & IN_ATTACK)
			{
				cmd->tick_count = TIME_TO_TICKSZZZ(bestTargetSimTime);
			}
		}
}

void legitBackTrackClass::legitBackTrack(CUserCmd* cmd, CBaseEntity* pLocal)
{
		int bestTargetIndex = -1;
		float bestFov = 100.f;
		player_info_t info;
		if (!pLocal->isAlive())
			return;

		for (int i = 1; i < 65; i++)
		{
			auto entity = Interfaces.pEntList->GetClientEntity(i);

			if (!entity || !pLocal)
				continue;

			if (entity == pLocal)
				continue;

			if (!Interfaces.pEngine->GetPlayerInfo(i, &info))
				continue;
			if (entity->IsDormant())
				continue;

			if (entity->GetTeam() == pLocal->GetTeam())
				continue;


			if (entity->isAlive())
			{

				float simtime = entity->GetSimulationTime();
				Vector hitboxPos = Bones(entity, cmd);
				if(hitboxPos.IsZero())
					continue;

				headPositions[i][cmd->command_number % 13] = backtrackData{ simtime, hitboxPos };
				Vector ViewDir = angle_vector(cmd->viewangles + (*G::LocalPlayer->GetPunchAnglePtr() * 2.f));
				float FOVDistance = distance_point_to_line(hitboxPos, pLocal->GetEyePosition(), ViewDir);
				
				if (bestFov > FOVDistance)
				{
					bestFov = FOVDistance;
					bestTargetIndex = i;
				}
			}
		}

	float bestTargetSimTime;
	bool memetracking = false;
	if (bestTargetIndex != -1)
	{
		float tempFloat = 180.f;
		Vector ViewDir = angle_vector(cmd->viewangles + (*G::LocalPlayer->GetPunchAnglePtr() * 2.f));
		for (int t = 0; t < g_Options.NewLegitbot.Aimbot.BackTrackIng; ++t)
		{
			float tempFOVDistance = distance_point_to_line(headPositions[bestTargetIndex][t].hitboxPos, pLocal->GetEyePosition(), ViewDir);
			if (tempFloat > tempFOVDistance && headPositions[bestTargetIndex][t].simtime > pLocal->GetSimulationTime() - 1.f)
			{
				tempFloat = tempFOVDistance;
				bestTargetSimTime = headPositions[bestTargetIndex][t].simtime;
				memetracking = true;
			}
		}
		if (cmd->buttons & IN_ATTACK)
		{
			cmd->tick_count = TIME_TO_TICKSZZZ(bestTargetSimTime);
		}
	}
}

legitBackTrackClass* backtracking = new legitBackTrackClass();
backtrackData headPositions[64][12];