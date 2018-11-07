#include "stdafx.h"
#include "SkinChanger-KentMeister.h"
#include <unordered_map>
#include <random>

#define INVALID_EHANDLE_INDEX	0xFFFFFFFF
#define RandomIntZ(min, max) (rand() % (max - min + 1) + min)

CSkinchanger* g_Skinchanger = new CSkinchanger;

void CSkinchanger::ForceItemUpdates()
{
	typedef void(*CL_FullUpdate_t) (void);
	static CL_FullUpdate_t cl_fullupdate = (CL_FullUpdate_t)(offsets.IDA_FullUpdate);
	cl_fullupdate();
}
void CSkinchanger::UpdateModels()
{
	//Knifes
	this->Knifes.knife_default_ct = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_default_ct.mdl");
	this->Knifes.knife_default_t = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_default_t.mdl");
	this->Knifes.knife_karam = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_karam.mdl");
	this->Knifes.knife_bayonet = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_bayonet.mdl");
	this->Knifes.knife_m9_bay = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_m9_bay.mdl");
	this->Knifes.knife_tactical = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_tactical.mdl");
	this->Knifes.knife_gut = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_gut.mdl");
	this->Knifes.knife_falchion_advanced = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_falchion_advanced.mdl");
	this->Knifes.knife_push = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_push.mdl");
	this->Knifes.knife_butterfly = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_butterfly.mdl");
	this->Knifes.knife_flip = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_flip.mdl");
	this->Knifes.knife_survival_bowie = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_survival_bowie.mdl");
	this->Knifes.knife_navaja = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_gypsy_jackknife.mdl");
	this->Knifes.knife_stiletto = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_stiletto.mdl");
	this->Knifes.knife_ursus = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_ursus.mdl");
	this->Knifes.knife_talon = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_widowmaker.mdl");
	//Gloves
	this->Gloves.glove_bloodhound = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl");
	this->Gloves.glove_sporty = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_bloodhound/v_glove_sporty.mdl");
	this->Gloves.glove_slick = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_bloodhound/v_glove_slick.mdl");
	this->Gloves.glove_handwrap_leathery = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_bloodhound/v_glove_handwrap_leathery.mdl");
	this->Gloves.glove_motorcycle = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_bloodhound/v_glove_motorcycle.mdl");
	this->Gloves.glove_specialist = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_bloodhound/v_glove_specialist.mdl");
	this->Gloves.glove_hydra = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound_hydra.mdl");


	
}
int CSkinchanger::GetModelByIndex(int item_def_index)
{
	switch (item_def_index)
	{
	case WEAPON_KNIFE:return this->Knifes.knife_default_ct; break;
	case WEAPON_KNIFE_T:return this->Knifes.knife_default_t; break;
	case WEAPON_KNIFE_KARAMBIT:return this->Knifes.knife_karam; break;
	case WEAPON_KNIFE_BAYONET:return this->Knifes.knife_bayonet; break;
	case WEAPON_KNIFE_M9_BAYONET:return this->Knifes.knife_m9_bay; break;
	case WEAPON_KNIFE_TACTICAL:return this->Knifes.knife_tactical; break;
	case WEAPON_KNIFE_GUT:return this->Knifes.knife_gut; break;
	case WEAPON_KNIFE_FALCHION:return this->Knifes.knife_falchion_advanced; break;
	case WEAPON_KNIFE_PUSH:return this->Knifes.knife_push; break;
	case WEAPON_KNIFE_BUTTERFLY:return this->Knifes.knife_butterfly; break;
	case WEAPON_KNIFE_FLIP:return this->Knifes.knife_flip; break;
	case WEAPON_KNIFE_SURVIVAL_BOWIE:return this->Knifes.knife_survival_bowie; break;
	case WEAPON_KNIFE_NAVAJA:return this->Knifes.knife_navaja; break;
	case WEAPON_KNIFE_STILETTO:return this->Knifes.knife_stiletto; break;
	case WEAPON_KNIFE_URSUS:return this->Knifes.knife_ursus; break;
	case WEAPON_KNIFE_TALON:return this->Knifes.knife_talon; break;
	default:return 0; break;
	}
}

