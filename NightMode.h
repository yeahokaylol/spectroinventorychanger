
#include "stdafx.h"


void DoNightMode()
{
	static bool bPerformed = false, bLastSetting;

	ConVar* r_drawspecificstaticprop = Interfaces.g_ICVars->FindVar("r_drawspecificstaticprop");
	SpoofedConvar* r_drawspecificstaticprop_s = new SpoofedConvar(r_drawspecificstaticprop);
	r_drawspecificstaticprop_s->SetInt(0);

	ConVar* fog_override = Interfaces.g_ICVars->FindVar("fog_override");
	SpoofedConvar* fog_override_spoofed = new SpoofedConvar(fog_override);
	fog_override_spoofed->SetInt(1);

	ConVar* fog_enable = Interfaces.g_ICVars->FindVar("fog_enable");
	SpoofedConvar* fog_enable_spoofed = new SpoofedConvar(fog_enable);
	fog_enable_spoofed->SetInt(0);

	static ConVar* sv_skyname = Interfaces.g_ICVars->FindVar("sv_skyname");
	*(float*)((DWORD)&sv_skyname->m_fnChangeCallbacks + 0xC) = NULL;
	sv_skyname->m_nFlags &= ~FCVAR_CHEAT; // something something dont force convars


	if (!bPerformed)
	{
		for (auto i = Interfaces.pMaterialSystem->FirstMaterial(); i != Interfaces.pMaterialSystem->InvalidMaterial(); i = Interfaces.pMaterialSystem->NextMaterial(i))
		{
			IMaterial* pMaterial = Interfaces.pMaterialSystem->GetMaterial(i);

			if (!pMaterial || pMaterial->IsErrorMaterial())
				continue;

			if (bLastSetting)
			{
				if (strstr(pMaterial->GetTextureGroupName(), "Model")) {
					pMaterial->ColorModulate(0.60f, 0.60f, 0.60f);
				}

				if (strstr(pMaterial->GetTextureGroupName(), "World"))
				{
					//pMaterial->SetMaterialVarFlag(MATERIAL_VAR_TRANSLUCENT, false);
					sv_skyname->SetValue("sky_csgo_night02");
					pMaterial->ColorModulate(0.2f, 0.2f, 0.2f);
				}

				if (strstr(pMaterial->GetTextureGroupName(), "StaticProp"))
				{
					pMaterial->ColorModulate(0.3f, 0.3f, 0.3f);
				}
			}
			else
			{
				if (strstr(pMaterial->GetTextureGroupName(), "Model")) {
					pMaterial->ColorModulate(1.f, 1.f, 1.f);
				}
				if ((strstr(pMaterial->GetTextureGroupName(), "World")) || strstr(pMaterial->GetTextureGroupName(), "StaticProp"))
				{
					sv_skyname->SetValue("vertigoblue_hdr"); // braucht fix für default value vonner skybox
															 //pMaterial->SetMaterialVarFlag(MATERIAL_VAR_TRANSLUCENT, false);
					pMaterial->ColorModulate(1.f, 1.f, 1.f);
				}
			}

		}
		bPerformed = true;
	}
	if (bLastSetting != g_Options.Visuals.Visuals_NightMode)
	{
		bLastSetting = g_Options.Visuals.Visuals_NightMode;
		bPerformed = false;
	}
}
void DoAsusWalls()
{
	static bool bPerformed = false, bLastSetting;

	if (!bPerformed)
	{
		for (auto i = Interfaces.pMaterialSystem->FirstMaterial(); i != Interfaces.pMaterialSystem->InvalidMaterial(); i = Interfaces.pMaterialSystem->NextMaterial(i))
		{
			IMaterial* pMaterial = Interfaces.pMaterialSystem->GetMaterial(i);

			if (!pMaterial || pMaterial->IsErrorMaterial())
				continue;

			if (strstr(pMaterial->GetTextureGroupName(), "World") || (strstr(pMaterial->GetTextureGroupName(), "StaticProp")))
			{
				if (bLastSetting)
				{
					pMaterial->AlphaModulate(0.6f);
				}
				else
				{
					pMaterial->AlphaModulate(1.00f);
				}
			}
		}
		bPerformed = true;
	}
	if (bLastSetting != g_Options.Visuals.Visuals_Asus)
	{
		bLastSetting = g_Options.Visuals.Visuals_Asus;
		bPerformed = false;
	}


}
