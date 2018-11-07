#include "stdafx.h"
#include "LegitBot.h"
#include "LegitMath.h"
CLegitClass* g_pLegitbot = new CLegitClass;



bool IsHitChance(float flChance, CBaseCombatWeapon *pWep)
{
	if (!pWep) return false;
	if (flChance >= 99.f)
		flChance = 99.f;

	if (flChance < 1)
		flChance = 1;

	float flSpread = pWep->GetInaccuracy() * 10;
	return((((100.f - flChance) * 0.65f) * 0.01125) >= flSpread);
}

enum
{
	HITBOX_HEAD,
	HITBOX_NECK,
	HITBOX_PELVIS,
	HITBOX_BELLY,
	HITBOX_THORAX,
	HITBOX_LOWER_CHEST,
	HITBOX_UPPER_CHEST,
	HITBOX_RIGHT_THIGH,
	HITBOX_LEFT_THIGH,
	HITBOX_RIGHT_CALF,
	HITBOX_LEFT_CALF,
	HITBOX_RIGHT_FOOT,
	HITBOX_LEFT_FOOT,
	HITBOX_RIGHT_HAND,
	HITBOX_LEFT_HAND,
	HITBOX_RIGHT_UPPER_ARM,
	HITBOX_RIGHT_FOREARM,
	HITBOX_LEFT_UPPER_ARM,
	HITBOX_LEFT_FOREARM,
	HITBOX_MAX
};

float GetFov(const Vector& viewAngle, const Vector& aimAngle)
{


		Vector delta = aimAngle - viewAngle;
		delta.Normalize();
		return sqrtf(powf(delta.x, 2.0f) + powf(delta.y, 2.0f));

}

void CLegitClass::Run(CUserCmd* pCmd, CBaseCombatWeapon* weap)
{

	if (!pCmd)
		return;
	if (!weap)
		return;
	if (weap->IsKnife() || weap->IsGrenade())
		return;



	this->Run_Aim(pCmd);


	static int CustomDelay = 0;
	if ((GetAsyncKeyState(g_Options.NewLegitbot.Triggerbot.Key) || g_Options.NewLegitbot.Triggerbot.AutoFire) && g_Options.NewLegitbot.Triggerbot.Enabled)
	{
		if (g_Options.NewLegitbot.Triggerbot.Delay > 1)
		{
			if ((int)GetTickCount() > CustomDelay)
			{
				Triggerbot();
				CustomDelay = (int)GetTickCount() + g_Options.NewLegitbot.Triggerbot.Delay;
			}
		}
		else
			Triggerbot();
	}
}

//CBaseCombatWeapon* Weapon;
#define WeaponID g_Options.wpn
//CBaseEntity* pLocalEntity;



Vector ClosestBone(CBaseEntity *Entity, CUserCmd* cmd, Vector Rcs)
{

	auto BoneIDByMenu = [](int MenuVar)
	{
		switch (MenuVar)
		{
		case 0:return 8; break;
		case 1:return 2; break;
		case 2:return 7; break;
		case 3:return 6; break;
		case 4:return 5; break;
		case 5:return 4; break;
		case 6:return 3; break;
		case 7:return 0; break;
		default:return MenuVar;break;
		}
	};
	
	if (g_Options.NewLegitbot.Weapon[WeaponID].Nearest)
	{
		float BestDist = 180.f;
		Vector Aim = Vector(0.0f, 0.0f, 0.0f);

		matrix3x4 matrix[128];

		if (!Entity->SetupBones(matrix, 128, BONE_USED_BY_HITBOX, Interfaces.pEngine->GetLastTimeStamp()))
			return Aim;

		studiohdr_t* pStudioModel = Interfaces.g_pModelInfo->GetStudioModel(Entity->GetModel());
		if (!pStudioModel)
			return Aim;

		mstudiohitboxset_t* set = pStudioModel->GetHitboxSet(Entity->GetHitboxSet());
		if (!set)
			return Aim;

		for (int i = 0; i < set->numhitboxes; i++)
		{
			if (i == HITBOX_RIGHT_THIGH || i == HITBOX_LEFT_THIGH || i == HITBOX_RIGHT_CALF
				|| i == HITBOX_LEFT_CALF || i == HITBOX_RIGHT_FOOT || i == HITBOX_LEFT_FOOT
				|| i == HITBOX_RIGHT_HAND || i == HITBOX_LEFT_HAND || i == HITBOX_RIGHT_UPPER_ARM
				|| i == HITBOX_RIGHT_FOREARM || i == HITBOX_LEFT_UPPER_ARM || i == HITBOX_LEFT_FOREARM)
				continue;

			mstudiobbox_t* hitbox = set->pHitbox(i);

			if (!hitbox)
				continue;



			Vector Check = Vector(matrix[hitbox->bone][0][3], matrix[hitbox->bone][1][3], matrix[hitbox->bone][2][3]);
			if (!Entity->IsVisibleVector(Check))continue;


			float thisdist = 360.f;
			if (Rcs.IsZero())
			{
				thisdist = GetFov(cmd->viewangles, LegitMath::CalcAngle(G::LocalPlayer->GetEyePosition(), Check));

			}
			else
			{
				thisdist = GetFov(cmd->viewangles + Rcs, LegitMath::CalcAngle(G::LocalPlayer->GetEyePosition(), Check));
			}


			
			
			if (thisdist < BestDist)
			{
				BestDist = thisdist;
				Aim = Check;
			}
		}
		return Aim;
	}
	else
	{

		Vector bonepos = Entity->GetBonePos(BoneIDByMenu(g_Options.NewLegitbot.Weapon[WeaponID].Bone));
		if (Entity->IsVisibleVector(bonepos))
		{
			return bonepos;
		}
		else
		{
			return Vector(0.f, 0.f, 0.f);
		}
	}
		
}



