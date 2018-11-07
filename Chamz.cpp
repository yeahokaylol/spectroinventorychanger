#include "stdafx.h"
#include "Global.h"
#include "Chams.h"


#define RGB_TO_CColor_ARRAY(_array, r, g, b) _array[0] = r / 255.0f; _array[1] = g / 255.0f; _array[2] = b / 255.0f;


void InitKeyValuesZ(KeyValues* keyValues, char* name)
{
	using InitKeyValuesFn = void(__thiscall*)(void* thisptr, const char* name);
	reinterpret_cast<InitKeyValuesFn>(offsets.InitKeyValuesEx)(keyValues, name);
}

void LoadFromBufferZ(KeyValues* pKeyValues, const char* resourceName, const char* pBuffer, void* pFileSystem = nullptr, const char* pPathID = NULL, void* pfnEvaluateSymbolProc = nullptr)
{
	typedef void(__thiscall* LoadFromBufferFn)(void* ths, const char* resourceName, const char* pBuffer, void* pFileSystem, const char* pPathID, void* pfnEvaluateSymbolProc);
	static LoadFromBufferFn LoadFromBufferEx = NULL;
	if (!LoadFromBufferEx)
	{
		//DWORD addr = (DWORD)Mem::FindPattern(("client_panorama.dll"), ("55 8B EC 83 EC 48 53 56 57 8B F9 89 7D F4"));
		DWORD addr = (DWORD)Utils.FindPatternIDA(("client_panorama.dll"), ("55 8B EC 83 E4 F8 83 EC 34 53 8B 5D 0C 89 4C 24 04"));
		LoadFromBufferEx = (LoadFromBufferFn)(addr);
	}

	LoadFromBufferEx(pKeyValues, resourceName, pBuffer, pFileSystem, pPathID, pfnEvaluateSymbolProc);
}
bool Filter(CBaseEntity *entity)
{
	if (!entity || !G::LocalPlayer) return true;
	int i = entity->GetIndex();
	if (entity->IsDormant() /*&& PlayerAlpha[i] == 0 && PlayerBoxAlpha[i] == 0.f && PlayerNickVal[i] == 0*/) return true;
	if (!entity->isAlive()) return true;
	if (entity->GetTeam() == G::LocalPlayer->GetTeam() && !g_Options.Visuals.Visuals_ChamsTeam) return true;
	if (entity->GetTeam() != 2 && entity->GetTeam() != 3) return true;
	if (entity == G::LocalPlayer && !Interfaces.pInput->m_fCameraInThirdPerson) return true;
	if (entity->GetClientClass()->m_ClassID != _CCSPlayer) return true;

	return false;
}

int created = 0;

namespace Chams
{
	bool clean = true;
	bool materialsCreated = false;
	bool enablePlayersDraw = true;

	IMaterial* ignorezLit = NULL;
	IMaterial* ignorezLitWireframe = NULL;
	IMaterial* lit = NULL;
	IMaterial* litWireframe = NULL;
	IMaterial* flat = NULL;
	IMaterial* ignorezFlat = NULL;
	IMaterial* cubeMap = NULL;
	IMaterial* cubeMapRed = NULL;

	IMaterial* matShowingEnemy = NULL;
	IMaterial* matHiddenEnemy = NULL;
	IMaterial* matShowingTeam = NULL;
	IMaterial* matHiddenTeam = NULL;
	IMaterial* matWeapon = NULL;
	IMaterial* matBlack = NULL;
	IMaterial* matWhite = NULL;

	float CColorHiddenEnemy[3], CColorHiddenTeam[3], CColorShowingEnemy[3], CColorShowingTeam[3], CColorShowingLocalPlayer[3];
	float CColorWhite[3], CColorDoctor[3], CColorBlack[3], CColorGlow[3];

	bool execute = true;
	bool dmeClean = true;
	bool frsClean = true;


