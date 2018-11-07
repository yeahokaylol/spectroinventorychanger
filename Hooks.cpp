#pragma region INCLUDES
#include "stdafx.h"
#include "Tools/Hacks/Misc.h"
#include "Tools/Hacks/Esp.h"
#include "Tools/Hacks/Antiaim.h"
#include "Tools/Hacks/Aimbot.h"
#include "Tools/Hacks/CreateMoveETC.h"
#include "Tools/Hacks/KnifeBot.h"
#include "playsoundapi.h"
#include "NightMode.h"
#include "ResolverV2.h"
#include "SkinChanger-KentMeister.h"
#include "PredSys.h"
#include "LegitBot.h"
#include "BulletTracers.h"
#include "imgui\imgui.h"
#include "imgui\imgui_internal.h"
#include "imgui\dx9\imgui_dx9.h"
#include "NameSpace.h"
#include "LegitBackTracking.h"
#include "Chamz.h"
#include "DamageD9.h"
#include "RenderD9.h"
#include "C:\Users\Danutu\Desktop\Zeus - Fixed By Bugzy\calantag.h"
#include "Protobuf/Protobuffs.h"
#include <windows.h>
#include <Lmcons.h>
#include "Esp.h"
#pragma comment(lib, "Winmm.lib")
#pragma endregion
#pragma region DEFINES
#define DEV

#define PI_2 PI/2
#define PI_4 PI/4
#define MakePtr(cast, ptr, addValue) (cast)( (DWORD)(ptr) + (DWORD)(addValue))
#define TICKS_TO_TIME( t )		( Interfaces.pGlobalVars->interval_per_tick * ( t ) )

#define TICK_INTERVAL1			( Interfaces.pGlobalVars->interval_per_tick )
#define TIME_TO_TICKS( dt )		( (int)( 0.5f + (float)(dt) / TICK_INTERVAL1 ) )
#pragma endregion




#pragma region VMT
CHackManager Hacks;
typedef void(__stdcall *iFrameStageNotifyFn)(ClientFrameStage_t);
typedef void(__thiscall *iPaintTraverse)(void*, unsigned int, bool, bool);
typedef void(__thiscall *PlaySoundFn)(void*, const char*);
typedef void(__thiscall* IDrawModelExecute)(void*, void*, void*, const ModelRenderInfo_t&, matrix3x4*);
typedef void(__stdcall *iOverRideViewFn)(CViewSetup*);
typedef float(__stdcall *ViewModelViewFn)();
typedef bool(__thiscall *CreateMoveFn) (void*, float, CUserCmd*);
typedef bool(__thiscall* DoPostScreenSpaceEffectsFn)(void*, CViewSetup*);
typedef void(__thiscall *SceneEnd_t)(void *pEcx);
typedef bool(__thiscall *FireEventClientSide)(void*, IGameEvent*);
typedef void(__thiscall *BeginFrameFn)(void*);
typedef void(__thiscall* TraceRayFn)(void*, Ray_t const&, unsigned int, CTraceFilter*, trace_t&);
typedef void(__thiscall* EmitSoundFn)(IEngineSound*, IRecipientFilter&, int, int, const char*, unsigned int, const char*, float, float, int, int, int, const Vector*, const Vector*, CUtlVector<Vector>*, bool, int, int);



VMT *CLIENTVMT = nullptr;
VMT *PANELVMT = nullptr;
VMT *SURFACEVMT = nullptr;
VMT *DMEVMT = nullptr;
VMT *CLIENTMOVEVMT = nullptr;
VMT *GAMEEVENTVMT = nullptr;
VMT *STUDIORENDERVMT = nullptr;
VMT *EMITSOUNDVMT = nullptr;
vfunc_hook gc_hook;


#pragma endregion
#pragma region Staff
std::vector<const char*> smoke_materials = {
	//"effects/overlaysmoke",
	"particle/beam_smoke_01",
	"particle/particle_smokegrenade",
	"particle/particle_smokegrenade1",
	"particle/particle_smokegrenade2",
	"particle/particle_smokegrenade3",
	"particle/particle_smokegrenade_sc",
	"particle/smoke1/smoke1",
	"particle/smoke1/smoke1_ash",
	"particle/smoke1/smoke1_nearcull",
	"particle/smoke1/smoke1_nearcull2",
	"particle/smoke1/smoke1_snow",
	"particle/smokesprites_0001",
	"particle/smokestack",
	"particle/vistasmokev1/vistasmokev1",
	"particle/vistasmokev1/vistasmokev1_emods",
	"particle/vistasmokev1/vistasmokev1_emods_impactdust",
	"particle/vistasmokev1/vistasmokev1_fire",
	"particle/vistasmokev1/vistasmokev1_nearcull",
	"particle/vistasmokev1/vistasmokev1_nearcull_fog",
	"particle/vistasmokev1/vistasmokev1_nearcull_nodepth",
	"particle/vistasmokev1/vistasmokev1_smokegrenade",
	"particle/vistasmokev1/vistasmokev4_emods_nocull",
	"particle/vistasmokev1/vistasmokev4_nearcull",
	"particle/vistasmokev1/vistasmokev4_nocull"
};
#pragma endregion
#pragma region EventListener
typedef void(*Fucntion)(IGameEvent* event);


float hitmarkerAlpha = -1.f;

static void Hitmarker(int W, int H)
{
	if (hitmarkerAlpha < 0.f)
		hitmarkerAlpha = 0.f;
	else if (hitmarkerAlpha > 0.f)
		hitmarkerAlpha -= 0.01f;



	if (hitmarkerAlpha > 0.f)
	{
		DrawLine(W / 2 - 10, H / 2 - 10, W / 2 - 5, H / 2 - 5, CColor(240, 240, 240, (hitmarkerAlpha * 255.f)));
		DrawLine(W / 2 - 10, H / 2 + 10, W / 2 - 5, H / 2 + 5, CColor(240, 240, 240, (hitmarkerAlpha * 255.f)));
		DrawLine(W / 2 + 10, H / 2 - 10, W / 2 + 5, H / 2 - 5, CColor(240, 240, 240, (hitmarkerAlpha * 255.f)));
		DrawLine(W / 2 + 10, H / 2 + 10, W / 2 + 5, H / 2 + 5, CColor(240, 240, 240, (hitmarkerAlpha * 255.f)));

	}
}

EGCResult __fastcall hkGCRetrieveMessage(void* ecx, void*, uint32_t *punMsgType, void *pubDest, uint32_t cubDest, uint32_t *pcubMsgSize)
{
	static auto oGCRetrieveMessage = gc_hook.get_original<GCRetrieveMessage>(2);
	auto status = oGCRetrieveMessage(ecx, punMsgType, pubDest, cubDest, pcubMsgSize);

	if (status == k_EGCResultOK)
	{

		void* thisPtr = nullptr;
		__asm mov thisPtr, ebx;
		auto oldEBP = *reinterpret_cast<void**>((uint32_t)_AddressOfReturnAddress() - 4);

		uint32_t messageType = *punMsgType & 0x7FFFFFFF;
		Hacks.ProtoFeatures.ReceiveMessage(thisPtr, oldEBP, messageType, pubDest, cubDest, pcubMsgSize);
	}

	return status;
}

EGCResult __fastcall hkGCSendMessage(void* ecx, void*, uint32_t unMsgType, const void* pubData, uint32_t cubData)
{
	static auto oGCSendMessage = gc_hook.get_original<GCSendMessage>(0);

	EGCResult status;

	bool sendMessage = Hacks.ProtoFeatures.PreSendMessage(unMsgType, const_cast<void*>(pubData), cubData);

	if (!sendMessage)
		return k_EGCResultOK;

	return oGCSendMessage(ecx, unMsgType, const_cast<void*>(pubData), cubData);
}

void Hurt(IGameEvent* event)
{

	if (g_Options.Visuals.Visuals_Hitmarker || g_Options.Visuals.Visuals_DrawCapsules || (g_Options.Ragebot.Ragebot_Resolver && g_Options.Ragebot.Ragebot_AimbotEnabled))
	{
		if (Interfaces.pEngine->GetPlayerForUserID(event->GetInt("attacker")) == Interfaces.pEngine->GetLocalPlayer())
		{
			if (g_Options.Visuals.Visuals_Hitmarker)
			{
				hitmarkerAlpha = 1.f;
				Interfaces.pEngine->ClientCmd_Unrestricted("play buttons\\arena_switch_press_02.wav", 0);
			}
			if (g_Options.Visuals.Visuals_DrawCapsules)
			{
				CBaseEntity* hittedplayer = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetPlayerForUserID(event->GetInt("userid")));

				if (hittedplayer && hittedplayer->GetIndex() > 0 && hittedplayer->GetIndex() < 64 && hittedplayer->IsPlayer())
				{
					if (G::LocalPlayer && hittedplayer != G::LocalPlayer)
						Esp::CapsuleOverlay(hittedplayer, Hacks.Colors.LagCompHitboxes, g_Options.Visuals.Visuals_DrawCapsulesDuration);
				}
			}
			if ((g_Options.Ragebot.Ragebot_Resolver && g_Options.Ragebot.Ragebot_AimbotEnabled))
			{
				int id = Interfaces.pEngine->GetPlayerForUserID(event->GetInt("userid"));
				Resolver->pResolverData[id].playerhurtcalled = true;
			}
		}
	}
}
class CGameEventListener : public IGameEventListener2
{
private:
	std::string eventName;
	Fucntion Call;
	bool server;
public:
	CGameEventListener() : eventName(""), Call(nullptr), server(false)
	{
	}

