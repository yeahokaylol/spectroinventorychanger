#include "stdafx.h"
#include "D9Visuals.h"
#include "DamageD9.h"
#include "LegitMath.h"




bool D9Visuals::canUseSetupBones = false;
int D9Visuals::PlayerAlpha[65];
int D9Visuals::PlayerNickVal[65];
float D9Visuals::PlayerBoxAlpha[65];
#define PlayerReadyAlpha(x) PlayerAlpha[x->GetIndex()]

FORCEINLINE float DotProductESP(const Vector& a, const Vector& b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}


wchar_t GetWeaponIcon(CBaseCombatWeapon *weapon);

bool D9Visuals::Filter(CBaseEntity *entity, bool& IsVis)
{
	if (!entity || !G::LocalPlayer) return true;
	if (!entity->isAlive()) return true; 
	if (entity->GetTeam() == G::LocalPlayer->GetTeam() && !g_Options.Visuals.Visuals_EspTeam) return true;
	if (entity->GetTeam() != 2 && entity->GetTeam() != 3) return true;

	IsVis = (entity->IsVisible(8) && !entity->IsDormant());
	if(g_Options.Visuals.Visuals_VisableOnly && !IsVis)return true;
	return false;
}
#define M_PI		3.14159265358979323846f

#define weapoid  *G::LocalPlayer->GetActiveBaseCombatWeapon()->GetItemDefinitionIndex()
void FovCrosshair()
{
	if (!G::LocalPlayer->isAlive())
		return;

	auto Gun = G::LocalPlayer->GetActiveBaseCombatWeapon();
	if (!Gun)
		return;
	

	if (!Gun->IsGun())
		return;

	if (!g_Options.NewLegitbot.Weapon[weapoid].Enabled)
		return;
	
	int ShootFired = G::LocalPlayer->GetActiveBaseCombatWeapon()->isPistol() ? g_Options.m_iBulletsFire : G::LocalPlayer->GetShootsField();

	//g_Options.m_iBulletsFire

	bool psile = (g_Options.NewLegitbot.Weapon[weapoid].pSilent && (ShootFired < 1)) ? true : false;



	float fov = psile ? g_Options.NewLegitbot.Weapon[weapoid].pSilentFov : g_Options.NewLegitbot.Weapon[weapoid].Fov;

	float radAimbotFov = (float)(fov * M_PI / 180.f);
	float radViewFov = (float)(Hacks.FOV * M_PI / 180.f);

	float circleRadius = tanf(radAimbotFov / 2) / tanf(radViewFov / 2) * (float)render->viewPort.Width;
	if (circleRadius != 0)
	{
		render->DrawCircleFast((float)render->viewPort.Width / 2.f, (float)render->viewPort.Height / 2.f, circleRadius, 50, psile ? D3DCOLOR_ARGB(255, 244, 0, 0) : D3DCOLOR_ARGB(255, 244, 244, 244));
	}

}

void AngleVectorsVis(const Vector &angles, Vector *forward)
{
	Assert(s_bMathlibInitialized);
	Assert(forward);

	float	sp, sy, cp, cy;

	sy = sin(DEG2RAD(angles[1]));
	cy = cos(DEG2RAD(angles[1]));

	sp = sin(DEG2RAD(angles[0]));
	cp = cos(DEG2RAD(angles[0]));

	forward->x = cp * cy;
	forward->y = cp * sy;
	forward->z = -sp;
}

void DrawLinesAA() {
	Vector src3D, dst3D, forward, src, dst;
	trace_t tr;
	Ray_t ray;
	CTraceFilter filter;

	filter.pSkip = G::LocalPlayer;

	DWORD LBYCOLOR = D3D_COLOR_BLUE(255);
	DWORD FAKECOLOR = D3D_COLOR_RED(255);
	DWORD REALCOLOR = D3D_COLOR_GREEN(255);

	// LBY
	AngleVectorsVis(Vector(0, Hacks.lineLBY, 0), &forward);
	src3D = G::LocalPlayer->GetVecOrigin();
	dst3D = src3D + (forward * 55.f); //replace 50 with the length you want the line to have

	ray.Init(src3D, dst3D);

	Interfaces.pTrace->TraceRay(ray, 0, &filter, &tr);

	if (!render->WorldToScreen(src3D, src) || !render->WorldToScreen(tr.endpos, dst))
		return;
	render->DrawLineFast(src.x, src.y, dst.x, dst.y, LBYCOLOR);
	// REAL AGNEL
	AngleVectorsVis(Vector(0, Hacks.lineRealAngle, 0), &forward);
	dst3D = src3D + (forward * 50.f); //replace 50 with the length you want the line to have

	ray.Init(src3D, dst3D);

	Interfaces.pTrace->TraceRay(ray, 0, &filter, &tr);

	if (!render->WorldToScreen(src3D, src) || !render->WorldToScreen(tr.endpos, dst))
		return;


	render->DrawLineFast(src.x, src.y, dst.x, dst.y, REALCOLOR);

	// Fake AGNEL
	AngleVectorsVis(Vector(0, Hacks.lineFakeAngle, 0), &forward);
	dst3D = src3D + (forward * 50.f); //replace 50 with the length you want the line to have

	ray.Init(src3D, dst3D);

	Interfaces.pTrace->TraceRay(ray, 0, &filter, &tr);

	if (!render->WorldToScreen(src3D, src) || !render->WorldToScreen(tr.endpos, dst))
		return;

	render->DrawLineFast(src.x, src.y, dst.x, dst.y, FAKECOLOR);
}

