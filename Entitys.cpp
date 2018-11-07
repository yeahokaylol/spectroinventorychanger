#include "stdafx.h"
inline DWORD FindPatternAimbot(char *pattern, char *mask, DWORD offset, char *moduleName)
{
	HMODULE hModule;
	MODULEINFO moduleInfo;
	DWORD dModule, dModuleSize;

	hModule = GetModuleHandle(moduleName);
	GetModuleInformation(GetCurrentProcess(), hModule, &moduleInfo, sizeof(MODULEINFO));

	dModule = (DWORD)moduleInfo.lpBaseOfDll;
	dModuleSize = moduleInfo.SizeOfImage;

	DWORD start = dModule;
	DWORD end = dModule + dModuleSize;

	int patternLength = strlen(mask);
	bool found = false;

	for (DWORD i = start; i < end - patternLength; i++)
	{
		found = true;

		for (int idx = 0; idx < patternLength; idx++)
		{
			if (*(mask + idx) == 'x' && *(pattern + idx) != *(char*)(i + idx))
			{
				found = false;
				break;
			}
		}

		if (found)
			return i + offset;
	}
	return NULL;
}

CBaseHandle CBaseEntity::GetObserverTarget() {
	if (!this)
		return NULL;

	return *reinterpret_cast<CBaseHandle*>(uintptr_t(this) + offsets.m_hObserverTarget);
}

void CBaseEntity::SetAbsAngles(const Vector &angles)//?
{
	using SetAbsAnglesFn = void(__thiscall*)(void*, const QAngle &angles);
	static SetAbsAnglesFn SetAbsAngles = (SetAbsAnglesFn)Utils.FindPatternIDA("client_panorama.dll", "55 8B EC 83 E4 F8 83 EC 64 53 56 57 8B F1 E8");
	SetAbsAngles(this, angles);
}
void CBaseEntity::SetAbsOrigin(const Vector &origin)//?
{
	using SetAbsOriginFn = void(__thiscall*)(void*, const Vector &origin);
	static SetAbsOriginFn SetAbsOrigin = (SetAbsOriginFn)Utils.FindPatternIDA("client_panorama.dll", "55 8B EC 83 E4 F8 51 53 56 57 8B F1 E8");
	SetAbsOrigin(this, origin);
}



std::array<float, 24> &CBaseEntity::m_flPoseParameter()
{
	return *(std::array<float, 24>*)((uintptr_t)this + 0x2764);
}


void CBaseEntity::InvalidateBoneCache()
{
	static DWORD invalidateBoneCache = FindPatternAimbot("\x80\x3D\x00\x00\x00\x00\x00\x74\x16\xA1\x00\x00\x00\x00\x48\xC7\x81", "xx?????xxx????xxx", 0, "client_panorama.dll");
	unsigned long g_iModelBoneCounter = **(unsigned long**)(invalidateBoneCache + 10);
	*(unsigned int*)((DWORD)this + 0x2914) = 0xFF7FFFFF; // m_flLastBoneSetupTime = -FLT_MAX;
	*(unsigned int*)((DWORD)this + 0x2680) = (g_iModelBoneCounter - 1); // m_iMostRecentModelBoneCounter = g_iModelBoneCounter - 1;
}

int CBaseEntity::GetSequence()
{
	return *reinterpret_cast<int*>((DWORD)this + offsets.m_nSequence);
}
VarMapping_t *CBaseEntity::VarMapping()
{
	return reinterpret_cast<VarMapping_t*>((DWORD)this + 0x24);
}
bool CBaseEntity::IsVisible(int bone)
{
	if (!this)
		return false;
	Ray_t ray;
	trace_t tr;
	ray.Init(G::LocalPlayer->GetEyePosition(), this->GetBonePos(bone));
	CTraceFilter traceFilter;
	traceFilter.pSkip = G::LocalPlayer;
	Interfaces.pTrace->TraceRay(ray, MASK_SHOT, &traceFilter, &tr);

	return (tr.m_pEnt == this || tr.IsVisible());
}
bool CBaseEntity::IsVisibleVector(Vector bone)
{
	if(!this || !G::LocalPlayer)
		return false;

	
	Ray_t ray;
	trace_t tr;
	ray.Init(G::LocalPlayer->GetEyePosition(), bone);
	CTraceFilter traceFilter;
	traceFilter.pSkip = G::LocalPlayer;
	Interfaces.pTrace->TraceRay(ray, MASK_SHOT, &traceFilter, &tr);

	return (tr.m_pEnt == this || tr.IsVisible());
}
bool CBaseEntity::IsEnemy()
{

	return (this->GetTeam() == G::LocalPlayer->GetTeam() || this->GetTeam() == 0) ? false : true;
}