	IMaterial* CreateMaterialChamsNew(bool shouldIgnoreZ, bool isLit, bool isWireframe, std::string matdata)
	{
		std::string type = (!isLit) ? ("UnlitGeneric") : ("VertexLitGeneric");

		//std::string matdata = "\"" + type + "\"\n{\n\t\"$basetexture\" \"vgui/white_additive\"\n\t\"$envmap\"  \"\"\n\t\"$model\" \"1\"\n\t\"$flat\" \"1\"\n\t\"$nocull\"  \"0\"\n\t\"$selfillum\" \"1\"\n\t\"$halflambert\" \"1\"\n\t\"$nofog\"  \"0\"\n\t\"$znearer\" \"0\"\n\t\"$wireframe\" \"" + std::to_string(isWireframe) + "\"\n\t\"$ignorez\" \"" + std::to_string(shouldIgnoreZ) + "\"\n}\n";

		if (matdata == "")
		{
			matdata += ("\"") + type + ("\"\n{\n");
			matdata += ("\t\"$basetexture\" \"vgui/white_additive\"\n");
			matdata += ("\t\"$envmap\" \"\"\n");
			matdata += ("\t\"$model\" \"1\"\n");
			matdata += ("\t\"$flat\" \"1\"\n");
			matdata += ("\t\"$nocull\" \"0\"\n");
			matdata += ("\t\"$selfillum\" \"1\"\n");
			matdata += ("\t\"$halflambert\" \"1\"\n");
			matdata += ("\t\"$znearer\" \"0\"\n");
			matdata += ("\t\"$wireframe\" \"") + std::to_string(isWireframe) + ("\"\n");
			matdata += ("\t\"$ignorez\" \"") + std::to_string(shouldIgnoreZ) + ("\"\n");
			matdata += ("}\n");
		}

		//printf(matdata.c_str());

		std::string matname = ("ctmlg_") + std::to_string(rand() % 30) + std::to_string(created) + (".vmt");
		++created;

		/*KeyValues* pKeyValues = new KeyValues(matname.c_str());
		InitKeyValues(pKeyValues, type.c_str());*/
		
		KeyValues* pKeyValues = static_cast< KeyValues* >(malloc(sizeof(KeyValues)));
		InitKeyValuesZ(pKeyValues, (char*)matname.c_str());
		LoadFromBufferZ(pKeyValues, matname.c_str(), matdata.c_str());


		IMaterial* createdMaterial = Interfaces.pMaterialSystem->CreateMaterial(matname.c_str(), pKeyValues);

		createdMaterial->IncrementReferenceCount();

		return createdMaterial;
	}

	void CreateMaterials()
	{
		if (materialsCreated)
			return;

		RGB_TO_CColor_ARRAY(CColorHiddenEnemy, 214, 255, 254);
		//	RGB_TO_CColor_ARRAY(CColorShowingEnemy, 0, 255, 242);
		RGB_TO_CColor_ARRAY(CColorShowingEnemy, 255, 67, 0);

		RGB_TO_CColor_ARRAY(CColorHiddenTeam, 255, 214, 246);
		RGB_TO_CColor_ARRAY(CColorShowingTeam, 175, 228, 255);
		RGB_TO_CColor_ARRAY(CColorShowingLocalPlayer, 255, 59, 0);

		RGB_TO_CColor_ARRAY(CColorWhite, 255, 255, 255);
		RGB_TO_CColor_ARRAY(CColorDoctor, 117, 164, 239);

		RGB_TO_CColor_ARRAY(CColorBlack, 0, 0, 0);

		RGB_TO_CColor_ARRAY(CColorGlow, 150, 0, 0);

		ignorezLit = CreateMaterialChamsNew(true, true, false);
		ignorezLitWireframe = CreateMaterialChamsNew(true, true, true);
		lit = CreateMaterialChamsNew(false, true, false);
		litWireframe = CreateMaterialChamsNew(false, true, true);
		flat = CreateMaterialChamsNew(false, false, false);
		ignorezFlat = CreateMaterialChamsNew(true, false, false);

		matShowingEnemy = CreateMaterialChamsNew(false, true, false);
		matHiddenEnemy = CreateMaterialChamsNew(true, true, false);
		matShowingTeam = CreateMaterialChamsNew(false, true, false);
		matHiddenTeam = CreateMaterialChamsNew(true, true, false);
		matWeapon = CreateMaterialChamsNew(false, true, false);
		matBlack = CreateMaterialChamsNew(false, true, false);
		matWhite = CreateMaterialChamsNew(false, true, false);

		{
			string matdata = "";
			matdata += ("\"UnlitGeneric\"\n{\n");
			matdata += ("\t\"$envmap\"     \"editor/cube_vertigo\"\n");
			matdata += ("\t\"$envmaptint\" \"[1 1 1]\"\n");
			matdata += ("\t\"$model\"      \"1\"\n");
			matdata += ("\t\"$additive\"   \"1\"\n");
			matdata += ("}");

			cubeMap = CreateMaterialChamsNew(false, true, false, matdata);
		}

		{
			string matdata = "";
			matdata += ("\"UnlitGeneric\"\n{\n");
			matdata += ("\t\"$envmap\"     \"editor/cube_vertigo\"\n");
			matdata += ("\t\"$envmaptint\" \"[0.9 0.9 0.9]\"\n");
			matdata += ("\t\"$model\"      \"1\"\n");
			matdata += ("\t\"$additive\"   \"1\"\n");
			matdata += ("}");

			cubeMapRed = CreateMaterialChamsNew(false, true, false, matdata);
		}

		materialsCreated = true;
	}


