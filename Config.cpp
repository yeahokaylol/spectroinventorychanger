#include "Config.h"
//#include "SDK.h"
#include <winerror.h>
/*#include <ShlObj_core.h>
#pragma comment(lib, "Shell32.lib")*/


std::string GetCFGNameChanger(int iWeaponID, int secondint)
{
		switch (iWeaponID)
		{
		case WEAPON_DEAGLE:
			return ("Desert Eagle");
		case WEAPON_ELITE:
			return ("Dual Berettas");
		case WEAPON_FIVESEVEN:
			return ("Five-SeveN");
		case WEAPON_GLOCK:
			return ("Glock-18");
		case WEAPON_AK47:
			return ("AK-47");
		case WEAPON_AUG:
			return ("AUG");
		case WEAPON_AWP:
			return ("AWP");
		case WEAPON_FAMAS:
			return ("FAMAS");
		case WEAPON_MP5:
			return ("MP-5");
		case WEAPON_G3SG1:
			return ("G3SG1");
		case WEAPON_GALILAR:
			return ("Galil");
		case WEAPON_M249:
			return ("M249");
		case WEAPON_M4A1:
			return ("M4A1");
		case WEAPON_MAC10:
			return ("MAC-10");
		case WEAPON_P90:
			return ("P90");
		case WEAPON_UMP45:
			return ("UMP-45");
		case WEAPON_XM1014:
			return ("XM1014");
		case WEAPON_BIZON:
			return ("PP-Bizon");
		case WEAPON_MAG7:
			return ("MAG-7");
		case WEAPON_NEGEV:
			return ("Negev");
		case WEAPON_SAWEDOFF:
			return ("Sawed-Off");
		case WEAPON_TEC9:
			return ("Tec-9");
		case WEAPON_TASER:
			return ("Taser");
		case WEAPON_HKP2000:
			return ("P2000");
		case WEAPON_MP7:
			return ("MP7");
		case WEAPON_MP9:
			return ("MP9");
		case WEAPON_NOVA:
			return ("Nova");
		case WEAPON_P250:
			return ("P250");
		case WEAPON_SCAR20:
			return ("SCAR-20");
		case WEAPON_SG556:
			return ("SG 553");
		case WEAPON_SSG08:
			return ("SSG 08");
		case WEAPON_KNIFE:
			return ("KnifeCT");
		case WEAPON_FLASHBANG:
			return ("Flashbang");
		case WEAPON_HEGRENADE:
			return ("HE Grenade");
		case WEAPON_SMOKEGRENADE:
			return ("Smoke Grenade");
		case WEAPON_MOLOTOV:
			return ("Molotov");
		case WEAPON_DECOY:
			return ("Decoy");
		case WEAPON_INCGRENADE:
			return ("Incendiary Grenade");
		case WEAPON_C4:
			return ("C4");
		case WEAPON_KNIFE_T:
			return ("KnifeT");
		case WEAPON_M4A1_SILENCER:
			return ("M4A1-S");
		case WEAPON_USP_SILENCER:
			return ("USP-S");
		case WEAPON_CZ75A:
			return ("CZ75-Auto");
		case WEAPON_REVOLVER:
			return ("R8 Revolver");
		case WEAPON_KNIFE_BAYONET:
			return ("KNIFE_BAYONET");
		case WEAPON_KNIFE_M9_BAYONET:
			return ("KNIFE_M9_BAYONET");
		case WEAPON_KNIFE_SURVIVAL_BOWIE:
			return ("KNIFE_BOWIE");
		case WEAPON_KNIFE_BUTTERFLY:
			return ("KNIFE_BUTTERFLY");
		case WEAPON_KNIFE_FALCHION:
			return ("KNIFE_FALCHION");
		case WEAPON_KNIFE_FLIP:
			return ("KNIFE_FLIP");
		case WEAPON_KNIFE_PUSH:
			return ("KNIFE_PUSH");
		case WEAPON_KNIFE_TACTICAL:
			return ("KNIFE_TACTICAL");
		case WEAPON_KNIFE_NAVAJA:
			return ("KNIFE_Navaja");
		case WEAPON_KNIFE_STILETTO:
			return ("KNIFE_Stiletto");
		case WEAPON_KNIFE_URSUS:
			return ("KNIFE_Ursus");
		case WEAPON_KNIFE_TALON:
			return ("KNIFE_Talon");
		default:
			return ("none");
		}
}