void SpreadCrosshair()
{
	

	if (g_Options.Visuals.Visuals_Spread && G::LocalPlayer && G::LocalPlayer->isAlive())
	{
		auto gun = G::LocalPlayer->GetActiveBaseCombatWeapon();
		if (gun)
		{
			if (g_Options.Visuals.Visuals_Spread_Type == 0)
			{

				float accuracy = gun->GetInaccuracy() * 550.f;

				if (accuracy > 0.f)
				{
					render->DrawCircleFast((float)render->viewPort.Width / 2.f, (float)render->viewPort.Height / 2.f, accuracy, 255, D3DCOLOR_ARGB(255, 244, 244, 244));
				}
			}
			if (g_Options.Visuals.Visuals_Spread_Type == 1)
			{

				float accuracy = gun->GetInaccuracy() * 550.f;

				if (accuracy > 0.f)
				{
					render->DrawFilledCircleFast((float)render->viewPort.Width / 2.f, (float)render->viewPort.Height / 2.f, accuracy, 255, D3DCOLOR_ARGB(140, 40, 40, 40));

				}
			}
		}
	}




}
void DrawSnapLine(Vector to, D3DCOLOR clr, int width, int height)
{
	Vector From((width / 2), height - 1, 0);
	render->DrawLineFast(From.x, From.y, to.x, to.y, clr);
}