	CGameEventListener(const std::string& gameEventName, const Fucntion Func, bool Server) : eventName(gameEventName), Call(Func), server(Server)
	{
		this->RegListener();
	}

	virtual void FireGameEvent(IGameEvent* event)
	{
		this->Call(event);
	}

	virtual int IndicateEventHandling(void)
	{
		return 0x2A;
	}

	void RegListener(void)
	{
		static bool first = true;
		if (!first)
			return;
		if (Interfaces.g_GameEventMgr->AddListener(this, this->eventName.c_str(), server))
			Hacks.listeners.push_back(this);
	}
};


#define REG_EVENT_LISTENER(p, e, n, s) p = new CGameEventListener(n, e, s)
CGameEventListener* Deaths;
CGameEventListener* BulletImpacts;
CGameEventListener* Hurts;

void BulletImpact(IGameEvent* event)
{

	int iUser = Interfaces.pEngine->GetPlayerForUserID(event->GetInt("userid"));

	if (iUser != Interfaces.pEngine->GetLocalPlayer())
		return;

	CBaseEntity* pPlayer = Interfaces.pEntList->GetClientEntity(iUser);

	if (!pPlayer)
		return;




	float x, y, z;
	x = event->GetFloat("x");
	y = event->GetFloat("y");
	z = event->GetFloat("z");

	BulletImpact_t impact(pPlayer, Vector(x, y, z), Interfaces.pGlobalVars->curtime, Color::Green());

	g_pBulletTracer->Impacts.push_back(impact);
}

