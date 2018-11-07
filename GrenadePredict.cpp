#include "GrenadePredict.h"
#include <numeric>
constexpr const float M_PI = 3.14159265358979323846f;
void inline SinCos(float radians, float *sine, float *cosine) {
	*sine = sin(radians);
	*cosine = cos(radians);
}
enum {
	PITCH = 0,	// up / down
	YAW,		// left / right
	ROLL		// fall over
};

void VectorAngles(const Vector& forward, Vector& angles) {
	if (forward.y == 0 && forward.x == 0) {
		angles.x = forward.z > 0.f ? 270.f : 90.f;
		angles.y = 0;
	}

	else {
		angles.x = (atan2(-forward.z, forward.Length2D()) * 180 / M_PI);
		if (angles.x < 0)
			angles.x += 360;

		angles.y = (atan2(forward.y, forward.x) * 180 / M_PI);
		if (angles.y < 0)
			angles.y += 360;
	}

	angles.z = 0;
}

bool ScreenTransform(const Vector& point, Vector& screen) {
	float w;
	const VMatrix& worldToScreen = Interfaces.pEngine->WorldToScreenMatrix();

	screen.x = worldToScreen[0][0] * point[0] + worldToScreen[0][1] * point[1] + worldToScreen[0][2] * point[2] + worldToScreen[0][3];
	screen.y = worldToScreen[1][0] * point[0] + worldToScreen[1][1] * point[1] + worldToScreen[1][2] * point[2] + worldToScreen[1][3];
	w = worldToScreen[3][0] * point[0] + worldToScreen[3][1] * point[1] + worldToScreen[3][2] * point[2] + worldToScreen[3][3];
	screen.z = 0.0f;

	bool behind = false;

	if (w < 0.001f) {
		behind = true;
		screen.x *= 100000;
		screen.y *= 100000;
	}
	else {
		behind = false;
		float invw = 1.0f / w;
		screen.x *= invw;
		screen.y *= invw;
	}

	return behind;
}
bool VisWorldToScreen(const Vector &origin, Vector &screen) {
	if (!ScreenTransform(origin, screen)) {
		int ScreenWidth, ScreenHeight;
		Interfaces.pEngine->GetScreenSize(ScreenWidth, ScreenHeight);
		float x = float(ScreenWidth) / 2;
		float y = (float)ScreenHeight / 2;
		x += 0.5f * screen.x * ScreenWidth + 0.5f;
		y -= 0.5f * screen.y * ScreenHeight + 0.5f;
		screen.x = x;
		screen.y = y;
		return true;
	}

	return false;
}

void AngleVectorZ(const Vector& angles, Vector& forward) {
	float sp, sy, cp, cy;

	SinCos(DEG2RAD(angles[YAW]), &sy, &cy);
	SinCos(DEG2RAD(angles[PITCH]), &sp, &cp);

	forward.x = cp*cy;
	forward.y = cp*sy;
	forward.z = -sp;
}
Vector CalcAngle(Vector src, Vector dst) {
	Vector angles;
	VectorAngles((dst - src), angles);
	angles.Normalize();
	return angles;
}
float DotProduct(Vector a, Vector b) {
	float one[] = { a.x, a.y, a.z };
	float two[] = { b.x, b.y, b.z };

	return std::inner_product(one, one + 3, two, 0.0f);
}

void AngleVectors(const Vector& angles, Vector* forward, Vector* right, Vector* up) {
	float sr, sp, sy, cr, cp, cy;

	SinCos(DEG2RAD(angles[YAW]), &sy, &cy);
	SinCos(DEG2RAD(angles[PITCH]), &sp, &cp);
	SinCos(DEG2RAD(angles[ROLL]), &sr, &cr);

	if (forward) {
		forward->x = cp*cy;
		forward->y = cp*sy;
		forward->z = -sp;
	}

	if (right) {
		right->x = (-1 * sr*sp*cy + -1 * cr*-sy);
		right->y = (-1 * sr*sp*sy + -1 * cr*cy);
		right->z = -1 * sr*cp;
	}

	if (up) {
		up->x = (cr*sp*cy + -sr*-sy);
		up->y = (cr*sp*sy + -sr*cy);
		up->z = cr*cp;
	}
}
enum acts {
	ACT_NONE = 0,
	ACT_THROW,
	ACT_LOB,
	ACT_DROP,
};

