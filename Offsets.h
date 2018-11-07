#pragma once

#include "stdafx.h"
//typedef unsigned __int16 DWORD;
struct COffsets
{

	DWORD m_nSequence;
	DWORD m_iHealth;
	DWORD m_iTeamNum;
	DWORD m_bGunGameImmunity;
	DWORD m_lifeState;
	DWORD m_nTickBase;
	DWORD m_viewPunchAngle;
	DWORD m_aimPunchAngle;
	DWORD m_vecOrigin;
	DWORD m_vecViewOffset;
	DWORD m_flNextPrimaryAttack;
	DWORD m_hActiveWeapon;
	DWORD m_nMoveType;
	DWORD m_bHasHelmet;
	DWORD m_ArmorValue;
	DWORD m_hOwnerEntity;
	DWORD m_flFlashDuration;
	DWORD m_bIsScoped;
	DWORD m_nFallbackPaintKit;
	DWORD m_nFallbackSeed;
	DWORD m_flFallbackWear;
	DWORD m_nFallbackStatTrak;
	DWORD m_AttributeManager;
	DWORD m_Item;
	DWORD m_iEntityLevel;
	DWORD m_iItemIDHigh;
	DWORD m_iItemIDLow;
	DWORD m_iAccountID;
	DWORD m_iEntityQuality;
	DWORD m_OriginalOwnerXuidLow;
	DWORD m_OriginalOwnerXuidHigh;
	DWORD m_iItemDefinitionIndex;
	DWORD m_flLowerBodyYawTarget;
	DWORD m_flSimulationTime;
	DWORD ClipTraceToPlayersFn;
	//sigs
	DWORD LoadFromBufferEx;
	DWORD InitKeyValuesEx;
	DWORD ServerRankRevealAllEx;
	uintptr_t m_hObserverTarget;



	DWORD m_flFriction;
	DWORD m_flC4Blow;
	DWORD m_vecMins;
	DWORD m_vecMaxs;
	DWORD m_bBombDefused;
	DWORD m_bSpotted;
	DWORD m_angRotation;
	DWORD m_bHasDefuser;
	DWORD m_flPostponeFireReadyTime;
	DWORD m_szCustomName;
	DWORD m_bPinPulled;
	DWORD m_fThrowTime;

	DWORD m_nAccountID;
	DWORD m_nModeIndex;
	DWORD m_hViewModel;
	DWORD m_hWeapon;
	DWORD GlowManager;
	DWORD InvalidateBoneCacheEx;
	DWORD m_flPoseParameter;
	DWORD IDA_FullUpdate;
	DWORD dwIsReady;
};

extern COffsets offsets;

namespace Offsets
{
	extern void GrabOffsets();
}