void Init()
{
	char buffer[UNLEN + 1];
	DWORD size;
	size = sizeof(buffer);
	GetUserName(buffer, &size);
	char title[UNLEN];
	char ch1[50] = "echo [LORE-CHEATS.COM] Welcome Back ";
	char *ch = strcat(ch1, buffer);


	REG_EVENT_LISTENER(Hurts, &Hurt, "player_hurt", false);
	REG_EVENT_LISTENER(BulletImpacts, &BulletImpact, "bullet_impact", false);

	//static auto developer = Interfaces.g_ICVars->FindVar("developer");
	//developer->SetValue(1);

	Interfaces.pEngine->ClientCmd_Unrestricted("toggleconsole", 0);
	Interfaces.pEngine->ClientCmd_Unrestricted("clear", 0);
	Interfaces.pEngine->ClientCmd_Unrestricted(ch, 0);
	Interfaces.pEngine->ClientCmd_Unrestricted("echo [LORE-CHEATS.COM] Thanks for purchasing our software",0);
	Interfaces.pEngine->ClientCmd_Unrestricted("echo [LORE-CHEATS.COM] This cheat is a community project and will keep recieving updates as time goes", 0);
	Interfaces.pEngine->ClientCmd_Unrestricted("echo [LORE-CHEATS.COM] If you experience any issues, dm us on discord or use @admin to get our attention", 0);
	Interfaces.pEngine->ClientCmd_Unrestricted("echo [LORE-CHEATS.COM] Use the insert key to open the menu!", 0);
	Interfaces.pEngine->ClientCmd_Unrestricted("echo   ", 0);
	Interfaces.pEngine->ClientCmd_Unrestricted("echo  =======================================================================================================================================================  ", 0);
	Interfaces.pEngine->ClientCmd_Unrestricted("echo   ", 0);
	Interfaces.pEngine->ClientCmd_Unrestricted("echo Changelog:", 0);
	Interfaces.pEngine->ClientCmd_Unrestricted("echo + [SKINS] Inventory Changer", 0);
	Interfaces.pEngine->ClientCmd_Unrestricted("echo + [SKINS] Inventory Manager", 0);
	Interfaces.pEngine->ClientCmd_Unrestricted("echo + [RAGEBOT] New Improved Resolver", 0);
	Interfaces.pEngine->ClientCmd_Unrestricted("echo + [MISC] Buy Bot", 0);

}
#pragma endregion
#pragma region PaintTraverse
void __stdcall Hooked_PaintTraverse(unsigned int vguiPanel, bool forceRepaint, bool allowForce)
{
	//iPaintTraverse
	static iPaintTraverse oPaintTraverse = PANELVMT->GetOriginalMethod<iPaintTraverse>(41);
	CBaseEntity* local = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
	if (INIT::Exit)
	return oPaintTraverse(Interfaces.pPanel, vguiPanel, forceRepaint, allowForce);

	if (g_Options.Visuals.Visuals_NoScope && g_Options.Visuals.Enabled  && !strcmp("HudZoom", Interfaces.pPanel->GetName(vguiPanel)))
		return;

	
	oPaintTraverse(Interfaces.pPanel, vguiPanel, forceRepaint, allowForce);

	if (strcmp("FocusOverlayPanel", Interfaces.pPanel->GetName(vguiPanel)))
		return;

	
	
	static bool CanUpdate = true;
	static bool bLastSet = false;

	if (Interfaces.pEngine->IsConnected() && Interfaces.pEngine->IsInGame())
	{

		for (int i = 0; i < Interfaces.pEntList->GetHighestEntityIndex(); i++)
		{

			if (CanUpdate || bLastSet != g_Options.Visuals.Visuals_NoPostProcess)
			{
				bLastSet = g_Options.Visuals.Visuals_NoPostProcess;
				ConVar* mat_postprocess_enable = Interfaces.g_ICVars->FindVar("mat_postprocess_enable");
				mat_postprocess_enable->SetValue(!bLastSet);
				CanUpdate = false;

			}

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					G::viewMatrix[i][j] = Interfaces.pEngine->WorldToScreenMatrix()[i][j];
				}
			}
			static bool bSpoofed = false;
			if (!bSpoofed)
			{
				ConVar* sv_cheats = Interfaces.g_ICVars->FindVar("sv_cheats");
				SpoofedConvar* sv_cheats_spoofed = new SpoofedConvar(sv_cheats);
				sv_cheats_spoofed->SetInt(1);
				bSpoofed = true;
			}

			//if (g_Options.Visuals.Enabled)
			{
				DoAsusWalls();
				DoNightMode();

				
				CBaseEntity *entity = Interfaces.pEntList->GetClientEntity(i);
				player_info_t pinfo;

				if (entity == local && local->isAlive())//&& Interfaces.pEngine->GetPlayerInfo(Interfaces.pEngine->GetLocalPlayer(), &pinfo))
				{

					Vector max = entity->BBMax();//entity->GetCollideable()->OBBMaxs(); entity->BBMax()
					Vector pos, pos3D;
					Vector top, top3D;
					pos3D = entity->GetAbsOrigin();
					top3D = pos3D + Vector(0, 0, max.z);

					if (!render->WorldToScreen(pos3D, pos) || !render->WorldToScreen(top3D, top))
						return;

					float height = (pos.y - top.y);
					float width = height / 4.f;


					if (g_Options.Visuals.Visuals_BoxEnabled)
					{
						Interfaces.pSurface->DrawSetColor(255, 255, 255, 255);
						Interfaces.pSurface->DrawOutlinedRect(int(top.x - width), int(top.y), int(top.x + width), int(top.y + height));
						Interfaces.pSurface->DrawSetColor(0, 0, 0, 255);
						Interfaces.pSurface->DrawOutlinedRect(int(top.x - width - 1), int(top.y - 1), int(top.x + width + 1), int(top.y + height + 1));
						Interfaces.pSurface->DrawOutlinedRect(int(top.x - width + 1), int(top.y + 1), int(top.x + width - 1), int(top.y + height - 1));
					}


				}




				if (G::LocalPlayer)
				{


					Misc::DrawScope(render->viewPort.Width, render->viewPort.Height);
					//Esp::DoEsp();

					if (g_Options.Visuals.Visuals_Hitmarker)
						Hitmarker(render->viewPort.Width, render->viewPort.Height);

					Esp::CSoundESP::Get().Draw();


					if (G::LocalPlayer->isAlive())
					{
						if (g_Options.Visuals.lbyIndicator)
						{

							int offsetH = render->viewPort.Height - render->viewPort.Height / 30 - 27;

							Interfaces.pSurface->DrawT2(4, offsetH, Hacks.lbychoke ? CColor(255, 40, 40, 255) : CColor(40, 255, 40, 255), Hacks.hFntIndicators, false, "LBY");
						}

						if (g_Options.Visuals.strelkiIndicator)
						{

							bool right = Hacks.strelki > 0.f && Hacks.strelki < 175.f;
							bool levo = Hacks.strelki < 0.f && Hacks.strelki > -175.f;


							Interfaces.pSurface->DrawT2(render->viewPort.Width / 2 - 98, render->viewPort.Height / 2 - 15, levo ? CColor(40, 40, 40, 255) : CColor(54, 54, 54, 255), Hacks.hFntIndicators, false, "<");
							Interfaces.pSurface->DrawT2(render->viewPort.Width / 2 - 98, render->viewPort.Height / 2 - 15, levo ? CColor(54, 54, 54, 255) : CColor(Hacks.Colors.Stelki), Hacks.hFntIndicators, false, "<");

							Interfaces.pSurface->DrawT2(render->viewPort.Width / 2 + 82, render->viewPort.Height / 2 - 15, right ? CColor(40, 40, 40, 255) : CColor(54, 54, 54, 255), Hacks.hFntIndicators, false, ">");
							Interfaces.pSurface->DrawT2(render->viewPort.Width / 2 + 82, render->viewPort.Height / 2 - 15, right ? CColor(54, 54, 54, 255) : CColor(Hacks.Colors.Stelki), Hacks.hFntIndicators, false, ">");



						}
					}


				}
			}
			if (g_Options.Visuals.Visuals_DrawEventLog)
			{
				LogEvents::Draw();
			}
			else
			{
				CanUpdate = true;
				if (LogEvents::events.size())
				{
					LogEvents::events.clear();
				}
			}


			Interfaces.pPanel->SetMouseInputEnabled(vguiPanel, g_Options.Menu.Opened);

		}
	

	

	}

}
#pragma endregion
#pragma region OverrideView
void __stdcall Hooked_OverrideView(CViewSetup* pSetup)
{
	static iOverRideViewFn oOverrideView = CLIENTMOVEVMT->GetOriginalMethod<iOverRideViewFn>(18);

	if (Interfaces.pEngine->IsConnected() && Interfaces.pEngine->IsInGame() && G::LocalPlayer)
	{
		static ConVar* zoom_sensitivity_ratio_mouse = NULL;
		static float defaultSens = 1.0f;

		if (!zoom_sensitivity_ratio_mouse)
		{
			zoom_sensitivity_ratio_mouse = Interfaces.g_ICVars->FindVar(("zoom_sensitivity_ratio_mouse"));
			defaultSens = zoom_sensitivity_ratio_mouse->GetFloat();
		}


			if (!g_Options.Visuals.Visuals_NoZoom)
			{
				pSetup->fov += g_Options.Misc.Misc_Fov * 1.f;
			}
			else
			{
				pSetup->fov = 90.f + (g_Options.Misc.Misc_Fov * 1.f);
			}



		if (G::LocalPlayer && G::LocalPlayer->m_bIsScoped() && g_Options.Visuals.Visuals_NoZoom)
		{
			zoom_sensitivity_ratio_mouse->SetValue(2.0f);
		}
		else if (g_Options.Visuals.Visuals_NoZoom)
		{
			zoom_sensitivity_ratio_mouse->SetValue(defaultSens);
		}

	
		Hacks.FOV = pSetup->fov;



	}
	oOverrideView(pSetup);
}
#pragma endregion
#pragma region FrameStageHook
void __stdcall Hooked_Frame_Stage_Notify(ClientFrameStage_t curStage)
{
	static iFrameStageNotifyFn oFrameStageNotify = CLIENTVMT->GetOriginalMethod<iFrameStageNotifyFn>(37);
	
	
	if (!Interfaces.pEngine->IsInGame() || !Interfaces.pEngine->IsConnected())
	{
		G::LocalPlayer = nullptr;

		return oFrameStageNotify(curStage);
	}

	G::LocalPlayer = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());

	if (!G::LocalPlayer)
	{
		return oFrameStageNotify(curStage);
	}

	if (curStage == FRAME_NET_UPDATE_POSTDATAUPDATE_START && g_Options.Ragebot.Ragebot_AimbotEnabled)
	{
		if (g_Options.Ragebot.resolver)
			Resolver->Resolve();
		else
			Resolver->AntiAimResolver();
	}

	Vector* pPunchAngle = nullptr;
	Vector* pViewPunchAngle = nullptr;

	Vector vPunchAngle;
	Vector vViewPunchAngle;

	if (curStage == FRAME_RENDER_START)
	{
		if (*reinterpret_cast<bool*>(reinterpret_cast<DWORD>(Interfaces.pInput) + 0xA5))
		{
			Vector OutPut;
			switch (g_Options.Misc.Visuals_ThirdPersonAngle)
			{
			case 0:OutPut = Hacks.LastAngles; break;
			case 1:OutPut = Hacks.LastAnglesReal; break;
			case 2:OutPut = Vector(0, G::LocalPlayer->pelvisangs(), 0); break;
			default:OutPut = Hacks.LastAnglesReal; break;
			}
			*reinterpret_cast<Vector*>(reinterpret_cast<DWORD>(G::LocalPlayer) + 0x31C8) = OutPut;
		}
	}

	if (curStage == FRAME_NET_UPDATE_START)
	{
		for (int i = 1; i < 65; i++)
		{
			auto player = Interfaces.pEntList->GetClientEntity(i);

			if (!player)
				continue;

			if (player == G::LocalPlayer)
				continue;
			if (player->IsDormant())
				continue;
			if (player->GetTeam() == G::LocalPlayer->GetTeam())
				continue;

			VarMapping_t *map = player->VarMapping();
			if (map)
			{
				if (g_Options.Ragebot.LagComp)
				{
					map->m_nInterpolatedEntries = 0;
				}
				else
				{
					if (map->m_nInterpolatedEntries == 0)
						map->m_nInterpolatedEntries = 6;
				}
			}
		}
	}

	

	static bool enabledtp = true;
	static bool check = false;
	if (g_Options.Misc.Visuals_ThirdPersonKey > 0)
	{
		if (GetAsyncKeyState(g_Options.Misc.Visuals_ThirdPersonKey))
		{
			if (!check)
				enabledtp = !enabledtp;
			check = true;
		}
		else
			check = false;
	}


	if (curStage == FRAME_RENDER_START)
	{
		if (g_Options.Visuals.Visuals_NoRecoil)
		{
			pPunchAngle = G::LocalPlayer->GetPunchAnglePtr();
			pViewPunchAngle = G::LocalPlayer->GetViewPunchAnglePtr();
			vPunchAngle = *pPunchAngle;
			vViewPunchAngle = *pViewPunchAngle;

			*pPunchAngle = Vector(0, 0, 0);
			*pViewPunchAngle = Vector(0, 0, 0);
		}

		if (g_Options.Misc.Visuals_ThirdPerson && enabledtp && G::LocalPlayer->isAlive())
		{

			*(bool*)((DWORD)Interfaces.pInput + 0xA5) = true;
			*(float*)((DWORD)Interfaces.pInput + 0xA8 + 0x8) = g_Options.Misc.Visuals_ThirdPersonDistance;
		}
		else
		{
			*(bool*)((DWORD)Interfaces.pInput + 0xA5) = false;
			*(float*)((DWORD)Interfaces.pInput + 0xA8 + 0x8);
		}

		for (auto matName : smoke_materials)
		{
			IMaterial* mat = Interfaces.pMaterialSystem->FindMaterial(matName, "Other textures");
			mat->SetMaterialVarFlag(g_Options.Visuals.Visuals_NoSmokeVar && g_Options.Visuals.Visuals_NoSmoke ? MATERIAL_VAR_WIREFRAME : MATERIAL_VAR_NO_DRAW, g_Options.Visuals.Visuals_NoSmoke);
		}
		if (g_Options.Visuals.Visuals_NoSmoke) {
			static int* smokecount = *(int**)(Utils.FindPattern("client_panorama.dll", "A3 ? ? ? ? 57 8B CB") + 0x1);
			*smokecount = 0;
		}

		for (int i = 1; i < 65; i++)
		{
			if (i == Interfaces.pEngine->GetLocalPlayer())
				continue;

			auto pEntity = Interfaces.pEntList->GetClientEntity(i);
			if (!pEntity)
				continue;
			if (pEntity->IsDormant() || !pEntity->isAlive() || pEntity->HasGunGameImmunity())
				continue;

			*(int*)((DWORD)pEntity + 0xA30) = Interfaces.pGlobalVars->framecount; //we'll skip occlusion checks now
			*(int*)((DWORD)pEntity + 0xA28) = 0;//clear occlusion flags
		}
	}


	


		

	
	oFrameStageNotify(curStage);


	if (curStage == FRAME_NET_UPDATE_POSTDATAUPDATE_START)
	{
		if (g_Options.Skinchanger.EnabledChanger)
			g_Skinchanger->CreateMove();
	}

	if (pPunchAngle && pViewPunchAngle && g_Options.Visuals.Visuals_NoRecoil)
	{
		*pPunchAngle = vPunchAngle;
		*pViewPunchAngle = vViewPunchAngle;
	}	
}
#pragma endregion

#pragma region Chams
IMaterial* CreateMaterial(bool bShouldIgnoreZ, bool bShouldFlat)
{
	IMaterial* createdMaterial;

	if (bShouldIgnoreZ)
	{
		if (bShouldFlat)
			createdMaterial = Interfaces.pMaterialSystem->FindMaterial("chamsmat_flat_ignorez", "Model textures");
		else
			createdMaterial = Interfaces.pMaterialSystem->FindMaterial("chamsmat_ignorez", "Model textures");
	}
	else
	{
		if (bShouldFlat)
			createdMaterial = Interfaces.pMaterialSystem->FindMaterial("chamsmat_flat", "Model textures");
		else
			createdMaterial = Interfaces.pMaterialSystem->FindMaterial("chamsmat", "Model textures");
	}

	createdMaterial->IncrementReferenceCount();

	return createdMaterial;
}