int GrenadeType = 0;
acts act = ACT_NONE;
std::vector <Vector>path;
static int LastSimulateTick = 0;

void CGrenadePrediction::Tick(int buttons) {
	bool in_attack = (buttons & IN_ATTACK);
	bool in_attack2 = (buttons & IN_ATTACK2);

	act = (in_attack && in_attack2) ? ACT_LOB :
		(in_attack2) ? ACT_DROP : ACT_THROW;
}

void CGrenadePrediction::PredictGrenade() {
	if (!Hacks.LocalPlayer)
		return;

	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)Hacks.LocalWeapon;

	if (!pWeapon)
		return;

	if (pWeapon->IsGrenade()) {
		GrenadeType = *pWeapon->GetItemDefinitionIndex();

		int tick = Interfaces.pGlobalVars->tickcount;

		if (LastSimulateTick != tick) {
			Simulate();
			LastSimulateTick = tick;
		}
	}
	else {
		GrenadeType = 0;
	}
}

inline float CSGO_Armor(float flDamage, int ArmorValue) {
	float flArmorRatio = 0.5f;
	float flArmorBonus = 0.5f;
	if (ArmorValue > 0) {
		float flNew = flDamage * flArmorRatio;
		float flArmor = (flDamage - flNew) * flArmorBonus;

		if (flArmor > static_cast< float >(ArmorValue)) {
			flArmor = static_cast< float >(ArmorValue) * (1.f / flArmorBonus);
			flNew = flDamage - flArmor;
		}

		flDamage = flNew;
	}
	return flDamage;
}

auto Draw3DBox = [](Vector Org, Vector vMin, Vector vMax, int r, int g, int b, int a)
{
	Vector _min = Org + vMin;
	Vector _max = Org + vMax;
	Vector min, max;

	Vector crnr2 = Vector(_max.x, _min.y, _min.z);
	Vector crnr3 = Vector(_max.x, _min.y, _max.z);
	Vector crnr4 = Vector(_min.x, _min.y, _max.z);
	Vector crnr5 = Vector(_min.x, _max.y, _max.z);
	Vector crnr6 = Vector(_min.x, _max.y, _min.z);
	Vector crnr7 = Vector(_max.x, _max.y, _min.z);
	Vector crnr2_;
	Vector crnr3_;
	Vector crnr4_;
	Vector crnr5_;
	Vector crnr6_;
	Vector crnr7_;

	if (WorldToScreen(_min, min) &&
		WorldToScreen(_max, max) &&
		WorldToScreen(crnr2, crnr2_) &&
		WorldToScreen(crnr3, crnr3_) &&
		WorldToScreen(crnr4, crnr4_) &&
		WorldToScreen(crnr5, crnr5_) &&
		WorldToScreen(crnr6, crnr6_) &&
		WorldToScreen(crnr7, crnr7_))
	{
		DrawLine(min.x, min.y, crnr2_.x, crnr2_.y, CColor(r, g, b, a));
		DrawLine(min.x, min.y, crnr4_.x, crnr4_.y, CColor(r, g, b, a));
		DrawLine(min.x, min.y, crnr6_.x, crnr6_.y, CColor(r, g, b, a));
		DrawLine(max.x, max.y, crnr5_.x, crnr5_.y, CColor(r, g, b, a));
		DrawLine(max.x, max.y, crnr7_.x, crnr7_.y, CColor(r, g, b, a));
		DrawLine(max.x, max.y, crnr3_.x, crnr3_.y, CColor(r, g, b, a));
		DrawLine(crnr2_.x, crnr2_.y, crnr7_.x, crnr7_.y, CColor(r, g, b, a));
		DrawLine(crnr2_.x, crnr2_.y, crnr3_.x, crnr3_.y, CColor(r, g, b, a));
		DrawLine(crnr4_.x, crnr4_.y, crnr5_.x, crnr5_.y, CColor(r, g, b, a));
		DrawLine(crnr4_.x, crnr4_.y, crnr3_.x, crnr3_.y, CColor(r, g, b, a));
		DrawLine(crnr6_.x, crnr6_.y, crnr5_.x, crnr5_.y, CColor(r, g, b, a));
		DrawLine(crnr6_.x, crnr6_.y, crnr7_.x, crnr7_.y, CColor(r, g, b, a));
	}
};