int CLegitClass::FindTarget(CUserCmd* pCmd, Vector Rcs, Vector& NextBonePos)
{
	float flMax = 180.f;
	int flHeathMax = 150;
	int iMaxSpeed = 1000;
	int iBestTarget = -1;

	if (G::LocalPlayer && G::LocalPlayer->isAlive()) {
		for (int i = 1; i < 65; i++)
		{
			auto pEntityPlayer = Interfaces.pEntList->GetClientEntity(i);
			if (!pEntityPlayer)
				continue;
			if (pEntityPlayer == G::LocalPlayer)
				continue;
			if (!pEntityPlayer->isAlive())
				continue;
			if (pEntityPlayer->IsDormant())
				continue;
			if (pEntityPlayer->HasGunGameImmunity())
				continue;
			if (pEntityPlayer->GetTeam() == G::LocalPlayer->GetTeam() && !g_Options.NewLegitbot.Aimbot.FriendlyFire)
				continue;
			
			Vector PreVectorPos = ClosestBone(pEntityPlayer, pCmd, Rcs);
			if (PreVectorPos.IsZero())continue;
				

			float flFoV = GetFov(pCmd->viewangles, LegitMath::CalcAngle(G::LocalPlayer->GetEyePosition(), PreVectorPos));
			if (flFoV < flMax) {
				flMax = flFoV;
				NextBonePos = PreVectorPos;
				iBestTarget = i;
			}
			
		}
	}
	return iBestTarget;
}
Vector CurveSmooth(Vector& viewangles, Vector target, float factor)
{
	factor /= 10.f;

	if (factor <= 0.0f)
		return target;

	Vector delta = target - viewangles;
	delta.Clamp();

	float smooth = powf(factor, 0.4f);
	smooth = min(0.99f, smooth);

	float factorX = factor, factorY = factor;

	if (delta.x < 0.0f)
	{
		if (factorX > fabs(delta.x))
			factorX = fabs(delta.x);

		target.x = viewangles.x - factorX;
	}
	else
	{
		if (factorX > delta.x)
			factorX = delta.x;

		target.x = viewangles.x + factorX;
	}

	if (delta.y < 0.0f)
	{
		if (factorY > fabs(delta.y))
			factorY = fabs(delta.y);

		target.y = viewangles.y - factorY;
	}
	else
	{
		if (factorY > delta.y)
			factorY = delta.y;

		target.y = viewangles.y + factorY;
	}

	return target;
}
void CLegitClass::Run_Aim(CUserCmd* cmd)
{
	

	if (g_Options.Menu.Opened)
		return;
	if (!g_Options.NewLegitbot.Aimbot.Enabled)
		return;
	if (g_Options.NewLegitbot.Aimbot.bKillDelay && Interfaces.pGlobalVars->curtime <= G::KillStopDelay)
		return;

	if (g_Options.NewLegitbot.Aimbot.JumpCheck && !(G::LocalPlayer->GetFlags() & FL_ONGROUND))
		return;

	if (g_Options.NewLegitbot.Aimbot.FlashCheck && G::LocalPlayer->GetFlashDuration() > g_Options.NewLegitbot.Aimbot.FlashCheckAlpha)
		return;

	auto weap = G::LocalPlayer->GetActiveBaseCombatWeapon();
	if (!weap)
		return;
	if (weap->IsMiscWeapon())
		return;
	if (weap->IsReloading())
		return;
	

	if (!g_Options.NewLegitbot.Weapon[WeaponID].Enabled)
		return;

	

	int ShootFired = weap->isPistol() ? g_Options.m_iBulletsFire : G::LocalPlayer->GetShootsField();

	bool psile = (g_Options.NewLegitbot.Weapon[WeaponID].pSilent && (ShootFired <= 1)) && (g_Options.NewLegitbot.Weapon[WeaponID].pSilentHitChance > RandomFloat(0.f, 100.f) || g_Options.NewLegitbot.Weapon[WeaponID].pSilentHitChance == 0.f) ? true : false;

	//printf("psalo = %s", psile ? "true" : "false");

	if (g_Options.NewLegitbot.Aimbot.RCSFix || weap->isRifle())
		if (ShootFired >= 3)
			return;

	Vector Rcs = Vector(0.f,0.f,0.f);

	if (WeaponID != WEAPON_AWP && WeaponID != WEAPON_SSG08)
	{
		Rcs.x = G::LocalPlayer->GetPunchAnglePtr()->x * (g_Options.NewLegitbot.Weapon[WeaponID].RcsX / 50.f);
		Rcs.y = G::LocalPlayer->GetPunchAnglePtr()->y * (g_Options.NewLegitbot.Weapon[WeaponID].RcsY / 50.f);
	}
	

	if (g_Options.NewLegitbot.Weapon[WeaponID].Aimtype == 0)
	{
		if (ShootFired <= (g_Options.NewLegitbot.Weapon[WeaponID].StartBullet - 1) && !psile)
			return;

		if (g_Options.NewLegitbot.Weapon[WeaponID].EndBullet != 0 && ShootFired >= g_Options.NewLegitbot.Weapon[WeaponID].EndBullet)
			return;
	}
	if (g_Options.NewLegitbot.Weapon[WeaponID].Aimtype == 1)
	{
		if (!GetAsyncKeyState(g_Options.NewLegitbot.Aimbot.Key) || g_Options.NewLegitbot.Aimbot.Key <= 0)
			return;
	}



	Vector vecBone = Vector(0.f, 0.f, 0.f);
	
	int pID = this->FindTarget(cmd, g_Options.NewLegitbot.Weapon[g_Options.wpn].NearestRCS ? Rcs : Vector(0.f, 0.f, 0.f), vecBone);
	

	if (pID <= 0 || vecBone.IsZero())
		return;

	if (g_Options.NewLegitbot.Aimbot.SmokeCheck && G::LineToSmoke(vecBone, G::LocalPlayer->GetEyePosition(), true))
		return;


		Vector dst = LegitMath::CalcAngle(G::LocalPlayer->GetEyePosition(), vecBone);

		float fov = psile ? g_Options.NewLegitbot.Weapon[WeaponID].pSilentFov : g_Options.NewLegitbot.Weapon[WeaponID].Fov;

		if (GetFov(cmd->viewangles, dst) > fov)
			return;

		
		float smooth = psile ? 0.f : g_Options.NewLegitbot.Weapon[WeaponID].Smooth;


		dst -= Rcs;



		if(smooth > 1.f && !psile)
		{
	
			if (g_Options.NewLegitbot.Weapon[WeaponID].SmoothType == 0)
			{
				Vector delta = cmd->viewangles - dst;
				if (!delta.IsZero())
				{
					//delta.Normalize();
					Misc::Normalize(delta);
					dst = cmd->viewangles - delta / smooth;
				}
			}
			else if (g_Options.NewLegitbot.Weapon[WeaponID].SmoothType == 1)
			{
				dst = CurveSmooth(cmd->viewangles, dst, smooth / 10.f); 
			}

		}
		
		

		Misc::Normalize(dst);
		//dst.Normalize();
		//dst.Clamp();

		if (g_Options.NewLegitbot.Aimbot.FastZoom && (WeaponID == WEAPON_AWP || WeaponID == WEAPON_SSG08))
		{
			if (cmd->buttons & IN_ATTACK)
			{
				if (!G::LocalPlayer->m_bIsScoped())
				{
						cmd->buttons &= ~IN_ATTACK;
						cmd->buttons |= IN_ZOOM;


				}
			}
		}
		
	//	if (psile)
	//	{
	//		Hacks.SendPacket = false;
	//	}
		if (!psile)
			Hacks.SendPacket = false;

		cmd->viewangles = dst;

		
		if(!Hacks.SendPacket)
		{
			Interfaces.pEngine->SetViewAngles(cmd->viewangles.Normalize());
		}
	
}
#include <chrono>