void InitKeyValues(KeyValues* keyValues, char* name)
{
	using InitKeyValuesFn = void(__thiscall*)(void* thisptr, const char* name);
	reinterpret_cast<InitKeyValuesFn>(offsets.InitKeyValuesEx)(keyValues, name);
}

void LoadFromBuffer(KeyValues* pKeyValues, const char* resourceName, const char* pBuffer, void* pFileSystem = nullptr, const char* pPathID = NULL, void* pfnEvaluateSymbolProc = nullptr)
{
	using LoadFromBufferFn = void(__thiscall*)(void*, const char*, const char*, void*, const char*, void*);
	reinterpret_cast<LoadFromBufferFn>(offsets.LoadFromBufferEx)(pKeyValues, resourceName, pBuffer, pFileSystem, pPathID, pfnEvaluateSymbolProc);
}

IMaterial* Create_Material(bool Ignore, bool Lit, bool Wireframe)
{
	static int created = 0;
	static const char tmp[] =
	{
		"\"%s\"\
		\n{\
		\n\t\"$basetexture\" \"vgui/white_additive\"\
		\n\t\"$envmap\" \"\"\
		\n\t\"$ignorez\" \"%i\"\
		\n\t\"$model\" \"1\"\
		\n\t\"$flat\" \"1\"\
		\n\t\"$nocull\"  \"0\"\
		\n\t\"$selfillum\" \"1\"\
		\n\t\"$halflambert\" \"1\"\
		\n\t\"$nofog\"  \"0\"\
		\n\t\"$znearer\" \"0\"\
		\n\t\"$wireframe\" \"%i\"\
        \n}\n"
	};
	char* baseType = (Lit == true ? "VertexLitGeneric" : "UnlitGeneric");
	char material[512];
	char name[512];
	sprintf_s(material, sizeof(material), tmp, baseType, (Ignore) ? 1 : 0, (Wireframe) ? 1 : 0);
	sprintf_s(name, sizeof(name), "#Aimpulse_Chams_%i.vmt", created);
	++created;
	KeyValues* keyValues = static_cast< KeyValues* >(malloc(sizeof(KeyValues)));
	InitKeyValues(keyValues, baseType);
	LoadFromBuffer(keyValues, name, material);
	IMaterial* createdMaterial = Interfaces.pMaterialSystem->CreateMaterial(name, keyValues);
	createdMaterial->IncrementReferenceCount();
	return createdMaterial;
}