void CGrenadePrediction::PaintGrenadeTrajectory() {
	if (LastSimulateTick != 0 && LastSimulateTick == Interfaces.pGlobalVars->tickcount) {
		int size = path.size();

		if (GrenadeType && size > 1) {
			Vector screen1, screen2;
			Vector prev = path[0];

			Vector endpos = path[size - 1];
			Vector absendpos = endpos;

			float totaladded = 0.0f;

			while (totaladded < 30.0f) {
				if (Interfaces.pTrace->GetPointContents(endpos) == CONTENTS_EMPTY)
					break;

				totaladded += 2.0f;
				endpos.z += 2.0f;
			}

			//check if end pos has an enemy near it
			auto bestdmg = 0;
			static CColor redcol = { 255, 0, 0, 255 };
			static CColor greencol = { 0, 255, 0, 255 };
			static CColor yellowgreencol = { 177, 253, 2, 255 };
			static CColor yellowcol = { 255, 255, 0, 255 };
			static CColor orangecol = { 255, 128, 0, 255 };

			CColor *BestColor = &redcol;

			CBaseCombatWeapon* pWeapon = Hacks.LocalWeapon;

			if (pWeapon && *pWeapon->GetItemDefinitionIndex() == WEAPON_HEGRENADE) {
				for (int i = 1; i < 32; i++) {
					CBaseEntity *pEntity = Interfaces.pEntList->GetClientEntity(i);

					if (!pEntity)
						continue;

					//if ( G::Target && G::Target == pEntity )//pEntity->IsTarget )
					//{
					float dist = (pEntity->GetAbsOrigin() - endpos).Length();

					if (dist < 350.0f) {
						CTraceFilterIgnoreGrenades filter;
						filter.pSkip = (IHandleEntity*)Hacks.LocalPlayer;
						filter.m_icollisionGroup = 0;
						Ray_t ray;
						Vector NadeScreen;
						VisWorldToScreen(endpos, NadeScreen); //CAPPED

						Vector vPelvis = pEntity->GetBonePosition(3);
						ray.Init(endpos, vPelvis);
						trace_t ptr;
						Interfaces.pTrace->TraceRay(ray, MASK_SHOT, (ITraceFilter*)&filter, &ptr);

						if (ptr.m_pEnt == pEntity) {
							Vector PelvisScreen;

							VisWorldToScreen(vPelvis, PelvisScreen);

							static float a = 105.0f;
							static float b = 25.0f;
							static float c = 140.0f;

							float d = (((pEntity->GetAbsOrigin() - absendpos).Length() - b) / c);
							float flDamage = a*exp(-d * d);
							unsigned int LocalPlayerObserveTarget = Hacks.LocalPlayer->GetObserverTarget();
							auto dmg = max(static_cast<int>(ceilf(CSGO_Armor(flDamage, pEntity->GetArmor()))), 0);

							//int healthafterexplosion = (int)(max((int)pEntityToDrawHealth->GetHealth() - max((int)ceilf(CSGO_Armor(flDamage, pEntityToDrawHealth->GetArmor())), 0), 0));
							char dmgstr[128];
							sprintf_s(dmgstr, "-%i HP", dmg);

							CColor *destcolor = dmg <= 0 ? &redcol : dmg >= 40.0f ? &greencol : dmg >= 30.0f ? &yellowgreencol : dmg >= 20.0f ? &yellowcol : &orangecol;
							DrawLine(static_cast<int>(NadeScreen.x), static_cast<int>(NadeScreen.y), static_cast<int>(PelvisScreen.x), static_cast<int>(PelvisScreen.y), CColor(destcolor->r(), destcolor->g(), destcolor->b(), destcolor->a()));
							//Drawmanager->DrawLine(static_cast<int>(NadeScreen.x), static_cast<int>(NadeScreen.y), static_cast<int>(PelvisScreen.x), static_cast<int>(PelvisScreen.y), Color(destcolor->r(), destcolor->g(), destcolor->b(), destcolor->a()));
							//DrawStringUnencrypted( dmgstr, Vector2D( PelvisScreen.x, PelvisScreen.y - 25 ), *destcolor, pFont );

							Vector midpoint = (vPelvis + absendpos) * 0.5f;
							Vector midpointscreen;
							VisWorldToScreen(midpoint, midpointscreen); //CAPPED

							DrawString(Hacks.Font_ESP, static_cast<int>(midpointscreen.x), static_cast<int>(midpointscreen.y), *destcolor, FONT_CENTER, dmgstr);
						
							//Drawmanager->DrawText(*destcolor, static_cast<int>(midpointscreen.x + 20), static_cast<int>(midpointscreen.y - 20),  false, dmgstr);

							//Drawmanager->DrawString( D::Font::ESP, PelvisScreen.x, PelvisScreen.y - 25, *destcolor, false, dmgstr );

							/*

							sprintf_s( dmgstr, "%.1f", ( absendpos - vPelvis ).Length( ) );
							//DrawStringUnencrypted( dmgstr, Vector2D( midpointscreen.x, midpointscreen.y ), Color( 255, 255, 255, 255 ), pFontSmall );

							Drawmanager->DrawString( D::Font::ESP, midpointscreen.x, midpointscreen.y, Color( 255, 255, 255, 255 ), false, dmgstr );
							*/

							if (dmg > bestdmg) {
								BestColor = destcolor;
								bestdmg = dmg;
							}
						}
					}
				}
			}

			for (auto& cur : path) {
				if (VisWorldToScreen(prev, screen1) && VisWorldToScreen(cur, screen2)) //CAPPED
				{
					DrawLine(static_cast<int>(screen1.x), static_cast<int>(screen1.y), static_cast<int>(screen2.x), static_cast<int>(screen2.y), CColor(0, 125, 255, 255));
					//Drawmanager->DrawLine(static_cast<int>(screen1.x), static_cast<int>(screen1.y), static_cast<int>(screen2.x), static_cast<int>(screen2.y), Color(BestColor->r(), BestColor->g(), BestColor->b(), BestColor->a()));
				}

				prev = cur;
			}

			Draw3DBox(prev, Vector(-15, -15, -15), Vector(15, 15, 15), 255, 200, 25, 255);
		}
	}
}