void D9Visuals::Render()
{
	if (!Interfaces.pEngine->IsInGame() || !Interfaces.pEngine->IsConnected() || !G::LocalPlayer)
		return;
	

	if (g_Options.Visuals.Visuals_DrawLinesAA)
	{
		DrawLinesAA();
	}

	DrawCrossHair(6.5f, D3D_COLOR_BLACK(240));
	DrawCrossHair(4.5f, D3D_COLOR_WHITE(240));
	SpreadCrosshair();
	//hitMarkers->Draw();
	DamageESP::Draw();
	if (g_Options.NewLegitbot.Aimbot.DrawFOV) FovCrosshair();

	//OutOfViewIndicatorCircle();

	for (int i = 1; i < 65; i++)
	{
		auto entity = Interfaces.pEntList->GetClientEntity(i);
		bool Visable;
		if (!Filter(entity, Visable))
		{





			if (entity->IsDormant())
			{
				if (PlayerAlpha[i] != 0)
					PlayerAlpha[i] -= 1.5;

				if (PlayerBoxAlpha[i] != 0.f)
					PlayerBoxAlpha[i] -= 0.01f;

				if (PlayerNickVal[i] != 0)
					PlayerNickVal[i] -= 2;

			}
			else
			{
				if (PlayerAlpha[i] != 255)
					PlayerAlpha[i] += 5;

				if (PlayerBoxAlpha[i] != 1.f)
					PlayerBoxAlpha[i] += 0.05f;

				if (PlayerNickVal[i] != 100)
					PlayerNickVal[i] += 2;

			}
			if (PlayerBoxAlpha[i] < 0.f)
				PlayerBoxAlpha[i] = 0.f;
			if (PlayerBoxAlpha[i] > 1.f)
				PlayerBoxAlpha[i] = 1.f;
			if (PlayerAlpha[i] < 0)
				PlayerAlpha[i] = 0;
			if (PlayerAlpha[i] > 255)
				PlayerAlpha[i] = 255;
			if (PlayerNickVal[i] < 0)
				PlayerNickVal[i] = 0;
			if (PlayerNickVal[i] > 100)
				PlayerNickVal[i] = 100;

		
			int typecolor = entity->GetTeam() == 3 ? Visable ? 0 : 1 : Visable ? 2 : 3;
		
		
			if (g_Options.Visuals.Visuals_Name) DrawName(entity);
			DrawWeapon(entity);
			
			if (g_Options.Visuals.Visuals_BoxEnabled) DrawBox(entity, typecolor);
			if (g_Options.Visuals.Visuals_HealthBar) DrawHealth(entity);
			if (g_Options.Visuals.Visuals_Skeltal) DrawBoneESP(entity, typecolor);




		}
		

	}

	for (int i = 65; i < Interfaces.pEntList->GetHighestEntityIndex();i++)
	{
		auto pEntity = Interfaces.pEntList->GetClientEntity(i);
		if (!pEntity)
			continue;
		if (!G::LocalPlayer)
			continue;
		if (pEntity == G::LocalPlayer)
			continue;
		if (pEntity->IsDormant())
			continue;

		if (g_Options.Visuals.Visuals_C4 && strstr(pEntity->GetClientClass()->m_pNetworkName, "CPlantedC4"))
		{
			if (!pEntity->BombDefused())
			{
				float flTime = pEntity->BombTimer() - Interfaces.pGlobalVars->curtime;
				if (pEntity->BombTimer() - Interfaces.pGlobalVars->curtime > 0.f)
				{
					Vector vPos;
					if (render->WorldToScreen(pEntity->GetAbsOrigin(), vPos))
					{
						bool bCanDefuse = (G::LocalPlayer->HasKit() && flTime > 5.f) || flTime > 10.f;
						static char msg[32];
						sprintf_s(msg, 32, "C4 | %.2f", flTime);

						render->DrawStringWithFont(render->fntVerdana10, vPos.x, vPos.y, D3D_COLOR_BLACK(255), "%s", msg);
						render->DrawStringWithFont(render->fntVerdana10, vPos.x, vPos.y + 1, bCanDefuse ? D3D_COLOR_WHITE(255) : D3D_COLOR_ORANGE(255), "%s", msg);
					}
				}
			}
			else
			{
				Vector vPos;
				if (render->WorldToScreen(pEntity->GetAbsOrigin(), vPos))
				{
					static char msg[32];
					sprintf_s(msg, 32, "C4 | DEFUSED");
					render->DrawStringWithFont(render->fntVerdana10, vPos.x, vPos.y, D3D_COLOR_BLACK(255), "%s", msg);
					render->DrawStringWithFont(render->fntVerdana10, vPos.x, vPos.y + 1, D3D_COLOR_RED(255), "%s", msg);
				}
			}
		}
		if (g_Options.Visuals.Visuals_DroppedWeapons && pEntity->IsWeapon())
		{
			auto weapon = static_cast< CBaseCombatWeapon* >(pEntity);
			auto plr = Interfaces.pEntList->GetClientEntityFromHandle(weapon->GetOwnerHandle());
			Vector vOrig3D = pEntity->GetAbsOrigin(), vOrig;

			if (render->WorldToScreen(vOrig3D, vOrig))
			{
				player_info_t info;
				if (plr == nullptr || !plr->isAlive() || !(plr->GetHealth() > 0) || !(Interfaces.pEngine->GetPlayerInfo(plr->GetIndex(), &info)))
				{
					if (!(vOrig3D.y >= -5 && vOrig3D.y <= 5 && vOrig3D.x >= -5 && vOrig3D.x <= 5))
					{
						DWORD outlineColor = D3D_COLOR_BLACK(255);
						DWORD textColor = D3D_COLOR_WHITE(255);
						render->DrawStringWithFont(render->fntVerdana9, vOrig.x, vOrig.y + 1, outlineColor, "%s", (char*)weapon->GetWeaponName().c_str());
						render->DrawStringWithFont(render->fntVerdana9, vOrig.x, vOrig.y, textColor, "%s", (char*)weapon->GetWeaponName().c_str());
					}
				}
			}

		}



	}


	if (g_Options.Visuals.Visuals_GrenadePrediction)
	{
		if (GranadePrediction::pInstance->IsPredicted())
		{
			GranadePrediction::ShowPoint *points = GranadePrediction::pInstance->GetPoints();

			Vector screen[3];

			for (int i = 0; i < GranadePrediction::MAX_POINTS; i++)
			{
				if (!points[i].valid) return;

				if (render->WorldToScreen(points[i].start, screen[0]) && render->WorldToScreen(points[i].end, screen[1]))
				{
					render->DrawLineFast(screen[0].x, screen[0].y, screen[1].x, screen[1].y, D3D_COLOR_RED(255));
					//render->DrawLineFast(screen[0].x, screen[0].y + 2, screen[1].x, screen[1].y + 2, D3D_COLOR_DARKRED(cfg.Visual.espAlpha));
					//render->DrawLineFast(screen[0].x, screen[0].y - 2, screen[1].x, screen[1].y - 2, D3D_COLOR_DARKRED(cfg.Visual.espAlpha));

					if (points[i].plane)
					{
						render->DrawCircleFast(screen[0].x, screen[0].y, 3, 5, D3D_COLOR_PINK(255));

					}
				}
			}
		}
	}


}


void D9Visuals::PunchAnglesToScreen(int height, int width, int FOV, int *resultX, int *resultY)
{

	*resultX = width / 2;
	*resultY = height / 2;
	float dy = height / (float)FOV;
	float dx = width / (float)FOV;

	if (!g_Options.Visuals.Visuals_NoRecoil)
	{
		*resultX -= (int)(dx*(G::LocalPlayer->GetPunchAngle().y));
		*resultY += (int)(dy*(G::LocalPlayer->GetPunchAngle().x));
	}
}

void D9Visuals::DrawCrossHair(float size, D3DCOLOR color)
{
	if (!g_Options.Visuals.Visuals_Crosshair)
		return;

	int x, y;
	if (Hacks.FOV == 0)
		PunchAnglesToScreen(render->viewPort.Height, render->viewPort.Width, 90, &x, &y);
	else
		PunchAnglesToScreen(render->viewPort.Height, render->viewPort.Width, Hacks.FOV, &x, &y);

	render->DrawLineFast((float)(x - size / 2.f), (float)y, (float)(x + size / 2.f + 1.f), (float)y, color);
	render->DrawLineFast((float)x, (float)(y - size / 2.f), (float)x, (float)(y + size / 2.f + 1.f), color);
}