Vector CBaseEntity::GetAbsOrigin()
{
	if (!this) return Vector(0.f, 0.f, 0.f);
	return *(Vector*)((DWORD)this + 0x134);
}
Vector CBaseEntity::GetNetworkOrigin()
{
		return *(Vector*)((DWORD)this + offsets.m_flFriction);
}
Vector CBaseEntity::GetEyeAngles()
{
	return *(Vector*)((DWORD)this + 0xB23C);
}
Vector* CBaseEntity::GetEyeAnglesPointer()
{
	return (Vector*)((DWORD)this + 0xB23C);
}

void* CBaseEntity::GetRenderableAutism()
{
	typedef void* (__thiscall* GetRenderableFn)(void*);
	return getvfunc<GetRenderableFn>(this, 5)(this);
}

bool CBaseEntity::SetupBones(matrix3x4* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime)
{
	/*if (!this)return false;
	__asm
	{
		mov edi, this
		lea ecx, dword ptr ds : [edi + 0x4]
		mov edx, dword ptr ds : [ecx]
		push currentTime
		push boneMask
		push nMaxBones
		push pBoneToWorldOut
		call dword ptr ds : [edx + 0x34]
	}*/

	const auto pRen = GetRenderable();

	typedef bool(__thiscall* SetupBonesFn)(void*, matrix3x4*, int, int, float);
	return getvfunc<SetupBonesFn>(pRen, 13)(pRen, pBoneToWorldOut, nMaxBones, boneMask, currentTime);
}


IClientNetworkable* CBaseEntity::GetNetworkable()
{
	return (IClientNetworkable*)((DWORD)this + 0x8);
}
CBaseHandle* CBaseEntity::GetWearables()
{
	return (CBaseHandle*)((uintptr_t)this + 0x2EF4);
}
void CBaseEntity::SetModelIndexVirtual(int index)
{
	typedef void(__thiscall* SetModelIndexFn)(void*, int);
	getvfunc<SetModelIndexFn>(this, 75)(this, index);
}