void CGrenadePrediction::Setup(CBaseEntity* pl, Vector& vecSrc, Vector& vecThrow, const Vector& angEyeAngles) {
	Vector angThrow = angEyeAngles;
	float pitch = angThrow.x;

	if (angThrow.x <= 90.0f) {
		if (angThrow.x < -90.0f) {
			angThrow.x += 360.0f;
		}
	}
	else {
		angThrow.x -= 360.0f;
	}
	angThrow.x = angThrow.x - (90.0f - fabs(angThrow.x)) * 10.0f / 90.0f;

	// Gets ThrowVelocity from weapon files
	// Clamped to [15,750]
	float flVel = 750.0f * 0.9f;

	// Do magic on member of grenade object [esi+9E4h]
	// m1=1  m1+m2=0.5  m2=0
	static const float power[] = { 1.0f, 1.0f, 0.5f, 0.0f };
	float b = power[act];
	// Clamped to [0,1]
	b = b * 0.7f;
	b = b + 0.3f;
	flVel *= b;

	Vector vForward, vRight, vUp;
	AngleVectors(angThrow, &vForward, &vRight, &vUp);

	vecSrc = pl->GetEyePosition();
	float off = (power[act] * 12.0f) - 12.0f;
	vecSrc.z += off;

	// Game calls UTIL_TraceHull here with hull and assigns vecSrc tr.endpos
	trace_t tr;
	Vector vecDest = vecSrc;

	vecDest.MultAdd(vForward, 22.0f);

	CGrenadePredictTraceFilter filter;
	filter.pSkip = (IHandleEntity*)Hacks.LocalPlayer;
	filter.m_icollisionGroup = 0;
	HullTrace(vecSrc, vecDest, (ITraceFilter*)&filter, tr);

	// After the hull trace it moves 6 units back along vForward
	// vecSrc = tr.endpos - vForward * 6
	Vector vecBack = vForward; vecBack *= 6.0f;
	vecSrc = tr.endpos;
	vecSrc -= vecBack;

	// Finally calculate velocity
	vecThrow = pl->GetVecVelocity(); vecThrow *= 1.25f;
	vecThrow.MultAdd(vForward, flVel);
}