int knifeItemIndex(int MenuVar, int team)
{
	switch (MenuVar)
	{
	case 0:
	default:
		switch (team)
		{
		default:
		case 2:return WEAPON_KNIFE_T; break;
		case 3:return WEAPON_KNIFE; break;
		}break;
	case 1: return WEAPON_KNIFE_KARAMBIT; break;
	case 2: return WEAPON_KNIFE_BAYONET; break;
	case 3: return WEAPON_KNIFE_M9_BAYONET; break;
	case 4: return WEAPON_KNIFE_TACTICAL; break;
	case 5: return WEAPON_KNIFE_GUT; break;
	case 6: return WEAPON_KNIFE_FALCHION; break;
	case 7: return WEAPON_KNIFE_PUSH; break;
	case 8: return WEAPON_KNIFE_BUTTERFLY; break;
	case 9: return WEAPON_KNIFE_FLIP; break;
	case 10: return WEAPON_KNIFE_SURVIVAL_BOWIE; break;
	case 11: return WEAPON_KNIFE_NAVAJA; break;
	case 12: return WEAPON_KNIFE_STILETTO; break;
	case 13: return WEAPON_KNIFE_URSUS; break;
	case 14: return WEAPON_KNIFE_TALON; break;
	}
}

void CSkinchanger::CreateMove()
{
		if (!G::LocalPlayer)return;
		player_info_t localplayer_info;
		if (Interfaces.pEngine->GetPlayerInfo(Interfaces.pEngine->GetLocalPlayer(), &localplayer_info))
		{
			if (g_Options.Skinchanger.glovemodel > 0)
			{
				this->GloveChanger(localplayer_info);
			}

			CBaseHandle* hWeapons = G::LocalPlayer->GetWeaponsZ();
			if (hWeapons)
			{
				for (CBaseHandle i = 0; hWeapons[i] != INVALID_EHANDLE_INDEX; i++)
				{
					CBaseAttributableItem* weapon = (CBaseAttributableItem*)Interfaces.pEntList->GetClientEntityFromHandle(hWeapons[i]);
					if (!weapon)
						continue;
					if(*weapon->GetItemDefinitionIndex() < 1)
						continue;

					*weapon->GetItemIDHigh() = -1;
					*weapon->GetAccountID() = localplayer_info.xuidlow;
					if (weapon->IsKnife())
					{
						*weapon->GetItemDefinitionIndex() = knifeItemIndex(g_Options.Skinchanger.knifemodel, G::LocalPlayer->GetTeam());
						auto WeaponIDMEME = *weapon->GetItemDefinitionIndex();

						*(int*)((DWORD)weapon + offsets.m_nModeIndex) = this->GetModelByIndex(WeaponIDMEME);

						auto WorldModel = weapon->GetWorldModel();
						if (WorldModel)
						{
							CBaseAttributableItem *pWorldModel = (CBaseAttributableItem*)Interfaces.pEntList->GetClientEntityFromHandle(WorldModel);
							if (pWorldModel)
							{
								pWorldModel->SetModelIndex(this->GetModelByIndex(WeaponIDMEME) + 1);
							}
						}
					}


					this->ApplyCustomSkin(weapon, localplayer_info);
					this->ApplyStickerHooks(weapon);
				}
			}
		}
	
}


