
#include "DamageESP.h"
#include "RenderD9.h"
namespace DamageESP
{
	std::array<FloatingText, MAX_FLOATING_TEXTS> floatingTexts;
	int floatingTextsIdx = 0;

	void HandleGameEvent(IGameEvent* pEvent)
	{
		if (!(Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected() && G::LocalPlayer))
			return;

		const char *name = pEvent->GetName();

		static Vector lastImpactPos = Vector(0, 0, 0);

		int winner = pEvent->GetInt(("winner"));
		int round_end = pEvent->GetInt(("round_end"));

		bool g_bRoundEnded = false;
		int g_iTEScore = 0;
		int g_iCTScore = 0;
		bool g_bBombPlanted = false;

		if (g_Options.Misc.EndRoundTalk)
		{

			if (strcmp(name, ("bomb_defused")) == NULL || strcmp(name, ("bomb_exploded")) == NULL || strcmp(name, ("round_end")) == NULL)
			{
				g_bRoundEnded = true;

				if (strcmp(name, ("round_end")) == NULL)
				{
					winner = pEvent->GetInt(("winner"));

					if (winner > 1 && winner < 4)
					{
						if (winner == 2)
							g_iTEScore++;

						else
							g_iCTScore++;
					};
				};



				if (strcmp(name, ("round_end")) == NULL && (rand() % (1 + 1 - 0)) + 0 == 0 && winner > 1 && winner < 4)
				{
					if (winner == G::LocalPlayer->GetTeam())
					{
						switch ((rand() % (g_Options.Misc.talk + 1 - 0)) + 0)
						{
						case 0: Interfaces.pEngine->ClientCmd_Unrestricted("say nS+", 0); break;
						case 1: Interfaces.pEngine->ClientCmd_Unrestricted("say very good round", 0); break;
						case 2: Interfaces.pEngine->ClientCmd_Unrestricted("say splendid round+", 0); break;
						case 3: Interfaces.pEngine->ClientCmd_Unrestricted("say good round+", 0); break;
						case 4: Interfaces.pEngine->ClientCmd_Unrestricted("say nice Round man", 0); break;
						case 5: Interfaces.pEngine->ClientCmd_Unrestricted("say amazing play+", 0); break;
						case 6: Interfaces.pEngine->ClientCmd_Unrestricted("say stronk team ❤", 0); break;
						case 7: Interfaces.pEngine->ClientCmd_Unrestricted("say nice teamplay :*", 0); break;
						case 8: Interfaces.pEngine->ClientCmd_Unrestricted("say hard play man+", 0); break;
						case 9: Interfaces.pEngine->ClientCmd_Unrestricted("say high skill team ❤", 0); break;
						};
					}

					else
					{
						switch ((rand() % (g_Options.Misc.talk + 1 - 0)) + 0)
						{
						case 0: Interfaces.pEngine->ClientCmd_Unrestricted("say i fuck all ur family", 0); break;
						case 1: Interfaces.pEngine->ClientCmd_Unrestricted("say u all 5 hack man?", 0); break;
						case 2: Interfaces.pEngine->ClientCmd_Unrestricted("say full hack pre-mates?", 0); break;
						case 3: Interfaces.pEngine->ClientCmd_Unrestricted("say why hack?", 0); break;
						case 4: Interfaces.pEngine->ClientCmd_Unrestricted("say go away guys..", 0); break;
						case 5: Interfaces.pEngine->ClientCmd_Unrestricted("say mby turn off pls?", 0); break;
						case 6: Interfaces.pEngine->ClientCmd_Unrestricted("say Reported all 5", 0); break;
						case 7: Interfaces.pEngine->ClientCmd_Unrestricted("say reportbotted all :*", 0); break;
						case 8: Interfaces.pEngine->ClientCmd_Unrestricted("say wait VAC guys!", 0); break;
						case 9: Interfaces.pEngine->ClientCmd_Unrestricted("say u will get OW np :@", 0); break;
						};
					};


				};



				g_bBombPlanted = false;
			}

			else if (strcmp(name, ("bomb_planted")) == NULL)
				g_bBombPlanted = true;

			else if (strcmp(name, ("round_start")) == NULL)
			{



				if ((rand() % (1 + 1 - 0)) + 0 == 0)
				{
					if ((g_iCTScore > g_iTEScore && G::LocalPlayer->GetTeam() == 3) || (g_iTEScore > g_iCTScore && G::LocalPlayer->GetTeam() == 2))
					{
						switch ((rand() % (g_Options.Misc.talk + 1 - 0)) + 0)
						{
						case 0: Interfaces.pEngine->ClientCmd_Unrestricted("say we still win+", 0); break;
						case 1: Interfaces.pEngine->ClientCmd_Unrestricted("say you will lose this game I promise+", 0); break;
						case 2: Interfaces.pEngine->ClientCmd_Unrestricted("say splendid game+", 0); break;
						case 3: Interfaces.pEngine->ClientCmd_Unrestricted("say so good team, definitely win", 0); break;
						case 4: Interfaces.pEngine->ClientCmd_Unrestricted("say no disguise we winning", 0); break;
						case 5: Interfaces.pEngine->ClientCmd_Unrestricted("say EZ game?", 0); break;
						case 6: Interfaces.pEngine->ClientCmd_Unrestricted("say we will win ❤", 0); break;
						case 7: Interfaces.pEngine->ClientCmd_Unrestricted("say so fkn EZ", 0); break;
						case 8: Interfaces.pEngine->ClientCmd_Unrestricted("say dont be mad guys, its only a game", 0); break;
						case 9: Interfaces.pEngine->ClientCmd_Unrestricted("say dont worry man we will win ❤", 0); break;
						case 10: Interfaces.pEngine->ClientCmd_Unrestricted("say drop me AWP ❤", 0); break;
						case 11: Interfaces.pEngine->ClientCmd_Unrestricted("say go eco 1", 0); break;
						case 12: Interfaces.pEngine->ClientCmd_Unrestricted("say man go eco 1 to hav money", 0); break;
						case 13: Interfaces.pEngine->ClientCmd_Unrestricted("say now i dont have money", 0); break;
						case 14: Interfaces.pEngine->ClientCmd_Unrestricted("say if we dont eco we cant win", 0); break;
						case 15: Interfaces.pEngine->ClientCmd_Unrestricted("say EZ+", 0); break;
						case 16: Interfaces.pEngine->ClientCmd_Unrestricted("say gg, we win it", 0); break;
						};


					}

					else if ((g_iTEScore > g_iCTScore && G::LocalPlayer->GetTeam() == 3) || (g_iCTScore > g_iTEScore && G::LocalPlayer->GetTeam() == 2))
					{
						switch ((rand() % (g_Options.Misc.talk + 1 - 0)) + 0)
						{
						case 0: Interfaces.pEngine->ClientCmd_Unrestricted("say i reported all 5", 0); break;
						case 1: Interfaces.pEngine->ClientCmd_Unrestricted("say please report first 2 for WH", 0); break;
						case 2: Interfaces.pEngine->ClientCmd_Unrestricted("say first 2 cheat for sure+", 0); break;
						case 3: Interfaces.pEngine->ClientCmd_Unrestricted("say kick your cheater pls", 0); break;
						case 4: Interfaces.pEngine->ClientCmd_Unrestricted("say u boosted cunts", 0); break;
						case 5: Interfaces.pEngine->ClientCmd_Unrestricted("say nice man, boosted by hacker+", 0); break;
						case 6: Interfaces.pEngine->ClientCmd_Unrestricted("say why we lose ?", 0); break;
						case 7: Interfaces.pEngine->ClientCmd_Unrestricted("say are we losing?", 0); break;
						case 8: Interfaces.pEngine->ClientCmd_Unrestricted("say guys, let's go win mby?", 0); break;
						case 9: Interfaces.pEngine->ClientCmd_Unrestricted("say we win or we lose?", 0); break;
						case 10: Interfaces.pEngine->ClientCmd_Unrestricted("say do we lose?", 0); break;
						case 11: Interfaces.pEngine->ClientCmd_Unrestricted("say guys, lets play?", 0); break;
						case 12: Interfaces.pEngine->ClientCmd_Unrestricted("say guys, pls focus on fkn game", 0); break;
						case 13: Interfaces.pEngine->ClientCmd_Unrestricted("say i dont have money now", 0); break;
						case 14: Interfaces.pEngine->ClientCmd_Unrestricted("say eco 1", 0); break;
						case 15: Interfaces.pEngine->ClientCmd_Unrestricted("say now i dont have money", 0); break;
						case 16: Interfaces.pEngine->ClientCmd_Unrestricted("say if we dont eco we cant win", 0); break;
						case 17: Interfaces.pEngine->ClientCmd_Unrestricted("say man go eco 1 to hav money", 0); break;
						case 18: Interfaces.pEngine->ClientCmd_Unrestricted("say man if u have $$ go drop to ur team", 0); break;
						case 19: Interfaces.pEngine->ClientCmd_Unrestricted("say man if u wanna win, go drop to ur team", 0); break;
						};


					};
				};
			}

		}
		
		if (g_Options.Misc.BuyBot && !strcmp(name, ("round_prestart"))) {

			//if (g_Options.Misc.item == 1) {
				Interfaces.pEngine->ClientCmd_Unrestricted("buy ak47", 0);
			//}

		}

		if (!strcmp(name, ("player_hurt")))
		{
			float curTime =  Interfaces.pGlobalVars->curtime;

			

			int userid = pEvent->GetInt(("userid"));
			int attackerid = pEvent->GetInt(("attacker"));
			int dmg_health = pEvent->GetInt(("dmg_health"));
			int hitgroup = pEvent->GetInt(("hitgroup"));
			

			CBaseEntity *entity = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetPlayerForUserID(userid));
			CBaseEntity *attacker = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetPlayerForUserID(attackerid));