std::string SanitizeNameFST(char *name, int pEntity)
{
	name[127] = '\0';

	std::string tmp(name);

	for (size_t i = 0; i < tmp.length(); i++)
	{
		if ((
			tmp[i] >= 'a' && tmp[i] <= 'z' ||
			tmp[i] >= 'A' && tmp[i] <= 'Z' ||
			tmp[i] >= '0' && tmp[i] <= '9' ||
			tmp[i] == ' ' || tmp[i] == '.' || tmp[i] == '/' || tmp[i] == ':' ||
			tmp[i] == ',' || tmp[i] == '_' || tmp[i] == '#' || tmp[i] == '$' ||
			tmp[i] == '<' || tmp[i] == '>' || tmp[i] == '-' || tmp[i] == '+' ||
			tmp[i] == '*' || tmp[i] == '%' || tmp[i] == '@' || tmp[i] == '(' ||
			tmp[i] == ')' || tmp[i] == '{' || tmp[i] == '}' || tmp[i] == '[' || tmp[i] == ']' ||
			tmp[i] == '!' || tmp[i] == '&' || tmp[i] == '~' || tmp[i] == '^'
			) == false)
		{
			tmp[i] = '_';
		}
	}
	if (pEntity)
	{
		if (tmp.length() > (size_t)(20 * D9Visuals::PlayerNickVal[pEntity] / 100))
		{
			tmp.erase((20 * D9Visuals::PlayerNickVal[pEntity] / 100), (tmp.length() - (20 * D9Visuals::PlayerNickVal[pEntity] / 100)));
			tmp.append("...");
		}
	}
	else
	{
		if (tmp.length() > (20))
		{
			tmp.erase(20, (tmp.length() - 20));
			tmp.append("...");
		}
	}
	return tmp;
}

