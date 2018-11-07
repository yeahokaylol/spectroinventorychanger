#pragma once
#include "ImGUI\imgui.h"
#include <vector>

class RageTabNew
{
public:
	bool MP[6] = { true, true, true , true , true , true }; //hitboxes
	float MPs[6] = { 0.5f, 0.5f, 0.5f , 0.5f , 0.5f , 0.5f };


	bool AutoPistol = false;
	bool AutoRevolver = false;
	bool LagComp = false;

	bool Ragebot_Knopka180 = false;

	int Ragebot_BodyKeyEnable;


	int Ragebot_Knopka180Val = 0;
	int Ragebot_Knopka180ValAA = 0;

	bool Ragebot_MoonWalk = false;
	bool Ragebot_FakeWalk = false;
	int Ragebot_FakeWalkKey = 0;

	int Ragebot_BodyAimAfterHP = 0;
	bool BodyWhenFake = false;
	bool Ragebot_BodyAwp = false;
	bool Ragebot_AimbotEnabled = false;
	int Ragebot_Selection = 0;
	int Ragebot_Hitbox = 6;
	bool Ragebot_AutoShoot = false;
	bool Ragebot_Autoscope = false;
	bool Ragebot_SilentAim = false;
	bool resolver = false;
	float Ragebot_Hitchance = 0.f;
	float Ragebot_MinDamage = 0.f;
	bool Ragebot_Resolver = false;
	int Ragebot_AutoWallMode = 1;
	int Ragebot_PreferBodyAim = 1;
	bool Ragebot_PositionAdjustment = false;
	bool Ragebot_CustomHitscan[6] = { true, true, true , true , true , true };


	bool AntiAim_Enabled = false;
	bool AntiAim_EnabledMove = false;
	bool AntiAim_EnabledEdge = false;

	int AntiAim_Pitch = 0;
	int AntiAim_Yaw = 0;
	int AntiAim_FakeYaw = 0;
	bool AntiAim_AtTargets = false;
	int Ragebot_AddRealYaw = 0;
	int Ragebot_AddFakeYaw = 0;


	int AntiAim_PitchMove = 0;
	int AntiAim_YawMove = 0;
	int AntiAim_FakeYawMove = 0;
	bool AntiAim_AtTargetsMove = false;
	int Ragebot_AddRealYawMove = 0;
	int Ragebot_AddFakeYawMove = 0;


	int AntiAim_PitchEdge = 0;
	int AntiAim_YawEdge = 0;
	int AntiAim_FakeYawEdge = 0;
	int Ragebot_AddRealYawEdge = 0;
	int Ragebot_AddFakeYawEdge = 0;
	float Ragebot_LBYDELTA = 0.f;
};
class VisualsTabNew
{
public:
	bool Enabled = false;
	bool Visuals_BoxEnabled = false;
	int Visuals_BoxType = 1;
	int Visuals_HealthBarType = 1;
	bool Visuals_Scoped = false;
	bool Visuals_AmmoESP = false;
	int Visuals_AmmoESPType = 1;
	int OffscreenIndicatorSize = 12;
	float OffscreenIndicatorRadius = 230.f;
	bool OffscreenIndicator;
	int OffscreenIndicatorCheck;
	bool Visuals_EspTeam = false;
	bool Visuals_VisableOnly = false;



	bool Visuals_HealthBar = false;
	bool Visuals_Name = false;
	bool Visuals_ArmorBar = false;
	bool Visuals_Flashed = false;
	bool Visuals_Defuser = false;
	bool Visuals_Weapons = false;
	int Visuals_WeaponsType = 0;
	bool Visuals_AimLines = false;
	bool Visuals_Skeltal = false;
	bool Visuals_EngineRadar = false;
	int x, y;
	bool Visuals_DrawLinesAA = false;
	bool Visuals_DroppedWeapons = false;
	bool Visuals_NoRecoil = false;
	bool Visuals_NoFlash = false;
	bool Visuals_NoSmoke = false;
	bool Visuals_NoSmokeVar = false;
	bool Visuals_NoScope = false;
	bool Visuals_NoZoom = false;
	bool Visuals_NoPostProcess = false;