Vector CBaseEntity::GetVecOrigin()
{
	if (!this) return Vector(0.f, 0.f, 0.f);
	return *(Vector*)((DWORD)this + 0x134);
}
player_info_t CBaseEntity::GetPlayerInfo()
{
	player_info_t pinfo;
	Interfaces.pEngine->GetPlayerInfo(GetIndex(), &pinfo);
	return pinfo;
}
bool CBaseEntity::IsDormant()
{
	if (!Interfaces.pEngine->IsConnected())
		return true;

	return *(bool*)((DWORD)this + 0xE9);
}
int CBaseEntity::GetIndex()
{
	if (!this)
		return -1;
	int iEntIndex;

	PVOID pEnt = (PVOID)this;

	__asm
	{
		MOV ECX, this
		MOV EAX, DWORD PTR DS : [ECX + 0x8]
		MOV EDX, DWORD PTR DS : [EAX + 0x28]
		LEA ESI, DWORD PTR DS : [ECX + 0x8]
		MOV ECX, ESI
		CALL EDX
		MOV iEntIndex, EAX
	}

	return iEntIndex;
}
bool CBaseEntity::IsPlayer()
{
	if (!this)
	{
		return false;
	}
	ClientClass* cClass = (ClientClass*)this->GetClientClass();
	if(!cClass)
		return false;
	if (cClass->m_ClassID != 35)
	{
		return false;
	}
	return true;
}
bool CBaseEntity::IsWeapon()
{
	if (!this)
	{
		return false;
	}
	ClientClass* cClass = (ClientClass*)this->GetClientClass();

	if (cClass->m_ClassID != ClientClassIDS::CAK47 && cClass->m_ClassID != ClientClassIDS::CBaseCSGrenadeProjectile && cClass->m_ClassID != ClientClassIDS::CC4 && cClass->m_ClassID != ClientClassIDS::CBaseWeaponWorldModel && cClass->m_ClassID != ClientClassIDS::CDEagle && cClass->m_ClassID != ClientClassIDS::CDecoyGrenade && cClass->m_ClassID != ClientClassIDS::CFlashbang && cClass->m_ClassID != ClientClassIDS::CHEGrenade && cClass->m_ClassID != ClientClassIDS::CKnife && cClass->m_ClassID != ClientClassIDS::CMolotovGrenade && cClass->m_ClassID != ClientClassIDS::CWeaponAWP && cClass->m_ClassID != ClientClassIDS::CSmokeGrenade && cClass->m_ClassID != ClientClassIDS::CWeaponAug && cClass->m_ClassID != ClientClassIDS::CWeaponBizon && cClass->m_ClassID != ClientClassIDS::CWeaponElite && cClass->m_ClassID != ClientClassIDS::CWeaponFamas && cClass->m_ClassID != ClientClassIDS::CWeaponFiveSeven && cClass->m_ClassID != ClientClassIDS::CWeaponG3SG1 && cClass->m_ClassID != ClientClassIDS::CWeaponGlock && cClass->m_ClassID != ClientClassIDS::CWeaponGalilAR && cClass->m_ClassID != ClientClassIDS::CWeaponXM1014 && cClass->m_ClassID != ClientClassIDS::CWeaponUMP45 && cClass->m_ClassID != ClientClassIDS::CWeaponTec9 && cClass->m_ClassID != ClientClassIDS::CWeaponTaser && cClass->m_ClassID != ClientClassIDS::CWeaponSawedoff && cClass->m_ClassID != ClientClassIDS::CWeaponSSG08 && cClass->m_ClassID != ClientClassIDS::CWeaponSG556 && cClass->m_ClassID != ClientClassIDS::CWeaponSCAR20 && cClass->m_ClassID != ClientClassIDS::CWeaponP90 && cClass->m_ClassID != ClientClassIDS::CWeaponP250 && cClass->m_ClassID != ClientClassIDS::CWeaponNOVA && cClass->m_ClassID != ClientClassIDS::CWeaponSawedoff && cClass->m_ClassID != ClientClassIDS::CWeaponSG556 && cClass->m_ClassID != ClientClassIDS::CWeaponMP9 && cClass->m_ClassID != ClientClassIDS::CWeaponMag7 && cClass->m_ClassID != ClientClassIDS::CWeaponM4A1 && cClass->m_ClassID != ClientClassIDS::CWeaponNegev && cClass->m_ClassID != ClientClassIDS::CWeaponHKP2000)
	{
		return false;
	}
	return true;
}
bool CBaseEntity::IsGrenade()
{
	if (!this)
		return false;
	ClientClass* cClass = (ClientClass*)this->GetClientClass();

	if (cClass->m_ClassID == ClientClassIDS::CDecoyGrenade || cClass->m_ClassID == ClientClassIDS::CFlashbang || cClass->m_ClassID == ClientClassIDS::CHEGrenade || cClass->m_ClassID == ClientClassIDS::CMolotovGrenade)
		return true;
	else
		return false;

}
bool CBaseEntity::IsHostage()
{
	if (!this)
	{
		return false;
	}
	ClientClass* cClass = (ClientClass*)this->GetClientClass();

	return cClass->m_ClassID == ClientClassIDS::CHostage;
}
bool CBaseEntity::IsChicken()
{
	if (!this)
	{
		return false;
	}
	ClientClass* cClass = (ClientClass*)this->GetClientClass();

	return cClass->m_ClassID == ClientClassIDS::CChicken;
}
int CBaseEntity::GetHealth()
{
	return *(int*)((DWORD)this + offsets.m_iHealth);
}
bool CBaseEntity::isAlive()
{
	return (bool)(*(int*)((DWORD)this + offsets.m_lifeState) == 0);
}
int CBaseEntity::GetFlags()
{
	return *(int*)((DWORD)this + 0x100);
}
int CBaseEntity::GetTeam()
{
	if (!this)return NULL;
	return *(int*)((DWORD)this + offsets.m_iTeamNum);
}
float CBaseEntity::GetFlashDuration()
{
	if (!this)return NULL;
	return *(float*)((DWORD)this + 0xA308);
}
bool CBaseEntity::IsFlashed()
{
	if (!this)return false;
	return GetFlashDuration() > 0;
}
int CBaseEntity::GetTickBase(void)
{
	if (!this)return NULL;
	return *(int*)((DWORD)this + offsets.m_nTickBase);
}
float CBaseEntity::BombTimer()
{
	if (!this)return NULL;
	float flBombTime = *(float*)((DWORD)this + 0x297C);
	return (flBombTime > 0.f) ? flBombTime : 0.f;
}
float CBaseEntity::pelvisangs()
{
	if (!this)return NULL;
	return *(float*)((DWORD)this + 0x39EC);
}
Vector& CBaseEntity::GetAbsAnglesNew()
{
	if (!this)return Vector();
	using OriginalFn = Vector & (__thiscall*)(void*);
	return getvfunc<OriginalFn>(this, 11)(this);
}
Vector CBaseEntity::GetVecViewOffset()
{
	if (!this)return Vector();
	return *(Vector*)((DWORD)this + offsets.m_vecViewOffset);
}
Vector CBaseEntity::BBMin()
{
	if (!this)return Vector();
	return *(Vector*)((DWORD)this + offsets.m_vecMins);
}
Vector CBaseEntity::BBMax()
{
	if (!this)return Vector();
	return *(Vector*)((DWORD)this + offsets.m_vecMaxs);
}
bool CBaseEntity::m_bIsScoped()
{
	if (!this)
		return false;
	return *(bool*)((DWORD)this + offsets.m_bIsScoped);
}
int CBaseEntity::GetMoveType()
{
	if (!this)return NULL;
	return *(int*)((DWORD)this + offsets.m_nMoveType);
}
int CBaseEntity::GetShootsField()
{
	if (!this)return NULL;
	return *reinterpret_cast<int*>((DWORD)this + 0xA2C0);
}
Vector CBaseEntity::GetBonePos(int i)
{
	if (!this)
		return Vector(0.0f, 0.0f, 0.0f);

	matrix3x4 boneMatrix[128];
	if (this->SetupBones(boneMatrix, 128, BONE_USED_BY_HITBOX, 0))
	{
		return Vector(boneMatrix[i][0][3], boneMatrix[i][1][3], boneMatrix[i][2][3]);
	}
	return Vector(0.0f, 0.0f, 0.0f);
}
int CBaseEntity::GetHitboxSet()
{
	if (!this)return NULL;
	return *(int*)((DWORD)this + 0x9FC);
}
Vector CBaseEntity::WorldSpaceCenter()
{
	Vector Max = this->BBMax() + this->GetAbsOrigin();
	Vector Min = this->BBMin() + this->GetAbsOrigin();

	Vector Size = Max - Min;

	Size /= 2;

	Size += Min;

	return Size;
}
Vector CBaseEntity::GetEyePosition()
{
	if (!this)return Vector();
	return GetAbsOrigin() + GetVecViewOffset();
}
bool CBaseEntity::BombDefused()
{
	if (!this)
		return false;
	return *(bool*)((DWORD)this + offsets.m_bBombDefused);
}
Vector CBaseEntity::GetPunchAngle()
{
	return *(Vector*)((DWORD)this + offsets.m_aimPunchAngle);
}
bool CBaseEntity::GetScope()
{
	if (!this)
		return false;
	return *(bool*)((DWORD)this + offsets.m_bIsScoped);
}
Vector CBaseEntity::GetVecVelocity()
{
	return *(Vector*)((DWORD)this + 0x110);
}
float CBaseEntity::GetLowerBodyYaw()
{
	return *(float*)((DWORD)this + offsets.m_flLowerBodyYawTarget);
}
Vector* CBaseEntity::GetPunchAnglePtr()
{
	return (Vector*)((DWORD)this + offsets.m_aimPunchAngle);
}
float CBaseEntity::GetSimulationTime()
{
	if (!this)return NULL;
	return *(float*)((DWORD)this + offsets.m_flSimulationTime);
}
Vector* CBaseEntity::GetViewPunchAnglePtr()
{
	return (Vector*)((DWORD)this + 0x3010);
}
bool CBaseEntity::HasGunGameImmunity()
{
	if (!this)
		return false;
	return *(bool*)((DWORD)this + offsets.m_bGunGameImmunity);
}
bool CBaseEntity::HasHelmet()
{
	if (!this)
		return false;
	return *(bool*)((DWORD)this + offsets.m_bHasHelmet);
}
bool CBaseEntity::IsDefusing()
{
	if (!this)return false;

	return *(int*)((DWORD)this + 0x3898);
}
int CBaseEntity::GetArmor()
{
	return *(int*)((DWORD)this + 0xB24C);
}
bool CBaseEntity::HasKit()
{
	if (!this)
		return false;
	return *(bool*)((DWORD)this + offsets.m_bHasDefuser);
}