void D9Visuals::DrawName(CBaseEntity *entity)
{
	//	if (entity->IsDormant() && !CanShowDormant(entity) || entity == G::LocalPlayer)
	//		return;

	player_info_t info;
	Interfaces.pEngine->GetPlayerInfo(entity->GetIndex(), &info);
		

	float height, width, x, y;

	if (GetPlayerBox(entity, x, y, width, height))
	{
		//	int da = GetDormantAlpha(entity) + 55;
		float _x = x;
		float _y = y;

		auto outlineColor = D3D_COLOR_BLACK(PlayerReadyAlpha(entity));
		auto textColor = D3D_COLOR_WHITE(PlayerReadyAlpha(entity));

		std::string name = SanitizeNameFST(info.name, entity->GetIndex());

		_x += (width / 2.f) - render->GetTextWitdh((char*)name.c_str(), render->fntVerdana10) / 2.f;
		_y -= 8.f;
		render->DrawString(_x, _y - 3.f, outlineColor, "%s", (char*)name.c_str());
		render->DrawString(_x, _y - 2.f, textColor, "%s", (char*)name.c_str());

	}
}
void D9Visuals::DrawWeapon(CBaseEntity *entity)
{
	bool enemy = entity->GetTeam() != G::LocalPlayer->GetTeam() || g_Options.Visuals.Visuals_EspTeam;

	if (!enemy && !g_Options.Visuals.Visuals_EspTeam)
		return;


	CBaseCombatWeapon *w = entity->GetActiveBaseCombatWeapon();

	if (!w)
		return;



	float height, width, x, y;

	if (GetPlayerBox(entity, x, y, width, height))
	{
		//	int da = GetDormantAlpha(entity) + 55;
		float boxHeight = 5;
		float padd = 1;
		float _x = x;
		float _y = y;

		DWORD outlineColor = D3D_COLOR_BLACK(PlayerReadyAlpha(entity));
		DWORD textColor = D3D_COLOR_WHITE(PlayerReadyAlpha(entity));
		DWORD textColorScoped = D3D_COLOR_ORANGE(PlayerReadyAlpha(entity));
		DWORD textColorFaked = D3D_COLOR_GREEN(PlayerReadyAlpha(entity));
		DWORD textColorPENT = D3D_COLOR_RED(PlayerReadyAlpha(entity));
		DWORD textColorEmpty = D3D_COLOR_YELLOW(PlayerReadyAlpha(entity));
		DWORD textColorDefuser = D3D_COLOR_BLUE(PlayerReadyAlpha(entity));

		
		DWORD lineColor = D3D_COLOR_WHITE(PlayerReadyAlpha(entity));

	
	




	
			char ammo[20];
			sprintf_s(ammo, 20, "%d/%d", w->ammo());

		

			_x = x + width + padd;
			_y = y;
			if (g_Options.Visuals.Visuals_AimLines)
			{
				DrawSnapLine(Vector(x + (width / 2), y + height, 0), D3D_COLOR_RED(PlayerReadyAlpha(entity)), render->viewPort.Width, render->viewPort.Height);
			}

			if (g_Options.Visuals.Visuals_Weapons && g_Options.Visuals.Visuals_WeaponsType == 0)
			{
				render->DrawStringWithFont(render->fntVerdana9, _x, _y + 1, outlineColor, "%s", (char*)w->GetWeaponName().c_str());
				render->DrawStringWithFont(render->fntVerdana9, _x, _y, textColorEmpty, "%s", (char*)w->GetWeaponName().c_str());
				_y += 7.f;
			}

			if (w->ammo() >= 1 && !w->IsReloading() && g_Options.Visuals.Visuals_AmmoESP && g_Options.Visuals.Visuals_AmmoESPType == 0)
			{
				render->DrawStringWithFont(render->fntVerdana9, _x, _y + 1, outlineColor, "%s", ammo);
				render->DrawStringWithFont(render->fntVerdana9, _x, _y, textColor, "%s", ammo);
				_y += 7.f;
			}
			else if (g_Options.Visuals.Visuals_AmmoESP && !w->IsReloading() && g_Options.Visuals.Visuals_AmmoESPType == 0)
			{
				render->DrawStringWithFont(render->fntVerdana9, _x, _y + 1, outlineColor, "%s", ("EMPTY"));
				render->DrawStringWithFont(render->fntVerdana9, _x, _y, textColorEmpty, "%s", ("EMPTY"));
				_y += 7.f;
			}
			else if (g_Options.Visuals.Visuals_AmmoESP && w->IsReloading())
			{
				render->DrawStringWithFont(render->fntVerdana9, _x, _y + 1, outlineColor, "%s", ("RELOADING"));
				render->DrawStringWithFont(render->fntVerdana9, _x, _y, textColorScoped, "%s", ("RELOADING"));
				_y += 7.f;
			}

			if (entity->m_bIsScoped() && g_Options.Visuals.Visuals_Scoped)
			{
				render->DrawStringWithFont(render->fntVerdana9, _x, _y + 1, outlineColor, "%s", ("SCOPE"));
				render->DrawStringWithFont(render->fntVerdana9, _x, _y, textColorScoped, "%s", ("SCOPE"));
				_y += 7.f;
			}
			if (entity->IsFlashed() && g_Options.Visuals.Visuals_Flashed)
			{
				render->DrawStringWithFont(render->fntVerdana9, _x, _y + 1, outlineColor, "%s", ("FLASHED"));
				render->DrawStringWithFont(render->fntVerdana9, _x, _y, textColorScoped, "%s", ("FLASHED"));
				_y += 7.f;
			}
			if (entity->IsDefusing() && g_Options.Visuals.Visuals_Flashed)
			{
				render->DrawStringWithFont(render->fntVerdana9, _x, _y + 1, outlineColor, "%s", ("DEFUSING"));
				render->DrawStringWithFont(render->fntVerdana9, _x, _y, textColorDefuser, "%s", ("DEFUSING"));
				_y += 7.f;
			}

			
			if (g_Options.Visuals.Visuals_ArmorBar)
			{
				if (entity->GetArmor() > 0)
				{
					if (entity->HasHelmet())
					{
						render->DrawStringWithFont(render->fntVerdana9, _x, _y + 1, outlineColor, "%s", ("2 ARMOR"));
						render->DrawStringWithFont(render->fntVerdana9, _x, _y, textColorFaked, "%s", ("2 ARMOR"));
					}
					else
					{
						render->DrawStringWithFont(render->fntVerdana9, _x, _y + 1, outlineColor, "%s", ("1 ARMOR"));
						render->DrawStringWithFont(render->fntVerdana9, _x, _y, textColorFaked, "%s", ("1 ARMOR"));
					}
				}
				else
				{
					render->DrawStringWithFont(render->fntVerdana9, _x, _y + 1, outlineColor, "%s", ("NO ARMOR"));
					render->DrawStringWithFont(render->fntVerdana9, _x, _y, textColorFaked, "%s", ("NO ARMOR"));
				}
				_y += 7.f;
			}
			if (g_Options.Ragebot.Ragebot_AimbotEnabled && g_Options.Ragebot.Ragebot_Resolver)
			{

				if (Hacks.FakingLBY[entity->GetIndex()] == 1)
				{
					render->DrawStringWithFont(render->fntVerdana9, _x, _y + 1, outlineColor, "%s", ("FAKE"));
					render->DrawStringWithFont(render->fntVerdana9, _x, _y, textColorPENT, "%s", ("FAKE"));
					_y += 7.f;
				}
				else if (Hacks.FakingLBY[entity->GetIndex()] == 2)
				{
					render->DrawStringWithFont(render->fntVerdana9, _x, _y + 1, outlineColor, "%s", ("REAL"));
					render->DrawStringWithFont(render->fntVerdana9, _x, _y, textColorFaked, "%s", ("REAL"));
					_y += 7.f;
				}

				if (Hacks.fakewalking[entity->GetIndex()])
				{
					render->DrawStringWithFont(render->fntVerdana9, _x, _y + 1, outlineColor, "%s", ("FAKEWALKING"));
					render->DrawStringWithFont(render->fntVerdana9, _x, _y, textColorPENT, "%s", ("FAKEWALKING"));
					_y += 7.f;
				}

				std::string destinationstring;

				switch (Hacks.CurMode[entity->GetIndex()])
				{
				case ResolverModes::NONE:
					destinationstring = "NO RESOLVE";
					break;
				case ResolverModes::LBY:
					destinationstring = "LOWERBODY";
					break;
				case ResolverModes::LBY_BRUTE:
					destinationstring = ("LBY BRUTE");
					break;
				case ResolverModes::MOVING:
					destinationstring = "MOVING LBY";
					break;
				case ResolverModes::LBY_979BRUTE:
					destinationstring = "979 BRUTE";
					break;					
				case ResolverModes::LBY_FLICK:
					destinationstring = "LBY FLICK";
					break;
				case ResolverModes::LBY_DELTA120:
					destinationstring = "LBYDELTA120";
					break;
				case ResolverModes::BREKINGLBY:
					destinationstring = "BREAKING LBY";
					break;
				case ResolverModes::LASTSHAKELBY:
					destinationstring = "LAST SHAKE LBY";
					break;
					
				}

				render->DrawStringWithFont(render->fntVerdana9, _x, _y + 1.f, outlineColor, "%s", destinationstring.c_str());
				render->DrawStringWithFont(render->fntVerdana9, _x, _y, textColor, "%s", destinationstring.c_str());
				_y += 7.f;


			}
		
				

			
		int NewX = x;
		int NewY = y + height;

		if (g_Options.Visuals.Visuals_AmmoESP && g_Options.Visuals.Visuals_AmmoESPType == 1)
		{

			
			render->DrawFilledRectangle(NewX, NewY, 6, (width) * (PlayerReadyAlpha(entity) / 255), D3DCOLOR_ARGB(PlayerReadyAlpha(entity), 5, 5, 5));
			if (w->ammo() >= 1 && !w->IsReloading())
			{
				render->DrawFilledRectangle(NewX + 1, NewY + 1, 4, ((width - 2.f) * w->ammo() / w->BulletSize() ) * (PlayerReadyAlpha(entity) / 255), D3DCOLOR_ARGB(PlayerReadyAlpha(entity), 83, 140, 232));
			}
			else
			{
				render->DrawFilledRectangle(NewX + 1, NewY + 1, 4, (width - 2.f) * (PlayerReadyAlpha(entity) / 255), D3DCOLOR_ARGB(PlayerReadyAlpha(entity), 255, 165, 0));
			}


			NewY += 7;
		}

		if (g_Options.Visuals.Visuals_Weapons && g_Options.Visuals.Visuals_WeaponsType == 1)
		{
			wchar_t weapIcon[2] = { GetWeaponIcon(w), '\0' };

			_x = x + (width - render->GetTextWitdhW(weapIcon, render->fntWeaponIcon)) / 2;
			_y = y + height + 7;

			render->DrawStringWithFontW(render->fntWeaponIcon, _x, NewY + 1, outlineColor, L"%s", weapIcon);
			render->DrawStringWithFontW(render->fntWeaponIcon, _x, NewY, textColor, L"%s", weapIcon);
		}
		

		

	}
}
void D9Visuals::DrawHealth(CBaseEntity *entity)
{

	bool enemy = entity->GetTeam() != G::LocalPlayer->GetTeam() || g_Options.Visuals.Visuals_EspTeam;

	if (!enemy && !g_Options.Visuals.Visuals_EspTeam)
		return;

	float height, width, x, y;

	if (GetPlayerBox(entity, x, y, width, height))
	{
		//int da = GetDormantAlpha(entity) + 55;
		float boxWidth = 5;
		float padd = 1;
		float _x = x;
		float _y = y;



		DWORD outlineColor = D3D_COLOR_BLACK(PlayerReadyAlpha(entity) / 2);
		DWORD textColor = D3D_COLOR_WHITE(PlayerReadyAlpha(entity));

			static int OldHealth[65];
			static bool Animate[65];
			static float Curtime[65];
			int ID = entity->GetIndex();
			_x -= padd;

			float healthBarHeight = (entity->GetHealth() * height * PlayerBoxAlpha[entity->GetIndex()] / 100.0f);
			float healthBarHeight2 = (OldHealth[entity->GetIndex()] * height * PlayerBoxAlpha[entity->GetIndex()] / 100.0f);

			if (OldHealth[entity->GetIndex()] > 100)
			{
				healthBarHeight2 = (OldHealth[entity->GetIndex()] * height * PlayerBoxAlpha[entity->GetIndex()] / OldHealth[entity->GetIndex()]);
			}
			DWORD lineColor = D3DCOLOR_ARGB(PlayerReadyAlpha(entity), 153, min(255, OldHealth[entity->GetIndex()] * 225 / 100), 0);


			render->DrawFilledRectangle(_x - boxWidth, _y, height * PlayerBoxAlpha[entity->GetIndex()], boxWidth, outlineColor);
			//	render->DrawFilledRectangle(_x - boxWidth + 1, _y + (height - healthBarHeight) + 1, healthBarHeight - 2, boxWidth - 2, lineColor);
			render->DrawFilledRectangle(_x - boxWidth + 1, _y + (height * PlayerBoxAlpha[entity->GetIndex()] - healthBarHeight2) + 1, healthBarHeight2 - 2, boxWidth - 2, lineColor);

			if (g_Options.Visuals.Visuals_HealthBarType == 1)
			{
				for (int i = 1; i < 4; i++)
					render->DrawLineFast(_x - 1, _y + i * (height * PlayerBoxAlpha[entity->GetIndex()] / 4.0f), _x - boxWidth + 1, _y + i * (height * PlayerBoxAlpha[entity->GetIndex()] / 4.0f), outlineColor);
			}

			if (entity->GetHealth() < 100)
			{
				char health[6];
				sprintf_s(health, 6, "%d", OldHealth[entity->GetIndex()]);

				_x -= render->GetTextWitdh(health, render->fntVerdana9) - 4;
				_y = y + (height * PlayerBoxAlpha[entity->GetIndex()] - healthBarHeight2) + 1;

				render->DrawStringWithFont(render->fntVerdana9, _x, _y + 1, outlineColor, "%s", health);
				render->DrawStringWithFont(render->fntVerdana9, _x, _y, textColor, "%s", health);
			}


			if (OldHealth[ID] <= entity->GetHealth())
			{
				OldHealth[ID] = entity->GetHealth();
				Animate[ID] = false;
			}


			if (OldHealth[ID] > entity->GetHealth())
			{
				if (!Animate[ID])
				{
					Curtime[ID] = Interfaces.pGlobalVars->curtime;
					Animate[ID] = true;
				}
				do
				{
					OldHealth[ID] -= 0.07;

				} while (Curtime[ID] - Interfaces.pGlobalVars->curtime > 0.44f && Animate[ID]);
			}
	}
}