	bool Visuals_Chams = false;
	bool Visuals_ChamsTeam = false;
	bool Visuals_ChamsXQZ = false;
	int  Visuals_ChamsMaterial = 1;
	bool Visuals_GhostAngle = false;
	bool Visuals_ChamsGuns = false;
	bool Visuals_Crosshair = false;
	bool Visuals_CrosshairDynamic = false;

	bool Visuals_Hitmarker = false;
	bool Visuals_Spread = false;
	bool Visuals_GrenadePrediction = false;
	bool Visuals_DamageESP = false;
	bool Visuals_C4 = false;


	bool Vis_Glow = false;
	bool Vis_Glow_Team = false;
	bool Vis_Glow_Vis = false;


	bool Visuals_NightMode = false;
	bool Visuals_Asus = false;

	bool Visuals_DrawBeams = false;
	float Visuals_DrawBeamsDuration = 3.f;
	float Visuals_DrawBeamsSize = 3.f;

	bool Visuals_DrawCapsules = false;
	bool Visuals_DrawEventLog = false;
	float Visuals_DrawCapsulesDuration = 5.f;
	int Visuals_Spread_Type = 0;
	struct
	{
		bool Enabled = false;
		float Distance = 800.f;
		int type = 0;
		float Radius = 10.f;
		bool Animated = false;
		bool visonly = false;
	}SoundESP;
	struct
	{
		struct
		{
			bool	ExternalRadar;
			int		RadarStyle;
			float	RadarDistance;
			bool	RadarVisibleOnly;
			bool	RadarSmoke;
		}Radar;
		bool Monitor = false;
	}Panels;
 
	bool lbyIndicator = false;
	bool strelkiIndicator = false;
	bool bomblog;
	bool damagelog;
	bool purchaselog;
	bool connectlog;
	bool killlog;

};


class cLegitBot
{
public:
	struct
	{
		bool 	Enabled;
		bool AutoPistol = false;
		int 	Key;
		bool	OnKey;
		bool DistanceBased = false;
		int   AimType;
		bool	BackTracking = false;
		int		BackTrackIng = 1;
		int 	Filter; 
		bool 	VisCheck;
		bool 	AlwaysOn;
		bool	FriendlyFire;
		bool	SmokeCheck;
		bool    bKillDelay;
		float		iKillDelay = 0.3f;
		float  HitChance = 30.f;
		bool	JumpCheck;
		bool    FlashCheck;
		float  FlashCheckAlpha;
		bool DrawFOV = false;
		bool FastZoom;
		bool RCSFix = false;
		
	} Aimbot;

	struct
	{
		bool	Enabled;
		bool	AutoFire;
		int		Key;
		bool 	HitChance;
		float	HitChanceAmt;
		bool AutoWall;
		int Delay;


		struct
		{
			bool Head;
			bool Chest;
			bool Stomach;
			bool Arms;
			bool Legs;
			bool Friendly;
			bool smoke;
		} Filter;

	} Triggerbot;

	class Weapon_t
	{
	public:
		bool Enabled = false;
		int Aimtype = 0;
		int SmoothType = 0;
		float Fov = 0;
		int Bone = 0;
		bool Nearest = false;
		bool NearestRCS = false;
		float Smooth = 0.0f;
		bool FireDelayRepeat = false;
		int FireDelay = 1;
		int StartBullet = 1;
		int EndBullet = 100;
		float RcsX = 0.f;
		float RcsY = 0.f;
		bool pSilent = false;
		int pSilentBullet = 1;
		float pSilentFov = 0.0f;
		float pSilentHitChance = 0.f;
		int PaintKit;
	}Weapon[520];
};

class cMiscTab
{
public:
	struct
	{
		bool AntiUntrusted = true;

	}AntiCheats;
	struct
	{
		int Misc_FakeLag = 0;
		bool Misc_InAirOnly = false;
		int Misc_FakeLagFactor = 7;
	}FakeLag;


	bool Misc_AutoAccept = false;
	bool Misc_KnifeBot = false;
	bool Misc_ZeusBot = false;
	bool Misc_ZStrafe = false;
	int Misc_ZStrafeKey = 0;
	bool BuyBot;
	int item = 0;

