#include "BulletTracers.h"
#include "stdafx.h"
CBulletTracer* g_pBulletTracer = new CBulletTracer();



void CBulletTracer::Main()
{
//	if (!Vars.Visuals.bBulletImpacts)
//		return;

	//if the player is not ingame, clear the shots
	if (!Interfaces.pEngine->IsInGame() || !Interfaces.pEngine->IsConnected() || !G::LocalPlayer || !g_Options.Visuals.Visuals_DrawBeams)
	{
		if(Impacts.size())
		Impacts.clear();
		return;
	}

	if (Impacts.size() > 30)
		Impacts.pop_back();

	for (size_t i = 0; i < Impacts.size(); i++)
	{
		auto current = Impacts.at(i);

		if (!current.pPlayer)
			continue;
		if(current.pPlayer != G::LocalPlayer)
			continue;
		

		if (current.pPlayer == G::LocalPlayer)
			current.color = Color(Hacks.Colors.Beams.r(), Hacks.Colors.Beams.g(), Hacks.Colors.Beams.b()); //color of local player's tracers

		BeamInfo_t beamInfo;
		beamInfo.m_nType = TE_BEAMPOINTS;
		beamInfo.m_pszModelName = "sprites/physbeam.vmt";
		beamInfo.m_nModelIndex = -1;
		beamInfo.m_flHaloScale = 0.0f;
		beamInfo.m_flLife = g_Options.Visuals.Visuals_DrawBeamsDuration; //duration of tracers
		beamInfo.m_flWidth = g_Options.Visuals.Visuals_DrawBeamsSize; //start width
		beamInfo.m_flEndWidth = g_Options.Visuals.Visuals_DrawBeamsSize; //end width
		beamInfo.m_flFadeLength = 0.0f;
		beamInfo.m_flAmplitude = 2.0f;
		beamInfo.m_flBrightness = 255.f;
		beamInfo.m_flSpeed = 0.2f;
		beamInfo.m_nStartFrame = 0;
		beamInfo.m_flFrameRate = 0.f;
		beamInfo.m_flRed = current.color.r();
		beamInfo.m_flGreen = current.color.g();
		beamInfo.m_flBlue = current.color.b();
		beamInfo.m_nSegments = 2;
		beamInfo.m_bRenderable = true;
		beamInfo.m_nFlags = FBEAM_ONLYNOISEONCE | FBEAM_NOTILE | FBEAM_HALOBEAM;

		beamInfo.m_vecStart = current.pPlayer->GetEyePosition();
		beamInfo.m_vecEnd = current.vecImpactPos;

		auto beam = Interfaces.g_pBeams->CreateBeamPoints(beamInfo);
		if (beam)
			Interfaces.g_pBeams->DrawBeam(beam);

	//	Interfaces.g_pDebugOverlay->AddBoxOverlay(current.vecImpactPos, Vector(-2, -2, -2), Vector(2, 2, 2), Vector(0, 0, 0), current.color.r(), current.color.g(), current.color.b(), 125, 0.8f);

		Impacts.erase(Impacts.begin() + i);
	}
}