void CConfig::Setup()
{

		SetupValue(g_Options.Ragebot.LagComp, false, ("Ragebot"), ("LagComp"));

		
		SetupValue(g_Options.Ragebot.AutoPistol, false, ("Ragebot"), ("AutoPistol"));
		SetupValue(g_Options.Ragebot.Ragebot_BodyKeyEnable, 0, ("Ragebot"), ("Ragebot_BodyKeyEnable"));
		SetupValue(g_Options.Ragebot.Ragebot_Knopka180, false, ("Ragebot"), ("Ragebot_Knopka180"));
		SetupValue(g_Options.Ragebot.Ragebot_Knopka180Val, 0, ("Ragebot"), ("Ragebot_Knopka180Val"));
		SetupValue(g_Options.Ragebot.Ragebot_Knopka180ValAA, 0, ("Ragebot"), ("Ragebot_Knopka180ValAA"));
		SetupValue(g_Options.Ragebot.Ragebot_MoonWalk, false, ("Ragebot"), ("Ragebot_MoonWalk"));
		SetupValue(g_Options.Ragebot.Ragebot_FakeWalk, false, ("Ragebot"), ("Ragebot_FakeWalk"));
		SetupValue(g_Options.Ragebot.Ragebot_FakeWalkKey, 0, ("Ragebot"), ("Ragebot_FakeWalkKey"));
		SetupValue(g_Options.Ragebot.Ragebot_BodyAimAfterHP, 30, ("Ragebot"), ("Ragebot_BodyAimAfterHP"));
		SetupValue(g_Options.Ragebot.BodyWhenFake, true, ("Ragebot"), ("BodyWhenFake"));
		SetupValue(g_Options.Ragebot.Ragebot_BodyAwp, true, ("Ragebot"), ("Ragebot_BodyAwp"));
		SetupValue(g_Options.Ragebot.Ragebot_AimbotEnabled, true, ("Ragebot"), ("Ragebot_AimbotEnabled"));
		SetupValue(g_Options.Ragebot.Ragebot_Selection, 0, ("Ragebot"), ("Ragebot_Selection"));
		SetupValue(g_Options.Ragebot.Ragebot_Hitbox, 6, ("Ragebot"), ("Ragebot_Hitbox"));
		SetupValue(g_Options.Ragebot.Ragebot_AutoShoot, true, ("Ragebot"), ("Ragebot_AutoShoot"));
		SetupValue(g_Options.Ragebot.Ragebot_Autoscope, true, ("Ragebot"), ("Ragebot_Autoscope"));
		SetupValue(g_Options.Ragebot.Ragebot_SilentAim, true, ("Ragebot"), ("Ragebot_SilentAim"));
		SetupValue(g_Options.Ragebot.Ragebot_Hitchance, 30.f, ("Ragebot"), ("Ragebot_Hitchance"));
		SetupValue(g_Options.Ragebot.Ragebot_MinDamage, 15.f, ("Ragebot"), ("Ragebot_MinDamage"));
		SetupValue(g_Options.Ragebot.Ragebot_Resolver, true, ("Ragebot"), ("Ragebot_Resolver"));
		SetupValue(g_Options.Ragebot.Ragebot_AutoWallMode, 1, ("Ragebot"), ("Ragebot_AutoWallMode"));
		SetupValue(g_Options.Ragebot.Ragebot_PreferBodyAim, 1, ("Ragebot"), ("Ragebot_PreferBodyAim"));
		SetupValue(g_Options.Ragebot.Ragebot_PositionAdjustment, true, ("Ragebot"), ("Ragebot_PositionAdjustment"));
		SetupValue(g_Options.Ragebot.Ragebot_CustomHitscan[0], true, ("Ragebot"), ("Ragebot_CustomHitscan[0]"));
		SetupValue(g_Options.Ragebot.Ragebot_CustomHitscan[1], true, ("Ragebot"), ("Ragebot_CustomHitscan[1]"));
		SetupValue(g_Options.Ragebot.Ragebot_CustomHitscan[2], true, ("Ragebot"), ("Ragebot_CustomHitscan[2]"));
		SetupValue(g_Options.Ragebot.Ragebot_CustomHitscan[3], true, ("Ragebot"), ("Ragebot_CustomHitscan[3]"));
		SetupValue(g_Options.Ragebot.Ragebot_CustomHitscan[4], true, ("Ragebot"), ("Ragebot_CustomHitscan[4]"));
		SetupValue(g_Options.Ragebot.Ragebot_CustomHitscan[5], true, ("Ragebot"), ("Ragebot_CustomHitscan[5]"));
		SetupValue(g_Options.Ragebot.AntiAim_Enabled, true, ("Ragebot"), ("AntiAim_Enabled"));
		SetupValue(g_Options.Ragebot.AntiAim_EnabledMove, true, ("Ragebot"), ("AntiAim_EnabledMove"));
		SetupValue(g_Options.Ragebot.AntiAim_EnabledEdge, true, ("Ragebot"), ("AntiAim_EnabledEdge"));
		SetupValue(g_Options.Ragebot.AntiAim_Pitch, 0, ("Ragebot"), ("AntiAim_Pitch"));
		SetupValue(g_Options.Ragebot.AntiAim_Yaw, 0, ("Ragebot"), ("AntiAim_Yaw"));
		SetupValue(g_Options.Ragebot.AntiAim_FakeYaw, 0, ("Ragebot"), ("AntiAim_FakeYaw"));
		SetupValue(g_Options.Ragebot.AntiAim_AtTargets, false, ("Ragebot"), ("AntiAim_AtTargets"));
		SetupValue(g_Options.Ragebot.Ragebot_AddRealYaw, 0, ("Ragebot"), ("Ragebot_AddRealYaw"));
		SetupValue(g_Options.Ragebot.Ragebot_AddFakeYaw, 0, ("Ragebot"), ("Ragebot_AddFakeYaw"));


		SetupValue(g_Options.Ragebot.AntiAim_PitchMove, 0, ("Ragebot"), ("AntiAim_PitchMove"));
		SetupValue(g_Options.Ragebot.AntiAim_YawMove, 0, ("Ragebot"), ("AntiAim_YawMove"));
		SetupValue(g_Options.Ragebot.AntiAim_FakeYawMove, 0, ("Ragebot"), ("AntiAim_FakeYawMove"));
		SetupValue(g_Options.Ragebot.AntiAim_AtTargetsMove, false, ("Ragebot"), ("AntiAim_AtTargetsMove"));
		SetupValue(g_Options.Ragebot.Ragebot_AddRealYawMove, 0, ("Ragebot"), ("Ragebot_AddRealYawMove"));
		SetupValue(g_Options.Ragebot.Ragebot_AddFakeYawMove, 0, ("Ragebot"), ("Ragebot_AddFakeYawMove"));
		SetupValue(g_Options.Ragebot.AntiAim_PitchEdge, 0, ("Ragebot"), ("AntiAim_PitchEdge"));
		SetupValue(g_Options.Ragebot.AntiAim_YawEdge, 0, ("Ragebot"), ("AntiAim_YawEdge"));
		SetupValue(g_Options.Ragebot.AntiAim_FakeYawEdge, 0, ("Ragebot"), ("AntiAim_FakeYawEdge"));
		SetupValue(g_Options.Ragebot.Ragebot_AddRealYawEdge, 0, ("Ragebot"), ("Ragebot_AddRealYawEdge"));
		SetupValue(g_Options.Ragebot.Ragebot_AddFakeYawEdge, 0, ("Ragebot"), ("Ragebot_AddFakeYawEdge"));
		SetupValue(g_Options.Ragebot.Ragebot_LBYDELTA, 90.f, ("Ragebot"), ("Ragebot_LBYDELTA"));


		
		SetupValue(g_Options.Visuals.Enabled, true, ("Visuals"), ("Enabled"));
		SetupValue(g_Options.Visuals.Visuals_BoxEnabled, false, ("Visuals"), ("Visuals_BoxEnabled"));
		SetupValue(g_Options.Visuals.Visuals_VisableOnly, false, ("Visual"), ("VisabileOnly"));
		SetupValue(g_Options.Visuals.Visuals_BoxType, 0, ("Visuals"), ("Visuals_BoxType"));
		SetupValue(g_Options.Visuals.Visuals_Scoped, false, ("Visuals"), ("Visuals_Scoped"));
		SetupValue(g_Options.Visuals.Visuals_AmmoESP, false, ("Visuals"), ("Visuals_AmmoESP"));
		SetupValue(g_Options.Visuals.Visuals_AmmoESPType, 0, ("Visuals"), ("Visuals_AmmoESPType"));
		SetupValue(g_Options.Visuals.Visuals_EspTeam, false, ("Visuals"), ("Visuals_EspTeam"));
		SetupValue(g_Options.Visuals.Visuals_HealthBar, false, ("Visuals"), ("Visuals_HealthBar"));
		SetupValue(g_Options.Visuals.Visuals_HealthBarType, 0, ("Visuals"), ("Visuals_HealthBarType"));
		SetupValue(g_Options.Visuals.Visuals_Name, false, ("Visuals"), ("Visuals_Name"));
		SetupValue(g_Options.Visuals.Visuals_ArmorBar, false, ("Visuals"), ("Visuals_ArmorBar"));
		SetupValue(g_Options.Visuals.Visuals_Flashed, false, ("Visuals"), ("Visuals_Flashed"));
		SetupValue(g_Options.Visuals.Visuals_Defuser, false, ("Visuals"), ("Visuals_Defuser"));
		SetupValue(g_Options.Visuals.Visuals_Weapons, false, ("Visuals"), ("Visuals_Weapons"));
		SetupValue(g_Options.Visuals.Visuals_WeaponsType, 0, ("Visuals"), ("Visuals_WeaponsType"));


		SetupValue(g_Options.Visuals.Visuals_AimLines, false, ("Visuals"), ("Visuals_AimLines"));
		SetupValue(g_Options.Visuals.Visuals_Skeltal, false, ("Visuals"), ("Visuals_Skeltal"));
		SetupValue(g_Options.Visuals.Visuals_EngineRadar, false, ("Visuals"), ("Visuals_EngineRadar"));
		SetupValue(g_Options.Visuals.Visuals_DrawLinesAA, false, ("Visuals"), ("Visuals_DrawLinesAA"));
		SetupValue(g_Options.Visuals.Visuals_DroppedWeapons, false, ("Visuals"), ("Visuals_DroppedWeapons"));
		SetupValue(g_Options.Visuals.Visuals_NoRecoil, false, ("Visuals"), ("Visuals_NoRecoil"));
		SetupValue(g_Options.Visuals.Visuals_NoFlash, false, ("Visuals"), ("Visuals_NoFlash"));
		SetupValue(g_Options.Visuals.Visuals_NoSmoke, false, ("Visuals"), ("Visuals_NoSmoke"));
		SetupValue(g_Options.Visuals.Visuals_NoScope, false, ("Visuals"), ("Visuals_NoScope"));
		SetupValue(g_Options.Visuals.Visuals_NoSmokeVar, false, ("Visuals"), ("Visuals_NoSmokeVar"));
		SetupValue(g_Options.Visuals.Visuals_NoZoom, false, ("Visuals"), ("Visuals_NoZoom"));
		SetupValue(g_Options.Visuals.Visuals_NoPostProcess, false, ("Visuals"), ("Visuals_NoPostProcess"));
		SetupValue(g_Options.Visuals.lbyIndicator, false, ("Visuals"), ("lbyIndicator"));
		SetupValue(g_Options.Visuals.strelkiIndicator, false, ("Visuals"), ("strelkiIndicator"));

		SetupValue(g_Options.Visuals.Visuals_Chams, false, ("Visuals"), ("Visuals_Chams"));
		SetupValue(g_Options.Visuals.Visuals_ChamsTeam, false, ("Visuals"), ("Visuals_ChamsTeam"));
		SetupValue(g_Options.Visuals.Visuals_ChamsXQZ, false, ("Visuals"), ("Visuals_ChamsXQZ"));
		SetupValue(g_Options.Visuals.Visuals_GhostAngle, false, ("Visuals"), ("Visuals_GhostAngle"));
		SetupValue(g_Options.Visuals.Visuals_ChamsGuns, false, ("Visuals"), ("Visuals_ChamsGuns"));
		SetupValue(g_Options.Visuals.Visuals_Crosshair, false, ("Visuals"), ("Visuals_Crosshair"));
		SetupValue(g_Options.Visuals.Visuals_CrosshairDynamic, false, ("Visuals"), ("Visuals_CrosshairDynamic"));
		SetupValue(g_Options.Visuals.Visuals_Hitmarker, false, ("Visuals"), ("Visuals_Hitmarker"));
		SetupValue(g_Options.Visuals.Visuals_Spread, false, ("Visuals"), ("Visuals_Spread"));
		SetupValue(g_Options.Visuals.Visuals_Spread_Type, false, ("Visuals"), ("Visuals_Spread_Type"));
		SetupValue(g_Options.Visuals.Visuals_GrenadePrediction, false, ("Visuals"), ("Visuals_GrenadePrediction"));

		SetupValue(g_Options.Visuals.Visuals_C4, false, ("Visuals"), ("Visuals_C4"));
		SetupValue(g_Options.Visuals.Vis_Glow, false, ("Visuals"), ("Vis_Glow"));
		SetupValue(g_Options.Visuals.Vis_Glow_Team, false, ("Visuals"), ("Vis_Glow_Team"));
		SetupValue(g_Options.Visuals.Vis_Glow_Vis, false, ("Visuals"), ("Vis_Glow_Vis"));
		SetupValue(g_Options.Visuals.Visuals_NightMode, false, ("Visuals"), ("Visuals_NightMode"));
		SetupValue(g_Options.Visuals.Visuals_Asus, false, ("Visuals"), ("Visuals_Asus"));
		SetupValue(g_Options.Visuals.Visuals_DrawBeams, false, ("Visuals"), ("Visuals_DrawBeams"));
		SetupValue(g_Options.Visuals.Visuals_DrawBeamsDuration, 5.f, ("Visuals"), ("Visuals_DrawBeamsDuration"));
		SetupValue(g_Options.Visuals.Visuals_DrawBeamsSize, 3.f, ("Visuals"), ("Visuals_DrawBeamsSize"));
		SetupValue(g_Options.Visuals.Visuals_DrawCapsules, false, ("Visuals"), ("Visuals_DrawCapsules"));
		SetupValue(g_Options.Visuals.Visuals_DrawCapsulesDuration, 5.f, ("Visuals"), ("Visuals_DrawCapsulesDuration"));
		SetupValue(g_Options.Visuals.Visuals_DrawEventLog, false, ("Visuals"), ("Visuals_DrawEventLog"));

		SetupValue(g_Options.Visuals.SoundESP.Enabled, false, ("Visuals.SoundESP"), ("Enabled"));
		SetupValue(g_Options.Visuals.SoundESP.Distance, 800.f, ("Visuals.SoundESP"), ("Distance"));
		SetupValue(g_Options.Visuals.SoundESP.type, 0, ("Visuals.SoundESP"), ("type"));
		SetupValue(g_Options.Visuals.SoundESP.Animated, false, ("Visuals.SoundESP"), ("Animated"));
		SetupValue(g_Options.Visuals.SoundESP.visonly, false, ("Visuals.SoundESP"), ("No Visable Only"));
		SetupValue(g_Options.Visuals.SoundESP.Radius, 10.f, ("Visuals.SoundESP"), ("Radius"));

		SetupValue(g_Options.Visuals.Panels.Radar.ExternalRadar, false, ("Visuals.Panels.Radar"), ("ExternalRadar"));
		SetupValue(g_Options.Visuals.Panels.Radar.RadarStyle, 0, ("Visuals.Panels.Radar"), ("RadarStyle"));
		SetupValue(g_Options.Visuals.Panels.Radar.RadarDistance, 0.f, ("Visuals.Panels.Radar"), ("RadarDistance"));
		SetupValue(g_Options.Visuals.Panels.Radar.RadarVisibleOnly, false, ("Visuals.Panels.Radar"), ("RadarVisibleOnly"));
		SetupValue(g_Options.Visuals.Panels.Radar.RadarSmoke, false, ("Visuals.Panels.Radar"), ("RadarSmoke"));

		SetupValue(g_Options.Visuals.Visuals_DamageESP, false, ("Visuals"), ("Visuals_DamageESP"));

		SetupValue(g_Options.Misc.AntiCheats.AntiUntrusted, true, ("Misc.AntiCheats"), ("AntiUntrusted"));
		SetupValue(g_Options.Misc.FakeLag.Misc_FakeLag, 0, ("Misc.FakeLag"), ("Misc_FakeLag"));
		SetupValue(g_Options.Misc.FakeLag.Misc_InAirOnly, false, ("Misc.FakeLag"), ("Misc_InAirOnly"));
		SetupValue(g_Options.Misc.FakeLag.Misc_FakeLagFactor, 7, ("Misc.FakeLag"), ("Misc_FakeLagFactor"));
		SetupValue(g_Options.Misc.Misc_AutoAccept, false, ("Misc"), ("Misc_AutoAccept"));
		SetupValue(g_Options.Misc.Misc_KnifeBot, false, ("Misc"), ("Misc_KnifeBot"));
		SetupValue(g_Options.Misc.Misc_Ranks, false, ("Misc"), ("Misc_Ranks"));
		SetupValue(g_Options.Misc.Misc_AutoJump, true, ("Misc"), ("Misc_AutoJump"));
		SetupValue(g_Options.Misc.Misc_AutoStrafe, false, ("Misc"), ("Misc_AutoStrafe"));
		SetupValue(g_Options.Misc.Misc_AutoStraferMode, 0, ("Misc"), ("Misc_AutoStraferMode"));
		SetupValue(g_Options.Misc.Misc_Fov, 0, ("Misc"), ("Misc_Fov"));
		SetupValue(g_Options.Misc.ViewModelFov, 68, ("Misc"), ("ViewModelFov"));
		SetupValue(g_Options.Misc.Visuals_ThirdPerson, false, ("Misc"), ("Visuals_ThirdPerson"));
		SetupValue(g_Options.Misc.Visuals_ThirdPersonAngle, 0, ("Misc"), ("Visuals_ThirdPersonAngle"));
		SetupValue(g_Options.Misc.Visuals_ThirdPersonKey, 0, ("Misc"), ("Visuals_ThirdPersonKey"));
		SetupValue(g_Options.Misc.Visuals_ThirdPersonDistance, 150, ("Misc"), ("Visuals_ThirdPersonDistance"));

		

		SetupValue(g_Options.Misc.SpectatorList, false, ("Misc"), ("SpectatorList"));
		SetupValue(g_Options.Menu.Animations, false, ("Menu"), ("Animations"));
		//SetupValue(g_Options.Menu.SkinChangerWindow, false, ("Menu"), ("SkinChangerWindow"));


		SetupValue(g_Options.NewLegitbot.Triggerbot.Enabled, false, ("Triggerbot"), ("Enabled"));
		SetupValue(g_Options.NewLegitbot.Triggerbot.AutoFire, false, ("Triggerbot"), ("AutoFire"));
		SetupValue(g_Options.NewLegitbot.Triggerbot.Key, 0, ("Triggerbot"), ("Key"));
		SetupValue(g_Options.NewLegitbot.Triggerbot.HitChance, false, ("Triggerbot"), ("HitChance"));
		SetupValue(g_Options.NewLegitbot.Triggerbot.HitChanceAmt, 0.f, ("Triggerbot"), ("HitChanceAmt"));
		SetupValue(g_Options.NewLegitbot.Triggerbot.Delay, 50, ("Triggerbot"), ("Delay"));
		SetupValue(g_Options.NewLegitbot.Triggerbot.Filter.Head, false, ("Triggerbot.Filter"), ("Head"));
		SetupValue(g_Options.NewLegitbot.Triggerbot.Filter.Chest, false, ("Triggerbot.Filter"), ("Chest"));
		SetupValue(g_Options.NewLegitbot.Triggerbot.Filter.Stomach, false, ("Triggerbot.Filter"), ("Stomach"));
		SetupValue(g_Options.NewLegitbot.Triggerbot.Filter.Arms, false, ("Triggerbot.Filter"), ("Arms"));
		SetupValue(g_Options.NewLegitbot.Triggerbot.Filter.Legs, false, ("Triggerbot.Filter"), ("Legs"));
		SetupValue(g_Options.NewLegitbot.Triggerbot.Filter.Friendly, false, ("Triggerbot.Filter"), ("Friendly"));


		SetupValue(g_Options.NewLegitbot.Aimbot.Enabled, false, ("Legit"), ("Legit.Enabled"));
		SetupValue(g_Options.NewLegitbot.Aimbot.AutoPistol, false, ("Legit"), ("Legit.AutoPistol"));
		SetupValue(g_Options.NewLegitbot.Aimbot.Key, 0, ("Legit"), ("Legit.Key"));
		SetupValue(g_Options.NewLegitbot.Aimbot.OnKey, false, ("Legit"), ("Legit.OnKey"));
		SetupValue(g_Options.NewLegitbot.Aimbot.DistanceBased, false, ("Legit"), ("Legit.DistanceBased"));
		SetupValue(g_Options.NewLegitbot.Aimbot.BackTracking, false, ("Legit"), ("Legit.BackTracking"));
		SetupValue(g_Options.NewLegitbot.Aimbot.BackTrackIng, 1.f, ("Legit"), ("Legit.BackTrackTicks"));
		SetupValue(g_Options.NewLegitbot.Aimbot.FriendlyFire, false, ("Legit"), ("Legit.FriendlyFire"));
		SetupValue(g_Options.NewLegitbot.Aimbot.SmokeCheck, false, ("Legit"), ("Legit.SmokeCheck"));
		SetupValue(g_Options.NewLegitbot.Aimbot.bKillDelay, false, ("Legit"), ("Legit.bKillDelay"));
		SetupValue(g_Options.NewLegitbot.Aimbot.iKillDelay, 0.3f, ("Legit"), ("Legit.iKillDelay"));
		SetupValue(g_Options.NewLegitbot.Aimbot.JumpCheck, false, ("Legit"), ("Legit.JumpCheck"));
		SetupValue(g_Options.NewLegitbot.Aimbot.FlashCheck, false, ("Legit"), ("Legit.FlashCheck"));
		SetupValue(g_Options.NewLegitbot.Aimbot.FlashCheckAlpha, 0.0f, ("Legit"), ("Legit.FlashCheckAlpha"));
		SetupValue(g_Options.NewLegitbot.Aimbot.FastZoom, false, ("Legit"), ("Legit.FastZoom"));
		SetupValue(g_Options.NewLegitbot.Aimbot.DrawFOV, false, ("Legit"), ("Legit.DrawFOV"));
		SetupValue(g_Options.NewLegitbot.Aimbot.RCSFix, false, ("Legit"), ("Legit.RCSFix"));
		
	

		
		for (int idNEW = 1; idNEW < 64; idNEW++)
		{
			if (idNEW == 5 || idNEW == 6 || idNEW == 12 || idNEW == 15 || idNEW == 18 || idNEW == 20 || idNEW == 21 || idNEW == 22 || idNEW == 23
				|| idNEW == 37 || idNEW == 41 || idNEW == 50 || idNEW == 51 || idNEW == 52 || idNEW == 53 || idNEW == 54 || idNEW == 55 || idNEW == 56 || idNEW == 57
				|| idNEW == 58)
				continue;
			SetupValue(g_Options.NewLegitbot.Weapon[idNEW].Bone, 0, GetCFGNameChanger(idNEW, 0), ("Legit.Bone"));
			SetupValue(g_Options.NewLegitbot.Weapon[idNEW].Enabled, false, GetCFGNameChanger(idNEW, 0), ("Legit.Enabled"));
			SetupValue(g_Options.NewLegitbot.Weapon[idNEW].EndBullet, 0, GetCFGNameChanger(idNEW, 0), ("Legit.EndBullet"));
			SetupValue(g_Options.NewLegitbot.Weapon[idNEW].Fov, 0.f, GetCFGNameChanger(idNEW, 0), ("Legit.Fov"));
			SetupValue(g_Options.NewLegitbot.Weapon[idNEW].Nearest, 0, GetCFGNameChanger(idNEW, 0), ("Legit.Nearest"));
			SetupValue(g_Options.NewLegitbot.Weapon[idNEW].pSilent, false, GetCFGNameChanger(idNEW, 0), ("Legit.pSilent"));
			SetupValue(g_Options.NewLegitbot.Weapon[idNEW].NearestRCS, false, GetCFGNameChanger(idNEW, 0), ("Legit.NearestRCS"));
			SetupValue(g_Options.NewLegitbot.Weapon[idNEW].pSilentFov, 0.f, GetCFGNameChanger(idNEW, 0), ("Legit.pSilentFov"));
			SetupValue(g_Options.NewLegitbot.Weapon[idNEW].pSilentHitChance, 0.f, GetCFGNameChanger(idNEW, 0), ("Legit.pSilentHitChance"));
			SetupValue(g_Options.NewLegitbot.Weapon[idNEW].RcsX, 1.f, GetCFGNameChanger(idNEW, 0), ("Legit.RcsX"));
			SetupValue(g_Options.NewLegitbot.Weapon[idNEW].RcsY, 1.f, GetCFGNameChanger(idNEW, 0), ("Legit.RcsY"));
			SetupValue(g_Options.NewLegitbot.Weapon[idNEW].Smooth, 0.f, GetCFGNameChanger(idNEW, 0), ("Legit.Smooth"));
			SetupValue(g_Options.NewLegitbot.Weapon[idNEW].StartBullet, 0, GetCFGNameChanger(idNEW, 0), ("Legit.StartBullet"));
			SetupValue(g_Options.NewLegitbot.Weapon[idNEW].EndBullet, 0, GetCFGNameChanger(idNEW, 0), ("Legit.EndBullet"));
			
			SetupValue(g_Options.NewLegitbot.Weapon[idNEW].Aimtype, 0, GetCFGNameChanger(idNEW, 0), ("Legit.Aimtype"));
			SetupValue(g_Options.NewLegitbot.Weapon[idNEW].SmoothType, 0, GetCFGNameChanger(idNEW, 0), ("Legit.SmoothType"));


		}



		
}
void CConfig::SetupValue(char &value, char def, std::string category, std::string name)
{
	value = def;
	chars.push_back(new ConfigValue<char>(category, name, &value));
}
void CConfig::SetupValue(int &value, int def, std::string category, std::string name)
{
	value = def;
	ints.push_back(new ConfigValue<int>(category, name, &value));
}

