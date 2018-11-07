#pragma once
#include <vector>
#include <algorithm>
#include "stdafx.h"
#include "resource.h"
#include "SDK/SDK Headers/CGameEvent.h"
#include "RankReveal.h"
#include "DrawModel.h"
#include "DirectX.h"
#include "Protobuf/IMemAlloc.h"
#include "Protobuf/Protobuffs.h"

enum DataUpdateType_t
{
	DATA_UPDATE_CREATED = 0,
	DATA_UPDATE_DATATABLE_CHANGED
};


void __stdcall Hooked_PaintTraverse(unsigned int vguiPanel, bool forceRepaint, bool allowForce);
EGCResult __fastcall hkGCRetrieveMessage(void* ecx, void*, uint32_t *punMsgType, void *pubDest, uint32_t cubDest, uint32_t *pcubMsgSize);
EGCResult __fastcall hkGCSendMessage(void* ecx, void*, uint32_t unMsgType, const void* pubData, uint32_t cubData);
using GCRetrieveMessage = EGCResult(__thiscall*)(void*, uint32_t *punMsgType, void *pubDest, uint32_t cubDest, uint32_t *pcubMsgSize);
using GCSendMessage = EGCResult(__thiscall*)(void*, uint32_t unMsgType, const void* pubData, uint32_t cubData);
bool __fastcall Hooked_FireEventClientSide(void*, void*, IGameEvent* pEvent);
void __stdcall Hooked_Frame_Stage_Notify(ClientFrameStage_t curStage);
float	__stdcall Hooked_ViewModelView();
void __stdcall hkLockCursor();
void __stdcall Hooked_OverrideView(CViewSetup* pSetup);
bool __fastcall	 Hooked_DoPostScreenSpaceEffects(void* thisptr, int edx, CViewSetup* pSetup);
LRESULT __stdcall Hooked_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT __stdcall Hooked_D3D9_EndScene(IDirect3DDevice9* pDevice);
HRESULT __stdcall Hooked_Reset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
void __fastcall Hooked_PlaySound(void* ecx, void* edx, const char* filename);
void __fastcall Hooked_BeginFrame(void* thisptr);
void __fastcall Hooked_DrawModelExecute(void* thisptr, int edx, void* ctx, void* state, const ModelRenderInfo_t& pInfo, matrix3x4* pCustomBoneToWorld);
int __fastcall Hooked_SendDatagram(void* netchan, void*, void *datagram);
bool __fastcall Hooked_CreateMoveMain(void* thisptr, void*, float SampleTime, CUserCmd* pCmd);
void __fastcall Hooked_EmitSound(IEngineSound* thisptr, int edx, IRecipientFilter& filter, int iEntIndex, int iChannel, const char* pSoundEntry, unsigned int nSoundEntryHash, const char* pSample, float flVolume, float flAttenuation, int nSeed, int iFlags, int iPitch, const Vector* pOrigin, const Vector* pDirection, CUtlVector<Vector>* pUtlVecOrigins, bool bUpdatePositions, int flSoundTime, int iSpeakerEntity);
//void __stdcall TEFireBulletsPostDataUpdate_h(DataUpdateType_t updateType);

void Init();




typedef int(__thiscall *SendDatagramFn)(void*, void *);

enum ResolverModes
{
	NONE,
	LBY,
	LBY_BRUTE,
	LBY_FLICK,
	LBY_979BRUTE,
	LBY_DELTA120,
	BREKINGLBY,
	MOVING,
	LASTSHAKELBY,
};