RecvVarProxyFn oRecvnModelIndex;
void ViewModel_Index_Proxy(CRecvProxyData *pDataConst, void *pStruct, void *pOut)
{
	// Get local player (just to stop replacing spectators knifes)
	if (G::LocalPlayer && g_Options.Skinchanger.EnabledChanger && Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected())
	{

		// If we are alive and holding a default knife(if we already have a knife don't worry about changing)
		if (G::LocalPlayer->isAlive() && (
			pDataConst->m_Value.m_Int == g_Skinchanger->Knifes.knife_default_t ||
			pDataConst->m_Value.m_Int == g_Skinchanger->Knifes.knife_default_ct ||
			pDataConst->m_Value.m_Int == g_Skinchanger->Knifes.knife_bayonet ||
			pDataConst->m_Value.m_Int == g_Skinchanger->Knifes.knife_butterfly ||
			pDataConst->m_Value.m_Int == g_Skinchanger->Knifes.knife_flip ||
			pDataConst->m_Value.m_Int == g_Skinchanger->Knifes.knife_gut ||
			pDataConst->m_Value.m_Int == g_Skinchanger->Knifes.knife_karam ||
			pDataConst->m_Value.m_Int == g_Skinchanger->Knifes.knife_m9_bay ||
			pDataConst->m_Value.m_Int == g_Skinchanger->Knifes.knife_tactical ||
			pDataConst->m_Value.m_Int == g_Skinchanger->Knifes.knife_falchion_advanced ||
			pDataConst->m_Value.m_Int == g_Skinchanger->Knifes.knife_push ||
			pDataConst->m_Value.m_Int == g_Skinchanger->Knifes.knife_survival_bowie ||
			pDataConst->m_Value.m_Int == g_Skinchanger->Knifes.knife_navaja ||
			pDataConst->m_Value.m_Int == g_Skinchanger->Knifes.knife_stiletto ||
			pDataConst->m_Value.m_Int == g_Skinchanger->Knifes.knife_ursus ||
			pDataConst->m_Value.m_Int == g_Skinchanger->Knifes.knife_talon) && g_Options.Skinchanger.knifemodel > 0)
		{
			// Set whatever knife we want
			switch (g_Options.Skinchanger.knifemodel)
			{
			case 0:
				pDataConst->m_Value.m_Int = G::LocalPlayer->GetTeam() == 2 ? g_Skinchanger->Knifes.knife_default_t : g_Skinchanger->Knifes.knife_default_ct;
				break; case 1: {
					pDataConst->m_Value.m_Int = g_Skinchanger->Knifes.knife_karam;
				}
				break; case 2: {
					pDataConst->m_Value.m_Int = g_Skinchanger->Knifes.knife_bayonet;
				}
				break; case 3: {
					pDataConst->m_Value.m_Int = g_Skinchanger->Knifes.knife_m9_bay;
				}
				break; case 4: {
					pDataConst->m_Value.m_Int = g_Skinchanger->Knifes.knife_tactical;
				}
				break; case 5: {
					pDataConst->m_Value.m_Int = g_Skinchanger->Knifes.knife_gut;
				}
				break; case 6: {
					pDataConst->m_Value.m_Int = g_Skinchanger->Knifes.knife_falchion_advanced;
				}
				break; case 7: {
					pDataConst->m_Value.m_Int = g_Skinchanger->Knifes.knife_push;
				}
				break; case 8: {
					pDataConst->m_Value.m_Int = g_Skinchanger->Knifes.knife_butterfly;
				}
				break; case 9: {
					pDataConst->m_Value.m_Int = g_Skinchanger->Knifes.knife_flip;
				}
				break; case 10: {
					pDataConst->m_Value.m_Int = g_Skinchanger->Knifes.knife_survival_bowie;
				}
				break; case 11: {
					pDataConst->m_Value.m_Int = g_Skinchanger->Knifes.knife_navaja;
				}
				break; case 12: {
					pDataConst->m_Value.m_Int = g_Skinchanger->Knifes.knife_stiletto;
				}
				break; case 13: {
					pDataConst->m_Value.m_Int = g_Skinchanger->Knifes.knife_ursus;
				}
				break; case 14: {
					pDataConst->m_Value.m_Int = g_Skinchanger->Knifes.knife_talon;
				}
			}
		}
	}

	// Carry on the to original proxy
	oRecvnModelIndex(pDataConst, pStruct, pOut);

}

bool CSkinchanger::ApplyCustomSkin(CBaseAttributableItem* attrib_item, player_info_t pInfo) {
	if (attrib_item)
	{
		int nWeaponIndex = *attrib_item->GetItemDefinitionIndex();
		if (g_Options.Skinchanger.SkinMaster[nWeaponIndex].PaintKit > 0)
			*attrib_item->GetFallbackPaintKit() = g_Options.Skinchanger.SkinMaster[nWeaponIndex].PaintKit;
		*attrib_item->GetFallbackSeed() = g_Options.Skinchanger.SkinMaster[nWeaponIndex].Seed;
		if (((CBaseCombatWeapon*)attrib_item)->IsKnife())
			if (g_Options.Skinchanger.knifemodel > 0)
				*attrib_item->GetEntityQuality() = 3;
			else
				*attrib_item->GetEntityQuality() = 1;
		else
			*attrib_item->GetEntityQuality() = g_Options.Skinchanger.SkinMaster[nWeaponIndex].Stattrak ? 4 : 0;
		if (g_Options.Skinchanger.SkinMaster[nWeaponIndex].Stattrak)
			*attrib_item->GetFallbackStatTrak() = g_Options.Skinchanger.SkinMaster[nWeaponIndex].StattrakValue;
		else
			*attrib_item->GetFallbackStatTrak() = -1;
		if (g_Options.Skinchanger.SkinMaster[nWeaponIndex].Wear == 0.f)
			*attrib_item->GetFallbackWear() = 0.00000001f;
		else
		{
			if (g_Options.Skinchanger.SkinMaster[nWeaponIndex].Wear >= 100.f)
				*attrib_item->GetFallbackWear() = 1.f;
			else
				*attrib_item->GetFallbackWear() = g_Options.Skinchanger.SkinMaster[nWeaponIndex].Wear / 100;
		}
		return true;
	}
	else return false;
}