	bool Misc_AutoJump = false;
	bool Misc_AutoStrafe = false;
	int Misc_AutoStraferMode = 0;
	int clantagselection = 0;

	bool TrashTalk;
	bool EndRoundTalk;
	int talk;
	

	bool Misc_ClanTagSpammer;
	bool Misc_ClanTagAnimate;
	char ClanTag[64];
	bool ClanTagOn;
	
	bool ClanTagAnim;
	
	int Misc_Fov = 0;
	int ViewModelFov = 75;
	char configname[128] = "New Config";
	char confignameskins[128] = "New Config";
	char confignameColors[128] = "New Config";



	bool Visuals_ThirdPerson = false;
	int Visuals_ThirdPersonAngle = 0;
	int Visuals_ThirdPersonKey = 0;
	int Visuals_ThirdPersonDistance = 150;


	bool    SpectatorList = false;
	bool Misc_Ranks = false;
	bool connectinventory;
	bool rankchanger;
	int rank_id = 9;
	int wins = 100;
	int level = 40;
	int friendly = 999;
	int teaching = 999;
	int leader = 999;
	int weaponid = 7;
	int index = 1;
	int quality = 6;
	int paintkit = 474;
	float seed = 0;
	float wear = 0.00001;
	bool AutoEquip = false;


};
std::string ClanTagS;
class cMenu
{
public:
	bool	Opened = false;
	//bool    SkinChangerWindow = false;
	int 	Key;
	bool	Ragebot = false;
	bool	Legitbot = false;
	bool	Visual = false;
	bool	Misc = false;
	bool    Animations = false;
};
#define STICKERS_COUNT 5


class Sticker_t
{
public:
	int iID = 0;
	float flWear = 0.f;
	float flScale = 1.f;
	int iRotation = 0;
};
class cSkins
{
public:
	bool EnabledChanger = false;
	int WeaponID = 7;
	int knifemodel = 3;
	int glovemodel = 2;
	int gloveskin = 1;
	bool sticker;
	struct
	{
		int PaintKit = 0;
		int Seed = 0;
		bool Stattrak = false;
		int StattrakValue = 1337;
		float Wear = 0.1f;
		bool StickersEnabled = false;
		Sticker_t Stickers[STICKERS_COUNT];
	} SkinMaster[520];
	struct
	{
		bool Enable = false;
		int Player = 0;
		char CustomPlayer[128] = "models/player/";
		int Arms = 0;
		char CustomArms[128] = "models/weapons/";
		int Knife = 0;
		char CustomKnife[128] = "models/weapons/";
		int Weapon = 0;
	} MDLModels;
};
class cPlayersList
{
public:
	bool	Playerlist;
	bool	Resolveall;
	struct
	{
		int YAngle;
		int PAngle;
		int Resolver;
		bool Baim;
	}AAA[64];

};
namespace ResolverVars
{
	extern int ResolverStage[65];
	extern int DidhitHS[65];
	extern int ResolvedpAngles[65];
}



class Variables
{
public:

	RageTabNew Ragebot;
	VisualsTabNew Visuals;
	cMiscTab Misc;
	cPlayersList Players;
	cLegitBot NewLegitbot;
	cSkins Skinchanger;

	//	cRagebot Ragebot;
	//	cPlayersList Players;
	//	cVisuals Visuals;
	//	cMisc Misc;
	//	cLegitBot Legitbot;
	//	cSkins Skins;
	cMenu Menu;

	int wpn;
	int i = 0;

	Variables()
	{
		wpn = -1;
	}

	int Bomber;
	int Hostage;
	int Defuser;
	bool Bomb;
	bool font2;
	bool shoot;
	//QAngle lastTickViewAngles = { 0,0,0 };
	bool bIsNoShot;
	int m_iBulletsFire = 0;

	float g_fMColor[4] = { 0.20f, 0.20f, 0.20f, 1.0f }; //RGBA color
	float g_fBColor[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	float g_fTColor[4] = { 1.f, 1.f, 1.f, 1.0f };


	ImFont* font;
	//CColorsTab ColorsTab;
};

namespace CPlayerList
{
	extern std::vector<int> Players;
}

extern Variables g_Options;