CBaseHandle CBaseCombatWeapon::GetOwnerHandle()
{
	if (!this)return NULL;
	return *reinterpret_cast<CBaseHandle*>(uintptr_t(this) + offsets.m_hOwnerEntity);
}

const char* CBaseCombatWeapon::GetName()
{
	typedef const char* (__thiscall* tGetName)(void*);
	return getvfunc< tGetName >(this, 376)(this);
}

void CBaseCombatWeapon::UpdateAccuracyPenalty()
{
	if (!this)
		return;

	typedef void(__thiscall* OriginalFn)(void*);
	getvfunc<OriginalFn>(this, 468)(this);
}
float CBaseCombatWeapon::GetInaccuracy()
{
	if (!this)
		return 0.f;

	typedef float(__thiscall* OriginalFn)(void*);
	return getvfunc< OriginalFn >(this, 467)(this);
}
float CBaseCombatWeapon::GetSpread()
{
	if (!this)
		return 0.f;

	typedef float(__thiscall* OriginalFn)(void*);
	return getvfunc< OriginalFn >(this, 436)(this);
}
bool CBaseCombatWeapon::HasAmmo()
{
	if (IsMiscWeapon())
		return 1;
	return ammo() > 0;
}
bool CBaseCombatWeapon::isPistol()
{
	if (!this)
		return false;
	int WeaponId = *this->GetItemDefinitionIndex();

	return WeaponId == WEAPON_DEAGLE || WeaponId == WEAPON_ELITE || WeaponId == WEAPON_FIVESEVEN || WeaponId == WEAPON_P250 ||
		WeaponId == WEAPON_GLOCK || WeaponId == WEAPON_USP_SILENCER || WeaponId == WEAPON_CZ75A || WeaponId == WEAPON_HKP2000 || WeaponId == WEAPON_TEC9 /*|| WeaponId == weapon_revolver*/;
}
bool CBaseCombatWeapon::isShotgun()
{
	if (!this)
		return false;
	int WeaponId = *this->GetItemDefinitionIndex();

	return WeaponId == WEAPON_XM1014 || WeaponId == WEAPON_NOVA || WeaponId == WEAPON_SAWEDOFF || WeaponId == WEAPON_MAG7;
}
bool CBaseCombatWeapon::isSniper()
{
	if (!this)
		return false;
	int WeaponId = *this->GetItemDefinitionIndex();

	return WeaponId == WEAPON_AWP || WeaponId == WEAPON_SCAR20 || WeaponId == WEAPON_G3SG1 || WeaponId == WEAPON_SSG08;
}
bool CBaseCombatWeapon::isScoped()
{
	if (!this)
		return false;
	int WeaponId = *this->GetItemDefinitionIndex();

	return WeaponId == WEAPON_AWP || WeaponId == WEAPON_SCAR20 || WeaponId == WEAPON_G3SG1 || WeaponId == WEAPON_SSG08 || WeaponId == WEAPON_SG556 || WeaponId == WEAPON_AUG;
}
bool CBaseCombatWeapon::isAWP()
{
	if (!this)
		return false;
	int WeaponId = *this->GetItemDefinitionIndex();

	return WeaponId == WEAPON_AWP;
}
bool CBaseCombatWeapon::isScout()
{
	if (!this)
		return false;
	int WeaponId = *this->GetItemDefinitionIndex();

	return WeaponId == WEAPON_SG556;
}

