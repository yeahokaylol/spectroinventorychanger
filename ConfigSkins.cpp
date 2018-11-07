#include "ConfigSkins.h"
//#include "SDK.h"
#include <winerror.h>
#include <ShlObj.h>
#include <ShlObj_core.h>
#pragma comment(lib, "Shell32.lib")


std::string GetCFGNameChangerRR(int iWeaponID, int secondint)
{
	if (secondint == 0)
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
		case WEAPON_MP5:
			return ("MP-5");
		case WEAPON_AWP:
			return ("AWP");
		case WEAPON_FAMAS:
			return ("FAMAS");
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
	else
	{
		return ("none");
	}
}

void CConfigSkins::Setup()
{
		for (int idNEW = 1; idNEW < 519; idNEW++)
		{
			if ((idNEW > 65 && idNEW < 499))
				continue;
			if(idNEW == 5 || idNEW == 6 || idNEW == 12 || idNEW == 15 || idNEW == 18 || idNEW == 20 || idNEW == 21 || idNEW == 22 || idNEW == 23
				|| idNEW == 37 || idNEW == 41 || idNEW == 50 || idNEW == 51 || idNEW == 52 || idNEW == 53 || idNEW == 54 || idNEW == 55 || idNEW == 56 || idNEW == 57
				|| idNEW == 58 || idNEW == 65 || idNEW == 499)
				continue;
			SetupValue(g_Options.Skinchanger.SkinMaster[idNEW].PaintKit, 0, GetCFGNameChangerRR(idNEW, 0), ("PaintKit"));
			SetupValue(g_Options.Skinchanger.SkinMaster[idNEW].Seed, 0, GetCFGNameChangerRR(idNEW, 0), ("Seed"));
			SetupValue(g_Options.Skinchanger.SkinMaster[idNEW].Stattrak, false, GetCFGNameChangerRR(idNEW, 0), ("Stattrak"));
			SetupValue(g_Options.Skinchanger.SkinMaster[idNEW].StattrakValue, 0, GetCFGNameChangerRR(idNEW, 0), ("StattrakValue"));
			SetupValue(g_Options.Skinchanger.SkinMaster[idNEW].Wear, 0.f, GetCFGNameChangerRR(idNEW, 0), ("Wear"));
	//		SetupValue(g_Options.Skinchanger.SkinMaster[idNEW].StickersEnabled, false, GetCFGNameChangerRR(idNEW, 0), ("StickersEnabled"));
		}
		SetupValue(g_Options.Skinchanger.EnabledChanger, false, "SkinChanger", ("EnabledChanger"));
		SetupValue(g_Options.Skinchanger.knifemodel, 3, "SkinChanger", ("KnifeModel"));
		SetupValue(g_Options.Skinchanger.glovemodel, 3, "SkinChanger", ("GloveModel"));
		SetupValue(g_Options.Skinchanger.gloveskin, 0, "SkinChanger", ("GloveSkin"));

}
void CConfigSkins::SetupValue(char &value, char def, std::string category, std::string name)
{
	value = def;
	chars.push_back(new ConfigValueSkins<char>(category, name, &value));
}
void CConfigSkins::SetupValue(int &value, int def, std::string category, std::string name)
{
	value = def;
	ints.push_back(new ConfigValueSkins<int>(category, name, &value));
}

void CConfigSkins::SetupValue(float &value, float def, std::string category, std::string name)
{
	value = def;
	floats.push_back(new ConfigValueSkins<float>(category, name, &value));
}

void CConfigSkins::SetupValue(bool &value, bool def, std::string category, std::string name)
{
	value = def;
	bools.push_back(new ConfigValueSkins<bool>(category, name, &value));
}


#include <stdio.h>
void CConfigSkins::Delete(CFGTYPE Type)
{
	static char path[MAX_PATH];
	std::string file;

	if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, path)))
	{
		char szCmd[256];
		sprintf(szCmd, "\\Lore Cheats\\Skins\\%s.ini", g_Options.Misc.confignameskins);
		file = std::string(path) + szCmd;
	}

	DeleteFileA(file.c_str());


}
void CConfigSkins::Rename(char* newname, CFGTYPE Type)
{
	static char path[MAX_PATH];
	std::string file, output;

	if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, path)))
	{
		char szCmd[256];
		sprintf(szCmd, "\\Lore Cheats\\Skins\\%s.ini", g_Options.Misc.confignameskins);
		char szCmd2[256];
		sprintf(szCmd2, "\\Lore Cheats\\Skins\\%s.ini", newname);

		file = std::string(path) + szCmd;
		output = std::string(path) + szCmd2;
	}

	std::rename(file.c_str(), output.c_str());

}
void CConfigSkins::Save(CFGTYPE Type)
{
	static char path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, path)))
	{
		char szCmd[256];
		sprintf(szCmd, "\\Lore Cheats\\Skins\\%s.ini", g_Options.Misc.confignameskins);
		folder = std::string(path) + ("\\Lore Cheats\\Skins\\");


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

void CConfigSkins::Load(CFGTYPE Type)
{
	static char path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, path)))
	{
		char szCmd[256];
		sprintf(szCmd, "\\Lore Cheats\\Skins\\%s.ini", g_Options.Misc.confignameskins);
		folder = std::string(path) + ("\\Lore Cheats\\Skins\\");
		
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


CConfigSkins* pConfigSkins = new CConfigSkins();