void CGrenadePrediction::Simulate() {
	Vector vecSrc, vecThrow;
	Vector eyeangs;
	Interfaces.pEngine->GetViewAngles(eyeangs);
	Setup(Hacks.LocalPlayer, vecSrc, vecThrow, eyeangs);

	float interval = Interfaces.pGlobalVars->interval_per_tick;

	// Log positions 20 times per sec
	int logstep = static_cast< int >(0.05f / interval);
	int logtimer = 0;

	path.clear();
	for (unsigned int i = 0; i < /*path.max_size( ) - 1*/1024; ++i) {
		if (!logtimer)
			path.push_back(vecSrc);

		int s = Step(vecSrc, vecThrow, i, interval);
		if ((s & 1)) break;

		// Reset the log timer every logstep OR we bounced
		if ((s & 2) || logtimer >= logstep) logtimer = 0;
		else ++logtimer;

		if (vecThrow == Vector())
			break;
	}
	path.push_back(vecSrc);
}
int CGrenadePrediction::Step(Vector& vecSrc, Vector& vecThrow, int tick, float interval) {
	// Apply gravity
	Vector move;
	AddGravityMove(move, vecThrow, interval, false);

	// Push entity
	trace_t tr;
	PushEntity(vecSrc, move, tr);

	int result = 0;
	// Check ending conditions
	if (CheckDetonate(vecThrow, tr, tick, interval) || tr.fraction == 0.0f) {
		result |= 1;
	}

	// Resolve collisions
	if (tr.fraction != 1.0f) {
		result |= 2; // Collision!
		ResolveFlyCollisionCustom(tr, vecThrow, interval);
	}

	// Set new position
	vecSrc = tr.endpos;

	return result;
}

bool CGrenadePrediction::CheckDetonate(const Vector& vecThrow, const trace_t& tr, int tick, float interval) {
	switch (GrenadeType) {
	case 44:
	case 43:
		// Pure timer based, detonate at 1.5s, checked every 0.2s
		return static_cast< float >(tick)*interval > 1.5f && !(tick%static_cast< int >(0.2f / interval));

	case 47:
	case 45:
		// Velocity must be <0.1, this is only checked every 0.2s
		if (vecThrow.Length() < 0.1f) {
			int det_tick_mod = static_cast< int >(0.2f / interval);
			return !(tick%det_tick_mod);
		}
		return false;

	case 48:
	case 46:
		// Detonate when hitting the floor
		if (tr.fraction != 1.0f && tr.plane.normal.z > 0.7f)
			return true;

		return static_cast< float >(tick)*interval > 2.35f && !(tick%static_cast< int >(0.05f / interval));

		// OR we've been flying for too long

	default:
		return false;
	}
}

void CGrenadePrediction::AddGravityMove(Vector& move, Vector& vel, float frametime, bool onground) {
	static ConVar *sv_gravity = Interfaces.g_ICVars->FindVar("sv_gravity");

	Vector basevel(0.0f, 0.0f, 0.0f);

	move.x = (vel.x + basevel.x) * frametime;
	move.y = (vel.y + basevel.y) * frametime;

	if (onground) {
		move.z = (vel.z + basevel.z) * frametime;
	}
	else {
		// Game calls GetActualGravity( this );
		float gravity = (sv_gravity ? sv_gravity->GetFloat() : 800.0f) * 0.4f;

		float newZ = vel.z - (gravity * frametime);
		move.z = ((vel.z + newZ) / 2.0f + basevel.z) * frametime;

		vel.z = newZ;
	}
}

void CGrenadePrediction::HullTrace(Vector src, Vector end, ITraceFilter* filter, trace_t& tr) {
	Ray_t ray;

	static const Vector mins(-2.0f, -2.0f, -2.0f);
	static const Vector maxs(2.0f, 2.0f, 2.0f);

	ray.Init(src, end, mins, maxs);

	Interfaces.pTrace->TraceRay(ray, 0x200400B, filter, &tr);
}

void CGrenadePrediction::PushEntity(Vector& src, const Vector& move, trace_t& tr) {
	Vector vecAbsEnd = src + move;

	// Trace through world
	CGrenadePredictTraceFilter filter;
	filter.pSkip = (IHandleEntity*)Hacks.LocalPlayer;
	filter.m_icollisionGroup = 0;

	HullTrace(src, vecAbsEnd, (ITraceFilter*)&filter, tr);
}