void D9Visuals::DrawBox(CBaseEntity *entity, int cType)
{
	if (entity == G::LocalPlayer)
		return;



	float height, width, x, y;


	if (GetPlayerBox(entity, x, y, width, height))
	{
		x += 1;
		y += 1;
		width -= 2;
		height -= 2;


		DWORD boxColor = D3D_COLOR_WHITE(PlayerReadyAlpha(entity));
		DWORD outlineColor = D3D_COLOR_BLACK(PlayerReadyAlpha(entity));

		switch (cType)
		{
		case 0:boxColor = D3DCOLOR_ARGB(PlayerReadyAlpha(entity), Hacks.Colors.CTBoxVisable.r(), Hacks.Colors.CTBoxVisable.g(), Hacks.Colors.CTBoxVisable.b()); break;
		case 1:boxColor = D3DCOLOR_ARGB(PlayerReadyAlpha(entity), Hacks.Colors.CTBoxInVisable.r(), Hacks.Colors.CTBoxInVisable.g(), Hacks.Colors.CTBoxInVisable.b()); break;
		case 2:boxColor = D3DCOLOR_ARGB(PlayerReadyAlpha(entity), Hacks.Colors.TBoxVisable.r(), Hacks.Colors.TBoxVisable.g(), Hacks.Colors.TBoxVisable.b()); break;
		case 3:boxColor = D3DCOLOR_ARGB(PlayerReadyAlpha(entity), Hacks.Colors.TBoxInVisable.r(), Hacks.Colors.TBoxInVisable.g(), Hacks.Colors.TBoxInVisable.b()); break;
		default:return; break;

		}

		if (g_Options.Visuals.Visuals_BoxEnabled)
		{

			int i = entity->GetIndex();
			render->DrawCornierBoxFastAlpha(x - 1, y - 1, height + 2, width + 2, outlineColor, PlayerBoxAlpha[i]);/*DrawBoxFastAlpha*/
			render->DrawCornierBoxFastAlpha(x, y, height, width, boxColor, PlayerBoxAlpha[i]);/*DrawBoxFastAlpha*/
			render->DrawCornierBoxFastAlpha(x + 1, y + 1, height - 2, width - 2, outlineColor, PlayerBoxAlpha[i]);/*DrawBoxFastAlpha*/
		}
	}
}