	void DrawCColoredModel(DrawModelParams p, IMaterial *pMaterialHidden, IMaterial *pMaterialShowing, CColor CColorHidden, CColor CColorShowing)
	{
		if (pMaterialHidden)
		{
			pMaterialHidden->ColorModulate(CColorHidden.r() / 255.f, CColorHidden.g() / 255.f, CColorHidden.b() / 255.f);
			pMaterialHidden->AlphaModulate(CColorHidden.a() / 255.f);

			Interfaces.g_pModelRender->ForcedMaterialOverride(pMaterialHidden);

			p.oDrawModel(p._this, p.results, p.info, p.pBoneToWorld, p.pFlexWeights, p.pFlexDelayedWeights, p.origin, p.drawFlags);
		}

		if (pMaterialShowing)
		{
			pMaterialShowing->ColorModulate(CColorShowing.r() / 255.f, CColorShowing.g() / 255.f, CColorShowing.b() / 255.f);
			pMaterialShowing->AlphaModulate(CColorShowing.a() / 255.f);

			Interfaces.g_pModelRender->ForcedMaterialOverride(pMaterialShowing);

			p.oDrawModel(p._this, p.results, p.info, p.pBoneToWorld, p.pFlexWeights, p.pFlexDelayedWeights, p.origin, p.drawFlags);
		}
	}

	void DrawCColoredModel(CBaseEntity *entity, IMaterial *pMaterialHidden, IMaterial *pMaterialShowing, CColor CColorHidden, CColor CColorShowing)
	{
		if (pMaterialHidden)
		{
			pMaterialHidden->ColorModulate(CColorHidden.r() / 255.f, CColorHidden.g() / 255.f, CColorHidden.b() / 255.f);
			pMaterialHidden->AlphaModulate(CColorHidden.a() / 255.f);

			Interfaces.g_pModelRender->ForcedMaterialOverride(pMaterialHidden);

			entity->DrawModelChams(0x1, CColorHidden.a());
		}

		if (pMaterialShowing)
		{
			pMaterialShowing->ColorModulate(CColorShowing.r() / 255.f, CColorShowing.g() / 255.f, CColorShowing.b() / 255.f);
			pMaterialShowing->AlphaModulate(CColorShowing.a() / 255.f);

			Interfaces.g_pModelRender->ForcedMaterialOverride(pMaterialShowing);

			entity->DrawModelChams(0x1, CColorShowing.a());
		}
	}

	bool DrawModel(DrawModel_t oDrawModel, void *_this, void* results, DrawModelInfo_t& info, matrix3x4* pBoneToWorld, float* pFlexWeights, float* pFlexDelayedWeights, Vector& origin, int drawFlags)
	{
		DrawModelParams p = DrawModelParams{ oDrawModel, (DWORD*)_this, (DWORD*)results, info, pBoneToWorld, pFlexWeights, pFlexDelayedWeights, origin, drawFlags };

		if (!execute)
		{
			dmeClean = true;
			return false;
		}

		dmeClean = false;

		CreateMaterials();

		CBaseEntity *entity = (CBaseEntity*)((DWORD)info.m_pClientEntity - 4);
		CBaseEntity *pLocal = G::LocalPlayer;
		studiohdr_t* hdr = info.m_pStudioHdr;

		if (!entity || !hdr || !pLocal)
			return false;

		string modelName = hdr->name;

		if (modelName.find(("shadow")) != -1)
			return false;

		if (modelName.find(("player")) != -1 )
		{
			if (entity->EntIndex() > Interfaces.pEngine->GetMaxClients())//(entity->EntIndex() > Interfaces.pEngine->GetMaxClients())
			{
				if (entity == pLocal)
				{
					if (pLocal->isAlive())
					{
						if (G::LocalPlayer->m_bIsScoped())
						{
							DrawCColoredModel(p, ignorezLit, lit, CColor(0, 0, 0, 0), CColor(255, 255, 255, 50));
						}
						else if (g_Options.Visuals.Visuals_GhostAngle)
						{
							DrawCColoredModel(p, ignorezLit, lit, CColor(0, 0, 0, 0), CColor(255, 0, 255, 255));
						}

						if (g_Options.Visuals.Visuals_GhostAngle)
						{
							Interfaces.g_pModelRender->ForcedMaterialOverride(lit);
							lit->ColorModulate(Hacks.Colors.FakeAngleChams.r() / 255.f, Hacks.Colors.FakeAngleChams.g() / 255.f, Hacks.Colors.FakeAngleChams.b() / 255.f);
							p.oDrawModel(p._this, p.results, p.info, G::localPlayerLbyBones, p.pFlexWeights, p.pFlexDelayedWeights, p.origin, p.drawFlags);
						}

						return G::LocalPlayer->m_bIsScoped() || g_Options.Visuals.Visuals_GhostAngle;
					}

				}
			}
		
		}
		return false;
	}



};