class CHackManager
{
private:
	/* Typedefs */
	typedef void(__stdcall *iCreateMoveFn)(CInput*, void*, int, float, bool);
	typedef void(__stdcall* ClientCmdUnresticted)(const char* szCmdString, char flag);
	typedef bool(__cdecl* ServerRankRevealAllFn)(float*);

public:
	std::vector<IGameEventListener2*> listeners = {};
	char *clientstatestr = new char[51]{ 66, 56, 90, 90, 73, 62, 90, 90, 69, 69, 90, 90, 69, 69, 90, 90, 69, 69, 90, 90, 69, 69, 90, 90, 66, 59, 90, 90, 60, 67, 90, 90, 60, 73, 90, 90, 74, 60, 90, 90, 75, 75, 90, 90, 78, 79, 90, 90, 60, 57, 0 }; /*8B  3D  ??  ??  ??  ??  8A  F9  F3  0F  11  45  FC*/
	char *enginedllstr = new char[11]{ 31, 20, 29, 19, 20, 31, 84, 30, 22, 22, 0 };
	HANDLE EngineHandle = NULL;
	int adr;
	/* Original Functions */

	ClientCmdUnresticted oClientCmdUnresticted;
	ServerRankRevealAllFn ServerRankRevealEx;
	Protobuffs ProtoFeatures;
	/* Holding Varialbles */
	
	CUserCmd* CurrentCmd;
	CVerifiedUserCmd* VerifiedCmd;
	SendDatagramFn oSendDatagram = NULL;
	Vector LastAngles;
	Vector LastAnglesReal;
	bool ThirdPersonEnableNow;
	bool isastronaut;


	bool SendPacket = true;
	bool switcAA = false;
	float FOV;
	float MyLowerBody;
	float lineLBY;
	float lineRealAngle;
	float strelki;
	float lineFakeAngle;

	float lineFakeAnglePitch;
	float lineFakeAngleZ;

	int antiaimfake;
	Vector Angsss;

	bool KillDelay = false;

	int Yaw;
	int Pitch;
	

	int FakingLBY[64];
	bool fakewalking[64];
	ResolverModes CurMode[64];

	bool lbychoke;

	DWORD TAHOMA;
	DWORD hFntIndicators;
	/* Hooking */
	void Hook()
	{

		TAHOMA = Interfaces.pSurface->Create_Font();
		hFntIndicators = Interfaces.pSurface->Create_Font();

		Interfaces.pSurface->SetFontGlyphSet(TAHOMA, "Courier New", 14, FW_BOLD, NULL, NULL, FONTFLAG_DROPSHADOW);
		Interfaces.pSurface->SetFontGlyphSet(hFntIndicators, "Verdana", 27, FW_BOLD, NULL, NULL, FONTFLAG_OUTLINE);


		
		DirectXX::Get().ApplyHook();


		CLIENTVMT = new VMT(Interfaces.pClient);
		CLIENTVMT->HookVM(&Hooked_Frame_Stage_Notify, 37);

		

		//
		PANELVMT = new VMT(Interfaces.pPanel);
		PANELVMT->HookVM(&Hooked_PaintTraverse, 41);
		//
		SURFACEVMT = new VMT(Interfaces.pSurface);
		SURFACEVMT->HookVM(&Hooked_PlaySound, 82);
		//
		DMEVMT = new VMT(Interfaces.g_pModelRender);
		DMEVMT->HookVM(&Hooked_DrawModelExecute, 21);
		//
		CLIENTMOVEVMT = new VMT(Interfaces.pClientMode);
		CLIENTMOVEVMT->HookVM(&Hooked_OverrideView, 18);
		CLIENTMOVEVMT->HookVM(&Hooked_ViewModelView, 35);
		CLIENTMOVEVMT->HookVM(&Hooked_CreateMoveMain, 24);
		CLIENTMOVEVMT->HookVM(&Hooked_DoPostScreenSpaceEffects, 44);
		//
		GAMEEVENTVMT = new VMT(Interfaces.g_GameEventMgr);
		GAMEEVENTVMT->HookVM(&Hooked_FireEventClientSide, 9);
		//
		STUDIORENDERVMT = new VMT(Interfaces.g_pStudioRender);
		STUDIORENDERVMT->HookVM(&Hooked_BeginFrame, 9);
		STUDIORENDERVMT->HookVM(&DrawModel, 29);
		oDrawModel = STUDIORENDERVMT->GetOriginalMethod<DrawModel_t>(29);

		//
		//EMITSOUNDVMT = new VMT(Interfaces.s_EngineSound);
		//EMITSOUNDVMT->HookVM(&Hooked_EmitSound, 5);
		gc_hook.setup(Interfaces.g_SteamGameCoordinator);
		gc_hook.hook_index(0, hkGCSendMessage);
		gc_hook.hook_index(2, hkGCRetrieveMessage);

		ProtoFeatures.SendClientHello();
		ProtoFeatures.SendMatchmakingClient2GCHello();

		CLIENTVMT->ApplyVMT();
		PANELVMT->ApplyVMT();
		SURFACEVMT->ApplyVMT();
		DMEVMT->ApplyVMT();
		CLIENTMOVEVMT->ApplyVMT();
		GAMEEVENTVMT->ApplyVMT();
		STUDIORENDERVMT->ApplyVMT();
		//EMITSOUNDVMT->ApplyVMT();
		Init();
	}