int GetGloveSkinByMenu(int gloveIndex, int skinIndex)
{
	if (gloveIndex == 0) // bloudhound
	{
		switch (skinIndex)
		{
		case 0:
			return 10006; break;
		case 1:
			return 10007; break;
		case 2:
			return 10008; break;
		case 3:
			return 10039; break;
		default:
			return 0; break;
		}
	}
	else if (gloveIndex == 1) // Sport
	{
		switch (skinIndex)
		{
		case 0:
			return 10038; break;
		case 1:
			return 10037; break;
		case 2:
			return 10018; break;
		case 3:
			return 10019; break;
		case 4:
			return 10048; break;
		case 5:
			return 10047; break;
		case 6:
			return 10045; break;
		case 7:
			return 10046; break;
		default:
			return 0; break;
		}
	}
	else if (gloveIndex == 2) // Driver
	{
		switch (skinIndex)
		{
		case 0:
			return 10013; break;
		case 1:
			return 10015; break;
		case 2:
			return 10016; break;
		case 3:
			return 10040; break;
		case 4:
			return 10043; break;
		case 5:
			return 10044; break;
		case 6:
			return 10041; break;
		case 7:
			return 10042; break;
		default:
			return 0; break;
		}
	}
	else if (gloveIndex == 3) // Wraps
	{
		switch (skinIndex)
		{
		case 0:
			return 10009; break;
		case 1:
			return 10010; break;
		case 2:
			return 10021; break;
		case 3:
			return 10036; break;
		case 4:
			return 10053; break;
		case 5:
			return 10054; break;
		case 6:
			return 10055; break;
		case 7:
			return 10056; break;
		default:
			return 0; break;
		}
	}
	else if (gloveIndex == 4) // Moto
	{
		switch (skinIndex)
		{
		case 0:
			return 10024; break;
		case 1:
			return 10026; break;
		case 2:
			return 10027; break;
		case 3:
			return 10028; break;
		case 4:
			return 10050; break;
		case 5:
			return 10051; break;
		case 6:
			return 10052; break;
		case 7:
			return 10049; break;
		default:
			return 0; break;
		}
	}
	else if (gloveIndex == 5) // Specialist
	{
		switch (skinIndex)
		{
		case 0:
			return 10030; break;
		case 1:
			return 10033; break;
		case 2:
			return 10034; break;
		case 3:
			return 10035; break;
		case 4:
			return 10061; break;
		case 5:
			return 10062; break;
		case 6:
			return 10063; break;
		case 7:
			return 10064; break;
		default:
			return 0; break;
		}
	}
	else if (gloveIndex == 6) // HYDRA
	{
		switch (skinIndex)
		{
		case 0:
			return 10057; break;
		case 1:
			return 10058; break;
		case 2:
			return 10059; break;
		case 3:
			return 10060; break;
		default:
			return 0; break;
		}
	}
	else
		return 0;
}
int GetGloveIndexByMenu(int gloveIndexinmenu)
{
	switch (gloveIndexinmenu)
	{
	case 0: default: return 0; break;
	case 1: return 5027; break;
	case 2: return 5030; break;
	case 3: return 5031; break;
	case 4: return 5032; break;
	case 5: return 5033; break;
	case 6: return 5034; break;
	case 7: return 5035; break;
	}
}

int CSkinchanger::GetGloveModelIndexByMenu(int gloveIndexinmenu)
{
	switch (gloveIndexinmenu)
	{

	default:
	case 0:
		return NULL; break;
	case 1:return this->Gloves.glove_bloodhound; break;
	case 2:return this->Gloves.glove_sporty; break;
	case 3:return this->Gloves.glove_slick; break;
	case 4:return this->Gloves.glove_handwrap_leathery; break;
	case 5:return this->Gloves.glove_motorcycle; break;
	case 6:return this->Gloves.glove_specialist; break;
	case 7:return this->Gloves.glove_hydra; break;

	}
}