void CLegitClass::Triggerbot()
{

	if (!G::LocalPlayer || !G::LocalPlayer->isAlive())
		return;

	long currentTime_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()).count();
	static long timeStamp = currentTime_ms;
	long oldTimeStamp;

	Vector traceStart, traceEnd;
	trace_t tr;

	Vector viewAngles;
	Interfaces.pEngine->GetViewAngles(viewAngles);
	Vector viewAngles_rcs = viewAngles + G::LocalPlayer->GetPunchAngle() * 2.0f;

	LegitMath::AngleVectors(viewAngles_rcs, &traceEnd);

	traceStart = G::LocalPlayer->GetEyePosition();
	traceEnd = traceStart + (traceEnd * 8192.0f);


		Ray_t ray;
		ray.Init(traceStart, traceEnd);
		CTraceFilter traceFilter;
		traceFilter.pSkip = G::LocalPlayer;
		Interfaces.pTrace->TraceRay(ray, 0x46004003, &traceFilter, &tr);
	
	oldTimeStamp = timeStamp;
	timeStamp = currentTime_ms;

	CBaseEntity* player = tr.m_pEnt;

	if (!player)
		return;

	if (!player->IsPlayer())
		return;

	if (player == G::LocalPlayer
		|| player->IsDormant()
		|| !player->isAlive()
		|| player->HasGunGameImmunity())
		return;

	if (player->GetTeam() == G::LocalPlayer->GetTeam() && !g_Options.NewLegitbot.Triggerbot.Filter.Friendly)
		return;

	if (g_Options.NewLegitbot.Aimbot.SmokeCheck && G::LineToSmoke(traceStart, traceEnd, true))
		return;
	if (g_Options.NewLegitbot.Aimbot.JumpCheck && !(G::LocalPlayer->GetFlags() & FL_ONGROUND))
		return;
	if (g_Options.NewLegitbot.Aimbot.FlashCheck && G::LocalPlayer->IsFlashed())
		return;

	if (!tr.m_pEnt)
		return;


	int hitgroup = tr.hitgroup;
	bool didHit = false;

	if (g_Options.NewLegitbot.Triggerbot.Filter.Head && hitgroup == HITGROUP_HEAD)
		didHit = true;
	if (g_Options.NewLegitbot.Triggerbot.Filter.Chest && hitgroup == HITGROUP_CHEST)
		didHit = true;
	if (g_Options.NewLegitbot.Triggerbot.Filter.Stomach && hitgroup == HITGROUP_STOMACH)
		didHit = true;
	if (g_Options.NewLegitbot.Triggerbot.Filter.Arms && (hitgroup == HITGROUP_LEFTARM || hitgroup == HITGROUP_RIGHTARM))
		didHit = true;
	if (g_Options.NewLegitbot.Triggerbot.Filter.Legs && (hitgroup == HITGROUP_LEFTLEG || hitgroup == HITGROUP_RIGHTLEG))
		didHit = true;

	//if (Vars.Legitbot.Triggerbot.Filter.smoke && LineGoesThroughSmoke(tr.startpos, tr.endpos, 1))
	//return;

	if (didHit)
	{
		if (g_Options.NewLegitbot.Aimbot.FastZoom)
		{
			if (*G::LocalPlayer->GetActiveBaseCombatWeapon()->GetItemDefinitionIndex() == WEAPON_AWP || *G::LocalPlayer->GetActiveBaseCombatWeapon()->GetItemDefinitionIndex() == WEAPON_SSG08)
			{

				if (!G::LocalPlayer->m_bIsScoped())
				{
					Hacks.CurrentCmd->buttons &= ~IN_ATTACK;
					Hacks.CurrentCmd->buttons |= IN_ZOOM;
				}
			}
		}
	}

	if (didHit && (!g_Options.NewLegitbot.Triggerbot.HitChance || IsHitChance(g_Options.NewLegitbot.Triggerbot.HitChanceAmt, G::LocalPlayer->GetActiveBaseCombatWeapon()))) {
		if (*G::LocalPlayer->GetActiveBaseCombatWeapon()->GetItemDefinitionIndex() == WEAPON_REVOLVER)
			Hacks.CurrentCmd->buttons |= IN_ATTACK2;
		else
		{
			float dist = LegitMath::VectorDistance(G::LocalPlayer->GetVecOrigin(), tr.m_pEnt->GetVecOrigin());

			if (*G::LocalPlayer->GetActiveBaseCombatWeapon()->GetItemDefinitionIndex() == WEAPON_TASER && dist < 800.f)
				Hacks.CurrentCmd->buttons |= IN_ATTACK;
			else if (*G::LocalPlayer->GetActiveBaseCombatWeapon()->GetItemDefinitionIndex() != WEAPON_TASER)
				Hacks.CurrentCmd->buttons |= IN_ATTACK;
		}


	}
}