			if (!entity || attacker != G::LocalPlayer)
				return;

			FloatingText txt;
			txt.startTime = curTime;
			txt.hitgroup = hitgroup;
			txt.hitPosition = lastImpactPos;
			txt.damage = dmg_health;
			txt.randomIdx = rand() % 5;
			txt.valid = true;

			floatingTexts[floatingTextsIdx++ % MAX_FLOATING_TEXTS] = txt;

			if (g_Options.Misc.TrashTalk && dmg_health > 99 && hitgroup == 1)
			{
				Interfaces.pEngine->ClientCmd_Unrestricted("say Tapped", 0);
			}

		}
		else if (!strcmp(name, ("bullet_impact")))
		{
			int userid = pEvent->GetInt(("userid"));
			float x = pEvent->GetFloat(("x"));
			float y = pEvent->GetFloat(("y"));
			float z = pEvent->GetFloat(("z"));

			CBaseEntity *entity = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetPlayerForUserID(userid));

			if (!entity || entity != G::LocalPlayer)
				return;

			lastImpactPos = Vector(x, y, z);
		}


		

	}



	void Draw()
	{
		if (!g_Options.Visuals.Visuals_DamageESP)
			return;

		
		for (int i = 0; i < MAX_FLOATING_TEXTS; i++)
		{
			FloatingText *txt = &floatingTexts[i % MAX_FLOATING_TEXTS];

			if (!txt->valid)
				continue;

			float endTime = txt->startTime + 1.1f;

			if (endTime < Interfaces.pGlobalVars->curtime)
			{
				txt->valid = false;
				continue;
			}

			Vector screen;

			if (render->WorldToScreen(txt->hitPosition, screen))
			{
				float t = 1.0f - (endTime - Interfaces.pGlobalVars->curtime) / (endTime - txt->startTime);

				screen.y -= t * (35.0f);
				screen.x -= (float)txt->randomIdx * t * 3.0f;

				char msg[12];
				sprintf_s(msg, 12, "-%dHP", txt->damage);

				int width = render->GetTextWitdh(msg, render->fntVerdana10);

				render->DrawStringWithFont(render->fntVerdana10, screen.x - width / 2, screen.y - 11 + 1, D3D_COLOR_BLACK((int)((1.0f - t) * (float)255)), msg);

				render->DrawStringWithFont(render->fntVerdana10, screen.x - width / 2, screen.y - 11, D3DCOLOR_ARGB(Hacks.Colors.DamageESP.a(), Hacks.Colors.DamageESP.r(), Hacks.Colors.DamageESP.g(), Hacks.Colors.DamageESP.b()), msg);
			}
		}
	}
};