void CSkinchanger::GloveChanger(player_info_t pInfo)
{
	static bool glovesUpdated = false;
	if (!Interfaces.pEntList->GetClientEntityFromHandle(*G::LocalPlayer->GetWearables()))
	{
		for (ClientClass *pClass = Interfaces.pClient->GetAllClasses(); pClass; pClass = pClass->m_pNext)
		{
			if (pClass->m_ClassID != 45)
				continue;

			int entry = (Interfaces.pEntList->GetHighestEntityIndex() + 1), serial = RandomIntZ(0x0, 0xFFF);
			pClass->m_pCreateFn(entry, serial);
			G::LocalPlayer->GetWearables()[0] = entry | (serial << 16);
			glovesUpdated = true;

			break;
		}
	}
	CBaseAttributableItem* glove = (CBaseAttributableItem*)Interfaces.pEntList->GetClientEntity(G::LocalPlayer->GetWearables()[0] & 0xFFF);
	
	if (glove && glovesUpdated)
	{
		*glove->GetItemIDHigh() = -1;
		*glove->GetFallbackStatTrak() = -1;
		*glove->GetItemDefinitionIndex() = GetGloveIndexByMenu(g_Options.Skinchanger.glovemodel);
		*glove->GetFallbackPaintKit() = GetGloveSkinByMenu(g_Options.Skinchanger.glovemodel - 1, g_Options.Skinchanger.gloveskin);
		*glove->GetFallbackWear() = 0.00000001f;
		*glove->GetFallbackSeed() = 0;
		glove->SetModelIndex(this->GetGloveModelIndexByMenu(g_Options.Skinchanger.glovemodel));
		glove->PreDataUpdate(0);
		glovesUpdated = false;
	}
}










enum class EStickerAttributeType
{
	Index,
	Wear,
	Scale,
	Rotation
};
DWORD dwEconItemInterfaceWrapper = 0;

typedef float(__thiscall* GetStickerAttributeBySlotIndexFloatFn)(void*, int, EStickerAttributeType, float);
GetStickerAttributeBySlotIndexFloatFn oGetStickerAttributeBySlotIndexFloat;
float __fastcall Hooked_GetStickerAttributeBySlotIndexFloat(void* thisptr, void* edx, int iSlot, EStickerAttributeType iAttribute, float flUnknown)
{
	auto pItem = reinterpret_cast<CBaseAttributableItem*>(DWORD(thisptr) - dwEconItemInterfaceWrapper);
	if (!pItem)
		return oGetStickerAttributeBySlotIndexFloat(thisptr, iSlot, iAttribute, flUnknown);

	int iID = *pItem->GetItemDefinitionIndex();
	if (!g_Options.Skinchanger.SkinMaster[iID].StickersEnabled)
		return oGetStickerAttributeBySlotIndexFloat(thisptr, iSlot, iAttribute, flUnknown);

	switch (iAttribute)
	{
	case EStickerAttributeType::Wear:
		return min(1.f, g_Options.Skinchanger.SkinMaster[iID].Stickers[iSlot].flWear + 0.0000000001f);
	case EStickerAttributeType::Scale:
		return g_Options.Skinchanger.SkinMaster[iID].Stickers[iSlot].flScale;
	case EStickerAttributeType::Rotation:
		return g_Options.Skinchanger.SkinMaster[iID].Stickers[iSlot].iRotation;
	default:
		break;
	}

	return oGetStickerAttributeBySlotIndexFloat(thisptr, iSlot, iAttribute, flUnknown);
}

