#pragma once
#include "stdafx.h"


static void VectorAngles(const Vector& forward, Vector& angles)
{
	if (forward[1] == 0.0f && forward[0] == 0.0f)
	{
		angles[0] = (forward[2] > 0.0f) ? 270.0f : 90.0f;
		angles[1] = 0.0f;
	}
	else
	{
		angles[0] = atan2(-forward[2], forward.Length2D()) * -180 / M_PI;
		angles[1] = atan2(forward[1], forward[0]) * 180 / M_PI;

		if (angles[1] > 90) angles[1] -= 180;
		else if (angles[1] < 90) angles[1] += 180;
		else if (angles[1] == 90) angles[1] = 0;
	}

	angles[2] = 0.0f;
}

namespace global_count
{
	int hits[65] = { 0.f };
	int shots_fired[65] = { 0.f };

	bool didhit;
	bool on_fire;
}

bool adjusting_stop(CBaseEntity* player, CAnimationLayer *layer)
{
	for (int i = 0; i < 15; i++)
	{
		for (int s = 0; s < 14; s++)
		{
			auto anim_layer = player->GetAnimOverlay(s);
			if (!anim_layer.m_pOwner)
				continue;
			const int activity = player->GetSequenceActivity(layer[i].m_nSequence);
			if (activity == 981 && anim_layer.m_flWeight == 1.f)
			{
				return true;
			}
		}
	}
	return false;
} 

float __fastcall ang_dif(float a1, float a2)
{
	float val = fmodf(a1 - a2, 360.0);

	while (val < -180.0f) val += 360.0f;
	while (val > 180.0f) val -= 360.0f;

	return val;
}

static int GetSequenceActivity(CBaseEntity* pEntity, int sequence)
{
	const model_t* pModel = pEntity->GetModel();
	if (!pModel)
		return 0;

	auto hdr = Interfaces.g_pModelInfo->GetStudioModel(pEntity->GetModel());

	if (!hdr)
		return -1;

	static auto get_sequence_activity = reinterpret_cast<int(__fastcall*)(void*, studiohdr_t*, int)>(Utils.FindPattern("client_panorama.dll", "55 8B EC 83 7D 08 FF 56 8B F1 74 3D"));

	return get_sequence_activity(pEntity, hdr, sequence);
}

struct ResolverData
{

	float yaw, addyaw, addmoveyaw, lbycurtime, unres;
	int Shoot;
	float  lastmovinglby = 1337.f;
	int tick, balanceadjusttick, missedshots, shoots;
	bool playerhurtcalled;

};

struct ResolveInfo
{
	ResolveInfo()
	{
		m_bActive = false;

		m_flVelocity = 0.f;
		m_vecVelocity = Vector(0, 0, 0);
		m_angEyeAngles = QAngle(0, 0, 0);
		m_flSimulationTime = 0.f;
		m_flLowerBodyYawTarget = 0.f;

		m_flStandingTime = 0.f;
		m_flMovingLBY = 0.f;
		m_flLbyDelta = 180.f;
		m_bIsMoving = false;

		m_angDirectionFirstMoving = QAngle(0, 0, 0);
		m_nCorrectedFakewalkIdx = 0;
	}

	void SaveRecord(CBaseEntity *player)
	{
		m_flLowerBodyYawTarget = player->GetLowerBodyYaw();
		m_flSimulationTime = player->GetSimulationTime();
		m_flVelocity = player->GetVecVelocity().Length2D();
		m_vecVelocity = player->GetVecVelocity();
		m_angEyeAngles = *player->GetEyeAnglesPointer();

		m_iLayerCount = player->GetNumAnimOverlays();
		for (int i = 0; i < m_iLayerCount; i++)
			animationLayer[i] = player->GetAnimOverlaysAARec()[i];
	}

	bool operator==(const ResolveInfo &other)
	{
		return other.m_flSimulationTime == m_flSimulationTime;
	}

	bool m_bActive;

