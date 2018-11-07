#pragma once

#include "stdafx.h"
#include "Global.h"
#include "GrenadePrediction.h"

FORCEINLINE float DotProductGrenPred(const Vector& a, const Vector& b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

namespace GranadePrediction
{
	ShowPoint::ShowPoint(Vector start_, Vector end_, bool plane_, bool valid_, Vector normal_, bool detonate_)
	{
		start = start_;
		end = end_;
		valid = valid_;
		plane = plane_;
		normal = normal_;
		detonate = detonate_;
	}

	Predict::Predict()
	{
		for (int i = 0; i < MAX_POINTS; i++)
		{
			m_Points[i].valid = false;
		}

		m_bPredicted = false;
	}

	ShowPoint *Predict::GetPoints()
	{
		return m_Points;
	}

	bool Predict::IsPredicted()
	{
		return m_bPredicted;
	}

	void Predict::SetPredicted(bool value)
	{
		m_bPredicted = value;
	}

	bool CheckDetonate(CBaseCombatWeapon *weap, float speed, float timeAlive, trace_t &tr)
	{
		if (!weap)
			return true;

		switch (*weap->GetItemDefinitionIndex())
		{
		case WEAPON_FLASHBANG:
		case WEAPON_HEGRENADE:
			if (timeAlive > 2.5f)
				return true;
			break;

		case WEAPON_MOLOTOV:
		case WEAPON_INCGRENADE:
			if (tr.fraction != 1.0f && tr.plane.normal.z>0.7f || timeAlive > 3.5f)
				return true;
			break;

		case WEAPON_DECOY:
		case WEAPON_SMOKEGRENADE:
			if (speed < 0.1f)
				return true;

			break;
		}

		return false;
	}

	void Predict::PredictNade(CBaseEntity* m_pEntity)
	{
		auto AngleVectors = [](Vector q, Vector& vec)
		{
			auto SinCosAuto = [](float radians, float *sine, float *cosine)
			{
				*sine = sin(radians);
				*cosine = cos(radians);
			};

			float sp, sy, cp, cy;

			SinCosAuto(DEG2RAD(q[1]), &sy, &cy);
			SinCosAuto(DEG2RAD(q[0]), &sp, &cp);

			vec.x = cp * cy;
			vec.y = cp * sy;
			vec.z = -sp;
		};

		float GRENADE_COEFFICIENT_OF_RESTITUTION = 0.45f;
		if (!G::LocalPlayer)
			return;


		float fStep = Interfaces.pGlobalVars->interval_per_tick;
		float fGravity = Interfaces.g_ICVars->FindVar(("sv_gravity"))->GetFloat() / 8.0f;//800.0f / 8.f;

		Vector vPos, vThrow, vThrow2, vViewAngles;
		Vector vStart;


		if (m_pEntity == G::LocalPlayer)
			Interfaces.pEngine->GetViewAngles(vViewAngles);
		else
			return;

		vThrow = vViewAngles;

		if (vThrow[0] < 0)
			vThrow[0] = -10 + vThrow[0] * ((90 - 10) / 90.0f);
		else
			vThrow[0] = -10 + vThrow[0] * ((90 + 10) / 90.0f);

		/*float fVel = (90 - vThrow[0]) * 4;
		if (fVel > 500)
		fVel = 500;*/

		/*int  act = (in_attack && in_attack2) ? ACT_LOB :
		(in_attack2) ? ACT_DROP :
		(in_attack) ? ACT_THROW :
		ACT_NONE;*/

		int act = 1;

		if (Hacks.CurrentCmd->buttons & IN_ATTACK && Hacks.CurrentCmd->buttons & IN_ATTACK2)
			act = 2;
		else if (Hacks.CurrentCmd->buttons & IN_ATTACK2)
			act = 3;

		float flVel = 403.0f * 0.9f;

		// Do magic on member of grenade object [esi+9E4h]
		// m1=1  m1+m2=0.5  m2=0
		static const float power[] = { 1.0f, 1.0f, 0.5f, 0.0f };
		float b = power[act];
		// Clamped to [0,1]
		b = b * 0.7f;
		b = b + 0.3f;
		flVel *= b;

		AngleVectors(vThrow, vThrow2);

		Vector vEye = m_pEntity->GetEyePosition();
		vStart = vEye + vThrow2 * 16;

		vThrow2 = (vThrow2 * flVel) + m_pEntity->GetVecVelocity();	// casualhacker for da magic calc help

		int idx = 0;

		float timeAlive = 0.0f;
		float speed = 0;

		for (float fTime = 0.0f; idx < MAX_POINTS; fTime += fStep)
		{
			vPos = vStart + vThrow2 * fStep;

			Ray_t ray;
			trace_t trace;

			CTraceFilter filter;
			filter.pSkip = m_pEntity;

			ray.Init(vStart, vPos);
			Interfaces.pTrace->TraceRay(ray, MASK_SOLID, &filter, &trace);

			bool plane = false;

			if (trace.fraction != 1.0f)
			{
				plane = true;

				vThrow2 = trace.plane.normal * -2.0f * DotProductGrenPred(vThrow2, trace.plane.normal) + vThrow2;
				vThrow2 *= GRENADE_COEFFICIENT_OF_RESTITUTION;

				vPos = vStart + vThrow2 * trace.fraction * fStep;
				fTime += (fStep * (1 - trace.fraction));
			}

			bool detonate = CheckDetonate(G::LocalPlayer->GetActiveBaseCombatWeapon(), (vStart - vPos).Length() / fStep, fTime, trace);

			m_Points[idx] = ShowPoint(vStart, vPos, plane, true, trace.plane.normal, detonate);

			vStart = vPos;
			vThrow2.z -= fGravity * trace.fraction * fStep;

			idx++;

			if (detonate)
			{
				break;
			}
		}

		for (int i = idx; i < MAX_POINTS; i++)
		{
			m_Points[i].valid = false;
		}

		m_bPredicted = true;
	}

	Predict *pInstance = new Predict();
}