typedef UINT(__thiscall* GetStickerAttributeBySlotIndexIntFn)(void*, int, EStickerAttributeType, float);
GetStickerAttributeBySlotIndexIntFn oGetStickerAttributeBySlotIndexInt;
UINT __fastcall Hooked_GetStickerAttributeBySlotIndexInt(void* thisptr, void* edx, int iSlot, EStickerAttributeType iAttribute, UINT iUnknown)
{
	auto pItem = reinterpret_cast<CBaseAttributableItem*>(DWORD(thisptr) - dwEconItemInterfaceWrapper);
	if (!pItem)
		return oGetStickerAttributeBySlotIndexInt(thisptr, iSlot, iAttribute, iUnknown);

	int iID = *pItem->GetItemDefinitionIndex();
	if (!g_Options.Skinchanger.SkinMaster[iID].StickersEnabled)
		return oGetStickerAttributeBySlotIndexInt(thisptr, iSlot, iAttribute, iUnknown);

	return g_Options.Skinchanger.SkinMaster[iID].Stickers[iSlot].iID;
	// return Parser::Stickers.List[g_Weapons[iID].Stickers[iSlot].iID].iID; //
}
bool IsCodePtr(void* ptr)
{
	constexpr const DWORD protect_flags = PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY;

	MEMORY_BASIC_INFORMATION out;
	VirtualQuery(ptr, &out, sizeof out);

	return out.Type
		&& !(out.Protect & (PAGE_GUARD | PAGE_NOACCESS))
		&& out.Protect & protect_flags;
}
void CSkinchanger::ApplyStickerHooks(CBaseAttributableItem* attrib_item)
{
	if (!dwEconItemInterfaceWrapper)
		dwEconItemInterfaceWrapper = 0x2DB0 + 0xC;

	void**& vmt = *reinterpret_cast<void***>(DWORD(attrib_item) + dwEconItemInterfaceWrapper);

	static void** hooked_vmt = nullptr;
	if (!hooked_vmt)
	{
		size_t size = 0;

		while (IsCodePtr(vmt[size]))
			++size;

		hooked_vmt = new void*[size];
		memcpy(hooked_vmt, vmt, size * sizeof(void*));

		oGetStickerAttributeBySlotIndexFloat = (GetStickerAttributeBySlotIndexFloatFn)hooked_vmt[4];
		hooked_vmt[4] = reinterpret_cast<void*>(&Hooked_GetStickerAttributeBySlotIndexFloat);

		oGetStickerAttributeBySlotIndexInt = (GetStickerAttributeBySlotIndexIntFn)hooked_vmt[5];
		hooked_vmt[5] = reinterpret_cast<void*>(&Hooked_GetStickerAttributeBySlotIndexInt);
	}
	vmt = hooked_vmt;
}


#define SEQUENCE_DEFAULT_DRAW 0
#define SEQUENCE_DEFAULT_IDLE1 1
#define SEQUENCE_DEFAULT_IDLE2 2
#define SEQUENCE_DEFAULT_LIGHT_MISS1 3
#define SEQUENCE_DEFAULT_LIGHT_MISS2 4
#define SEQUENCE_DEFAULT_HEAVY_MISS1 9
#define SEQUENCE_DEFAULT_HEAVY_HIT1 10
#define SEQUENCE_DEFAULT_HEAVY_BACKSTAB 11
#define SEQUENCE_DEFAULT_LOOKAT01 12

#define SEQUENCE_BUTTERFLY_DRAW 0
#define SEQUENCE_BUTTERFLY_DRAW2 1
#define SEQUENCE_BUTTERFLY_LOOKAT01 13
#define SEQUENCE_BUTTERFLY_LOOKAT03 15

#define SEQUENCE_FALCHION_IDLE1 1
#define SEQUENCE_FALCHION_HEAVY_MISS1 8
#define SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP 9
#define SEQUENCE_FALCHION_LOOKAT01 12
#define SEQUENCE_FALCHION_LOOKAT02 13

#define SEQUENCE_DAGGERS_IDLE1 1
#define SEQUENCE_DAGGERS_LIGHT_MISS1 2
#define SEQUENCE_DAGGERS_LIGHT_MISS5 6
#define SEQUENCE_DAGGERS_HEAVY_MISS2 11
#define SEQUENCE_DAGGERS_HEAVY_MISS1 12

#define SEQUENCE_BOWIE_IDLE1 1

#define	LIFE_ALIVE 0
#include <memory>



class RecvPropHook
{
private:
	RecvProp* target_property;
	RecvVarProxyFn original_proxy_fn;
public:
	RecvPropHook(RecvProp* target_property)
	{
		this->target_property = target_property;
		this->original_proxy_fn = (RecvVarProxyFn)target_property->m_ProxyFn;
	}

	~RecvPropHook()
	{
		target_property->m_ProxyFn = this->original_proxy_fn;
	}