bool CBaseCombatWeapon::IsGun()
{
	if (!this)
		return false;
	int id = *this->GetItemDefinitionIndex();

	if (id == WEAPON_KNIFE || id == WEAPON_HEGRENADE || id == WEAPON_DECOY || id == WEAPON_INCGRENADE || id == WEAPON_MOLOTOV || id == WEAPON_C4 || id == WEAPON_FLASHBANG || id == WEAPON_SMOKEGRENADE || id == WEAPON_KNIFE_T)
		return false;
	else
		return true;
}
bool CBaseCombatWeapon::isRifle()
{
	if (!this)
		return false;
	int WeaponId = *this->GetItemDefinitionIndex();

	return WeaponId == WEAPON_AK47 || WeaponId == WEAPON_M4A1 || WeaponId == WEAPON_M4A1_SILENCER || WeaponId == WEAPON_GALILAR || WeaponId == WEAPON_FAMAS ||
		WeaponId == WEAPON_AUG || WeaponId == WEAPON_SG556;
}
bool CBaseCombatWeapon::isSmgW()
{
	if (!this)
		return false;
	int WeaponId = *this->GetItemDefinitionIndex();

	return WeaponId == WEAPON_MAC10 || WeaponId == WEAPON_MP7 || WeaponId == WEAPON_MP9 || WeaponId == WEAPON_P90 || WeaponId == WEAPON_MP5 ||
		WeaponId == WEAPON_BIZON || WeaponId == WEAPON_UMP45;
}
bool CBaseCombatWeapon::isMachineW()
{
	if (!this)
		return false;
	int WeaponId = *this->GetItemDefinitionIndex();

	return WeaponId == WEAPON_NEGEV || WeaponId == WEAPON_M249;
}
bool CBaseCombatWeapon::IsNade()
{
	if (!this)
		return false;
	int WeaponId = *this->GetItemDefinitionIndex();

	return WeaponId == WEAPON_FLASHBANG || WeaponId == WEAPON_HEGRENADE || WeaponId == WEAPON_SMOKEGRENADE ||
		WeaponId == WEAPON_MOLOTOV || WeaponId == WEAPON_DECOY || WeaponId == WEAPON_INCGRENADE;
}
int CBaseCombatWeapon::BulletSize()
{
	if (!this)
		return NULL;

	int WeaponId = *this->GetItemDefinitionIndex();
	switch (WeaponId)
	{
	case WEAPON_ELITE:
	case WEAPON_MAC10:
	case WEAPON_M4A1:
	case WEAPON_AK47:
	case WEAPON_MP5:
	case WEAPON_MP7:
	case WEAPON_MP9:
	case WEAPON_SG556:
	case WEAPON_AUG:
		return 30;
	case WEAPON_NEGEV:
		return 150;
	case WEAPON_M249:
		return 100;
	case WEAPON_REVOLVER:
		return 8;
	case WEAPON_M4A1_SILENCER:
	case WEAPON_GLOCK:
	case WEAPON_SCAR20:
	case WEAPON_G3SG1:
		return 20;
	case WEAPON_DEAGLE:
		return 7;
	case WEAPON_P90:
		return 50;
	case WEAPON_UMP45:
		return 25;
	case WEAPON_SSG08:
	case WEAPON_AWP:
		return 10;
	case WEAPON_GALILAR:
		return 35;
	case WEAPON_FAMAS:
		return 25;
	case WEAPON_CZ75A:
	case WEAPON_USP_SILENCER:
		return 12;
	case WEAPON_HKP2000:
	case WEAPON_P250:
		return 13;
	case WEAPON_TEC9:
		return 24;
	case WEAPON_NOVA:
		return 8;
	case WEAPON_XM1014:
	case WEAPON_SAWEDOFF:
		return 7;
	case WEAPON_MAG7:
		return 5;
	case WEAPON_BIZON:
		return 64;
	default:
		return 1;

	}

}
float CBaseCombatWeapon::hitchance()
{
	float inaccuracy = GetInaccuracy();
	if (inaccuracy == 0)
		inaccuracy = 0.0000001f;
	inaccuracy = 1 / inaccuracy;
	return inaccuracy;
}
bool CBaseCombatWeapon::IsMiscWeapon()
{
	int iWeaponID = *this->GetItemDefinitionIndex();
	return (iWeaponID == tknife || iWeaponID == ctknife
		|| iWeaponID == goldknife || iWeaponID == bomb
		|| iWeaponID == hegren || iWeaponID == decoygren
		|| iWeaponID == flashgren || iWeaponID == molotov
		|| iWeaponID == smoke || iWeaponID == incendiary || iWeaponID == 59
		|| iWeaponID == 500 || iWeaponID == 505 || iWeaponID == 506
		|| iWeaponID == 507 || iWeaponID == 508 || iWeaponID == 509
		|| iWeaponID == 515);
}
bool CBaseCombatWeapon::IsGrenade()
{
	int iWeaponID = *this->GetItemDefinitionIndex();
	return (iWeaponID == decoygren
		|| iWeaponID == flashgren || iWeaponID == molotov || iWeaponID == hegren
		|| iWeaponID == smoke || iWeaponID == incendiary);
}
bool CBaseCombatWeapon::IsKnife()
{
	int iWeaponID = *this->GetItemDefinitionIndex();
	return (iWeaponID == tknife || iWeaponID == ctknife
		|| iWeaponID == goldknife || iWeaponID == 59 || iWeaponID == 41
		|| iWeaponID == 500 || iWeaponID == 505 || iWeaponID == 506
		|| iWeaponID == 507 || iWeaponID == 508 || iWeaponID == 509
		|| iWeaponID == 515);
}
bool CBaseCombatWeapon::IsReloading()//
{
	if (!this)return false;

	return *(bool*)((DWORD)this + 0x3275);
}
CCSWeaponInfo* CBaseCombatWeapon::GetCSWpnData()//
{
	if (!this) return nullptr;
	typedef CCSWeaponInfo*(__thiscall* OriginalFn)(void*);
	return getvfunc<OriginalFn>(this, 444)(this);
}
float CBaseCombatWeapon::GetPostponeFireReadyTime()
{
	return *(float*)((DWORD)this + offsets.m_flPostponeFireReadyTime);
}
float CBaseCombatWeapon::NextPrimaryAttack()
{
	return *(float*)((DWORD)this + offsets.m_flNextPrimaryAttack);
}

