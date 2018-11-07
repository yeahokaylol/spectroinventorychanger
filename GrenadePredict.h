#pragma once

#include "stdafx.h"


#define GrenadePrediction CGrenadePrediction::GetInstance()

class CGrenadePrediction {
	IMPLEMENT_SINGLETON(CGrenadePrediction);

public:
	void Tick(int buttons);
	void PredictGrenade();
	void PaintGrenadeTrajectory();
private:
	void Setup(CBaseEntity* pl, Vector& vecSrc, Vector& vecThrow, const Vector& angEyeAngles);
	void Simulate();
	int  Step(Vector& vecSrc, Vector& vecThrow, int tick, float interval);
	bool CheckDetonate(const Vector& vecThrow, const trace_t& tr, int tick, float interval);
	void AddGravityMove(Vector& move, Vector& vel, float frametime, bool onground);
	void HullTrace(Vector src, Vector end, ITraceFilter* filter, trace_t& tr);
	void PushEntity(Vector& src, const Vector& move, trace_t& tr);
	void ResolveFlyCollisionCustom(trace_t& tr, Vector& vecVelocity, float interval);
	unsigned char PhysicsClipVelocity(const Vector& in, const Vector& normal, Vector& out, float overbounce);
};

class CTraceFilterIgnoreGrenades {
public:
	virtual bool ShouldHitEntity(IHandleEntity* pEntityHandle, int contentsMask) {
		if (!pEntityHandle) {
			return !(pEntityHandle == pSkip);
		}

		//return BaseShouldHitEntity( pSkip, ( IHandleEntity* ) pEntityHandle, m_icollisionGroup, contentsMask );

		ClientClass *clclass = ((CBaseEntity*)pEntityHandle)->GetClientClass();

		if (clclass) {
			if (strstr(clclass->m_pNetworkName, "CBaseCSGrenadeProjectile"))
				return false;

			//if ( clclass->m_ClassID == ClassID::_CBaseCSGrenadeProjectile )
			//	return false;
		}

		return !(pEntityHandle == pSkip);

		//return BaseShouldHitEntity( pSkip, ( IHandleEntity* ) pEntityHandle, m_icollisionGroup, contentsMask );
	}

	virtual TraceType_t    GetTraceType() const {
		return TRACE_EVERYTHING;
	}

	IHandleEntity* pSkip;
	int m_icollisionGroup;
};
class CGrenadePredictTraceFilter {
public:
	virtual bool ShouldHitEntity(IHandleEntity* pEntityHandle, int contentsMask) {
		if (!pEntityHandle)
			return !(pEntityHandle == pSkip);
		//return BaseShouldHitEntity( pSkip, ( IHandleEntity* ) pEntityHandle, m_icollisionGroup, contentsMask );


		//if (contentsMask & CONTENTS_WINDOW)
		//    return false;

		if (pEntityHandle == pSkip)
			return false;

		if (((CBaseEntity*)pEntityHandle)->IsPlayer())
			return false;

		ClientClass *clclass = ((CBaseEntity*)pEntityHandle)->GetClientClass();

		if (clclass) {
			if (strstr(clclass->m_pNetworkName, "CBaseCSGrenadeProjectile"))
				return false;

			//if ( ReadInt( ( uintptr_t ) &clclass->m_ClassID ) == ClassID::_CBaseCSGrenadeProjectile )
			//return false;
		}

		return !(pEntityHandle == pSkip);

		//return BaseShouldHitEntity( pSkip, ( IHandleEntity* ) pEntityHandle, m_icollisionGroup, contentsMask );
	}

	virtual TraceType_t    GetTraceType() const {
		return TRACE_EVERYTHING;
	}

	IHandleEntity* pSkip;
	int m_icollisionGroup;
};