	float_t m_flVelocity;
	Vector m_vecVelocity;
	QAngle m_angEyeAngles;
	float_t m_flSimulationTime;
	float_t m_flLowerBodyYawTarget;

	int32_t m_iLayerCount = 0;
	CAnimationLayer animationLayer[15];

	float_t m_flStandingTime;
	float_t m_flMovingLBY;
	float_t m_flLbyDelta;
	bool m_bIsMoving;

	QAngle m_angDirectionFirstMoving;
	int32_t m_nCorrectedFakewalkIdx;

	int32_t m_nShotsMissed = 0;
};
const inline float_t LBYDelta(const ResolveInfo &v)
{
	return v.m_angEyeAngles.y - v.m_flLowerBodyYawTarget;
}
ResolveInfo arr_infos[65];
class CResolver {
public:
	void AntiAimResolver();
	void Resolve();
	ResolverData pResolverData[64];
	bool IsEntityMoving(CBaseEntity *player);
	bool IsAdjustingBalance(CBaseEntity *player, ResolveInfo &record, CAnimationLayer *layer);
	bool IsAdjustingStopMoving(CBaseEntity *player, ResolveInfo &record, CAnimationLayer *layer);
	bool IsFakewalking(CBaseEntity *player, ResolveInfo &record);
	float_t ResolveFakewalk(CBaseEntity *player, ResolveInfo &curtickrecord);
	bool IsAdjustingBalance1(CBaseEntity *player, CAnimationLayer *layer);
private:
	void DeleteInfo(int i);
	
	
};

extern CResolver* Resolver;
extern CResolver* Resolve;

void CResolver::DeleteInfo(int i)
{
	pResolverData[i].addyaw = 0.f;
	pResolverData[i].addmoveyaw = 0.f;
	pResolverData[i].Shoot = 0;
	pResolverData[i].lastmovinglby = 1337.f;
	pResolverData[i].unres = 1337.f;

}
inline float ClampYaw(float yaw)
{
	while (yaw > 180.f)
		yaw -= 360.f;
	while (yaw < -180.f)
		yaw += 360.f;
	return yaw;
}
bool CResolver::IsEntityMoving(CBaseEntity *player)
{
	return (player->GetVecVelocity().Length2D() > 0.1f && player->GetFlags() & FL_ONGROUND);
}
bool CResolver::IsAdjustingBalance(CBaseEntity *player, ResolveInfo &record, CAnimationLayer *layer)
{
	for (int i = 0; i < record.m_iLayerCount; i++)
	{
		const int activity = player->GetSequenceActivity(record.animationLayer[i].m_nSequence);
		if (activity == 979)
		{
			*layer = record.animationLayer[i];
			return true;
		}
	}
	return false;
}


float save1[64];
float save2[64];
float avgspin[64];

bool CResolver::IsAdjustingBalance1(CBaseEntity *player, CAnimationLayer *layer)
{
	for (int i = 0; i < 15; i++)
	{
		const int activity = player->GetSequenceActivity(layer[i].m_nSequence);
		if (activity == 979)
		{
			return true;
		}
	}
	return false;
}