	void UnHook()
	{
		CLIENTVMT->ReleaseVMT();
		PANELVMT->ReleaseVMT();
		SURFACEVMT->ReleaseVMT();
		DMEVMT->ReleaseVMT();
		CLIENTMOVEVMT->ReleaseVMT();
		GAMEEVENTVMT->ReleaseVMT();
		STUDIORENDERVMT->ReleaseVMT();
		EMITSOUNDVMT->ReleaseVMT();
		DirectXX::Get().ReleaseHook();
		
		for (auto listener : listeners)
			Interfaces.g_GameEventMgr->RemoveListener(listener);
	}



	struct
	{
		CColor CTBoxVisable = CColor(0,0,255,255);
		CColor CTBoxInVisable = CColor(255, 255, 0, 255);
		CColor TBoxVisable = CColor(255, 0, 0, 255);
		CColor TBoxInVisable = CColor(0, 255, 255, 255);
		CColor CTGlowVisable = CColor(0, 0, 255, 255);
		CColor CTGlowInVisable = CColor(255, 255, 0, 255);
		CColor TGlowVisable = CColor(255, 0, 0, 255);
		CColor TGlowInVisable = CColor(0, 255, 255, 255);
		CColor Beams = CColor(255, 0, 255, 255);
		CColor FilledSpread = CColor(40, 40, 40, 140);
		CColor LagCompHitboxes = CColor(255, 165, 0, 140);

		CColor CTChamsVisable = CColor(0, 0, 255, 255);
		CColor CTChamsInVisable = CColor(255, 255, 0, 255);
		CColor TChamsVisable = CColor(255, 0, 0, 255);
		CColor TChamsInVisable = CColor(0, 255, 255, 255);

		CColor FakeAngleChams = CColor(255, 255, 255, 255);
		CColor SoundESP = CColor(255, 255, 255, 255);
		CColor DamageESP = CColor(255, 165, 0, 255);
		CColor Stelki = CColor(255, 40, 255, 255);
		CColor OffscreenIndicator1 = CColor(255, 165, 0, 255);
		float OffscreenIndicator[4] = { 255.f, 165.f, 0.f, 255.f };
	}Colors;

};
#include <deque>

struct loginfo
{
	loginfo(std::string text,
		int colorR, int colorG, int colorB, int colorA,
		float time, int x = 250)
	{
		this->text = text;
		this->colorR = colorR;
		this->colorG = colorG;
		this->colorB = colorB;
		this->colorA = colorA;
		this->time = time;
		this->x = x;
	}

	std::string text;
	int colorR, colorG, colorB, colorA;
	float time; int x;
};

namespace LogEvents
{
	void FireGameEvent(IGameEvent* pEvent);
	void Draw();

	static std::deque<loginfo>events;
}