void D9Visuals::OutOfViewIndicatorCircle(CBaseEntity *entity)
{

	if (!g_Options.Visuals.OffscreenIndicator)
		return;


		
		auto pLocal = G::LocalPlayer;
		/*if (!entity || !pLocal)
			return;
		if (entity == pLocal)
			return;
		if (entity->IsDormant())
			return;
		if (entity->GetTeam() == pLocal->GetTeam())
			return;
		if (!entity->isAlive())
			return;*/

		if (entity == pLocal)
			return;

		Vector eyeangles, poopvec;
		int screen_w, screen_h;
		screen_w = render->viewPort.Width;
		screen_h = render->viewPort.Height;



		//Interfaces.pEngine->GetScreenSize(screen_w, screen_h);
		Interfaces.pEngine->GetViewAngles(eyeangles);
		QAngle newangle = LegitMath::CalcAngle(Vector(pLocal->GetAbsOrigin().x, pLocal->GetAbsOrigin().y, 0), Vector(entity->GetAbsOrigin().x, entity->GetAbsOrigin().y, 0));
		AngleVectorsVis(QAngle(0, 270, 0) - newangle + QAngle(0, eyeangles.y, 0), &poopvec);
		auto circlevec = Vector(screen_w / 2, screen_h / 2, 0) + (poopvec * 250.f);
		render->DrawFilledCircle1(Vector2D(circlevec.x, circlevec.y), CColor::Red(), 230, 30);

	

}