bool CResolver::IsAdjustingStopMoving(CBaseEntity *player, ResolveInfo &record, CAnimationLayer *layer)
{
	for (int i = 0; i < record.m_iLayerCount; i++)
	{
		const int activity = player->GetSequenceActivity(record.animationLayer[i].m_nSequence);
		if (activity == 980)
		{
			*layer = record.animationLayer[i];
			return true;
		}
	}
	return false;
}
float_t CResolver::ResolveFakewalk(CBaseEntity *player, ResolveInfo &curtickrecord)
{
	auto &record = arr_infos[player->GetIndex()];

	float_t yaw;
	int32_t correctedFakewalkIdx = record.m_nCorrectedFakewalkIdx;

	if (correctedFakewalkIdx < 2)
	{
		yaw = record.m_angDirectionFirstMoving.y + 180.f;
	}
	else if (correctedFakewalkIdx < 4)
	{
		yaw = player->GetLowerBodyYaw() + record.m_flLbyDelta;
	}
	else if (correctedFakewalkIdx < 6)
	{
		yaw = record.m_angDirectionFirstMoving.y;
	}
	else
	{
		QAngle dir;
		VectorAngles(curtickrecord.m_vecVelocity, dir);

		yaw = dir.y;
	}

	return yaw;
}
bool CResolver::IsFakewalking(CBaseEntity *player, ResolveInfo &record)
{
	bool
		bFakewalking = false,
		stage1 = false,			// stages needed cause we are iterating all layers, eitherwise won't work :)
		stage2 = false,
		stage3 = false;

	for (int i = 0; i < record.m_iLayerCount; i++)
	{
		if (record.animationLayer[i].m_nSequence == 26 && record.animationLayer[i].m_flWeight < 0.4f)
			stage1 = true;
		if (record.animationLayer[i].m_nSequence == 7 && record.animationLayer[i].m_flWeight > 0.001f)
			stage2 = true;
		if (record.animationLayer[i].m_nSequence == 2 && record.animationLayer[i].m_flWeight == 0)
			stage3 = true;
	}

	if (stage1 && stage2)
		if (stage3 || (player->GetFlags() & FL_DUCKING)) // since weight from stage3 can be 0 aswell when crouching, we need this kind of check, cause you can fakewalk while crouching, thats why it's nested under stage1 and stage2
			bFakewalking = true;
		else
			bFakewalking = false;
	else
		bFakewalking = false;

	return bFakewalking;
}
void CResolver::Resolve()
{
	bool in_air[64] = { false };
	bool change[64] = { false };
	bool fakewalk[64] = { false };
	bool wasmoving[64] = { false };
	bool wasfakewalk[64] = { false };
	bool lowdelta[64] = { false };
	bool highdelta[64] = { false };
	bool didsync[64] = { false };
	bool spin[64] = { false };
	bool moving[64] = { false };
	bool hadmovingdif[64] = { false };
	bool hadslowlby[64] = { false };
	bool has_fake979[64] = { false };
	bool was_inair[64] = { false };
	bool did_fakewalk_change[64] = { false };
	bool prebreak[64] = { false };
	bool was_stopping[64] = { false };
	bool did_shoot[64] = { false };
	bool nofake[64] = { false };

	float delta[64] = { 0.f };
	float oldlby[64] = { 0.f };
	float last_sim[64] = { 0.f };
	float last_sync[64] = { 0.f };
	float movinglby[64] = { 0.f };
	float deltaDiff[64] = { 0.f };
	float slowlby[64] = { 0.f };
	float movingdif[64] = { 0.f };
	float fakewalk_change[64] = { 0.f };
	float last_forced_shot[64] = { 0.0f };
	float stand_lby[64] = { 0.0f };

	static float add_time[64];

	static bool updated_once[64];
	static bool lbybreak[64];
	static bool nextflick[64];
	static bool lbybacktrack[64];
	static bool is_stopping[64];
	static bool freestanding_left[64];
	static bool freestanding_right[64];
	static bool freestanding_back[64];
	static bool should_do_freestanding[64];
	static bool balance[64];

	static bool angle_override[64];

	const auto local = G::LocalPlayer;

	if (!local)
		return;

	for (auto i = 0; i < Interfaces.pEngine->GetMaxClients(); ++i)
	{
		const auto player = Interfaces.pEntList->GetClientEntity(i);

		if (!player || local == player || player->GetTeam() == local->GetTeam() || player->HasGunGameImmunity() || player->IsDormant())
		{
			wasfakewalk[i] = false;
			hadmovingdif[i] = false;
			didsync[i] = false;
			didsync[i] = false;
			change[i] = false;
			highdelta[i] = false;
			lowdelta[i] = false;
			prebreak[i] = false;
			is_stopping[i] = false;
			was_stopping[i] = false;
			should_do_freestanding[i] = false;
			oldlby[i] = 0.f;
			last_sim[i] = 0.f;
			last_forced_shot[i] = 0.f;
			stand_lby[i] = false;
			nofake[i] = false;
			continue;
		}

		auto update = false;

		const auto lby = player->GetLowerBodyYaw();
		const auto eye = player->GetEyePosition();
		const auto sim = player->GetSimulationTime();
		const auto speed = player->GetVecVelocity().Length2D();

		float lbyDelta = ang_dif(lby, save1[i]);
		float lbyDelta2 = ang_dif(save1[i], save2[i]);

		int missed[65];
		int fired[65];
		fired[i] = global_count::shots_fired[i];

		missed[i] = global_count::shots_fired[i] - global_count::hits[i];
		while (missed[i] > 3) missed[i] -= 3;
		//	while (missed[i] < 0) missed[i] += 3;

		while (fired[i] >= 3) fired[i] -= 3;

		

		for (int s = 0; s < 14; s++)
		{

			auto anim_layer = player->GetAnimOverlay(s);
				
			if (!anim_layer.m_pOwner)
				continue;
			auto anime = &player->GetAnimOverlaysAARec()[1];
			auto activity = GetSequenceActivity(player, anime->m_nSequence);

			if (activity == -1)
				continue;

			if (sim - last_sim[i] >= 1)
			{
				if (sim - last_sim[i] == 1 && !IsAdjustingBalance1(player, anime))
				{
					didsync[i] = true;
					nofake[i] = true;
				}
				last_sim[i] = sim;
			}
			// this is a legit check justin. I know this was too hard for you to understand on stream, but this is what a legit check looks like.
			// I don't know how "nofake" didn't send off alarms in your head telling you what this is meant to be, but oh well, what do i know huh

			//if (GetAsyncKeyState() && (player->GetFlags() & FL_ONGROUND) && speed < 90.f)
			//{
			//	angle_override[i] = true;
			//}
			//else
			{
				angle_override[i] = false;
			}

			if (!(player->GetFlags() & FL_ONGROUND))
			{
				in_air[i] = true;
				was_inair[i] = true;
			}
			else
			{
				in_air[i] = false;
				if (speed >= 90.f)
				{
					movinglby[i] = lby;
					was_stopping[i] = false;
					moving[i] = true;
					add_time[i] = 0.22f;
					nextflick[i] = sim + add_time[i];
				}
				else if (speed > 0.1f && speed < 90.f)
				{
					add_time[i] = 0.22f;
					nextflick[i] = sim + add_time[i];

					if (IsAdjustingBalance1(player, anime))
					{
						fakewalk[i] = true;
						wasfakewalk[i] = true;
						hadslowlby[i] = false;
						if (oldlby[i] - lby >= 60 || oldlby[i] - lby <= -60)
						{
							did_fakewalk_change[i] = true;
							fakewalk_change[i] = oldlby[i] - lby;
						}
						else
							did_fakewalk_change[i] = false;

						if (adjusting_stop(player, anime))
						{
							is_stopping[i] = true;
							was_stopping[i] = true;

							if (wasmoving[i])
								deltaDiff[i] = lby - movinglby[i];
							else
							{
								if (hadslowlby[i])
									deltaDiff[i] = lby - slowlby[i];
								else
								{
									if (stand_lby[i] != 0.0f)
									{
										deltaDiff[i] = lby - stand_lby[i];
									}
								}
							}
						}
						else
							is_stopping[i] = false;


						if (oldlby[i] != lby)
						{
							deltaDiff[i] = oldlby[i] - lby;
							oldlby[i] = lby;
						}
					}
					else
					{
						did_shoot[i] = false;
						hadslowlby[i] = true;
						moving[i] = true;
						slowlby[i] = lby;
					}
				}
				else
				{
					if (!nofake )//&& !(GetAsyncKeyState(Options::Menu.RageBotTab.OverrideKey.GetKey())))
					{
						if (didsync[i])
							last_sync[i] = eye.y;

						stand_lby[i] = lby;

						if (fabs(last_sim[i] - sim) > 2.0f && speed < 0.1f)
						{
							last_sim[i] = 0.f;
							last_forced_shot[i] = 0.0f;
						}

						if (fabsf(last_forced_shot[i] - sim) > 0.1f && speed < 0.1f)
						{
							last_forced_shot[i] = sim;
							did_shoot[i] = true;
						} // dasmax codenz <3
						else
						{
							did_shoot[i] = false;
						}

						if (oldlby[i] != lby && !spin[i])
						{
							oldlby[i] = lby;
							update = true;

							change[i] = true;
							add_time[i] = Interfaces.pGlobalVars->interval_per_tick + 1.1f;
							nextflick[i] = sim + add_time[i];

							if (IsAdjustingBalance1(player, anime) && fabsf(lby - oldlby[i]) < 120 && anim_layer.m_flWeight == 0.f && !wasmoving[i])
							{
								delta[i] = fabsf(lby - oldlby[i]) - 35;
							}

							else
							{
								delta[i] = fabsf(lby - oldlby[i]);
							}
						}
						else
						{
							lbybreak[i] = false;
						}

						if (sim >= nextflick[i])
						{
							lbybreak[i] = true;
							add_time[i] = 1.1f;
							nextflick[i] = sim + add_time[i];
						}
						else
						{
							lbybreak[i] = false;
							lbybacktrack[i] = false;
						}

						if (!wasmoving[i])
						{

							if (anim_layer.m_flWeight == 1.f && IsAdjustingBalance1(player, anime))
							{
								highdelta[i] = true;
								lowdelta[i] = false;
								prebreak[i] = false;
							}

							else if (anim_layer.m_flWeight == 1.f && IsAdjustingBalance1(player, anime))
							{
								highdelta[i] = false;
								lowdelta[i] = false;
								prebreak[i] = true;
							}

							else if (anim_layer.m_flWeight == 0.f && !IsAdjustingBalance1(player, anime))
							{
								highdelta[i] = false;
								lowdelta[i] = true;
								prebreak[i] = false;
							}

							else if ((anim_layer.m_flWeight == 0.f && IsAdjustingBalance1(player, anime)) || (change[i] && delta[i] < 120 && IsAdjustingBalance1(player, anime)) || did_shoot[i])
							{
								highdelta[i] = false;
								lowdelta[i] = false;
								prebreak[i] = true;
							}

							else
							{
								highdelta[i] = false;
								lowdelta[i] = false;
								prebreak[i] = false;
							}


						}
					}
				}
			}
		}

		//------------------- Resolve -------------------//

		auto yaw = 0.f;

		/*if (GetAsyncKeyState(Options::Menu.RageBotTab.OverrideKey.GetKey()))
		{
			yaw = override_yaw(player, local);
		}*/

		if (in_air)
		{
			yaw = lby - (45 * fired[i] + 1);
		}
		else
		{
			if (moving)
			{
				yaw = lby;
			}
			else if (speed > 0.1f && speed < 90.f)
			{
				if (fakewalk)
				{
					if (wasmoving[i] && !hadslowlby[i])
					{
						if (fired[i] < 2)
							yaw = movinglby[i];
						else
						{
							yaw = lby;
						}

					}
					else if (wasmoving[i] && hadslowlby[i])
					{
						if (fired[i] < 2)
							yaw = movinglby[i];
						else
							yaw = slowlby[i];
					}
					else if (!wasmoving[i] && hadslowlby[i])
					{
						if (fired[i] < 2)
							yaw = slowlby[i];
						else
						{
							yaw = lby;
						}
					}
					else
					{
						yaw = lby;
					}
				}
				else
				{
					yaw = lby;
				}
			}
			else
			{
				if (lbybreak[i] || update) // :elephant: 
				{
					yaw = lby;
				}
				else if (!lbybreak[i] && !nofake[i])
				{
					// ------------ movement related things ------------ //

					if (wasmoving[i] && !wasfakewalk[i])
					{
						if (fired[i] < 2)
							yaw = movinglby[i];
						else
							yaw = slowlby[i];
					}

					else if (!wasmoving[i] && !wasfakewalk[i] && hadslowlby[i] && !change[i])
					{
						if (fired[i] < 2)
							yaw = slowlby[i];
						else
							lby;
					}

					else if (!wasmoving[i] && !wasfakewalk[i] && hadslowlby[i] && change[i])
					{
						if (fired[i] < 2)
							yaw = slowlby[i];
						else
							yaw = lby - delta[i];
					}

					else if (!wasmoving[i] && wasfakewalk[i] && hadslowlby[i] && !change[i])
					{
						if (fired[i] < 2)
							yaw = slowlby[i];
						else
						{
							yaw = lby - (20 * fired[i]);
						}
					}

					else if (!wasmoving[i] && wasfakewalk[i] && !hadslowlby[i] && change[i])
					{
						if (fired[i] < 2)
						{
							yaw = lby - deltaDiff[i];
						}
						else
							yaw = lby - (deltaDiff[i] * fired[i]);
					}

					else if (!wasmoving[i] && wasfakewalk[i] && !hadslowlby[i] && !change[i])
					{
						if (deltaDiff[i] > 35 || deltaDiff[i] < 35)
						{
							if (fired[i] < 2)
								yaw = lby - deltaDiff[i];
							else
							{
								yaw = lby - (90 * fired[i]);

							}
						}
						else
						{
							if (fired[i] < 2)
							{
								yaw = lby;
							}
							else
							{
								yaw = lby - (60 * fired[i]);
							}
						}
					}

					// ------------ standing related things ------------ //

					else if (!wasmoving[i] && !wasfakewalk[i] && !hadslowlby[i])
					{
						if (prebreak[i]) // if they did 979, but their delta < 120
						{
							if (fired[i] <= 2)
							{
								yaw = lby - (120 * fired[i] + 1);
							}
							else
								yaw = lby - delta[i] - (15 * fired[i]);
						}

						else if (lowdelta[i] && !change[i]) // if we did not see their lby change, but are balancing weight.
						{
							if (fired[i] < 2)
								yaw = lby - (60 * fired[i] + 1);
							else
							{
								yaw = lby + (35 * fired[i]);
							}
						}

						else if (lowdelta[i] && change[i]) // if we saw their lby change and can grab delta
						{
							if (fired[i] < 2)
								yaw = lby - delta[i];
							else
								yaw = lby - (75 * missed[i]);
						}

						else if (highdelta[i] && !change[i])
						{
							if (fired[i] < 1)
								yaw = lby - 135;
							else
							{

								yaw = lby - (120 * fired[i]); // backwards
							}
						}

						else if (highdelta[i] && change[i])
						{
							if (fired[i] < 2)
								yaw = lby - delta[i];
							else
							{
								yaw = lby - (delta[i] * fired[i]);
							}
						}

						else if (change[i] && !highdelta[i] && !lowdelta[i] && !prebreak[i]) // just be sure
						{
							if (fired[i] < 2)
								yaw = lby - delta[i];
							else
								yaw = lby - delta[i] - (20 * fired[i]); // so if the delta is 90, it will be 90 - (20 x2, then 3) which is 40 and 60.
						}

						else if (!highdelta[i] && !change[i] && !prebreak[i] && !lowdelta[i])
						{
							if (fired[i] < 2)
								yaw = lby;
							else
							{
								yaw = lby - 120;
							}
						}
						else
							yaw = lby;
					}
					else
						yaw = lby;
				}

				if (nofake[i])
				{
					yaw = eye.y;
				}
			}
		}
		player->GetAbsAnglesNew().y = yaw;
	}
}