void CConfig::SetupValue(float &value, float def, std::string category, std::string name)
{
	value = def;
	floats.push_back(new ConfigValue<float>(category, name, &value));
}

void CConfig::SetupValue(bool &value, bool def, std::string category, std::string name)
{
	value = def;
	bools.push_back(new ConfigValue<bool>(category, name, &value));
}


#include <stdio.h>
void CConfig::Delete(CFGTYPE Type)
{
	static char path[MAX_PATH];
	std::string file;

	if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, path)))
	{
		char szCmd[256];
		if (Type == maincfg)
			sprintf(szCmd, "\\Lore Cheats\\Main\\%s.ini", g_Options.Misc.configname);
		else
			sprintf(szCmd, "\\Lore Cheats\\Skins\\%s.ini", g_Options.Misc.confignameskins);
		file = std::string(path) + szCmd;
	}

	DeleteFileA(file.c_str());

	
}
void CConfig::Rename(char* newname, CFGTYPE Type)
{
	static char path[MAX_PATH];
	std::string file, output;

	if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, path)))
	{
		char szCmd[256];
		if (Type == maincfg)
			sprintf(szCmd, "\\Lore Cheats\\Main\\%s.ini", g_Options.Misc.configname);
		else
			sprintf(szCmd, "\\Lore Cheats\\Skins\\%s.ini", g_Options.Misc.confignameskins);
		char szCmd2[256];
		if (Type == maincfg)
			sprintf(szCmd2, "\\Lore Cheats\\Main\\%s.ini", newname);
		else
			sprintf(szCmd2, "\\Lore Cheats\\Skins\\%s.ini", newname);

		file = std::string(path) + szCmd;
		output = std::string(path) + szCmd2;
	}

	std::rename(file.c_str(), output.c_str());

}
void CConfig::Save(CFGTYPE Type)
{
	static char path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, path)))
	{
		char szCmd[256];
		if (Type == maincfg)
		{
			sprintf(szCmd, "\\Lore Cheats\\Main\\%s.ini", g_Options.Misc.configname);
			folder = std::string(path) + ("\\Lore Cheats\\Main\\");
		}
		else
		{
			sprintf(szCmd, "\\Lore Cheats\\Skins\\%s.ini", g_Options.Misc.confignameskins);
			folder = std::string(path) + ("\\Lore Cheats\\Skins\\");
		}


		file = std::string(path) + szCmd;
	}

	CreateDirectoryA(folder.c_str(), NULL);

	for (auto value : ints)
		WritePrivateProfileStringA(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : floats)
		WritePrivateProfileStringA(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : bools)
		WritePrivateProfileStringA(value->category.c_str(), value->name.c_str(), *value->value ? "true" : "false", file.c_str());


}

void CConfig::Load(CFGTYPE Type)
{
	static char path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, path)))
	{
		char szCmd[256];
		if (Type == maincfg)
		{
			sprintf(szCmd, "\\Lore Cheats\\Main\\%s.ini", g_Options.Misc.configname);
			folder = std::string(path) + ("\\Lore Cheats\\Main\\");
		}
		else
		{
			sprintf(szCmd, "\\Lore Cheats\\Skins\\%s.ini", g_Options.Misc.confignameskins);
			folder = std::string(path) + ("\\Lore Cheats\\Skins\\");
		}
		file = std::string(path) + szCmd;
	}

	CreateDirectoryA(folder.c_str(), NULL);

	char value_l[32] = { '\0' };

	for (auto value : ints)
	{
		GetPrivateProfileStringA(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atoi(value_l);
	}

	for (auto value : floats)
	{
		GetPrivateProfileStringA(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atof(value_l);
	}

	for (auto value : bools)
	{
		GetPrivateProfileStringA(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = !strcmp(value_l, "true");
	}
}





CConfig* pConfig = new CConfig();