	RecvVarProxyFn GetOriginalFunction()
	{
		return this->original_proxy_fn;
	}

	void SetProxyFunction(RecvVarProxyFn user_proxy_fn)
	{
		target_property->m_ProxyFn = user_proxy_fn;
	}
};

std::unique_ptr<RecvPropHook> sequenceHook;

RecvVarProxyFn oRecvProxySequence;
void RecvProxy_Sequence(CRecvProxyData* pDataConst, void* pStruct, void* pOut)
{
	static int lastSentSeq;
	CRecvProxyData* pData = const_cast<CRecvProxyData*>(pDataConst);

	int iSequence = pData->m_Value.m_Int;

	CBaseCombatWeapon* Weapon = static_cast<CBaseCombatWeapon*>(pStruct);
	CBaseEntity* pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());

	if (Weapon && Weapon->GetModelIndex() && pLocal)
	{
		std::string rWeapon = Interfaces.g_pModelInfo->GetModelName(Weapon->GetModel());

		if (rWeapon.find(("v_knife_push.mdl")) != std::string::npos)
		{
			switch (iSequence) {
			case SEQUENCE_DEFAULT_IDLE2:
				iSequence = SEQUENCE_DAGGERS_IDLE1; break;
			case SEQUENCE_DEFAULT_LIGHT_MISS1:
			case SEQUENCE_DEFAULT_LIGHT_MISS2:
				iSequence = RandomIntZ(SEQUENCE_DAGGERS_LIGHT_MISS1, SEQUENCE_DAGGERS_LIGHT_MISS5); break;
			case SEQUENCE_DEFAULT_HEAVY_MISS1:
				iSequence = RandomIntZ(SEQUENCE_DAGGERS_HEAVY_MISS2, SEQUENCE_DAGGERS_HEAVY_MISS1); break;
			case SEQUENCE_DEFAULT_HEAVY_HIT1:
			case SEQUENCE_DEFAULT_HEAVY_BACKSTAB:
			case SEQUENCE_DEFAULT_LOOKAT01:
				iSequence += 3; break;
			case SEQUENCE_DEFAULT_DRAW:
			case SEQUENCE_DEFAULT_IDLE1:
				break;
			default:
				iSequence += 2;
			}
		}
		else if (rWeapon.find(("v_knife_falchion_advanced.mdl")) != std::string::npos)
		{
			switch (iSequence) {
			case SEQUENCE_DEFAULT_IDLE2:
				iSequence = SEQUENCE_FALCHION_IDLE1; break;
			case SEQUENCE_DEFAULT_HEAVY_MISS1:
				iSequence = RandomIntZ(SEQUENCE_FALCHION_HEAVY_MISS1, SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP); break;
			case SEQUENCE_DEFAULT_LOOKAT01:
				iSequence = RandomIntZ(SEQUENCE_FALCHION_LOOKAT01, SEQUENCE_FALCHION_LOOKAT02); break;
			case SEQUENCE_DEFAULT_DRAW:
			case SEQUENCE_DEFAULT_IDLE1:
				break;
			default:
				iSequence--;
			}
		}
		else if (rWeapon.find(("v_knife_butterfly.mdl")) != std::string::npos)
		{
			switch (iSequence) {
			case SEQUENCE_DEFAULT_DRAW:
				iSequence = RandomIntZ(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2); break;
			case SEQUENCE_DEFAULT_LOOKAT01:
				iSequence = RandomIntZ(SEQUENCE_BUTTERFLY_LOOKAT01, SEQUENCE_BUTTERFLY_LOOKAT03); break;
			default:
				iSequence++;
			}
		}
		else if (rWeapon.find(("v_knife_survival_bowie.mdl")) != std::string::npos)
		{
			switch (iSequence) {
			case SEQUENCE_DEFAULT_DRAW:
			case SEQUENCE_DEFAULT_IDLE1:
				break;
			case SEQUENCE_DEFAULT_IDLE2:
				iSequence = SEQUENCE_BOWIE_IDLE1; break;
			default:
				iSequence--;
			}
		}
		else if (rWeapon.find(("models/weapons/v_knife_widowmaker.mdl")) != std::string::npos)
		{
			// Fix animations for the Bowie Knife.
			switch (iSequence)
			{
			case SEQUENCE_DEFAULT_LOOKAT01:
				iSequence = RandomIntZ(14, 15);
				break;
			}
		}
		else if (rWeapon.find(("models/weapons/v_knife_ursus.mdl")) != std::string::npos)
		{
			switch (iSequence)
			{
			case SEQUENCE_DEFAULT_DRAW:
				iSequence = RandomIntZ(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2);
				break;
			case SEQUENCE_DEFAULT_LOOKAT01:
				iSequence = RandomIntZ(SEQUENCE_BUTTERFLY_LOOKAT01, 14);
				break;
			default:
				iSequence++;
				break;
			}
		}
		else if (rWeapon.find(("models/weapons/v_knife_stiletto.mdl")) != std::string::npos)
		{
			switch (iSequence)
			{
			case SEQUENCE_DEFAULT_LOOKAT01:
				iSequence = RandomIntZ(12, 13);
				break;
			}
		}

		pData->m_Value.m_Int = iSequence;
	}

	if (!oRecvProxySequence)
		oRecvProxySequence = sequenceHook->GetOriginalFunction();

	oRecvProxySequence(pData, pStruct, pOut);
}


