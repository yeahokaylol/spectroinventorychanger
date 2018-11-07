#pragma once

#include "Offsets.h"
#include "Xor.h"
#define OffsetsHelper 
COffsets offsets;

void Offsets::GrabOffsets()
{
	offsets.m_nSequence = NetVarManager->GetOffset(OffsetsHelper("DT_CSPlayer"), OffsetsHelper("m_nSequence"));
	offsets.m_iHealth = NetVarManager->GetOffset(OffsetsHelper("DT_CSPlayer"), OffsetsHelper("m_iHealth"));
	offsets.m_iTeamNum = NetVarManager->GetOffset(OffsetsHelper("DT_CSPlayer"), OffsetsHelper("m_iTeamNum"));
	offsets.m_ArmorValue = NetVarManager->GetOffset(OffsetsHelper("DT_CSPlayer"), OffsetsHelper("m_ArmorValue"));
	offsets.m_bHasHelmet = NetVarManager->GetOffset(OffsetsHelper("DT_CSPlayer"), OffsetsHelper("m_bHasHelmet"));
	offsets.m_bHasDefuser = NetVarManager->GetOffset(OffsetsHelper("DT_CSPlayer"), OffsetsHelper("m_bHasDefuser"));
	offsets.m_bGunGameImmunity = NetVarManager->GetOffset(OffsetsHelper("DT_CSPlayer"), OffsetsHelper("m_bGunGameImmunity"));
	offsets.m_lifeState = NetVarManager->GetOffset(OffsetsHelper("DT_CSPlayer"), OffsetsHelper("m_lifeState"));
	offsets.m_nTickBase = NetVarManager->GetOffset(OffsetsHelper("DT_CSPlayer"), OffsetsHelper("m_nTickBase"));
	offsets.m_flFlashDuration = NetVarManager->GetOffset(OffsetsHelper("DT_CSPlayer"), OffsetsHelper("m_flFlashDuration"));
	offsets.m_viewPunchAngle = NetVarManager->GetOffset(OffsetsHelper("DT_BasePlayer"), OffsetsHelper("m_viewPunchAngle"));
	offsets.m_aimPunchAngle = NetVarManager->GetOffset(OffsetsHelper("DT_BasePlayer"), OffsetsHelper("m_aimPunchAngle"));
	offsets.m_vecOrigin = NetVarManager->GetOffset(OffsetsHelper("DT_BasePlayer"), OffsetsHelper("m_vecOrigin"));
	offsets.m_vecViewOffset = NetVarManager->GetOffset(OffsetsHelper("DT_CSPlayer"), OffsetsHelper("m_vecViewOffset[0]"));
	offsets.m_hActiveWeapon = NetVarManager->GetOffset(OffsetsHelper("DT_CSPlayer"), OffsetsHelper("m_hActiveWeapon"));
	offsets.m_hOwnerEntity = NetVarManager->GetOffset(OffsetsHelper("DT_BaseEntity"), OffsetsHelper("m_hOwnerEntity"));
	offsets.m_nMoveType = 0x258;

	offsets.m_angRotation = NetVarManager->GetOffset(OffsetsHelper("DT_BaseEntity"), OffsetsHelper("m_angRotation"));
	
	offsets.m_flC4Blow = NetVarManager->GetOffset(OffsetsHelper("DT_PlantedC4"), OffsetsHelper("m_flC4Blow"));
	offsets.m_bBombDefused = NetVarManager->GetOffset(OffsetsHelper("DT_PlantedC4"), OffsetsHelper("m_bBombDefused"));


	offsets.m_bPinPulled = NetVarManager->GetOffset(OffsetsHelper("DT_BaseCSGrenade"), OffsetsHelper("m_bPinPulled"));
	offsets.m_fThrowTime = NetVarManager->GetOffset(OffsetsHelper("DT_BaseCSGrenade"), OffsetsHelper("m_fThrowTime"));

	offsets.m_vecMins = NetVarManager->GetOffset(OffsetsHelper("DT_BaseEntity"), OffsetsHelper("m_vecMins"));
	offsets.m_vecMaxs = NetVarManager->GetOffset(OffsetsHelper("DT_BaseEntity"), OffsetsHelper("m_vecMaxs"));

	offsets.m_flFriction = NetVarManager->GetOffset(OffsetsHelper("DT_CSPlayer"), OffsetsHelper("m_flFriction"));
	offsets.m_bSpotted = NetVarManager->GetOffset(OffsetsHelper("DT_BaseEntity"), OffsetsHelper("m_bSpotted"));

	offsets.m_flPostponeFireReadyTime = NetVarManager->GetOffset(OffsetsHelper("DT_WeaponCSBase"), OffsetsHelper("m_flPostponeFireReadyTime"));


	offsets.m_flPoseParameter = NetVarManager->GetOffset(("DT_CSPlayer"), ("m_flPoseParameter"));

	offsets.m_nAccountID = 0x2FB8;
	offsets.m_nModeIndex = NetVarManager->GetOffset("DT_BaseViewModel", "m_nModelIndex");



	offsets.m_hViewModel = NetVarManager->GetOffset("DT_BasePlayer", "m_hViewModel[0]");
	if (!offsets.m_hViewModel)
		offsets.m_hViewModel = 0x32FC;
	offsets.m_hWeapon = NetVarManager->GetOffset("DT_BaseViewModel", "m_hWeapon");



	offsets.m_hObserverTarget = NetVarManager->GetOffset("DT_CSPlayer", "m_hObserverTarget");

	offsets.m_flNextPrimaryAttack = NetVarManager->GetOffset(OffsetsHelper("DT_BaseCombatWeapon"), OffsetsHelper("m_flNextPrimaryAttack"));
	offsets.m_nFallbackPaintKit = NetVarManager->GetOffset(OffsetsHelper("DT_BaseCombatWeapon"), OffsetsHelper("m_nFallbackPaintKit"));
	offsets.m_nFallbackSeed = NetVarManager->GetOffset(OffsetsHelper("DT_BaseCombatWeapon"), OffsetsHelper("m_nFallbackSeed"));
	offsets.m_flFallbackWear = NetVarManager->GetOffset(OffsetsHelper("DT_BaseCombatWeapon"), OffsetsHelper("m_flFallbackWear"));
	offsets.m_nFallbackStatTrak = NetVarManager->GetOffset(OffsetsHelper("DT_BaseCombatWeapon"), OffsetsHelper("m_nFallbackStatTrak"));
	offsets.m_AttributeManager = NetVarManager->GetOffset(OffsetsHelper("DT_BaseCombatWeapon"), OffsetsHelper("m_AttributeManager"));
	offsets.m_szCustomName = NetVarManager->GetOffset(OffsetsHelper("DT_BaseCombatWeapon"), OffsetsHelper("m_szCustomName"));
	offsets.m_Item = NetVarManager->GetOffset(OffsetsHelper("DT_BaseCombatWeapon"), OffsetsHelper("m_Item"));
	offsets.m_iEntityLevel = NetVarManager->GetOffset(OffsetsHelper("DT_BaseCombatWeapon"), OffsetsHelper("m_iEntityLevel"));
	offsets.m_iItemIDHigh = NetVarManager->GetOffset(OffsetsHelper("DT_BaseCombatWeapon"), OffsetsHelper("m_iItemIDHigh"));
	offsets.m_iItemIDLow = NetVarManager->GetOffset(OffsetsHelper("DT_BaseCombatWeapon"), OffsetsHelper("m_iItemIDLow"));
	offsets.m_iAccountID = NetVarManager->GetOffset(OffsetsHelper("DT_BaseCombatWeapon"), OffsetsHelper("m_iAccountID"));
	offsets.m_iEntityQuality = NetVarManager->GetOffset(OffsetsHelper("DT_BaseCombatWeapon"), OffsetsHelper("m_iEntityQuality"));
	offsets.m_OriginalOwnerXuidLow = NetVarManager->GetOffset(OffsetsHelper("DT_BaseAttributableItem"), OffsetsHelper("m_OriginalOwnerXuidLow"));
	offsets.m_OriginalOwnerXuidHigh = NetVarManager->GetOffset(OffsetsHelper("DT_BaseAttributableItem"), OffsetsHelper("m_OriginalOwnerXuidHigh"));
	offsets.m_iItemDefinitionIndex = NetVarManager->GetOffset(OffsetsHelper("DT_BaseAttributableItem"), OffsetsHelper("m_iItemDefinitionIndex"));
	offsets.m_flSimulationTime = NetVarManager->GetOffset(OffsetsHelper("DT_BaseEntity"), OffsetsHelper("m_flSimulationTime"));
	offsets.m_flLowerBodyYawTarget = NetVarManager->GetOffset(OffsetsHelper("DT_CSPlayer"), OffsetsHelper("m_flLowerBodyYawTarget"));
	offsets.m_bIsScoped = NetVarManager->GetOffset(OffsetsHelper("DT_CSPlayer"), OffsetsHelper("m_bIsScoped"));
//	offsets.GlowManager = *(DWORD*)(Utils.FindPatternIDA(("client_panorama.dll"), ("0F 11 05 ?? ?? ?? ?? 83 C8 01 C7 05 ?? ?? ?? ?? 00 00 00 00")) + 3);
	offsets.LoadFromBufferEx = Utils.FindPatternIDA(("client_panorama.dll"), ("55 8B EC 83 E4 F8 83 EC 34 53 8B 5D 0C 89 4C 24 04"));
	offsets.InitKeyValuesEx = Utils.FindPatternIDA(("client_panorama.dll"), ("55 8B EC 51 33 C0 C7 45"));
	offsets.ServerRankRevealAllEx = Utils.FindPatternIDA(("client_panorama.dll"), ("55 8B EC 8B 0D ? ? ? ? 85 C9 75 ? A1 ? ? ? ? 68 ? ? ? ? 8B 08 8B 01 FF 50 ? 85 C0 74 ? 8B C8 E8 ? ? ? ? 8B C8 EB ? 33 C9 89 0D ? ? ? ? 8B 45 ? FF 70 ? E8 ? ? ? ? B0 ? 5D"));
	offsets.ClipTraceToPlayersFn = Utils.FindPatternIDA(("client_panorama.dll"), ("53 8B DC 83 EC 08 83 E4 F0 83 C4 04 55 8B 6B 04 89 6C 24 04 8B EC 81 EC ? ? ? ? 8B 43 10"));
	offsets.GlowManager = *(DWORD*)(Utils.FindPatternIDA(("client_panorama.dll"), ("A1 ? ? ? ? A8 01 75 4B")) + 0x19);

	offsets.InvalidateBoneCacheEx = Utils.FindPatternIDA("client_panorama.dll", "80 3D ? ? ? ? ? 74 16 A1 ? ? ? ? 48 C7 81");
	offsets.IDA_FullUpdate = Utils.FindPatternIDA(("engine.dll"), ("A1 ? ? ? ? B9 ? ? ? ? 56 FF 50 14 8B 34 85"));
	offsets.dwIsReady = Utils.FindPatternIDA("client_panorama.dll", ("55 8B EC 83 E4 F8 83 EC 08 56 8B 35 ? ? ? ? 57 83 BE"));

//		offsets.GlowManager = *(DWORD*)(Utils.FindPatternIDA(strenc("client_panorama.dll"), strenc("A1 ? ? ? ? A8 01 75 4B")) + 0x19);
//	offsets.GlowManager = (*(DWORD*)(Utils.FindPatternIDA("client_panorama.dll", "A1 ? ? ? ? A8 01 75 4B") + 0x1)) + 4;
}