short* CBaseCombatWeapon::GetItemDefinitionIndex()
{
	return (short*)((DWORD)this + 0x2F9A);
}
int CBaseCombatWeapon::ammo()//
{
	return *(int*)((DWORD)this + 0x3234);
}

float CBaseCSGrenade::GetPinPulled()
{
	return *(float*)((DWORD)this + offsets.m_bPinPulled);
}
float CBaseCSGrenade::GetThrowTime()
{
	return *(float*)((DWORD)this + offsets.m_fThrowTime);
}


IClientNetworkable* CBaseAttributableItem::GetNetworkable()
{
	return reinterpret_cast<IClientNetworkable*>((DWORD)this + 0x8);
}
void CBaseAttributableItem::SetModelIndex(int index)
{
	typedef void(__thiscall* Fn)(void*, int);
	return getvfunc<Fn>(this, 75)(this, index);
}
void CBaseAttributableItem::PreDataUpdate(int updateType)
{
	PVOID pNetworkable = (PVOID)((DWORD)(this) + 0x8);
	typedef void(__thiscall* OriginalFn)(PVOID, int);
	return getvfunc<OriginalFn>(pNetworkable, 6)(pNetworkable, updateType);
}
 short* CBaseAttributableItem::GetItemDefinitionIndex() 
 {

	return (short*)((DWORD)this + 0x2F9A);
}

 int* CBaseAttributableItem::GetItemIDHigh() {
	// DT_BaseAttributableItem -> m_AttributeManager: 0x2D50
	// DT_BaseAttributableItem -> m_AttributeManager -> m_Item: 0x40
	// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_iItemIDHigh: 0x1E8
	return (int*)((DWORD)this + offsets.m_iItemIDHigh);
}
 int* CBaseAttributableItem::GetItemIDLow()
{
	return (int*)((DWORD)this + offsets.m_iItemIDLow);
}

 int* CBaseAttributableItem::GetEntityQuality() {
	// DT_BaseAttributableItem -> m_AttributeManager: 0x2D50
	// DT_BaseAttributableItem -> m_AttributeManager -> m_Item: 0x40
	// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_iCBaseEntityQuality: 0x1D4
	return (int*)((DWORD)this + offsets.m_iEntityQuality);
}

 char* CBaseAttributableItem::GetCustomName() {
	// DT_BaseAttributableItem -> m_AttributeManager: 0x2D50
	// DT_BaseAttributableItem -> m_AttributeManager -> m_Item: 0x40
	// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_szCustomName: 0x264
	return (char*)((DWORD)this + offsets.m_szCustomName);
}

 int* CBaseAttributableItem::GetOriginalOwnerXuidLow() {
	// DT_BaseAttributableItem -> m_OriginalOwnerXuidLow: 0x3138
	return (int*)((DWORD)this + offsets.m_OriginalOwnerXuidLow);
}

 int* CBaseAttributableItem::GetOriginalOwnerXuidHigh() {
	// DT_BaseAttributableItem -> m_OriginalOwnerXuidHigh: 0x313C
	return (int*)((DWORD)this + offsets.m_OriginalOwnerXuidHigh);
}

 int* CBaseAttributableItem::GetFallbackPaintKit() {
	// DT_BaseAttributableItem -> m_nFallbackPaintKit: 0x3140
	return (int*)((DWORD)this + offsets.m_nFallbackPaintKit);
}

 int* CBaseAttributableItem::GetFallbackSeed() {
	// DT_BaseAttributableItem -> m_nFallbackSeed: 0x3144
	return (int*)((DWORD)this + offsets.m_nFallbackSeed);
}

 float* CBaseAttributableItem::GetFallbackWear() {
	// DT_BaseAttributableItem -> m_flFallbackWear: 0x3148
	return (float*)((DWORD)this + offsets.m_flFallbackWear);
}

 int* CBaseAttributableItem::GetFallbackStatTrak() {
	// DT_BaseAttributableItem -> m_nFallbackStatTrak: 0x314C
	return (int*)((DWORD)this + offsets.m_nFallbackStatTrak);
}


 unsigned int* CBaseAttributableItem::GetAccountID()
{
	return (unsigned int*)((DWORD)this + offsets.m_iAccountID);
}