void CSkinchanger::KnifeEventFire(IGameEvent* event)
{
//	if (!g_Options.Skinchanger.EnabledChanger)
//		return;

	if (Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected() && G::LocalPlayer->isAlive())
	{
		if (G::LocalPlayer->GetActiveBaseCombatWeapon() && G::LocalPlayer->GetActiveBaseCombatWeapon()->IsKnife())
		{
			if (event && strcmp(event->GetName(), ("player_death")) == 0)
			{

				if (event->GetInt(("attacker")) && Interfaces.pEngine->GetPlayerForUserID(event->GetInt(("attacker"))) == Interfaces.pEngine->GetLocalPlayer())
				{
					std::string weapon = event->GetString(("weapon"));

					std::string wpn = weapon;

					std::string weaponmy = G::LocalPlayer->GetTeam() == 2 ? ("knife_t") : ("knife_default_ct");

					if (wpn == ("knife_default_ct") || wpn == ("knife_t") || wpn == ("bayonet") || wpn == ("knife_push") || wpn == ("knife_butterfly") || wpn == ("knife_survival_bowie") || wpn == ("knife_falchion") || wpn == ("knife_tactical") || wpn == ("knife_m9_bayonet") || wpn == ("knife_karambit") || wpn == ("knife_gut") || wpn == ("knife_flip") || wpn == ("knife_navaja") || wpn == ("knife_stiletto") || wpn == ("knife_ursus") || wpn == ("knife_talon"))
					{

						switch (*G::LocalPlayer->GetActiveBaseCombatWeapon()->GetItemDefinitionIndex())
						{
						case WEAPON_KNIFE_BAYONET:
							weaponmy = ("bayonet");
							break;
						case WEAPON_KNIFE_FLIP:
							weaponmy = ("knife_flip");
							break;
						case WEAPON_KNIFE_GUT:
							weaponmy = ("knife_gut");
							break;
						case WEAPON_KNIFE_KARAMBIT:
							weaponmy = ("knife_karambit");
							break;
						case WEAPON_KNIFE_M9_BAYONET:
							weaponmy = ("knife_m9_bayonet");
							break;
						case WEAPON_KNIFE_TACTICAL:
							weaponmy = ("knife_tactical");
							break;
						case WEAPON_KNIFE_FALCHION:
							weaponmy = ("knife_falchion");
							break;
						case WEAPON_KNIFE_SURVIVAL_BOWIE:
							weaponmy = ("knife_survival_bowie");
							break;
						case WEAPON_KNIFE_BUTTERFLY:
							weaponmy = ("knife_butterfly");
							break;
						case WEAPON_KNIFE_PUSH:
							weaponmy = ("knife_push");
							break;
						case WEAPON_KNIFE_NAVAJA:
							weaponmy = ("knife_navaja");
							break;
						case WEAPON_KNIFE_STILETTO:
							weaponmy = ("knife_stiletto");
							break;
						case WEAPON_KNIFE_URSUS:
							weaponmy = ("knife_ursus");
							break;
						case WEAPON_KNIFE_TALON:
							weaponmy = ("knife_talon");
						}

						if (weapon != weaponmy)
							event->SetString(("weapon"), weaponmy.c_str());
					}
				}
			}
		}
	}
}