void CResolver::AntiAimResolver()
{	
	for (int i = 1; i < 65; i++)
	{
		auto pEntity = Interfaces.pEntList->GetClientEntity(i);

		if (!pEntity || !G::LocalPlayer)
		{	DeleteInfo(i); continue; }
			

		if (pEntity == G::LocalPlayer)
		{
			DeleteInfo(i); continue;
		}

		if (pEntity->GetTeam() == G::LocalPlayer->GetTeam())
		{
			DeleteInfo(i); continue;
		}

		if (pEntity->IsDormant())
		{
			continue;
		}

		Hacks.CurMode[i] = ResolverModes::NONE;

		
		if (pEntity->isAlive())
		{

			if (g_Options.Ragebot.Ragebot_Resolver)
			{
				int FakeLby = 0;

				Vector* pAngles = pEntity->GetEyeAnglesPointer();
			

				if (G::LocalPlayer->GetShootsField() > 1)
				{
					if (G::LocalPlayer->GetShootsField() != pResolverData[G::AimbotID].shoots)
					{
						if (!pResolverData[G::AimbotID].playerhurtcalled)
						{
							pResolverData[G::AimbotID].addyaw += 45.f;
							pResolverData[G::AimbotID].addmoveyaw += 15.f;
							pResolverData[G::AimbotID].Shoot++;
						}
						else
							pResolverData[G::AimbotID].playerhurtcalled = false;
						pResolverData[G::AimbotID].shoots = G::LocalPlayer->GetShootsField();
					}
				}

				CAnimationLayer *layer6 = pEntity->GetAnimOverlayAARec(6);
				if (layer6 && layer6->m_flPlaybackRate > 0.0f && layer6->m_flPlaybackRate < 0.008f && pEntity->GetVecVelocity().Length2D() <= 24.0f)
					Hacks.fakewalking[i] = true;
				else
					Hacks.fakewalking[i] = false;

				for (int w = 0; w < 13; w++)
				{
					auto layer = pEntity->GetAnimOverlaysAARec()[w];

					int number = layer.m_nSequence,
						activity = pEntity->GetSequenceActivity(number);


					if (pResolverData[i].Shoot >= 10 || !G::LocalPlayer->isAlive())
					{
						pResolverData[i].Shoot = 0;
					}

					

					if (pEntity->GetVecVelocity().Length2D() > 1.f && pEntity->GetFlags() & FL_ONGROUND && !Hacks.fakewalking[i]) //чек на велосите и не в воздухе ли игрок, не ну а хули
					{
						pResolverData[i].lastmovinglby = pEntity->pelvisangs(); // записываем  лбу мув

						pAngles->y = pEntity->pelvisangs(); // лбу ресольвер на муве агада 

						Hacks.CurMode[i] = ResolverModes::MOVING;
					}
					else
					{
						if (pResolverData[i].lastmovinglby != 1337.f)
						{
							pAngles->y = pResolverData[i].lastmovinglby + pResolverData[G::AimbotID].addmoveyaw; //ставим ластлбу мув, хули нам пастерам

							Hacks.CurMode[i] = ResolverModes::LBY;
						}
						else
						{
							if (pResolverData[i].unres != 1337.f)
							{
								pAngles->y = pResolverData[i].unres + pResolverData[G::AimbotID].addmoveyaw; //ставим ластлбу мув, хули нам пастерам

								Hacks.CurMode[i] = ResolverModes::LASTSHAKELBY;
							}
							else
							{
								pAngles->y = pEntity->pelvisangs() + 180; //ставим ластлбу мув, хули нам пастерам

								Hacks.CurMode[i] = ResolverModes::LBY_BRUTE;
							}
						}
					}
					
					
				
				

					if (activity == 979 && (w == 3 || w == 2 || w == 5 || w == 6))
						FakeLby = 1;
			



				}

				Hacks.FakingLBY[i] = FakeLby;

				if (pEntity->GetAnimOverlaysAARec()[3].m_flWeight < 0.01f && pEntity->GetAnimOverlaysAARec()[3].m_flCycle < 0.92f &&  (pEntity->GetVecVelocity().Length2D() == 0 || Hacks.fakewalking[i]))
				{
					pAngles->y = pEntity->pelvisangs();
					pResolverData[i].unres = pEntity->pelvisangs() + 145.f; // записываем текущие лбу
					Hacks.CurMode[i] = ResolverModes::LBY_FLICK;
					Hacks.FakingLBY[i] = 2;

				}

				pAngles->Normalize();
			}
		}
	}
}
CResolver* Resolver = new CResolver();