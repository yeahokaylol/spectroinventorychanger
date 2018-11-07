
#include "DamageESP.h"
#define RandomInt(min, max) (rand() % (max - min + 1) + min)
namespace DamageESP
{
	std::array<FloatingText, MAX_FLOATING_TEXTS> floatingTexts;
	int floatingTextsIdx = 0;

	void HandleGameEvent(IGameEvent* pEvent)
	{
		//if (!cfg.Visual.damageESP)
		//	return;

		const char *name = pEvent->GetName();

		static Vector lastImpactPos = Vector(0, 0, 0);

		if (strcmp(name, ("player_hurt")))
		{
			float curTime = Interfaces.pGlobalVars->curtime;

			int userid = pEvent->GetInt(("userid"));
			int attackerid = pEvent->GetInt(("attacker"));
			int dmg_health = pEvent->GetInt(("dmg_health"));
			int hitgroup = pEvent->GetInt(("hitgroup"));

			CBaseEntity *entity = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetPlayerForUserID(userid));
			CBaseEntity *attacker = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetPlayerForUserID(attackerid));

			if (!entity || attacker != Hacks.LocalPlayer)
				return;

			FloatingText txt;
			txt.startTime = curTime;
			txt.hitgroup = hitgroup;
			//txt.hitPosition = lastImpactPos;
			txt.damage = dmg_health;
			txt.randomIdx = RandomInt(-5, 5);
			txt.valid = true;

			floatingTexts[floatingTextsIdx++ % MAX_FLOATING_TEXTS] = txt;
		}
		else if (!strcmp(name, ("bullet_impact")))
		{
			int iUser = Interfaces.pEngine->GetPlayerForUserID(pEvent->GetInt("userid"));

			auto pPlayer = reinterpret_cast< CBaseEntity* >(Interfaces.pEntList->GetClientEntity(iUser));

			if (pPlayer)
			{

				if (iUser == Interfaces.pEngine->GetLocalPlayer())
				{

					if (!pPlayer->IsDormant())
					{

						float x, y, z;
						x = pEvent->GetFloat("x");
						y = pEvent->GetFloat("y");
						z = pEvent->GetFloat("z");
						FloatingText txt;
						txt.hitPosition = Vector(x, y, z);
					}
				}
			}

		}
		
	}

	void Draw()
	{

		float curTime = Interfaces.pGlobalVars->curtime;

		for (int i = 0; i < MAX_FLOATING_TEXTS; i++)
		{
			FloatingText *txt = &floatingTexts[i % MAX_FLOATING_TEXTS];

			if (!txt->valid)
				continue;

			float endTime = txt->startTime + 1.1f;

			if (endTime < curTime)
			{
				txt->valid = false;
				continue;
			}

			char msg[12];
			sprintf_s(msg, 12, "-%dHP", txt->damage);
			Interfaces.g_pDebugOverlay->AddTextOverlayRGB(txt->hitPosition,1,1.f,255,255,255,255, msg);

			/*if (WorldToScreen(txt->hitPosition, screen))
			{
				float t = 1.0f - (endTime - curTime) / (endTime - txt->startTime);

				screen.y -= t * (35.0f);
				screen.x -= (float)txt->randomIdx * t * 3.0f;

				char msg[12];
				sprintf_s(msg, 12, "-%dHP", txt->damage);

			//	int width = render->GetTextWitdh(msg, render->fntVerdana10);
				Interfaces.pSurface->DrawT(screen.x, screen.y - 11 + 1, CColor(255, 0, 0, 255), Hacks.Font_ESP, false, msg);
				Interfaces.pSurface->DrawT(screen.x, screen.y - 11, CColor(255, 255, 255, 255), Hacks.Font_ESP, false, msg);
			//	Interfaces.pSurface->DrawString(Hacks.Font_ESP, NewX + 45, NewY + 45, 0, CColor(255, 255, 255, 255), L"-%dHP", txt->damage);
			//	Interfaces.pSurface->DrawString(Hacks.Font_ESP, NewX + 45, NewY + 45, 0, CColor(255, 255, 255, 255), L"-%dHP", txt->damage);
			//	render->DrawStringWithFont(render->fntVerdana10, screen.x - width / 2, screen.y - 11 + 1, D3D_COLOR_BLACK((int)((1.0f - t) * (float)cfg.Visual.espAlpha + 55.0f)), msg);
			//	render->DrawStringWithFont(render->fntVerdana10, screen.x - width / 2, screen.y - 11, D3D_COLOR_GREEN(cfg.Visual.espAlpha + 55), msg);
			}*/
		}
	}
};