bool Do_Chams(void* thisptr, int edx, void* ctx, void* state, const ModelRenderInfo_t& pInfo, matrix3x4* pCustomBoneToWorld, IDrawModelExecute oDrawModelExecuteEX)
{

	static IMaterial* Covered_Lit = Create_Material(true, true, false);
	static IMaterial* Visable_Lit = Create_Material(false, true, false);
	static IMaterial* Covered_Flat = Create_Material(true, false, false);
	static IMaterial* Visable_Flat = Create_Material(true, false, false);
	static IMaterial* GlassChams = Interfaces.pMaterialSystem->FindMaterial(("models/inventory_items/cologne_prediction/cologne_prediction_glass"), (TEXTURE_GROUP_OTHER));
	static IMaterial* GoldChams = Interfaces.pMaterialSystem->FindMaterial(("models/inventory_items/trophy_majors/gold"), (TEXTURE_GROUP_OTHER));
	static IMaterial* mp3_detail = Interfaces.pMaterialSystem->FindMaterial(("models/inventory_items/dogtags/dogtags_outline"), (TEXTURE_GROUP_OTHER));

	
	if (!(Interfaces.pEngine->IsConnected() && Interfaces.pEngine->IsInGame()) || INIT::Exit)
		return false;

	if(!G::LocalPlayer)
		return false;
	float ChamsRed = Hacks.Colors.CTChamsVisable.r();
	float ChamsGreen = Hacks.Colors.CTChamsVisable.g();
	float ChamsBlue = Hacks.Colors.CTChamsVisable.b();
	float ChamsRedT = Hacks.Colors.TChamsVisable.r();
	float ChamsGreenT = Hacks.Colors.TChamsVisable.g();
	float ChamsBlueT = Hacks.Colors.TChamsVisable.b();

	float ChamsRedIN = Hacks.Colors.CTChamsInVisable.r();
	float ChamsGreenIN = Hacks.Colors.CTChamsInVisable.g();
	float ChamsBlueIN = Hacks.Colors.CTChamsInVisable.b();
	float ChamsRedTIN = Hacks.Colors.TChamsInVisable.r();
	float ChamsGreenTIN = Hacks.Colors.TChamsInVisable.g();
	float ChamsBlueTIN = Hacks.Colors.TChamsInVisable.b();

	CBaseEntity* Model_Entity = Interfaces.pEntList->GetClientEntity(pInfo.entity_index);
	if (g_Options.Visuals.Visuals_Chams && Model_Entity->IsPlayer())
	{
		if (Model_Entity->GetTeam() == G::LocalPlayer->GetTeam() && !g_Options.Visuals.Visuals_ChamsTeam)
			return false;

		if (!Model_Entity->isAlive())
			return false;

		switch (g_Options.Visuals.Visuals_ChamsMaterial)
		{
		case 0:
		{


				if (Model_Entity->GetTeam() == 2)
				{
					Covered_Flat->ColorModulate(ChamsRedTIN / 255.f, ChamsGreenTIN / 255.f, ChamsBlueTIN / 255.f); // t colour
					Visable_Flat->ColorModulate(ChamsRedT / 255.f, ChamsGreenT / 255.f, ChamsBlueT / 255.f); // t colour Visable
				}
				else
				{
					Covered_Flat->ColorModulate(ChamsRedIN / 255.f, ChamsGreenIN / 255.f, ChamsBlueIN / 255.f); // ct colour
					Visable_Flat->ColorModulate(ChamsRed / 255.f, ChamsGreen / 255.f, ChamsBlue / 255.f); // ct colour Visable
				}


				if (Model_Entity->HasGunGameImmunity())
					Covered_Flat->AlphaModulate(0.75f);
				else
					Covered_Flat->AlphaModulate(1.0f);



				if (!g_Options.Visuals.Visuals_ChamsXQZ)
				{
					Interfaces.g_pModelRender->ForcedMaterialOverride(Covered_Flat, OVERRIDE_NORMAL);
					oDrawModelExecuteEX(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
				}

				Interfaces.g_pModelRender->ForcedMaterialOverride(Visable_Flat, OVERRIDE_NORMAL);
				oDrawModelExecuteEX(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

				return true;
			
		}break;
		case 1:
		{

				

				if (Model_Entity->GetTeam() == 2)
				{
					Covered_Lit->ColorModulate(ChamsRedTIN / 255.f, ChamsGreenTIN / 255.f, ChamsBlueTIN / 255.f); // t colour
					Visable_Lit->ColorModulate(ChamsRedT / 255.f, ChamsGreenT / 255.f, ChamsBlueT / 255.f); // t colour Visable
				}
				else
				{
					Covered_Lit->ColorModulate(ChamsRedIN / 255.f, ChamsGreenIN / 255.f, ChamsBlueIN / 255.f); // ct colour
					Visable_Lit->ColorModulate(ChamsRed / 255.f, ChamsGreen / 255.f, ChamsBlue / 255.f); // ct colour Visable
				}

			

				if (Model_Entity->HasGunGameImmunity())
					Covered_Lit->AlphaModulate(0.75f);
				else
					Covered_Lit->AlphaModulate(1.0f);



				if (!g_Options.Visuals.Visuals_ChamsXQZ)
				{
					Interfaces.g_pModelRender->ForcedMaterialOverride(Covered_Lit, OVERRIDE_NORMAL);
					oDrawModelExecuteEX(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
				}

				Interfaces.g_pModelRender->ForcedMaterialOverride(Visable_Lit, OVERRIDE_NORMAL);
				oDrawModelExecuteEX(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

				return true;
			
		}break;
		case 2:
		{

			
				if (Model_Entity->GetTeam() == 2)
				{
					GoldChams->ColorModulate(ChamsRedTIN / 255.f, ChamsGreenTIN / 255.f, ChamsBlueTIN / 255.f); // t colour
				}
				else
				{
					GoldChams->ColorModulate(ChamsRedIN / 255.f, ChamsGreenIN / 255.f, ChamsBlueIN / 255.f); // ct colour		
				}

			

				if (Model_Entity->HasGunGameImmunity())
					GoldChams->AlphaModulate(0.75f);
				else
					GoldChams->AlphaModulate(1.0f);

				GoldChams->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, !g_Options.Visuals.Visuals_ChamsXQZ);
				Interfaces.g_pModelRender->ForcedMaterialOverride(GoldChams, OVERRIDE_NORMAL);
				oDrawModelExecuteEX(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

				return true;
			
		}break;
		case 3:
		{

				if (Model_Entity->GetTeam() == 2)
				{
					Covered_Lit->ColorModulate(ChamsRedTIN / 255.f, ChamsGreenTIN / 255.f, ChamsBlueTIN / 255.f); // t colour
					
				}
				else
				{
					Covered_Lit->ColorModulate(ChamsRedIN / 255.f, ChamsGreenIN / 255.f, ChamsBlueIN / 255.f); // ct colour
				}

				if (!g_Options.Visuals.Visuals_ChamsXQZ)
				{
					Interfaces.g_pModelRender->ForcedMaterialOverride(Covered_Lit, OVERRIDE_NORMAL);
					oDrawModelExecuteEX(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
				}

				Interfaces.g_pModelRender->ForcedMaterialOverride(NULL, OVERRIDE_NORMAL);
				if (Model_Entity->GetTeam() == 2)
				{
					Interfaces.g_pRenderView->SetColorModulation(Hacks.Colors.TChamsVisable.Base());
				}
				else
				{
					Interfaces.g_pRenderView->SetColorModulation(Hacks.Colors.CTChamsVisable.Base());
				}
				oDrawModelExecuteEX(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
				return true;
			
		}break;
		case 4:
		{

				
				mp3_detail->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, !g_Options.Visuals.Visuals_ChamsXQZ);
				Interfaces.g_pModelRender->ForcedMaterialOverride(mp3_detail, OVERRIDE_NORMAL);
				oDrawModelExecuteEX(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

				return true;
			
		}break;
		case 5:
		{



			GlassChams->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, !g_Options.Visuals.Visuals_ChamsXQZ);
			Interfaces.g_pModelRender->ForcedMaterialOverride(GlassChams, OVERRIDE_NORMAL);
			oDrawModelExecuteEX(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
			return true;

		}break;

		default:break;
		}
	}
	if (Model_Entity->IsWeapon() && g_Options.Visuals.Visuals_ChamsGuns)
	{
			Covered_Lit->ColorModulate(0 / 255.f, 237 / 255.f, 255 / 255.f);
			Visable_Lit->ColorModulate(0 / 255.f, 200 / 255.f, 255 / 255.f);
			Visable_Lit->AlphaModulate(1.0f);
			Covered_Lit->AlphaModulate(1.0f);

			if (!g_Options.Visuals.Visuals_ChamsXQZ)
			{
				Interfaces.g_pModelRender->ForcedMaterialOverride(Covered_Lit, OVERRIDE_NORMAL);
				oDrawModelExecuteEX(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
			}

			Interfaces.g_pModelRender->ForcedMaterialOverride(Visable_Lit, OVERRIDE_NORMAL);
			oDrawModelExecuteEX(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

			return true;
	}
	if (g_Options.Visuals.Visuals_NoFlash)
	{
		IMaterial* Flash = Interfaces.pMaterialSystem->FindMaterial("effects\\flashbang", "ClientEffect textures");
		IMaterial* FlashWhite = Interfaces.pMaterialSystem->FindMaterial("effects\\flashbang_white", "ClientEffect textures");
		Flash->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
		FlashWhite->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
		
	}
	return false;
}




void __fastcall Hooked_DrawModelExecute(void* thisptr, int edx, void* ctx, void* state, const ModelRenderInfo_t& pInfo, matrix3x4* pCustomBoneToWorld)
{

	static IDrawModelExecute oDrawModelExecute = DMEVMT->GetOriginalMethod<IDrawModelExecute>(21);


	if(!Do_Chams(thisptr, edx, ctx, state, pInfo, pCustomBoneToWorld, oDrawModelExecute))
	oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

	Interfaces.g_pModelRender->ForcedMaterialOverride(nullptr, OVERRIDE_NORMAL);
}
#pragma endregion
#pragma region WNDPROC
extern LRESULT ImGui_ImplDX9_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void OpenMenu()
{
	static bool bDown = false;
	static bool bClicked = false;
	static bool bPrevMenuState = g_Options.Menu.Opened;
	ConVar* men = Interfaces.g_ICVars->FindVar("cl_mouseenable");
	if (G::pressedKeys[VK_INSERT])
	{
		bClicked = false;
		bDown = true;
	}
	else if (!G::pressedKeys[VK_INSERT] && bDown)
	{
		bClicked = true;
		bDown = false;
	}
	else
	{
		bClicked = false;
		bDown = false;
	}

	if (bClicked)
	{
		g_Options.Menu.Opened = !g_Options.Menu.Opened;
		men->SetValue(g_Options.Menu.Opened);
	}

	if (bPrevMenuState != g_Options.Menu.Opened)
	{
		men->SetValue(!g_Options.Menu.Opened);
		std::string msg = "cl_mouseenable " + std::to_string(!g_Options.Menu.Opened);
		//Interfaces.pEngine->ClientCmd_Unrestricted(msg.c_str(), 0);
		/*if (!g_Options.Menu.Opened == false)
		{
			Interfaces.pEngine->ClientCmd_Unrestricted("cl_mouseenable 0", 0);
			Interfaces.g_pInputSystem->EnableInput(false);
		}
		else
		{
			Interfaces.pEngine->ClientCmd_Unrestricted("cl_mouseenable 1", 0);
			Interfaces.g_pInputSystem->EnableInput(true);
		}*/
	}
	bPrevMenuState = g_Options.Menu.Opened;

}

LRESULT __stdcall Hooked_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	/*if (m_pMenu && m_pMenu->MainWindow && m_pMenu->MainWindow->visible)
	return true;

	OpenMenu();

	if (G::d3dinit && g_Options.Menu.Opened && ImGui_ImplDX9_WndProcHandler(hWnd, uMsg, wParam, lParam))
	return true;

	return CallWindowProc(Hooks::g_pOldWindowProc, hWnd, uMsg, wParam, lParam);*/
	if (INIT::Exit) return CallWindowProc(INIT::OldWindow, hWnd, uMsg, wParam, lParam);

	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
		G::pressedKeys[VK_LBUTTON] = true;
		break;
	case WM_LBUTTONUP:
		G::pressedKeys[VK_LBUTTON] = false;
		break;
	case WM_RBUTTONDOWN:
		G::pressedKeys[VK_RBUTTON] = true;
		break;
	case WM_RBUTTONUP:
		G::pressedKeys[VK_RBUTTON] = false;
		break;
	case WM_MBUTTONDOWN:
		G::pressedKeys[VK_MBUTTON] = true;
		break;
	case WM_MBUTTONUP:
		G::pressedKeys[VK_MBUTTON] = false;
		break;
	case WM_XBUTTONDOWN:
	{
		UINT button = GET_XBUTTON_WPARAM(wParam);
		if (button == XBUTTON1)
		{
			G::pressedKeys[VK_XBUTTON1] = true;
		}
		else if (button == XBUTTON2)
		{
			G::pressedKeys[VK_XBUTTON2] = true;
		}
		break;
	}
	case WM_XBUTTONUP:
	{
		UINT button = GET_XBUTTON_WPARAM(wParam);
		if (button == XBUTTON1)
		{
			G::pressedKeys[VK_XBUTTON1] = false;
		}
		else if (button == XBUTTON2)
		{
			G::pressedKeys[VK_XBUTTON2] = false;
		}
		break;
	}
	case WM_KEYDOWN:
		G::pressedKeys[wParam] = true;
		break;
	case WM_KEYUP:
		G::pressedKeys[wParam] = false;
		break;
	default: break;
	}

	OpenMenu();


	if (G::d3dinit && g_Options.Menu.Opened && ImGui_ImplDX9_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;
	return CallWindowProc(INIT::OldWindow, hWnd, uMsg, wParam, lParam);
}
#pragma endregion
#pragma region ViewModel
float __stdcall Hooked_ViewModelView()
{
	static ViewModelViewFn oViewModelView = CLIENTMOVEVMT->GetOriginalMethod<ViewModelViewFn>(35);
	float result = oViewModelView();
	return g_Options.Misc.ViewModelFov;
}
#pragma endregion
#pragma region FireEventClientSide
bool __fastcall Hooked_FireEventClientSide(void *ecx, void* edx, IGameEvent* pEvent) {

	static FireEventClientSide pGameEvent = GAMEEVENTVMT->GetOriginalMethod<FireEventClientSide>(9);

	if (!pEvent || INIT::Exit)
		return pGameEvent(ecx, pEvent);

	if (!strcmp(pEvent->GetName(), "game_newmap")) {
		g_Skinchanger->UpdateModels();
	}

	LogEvents::FireGameEvent(pEvent);
	DamageESP::HandleGameEvent(pEvent);
	if (g_Options.NewLegitbot.Aimbot.bKillDelay && g_Options.NewLegitbot.Aimbot.Enabled)
	{
	
		if (strcmp(pEvent->GetName(), "player_death") == 0)
		{
			int attacker = Interfaces.pEngine->GetPlayerForUserID(pEvent->GetInt("attacker"));
			int iLocalPlayer = Interfaces.pEngine->GetLocalPlayer();
			if (attacker == iLocalPlayer)
			{
					G::KillStopDelay = Interfaces.pGlobalVars->curtime + g_Options.NewLegitbot.Aimbot.iKillDelay;
			}
		}
	}


	return pGameEvent(ecx, pEvent);
}
#pragma endregion
#pragma region GlowESP
class CGlowObjectManagerR
{
public:
	class GlowObject_tT
	{
	public:
		void Set(CColor color)
		{
			int r, g, b, a;
			color.GetColor(r, g, b, a);
			vecGlowColor = Vector(r / 255.f, g / 255.f, b / 255.f);
			flGlowAlpha = a / 255.f;
			bRenderWhenOccluded = true;
			bRenderWhenUnoccluded = false;
			flBloomAmount = 1.f;
		}

		CBaseEntity* GetEntity() { return pEntity; }
		bool IsEmpty() const { return nNextFreeSlot != -2; }

	public:
		CBaseEntity*		pEntity;
		Vector				vecGlowColor;
		float				flGlowAlpha;

		char				pad0[4];
		float				flUnknown;
		float				flBloomAmount;
		float				flLocalPlayerIsZeroPoint;

		bool				bRenderWhenOccluded;
		bool				bRenderWhenUnoccluded;
		bool				bFullBloomRender;
		char				pad1[1];

		int					nFullBloomStencilTestValue;
		int					iUnk;
		int					nSplitScreenSlot;
		int					nNextFreeSlot;

	};

	GlowObject_tT* GlowObjectDefinitions;
	int		max_size;
	int		pad;
	int		size;
	GlowObject_tT* GlowObjectDefinitions2;
	int		currentObjects;
};

bool __fastcall Hooked_DoPostScreenSpaceEffects(void* thisptr, int edx, CViewSetup* pSetup)
{

	static DoPostScreenSpaceEffectsFn oDoPostScreenSpaceEffects = CLIENTMOVEVMT->GetOriginalMethod<DoPostScreenSpaceEffectsFn>(44);

	if (!(Interfaces.pEngine->IsConnected() && Interfaces.pEngine->IsInGame() && G::LocalPlayer && g_Options.Visuals.Vis_Glow && !INIT::Exit))
		return oDoPostScreenSpaceEffects(thisptr, pSetup);


		CGlowObjectManagerR* GlowObjectManager = (CGlowObjectManagerR*)offsets.GlowManager;

		
		for (int i = 0; i < GlowObjectManager->size; ++i)
		{
			CGlowObjectManagerR::GlowObject_tT* hGlowObject = &GlowObjectManager->GlowObjectDefinitions[i];
			CBaseEntity* pEntity = hGlowObject->pEntity;

			if (hGlowObject->IsEmpty() || !pEntity)
				continue;




			ClientClass* cClass = (ClientClass*)pEntity->GetClientClass();

			if (cClass->m_ClassID == 35)
			{
				if (pEntity->GetTeam() == G::LocalPlayer->GetTeam() && !g_Options.Visuals.Vis_Glow_Team)
					continue;
				if (pEntity == G::LocalPlayer && g_Options.Visuals.Visuals_GhostAngle)
					continue;

				bool IsVisible = pEntity->IsVisible(6);

				if(!IsVisible && g_Options.Visuals.Vis_Glow_Vis)
					continue;

				if (IsVisible)
				{
					if (pEntity->GetTeam() == 3)
					{
						hGlowObject->Set(Hacks.Colors.CTGlowVisable);
					}
					else
					{
						hGlowObject->Set(Hacks.Colors.TGlowVisable);
					}
				}
				else
				{
					if (pEntity->GetTeam() == 3)
					{
						hGlowObject->Set(Hacks.Colors.CTGlowInVisable);
					}
					else
					{
						hGlowObject->Set(Hacks.Colors.TGlowInVisable);
					}
				}

			}
			
		}
	
	return oDoPostScreenSpaceEffects(thisptr, pSetup);
}
#pragma endregion
#pragma region CreateMove
bool FakeLag()
{

	auto RandomFloatFSF = [](float a, float b)
	{
		float random = ((float)rand()) / (float)RAND_MAX;
		float diff = b - a;
		float r = random * diff;
		return a + r;
	};

	//hardcore
	int Type = g_Options.Misc.FakeLag.Misc_FakeLag;

	static int ticks = 0;
	const int ticksMax = 14; //16

	static bool new_factor = false;

	static int packetsToChoke = 1;

	if (Type == 1)
	{
		packetsToChoke = g_Options.Misc.FakeLag.Misc_FakeLagFactor;
	}
	else if (Type == 2)
	{
		float z_velocity = G::LocalPlayer->GetVecVelocity().z * 5.5f; //5.5 is the peak
		if (z_velocity < 0)
			z_velocity *= -1;



		packetsToChoke = z_velocity;
		if (packetsToChoke == 0)
			packetsToChoke += 3;
	}
	else if (Type == 3)
	{
		packetsToChoke = max(1, min((int)(fabs(G::LocalPlayer->GetVecVelocity().Length() / 80.f)), 5));
	}
	else if (Type == 4 && new_factor)
	{
		packetsToChoke = (rand() % 8) + 6;
		new_factor = false;
	}
	else if (Type == 5 && new_factor)
	{
		static int FakelagFactor = 10;
		static int m_iOldHealth = 0;
		static int iChoked;
		if (m_iOldHealth != G::LocalPlayer->GetHealth())
		{
			m_iOldHealth = G::LocalPlayer->GetHealth();
			packetsToChoke = rand() % 7 + 6 + 1;
			new_factor = false;
		}
	}
	else if (Type == 6 && new_factor)
	{
		int min_packets = 0;
		Vector vel_p_t = Vector(G::LocalPlayer->GetVecVelocity() * Interfaces.pGlobalVars->interval_per_tick);
		for (int i = 1; i <= 14; i++)
		{
			if (Vector(vel_p_t * i).Length() > 64)
			{
				min_packets = i;
				break;
			}
		}

		packetsToChoke = int(RandomFloatFSF(min_packets, ticksMax));
	}

	if (packetsToChoke > ticksMax)
		packetsToChoke = ticksMax;


	if (Misc::Shooting() || G::LocalPlayer->GetVecVelocity().Length() < 10.f)
		packetsToChoke = 1;


	if (ticks > packetsToChoke)
	{
		ticks = 0;
		Hacks.SendPacket = true;
		new_factor = true;
	}
	else
	{
		Hacks.SendPacket = false;
	}


	ticks++;

	return false;


}
void Marquee(std::string& clantag)
{
	std::string temp = clantag;
	clantag.erase(0, 1);
	clantag += temp[0];
}



void MarqueeTag()
{
	static std::string cur_clantag = "-Lore-Cheats.com-";
	static float oldTime;

	

	if (g_Options.Misc.clantagselection == 2)
	{
		if (Interfaces.pGlobalVars->curtime - oldTime >= 0.5f)
		{
			Marquee(cur_clantag);
			setclantag(cur_clantag.c_str());
			oldTime = Interfaces.pGlobalVars->curtime;;
		}
	}
	else if (g_Options.Misc.clantagselection == 4)
	{
		if (Interfaces.pGlobalVars->curtime - oldTime >= 0.5f)
		{
			Marquee(ClanTagS);
			setclantag(ClanTagS.c_str());
			oldTime = Interfaces.pGlobalVars->curtime;;
		}
	}
}
float NormalizeVel(float f)
{
	if (std::isnan(f) || std::isinf(f))
		f = 0;

	if (f > 9999999)
		f = 0;

	if (f < -9999999)
		f = 0;

	while (f < -180.0f) f += 360.0f;
	while (f > 180.0f) f -= 360.0f;

	return f;
}
void RankRevealAll()
{


	using ServerRankRevealAll = bool(__cdecl*)(int*);

	int v[3] = { 0.f,0.f,0.f };

	reinterpret_cast<ServerRankRevealAll>(offsets.ServerRankRevealAllEx)(v);


}
bool __fastcall Hooked_CreateMoveMain(void* thisptr, void*, float flInputSampleTime, CUserCmd* cmd)
{
	static CreateMoveFn oCreateMoveNew = CLIENTMOVEVMT->GetOriginalMethod<CreateMoveFn>(24);

	if (g_Options.Misc.Misc_Ranks && GetAsyncKeyState(VK_TAB))
	{
		RankRevealAll();
	}

	if (INIT::Exit)
		return true;
	if (!cmd)
		return true;
	if (cmd->command_number == 0 || !Interfaces.pEngine->IsInGame() || !Interfaces.pEngine->IsConnected())
		return true;

	Hacks.CurrentCmd = cmd;
	Hacks.SendPacket = true;

	if (!G::LocalPlayer || !G::LocalPlayer->isAlive())
		return true;

	CBaseCombatWeapon* pLocalWeapon = G::LocalPlayer->GetActiveBaseCombatWeapon();
	if(!pLocalWeapon)
		return true;

	//ClanTag();
	MarqueeTag();


	Vector org_view = cmd->viewangles;
	Misc::Normalize(org_view);
	CreateMoveETC::BhopMovement(org_view);


	DWORD* fp;
	__asm mov fp, ebp;

	g_Options.wpn = *pLocalWeapon->GetItemDefinitionIndex();

	g_PredictionSystem->StartPrediction();


	if (g_Options.Misc.Misc_KnifeBot)
		KnifeBot::Run();

	if (g_Options.Visuals.Visuals_GrenadePrediction && pLocalWeapon->IsGrenade())
	{
		GranadePrediction::pInstance->PredictNade(G::LocalPlayer);
	}
	else
	{
		GranadePrediction::pInstance->SetPredicted(false);
	}
	if (!pLocalWeapon->IsGrenade())
	{
		if (g_Options.NewLegitbot.Aimbot.Enabled && !g_Options.Ragebot.Ragebot_AimbotEnabled)
		{
			static float curtime = 0;
			if (Misc::Shooting() && pLocalWeapon->isPistol())
			{
				curtime = Interfaces.pGlobalVars->curtime + 0.205f;
				g_Options.m_iBulletsFire++;
			}
			else
			{
				if (Interfaces.pGlobalVars->curtime >= curtime || !pLocalWeapon->isPistol())
				{
					g_Options.m_iBulletsFire = 0;
				}
			}



			g_pLegitbot->Run(cmd, pLocalWeapon);

			if (g_Options.NewLegitbot.Aimbot.BackTracking)
			{
				backtracking->legitBackTrack(cmd, G::LocalPlayer);
			}
		}

		if (g_Options.Ragebot.Ragebot_AimbotEnabled && !g_Options.NewLegitbot.Aimbot.Enabled)
		{
			
			backtracking->RageBackTrack(cmd, G::LocalPlayer);

			if (pLocalWeapon->ammo() > 0)
			{
				Aimbot.Aim(cmd, org_view, pLocalWeapon);
			}
			else
			{
				cmd->buttons &= ~IN_ATTACK;
				cmd->buttons |= IN_RELOAD;
			}
		}
	}
	if (!g_Options.NewLegitbot.Aimbot.Enabled)
	{

		if (g_Options.Misc.FakeLag.Misc_FakeLag > 0)
			FakeLag();



		static bool bSSwitch;
		if (g_Options.Misc.FakeLag.Misc_FakeLag < 1)
		{
			Hacks.SendPacket = bSSwitch;
			bSSwitch = !bSSwitch;
		}

	}

	if (!Misc::Shooting() && !g_Options.NewLegitbot.Aimbot.Enabled)
		AA.Run();
	if (!pLocalWeapon->IsGrenade())
	{
		if (g_Options.Ragebot.Ragebot_AimbotEnabled && g_Options.Ragebot.AutoRevolver)
		{
			static int ticks = 0;
			if (*pLocalWeapon->GetItemDefinitionIndex() == WEAPON_REVOLVER && pLocalWeapon->ammo() > 0 && Aimbot.IsAbleToShoot(pLocalWeapon))
			{
				ticks++;
				if (ticks <= 14)
					cmd->buttons |= IN_ATTACK;
				else
					ticks = 0;
			}
			else
				ticks = 0;
		}
	}//Aimbot.AutoRevolver(cmd, pLocalWeapon);
	
	g_PredictionSystem->EndPrediction();


	if (g_Options.Ragebot.AutoPistol || g_Options.NewLegitbot.Aimbot.AutoPistol)
	{

		if (g_Options.wpn == WEAPON_FIVESEVEN || g_Options.wpn == WEAPON_DEAGLE || g_Options.wpn == WEAPON_ELITE || g_Options.wpn == WEAPON_P250 || g_Options.wpn == WEAPON_GLOCK || g_Options.wpn == WEAPON_USP_SILENCER || g_Options.wpn == WEAPON_TEC9 || g_Options.wpn == WEAPON_HKP2000)
		{
			if (cmd->buttons & IN_ATTACK)
			{
				float flCurTime = (float)G::LocalPlayer->GetTickBase() * Interfaces.pGlobalVars->interval_per_tick;
				float flNextAttack = pLocalWeapon->NextPrimaryAttack();

				if (flNextAttack > flCurTime)
				{
					cmd->buttons &= ~IN_ATTACK;
					cmd->buttons |= IN_ATTACK;
					cmd->buttons &= ~IN_ATTACK;
				}
			}
		}
	}
	if (!g_Options.Ragebot.Ragebot_AimbotEnabled && g_Options.NewLegitbot.Aimbot.Enabled)
	{
		static int Chok = 0;

		if (!cmd->buttons & IN_ATTACK)
		{
			Hacks.SendPacket = true;
		}
		else
		{

			if (!Hacks.SendPacket)
			{
				if (Chok > 2)
				{
					Hacks.SendPacket = true;
					Chok = 0;
				}
				Chok++;
			}
			else
			{
				Chok = 0;
			}

		}
	}


	if (g_Options.Visuals.Visuals_GhostAngle && Hacks.SendPacket)
	{
		Vector bkp = G::LocalPlayer->GetAbsAnglesNew();
		G::LocalPlayer->SetAbsAngles(Vector(bkp.x, cmd->viewangles.y, bkp.z));
		G::LocalPlayer->InvalidateBoneCache();
		G::LocalPlayer->SetupBones(G::localPlayerLbyBones, 128, 0x100, Interfaces.pEngine->GetLastTimeStamp());
		G::LocalPlayer->SetAbsAngles(bkp);
		G::LocalPlayer->InvalidateBoneCache();
	}
	if (!Hacks.SendPacket && !g_Options.NewLegitbot.Aimbot.Enabled)
		Hacks.lbychoke = (fabsf(NormalizeVel(NormalizeVel(G::LocalPlayer->pelvisangs()) - NormalizeVel(cmd->viewangles.y))) <= 2.f * 35.0f) || !(G::LocalPlayer->GetFlags() & FL_ONGROUND);


	CreateMoveETC::CleanUp(org_view);
	*(bool*)(*fp - 0x1C) = Hacks.SendPacket;


	return false;
}



#pragma endregion
#pragma region BulletTracer
void __fastcall Hooked_BeginFrame(void* thisptr)
{
	static BeginFrameFn oBeginFrame = STUDIORENDERVMT->GetOriginalMethod<BeginFrameFn>(9);
	g_pBulletTracer->Main();
	oBeginFrame(thisptr);
}
#pragma endregion
#pragma region LogEvents
void LogEvents::FireGameEvent(IGameEvent* pEvent)
{

	if (g_Options.Visuals.Visuals_DrawEventLog && Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected())
	{
		CBaseEntity* pLocal = G::LocalPlayer;
		if (pLocal)
		{
			static const char* team[]{ "",""," (Terrorist)"," (Counter-Terrorist)" };
			static const char* hasdefusekit[]{ "without defuse kit.","with defuse kit." };
			static const char* hasbomb[]{ "without the bomb.","with the bomb." };

			if (strstr(pEvent->GetName(), "player_hurt"))
			{
				auto userid = pEvent->GetInt("userid");
				auto attacker = pEvent->GetInt("attacker");

				if (!userid || !attacker)
					return;

				auto userid_id = Interfaces.pEngine->GetPlayerForUserID(userid);
				auto attacker_id = Interfaces.pEngine->GetPlayerForUserID(attacker);

				player_info_t userid_info, attacker_info;
				if (!Interfaces.pEngine->GetPlayerInfo(userid_id, &userid_info))
					return;

				if (!Interfaces.pEngine->GetPlayerInfo(attacker_id, &attacker_info))
					return;

				std::stringstream string;
				string << "[" << attacker_info.name << "]" << " did " << pEvent->GetInt("dmg_health") << " damage to " << userid_info.name << ".";
				if (g_Options.Visuals.damagelog)
					events.push_front(loginfo((string.str()), 255, 240, 30, 240, Interfaces.pGlobalVars->curtime));

			}
			else if (strcmp(pEvent->GetName(), "player_death") == 0)
			{
				auto userid = pEvent->GetInt("userid");
				auto attacker = pEvent->GetInt("attacker");

				if (!userid || !attacker)
					return;


				auto userid_id = Interfaces.pEngine->GetPlayerForUserID(userid);
				auto attacker_id = Interfaces.pEngine->GetPlayerForUserID(attacker);

				player_info_t userid_info, attacker_info;
				if (!Interfaces.pEngine->GetPlayerInfo(userid_id, &userid_info))
					return;

				if (!Interfaces.pEngine->GetPlayerInfo(attacker_id, &attacker_info))
					return;

				std::stringstream string;
				string << "[" << userid_info.name << "]" << team[pEvent->GetInt("team")] << " killed by " << "[" << attacker_info.name << "]" << ".";
				if (g_Options.Visuals.killlog)
					events.push_front(loginfo(string.str(), 255, 0, 0, 240, Interfaces.pGlobalVars->curtime));
			}
			else if (!strcmp(pEvent->GetName(), ("player_connect")))
			{
				int PlayerID = Interfaces.pEngine->GetPlayerForUserID(pEvent->GetInt(("userid")));

				player_info_t PlayerInfo;
				if (Interfaces.pEngine->GetPlayerInfo(PlayerID, &PlayerInfo)) {
					std::stringstream string;
					string << "[" << PlayerInfo.name << "]" << " just connected" << ".";
					if (g_Options.Visuals.connectlog)
						events.push_front(loginfo(string.str(), 100, 100, 255, 240, Interfaces.pGlobalVars->curtime));
				}
			}
			else if (strstr(pEvent->GetName(), "item_purchase"))
			{
				auto userid = pEvent->GetInt("userid");

				if (!userid)
					return;

				auto userid_id = Interfaces.pEngine->GetPlayerForUserID(userid);

				player_info_t userid_info;
				if (!Interfaces.pEngine->GetPlayerInfo(userid_id, &userid_info))
					return;

				std::stringstream string;
				string << "[" << userid_info.name << "]" << team[pEvent->GetInt("team")] << " purchased a(n) " << pEvent->GetString("weapon") << ".";
				if (g_Options.Visuals.purchaselog)
					events.push_front(loginfo(string.str(), 40, 237, 63, 240, Interfaces.pGlobalVars->curtime));
			}
			else if (strstr(pEvent->GetName(), "bomb_pickup"))
			{
				auto userid = pEvent->GetInt("userid");

				if (!userid)
					return;

				auto userid_id = Interfaces.pEngine->GetPlayerForUserID(userid);

				player_info_t userid_info;
				if (!Interfaces.pEngine->GetPlayerInfo(userid_id, &userid_info))
					return;

				std::stringstream string;
				string << "[" << userid_info.name << "]" << " has pickup bomb" << ".";
				if(g_Options.Visuals.bomblog)
					events.push_front(loginfo(string.str(), 255, 158, 2, 240, Interfaces.pGlobalVars->curtime));
			}
			else if (strstr(pEvent->GetName(), "bomb_beginplant"))
			{
				auto userid = pEvent->GetInt("userid");

				if (!userid)
					return;

				auto userid_id = Interfaces.pEngine->GetPlayerForUserID(userid);

				player_info_t userid_info;
				if (!Interfaces.pEngine->GetPlayerInfo(userid_id, &userid_info))
					return;

				std::stringstream string;
				string << "[" << userid_info.name << "]" << " has began planting the bomb at site " << pEvent->GetInt("site") << ".";
				if (g_Options.Visuals.bomblog)
					events.push_front(loginfo(string.str(), 255, 158, 2, 240, Interfaces.pGlobalVars->curtime));
			}
			else if (strstr(pEvent->GetName(), "bomb_begindefuse"))
			{
				auto userid = pEvent->GetInt("userid");

				if (!userid)
					return;

				auto userid_id = Interfaces.pEngine->GetPlayerForUserID(userid);

				player_info_t userid_info;
				if (!Interfaces.pEngine->GetPlayerInfo(userid_id, &userid_info))
					return;

				std::stringstream string;
				string << "[" << userid_info.name << "]" << " has began defusing the bomb " << hasdefusekit[pEvent->GetBool("haskit")];
				if (g_Options.Visuals.bomblog)
					events.push_front(loginfo(string.str(), 1, 145, 255, 240, Interfaces.pGlobalVars->curtime));
			}
			else if (strstr(pEvent->GetName(), "enter_bombzone"))
			{
				auto userid = pEvent->GetInt("userid");

				if (!userid)
					return;

				auto userid_id = Interfaces.pEngine->GetPlayerForUserID(userid);

				player_info_t userid_info;
				if (!Interfaces.pEngine->GetPlayerInfo(userid_id, &userid_info))
					return;
				
				std::stringstream string;
				string << "[" << userid_info.name << "]" << " entered the bomb zone " << hasbomb[pEvent->GetBool("hasbomb")];
				if (g_Options.Visuals.bomblog)
					events.push_front(loginfo(string.str(), 1, 145, 255, 240, Interfaces.pGlobalVars->curtime));
			}

			if (events.size() > 12)
				events.pop_back();
		}
	}
}
void LogEvents::Draw()
{
	if (events.size())
	{
		for (size_t i = 0; i < events.size(); i++)
		{
			float time = Interfaces.pGlobalVars->curtime - events[i].time;
			if (time > 6.f)
				events[i].colorA *= 0.98f;
			if (time > 6.f)
			{events[i].x -= 1;}		
			Interfaces.pSurface->DrawT2(events[i].x, 10.f + i * 15, CColor(events[i].colorR, events[i].colorG, events[i].colorB, events[i].colorA), Hacks.TAHOMA, false, ("%s" ,(char*)events[i].text.c_str()));
		}
	}
}
#pragma endregion
#pragma region AutoAccept
void __fastcall Hooked_PlaySound(void* ecx, void* edx, const char* filename)
{
	static PlaySoundFn oPlaySound = SURFACEVMT->GetOriginalMethod<PlaySoundFn>(82);
	oPlaySound(ecx, filename);
	if (!g_Options.Misc.Misc_AutoAccept || Interfaces.pEngine->IsInGame() || Interfaces.pEngine->IsConnected() || INIT::Exit || G::LocalPlayer)
		return;	
	typedef void(__cdecl* IsReadyFn)();
	static IsReadyFn IsReady = (IsReadyFn)(offsets.dwIsReady);
	if (!strcmp(filename, ("UI/competitive_accept_beep.wav")))
	{
		IsReady();
		FLASHWINFO fi;
		fi.cbSize = sizeof(FLASHWINFO);
		fi.hwnd =  render->window;
		fi.dwFlags = FLASHW_ALL | FLASHW_TIMERNOFG;
		fi.uCount = 0;
		fi.dwTimeout = 0;
		Beep(100, 5);
		FlashWindowEx(&fi);
	}
}
#pragma endregion
#pragma region SOUNDESP
#include "LegitMath.h"
void __fastcall Hooked_EmitSound(IEngineSound* thisptr, int edx, IRecipientFilter& filter, int iEntIndex, int iChannel, const char* pSoundEntry, unsigned int nSoundEntryHash, const char* pSample, float flVolume, float flAttenuation, int nSeed, int iFlags, int iPitch, const Vector* pOrigin, const Vector* pDirection, CUtlVector<Vector>* pUtlVecOrigins, bool bUpdatePositions, int flSoundTime, int iSpeakerEntity)
{
	static EmitSoundFn oEmitSound = EMITSOUNDVMT->GetOriginalMethod<EmitSoundFn>(5);
	oEmitSound(thisptr, filter, iEntIndex, iChannel, pSoundEntry, nSoundEntryHash, pSample, flVolume, flAttenuation, nSeed, iFlags, iPitch, pOrigin, pDirection, pUtlVecOrigins, bUpdatePositions, flSoundTime, iSpeakerEntity);
	if (iEntIndex < 1 || iEntIndex > 64 || !G::LocalPlayer)return;
	if (!Interfaces.pEngine->IsInGame() || !Interfaces.pEngine->IsConnected() || !g_Options.Visuals.SoundESP.Enabled || !G::LocalPlayer || INIT::Exit)return;
	auto pEntity = Interfaces.pEntList->GetClientEntity(iEntIndex);
	if (!pEntity || pEntity == G::LocalPlayer || !pEntity->IsPlayer() || !pEntity->isAlive())
		return;
	if (pEntity->GetTeam() == G::LocalPlayer->GetTeam() && !g_Options.Visuals.Visuals_EspTeam)
		return;
	if (pEntity->IsVisible(8) && g_Options.Visuals.SoundESP.visonly)
		return;
	float flDistance = LegitMath::VectorDistance(G::LocalPlayer->GetAbsOrigin(), pEntity->GetAbsOrigin());
	if (iChannel == 4 && strstr(pSample, ("footsteps")) && g_Options.Visuals.SoundESP.Distance > 0.f && flDistance <= g_Options.Visuals.SoundESP.Distance)
		Esp::CSoundESP::Get().AddSound(*pOrigin, Interfaces.pGlobalVars->curtime + 1.f, pEntity, g_Options.Visuals.SoundESP.Radius);
}
void Esp::CSoundESP::Draw()
{
	if (g_Options.Visuals.SoundESP.Enabled)
	{
		for (size_t i = 0; i < footsteps.size(); i++)
		{
			if ((footsteps[i].origin.IsZero()) || footsteps.size() > 10 || footsteps[i].time < Interfaces.pGlobalVars->curtime)
				footsteps.erase(footsteps.begin() + i);	
			if (g_Options.Visuals.SoundESP.Animated)
			{
				if (footsteps[i].isZeroz)
				{
					if (g_Options.Visuals.SoundESP.Radius > 10.f)
					{
						footsteps[i].radius -= 0.1f;
					}
					else
					{
						footsteps[i].radius -= 0.05f;
					}
				}
				if (!footsteps[i].isZeroz)
				{
					if (g_Options.Visuals.SoundESP.Radius > 10.f)
					{
						footsteps[i].radius += 0.1f;
					}
					else
					{
						footsteps[i].radius += 0.05f;
					}
				}
				if (footsteps[i].radius < 0.1f)
				{
					footsteps[i].radius = 0.1f;
					footsteps[i].isZeroz = false;
				}
				if (g_Options.Visuals.SoundESP.Radius < footsteps[i].radius)
				{
					footsteps[i].radius = g_Options.Visuals.SoundESP.Radius;
					footsteps[i].isZeroz = true;
				}
			}
			switch (g_Options.Visuals.SoundESP.type)
			{
			case 0:
			{
				Vector out;
				if (render->WorldToScreen(footsteps[i].origin, out))
				{
					Interfaces.pSurface->DrawSetColor1(Hacks.Colors.SoundESP);
					Interfaces.pSurface->DrawOutlinedRect(out.x - footsteps[i].radius / 2.f, out.y - footsteps[i].radius / 2.f, out.x + footsteps[i].radius / 2.f, out.y + footsteps[i].radius / 2.f);
				}
			}break;
			case 1:
			{
				this->DrawWave(footsteps[i].origin, footsteps[i].radius, Hacks.Colors.SoundESP);
			}break;
			default: break;

			}		
		}
	}

}
#pragma endregion


