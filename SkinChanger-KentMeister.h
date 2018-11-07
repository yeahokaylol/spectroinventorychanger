#pragma once
//#define RandomInt(nMin, nMax) (rand() % (nMax - nMin + 1) + nMin);
#include <unordered_map>
extern RecvVarProxyFn oRecvnModelIndex;
extern RecvVarProxyFn oRecvProxySequence;

class CSkinchanger
{
public:
	void KnifeEventFire(IGameEvent* event);
	void CreateMove();
	void ForceItemUpdates();
	void UpdateModels();
private:
	void GloveChanger(player_info_t pInfo);
	bool ApplyCustomSkin(CBaseAttributableItem* attrib_item, player_info_t pInfo);
	void ApplyStickerHooks(CBaseAttributableItem* attrib_item);
	int GetModelByIndex(int item_def_index);
	int GetGloveModelIndexByMenu(int gloveIndexinmenu);
public:
	struct
	{
		int knife_default_ct = NULL;
		int knife_default_t = NULL;
		int knife_karam = NULL;
		int knife_bayonet = NULL;
		int	knife_m9_bay = NULL;
		int knife_tactical = NULL;
		int knife_gut = NULL;
		int knife_falchion_advanced = NULL;
		int knife_push = NULL;
		int knife_butterfly = NULL;
		int knife_flip = NULL;
		int knife_survival_bowie = NULL;
		int knife_navaja = NULL;
		int knife_stiletto = NULL;
		int knife_ursus = NULL;
		int knife_talon = NULL;
	}Knifes;
	struct
	{
		int glove_bloodhound = NULL;
		int glove_sporty = NULL;
		int glove_slick = NULL;
		int glove_handwrap_leathery = NULL;
		int glove_motorcycle = NULL;
		int glove_specialist = NULL;
		int glove_hydra = NULL;
	}Gloves;
};
extern void ViewModel_Index_Proxy(CRecvProxyData *pDataConst, void *pStruct, void *pOut);
extern void RecvProxy_Sequence(CRecvProxyData* pDataConst, void* pStruct, void* pOut);
extern CSkinchanger* g_Skinchanger;