int& CBaseCombatWeapon::GetModelIndex()
{
	return *(int*)((DWORD)this + offsets.m_nModeIndex);
}
model_t* CBaseCombatWeapon::GetModel()
{
	return *(model_t**)((DWORD)this + 0x6C);
}
IClientRenderable* CBaseEntity::GetRenderable()
{
	return reinterpret_cast<IClientRenderable*>((DWORD)this + 0x4);
}

int CBaseEntity::DrawModelChams(int flags, uint8_t alpha) {
	using fn = int(__thiscall*)(void*, int, uint8_t);
	return getvfunc< fn >(GetRenderable(), 9)(GetRenderable(), flags, alpha);
}


std::string CBaseCombatWeapon::GetWeaponName()
{
	int id = *this->GetItemDefinitionIndex();
	switch (id)
	{
	case WEAPON_DEAGLE:
		return ("Desert Eagle");
	case WEAPON_ELITE:
		return ("Dual Berettas");
	case WEAPON_FIVESEVEN:
		return ("Five-Seven");
	case WEAPON_GLOCK:
		return ("Glock-18");
	case WEAPON_AK47:
		return ("AK-47");
	case WEAPON_AUG:
		return ("AUG");
	case WEAPON_MP5:
		return ("MP-5");
	case WEAPON_AWP:
		return ("AWP");
	case WEAPON_FAMAS:
		return ("FAMAS");
	case WEAPON_G3SG1:
		return ("G3SG1");
	case WEAPON_GALILAR:
		return ("Galil-AR");
	case WEAPON_M249:
		return ("M249");
	case WEAPON_M4A1:
		return ("M4A1");
	case WEAPON_MAC10:
		return ("MAC-10");
	case WEAPON_P90:
		return ("P90");
	case WEAPON_UMP45:
		return ("UMP-45");
	case WEAPON_XM1014:
		return ("XM1014");
	case WEAPON_BIZON:
		return ("PP-Bizon");
	case WEAPON_MAG7:
		return ("MAG-7");
	case WEAPON_NEGEV:
		return ("Negev");
	case WEAPON_SAWEDOFF:
		return ("Sawed-Off");
	case WEAPON_TEC9:
		return ("Tec-9");
	case WEAPON_TASER:
		return ("Taser");
	case WEAPON_HKP2000:
		return ("P2000");
	case WEAPON_MP7:
		return ("MP7");
	case WEAPON_MP9:
		return ("MP9");
	case WEAPON_NOVA:
		return ("Nova");
	case WEAPON_P250:
		return ("P250");
	case WEAPON_SCAR20:
		return ("SCAR-20");
	case WEAPON_SG556:
		return ("SG 553");
	case WEAPON_SSG08:
		return ("SSG 08");
	case WEAPON_KNIFE:
		return ("Knife");
	case WEAPON_FLASHBANG:
		return ("Flashbang");
	case WEAPON_HEGRENADE:
		return ("HE Grenade");
	case WEAPON_SMOKEGRENADE:
		return ("Smoke Grenade");
	case WEAPON_MOLOTOV:
		return ("Molotov");
	case WEAPON_DECOY:
		return ("Decoy");
	case WEAPON_INCGRENADE:
		return ("Incendiary Grenade");
	case WEAPON_C4:
		return ("C4");
	case WEAPON_M4A1_SILENCER:
		return ("M4A1-S");
	case WEAPON_USP_SILENCER:
		return ("USP-S");
	case WEAPON_CZ75A:
		return ("CZ75-Auto");
	case WEAPON_REVOLVER:
		return ("R8 Revolver");
	default:
		return ("Knife");
	}

	return "";
}


int CBaseEntity::GetSequenceActivity(int sequence)
{
	if (!this)return -1;

	auto hdr = Interfaces.g_pModelInfo->GetStudioModel(this->GetModel());

	if (!hdr)
		return -1;

	// c_csplayer vfunc 242, follow calls to find the function.

	static auto getSequenceActivity = (DWORD)(Utils.FindPatternIDA("client_panorama.dll", "55 8B EC 83 7D 08 FF 56 8B F1 74"));
	static auto GetSequenceActivity = reinterpret_cast<int(__fastcall*)(void*, studiohdr_t*, int)>(getSequenceActivity);

	return GetSequenceActivity(this, hdr, sequence);
}