bool D9Visuals::GetPlayerBox(CBaseEntity *entity, float &x, float &y, float &width, float &height, Vector offset)
{
	Vector top, down, s[2];

	Vector adjust = Vector(0, 0, -16) * entity->GetDuckAmount3();

	down = entity->GetAbsOrigin()/*G::absOriginCache[entity->GetIndex()]*/ - Vector(0, 0, 1);//entity->GetRenderOrigin(); //entity->GetAbsOrigin();//entity->GetNetworkOrigin();
	top = down + Vector(0, 0, 72) + offset + adjust;

	if (render->WorldToScreen(top, s[1]) && render->WorldToScreen(down, s[0]))
	{
		Vector delta = s[1] - s[0];

		height = fabsf(delta.y);
		width = height / 2.0f;

		x = s[1].x - (width / 2);
		y = s[1].y;

		return true;
	}

	return false;
}


void D9Visuals::DrawBoneESP(CBaseEntity *entity, int cType)
{
	int id = entity->GetIndex();

	matrix3x4 pBoneToWorldOut[128];

	if (!entity->SetupBones(pBoneToWorldOut, 128, 0x100, Interfaces.pEngine->GetLastTimeStamp()))
		return;


	if (entity == G::LocalPlayer)
		return;



	DWORD color;

	switch (cType)
	{
	case 0:color = D3DCOLOR_ARGB((int)(PlayerReadyAlpha(entity)), Hacks.Colors.CTBoxVisable.r(), Hacks.Colors.CTBoxVisable.g(), Hacks.Colors.CTBoxVisable.b()); break;
	case 1:color = D3DCOLOR_ARGB((int)(PlayerReadyAlpha(entity)), Hacks.Colors.CTBoxInVisable.r(), Hacks.Colors.CTBoxInVisable.g(), Hacks.Colors.CTBoxInVisable.b()); break;
	case 2:color = D3DCOLOR_ARGB((int)(PlayerReadyAlpha(entity)), Hacks.Colors.TBoxVisable.r(), Hacks.Colors.TBoxVisable.g(), Hacks.Colors.TBoxVisable.b()); break;
	case 3:color = D3DCOLOR_ARGB((int)(PlayerReadyAlpha(entity)), Hacks.Colors.TBoxInVisable.r(), Hacks.Colors.TBoxInVisable.g(), Hacks.Colors.TBoxInVisable.b()); break;
	default: color = D3D_COLOR_RED((int)(PlayerReadyAlpha(entity))); break;

	}

	DrawBone(entity, pBoneToWorldOut, color);

}

void D9Visuals::DrawBone(CBaseEntity *entity, matrix3x4 *pBoneToWorldOut, D3DCOLOR color)
{
	studiohdr_t* pStudioModel = Interfaces.g_pModelInfo->GetStudioModel((model_t*)entity->GetModel());

	if (pStudioModel)
	{
		int num = 0;

		for (int i = 0; i < pStudioModel->numbones; i++)
		{
			mstudiobone_t* pBone = pStudioModel->GetBone(i);

			if (!pBone)
				continue;

			if (!(pBone->flags & 256) || pBone->parent == -1)
				continue;

			Vector vBonePos1;
			if (!render->WorldToScreen(Vector(pBoneToWorldOut[i][0][3], pBoneToWorldOut[i][1][3], pBoneToWorldOut[i][2][3]), vBonePos1))
				continue;

			Vector vBonePos2;
			if (!render->WorldToScreen(Vector(pBoneToWorldOut[pBone->parent][0][3], pBoneToWorldOut[pBone->parent][1][3], pBoneToWorldOut[pBone->parent][2][3]), vBonePos2))
				continue;



			//render->DrawLine((float)vBonePos1.x, (float)vBonePos1.y, (float)vBonePos2.x, (float)vBonePos2.y, 1.5f, true, color);
			render->DrawLineFast((float)vBonePos1.x, (float)vBonePos1.y, (float)vBonePos2.x, (float)vBonePos2.y, color);
		}
	}
}

// https://www.unknowncheats.me/forum/counterstrike-global-offensive/169881-csgo-matWeapon-icons-ttf-font.html
wchar_t GetWeaponIcon(CBaseCombatWeapon *weapon)
{
	int code = 0xE000 + max(0, min(WEAPON_KNIFE_PUSH, *weapon->GetItemDefinitionIndex()));

	return (wchar_t)(code);
}
