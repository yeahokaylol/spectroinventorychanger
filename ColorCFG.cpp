#include "ColorCFG.h"
//#include "SDK.h"
#include <winerror.h>
#include <ShlObj_core.h>
#pragma comment(lib, "Shell32.lib")


void CConfigColors::DeclareSave(int col[4], std::string category)
{
	SetupValue(col[0], 0, category, ("red"));
	SetupValue(col[1], 0, category, ("green"));
	SetupValue(col[2], 0, category, ("blue"));
	SetupValue(col[3], 0, category, ("alpha"));
}

void CConfigColors::Setup()
{
	DeclareSave(CTBoxVisable, ("CTBoxVisable"));
	DeclareSave(CTBoxInVisable, ("CTBoxInVisable"));
	DeclareSave(TBoxVisable, ("TBoxVisable"));
	DeclareSave(TBoxInVisable, ("TBoxInVisable"));

	DeclareSave(CTGlowVisable, ("CTGlowVisable"));
	DeclareSave(CTGlowInVisable, ("CTGlowInVisable"));
	DeclareSave(TGlowVisable, ("TGlowVisable"));
	DeclareSave(TGlowInVisable, ("TGlowInVisable"));

	DeclareSave(Beams, ("Beams"));
	DeclareSave(FilledSpread, ("FilledSpread"));
	DeclareSave(LagCompHitboxes, ("LagCompHitboxes"));
	DeclareSave(SoundESP, ("SoundESP"));
	DeclareSave(DamageESP, ("DamageESP"));

	DeclareSave(FakeAngleChams, ("FakeAngleChams"));
	DeclareSave(Stelki, ("Arrow Indicator"));

	DeclareSave(CTChamsVisable, ("CTChamsVisable"));
	DeclareSave(CTChamsInVisable, ("CTChamsInVisable"));
	DeclareSave(TChamsVisable, ("TChamsVisable"));
	DeclareSave(TChamsInVisable, ("TChamsInVisable"));

	

}
void CConfigColors::SetupValue(char &value, char def, std::string category, std::string name)
{
	value = def;
	chars.push_back(new ConfigValueColors<char>(category, name, &value));
}
void CConfigColors::SetupValue(int &value, int def, std::string category, std::string name)
{
	value = def;
	ints.push_back(new ConfigValueColors<int>(category, name, &value));
}

void CConfigColors::SetupValue(float &value, float def, std::string category, std::string name)
{
	value = def;
	floats.push_back(new ConfigValueColors<float>(category, name, &value));
}

void CConfigColors::SetupValue(bool &value, bool def, std::string category, std::string name)
{
	value = def;
	bools.push_back(new ConfigValueColors<bool>(category, name, &value));
}


#include <stdio.h>
void CConfigColors::Delete()
{
	static char path[MAX_PATH];
	std::string file;

	if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, path)))
	{
		char szCmd[256];
		sprintf(szCmd, "\\Lore Cheats\\Colors\\%s.ini", g_Options.Misc.confignameColors);
		file = std::string(path) + szCmd;
	}

	DeleteFileA(file.c_str());


}
void CConfigColors::Rename(char* newname)
{
	static char path[MAX_PATH];
	std::string file, output;

	if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, path)))
	{
		char szCmd[256];
		sprintf(szCmd, "\\Lore Cheats\\Colors\\%s.ini", g_Options.Misc.confignameColors);
		char szCmd2[256];
		sprintf(szCmd2, "\\Lore Cheats\\Colors\\%s.ini", newname);

		file = std::string(path) + szCmd;
		output = std::string(path) + szCmd2;
	}

	std::rename(file.c_str(), output.c_str());

}
void CConfigColors::Save()
{
	static char path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, path)))
	{
		char szCmd[256];
		sprintf(szCmd, "\\Lore Cheats\\Colors\\%s.ini", g_Options.Misc.confignameColors);
		folder = std::string(path) + ("\\Lore Cheats\\Colors\\");


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

void CConfigColors::Load()
{
	static char path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, path)))
	{
		char szCmd[256];
		sprintf(szCmd, "\\Lore Cheats[colorcfg]\\%s.ini", g_Options.Misc.confignameColors);
		folder = std::string(path) + ("\\Lore Cheats[colorcfg]\\");

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


CConfigColors* pConfigColors = new CConfigColors();