void CGrenadePrediction::ResolveFlyCollisionCustom(trace_t& tr, Vector& vecVelocity, float interval) {
	// Calculate elasticity
	float flSurfaceElasticity;

	//Don't bounce off of players with perfect elasticity
	if (tr.m_pEnt && tr.m_pEnt->IsPlayer()) {
		flSurfaceElasticity = 0.3f;
	}
	else {
		flSurfaceElasticity = 1.0f;
	}

	if (tr.contents & CONTENTS_WINDOW) {
		vecVelocity *= 0.65f;
		Vector dummy;
		trace_t exit;
		Vector newprev;
		if (path.size() > 1) {
			Vector cur = path[path.size() - 1];
			for (unsigned int i = path.size() - 2; i >= 0; i--) {
				newprev = path[i];
				if (newprev != cur && (newprev - cur).Length() > 0.01f) {
					break;
				}
			}
			Vector angle = CalcAngle(newprev, cur);
			if (angle != Vector(0.0f, 0.0f, 0.0f)) {
				Vector vDir;
				AngleVectorZ(angle, vDir);
				vDir.Normalize();
				//VectorNormalizeFast( vDir );
				float flDistance = 0;
				Vector end;

				while (flDistance <= 90.0f) {
					flDistance += 4.0f;

					end = tr.endpos + (vDir * flDistance);

					if ((Interfaces.pTrace->GetPointContents(end) & MASK_SOLID) == 0) {
						tr.endpos = end;
						break;
					}
				}
			}
		}
		return;
	}

	// ReadFloat((uintptr_t)&entersurf->physics.elasticity); //1.0;  // Assume all surfaces have the same elasticity
	float flGrenadeElasticity = 0.45f; // GetGrenadeElasticity()
	float flTotalElasticity = flGrenadeElasticity * flSurfaceElasticity;
	if (flTotalElasticity > 0.9f) flTotalElasticity = 0.9f;
	if (flTotalElasticity < 0.0f) flTotalElasticity = 0.0f;

	// Calculate bounce
	Vector vecAbsVelocity;
	PhysicsClipVelocity(vecVelocity, tr.plane.normal, vecAbsVelocity, 2.0f);
	vecAbsVelocity *= flTotalElasticity;

	float flSpeedSqr = DotProduct(vecVelocity, vecVelocity);

	if (tr.plane.normal.z > 0.7f) // Floor
	{
		// Verify that we have an entity.
		vecVelocity = vecAbsVelocity;
		if (flSpeedSqr < (20 * 20)) {
			vecAbsVelocity.Zero();
			vecVelocity = vecAbsVelocity;
		}
		else {
			vecAbsVelocity *= ((1.0f - tr.fraction) * interval);
			PushEntity(tr.endpos, vecAbsVelocity, tr);
		}
	}
	else {
		if (flSpeedSqr < (20 * 20)) {
			vecAbsVelocity.Zero();
			vecVelocity = vecAbsVelocity;
		}
		else {
			vecVelocity = vecAbsVelocity;
		}
	}

#if 0
	// Stop completely once we move too slow
	float flSpeedSqr = vecAbsVelocity.LengthSqr();
	static const float flMinSpeedSqr = 20.0f * 20.0f; // 30.0f * 30.0f in CSS
	if (flSpeedSqr < flMinSpeedSqr) {
		vecAbsVelocity.Zero();
	}

	// Stop if on ground
	if (tr.plane.normal.z > 0.7f) {
		vecVelocity = vecAbsVelocity;
		vecAbsVelocity *= ((1.0f - tr.fraction) * interval);
		PushEntity(tr.endpos, vecAbsVelocity, tr);
	}
	else {
		vecVelocity = vecAbsVelocity;
	}
#endif
}

unsigned char CGrenadePrediction::PhysicsClipVelocity(const Vector& in, const Vector& normal, Vector& out, float overbounce) {
	static const float STOP_EPSILON = 0.1f;

	float    backoff;
	float    change;
	float    angle;
	int        i;
	unsigned char blocked;

	blocked = 0;

	angle = normal[2];

	if (angle > 0) {
		blocked |= 1;        // floor
	}
	if (!angle) {
		blocked |= 2;        // step
	}

	backoff = in.Dot(normal) * overbounce;

	for (i = 0; i < 3; i++) {
		change = normal[i] * backoff;
		out[i] = in[i] - change;
		if (out[i] > -STOP_EPSILON && out[i] < STOP_EPSILON) {
			out[i] = 0;
		}
	}

	return blocked;
}
