#include "stdafx.h"
#include "NameSpace.h"
#include "imgui\imgui.h"
#include "imgui\imgui_internal.h"
#include "imgui\dx9\imgui_dx9.h"
#include "Parser.h"
#include "SkinChanger-KentMeister.h"
#include "ConfigSkins.h"
#include "ColorCFG.h"
#include "RenderD9.h"
#include "C:\Users\Danutu\Desktop\Zeus - Fixed By Bugzy\calantag.h"
#include "Protobuf/inventory_changer.h"



int BulletSizeByMenu(int id)
{
	short WeaponId = id;
	switch (WeaponId)
	{
	case WEAPON_ELITE:
	case WEAPON_MAC10:
	case WEAPON_M4A1:
	case WEAPON_AK47:
	case WEAPON_MP5:
	case WEAPON_MP7:
	case WEAPON_MP9:
	case WEAPON_SG556:
	case WEAPON_AUG:
		return 30;
	case WEAPON_NEGEV:
		return 150;
	case WEAPON_M249:
		return 100;
	case WEAPON_REVOLVER:
		return 8;
	case WEAPON_M4A1_SILENCER:
	case WEAPON_GLOCK:
	case WEAPON_SCAR20:
	case WEAPON_G3SG1:
		return 20;
	case WEAPON_DEAGLE:
		return 7;
	case WEAPON_P90:
		return 50;
	case WEAPON_UMP45:
		return 25;
	case WEAPON_SSG08:
	case WEAPON_AWP:
		return 10;
	case WEAPON_GALILAR:
		return 35;
	case WEAPON_FAMAS:
		return 25;
	case WEAPON_CZ75A:
	case WEAPON_USP_SILENCER:
		return 12;
	case WEAPON_HKP2000:
	case WEAPON_P250:
		return 13;
	case WEAPON_TEC9:
		return 24;
	case WEAPON_NOVA:
		return 8;
	case WEAPON_XM1014:
	case WEAPON_SAWEDOFF:
		return 7;
	case WEAPON_MAG7:
		return 5;
	case WEAPON_BIZON:
		return 64;
	default:
		return 100;

	}

}

bool IsKnifeForMenu(int id)
{
	short iWeaponID = id;
	return (iWeaponID == 42 || iWeaponID == 59 || iWeaponID == 41
		|| iWeaponID == 500 || iWeaponID == 505 || iWeaponID == 506
		|| iWeaponID == 507 || iWeaponID == 508 || iWeaponID == 509
		|| iWeaponID == 515);
}

#define SliderIntFST(x1,x2,x3,x4) ImGui::PushItemWidth(120); ImGui::SliderInt(x1, &x2, x3, x4); ImGui::PopItemWidth();
#define SliderFloatFST(x1,x2,x3,x4) ImGui::PushItemWidth(120); ImGui::SliderFloat(x1, &x2, x3, x4); ImGui::PopItemWidth();
#define SliderFloatFSTCustom(x1,x2,x3,x4,x5) ImGui::PushItemWidth(x5); ImGui::SliderFloat(x1, &x2, x3, x4); ImGui::PopItemWidth();
#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))
// Menu Includes Futures
#include "icons/TitleBar.h"
#include "icons/LegitBar.h"
#include "icons/RageBar.h"
#include "icons/VisualsBar.h"
#include "icons/MiscBar.h"
IDirect3DTexture9 *TittleBar = nullptr;
IDirect3DTexture9 *LegitTabImg = nullptr;
IDirect3DTexture9 *RageTabImg = nullptr;
IDirect3DTexture9 *VisualsTabImg = nullptr;
IDirect3DTexture9 *MiscTabImg = nullptr;

IDirect3DTexture9* TextureImage = nullptr;
LPCTSTR pszPic = "lore.png";

int windowWidth = 800;
int windowHeight = 425;

int windowWidth2 = 650;
int windowHeight2 = 485;

int curWidth = windowWidth;
int curHeight = windowHeight;


void DeclareToSave(int col[4], CColor meme)
{
	col[0] = meme.r(); col[1] = meme.g(); col[2] = meme.b(); col[3] = meme.a();
}

#define DeclareToLoad(x1,x2) x2 = CColor(x1[0],x1[1],x1[2],x1[3])

bool ColorPickerNew(float* col, bool alphabar)
{
	const int EDGE_SIZE = 200; // = int(ImGui::GetWindowWidth() * 0.75f);
	const ImVec2 SV_PICKER_SIZE = ImVec2(EDGE_SIZE, EDGE_SIZE);
	const float SPACING = ImGui::GetStyle().ItemInnerSpacing.x;
	const float HUE_PICKER_WIDTH = 20.f;
	const float CROSSHAIR_SIZE = 7.0f;

	ImColor color(col[0], col[1], col[2]);
	bool value_changed = false;

	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	ImVec2 picker_pos = ImGui::GetCursorScreenPos();

	float hue, saturation, value;
	ImGui::ColorConvertRGBtoHSV(color.Value.x, color.Value.y, color.Value.z, hue, saturation, value);

	ImColor colors[] = {
		ImColor(255, 0, 0),
		ImColor(255, 255, 0),
		ImColor(0, 255, 0),
		ImColor(0, 255, 255),
		ImColor(0, 0, 255),
		ImColor(255, 0, 255),
		ImColor(255, 0, 0)
	};

	for (int i = 0; i < 6; i++)
	{
		draw_list->AddRectFilledMultiColor(
			ImVec2(picker_pos.x + SV_PICKER_SIZE.x + SPACING, picker_pos.y + i * (SV_PICKER_SIZE.y / 6)),
			ImVec2(picker_pos.x + SV_PICKER_SIZE.x + SPACING + HUE_PICKER_WIDTH,
				picker_pos.y + (i + 1) * (SV_PICKER_SIZE.y / 6)),
			colors[i],
			colors[i],
			colors[i + 1],
			colors[i + 1]
		);
	}

	draw_list->AddLine(
		ImVec2(picker_pos.x + SV_PICKER_SIZE.x + SPACING - 2, picker_pos.y + hue * SV_PICKER_SIZE.y),
		ImVec2(picker_pos.x + SV_PICKER_SIZE.x + SPACING + 2 + HUE_PICKER_WIDTH, picker_pos.y + hue * SV_PICKER_SIZE.y),
		ImColor(255, 255, 255)
	);

	if (alphabar)
	{
		float alpha = col[3];

		draw_list->AddRectFilledMultiColor(
			ImVec2(picker_pos.x + SV_PICKER_SIZE.x + 2 * SPACING + HUE_PICKER_WIDTH, picker_pos.y),
			ImVec2(picker_pos.x + SV_PICKER_SIZE.x + 2 * SPACING + 2 * HUE_PICKER_WIDTH, picker_pos.y + SV_PICKER_SIZE.y),
			ImColor(0, 0, 0), ImColor(0, 0, 0), ImColor(255, 255, 255), ImColor(255, 255, 255)
		);

		draw_list->AddLine(
			ImVec2(picker_pos.x + SV_PICKER_SIZE.x + 2 * (SPACING - 2) + HUE_PICKER_WIDTH, picker_pos.y + alpha * SV_PICKER_SIZE.y),
			ImVec2(picker_pos.x + SV_PICKER_SIZE.x + 2 * (SPACING + 2) + 2 * HUE_PICKER_WIDTH, picker_pos.y + alpha * SV_PICKER_SIZE.y),
			ImColor(255.f - alpha, 255.f, 255.f)
		);
	}

	const ImU32 c_oColorBlack = ImGui::ColorConvertFloat4ToU32(ImVec4(0.f, 0.f, 0.f, 1.f));
	const ImU32 c_oColorBlackTransparent = ImGui::ColorConvertFloat4ToU32(ImVec4(0.f, 0.f, 0.f, 0.f));
	const ImU32 c_oColorWhite = ImGui::ColorConvertFloat4ToU32(ImVec4(1.f, 1.f, 1.f, 1.f));

	ImVec4 cHueValue(1, 1, 1, 1);
	ImGui::ColorConvertHSVtoRGB(hue, 1, 1, cHueValue.x, cHueValue.y, cHueValue.z);
	ImU32 oHueColor = ImGui::ColorConvertFloat4ToU32(cHueValue);

	draw_list->AddRectFilledMultiColor(
		ImVec2(picker_pos.x, picker_pos.y),
		ImVec2(picker_pos.x + SV_PICKER_SIZE.x, picker_pos.y + SV_PICKER_SIZE.y),
		c_oColorWhite,
		oHueColor,
		oHueColor,
		c_oColorWhite
	);

	draw_list->AddRectFilledMultiColor(
		ImVec2(picker_pos.x, picker_pos.y),
		ImVec2(picker_pos.x + SV_PICKER_SIZE.x, picker_pos.y + SV_PICKER_SIZE.y),
		c_oColorBlackTransparent,
		c_oColorBlackTransparent,
		c_oColorBlack,
		c_oColorBlack
	);

	float x = saturation * SV_PICKER_SIZE.x;
	float y = (1 - value) * SV_PICKER_SIZE.y;
	ImVec2 p(picker_pos.x + x, picker_pos.y + y);
	draw_list->AddLine(ImVec2(p.x - CROSSHAIR_SIZE, p.y), ImVec2(p.x - 2, p.y), ImColor(255, 255, 255));
	draw_list->AddLine(ImVec2(p.x + CROSSHAIR_SIZE, p.y), ImVec2(p.x + 2, p.y), ImColor(255, 255, 255));
	draw_list->AddLine(ImVec2(p.x, p.y + CROSSHAIR_SIZE), ImVec2(p.x, p.y + 2), ImColor(255, 255, 255));
	draw_list->AddLine(ImVec2(p.x, p.y - CROSSHAIR_SIZE), ImVec2(p.x, p.y - 2), ImColor(255, 255, 255));

	ImGui::InvisibleButton("saturation_value_selector", SV_PICKER_SIZE);

	if (ImGui::IsItemActive() && ImGui::GetIO().MouseDown[0])
	{
		ImVec2 mouse_pos_in_canvas = ImVec2(ImGui::GetIO().MousePos.x - picker_pos.x, ImGui::GetIO().MousePos.y - picker_pos.y);

		if (mouse_pos_in_canvas.x <	0)
			mouse_pos_in_canvas.x = 0;
		else if (mouse_pos_in_canvas.x >= SV_PICKER_SIZE.x - 1)
			mouse_pos_in_canvas.x = SV_PICKER_SIZE.x - 1;

		if (mouse_pos_in_canvas.y < 0)
			mouse_pos_in_canvas.y = 0;
		else if (mouse_pos_in_canvas.y >= SV_PICKER_SIZE.y - 1)
			mouse_pos_in_canvas.y = SV_PICKER_SIZE.y - 1;

		value = 1 - (mouse_pos_in_canvas.y / (SV_PICKER_SIZE.y - 1));
		saturation = mouse_pos_in_canvas.x / (SV_PICKER_SIZE.x - 1);
		value_changed = true;
	}

	// hue bar logic
	ImGui::SetCursorScreenPos(ImVec2(picker_pos.x + SPACING + SV_PICKER_SIZE.x, picker_pos.y));
	ImGui::InvisibleButton("hue_selector", ImVec2(HUE_PICKER_WIDTH, SV_PICKER_SIZE.y));

	if (ImGui::GetIO().MouseDown[0] && (ImGui::IsItemHovered() || ImGui::IsItemActive()))
	{
		ImVec2 mouse_pos_in_canvas = ImVec2(ImGui::GetIO().MousePos.x - picker_pos.x, ImGui::GetIO().MousePos.y - picker_pos.y);

		if (mouse_pos_in_canvas.y <	0)
			mouse_pos_in_canvas.y = 0;
		else if (mouse_pos_in_canvas.y >= SV_PICKER_SIZE.y - 1)
			mouse_pos_in_canvas.y = SV_PICKER_SIZE.y - 1;

		hue = mouse_pos_in_canvas.y / (SV_PICKER_SIZE.y - 1);
		value_changed = true;
	}

	if (alphabar)
	{
		ImGui::SetCursorScreenPos(ImVec2(picker_pos.x + SPACING * 2 + HUE_PICKER_WIDTH + SV_PICKER_SIZE.x, picker_pos.y));
		ImGui::InvisibleButton("alpha_selector", ImVec2(HUE_PICKER_WIDTH, SV_PICKER_SIZE.y));

		if (ImGui::GetIO().MouseDown[0] && (ImGui::IsItemHovered() || ImGui::IsItemActive()))
		{
			ImVec2 mouse_pos_in_canvas = ImVec2(ImGui::GetIO().MousePos.x - picker_pos.x, ImGui::GetIO().MousePos.y - picker_pos.y);

			if (mouse_pos_in_canvas.y <	0)
				mouse_pos_in_canvas.y = 0;
			else if (mouse_pos_in_canvas.y >= SV_PICKER_SIZE.y - 1)
				mouse_pos_in_canvas.y = SV_PICKER_SIZE.y - 1;

			float alpha = mouse_pos_in_canvas.y / (SV_PICKER_SIZE.y - 1);
			col[3] = alpha;
			value_changed = true;
		}
	}

	color = ImColor::HSV(hue >= 1 ? hue - 10 * 1e-6 : hue, saturation > 0 ? saturation : 10 * 1e-6, value > 0 ? value : 1e-6);
	col[0] = color.Value.x;
	col[1] = color.Value.y;
	col[2] = color.Value.z;

	bool widget_used;
	ImGui::PushItemWidth((alphabar ? SPACING + HUE_PICKER_WIDTH : 0) + SV_PICKER_SIZE.x + SPACING + HUE_PICKER_WIDTH - 2 * ImGui::GetStyle().FramePadding.x);
	widget_used = alphabar ? ImGui::ColorEdit4("", col) : ImGui::ColorEdit3("", col);
	ImGui::PopItemWidth();

	float new_hue, new_sat, new_val;
	ImGui::ColorConvertRGBtoHSV(col[0], col[1], col[2], new_hue, new_sat, new_val);

	if (new_hue <= 0 && hue > 0)
	{
		if (new_val <= 0 && value != new_val)
		{
			color = ImColor::HSV(hue, saturation, new_val <= 0 ? value * 0.5f : new_val);
			col[0] = color.Value.x;
			col[1] = color.Value.y;
			col[2] = color.Value.z;
		}
		else if (new_sat <= 0)
		{
			color = ImColor::HSV(hue, new_sat <= 0 ? saturation * 0.5f : new_sat, new_val);
			col[0] = color.Value.x;
			col[1] = color.Value.y;
			col[2] = color.Value.z;
		}
	}

	return value_changed | widget_used;
}
bool ColorPicker4New(float col[4])
{
	return ColorPickerNew(col, true);
}

struct ColorListVar
{
	const char* name;
	union
	{
		CColor colorVarPtr;
	};


	ColorListVar(const char* name, CColor ptr)
	{
		this->name = name;
		colorVarPtr = ptr;
	}

};





ColorListVar colors[] = {

	{ "CT Box Visible", Hacks.Colors.CTBoxVisable },
	{ "CT Box InVisible", Hacks.Colors.CTBoxInVisable },
	{ "T Box Visible", Hacks.Colors.TBoxVisable },
	{ "T Box InVisible", Hacks.Colors.TBoxInVisable },
	{ "CT Glow Visible", Hacks.Colors.CTGlowVisable },
	{ "CT Glow InVisible", Hacks.Colors.CTGlowInVisable },
	{ "T Glow Visible", Hacks.Colors.TGlowVisable },
	{ "T Glow InVisible", Hacks.Colors.TGlowInVisable },
	{ "Beam-Tracer", Hacks.Colors.Beams },
	{ "Filled Spread Circle", Hacks.Colors.FilledSpread },
	{ "Hit-Capsule", Hacks.Colors.LagCompHitboxes },
	{ "CT Chams Visible", Hacks.Colors.CTChamsVisable },
	{ "CT Chams InVisible", Hacks.Colors.CTChamsInVisable },
	{ "T Chams Visible", Hacks.Colors.TChamsVisable },
	{ "T Chams InVisible", Hacks.Colors.TChamsInVisable },
	{ "Fake Angle Chams", Hacks.Colors.FakeAngleChams },
	{ "Sound Esp", Hacks.Colors.SoundESP },
	{ "Damage Esp", Hacks.Colors.DamageESP },
	{ "Arrows Indicators", Hacks.Colors.Stelki }
};

/*CColor ColorForMenu(int NeedColor)
{
	switch (NeedColor)
	{
	case 0:return Hacks.Colors.CTBoxVisable; break;
	case 1:return Hacks.Colors.CTBoxInVisable; break;
	case 2:return Hacks.Colors.TBoxVisable; break;
	case 3:return Hacks.Colors.TBoxInVisable; break;
	case 4:return Hacks.Colors.CTGlowVisable; break;
	case 5:return Hacks.Colors.CTGlowInVisable; break;
	case 6:return Hacks.Colors.TGlowVisable; break;
	case 7:return Hacks.Colors.TGlowInVisable; break;
	default:return CColor(255, 255, 255, 255); break;
	}
}*/


const char* colorNames[IM_ARRAYSIZE(colors)];


std::string SanitizeName(char *name)
{
	name[127] = '\0';

	std::string tmp(name);

	for (int i = 0; i < (int)tmp.length(); i++)
	{
		if ((
			tmp[i] >= 'a' && tmp[i] <= 'z' ||
			tmp[i] >= 'A' && tmp[i] <= 'Z' ||
			tmp[i] >= '0' && tmp[i] <= '9' ||
			tmp[i] == ' ' || tmp[i] == '.' || tmp[i] == '/' || tmp[i] == ':' ||
			tmp[i] == ',' || tmp[i] == '_' || tmp[i] == '#' || tmp[i] == '$' ||
			tmp[i] == '<' || tmp[i] == '>' || tmp[i] == '-' || tmp[i] == '+' ||
			tmp[i] == '*' || tmp[i] == '%' || tmp[i] == '@' || tmp[i] == '(' ||
			tmp[i] == ')' || tmp[i] == '{' || tmp[i] == '}' || tmp[i] == '[' || tmp[i] == ']' ||
			tmp[i] == '!' || tmp[i] == '&' || tmp[i] == '~' || tmp[i] == '^'
			) == false)
		{
			tmp[i] = '_';
		}
	}
	
		if (tmp.length() > (20))
		{
			tmp.erase(20, (tmp.length() - 20));
			tmp.append("...");
		}
	return tmp;
}


void StdReplaceStr1(std::string& replaceIn, const std::string& replace, const std::string& replaceWith)
{
	size_t const span = replace.size();
	size_t const step = replaceWith.size();
	size_t index = 0;

	while (true)
	{
		index = replaceIn.find(replace, index);

		if (index == std::string::npos)
			break;

		replaceIn.replace(index, span, replaceWith);
		index += step;
	}
}

std::vector<std::string> configs;
void GetConfigMassive(int meme)
{
	//get all files on folder

	configs.clear();

	static char path[MAX_PATH];
	std::string szPath1;

	if (!SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, path)))
		return;

	szPath1 = meme == 0 ? (std::string(path) + ("\\Lore Cheats\\Main\\*")) : meme == 1 ? (std::string(path) + ("\\Lore Cheats\\Skins\\*")) : (std::string(path) + ("\\Lore Cheats\\Colors\\*"));


	WIN32_FIND_DATA FindFileData;
	HANDLE hf;
	//configs.push_back("default.ini");

	hf = FindFirstFile(szPath1.c_str(), &FindFileData);
	if (hf != INVALID_HANDLE_VALUE) {
		do {
			std::string filename = FindFileData.cFileName;

			if (filename == ".")
				continue;

			if (filename == "..")
				continue;

			if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				if (filename.find(".ini") != std::string::npos)
				{
					configs.push_back(std::string(filename));
				}
			}
		} while (FindNextFile(hf, &FindFileData) != 0);
		FindClose(hf);
	}
}


static std::vector<char> ReadAllBytes(char const* filename)
{
	std::ifstream ifs(filename, std::ios::binary | std::ios::ate);
	std::ifstream::pos_type pos = ifs.tellg();

	std::vector<char>  result(pos);

	ifs.seekg(0, std::ios::beg);
	ifs.read(&result[0], pos);

	return result;
}


void DrawRagechildMeme(bool MenuNotOpened)
{
	ImGui::BeginChild(("RagebotChild1"), ImVec2(ImGui::GetWindowWidth() / 3 - 10, 0), true, MenuNotOpened ? ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar : ImGuiWindowFlags_NoResize | ImGuiWindowFlags_ShowBorders);
	{
		
		static bool Main = true;
		static bool Accuracy = false;
		static bool HitScan = false;


		static bool  WeapCFG = false;

		ImGuiStyle& style = ImGui::GetStyle();


		style.ItemSpacing = ImVec2(1, 1);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.1f, 0.1f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.2f, 0.2f, 0.8f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.2f, 0.2f, 1.f));


		if (ImGui::Button(("Main"), ImVec2(ImGui::GetWindowWidth() / 3 - 3, 22)))
		{
			Main = true;
			Accuracy = false;
			HitScan = false;
		};
		ImGui::SameLine();
		if (ImGui::Button(("Accuracy"), ImVec2(ImGui::GetWindowWidth() / 3 - 3, 22)))
		{
			Main = false;
			Accuracy = true;
			HitScan = false;
		};
		ImGui::SameLine();
		if (ImGui::Button(("Hitscan"), ImVec2(ImGui::GetWindowWidth() / 3 - 3, 22)))
		{
			Main = false;
			Accuracy = false;
			HitScan = true;
		};

		ImGui::Separator();
		ImGui::Text("  ");
		ImGui::PopStyleColor(); ImGui::PopStyleColor(); ImGui::PopStyleColor();
		style.ItemSpacing = ImVec2(8, 4);





		if (Main)
		{
			ImGui::Checkbox(("Enable"), &g_Options.Ragebot.Ragebot_AimbotEnabled);
			ImGui::Checkbox(("Silent-Aim"), &g_Options.Ragebot.Ragebot_SilentAim);
			ImGui::Checkbox("Improved Resolver", &g_Options.Ragebot.resolver);
			ImGui::Checkbox(("Auto Pistol"), &g_Options.Ragebot.AutoPistol);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(("auto click in attack key"));
			ImGui::Checkbox(("Auto Revolver"), &g_Options.Ragebot.AutoRevolver);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(("auto cocking"));

			ImGui::Checkbox(("No Interpolation"), &g_Options.Ragebot.LagComp);

			ImGui::Combo(("Selection"), &g_Options.Ragebot.Ragebot_Selection, ("fov\0\rdistance\0\rhealth\0\0"), -1, ImVec2(120, 0));
			ImGui::Combo(("Hitbox"), &g_Options.Ragebot.Ragebot_Hitbox, ("head\0\rneck\0\rchest\0\rpelvis\0\rarms\0\rlegs\0\rhitscan\0\0"), -1, ImVec2(120, 0));
			ImGui::Combo(("Autowall Type"), &g_Options.Ragebot.Ragebot_AutoWallMode, ("spravedlivii\0\rne spravedlivii\0\0"), -1, ImVec2(120, 0));
			

			

		}
		if (Accuracy)
		{

			ImGui::Checkbox(("Auto Shoot"), &g_Options.Ragebot.Ragebot_AutoShoot);
			ImGui::Checkbox(("Auto Scope"), &g_Options.Ragebot.Ragebot_Autoscope);

			

			ImGui::PushItemWidth(120);
			ImGui::SliderFloat(("Hit Chance"), &g_Options.Ragebot.Ragebot_Hitchance, 1.f, 100.f);
			ImGui::SliderFloat(("Min Damage"), &g_Options.Ragebot.Ragebot_MinDamage, 1.f, 100.f);
			ImGui::PopItemWidth();
			
			ImGui::Checkbox(("Anti Aim correction"), &g_Options.Ragebot.Ragebot_Resolver);
			ImGui::Checkbox(("Override Resolver"), &g_Options.Ragebot.Ragebot_Knopka180);
			ImGui::Hotkey(("Key##overrideresolver"), &g_Options.Ragebot.Ragebot_Knopka180Val, ImVec2(120,20));

			ImGui::Checkbox(("Position Adjustment"), &g_Options.Ragebot.Ragebot_PositionAdjustment);
			
		}
		if (HitScan)
		{
	

			ImGui::Text("Custom Hitscan");
			ImGui::Separator();
			ImGui::Checkbox(("Head"), &g_Options.Ragebot.Ragebot_CustomHitscan[0]);
			ImGui::SameLine();
			ImGui::Checkbox(("Neck"), &g_Options.Ragebot.Ragebot_CustomHitscan[1]);

			ImGui::Checkbox(("Pelvis"), &g_Options.Ragebot.Ragebot_CustomHitscan[2]);
			ImGui::SameLine();
			ImGui::Checkbox(("Body"), &g_Options.Ragebot.Ragebot_CustomHitscan[3]);
		
			ImGui::Checkbox(("Arms"), &g_Options.Ragebot.Ragebot_CustomHitscan[4]);
			ImGui::SameLine();
			ImGui::Checkbox(("Legs"), &g_Options.Ragebot.Ragebot_CustomHitscan[5]);

			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::SameLine();
			ImGui::Spacing();
			ImGui::Spacing();




			ImGui::Columns(2, NULL, false);

			ImGui::Text("Multipoint:");

			ImGui::Checkbox(("Head "), &g_Options.Ragebot.MP[0]);
			ImGui::Checkbox(("Neck "), &g_Options.Ragebot.MP[1]);
			ImGui::Checkbox(("Pelvis "), &g_Options.Ragebot.MP[2]);
			ImGui::Checkbox(("Body "), &g_Options.Ragebot.MP[3]);
			ImGui::Checkbox(("Arms "), &g_Options.Ragebot.MP[4]);
			ImGui::Checkbox(("Legs "), &g_Options.Ragebot.MP[5]);

			ImGui::NextColumn();

			ImGui::Text("Scale:");


			SliderFloatFSTCustom(("##mps0"), g_Options.Ragebot.MPs[0], 0.01f, 1.f, 100);
			SliderFloatFSTCustom(("##mps1"), g_Options.Ragebot.MPs[1], 0.01f, 1.f, 100);
			SliderFloatFSTCustom(("##mps2"), g_Options.Ragebot.MPs[2], 0.01f, 1.f, 100);
			SliderFloatFSTCustom(("##mps3"), g_Options.Ragebot.MPs[3], 0.01f, 1.f, 100);
			SliderFloatFSTCustom(("##mps4"), g_Options.Ragebot.MPs[4], 0.01f, 1.f, 100);
			SliderFloatFSTCustom(("##mps5"), g_Options.Ragebot.MPs[5], 0.01f, 1.f, 100);

			ImGui::NextColumn();

		}


	}ImGui::EndChild();
	ImGui::SameLine();
	ImGui::BeginChild(("RagebotChild2"), ImVec2(ImGui::GetWindowWidth() / 3 - 10, 0), true, MenuNotOpened ? ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar : ImGuiWindowFlags_NoResize | ImGuiWindowFlags_ShowBorders);
	{
		static bool Stand = true;
		static bool Move = false;
		static bool Edge = false;
		static bool Misc = false;

		ImGui::Text("Anti Aim System");
		ImGui::Separator();

		ImGui::Checkbox(("Atand AA Wnabled"), &g_Options.Ragebot.AntiAim_Enabled);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip((" enable stand antiaim \n if you have velocity < 85 - aa type = stand antiaims"));

		ImGui::Checkbox(("Move AA Enabled"), &g_Options.Ragebot.AntiAim_EnabledMove);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip((" enable move antiaim \n if you have velocity > 85 - aa type = move antiaims"));

		ImGui::Checkbox(("Edge AA Enabled"), &g_Options.Ragebot.AntiAim_EnabledEdge);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip((" enable edge antiaim \n if you are near the wall - aa type = edge antiaims"));
		

		ImGui::Hotkey(("Override AA Key"),&g_Options.Ragebot.Ragebot_Knopka180ValAA, ImVec2(160,20));

		ImGui::Separator();

		ImGuiStyle& style = ImGui::GetStyle();
		style.ItemSpacing = ImVec2(1, 1);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.1f, 0.1f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.2f, 0.2f, 0.8f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.2f, 0.2f, 1.f));


		ImGui::PushStyleColor(ImGuiCol_Button, Stand ? ImVec4(0.25f, 0.25f, 0.25f, 1.f) : ImVec4(0.1f, 0.1f, 0.1f, 1.f));

		if (ImGui::Button(("Stand"), ImVec2(ImGui::GetWindowWidth() / 4 - 3, 22)))
		{
			Stand = true;
			Move = false;
			Misc = false;
			Edge = false;
		};

		ImGui::PopStyleColor();

		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, Move ? ImVec4(0.25f, 0.25f, 0.25f, 1.f) : ImVec4(0.1f, 0.1f, 0.1f, 1.f));

		if (ImGui::Button(("Move"), ImVec2(ImGui::GetWindowWidth() / 4 - 3, 22)))
		{
			Stand = false;
			Move = true;
			Misc = false;
			Edge = false;
		};

		ImGui::PopStyleColor();

		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, Edge ? ImVec4(0.25f, 0.25f, 0.25f, 1.f) : ImVec4(0.1f, 0.1f, 0.1f, 1.f));
		if (ImGui::Button(("Edge"), ImVec2(ImGui::GetWindowWidth() / 4 - 3, 22)))
		{
			Stand = false;
			Move = false;
			Misc = false;
			Edge = true;
		};
		ImGui::PopStyleColor();


		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Button, Misc ? ImVec4(0.25f, 0.25f, 0.25f, 1.f) : ImVec4(0.1f, 0.1f, 0.1f, 1.f));
		if (ImGui::Button(("Misc"), ImVec2(ImGui::GetWindowWidth() / 4 - 3, 22)))
		{
			Stand = false;
			Move = false;
			Misc = true;
			Edge = false;
		};
		ImGui::PopStyleColor();

		ImGui::Text("  ");

		ImGui::PopStyleColor(); ImGui::PopStyleColor(); ImGui::PopStyleColor();
		style.ItemSpacing = ImVec2(8, 4);

		
		if (Stand)
		{
			
			ImGui::Combo(("Pitch"), &g_Options.Ragebot.AntiAim_Pitch, ("none\0\rdown\0\rup\0\rminimal\0\rfake down\0\rfake up\0\rfake zero\0\rdownup\0\0"), -1, ImVec2(120, 0));
			
		
			
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(("head angles x"));

		

			
			ImGui::Combo(("Real Yaw"), &g_Options.Ragebot.AntiAim_Yaw, "none\0\rbackwards\0\rbackwards jitter\0\rsideways\0\rfake lowerbody\0\rsquare jitter\0\0", -1, ImVec2(120, 0));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(("real angles y"));

			
			ImGui::PushItemWidth(120); ImGui::SliderInt(("Add Real Yaw"), &g_Options.Ragebot.Ragebot_AddRealYaw, -180, 180); ImGui::PopItemWidth();
			
			

			ImGui::Combo(("Fake yaw"), &g_Options.Ragebot.AntiAim_FakeYaw, "none\0\rbackwards\0\rbackwards jitter\0\rsideways\0\rfake lowerBody\0\rsquare jitter\0\0", -1, ImVec2(120, 0));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(("fake angles Y"));

			ImGui::PushItemWidth(120); ImGui::SliderInt(("Add Fake yaw"), &g_Options.Ragebot.Ragebot_AddFakeYaw, -180, 180); ImGui::PopItemWidth();

			ImGui::Checkbox(("At Targets"), &g_Options.Ragebot.AntiAim_AtTargets);
			

		}
		if (Move)
		{
			
			ImGui::Combo(("Pitch"), &g_Options.Ragebot.AntiAim_PitchMove, ("none\0\rdown\0\rup\0\rminimal\0\rfake down\0\rfake up\0\rfake zero\0\rdownup\0\0"), -1, ImVec2(120, 0));



			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(("head angles x"));




			ImGui::Combo(("Real Yaw"), &g_Options.Ragebot.AntiAim_YawMove, "none\0\rbackwards\0\rbackwards jitter\0\rsideways\0\rfake lowerbody\0\rsquare jitter\0\0", -1, ImVec2(120, 0));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(("Real Angles Y"));

			ImGui::PushItemWidth(120); ImGui::SliderInt(("Add Real Yaw"), &g_Options.Ragebot.Ragebot_AddRealYawMove, -180, 180); ImGui::PopItemWidth();

			ImGui::Combo(("Fake Yaw"), &g_Options.Ragebot.AntiAim_FakeYawMove, "none\0\rbackwards\0\rbackwards jitter\0\rsideways\0\rfake lowerBody\0\rsquare jitter\0\0", -1, ImVec2(120, 0));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(("fake angles y"));

			ImGui::PushItemWidth(120); ImGui::SliderInt(("Add Fake Yaw"), &g_Options.Ragebot.Ragebot_AddFakeYawMove, -180, 180); ImGui::PopItemWidth();

			ImGui::Checkbox(("At Targets"), &g_Options.Ragebot.AntiAim_AtTargetsMove);

		}
		if (Edge)
		{
			
			ImGui::Combo(("Pitch"), &g_Options.Ragebot.AntiAim_PitchEdge, ("none\0\rdown\0\rup\0\rminimal\0\rfake down\0\rfake up\0\rfake zero\0\rdownup\0\0"), -1, ImVec2(120, 0));



			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(("Head angles X"));




			ImGui::Combo(("Real Yaw"), &g_Options.Ragebot.AntiAim_YawEdge, "none\0\rbackwards\0\rbackwards jitter\0\rsideways\0\rfake lowerbody\0\rsquare jitter\0\0", -1, ImVec2(120, 0));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(("Real Angles Y"));

			ImGui::PushItemWidth(120); ImGui::SliderInt(("Add Real Yaw"), &g_Options.Ragebot.Ragebot_AddRealYawEdge, -180, 180); ImGui::PopItemWidth();

			ImGui::Combo(("Fake Yaw"), &g_Options.Ragebot.AntiAim_FakeYawEdge, "none\0\rbackwards\0\rbackwards jitter\0\rsideways\0\rfake lowerBody\0\rsquare jitter\0\0", -1, ImVec2(120, 0));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(("Fake Angles Y"));

			ImGui::PushItemWidth(120); ImGui::SliderInt(("Add Fake Yaw"), &g_Options.Ragebot.Ragebot_AddFakeYawEdge, -180, 180); ImGui::PopItemWidth();
		}
		if (Misc)
		{
			
			ImGui::Checkbox(("Moon Walk"), &g_Options.Ragebot.Ragebot_MoonWalk);
			ImGui::Checkbox(("Fake Walk"), &g_Options.Ragebot.Ragebot_FakeWalk);
			if (g_Options.Ragebot.Ragebot_FakeWalk)
			{
				ImGui::Hotkey(("Key   "),&g_Options.Ragebot.Ragebot_FakeWalkKey,ImVec2(120,20));
			}
			SliderFloatFST(("LBY Delta"), g_Options.Ragebot.Ragebot_LBYDELTA, 0.f, 180.f); 
		}


	}ImGui::EndChild();
	ImGui::SameLine();
	ImGui::BeginChild(("RagebotChild3"), ImVec2(ImGui::GetWindowWidth() / 3 - 10, 0), true, MenuNotOpened ? ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar : ImGuiWindowFlags_NoResize | ImGuiWindowFlags_ShowBorders);
	{
		ImGui::Text("Body Aim Settings");
		ImGui::Separator();

	
		ImGui::Combo(("Prefer Baim"), &g_Options.Ragebot.Ragebot_PreferBodyAim, ("off\0\rsmart\0\ralways\0\0"), -1, ImVec2(120, 0));
		ImGui::PushItemWidth(120);
		ImGui::SliderInt(("After x Hp"), &g_Options.Ragebot.Ragebot_BodyAimAfterHP, 0, 100);
		ImGui::PopItemWidth();
		ImGui::Checkbox(("With AWP"), &g_Options.Ragebot.Ragebot_BodyAwp);
		ImGui::Checkbox(("When Fake"), &g_Options.Ragebot.BodyWhenFake);
		ImGui::Hotkey(("Body Key"),&g_Options.Ragebot.Ragebot_BodyKeyEnable, ImVec2(120,20));
		
	}ImGui::EndChild();
}
void DrawVisualschildMeme(bool MenuNotOpened)
{
	ImGui::BeginChild(("RagebotChild1"), ImVec2(ImGui::GetWindowWidth() / 3 - 10, 0), true, MenuNotOpened ? ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar : ImGuiWindowFlags_NoResize | ImGuiWindowFlags_ShowBorders);
	{

		static bool Main = true;
		static bool Colors = false;

		static int Page = 0;

		ImGuiStyle& style = ImGui::GetStyle();


		style.ItemSpacing = ImVec2(1, 1);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.1f, 0.1f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.2f, 0.2f, 0.8f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.2f, 0.2f, 1.f));

		const char* meme = "page : error";
		switch (Page)
		{
		case 0: meme = "Page : 1";  break;
		case 1: meme = "Page : 2";  break;
		case 2: meme = "Page : 3";  break;
		case 3: meme = "Page : 4";  break;
		case 4: meme = "Page : 5";  break;
		default: break;
		}

		ImGui::Text(meme); ImGui::SameLine(); ImGui::Text(("                     ")); ImGui::SameLine();
		if (ImGui::Button(("<"), ImVec2(22, 22)))
		{
			if (Page != 0)
				Page--;
		};
		ImGui::SameLine();
		if (ImGui::Button((">"), ImVec2(22, 22)))
		{
			if (Page != 3)
				Page++;
		};
		ImGui::Separator();
		ImGui::Text(("        "));

		ImGui::PopStyleColor(); ImGui::PopStyleColor(); ImGui::PopStyleColor();
		style.ItemSpacing = ImVec2(8, 4);
		

		switch (Page)
		{
		case 0:
		{
			ImGui::Checkbox(("Enable Visuals"), &g_Options.Visuals.Enabled);
			ImGui::Checkbox(("Team Esp"), &g_Options.Visuals.Visuals_EspTeam);
			ImGui::Checkbox(("Visible Only"), &g_Options.Visuals.Visuals_VisableOnly);



			ImGui::Checkbox(("Draw Box"), &g_Options.Visuals.Visuals_BoxEnabled);
			if (g_Options.Visuals.Visuals_BoxEnabled)
			{
				ImGui::Combo(("Box Type"), &g_Options.Visuals.Visuals_BoxType, ("full\0\rcorner\0\0"), -1, ImVec2(120, 0));
			}
			ImGui::Checkbox(("Draw Health Bar"), &g_Options.Visuals.Visuals_HealthBar);
			if (g_Options.Visuals.Visuals_HealthBar)
			{
				ImGui::Combo(("Healthbar Type"), &g_Options.Visuals.Visuals_HealthBarType, ("default\0\rseparator\0\0"), -1, ImVec2(120, 0));
			}
			ImGui::Checkbox(("Draw Ammo Bar"), &g_Options.Visuals.Visuals_AmmoESP);
			if (g_Options.Visuals.Visuals_AmmoESP)
			{
				ImGui::Combo(("Type##ammobar"), &g_Options.Visuals.Visuals_AmmoESPType, ("text\0\rbar\0\0"), -1, ImVec2(120, 0));
			}

			ImGui::Checkbox(("Draw name"), &g_Options.Visuals.Visuals_Name);
			ImGui::Checkbox(("Draw Armor"), &g_Options.Visuals.Visuals_ArmorBar);
			ImGui::Checkbox(("Draw Weapons"), &g_Options.Visuals.Visuals_Weapons);
			if (g_Options.Visuals.Visuals_Weapons)
			{
				ImGui::Combo(("Type##weapons"), &g_Options.Visuals.Visuals_WeaponsType, ("text\0\ricons\0\0"), -1, ImVec2(120, 0));
			}
			ImGui::Checkbox(("Draw Skeleton"), &g_Options.Visuals.Visuals_Skeltal);
			



		}break;
		case 1:
		{
			ImGui::Checkbox(("Draw Aimlines"), &g_Options.Visuals.Visuals_AimLines);
			ImGui::Checkbox(("Draw Bomb"), &g_Options.Visuals.Visuals_C4);
			ImGui::Checkbox(("Draw Beam Tracer"), &g_Options.Visuals.Visuals_DrawBeams);
			if (g_Options.Visuals.Visuals_DrawBeams)
			{
				SliderFloatFST(("Duration ##beamtracer"), g_Options.Visuals.Visuals_DrawBeamsDuration, 1.f, 10.f);
				SliderFloatFST(("Size ##beamtracer"), g_Options.Visuals.Visuals_DrawBeamsSize, 0.1f, 10.f);

			}
			ImGui::Checkbox(("Draw Hit-Capsule"), &g_Options.Visuals.Visuals_DrawCapsules);
			if (g_Options.Visuals.Visuals_DrawCapsules)
			{
				SliderFloatFST(("Duration ##hitcapsule"), g_Options.Visuals.Visuals_DrawCapsulesDuration, 1.f, 10.f);
			}
			ImGui::Checkbox(("Draw Hit-Marker"), &g_Options.Visuals.Visuals_Hitmarker);
			ImGui::Checkbox(("Draw Event Log"), &g_Options.Visuals.Visuals_DrawEventLog);
			if (g_Options.Visuals.Visuals_DrawEventLog) {
				ImGui::BeginChild(("Filter"), ImVec2(ImGui::GetWindowContentRegionWidth() * 0.5f, 21 * 4)); {
					ImGui::Selectable("Buy Log", &g_Options.Visuals.purchaselog);
					ImGui::Selectable("Kils Log", &g_Options.Visuals.killlog);
					ImGui::Selectable("Damage Log", &g_Options.Visuals.damagelog);
					ImGui::Selectable("Connect Log", &g_Options.Visuals.connectlog);
					ImGui::Selectable("Bomb Log", &g_Options.Visuals.bomblog);
				}
				ImGui::EndChild();
			}
			
			ImGui::Checkbox(("Draw Spread"), &g_Options.Visuals.Visuals_Spread);
			if (g_Options.Visuals.Visuals_Spread)
			{
				ImGui::Combo(("Draw Spread Type"), &g_Options.Visuals.Visuals_Spread_Type, ("outline\0\rfilled\0\0"), -1, ImVec2(120, 0));
			}
			ImGui::Checkbox(("Grenade Prediction"), &g_Options.Visuals.Visuals_GrenadePrediction);
			ImGui::Checkbox(("Draw Damage"), &g_Options.Visuals.Visuals_DamageESP);
		}break;
		case 2:
		{
			/*ImGui::Checkbox(("enable sound esp"), &g_Options.Visuals.SoundESP.Enabled);
			if (g_Options.Visuals.SoundESP.Enabled)
			{
				ImGui::Combo(("Sound esp type"), &g_Options.Visuals.SoundESP.type, ("rect\0\rwawes\0\0"), -1, ImVec2(120, 0));
				SliderFloatFST((" Distance"), g_Options.Visuals.SoundESP.Distance, 50.f, 1500.f);
				SliderFloatFST((" Radius"), g_Options.Visuals.SoundESP.Radius, 5.f, 25.f);
				ImGui::Checkbox(("Animated"), &g_Options.Visuals.SoundESP.Animated);
				ImGui::SameLine();
				ImGui::Checkbox(("Novis. Only"), &g_Options.Visuals.SoundESP.visonly);

			}*/
			//ImGui::Separator();
			ImGui::Checkbox(("Engine Radar"), &g_Options.Visuals.Visuals_EngineRadar);
			//ImGui::SliderInt("X-Axys", &g_Options.Visuals.x, 0, 200);
			//ImGui::SliderInt("Y-Axys", &g_Options.Visuals.y, 0, 200);
			ImGui::Checkbox(("External Radar"), &g_Options.Visuals.Panels.Radar.ExternalRadar);
			ImGui::Combo(("Style"), &g_Options.Visuals.Panels.Radar.RadarStyle, ("box\0filled box\0circle\0filled circle\0\0"), -1, ImVec2(120, 0));
			SliderFloatFST(("##RadarDistance"), g_Options.Visuals.Panels.Radar.RadarDistance, 0.1f, 5.0f);
			ImGui::Checkbox(("Visible Only"), &g_Options.Visuals.Panels.Radar.RadarVisibleOnly);
			ImGui::Checkbox(("Smoke Check"), &g_Options.Visuals.Panels.Radar.RadarSmoke);
			ImGui::Separator();
			//ImGui::Checkbox(("Monitor info"), &g_Options.Visuals.Panels.Monitor);
		}break;
		case 3:
		{
			ImGui::Checkbox(("Lower Body Indicator"), &g_Options.Visuals.lbyIndicator);
			ImGui::Checkbox(("Arrows Indicator"), &g_Options.Visuals.strelkiIndicator);

			
		}break;

		default:break;
		}
	

	}ImGui::EndChild();
	ImGui::SameLine();
	ImGui::BeginChild(("RagebotChild2"), ImVec2(ImGui::GetWindowWidth() / 3 - 10, 0), true, MenuNotOpened ? ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar : ImGuiWindowFlags_NoResize | ImGuiWindowFlags_ShowBorders);
	{
	
		ImGui::Checkbox(("Chams"), &g_Options.Visuals.Visuals_Chams);
		ImGui::Checkbox(("Chams On Teammates"), &g_Options.Visuals.Visuals_ChamsTeam);
		ImGui::Checkbox(("Chams On Guns"), &g_Options.Visuals.Visuals_ChamsGuns);
		ImGui::Checkbox(("Chams Vis. Only"), &g_Options.Visuals.Visuals_ChamsXQZ);
		ImGui::Checkbox(("Chams On Local Dakes"), &g_Options.Visuals.Visuals_GhostAngle);
		ImGui::Combo(("Chams Material"), &g_Options.Visuals.Visuals_ChamsMaterial, ("flat\0\rtextured\0\rgold\0\rmaterial\0\rdogtags outline\0\rglass\0\0"), -1, ImVec2(120, 0));
		ImGui::Separator();

		ImGui::Checkbox(("Glow"), &g_Options.Visuals.Vis_Glow);
		ImGui::Checkbox(("Glow Teammates"), &g_Options.Visuals.Vis_Glow_Team);
		ImGui::Checkbox(("Glow Vis. Only"), &g_Options.Visuals.Vis_Glow_Vis);

		


		ImGui::Separator();
		ImGui::Text("Others");
		
		
		ImGui::Checkbox(("Night Mode"), &g_Options.Visuals.Visuals_NightMode);
		ImGui::Checkbox(("Asus Mode"), &g_Options.Visuals.Visuals_Asus);
		ImGui::Separator();
	}ImGui::EndChild();
	ImGui::SameLine();
	ImGui::BeginChild(("RagebotChild3"), ImVec2(ImGui::GetWindowWidth() / 3 - 10, 0), true, MenuNotOpened ? ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar : ImGuiWindowFlags_NoResize | ImGuiWindowFlags_ShowBorders);
	{

		ImGui::Checkbox(("Scoped Info"), &g_Options.Visuals.Visuals_Scoped);
		ImGui::Checkbox(("Flashed Info"), &g_Options.Visuals.Visuals_Flashed);
		ImGui::Checkbox(("Defuser Info"), &g_Options.Visuals.Visuals_Defuser);

		
		ImGui::Checkbox(("Anti-Aim Lines(Buggy)"), &g_Options.Visuals.Visuals_DrawLinesAA);
		ImGui::Checkbox(("Dropped Weapons"), &g_Options.Visuals.Visuals_DroppedWeapons);
		ImGui::Checkbox(("No-Visual Recoil"), &g_Options.Visuals.Visuals_NoRecoil);

		ImGui::Checkbox(("No-Flash"), &g_Options.Visuals.Visuals_NoFlash);
		ImGui::Checkbox(("No-Smoke"), &g_Options.Visuals.Visuals_NoSmoke);
		if(g_Options.Visuals.Visuals_NoSmoke)
			ImGui::Checkbox(("set no-smoke wireframe var"), &g_Options.Visuals.Visuals_NoSmokeVar);

		ImGui::Checkbox(("No-Scope"), &g_Options.Visuals.Visuals_NoScope);
		ImGui::Checkbox(("No-Zoom"), &g_Options.Visuals.Visuals_NoZoom);
		ImGui::Checkbox(("No-PostProcess"), &g_Options.Visuals.Visuals_NoPostProcess);
		ImGui::Checkbox("OffScreenESP", &g_Options.Visuals.OffscreenIndicator);


		ImGui::Checkbox(("Crosshair"), &g_Options.Visuals.Visuals_Crosshair);
		if(g_Options.Visuals.Visuals_Crosshair)
		ImGui::Checkbox(("Crosshair->Dynamic"), &g_Options.Visuals.Visuals_CrosshairDynamic);

		/*ImGui::Checkbox(("Sky Change"), &g_Options.Visuals.Visuals_Sky);
		if (g_Options.Visuals.Visuals_Sky)
		ImGui::Combo(("Sky"), &g_Options.Visuals.Visuals_SkyVal, ("NoSky\0\rNight\0\rNight2\0\0"), -1, ImVec2(120, 0));*/



	}ImGui::EndChild();

}
void DrawMiscchildMeme(bool MenuNotOpened)
{
	ImGui::BeginChild(("RagebotChild1"), ImVec2(ImGui::GetWindowWidth() / 3 - 10, 0), true, MenuNotOpened ? ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar : ImGuiWindowFlags_NoResize | ImGuiWindowFlags_ShowBorders);
	{
		
		static bool Main = true;
		static bool Colors = false;
		static bool Colors1 = false;
		static bool meme1 = true;
		static bool meme2 = false;
		static bool meme3 = false;
		static bool misc = false;

		ImGuiStyle& style = ImGui::GetStyle();


		style.ItemSpacing = ImVec2(1, 1);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.1f, 0.1f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.2f, 0.2f, 0.8f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.2f, 0.2f, 1.f));

		if (ImGui::Button(("Main"), ImVec2(ImGui::GetWindowWidth() / 3 - 5, 22)))
		{
			Main = true;
			Colors = false;
			Colors1 = false;
			misc = false;
		};
		ImGui::SameLine();

		if (ImGui::Button(("Movement"), ImVec2(ImGui::GetWindowWidth() / 3 - 5, 22)))
		{
			Main = false;
			Colors = false;
			Colors1 = true;
			misc = false;
		};
		ImGui::SameLine();
		if (ImGui::Button(("Misc"), ImVec2(ImGui::GetWindowWidth() / 3 - 5, 22)))
		{
			Main = false;
			Colors = false;
			Colors1 = false;
			misc = true;

		};

		ImGui::Separator();
		ImGui::Text(("        "));

		ImGui::PopStyleColor(); ImGui::PopStyleColor(); ImGui::PopStyleColor();
		style.ItemSpacing = ImVec2(8, 4);

	

		if (Main)
		{
			//ImGui::Separator();
			ImGui::Checkbox(("Anti Untrusted"), &g_Options.Misc.AntiCheats.AntiUntrusted);
			ImGui::Checkbox(("Menu Animations"), &g_Options.Menu.Animations);
			//ImGui::Checkbox(("skin-changer window"), &g_Options.Menu.SkinChangerWindow);

			ImGui::Checkbox(("Auto-Accept"), &g_Options.Misc.Misc_AutoAccept);
			//ImGui::SameLine();
			ImGui::Checkbox(("Knife-Bot"), &g_Options.Misc.Misc_KnifeBot);
			ImGui::Checkbox(("Spectator List"), &g_Options.Misc.SpectatorList);
			//ImGui::SameLine();
			ImGui::Checkbox(("Show Ranks"), &g_Options.Misc.Misc_Ranks);
			ImGui::Checkbox(("Playerlist"), &g_Options.Players.Playerlist);

			

			ImGui::Separator();


			ImGui::Checkbox(("Third-person"), &g_Options.Misc.Visuals_ThirdPerson);
			ImGui::Hotkey(("Key   "), &g_Options.Misc.Visuals_ThirdPersonKey, ImVec2(120, 20));
			SliderIntFST(("Third-Person Dist"), g_Options.Misc.Visuals_ThirdPersonDistance, 0, 300);
			ImGui::Combo(("Show angle"), &g_Options.Misc.Visuals_ThirdPersonAngle, ("fake\0\rreal\0\rlowerbody\0\0"), -1, ImVec2(120, 0));

			SliderIntFST(("Override Fov"), g_Options.Misc.Misc_Fov, 0, 40);
			SliderIntFST(("Viewmodel Fov"), g_Options.Misc.ViewModelFov, 0, 150);
			

			

		}
		
		if (Colors1)
		{
			//ImGui::Separator();
			
			ImGui::Checkbox(("Auto-jump"), &g_Options.Misc.Misc_AutoJump);
			if (g_Options.Misc.Misc_AutoJump)
				ImGui::Checkbox(("Auto-strafe"), &g_Options.Misc.Misc_AutoStrafe);
			if (g_Options.Misc.Misc_AutoStrafe && g_Options.Misc.Misc_AutoJump)
				ImGui::Combo(("Strafe type"), &g_Options.Misc.Misc_AutoStraferMode, ("silent\0\rnormal\0\rsideways\0\rforward\0\0"), -1, ImVec2(120, 0));


			ImGui::Separator();


			ImGui::Combo(("Fakelag Type"), &g_Options.Misc.FakeLag.Misc_FakeLag, ("off\0\rfactor\0\rsmart\0\radaptive\0\rswitch\0\radaptive2\0\rmaximum\0\0"), -1, ImVec2(120, 0));
			SliderIntFST(("Fakelag Factor"), g_Options.Misc.FakeLag.Misc_FakeLagFactor, 0, 14);

			

			//ImGui::Separator();
		}

		if (misc) {

			ImGui::Checkbox(("TrashTalk"), &g_Options.Misc.TrashTalk);
			ImGui::Checkbox(("EndRound Talk"), &g_Options.Misc.EndRoundTalk);
			ImGui::PushItemWidth(120);
			ImGui::SliderInt("Interval", &g_Options.Misc.talk, 0, 20);

			ImGui::Combo(("ClanTag"), &g_Options.Misc.clantagselection, ("Off\0\rLore-Cheats\0\rAnimated\0\rCustom\0\rC. Animated\0\0"), -1, ImVec2(120, 0));

			if (g_Options.Misc.clantagselection == 0)
			{
				setclantag("");
			}
			else if (g_Options.Misc.clantagselection == 1)
			{
				setclantag("Lored");
			}
			else if (g_Options.Misc.clantagselection == 2)
			{

			}
			else if (g_Options.Misc.clantagselection == 3)
			{
				ImGui::InputText("ClanTag", g_Options.Misc.ClanTag, 12);

				if (ImGui::Button("Change ClanTag"), &g_Options.Misc.ClanTagOn)
					setclantag(g_Options.Misc.ClanTag);


			}
			else if (g_Options.Misc.clantagselection == 4)
			{
				ImGui::InputText("ClanTag", g_Options.Misc.ClanTag, 12);

				std::stringstream ss;
				ss << g_Options.Misc.ClanTag;
				ss >> ClanTagS;



			}

			
			ImGui::Checkbox("Buy Bot", &g_Options.Misc.BuyBot);
			ImGui::Combo("##Buy Bot", &g_Options.Misc.item, "Off\0\rAk47\0\0");

		}

	}ImGui::EndChild();
	ImGui::SameLine();

	ImGui::BeginChild(("RagebotChild3"), ImVec2(0, 0), true, MenuNotOpened ? ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar : ImGuiWindowFlags_NoResize | ImGuiWindowFlags_ShowBorders);
	{
		static int pages = 0;
		static int Subpages = 0;
		ImGuiStyle& style = ImGui::GetStyle();

		style.ItemSpacing = ImVec2(1, 1);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.1f, 0.1f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.2f, 0.2f, 0.8f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.2f, 0.2f, 1.f));

		if (ImGui::Button(("Config System"), ImVec2(ImGui::GetWindowWidth() / 2 - 5, 22)))
		{
			pages = 0;
			
		};
		ImGui::SameLine();
		if (ImGui::Button(("Custom Colors System"), ImVec2(ImGui::GetWindowWidth() / 2 - 5, 22)))
		{
			pages = 1;
			
		};
		
		

		ImGui::PopStyleColor(); ImGui::PopStyleColor(); ImGui::PopStyleColor();
		style.ItemSpacing = ImVec2(8, 4);

		if (pages == 0)
		{
			style.ItemSpacing = ImVec2(1, 1);
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.1f, 0.1f, 1.f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.2f, 0.2f, 0.8f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.2f, 0.2f, 1.f));

			if (ImGui::Button(("Main Settings"), ImVec2(ImGui::GetWindowWidth() / 3 - 5, 22)))
			{
				Subpages = 0;

			};
			ImGui::SameLine();
			if (ImGui::Button(("Skins"), ImVec2(ImGui::GetWindowWidth() / 3 - 5, 22)))
			{
				Subpages = 1;

			};
			ImGui::SameLine();
			if (ImGui::Button(("Colors"), ImVec2(ImGui::GetWindowWidth() / 3 - 5, 22)))
			{
				Subpages = 2;

			};
			ImGui::PopStyleColor(); ImGui::PopStyleColor(); ImGui::PopStyleColor();
			style.ItemSpacing = ImVec2(8, 4);

			ImGui::Text("");
			if (Subpages == 0)
			{
				
		

			GetConfigMassive(maincfg);

			static int selectedcfg = 0;
			static std::string cfgname = "new main cfg";


			if (ImGui::ListBox("##selectcfg ", &selectedcfg, [](void* data, int idx, const char** out_text)
			{
				*out_text = configs[idx].c_str();
				return true;
			}, nullptr, configs.size(), 5))
			{
				cfgname = configs[selectedcfg];
				cfgname.erase(cfgname.length() - 4, 4);
				strcpy(g_Options.Misc.configname, cfgname.c_str());
			}

			ImGui::PushItemWidth(280); ImGui::InputText(("name"), g_Options.Misc.configname, 128); ImGui::PopItemWidth();

			if (ImGui::Button(("Save"), ImVec2(100.f, 20.f))) pConfig->Save(maincfg);
			ImGui::SameLine();
			if (ImGui::Button(("Load"), ImVec2(100.f, 20.f))) {
				pConfig->Load(maincfg);
			}
			ImGui::SameLine();
			if (ImGui::Button(("Delete"), ImVec2(100.f, 20.f))) {
				pConfig->Delete(maincfg);
			}

			static bool rename = false;
			if (!rename)
			{
				if (ImGui::Button(("Rename"), ImVec2(100.f, 20.f))) rename = true;
			}
			else
			{
				static char newnamecfg[128] = "new name config";

				if (ImGui::Button(("Apply"), ImVec2(100.f, 20.f)))
				{
					rename = false; pConfig->Rename(newnamecfg, maincfg);
				}
				ImGui::SameLine();
				ImGui::PushItemWidth(160); ImGui::InputText(("new name"), newnamecfg, 128); ImGui::PopItemWidth();
			}

		}

			if (Subpages == 1)
			{
					
				GetConfigMassive(skincfg);

				static int selectedcfg = 0;
				static std::string cfgname = "new skin cfg";


				if (ImGui::ListBox("##selectcfg ", &selectedcfg, [](void* data, int idx, const char** out_text)
				{
					*out_text = configs[idx].c_str();
					return true;
				}, nullptr, configs.size(), 5))
				{
					cfgname = configs[selectedcfg];
					cfgname.erase(cfgname.length() - 4, 4);
					strcpy(g_Options.Misc.confignameskins, cfgname.c_str());
				}

				ImGui::PushItemWidth(280); ImGui::InputText(("name"), g_Options.Misc.confignameskins, 128); ImGui::PopItemWidth();

				if (ImGui::Button(("Save"), ImVec2(100.f, 20.f))) pConfigSkins->Save(skincfg);
				ImGui::SameLine();
				if (ImGui::Button(("Load"), ImVec2(100.f, 20.f))) {
					pConfigSkins->Load(skincfg); g_Skinchanger->ForceItemUpdates();
				}
				ImGui::SameLine();
				if (ImGui::Button(("Delete"), ImVec2(100.f, 20.f))) {
					pConfigSkins->Delete(skincfg);
				}

				static bool rename = false;
				if (!rename)
				{
					if (ImGui::Button(("Rename"), ImVec2(100.f, 20.f))) rename = true;
				}
				else
				{
					static char newnamecfg[128] = "new name config";

					if (ImGui::Button(("Apply"), ImVec2(100.f, 20.f)))
					{
						rename = false; pConfigSkins->Rename(newnamecfg, skincfg);
					}
					ImGui::SameLine();
					ImGui::PushItemWidth(160); ImGui::InputText(("new name"), newnamecfg, 128); ImGui::PopItemWidth();
				}

			}
			if (Subpages == 2)
			{

				GetConfigMassive(3);

				static int selectedcfg = 0;
				static std::string cfgname = "new skin cfg";


				if (ImGui::ListBox("##selectcfg ", &selectedcfg, [](void* data, int idx, const char** out_text)
				{
					*out_text = configs[idx].c_str();
					return true;
				}, nullptr, configs.size(), 5))
				{
					cfgname = configs[selectedcfg];
					cfgname.erase(cfgname.length() - 4, 4);
					strcpy(g_Options.Misc.confignameColors, cfgname.c_str());
				}

				ImGui::PushItemWidth(280); ImGui::InputText(("name"), g_Options.Misc.confignameColors, 128); ImGui::PopItemWidth();

				if (ImGui::Button(("Save"), ImVec2(100.f, 20.f)))
				{


					
					DeclareToSave(pConfigColors->CTBoxVisable,Hacks.Colors.CTBoxVisable);
					DeclareToSave(pConfigColors->CTBoxInVisable, Hacks.Colors.CTBoxInVisable);
					DeclareToSave(pConfigColors->TBoxVisable, Hacks.Colors.TBoxVisable);
					DeclareToSave(pConfigColors->TBoxInVisable, Hacks.Colors.TBoxInVisable);
					DeclareToSave(pConfigColors->CTGlowVisable, Hacks.Colors.CTGlowVisable);
					DeclareToSave(pConfigColors->CTGlowInVisable, Hacks.Colors.CTGlowInVisable);
					DeclareToSave(pConfigColors->TGlowVisable, Hacks.Colors.TGlowVisable);
					DeclareToSave(pConfigColors->TGlowInVisable, Hacks.Colors.TGlowInVisable);
					DeclareToSave(pConfigColors->Beams, Hacks.Colors.Beams);
					DeclareToSave(pConfigColors->FilledSpread, Hacks.Colors.FilledSpread);
					DeclareToSave(pConfigColors->LagCompHitboxes, Hacks.Colors.LagCompHitboxes);
					DeclareToSave(pConfigColors->SoundESP, Hacks.Colors.SoundESP);
					DeclareToSave(pConfigColors->DamageESP, Hacks.Colors.DamageESP);
					DeclareToSave(pConfigColors->FakeAngleChams, Hacks.Colors.FakeAngleChams);
					DeclareToSave(pConfigColors->Stelki, Hacks.Colors.Stelki);

					DeclareToSave(pConfigColors->CTChamsVisable, Hacks.Colors.CTChamsVisable);
					DeclareToSave(pConfigColors->CTChamsInVisable, Hacks.Colors.CTChamsInVisable);
					DeclareToSave(pConfigColors->TChamsVisable, Hacks.Colors.TChamsVisable);
					DeclareToSave(pConfigColors->TChamsInVisable, Hacks.Colors.TChamsInVisable);








					pConfigColors->Save();
				}
				ImGui::SameLine();
				if (ImGui::Button(("Load"), ImVec2(100.f, 20.f))) {
					pConfigColors->Load();

					
					
					DeclareToLoad(pConfigColors->CTBoxVisable, Hacks.Colors.CTBoxVisable);
					DeclareToLoad(pConfigColors->CTBoxInVisable, Hacks.Colors.CTBoxInVisable);
					DeclareToLoad(pConfigColors->TBoxVisable, Hacks.Colors.TBoxVisable);
					DeclareToLoad(pConfigColors->TBoxInVisable, Hacks.Colors.TBoxInVisable);
					DeclareToLoad(pConfigColors->CTGlowVisable, Hacks.Colors.CTGlowVisable);
					DeclareToLoad(pConfigColors->CTGlowInVisable, Hacks.Colors.CTGlowInVisable);
					DeclareToLoad(pConfigColors->TGlowVisable, Hacks.Colors.TGlowVisable);
					DeclareToLoad(pConfigColors->TGlowInVisable, Hacks.Colors.TGlowInVisable);
					DeclareToLoad(pConfigColors->Beams, Hacks.Colors.Beams);
					DeclareToLoad(pConfigColors->FilledSpread, Hacks.Colors.FilledSpread);
					DeclareToLoad(pConfigColors->LagCompHitboxes, Hacks.Colors.LagCompHitboxes);
					DeclareToLoad(pConfigColors->SoundESP, Hacks.Colors.SoundESP);
					DeclareToLoad(pConfigColors->DamageESP, Hacks.Colors.DamageESP);
		
					DeclareToLoad(pConfigColors->FakeAngleChams, Hacks.Colors.FakeAngleChams);
					DeclareToLoad(pConfigColors->Stelki, Hacks.Colors.Stelki);

					
					DeclareToLoad(pConfigColors->CTChamsVisable, Hacks.Colors.CTChamsVisable);
					DeclareToLoad(pConfigColors->CTChamsInVisable, Hacks.Colors.CTChamsInVisable);
					DeclareToLoad(pConfigColors->TChamsVisable, Hacks.Colors.TChamsVisable);
					DeclareToLoad(pConfigColors->TChamsInVisable, Hacks.Colors.TChamsInVisable);

				}
				ImGui::SameLine();
				if (ImGui::Button(("Delete"), ImVec2(100.f, 20.f))) {
					pConfigColors->Delete();
				}

				static bool rename = false;
				if (!rename)
				{
					if (ImGui::Button(("Rename"), ImVec2(100.f, 20.f))) rename = true;
				}
				else
				{
					static char newnamecfg[128] = "new name config";

					if (ImGui::Button(("Apply"), ImVec2(100.f, 20.f)))
					{
						rename = false; pConfigColors->Rename(newnamecfg);
					}
					ImGui::SameLine();
					ImGui::PushItemWidth(160); ImGui::InputText(("new name"), newnamecfg, 128); ImGui::PopItemWidth();
				}

			}
		}
		

		if (pages == 1)
		{
			ImGui::Text("");
			for (int i = 0; i < IM_ARRAYSIZE(colors); i++)
				colorNames[i] = colors[i].name;
			static int colorSelected = 0;
			
			ImGui::BeginChild(("RagebotChild4"), ImVec2(210, 0), 0.f, MenuNotOpened ? ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar : ImGuiWindowFlags_NoResize);
			{
				ImGui::PushItemWidth(195);
				ImGui::ListBox("##COLORSELECTION", &colorSelected, colorNames, IM_ARRAYSIZE(colorNames), 16);
				ImGui::PopItemWidth();
			}ImGui::EndChild();
			ImGui::SameLine();
			ImGui::BeginChild(("RagebotChild5"), ImVec2(0, 0), 0.f, MenuNotOpened ? ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar : ImGuiWindowFlags_NoResize);
			{
			ImGui::NextColumn();
			{
				/*
				float col[4] = { min(255.f, ColorForMenu(colorSelected).r() / 255.f),  min(255.f, ColorForMenu(colorSelected).g() / 255.f),  min(255.f, ColorForMenu(colorSelected).b() / 255.f),min(255.f, ColorForMenu(colorSelected).a() / 255.f) };

				 if(ColorPicker4New(col))

				ColorForMenu(colorSelected) = CColor((BYTE)(col[0] * 255), (BYTE)(col[1] * 255), (BYTE)(col[2] * 255), (BYTE)(col[3] * 255));*/

				

				
				float col[4];
				CColor Dcol = CColor(255, 255, 255, 255);

				switch (colorSelected)
				{
				case 0: 
					Dcol = Hacks.Colors.CTBoxVisable;
					col[0] = Dcol.r() / 255.f;
					col[1] = Dcol.g() / 255.f;
					col[2] = Dcol.b() / 255.f;
					col[3] = Dcol.a() / 255.f;
					if (ColorPicker4New(col))
						Hacks.Colors.CTBoxVisable = CColor(col[0] * 255.f, col[1] * 255.f, col[2] * 255.f, col[3] * 255.f); break;
				case 1: //if (ImGui::ColorEdit4("##meme", col,true,true))
					Dcol = Hacks.Colors.CTBoxInVisable;
					col[0] = Dcol.r() / 255.f;
					col[1] = Dcol.g() / 255.f;
					col[2] = Dcol.b() / 255.f;
					col[3] = Dcol.a() / 255.f;
					if (ColorPicker4New(col))
						Hacks.Colors.CTBoxInVisable = CColor(col[0] * 255.f, col[1] * 255.f, col[2] * 255.f, col[3] * 255.f); break;
				case 2:
					Dcol = Hacks.Colors.TBoxVisable;
					col[0] = Dcol.r() / 255.f;
					col[1] = Dcol.g() / 255.f;
					col[2] = Dcol.b() / 255.f;
					col[3] = Dcol.a() / 255.f;
					if (ColorPicker4New(col))
						Hacks.Colors.TBoxVisable = CColor(col[0] * 255.f, col[1] * 255.f, col[2] * 255.f, col[3] * 255.f); break;
				case 3: 
					Dcol = Hacks.Colors.TBoxInVisable;
					col[0] = Dcol.r() / 255.f;
					col[1] = Dcol.g() / 255.f;
					col[2] = Dcol.b() / 255.f;
					col[3] = Dcol.a() / 255.f;
					if (ColorPicker4New(col))
						Hacks.Colors.TBoxInVisable = CColor(col[0] * 255.f, col[1] * 255.f, col[2] * 255.f, col[3] * 255.f); break;
				case 4: 
					Dcol = Hacks.Colors.CTGlowVisable;
					col[0] = Dcol.r() / 255.f;
					col[1] = Dcol.g() / 255.f;
					col[2] = Dcol.b() / 255.f;
					col[3] = Dcol.a() / 255.f;
					if (ColorPicker4New(col))
						Hacks.Colors.CTGlowVisable = CColor(col[0] * 255.f, col[1] * 255.f, col[2] * 255.f, col[3] * 255.f); break;
				case 5: 
					Dcol = Hacks.Colors.CTGlowInVisable;
					col[0] = Dcol.r() / 255.f;
					col[1] = Dcol.g() / 255.f;
					col[2] = Dcol.b() / 255.f;
					col[3] = Dcol.a() / 255.f;
					if (ColorPicker4New(col))
						Hacks.Colors.CTGlowInVisable = CColor(col[0] * 255.f, col[1] * 255.f, col[2] * 255.f, col[3] * 255.f); break;
				case 6:
					Dcol = Hacks.Colors.TGlowVisable;
					col[0] = Dcol.r() / 255.f;
					col[1] = Dcol.g() / 255.f;
					col[2] = Dcol.b() / 255.f;
					col[3] = Dcol.a() / 255.f;
					if (ColorPicker4New(col))
						Hacks.Colors.TGlowVisable = CColor(col[0] * 255.f, col[1] * 255.f, col[2] * 255.f, col[3] * 255.f); break;

				case 7:
					Dcol = Hacks.Colors.TGlowInVisable;
					col[0] = Dcol.r() / 255.f;
					col[1] = Dcol.g() / 255.f;
					col[2] = Dcol.b() / 255.f;
					col[3] = Dcol.a() / 255.f;
					if (ColorPicker4New(col))
						Hacks.Colors.TGlowInVisable = CColor(col[0] * 255.f, col[1] * 255.f, col[2] * 255.f, col[3] * 255.f); break;
				case 8: 
					Dcol = Hacks.Colors.Beams;
					col[0] = Dcol.r() / 255.f;
					col[1] = Dcol.g() / 255.f;
					col[2] = Dcol.b() / 255.f;
					col[3] = Dcol.a() / 255.f;
					 if(ColorPicker4New(col))
					Hacks.Colors.Beams = CColor(col[0] * 255.f, col[1] * 255.f, col[2] * 255.f, col[3] * 255.f); break;
				case 9:
					Dcol = Hacks.Colors.FilledSpread;
					col[0] = Dcol.r() / 255.f;
					col[1] = Dcol.g() / 255.f;
					col[2] = Dcol.b() / 255.f;
					col[3] = Dcol.a() / 255.f;
					if (ColorPicker4New(col))
						Hacks.Colors.FilledSpread = CColor(col[0] * 255.f, col[1] * 255.f, col[2] * 255.f, col[3] * 255.f); break;

				case 10:
					Dcol = Hacks.Colors.LagCompHitboxes;
					col[0] = Dcol.r() / 255.f;
					col[1] = Dcol.g() / 255.f;
					col[2] = Dcol.b() / 255.f;
					col[3] = Dcol.a() / 255.f;
					if (ColorPicker4New(col))
						Hacks.Colors.LagCompHitboxes = CColor(col[0] * 255.f, col[1] * 255.f, col[2] * 255.f, col[3] * 255.f); break;
				case 11:
					Dcol = Hacks.Colors.CTChamsVisable;
					col[0] = Dcol.r() / 255.f;
					col[1] = Dcol.g() / 255.f;
					col[2] = Dcol.b() / 255.f;
					col[3] = Dcol.a() / 255.f;
					if (ColorPicker4New(col))
						Hacks.Colors.CTChamsVisable = CColor(col[0] * 255.f, col[1] * 255.f, col[2] * 255.f, col[3] * 255.f); break;
				case 12:
					Dcol = Hacks.Colors.CTChamsInVisable;
					col[0] = Dcol.r() / 255.f;
					col[1] = Dcol.g() / 255.f;
					col[2] = Dcol.b() / 255.f;
					col[3] = Dcol.a() / 255.f;
					if (ColorPicker4New(col))
						Hacks.Colors.CTChamsInVisable = CColor(col[0] * 255.f, col[1] * 255.f, col[2] * 255.f, col[3] * 255.f); break;
				case 13:
					Dcol = Hacks.Colors.TChamsVisable;
					col[0] = Dcol.r() / 255.f;
					col[1] = Dcol.g() / 255.f;
					col[2] = Dcol.b() / 255.f;
					col[3] = Dcol.a() / 255.f;
					if (ColorPicker4New(col))
						Hacks.Colors.TChamsVisable = CColor(col[0] * 255.f, col[1] * 255.f, col[2] * 255.f, col[3] * 255.f); break;
				case 14:
					Dcol = Hacks.Colors.TChamsInVisable;
					col[0] = Dcol.r() / 255.f;
					col[1] = Dcol.g() / 255.f;
					col[2] = Dcol.b() / 255.f;
					col[3] = Dcol.a() / 255.f;
					if (ColorPicker4New(col))
						Hacks.Colors.TChamsInVisable = CColor(col[0] * 255.f, col[1] * 255.f, col[2] * 255.f, col[3] * 255.f); break;
				case 15:
					Dcol = Hacks.Colors.FakeAngleChams;
					col[0] = Dcol.r() / 255.f;
					col[1] = Dcol.g() / 255.f;
					col[2] = Dcol.b() / 255.f;
					col[3] = Dcol.a() / 255.f;
					if (ColorPicker4New(col))
						Hacks.Colors.FakeAngleChams = CColor(col[0] * 255.f, col[1] * 255.f, col[2] * 255.f, col[3] * 255.f); break;
				case 16:
					Dcol = Hacks.Colors.SoundESP;
					col[0] = Dcol.r() / 255.f;
					col[1] = Dcol.g() / 255.f;
					col[2] = Dcol.b() / 255.f;
					col[3] = Dcol.a() / 255.f;
					if (ColorPicker4New(col))
						Hacks.Colors.SoundESP = CColor(col[0] * 255.f, col[1] * 255.f, col[2] * 255.f, col[3] * 255.f); break;
				case 17:
					Dcol = Hacks.Colors.DamageESP;
					col[0] = Dcol.r() / 255.f;
					col[1] = Dcol.g() / 255.f;
					col[2] = Dcol.b() / 255.f;
					col[3] = Dcol.a() / 255.f;
					if (ColorPicker4New(col))
						Hacks.Colors.DamageESP = CColor(col[0] * 255.f, col[1] * 255.f, col[2] * 255.f, col[3] * 255.f); break;
				case 18:
					Dcol = Hacks.Colors.Stelki;
					col[0] = Dcol.r() / 255.f;
					col[1] = Dcol.g() / 255.f;
					col[2] = Dcol.b() / 255.f;
					col[3] = Dcol.a() / 255.f;
					if (ColorPicker4New(col))
						Hacks.Colors.Stelki = CColor(col[0] * 255.f, col[1] * 255.f, col[2] * 255.f, col[3] * 255.f); break;

					
				default:break;

				}
				
			}
			}ImGui::EndChild();

		}
	}ImGui::EndChild();

}
const char* weap[] = {
	"Desert Eagle",
	"Dual Berettas",
	"Five Seven",
	"Glock 18",
	"Ak 47",
	"AUG",
	"AWP",
	"Famas",
	"G3SG1",
	"MP 5",
	"Galil",
	"M249",
	"M4A4",
	"MAC 10",
	"P90",
	"UMP 45",
	"XM 1014",
	"PP Bizon",
	"Mag 7",
	"Negev",
	"Sawed Off",
	"Tec 9",
	"P2000",
	"MP 7",
	"Nova",
	"P250",
	"SCAR 20",
	"SG 553",
	"SSG 08",
	"M4A1-S",
	"USP-S",
	"CZ75",
	"Revolver",
	"Bayonet",
	"Flip Knife",
	"Gut Knife",
	"Karambit",
	"M9 Bayonet",
	"Huntsman Knife",
	"Falchion Knife",
	"Bowie Knife",
	"Butterfly Knife",
	"Shadow Daggers",
	"Navaja Knife",
	"Stiletto Knife",
	"Ursus Knife",
	"Talon Knife"

};
std::string GetWeaponName3()
{
	int id = g_Options.wpn;

	switch (id)
	{
	case WEAPON_DEAGLE:
		return ("desert eagle");
	case WEAPON_ELITE:
		return ("dual berettas");
	case WEAPON_FIVESEVEN:
		return ("five-seveN");
	case WEAPON_GLOCK:
		return ("glock-18");
	case WEAPON_AK47:
		return ("ak-47");
	case WEAPON_AUG:
		return ("aug");
	case WEAPON_AWP:
		return ("awp");
	case WEAPON_FAMAS:
		return ("famas");
	case WEAPON_G3SG1:
		return ("g3sg1");
	case WEAPON_MP5:
		return ("mp-5");
	case WEAPON_GALILAR:
		return ("galil");
	case WEAPON_M249:
		return ("m249");
	case WEAPON_M4A1:
		return ("m4a1");
	case WEAPON_MAC10:
		return ("mac-10");
	case WEAPON_P90:
		return ("p90");
	case WEAPON_UMP45:
		return ("ump-45");
	case WEAPON_XM1014:
		return ("xm1014");
	case WEAPON_BIZON:
		return ("pp-bizon");
	case WEAPON_MAG7:
		return ("mag-7");
	case WEAPON_NEGEV:
		return ("negev");
	case WEAPON_SAWEDOFF:
		return ("sawed-off");
	case WEAPON_TEC9:
		return ("tec-9");
	case WEAPON_TASER:
		return ("taser");
	case WEAPON_HKP2000:
		return ("p2000");
	case WEAPON_MP7:
		return ("mp7");
	case WEAPON_MP9:
		return ("mp9");
	case WEAPON_NOVA:
		return ("nova");
	case WEAPON_P250:
		return ("p250");
	case WEAPON_SCAR20:
		return ("scar-20");
	case WEAPON_SG556:
		return ("sg 553");
	case WEAPON_SSG08:
		return ("ssg 08");
	case WEAPON_KNIFE:
		return ("knife");
	case WEAPON_FLASHBANG:
		return ("flashbang");
	case WEAPON_HEGRENADE:
		return ("he grenade");
	case WEAPON_SMOKEGRENADE:
		return ("smoke grenade");
	case WEAPON_MOLOTOV:
		return ("molotov");
	case WEAPON_DECOY:
		return ("decoy");
	case WEAPON_INCGRENADE:
		return ("incendiary grenade");
	case WEAPON_C4:
		return ("c4");
	case WEAPON_KNIFE_T:
		return ("knife");
	case WEAPON_M4A1_SILENCER:
		return ("m4a1-S");
	case WEAPON_USP_SILENCER:
		return ("usp-s");
	case WEAPON_CZ75A:
		return ("cz75-auto");
	case WEAPON_REVOLVER:
		return ("r8 revolver");
	default:
		return ("knife");
	}

	return "";
}
bool sPistolmeme(int WeaponId)
{
	return WeaponId == WEAPON_DEAGLE || WeaponId == WEAPON_ELITE || WeaponId == WEAPON_FIVESEVEN || WeaponId == WEAPON_P250 ||
		WeaponId == WEAPON_GLOCK || WeaponId == WEAPON_USP_SILENCER || WeaponId == WEAPON_CZ75A || WeaponId == WEAPON_HKP2000 || WeaponId == WEAPON_TEC9 /*|| WeaponId == weapon_revolver*/;
}
void DrawlegitchildMeme(bool MenuNotOpened)
{
	//	ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.36f, 0.36f, 0.36f, 1.0f));
	//	ImGui::PushStyleColor(ImGuiCol_BorderShadow, ImVec4(0.05f, 1.0f, 0.05f, 0.f));

	ImGui::BeginChild(("RagebotChild1"), ImVec2(ImGui::GetWindowWidth() / 3 - 10, 0), true, MenuNotOpened ? ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar : ImGuiWindowFlags_NoResize | ImGuiWindowFlags_ShowBorders);
	{
		
		ImGui::Text(("Aimbot Settings"));
		ImGui::Separator();

		ImGui::Checkbox(("Enable Aimbot"), &g_Options.NewLegitbot.Aimbot.Enabled);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(("enable future aimbot"));

		ImGui::Checkbox(("Draw Fov"), &g_Options.NewLegitbot.Aimbot.DrawFOV);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(("drawing current fov aimbot"));

		ImGui::Checkbox(("Auto Pistol"), &g_Options.NewLegitbot.Aimbot.AutoPistol);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(("auto click in attack key"));

		ImGui::Checkbox(("BackTrack"), &g_Options.NewLegitbot.Aimbot.BackTracking);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(("backTrack to mexico"));
		ImGui::PushItemWidth(120);
		ImGui::SliderInt("Ticks", &g_Options.NewLegitbot.Aimbot.BackTrackIng, 1, 12, "%.0f");
		ImGui::PopItemWidth();
		ImGui::Checkbox("Rcs Fix", &g_Options.NewLegitbot.Aimbot.RCSFix);
		//	ImGui::Checkbox(("Aim on Key"), &g_Options.NewLegitbot.Aimbot.OnKey);

		/*ImGui::Checkbox(("FOV Distance Based"), &g_Options.NewLegitbot.Aimbot.DistanceBased);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(("Calculate FOV to player and Distance"));*/

		ImGui::Hotkey(("Aimbot Key##legit"), &g_Options.NewLegitbot.Aimbot.Key, ImVec2(130, 23));
		

		ImGui::Checkbox(("Friendly Fire"), &g_Options.NewLegitbot.Aimbot.FriendlyFire);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(("aim at teammates"));

		ImGui::Checkbox(("Smoke Check"), &g_Options.NewLegitbot.Aimbot.SmokeCheck);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(("if enemy is behind smoke, aim wont work"));

		ImGui::Checkbox(("Flash Check"), &g_Options.NewLegitbot.Aimbot.FlashCheck);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(("if you was flashed, aim dont work"));

		if (g_Options.NewLegitbot.Aimbot.FlashCheck)
		{
			if (g_Options.NewLegitbot.Aimbot.FlashCheckAlpha > 255.f)g_Options.NewLegitbot.Aimbot.FlashCheckAlpha = 255.f;
			if (g_Options.NewLegitbot.Aimbot.FlashCheckAlpha < 0.f) g_Options.NewLegitbot.Aimbot.FlashCheckAlpha = 0.f;

			SliderFloatFST(("flash check alpha"), g_Options.NewLegitbot.Aimbot.FlashCheckAlpha, 0.f, 255.f);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(("if you was flashed and white screen alpha > flash check alpha, aim dont work"));
		}

		ImGui::Checkbox(("Jump Check"), &g_Options.NewLegitbot.Aimbot.JumpCheck);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(("if you in air, aim wont work"));


		ImGui::Checkbox(("Killdelay"), &g_Options.NewLegitbot.Aimbot.bKillDelay);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(("enable kill delay"));
		
		SliderFloatFST(("killdelay amount"), g_Options.NewLegitbot.Aimbot.iKillDelay, 0.f, 2.f);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(("if delay running, aim wont work"));


	}ImGui::EndChild();
	ImGui::SameLine();
	ImGui::BeginChild(("RagebotChild2"), ImVec2(ImGui::GetWindowWidth() / 3 - 10, 0), true, MenuNotOpened ? ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar : ImGuiWindowFlags_NoResize | ImGuiWindowFlags_ShowBorders);
	{
		//if (g_pEngine->IsConnected())
		//	ImGui::Text(("Settings for %s"), GetWeaponName3().c_str());
		//else
		//	ImGui::Text(("Not alive/unknown weapon"));

		if (g_Options.wpn > 0)
		{
			ImGui::Text(("Settings for %s"), GetWeaponName3().c_str());
			ImGui::Separator();

			
			ImGui::Checkbox(("Enabled for cur. weapon"), &g_Options.NewLegitbot.Weapon[g_Options.wpn].Enabled);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(("enable aimbot with this Weapon ?"));


			ImGui::Combo(("Aimbot Type"), &g_Options.NewLegitbot.Weapon[g_Options.wpn].Aimtype, ("bullet CFG\0\rsticky\0\0"), -1, ImVec2(120, 0));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(("type aimbot"));
			ImGui::Combo(("Smooth Type"), &g_Options.NewLegitbot.Weapon[g_Options.wpn].SmoothType, ("normal\0\rcurve\0\0"), -1, ImVec2(120, 0));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(("smooth type aiming"));

			ImGui::Checkbox(("Nearest Bone"), &g_Options.NewLegitbot.Weapon[g_Options.wpn].Nearest);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(("aims at nearest to crosshair bone"));
			ImGui::Checkbox(("Bearest Rcs Lock"), &g_Options.NewLegitbot.Weapon[g_Options.wpn].NearestRCS);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip((" nearest bone with calc rcs \n if you start rcs, old aimbone = current aimbone"));

			
			if (!g_Options.NewLegitbot.Weapon[g_Options.wpn].Nearest) {
				//ImGui::Combo(("Hitbox"), &g_Options.NewLegitbot.Weapon[g_Options.wpn].Bone, ("PELVIS\0\r\0\r\0\rHIP\0\rLOWER SPINE\0\rMIDDLE SPINE\0\rUPPER SPINE\0\rNECK\0\rHEAD\0\0"), -1);
				//ImGui::InputInt(("Hitbox"), &g_Options.NewLegitbot.Weapon[g_Options.wpn].Bone);
				ImGui::Combo(("Hitbox"), &g_Options.NewLegitbot.Weapon[g_Options.wpn].Bone, ("head\0\rneck\0\rlower neck\0\rpelvis\0\rchest\0\rlower chest\0\rstomach\0\rlower stomach\0\0"), -1, ImVec2(120, 0));
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(("aimbot hitbox"));
			}



			ImGui::Checkbox(("Psilent"), &g_Options.NewLegitbot.Weapon[g_Options.wpn].pSilent);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(("perfect silent aim"));
			if (g_Options.NewLegitbot.Weapon[g_Options.wpn].pSilent)
			{
				ImGui::PushItemWidth(120);
				ImGui::SliderFloat(("Psilent Hitchance"), &g_Options.NewLegitbot.Weapon[g_Options.wpn].pSilentHitChance, 1.f, 100.f);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(("when hitchance > your value psilent will work"));

				ImGui::SliderFloat(("Psilent Fov"), &g_Options.NewLegitbot.Weapon[g_Options.wpn].pSilentFov, 0.1f, 10.f);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(("aimbot field of view for psilent"));
				ImGui::PopItemWidth();
			}
			ImGui::PushItemWidth(120);
			ImGui::SliderFloat(("Fov"), &g_Options.NewLegitbot.Weapon[g_Options.wpn].Fov, 0.1f, 20.f);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(("aimbot field of view"));


			ImGui::SliderFloat(("Smooth"), &g_Options.NewLegitbot.Weapon[g_Options.wpn].Smooth, 0.1f, 25.f);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(("aimbot smoothness"));



			ImGui::PopItemWidth();

			if (g_Options.wpn == WEAPON_AWP || g_Options.wpn == WEAPON_SSG08)
			{
				ImGui::Checkbox(("Fast-Zoom"), &g_Options.NewLegitbot.Aimbot.FastZoom);
			}
			else
			{
				
				ImGui::PushItemWidth(120);
				ImGui::SliderFloat(("Rcs Speed x"), &g_Options.NewLegitbot.Weapon[g_Options.wpn].RcsX, 1.f, 100.f);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(("recoil control system  vertical"));
				ImGui::SliderFloat(("Rcs Speed y"), &g_Options.NewLegitbot.Weapon[g_Options.wpn].RcsY, 1.f, 100.f);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(("recoil control system horizontal"));
				ImGui::PopItemWidth();

			}
	
			int maxbullets = BulletSizeByMenu(g_Options.wpn);

			if (g_Options.NewLegitbot.Weapon[g_Options.wpn].StartBullet > maxbullets) g_Options.NewLegitbot.Weapon[g_Options.wpn].StartBullet = maxbullets;
			if (g_Options.NewLegitbot.Weapon[g_Options.wpn].EndBullet > maxbullets) g_Options.NewLegitbot.Weapon[g_Options.wpn].EndBullet = maxbullets;


				ImGui::PushItemWidth(120);
				ImGui::SliderInt(("Bullet control one value"), &g_Options.NewLegitbot.Weapon[g_Options.wpn].StartBullet, 1, maxbullets);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(("aimbot after x bullet start"));
				ImGui::SliderInt(("Bullet control two value"), &g_Options.NewLegitbot.Weapon[g_Options.wpn].EndBullet, 1, maxbullets);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(("aimbot after x bullet end"));

				ImGui::PopItemWidth();
		


		}
		else
		{
			ImGui::Text(("Invalid Weapon"));
			ImGui::Separator();
		}

	}ImGui::EndChild();
	ImGui::SameLine();
	ImGui::BeginChild(("RagebotChild3"), ImVec2(ImGui::GetWindowWidth() / 3 - 10, 0), true, MenuNotOpened ? ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar : ImGuiWindowFlags_NoResize | ImGuiWindowFlags_ShowBorders);
	{
		ImGui::Text(("Triggerbot Settings"));
		ImGui::Separator();
		ImGui::Checkbox(("Enable   "), &g_Options.NewLegitbot.Triggerbot.Enabled);
		ImGui::SameLine();
		ImGui::Checkbox(("Ignore Key"), &g_Options.NewLegitbot.Triggerbot.AutoFire);
		if (g_Options.NewLegitbot.Triggerbot.AutoFire == false)
		{
			ImGui::PushItemWidth(120);
			ImGui::Hotkey(("Key     "), &g_Options.NewLegitbot.Triggerbot.Key, ImVec2(120, 23));
			ImGui::PopItemWidth();
		}
		
		ImGui::Checkbox(("Hit Chance"), &g_Options.NewLegitbot.Triggerbot.HitChance);

		ImGui::PushItemWidth(120);
		ImGui::SliderFloat(("Amount"), &g_Options.NewLegitbot.Triggerbot.HitChanceAmt, 1.f, 100.f, "%.0f");
		ImGui::PopItemWidth();


		ImGui::PushItemWidth(120);
		ImGui::SliderInt(("Delay"), &g_Options.NewLegitbot.Triggerbot.Delay, 1, 200);
		ImGui::PopItemWidth();
		ImGui::Text("");

		ImGui::BeginChild(("Filter"), ImVec2(ImGui::GetWindowContentRegionWidth() * 0.5f, 19 * 6));
		{
			ImGui::Selectable(("Head"), &g_Options.NewLegitbot.Triggerbot.Filter.Head);
			ImGui::Selectable(("Chest"), &g_Options.NewLegitbot.Triggerbot.Filter.Chest);
			ImGui::Selectable(("Stomach"), &g_Options.NewLegitbot.Triggerbot.Filter.Stomach);
			ImGui::Selectable(("Arms"), &g_Options.NewLegitbot.Triggerbot.Filter.Arms);
			ImGui::Selectable(("Legs"), &g_Options.NewLegitbot.Triggerbot.Filter.Legs);
			ImGui::Selectable(("Teammates"), &g_Options.NewLegitbot.Triggerbot.Filter.Friendly);
		}
		ImGui::EndChild();

	}ImGui::EndChild();

	//	ImGui::PopStyleColor();
	//	ImGui::PopStyleColor();
}
void DrawskinschildMeme(bool MenuNotOpened)
{

		ImGui::BeginChild(("SkinsChild1"), ImVec2(ImGui::GetWindowWidth() / 3 - 10, 0), true, MenuNotOpened ? ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar : ImGuiWindowFlags_NoResize | ImGuiWindowFlags_ShowBorders);
		{

			
			
			ImGui::Text("Skin Changer");
			ImGui::Separator();


			if (ImGui::Checkbox(("Enable Changer"), &g_Options.Skinchanger.EnabledChanger)) {
				g_Skinchanger->ForceItemUpdates();
				

			}
			
			ImGui::Checkbox("Auto Equip", &g_Options.Misc.AutoEquip);
			if (ImGui::Combo(("Knife Changer"), &g_Options.Skinchanger.knifemodel, ("None\0\rKarambit\0\rBayonet\0\rM9 Bayonet\0\rHuntsman\0\rGut Knife\0\rFalchion\0\rShadow Daggers\0\rButterfly\0\rFlip Knife\0\rBowie Knife\0\rNavaja Knife\0\rStiletto Knife\0\rUrsus Knife\0\rTalon Knife\0\0"), -1, ImVec2(130, 0)))g_Skinchanger->ForceItemUpdates();
			if (ImGui::Combo(("Glove Model"), &g_Options.Skinchanger.glovemodel, ("None\0\rBloodhound\0\rSport\0\rDriver\0\rHand Wraps\0\rMotorcycle\0\rSpecialst\0\rHydra\0\0"), -1, ImVec2(130, 0)))g_Skinchanger->ForceItemUpdates();



			const char* gstr;
			if (g_Options.Skinchanger.glovemodel == 1)
			{
				gstr = "Charred\0\rSnakebite\0\rBronzed\0\rGuerilla\0\0";
			}
			else if (g_Options.Skinchanger.glovemodel == 2)
			{
				gstr = "Hedge Maze\0\rPandoras Box\0\rSuperconductor\0\rArid\0\rVice\0\rOmega\0\rAmphibious\0\rBronze morph\0\0";
			}
			else if (g_Options.Skinchanger.glovemodel == 3)
			{
				gstr = "Lunar Weave\0\rconvoy\0\rCrimson Weave\0\rDiamondback\0\rOvertake\0\rRacing Green\0\rKing Snake\0\rImperial Plaid\0\0";
			}
			else if (g_Options.Skinchanger.glovemodel == 4)
			{
				gstr = "Leather\0\rSpruce ddpat\0\rSlaughter\0\rBadlands\0\rCobalt skulls\0\rOverprint\0\rDuct Tape\0\rArboreal\0\0";
			}
			else if (g_Options.Skinchanger.glovemodel == 5)
			{
				gstr = "Eclipse\0\rSpearmint\0\rBoom!\0\rCool Mint\0\rTurtle\0\rTransport\0\rPolygon\0\rPow!\0\0";
			}
			else if (g_Options.Skinchanger.glovemodel == 6)
			{
				gstr = "Forest ddpat\0\rCrimson Kimono\0\rEmerald Web\0\rFoundation\0\rCrimson Web\0\rBuckshot\0\rFade\0\rMogul\0\0";
			}
			else if (g_Options.Skinchanger.glovemodel == 7)
			{
				gstr = "Emerald\0\rMangrove\0\rRattler\0\rCase Hardened\0\0";
			}
			else
			{
				gstr = "";
			}
			ImGui::PushItemWidth(140);
			if (ImGui::Combo(("Glove skin"), &g_Options.Skinchanger.gloveskin, gstr, -1, ImVec2(130, 0)))g_Skinchanger->ForceItemUpdates();
			if (ImGui::InputInt(("Seed"), &g_Options.Skinchanger.SkinMaster[g_Options.wpn].Seed))g_Skinchanger->ForceItemUpdates();
			if (ImGui::SliderFloat(("Wear procent"), &g_Options.Skinchanger.SkinMaster[g_Options.wpn].Wear, 0, 100))g_Skinchanger->ForceItemUpdates();
			ImGui::PopItemWidth();
			if (ImGui::Checkbox(("Stattrak"), &g_Options.Skinchanger.SkinMaster[g_Options.wpn].Stattrak))g_Skinchanger->ForceItemUpdates();
			if (g_Options.Skinchanger.SkinMaster[g_Options.wpn].Stattrak)
			{
				if (ImGui::InputInt(("Stattrak value"), &g_Options.Skinchanger.SkinMaster[g_Options.wpn].StattrakValue))g_Skinchanger->ForceItemUpdates();
			}
			ImGui::Checkbox("Stickers", &g_Options.Skinchanger.sticker);
			ImGui::Checkbox("Rankchanger", &g_Options.Misc.rankchanger);
			ImGui::Checkbox("Inventory changer", &g_Options.Misc.connectinventory);
			

		}ImGui::EndChild();
		ImGui::SameLine();
		ImGui::BeginChild(("SkinsChild2"), ImVec2(ImGui::GetWindowWidth() / 3 - 10, 0), true, MenuNotOpened ? ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar : ImGuiWindowFlags_NoResize | ImGuiWindowFlags_ShowBorders);
		{

			const char* ranks[] = {
				"Off",
				"Silver 1",
				"Silver 2",
				"Silver 3",
				"Silver 4",
				"Silver Elite",
				"Silver Elite Master",
				"Gold Nova 1",
				"Gold Nova 2",
				"Gold Nova 3",
				"Gold Nova Master",
				"Master guardian 1",
				"Master Guardian 2",
				"Master Guardian Wlite",
				"Distinguished master Guardian",
				"Legendary Eagle",
				"Legendary Eagle Master",
				"Supreme Master First class",
				"The Global Wlite"
			};

		
			//ImGui::Combo("Weapon", )
			//ImGui::InputInt("Id", &g_Options.wpn);
			
			ImGui::Combo("Item", &g_Options.i, weap, ARRAYSIZE(weap));

			switch (g_Options.i)
			{
			case 0:
				g_Options.wpn = WEAPON_DEAGLE;
				break;
			case 1:
				g_Options.wpn = WEAPON_ELITE;
				break;
			case 2:
				g_Options.wpn = WEAPON_FIVESEVEN;
				break;
			case 3:
				g_Options.wpn = WEAPON_GLOCK;
				break;
			case 4:
				g_Options.wpn = WEAPON_AK47;
				break;
			case 5:
				g_Options.wpn = WEAPON_AUG;
				break;
			case 6:
				g_Options.wpn = WEAPON_AWP;
				break;
			case 7:
				g_Options.wpn = WEAPON_FAMAS;
				break;
			case 8:
				g_Options.wpn = WEAPON_G3SG1;
				break;
			case 9:
				g_Options.wpn = WEAPON_MP5;
				break;
			case 10:
				g_Options.wpn = WEAPON_GALILAR;
				break;
			case 11:
				g_Options.wpn = WEAPON_M249;
				break;
			case 12:
				g_Options.wpn = WEAPON_M4A1;
				break;
			case 13:
				g_Options.wpn = WEAPON_MAC10;
				break;
			case 14:
				g_Options.wpn = WEAPON_P90;
				break;
			case 15:
				g_Options.wpn = WEAPON_UMP45;
				break;
			case 16:
				g_Options.wpn = WEAPON_XM1014;
				break;
			case 17:
				g_Options.wpn = 26;
				break;
			case 18:
				g_Options.wpn = WEAPON_MAG7;
				break;
			case 19:
				g_Options.wpn = WEAPON_NEGEV;
				break;
			case 20:
				g_Options.wpn = WEAPON_SAWEDOFF;
				break;
			case 21:
				g_Options.wpn = WEAPON_TEC9;
				break;
			case 22:
				g_Options.wpn = WEAPON_HKP2000;
				break;
			case 23:
				g_Options.wpn = WEAPON_MP7;
				break;
			case 24:
				g_Options.wpn = WEAPON_NOVA;
				break;
			case 25:
				g_Options.wpn = WEAPON_P250;
				break;
			case 26:
				g_Options.wpn = WEAPON_SCAR20;
				break;
			case 27:
				g_Options.wpn = WEAPON_SG556;
				break;
			case 28:
				g_Options.wpn = WEAPON_SSG08;
				break;
			case 29:
				g_Options.wpn = WEAPON_M4A1_SILENCER;
				break;
			case 30:
				g_Options.wpn = WEAPON_USP_SILENCER;
				break;
			case 31:
				g_Options.wpn = WEAPON_CZ75A;
				break;
			case 32:
				g_Options.wpn = WEAPON_REVOLVER;
				break;
			case 33:
				g_Options.wpn = WEAPON_KNIFE_BAYONET;
				break;
			case 34:
				g_Options.wpn = WEAPON_KNIFE_FLIP;
				break;
			case 35:
				g_Options.wpn = WEAPON_KNIFE_GUT;
				break;
			case 36:
				g_Options.wpn = WEAPON_KNIFE_KARAMBIT;
				break;
			case 37:
				g_Options.wpn = WEAPON_KNIFE_M9_BAYONET;
				break;
			case 38:
				g_Options.wpn = WEAPON_KNIFE_TACTICAL;
				break;
			case 39:
				g_Options.wpn = WEAPON_KNIFE_FALCHION;
				break;
			case 40:
				g_Options.wpn = WEAPON_KNIFE_SURVIVAL_BOWIE;
				break;
			case 41:
				g_Options.wpn = WEAPON_KNIFE_BUTTERFLY;
				break;
			case 42:
				g_Options.wpn = WEAPON_KNIFE_PUSH;
				break;
			case 43:
				g_Options.wpn = WEAPON_KNIFE_NAVAJA;
				break;
			case 44:
				g_Options.wpn = WEAPON_KNIFE_STILETTO;
				break;
			case 45:
				g_Options.wpn = WEAPON_KNIFE_URSUS;
				break;
			case 46:
				g_Options.wpn = WEAPON_KNIFE_TALON;
				break;

			}


			std::string skinName = GetWeaponNameById(g_Options.wpn);
			if (g_Options.wpn <= 0)
				//ImGui::Text(("Parser not Found Skin For This Weapon | Try Later"));
				ImGui::InputInt((u8"skin"), &g_Options.Skinchanger.SkinMaster[g_Options.wpn].PaintKit);
			else
			{
				std::string skinStr = "";
				int curItem = -1;
				int s = 0;
				for (auto skin : weaponSkins[skinName])
				{
					int pk = skinMap[skin].paintkit;
					if (pk == g_Options.Skinchanger.SkinMaster[g_Options.wpn].PaintKit)
						curItem = s;

					skinStr += skinNames[skinMap[skin].tagName].c_str();
					skinStr.push_back('\0');
					s++;
				}
				skinStr.push_back('\0');
				
				if (ImGui::Combo((u8"skin"), &curItem, skinStr.c_str())) 
				{
					int pk = 0;
					int c = 0;
					for (auto skin : weaponSkins[skinName])
					{
						if (curItem == c)
						{
							pk = skinMap[skin].paintkit;
							break;
						}

						c++;
					}
					g_Options.Skinchanger.SkinMaster[g_Options.wpn].PaintKit = pk;
					if (g_Options.Skinchanger.EnabledChanger) g_Skinchanger->ForceItemUpdates();
					//g_skins.push_back(weaponskins);
				}
				
			}
			if (g_Options.Skinchanger.sticker)
			{
				ImGui::Text(" ");
				ImGui::Text("Sticker Changer");
				ImGui::Separator();

				if (!IsKnifeForMenu(g_Options.wpn) && g_Options.wpn != 0)
				{
					if (ImGui::Checkbox("Sticker Changer", &g_Options.Skinchanger.SkinMaster[g_Options.wpn].StickersEnabled)) if (g_Options.Skinchanger.EnabledChanger) g_Skinchanger->ForceItemUpdates();
					static int iSlot = 0;
					ImGui::Combo("slot", &iSlot, "1 slot\0\r2 slot\0\r3 slot\0\r4 slot\0\0", -1, ImVec2(120, 20));
					if (ImGui::SliderFloat("Wear ", &g_Options.Skinchanger.SkinMaster[g_Options.wpn].Stickers[iSlot].flWear, 0.f, 1.f))g_Skinchanger->ForceItemUpdates();
					if (ImGui::SliderFloat("Scale", &g_Options.Skinchanger.SkinMaster[g_Options.wpn].Stickers[iSlot].flScale, 0.f, 1.f)) g_Skinchanger->ForceItemUpdates();
					if (ImGui::SliderInt("Rotation", &g_Options.Skinchanger.SkinMaster[g_Options.wpn].Stickers[iSlot].iRotation, 0, 360))g_Skinchanger->ForceItemUpdates();
					if (ImGui::InputInt("Id", &g_Options.Skinchanger.SkinMaster[g_Options.wpn].Stickers[iSlot].iID))g_Skinchanger->ForceItemUpdates();
				}
			}

			
			weaponskins.wId = g_Options.wpn;
			weaponskins.paintkit = g_Options.Skinchanger.SkinMaster[g_Options.wpn].PaintKit;
			weaponskins.wear = g_Options.Skinchanger.SkinMaster[g_Options.wpn].Wear;
			weaponskins.seed = g_Options.Skinchanger.SkinMaster[g_Options.wpn].Seed;
			
			if (g_Options.Misc.connectinventory)
			{
				//ImGui::Text("Inventory Changer"); ImGui::SameLine();
				//if (ImGui::Button("Add")) {
				//	g_skins.push_back(weaponskins);
				//}
				//ImGui::InputInt("ID", &weaponskins.wId);//&g_Options.Misc.weaponid);
				//ImGui::InputInt("Paint Kit", &weaponskins.paintkit);//&g_Options.Misc.paintkit);
				//ImGui::InputFloat("Wear", &weaponskins.wear);//&g_Options.Misc.wear);
				//ImGui::InputInt("Quality", &weaponskins.quality);// &g_Options.Misc.quality);
				//ImGui::Combo("Quality", &weaponskins.quality, rare,ARRAYSIZE(rare));
				//ImGui::InputFloat("Seed", &weaponskins.seed);// &g_Options.Misc.seed);
			}
			if (g_Options.Misc.rankchanger)
			{
				ImGui::Text(" ");
				ImGui::Text("Rank Changer");
				ImGui::Separator();
				ImGui::Combo(("Rank"), &g_Options.Misc.rank_id, ranks, ARRAYSIZE(ranks));
				ImGui::SliderInt("Level", &g_Options.Misc.level, 0, 40);
				ImGui::InputInt("Wins", &g_Options.Misc.wins);
				ImGui::InputInt("Friendly", &g_Options.Misc.friendly);
				ImGui::InputInt("Teaching", &g_Options.Misc.teaching);
				ImGui::InputInt("Leader", &g_Options.Misc.leader);
			}

		}ImGui::EndChild();
		ImGui::SameLine();
		ImGui::BeginChild(("SkinsChild3"), ImVec2(ImGui::GetWindowWidth() / 3 - 10, 0), true, MenuNotOpened ? ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar : ImGuiWindowFlags_NoResize | ImGuiWindowFlags_ShowBorders);
		{

			static const char* rare[] =
			{
				"None",
				"Consumer Grade",
				"Industrial Grade",
				"Mil Spec",
				"Restricted",
				"Classified",
				"Covert",
				"Contraband",
			};

			ImGui::Text("Inventory Changer");
			ImGui::Separator();

			

			if (ImGui::ListBoxHeader("##skins"))
			{
				int id = 0;
				string gg;
				int weapon_index = 0;
				for (auto weapon : g_skins) {

					

					id = weapon.wId;
					switch (id)
					{
					case WEAPON_DEAGLE:
						gg = "Desert Eagle";
						break;
					case WEAPON_ELITE:
						gg = "Dual Berettas";
						break;
					case WEAPON_FIVESEVEN:
						gg = "Five-seveN";
						break;
					case WEAPON_GLOCK:
						gg = "Glock-18";
						break;
					case WEAPON_AK47:
						gg = "Ak-47";
						break;
					case WEAPON_AUG:
						gg = "AUG";
						break;
					case WEAPON_AWP:
						gg = "AWP";
						break;
					case WEAPON_FAMAS:
						gg = "Famas";
						break;
					case WEAPON_G3SG1:
						gg = "G3SG1";
						break;
					case WEAPON_MP5:
						gg = "MP-5";
						break;
					case WEAPON_GALILAR:
						gg = "Galil";
						break;
					case WEAPON_M249:
						gg = "M249";
						break;
					case WEAPON_M4A1:
						gg = "M4a4";
						break;
					case WEAPON_MAC10:
						gg = "MAC-10";
						break;
					case WEAPON_P90:
						gg = "P90";
						break;
					case WEAPON_UMP45:
						gg = "UMP-45";
						break;
					case WEAPON_XM1014:
						gg = "XM1014";
						break;
					case WEAPON_BIZON:
						gg = "PP-Bizon";
						break;
					case WEAPON_MAG7:
						gg = "MAG-7";
						break;
					case WEAPON_NEGEV:
						gg = "Negev";
						break;
					case WEAPON_SAWEDOFF:
						gg = "Sawed-Off";
						break;
					case WEAPON_TEC9:
						gg = "Tec-9";
						break;
					case WEAPON_KNIFE_BUTTERFLY:
						gg = "Butterfly";
						break;
					case WEAPON_KNIFE_FALCHION:
						gg = "Falchion Knife";
						break;
					case WEAPON_KNIFE_FLIP:
						gg = "Flip Knife";
						break;
					case WEAPON_KNIFE_GUT:
						gg = "Gut Knife";
						break;
					case WEAPON_KNIFE_KARAMBIT:
						gg = "Karambit";
						break;
					case WEAPON_KNIFE_M9_BAYONET:
						gg = "M9 Bayonet";
						break;
					case WEAPON_KNIFE_BAYONET:
						gg = "Bayonet";
						break;
					case WEAPON_KNIFE_STILETTO:
						gg = "Stiletto Knife";
						break;
					case WEAPON_KNIFE_URSUS:
						gg = "Ursus Knife";
						break;
					case WEAPON_KNIFE_TALON:
						gg = "Talon Knife";
						break;
					case WEAPON_KNIFE_NAVAJA:
						gg = "Navaja Knife";
						break;
					case WEAPON_HKP2000:
						gg = "P2000";
						break;
					case WEAPON_MP7:
						gg = "MP7";
						break;
					case WEAPON_MP9:
						gg = "MP9";
						break;
					case WEAPON_NOVA:
						gg = "Nova";
						break;
					case WEAPON_P250:
						gg = "P250";
						break;
					case WEAPON_SCAR20:
						gg = "Scar-20";
						break;
					case WEAPON_SG556:
						gg = "SG 553";
						break;
					case WEAPON_SSG08:
						gg = "SSG 08";
						break;
					case WEAPON_M4A1_SILENCER:
						gg = "M4a1-S";
						break;
					case WEAPON_USP_SILENCER:
						gg = "USP-S";
						break;
					case WEAPON_CZ75A:
						gg = "CZ75-auto";
						break;
					case WEAPON_REVOLVER:
						gg = "Revolver";
						break;
					default:
						gg = "None";
						break;
					}

					if (ImGui::Selectable(std::string(gg + " | " + std::to_string(weapon.paintkit)).c_str())) {
						g_skins.erase(g_skins.begin() + weapon_index);
					}
					weapon_index++;
				}
				ImGui::ListBoxFooter();

				//std::to_string(weapon.paintkit)).c_str()

				ImGui::Combo("Quality", &weaponskins.quality, rare, ARRAYSIZE(rare));

				if (ImGui::Button("Add")) {
					g_skins.push_back(weaponskins);
				}
				ImGui::SameLine();
				if (ImGui::Button("Apply"))
				{
					Hacks.ProtoFeatures.SendClientHello();
					Hacks.ProtoFeatures.SendMatchmakingClient2GCHello();
					g_Skinchanger->ForceItemUpdates();
				}
				//if (ImGui::Button(("Update"), ImVec2(100.f, 20.f))
				/*if (ImGui::Button("Delete")) {
					g_skins.erase(g_skins.begin() + weapon_index);
				}*/
			}
			

			//std::to_string(weapon.wId)

		}ImGui::EndChild();
		//ImGui::InputInt("Index", &g_Options.Misc.index);
}
class VectorRadar2D
{
public:
	VectorRadar2D() {}
	VectorRadar2D(float x_, float y_) { x = x_; y = y_; }
public:
	float x, y;
};
VectorRadar2D RotatePoint(Vector vecEntity, Vector vecLocal, int iPosX, int iPosY, int iSizeX, int iSizeY, float angle, float zoom, bool* bView, bool bRadians)
{
	float r_1, r_2;
	float x_1, y_1;

	r_1 = -(vecEntity.y - vecLocal.y);
	r_2 = vecEntity.x - vecLocal.x;
	float flYaw = angle - 90.0f;

	float flRad = flYaw * (3.14159265358979323846f / 180.0F);
	x_1 = (float)(r_2 * (float)cos((double)(flRad)) - r_1 * sin((double)(flRad))) / 20;
	y_1 = (float)(r_2 * (float)sin((double)(flRad)) + r_1 * cos((double)(flRad))) / 20;

	*bView = y_1 < 0;

	x_1 *= zoom;
	y_1 *= zoom;

	int sizeX = iSizeX / 2;
	int sizeY = iSizeY / 2;

	x_1 += sizeX;
	y_1 += sizeY;

	if (x_1 < 5)
		x_1 = 5;

	if (x_1 > iSizeX - 5)
		x_1 = iSizeX - 5;

	if (y_1 < 5)
		y_1 = 5;

	if (y_1 > iSizeY - 5)
		y_1 = iSizeY - 5;


	x_1 += iPosX;
	y_1 += iPosY;


	return VectorRadar2D(x_1, y_1);
}

void RenderMonitor()
{
	if (!Interfaces.pEngine->IsConnected())
		return;

	if (!Interfaces.pEngine->IsInGame())
		return;

	CBaseEntity* pLocal = G::LocalPlayer;

	if (!pLocal)
		return;

	if (!pLocal->isAlive())
		return;

	if (pLocal->IsDormant())
		return;

	if (ImGui::Begin(("Monitor"), &g_Options.Visuals.Panels.Monitor, ImVec2(200, 250), 1.0F, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize))
	{
		ImDrawList* windowDrawList = ImGui::GetWindowDrawList();

		ImVec2 siz = ImGui::GetWindowSize();
		ImVec2 pos = ImGui::GetWindowPos();
		CBaseCombatWeapon* pWeapon = G::LocalPlayer->GetActiveBaseCombatWeapon();
		if (pWeapon)
		{
			float accuracy = pWeapon->GetInaccuracy() * 550.f;

			if (accuracy > 179)
				accuracy = 179;

			int iSpeed = 0;
			Vector vSpeed = pLocal->GetVecVelocity();
			iSpeed = (int)vSpeed.Length2D();

			int iBoost = 0;
			Vector vBoost = pLocal->GetVecVelocity();
			iBoost = (int)vBoost.Length2D() - 300;

			float flPunch = 0.0f;
			Vector vRecoil = pLocal->GetPunchAngle();
			flPunch = (float)vRecoil.Length();

			if (iSpeed < 300)
				windowDrawList->AddText(ImVec2(pos.x + 25, pos.y + 1 + 217), CColor(255, 255, 255, 255).GetU32(), ("Speed"));
			if (iSpeed > 300)
				windowDrawList->AddText(ImVec2(pos.x + 25, pos.y + 1 + 217), CColor(255, 0, 0, 255).GetU32(), ("Boost"));
			windowDrawList->AddText(ImVec2(pos.x + 85, pos.y + 1 + 217), CColor(255, 255, 255, 255).GetU32(), ("Recoil"));
			windowDrawList->AddText(ImVec2(pos.x + 145, pos.y + 1 + 217), CColor(255, 255, 255, 255).GetU32(), ("Spread"));

			windowDrawList->AddRect(ImVec2(pos.x + 147, pos.y + 35), ImVec2(pos.x + 147 + 25, pos.y + 35 + 180), CColor(0, 0, 0, 255).GetU32());
			windowDrawList->AddRect(ImVec2(pos.x + 87, pos.y + 35), ImVec2(pos.x + 87 + 25, pos.y + 35 + 180), CColor(0, 0, 0, 255).GetU32());
			windowDrawList->AddRect(ImVec2(pos.x + 28, pos.y + 35), ImVec2(pos.x + 28 + 25, pos.y + 35 + 180), CColor(0, 0, 0, 255).GetU32());

			if (iSpeed < 300)
				windowDrawList->AddRectFilled(ImVec2(pos.x + 28, pos.y + 35 + 180 - (iSpeed * 0.6)), ImVec2(pos.x + 28 + 25, pos.y + 35 + 180), CColor(255, 255, 255, 255).GetU32());

			if (iSpeed > 300)
				windowDrawList->AddRectFilled(ImVec2(pos.x + 28, pos.y + 35 + 180 - (iBoost * 0.2)), ImVec2(pos.x + 28 + 25, pos.y + 35 + 180), CColor(255, 0, 0, 255).GetU32());

			windowDrawList->AddRectFilled(ImVec2(pos.x + 147, pos.y + 35 + 180 - accuracy), ImVec2(pos.x + 147 + 25, pos.y + 35 + 180), CColor(255, 255, 255, 255).GetU32());
			windowDrawList->AddRectFilled(ImVec2(pos.x + 87, pos.y + 35 + 180 - flPunch * 30), ImVec2(pos.x + 87 + 25, pos.y + 35 + 180), CColor(255, 255, 255, 255).GetU32());

			ImGui::End();
		}
	}
}
#define M_PI		3.14159265358979323846f
Vector RotatePoint1(Vector p, Vector c, float ang)
{
	float angleInRadians = ang * (M_PI / 180.f);
	float cosTheta = cos(angleInRadians);
	float sinTheta = sin(angleInRadians);
	return Vector(
		(cosTheta * (p.x - c.x) -
			sinTheta * (p.y - c.y) + c.x),
			(sinTheta * (p.x - c.x) +
				cosTheta * (p.y - c.y) + c.y),
		0);
}


void RenderRadar()
{
	ImGuiStyle& style = ImGui::GetStyle();
	ImVec2 oPadding = style.WindowPadding;
	float oAlpha = style.Colors[ImGuiCol_WindowBg].w;

	style.WindowPadding = ImVec2(0, 0);
	style.Colors[ImGuiCol_WindowBg].w = (float)255 / 255.0f;

	if (ImGui::Begin(("Radar"), &g_Options.Visuals.Panels.Radar.ExternalRadar, ImVec2(200, 200), 0.5F, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse))
	{

		ImVec2 siz = ImGui::GetWindowSize();
		ImVec2 pos = ImGui::GetWindowPos();

		ImDrawList* windowDrawList = ImGui::GetWindowDrawList();

		 CColor Black = CColor(255, 255, 255, 255);
		 CColor Red = CColor(255, 0, 0, 255);
		 CColor Purple = CColor(255, 0, 255, 255);
		 CColor Cyan = CColor(0, 150, 255, 255);
		 CColor Blue = CColor(0, 0, 255, 255);


		windowDrawList->AddLine(ImVec2(pos.x + (siz.x / 2), pos.y + 0), ImVec2(pos.x + (siz.x / 2), pos.y + siz.y), Black.GetU32(), 1.5f);
		windowDrawList->AddLine(ImVec2(pos.x + 0, pos.y + (siz.y / 2)), ImVec2(pos.x + siz.x, pos.y + (siz.y / 2)), Black.GetU32(), 1.5f);

		// Rendering players
		if (Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected())
		{
			CBaseEntity* pLocal = G::LocalPlayer;
			if (pLocal)
			{
				Vector vecLocal = pLocal->GetEyePosition();
				Vector ang;
				Interfaces.pEngine->GetViewAngles(ang);
				for (int i = 1; i < 65; i++)
				{
					CBaseEntity* pEntity = Interfaces.pEntList->GetClientEntity(i);

					if (!pEntity)
						continue;
					if (pEntity == pLocal)
						continue;
					if (!pEntity->isAlive())
						continue;
					if (pEntity->IsDormant())
						continue;
				
			
					player_info_t player_info;
					if (!Interfaces.pEngine->GetPlayerInfo(i, &player_info))continue;
				
					bool bVisible = pEntity->IsVisible(8);
					bool preVis = G::LineToSmoke(pEntity->GetBonePos(8), pLocal->GetEyePosition(), true);
					bool bViewCheck = false;
					VectorRadar2D vecEntity = RotatePoint(pEntity->GetAbsOrigin(), vecLocal, pos.x, pos.y, siz.x, siz.y, ang.y, g_Options.Visuals.Panels.Radar.RadarDistance, &bViewCheck, false);

				
					if (pEntity->GetTeam() == G::LocalPlayer->GetTeam() && !g_Options.Visuals.Visuals_EspTeam)
						continue;

					if (g_Options.Visuals.Panels.Radar.RadarVisibleOnly && !bVisible)
						continue;
					if (g_Options.Visuals.Panels.Radar.RadarSmoke && !preVis)
						continue;

					int rad = 4;
					ImU32 clr = (pEntity->IsEnemy() ? (bVisible ? Red.GetU32() : Purple.GetU32()) : (bVisible ? Cyan.GetU32() : Blue.GetU32()));

					switch (g_Options.Visuals.Panels.Radar.RadarStyle)
					{
					case 0:
						windowDrawList->AddRect(ImVec2(vecEntity.x - rad, vecEntity.y - rad), ImVec2(vecEntity.x + rad, vecEntity.y + rad), clr);
						break;
					case 1:
						windowDrawList->AddRectFilled(ImVec2(vecEntity.x - rad, vecEntity.y - rad), ImVec2(vecEntity.x + rad, vecEntity.y + rad), clr);
						break;
					case 2:
						windowDrawList->AddCircle(ImVec2(vecEntity.x, vecEntity.y), rad, clr);
						break;
					case 3:
						windowDrawList->AddCircleFilled(ImVec2(vecEntity.x, vecEntity.y), rad, clr);
						break;
					default:
						break;
					}
				}
			}
		}
	}
	ImGui::End();

	style.WindowPadding = oPadding;
	style.Colors[ImGuiCol_WindowBg].w = oAlpha;
}
void PlayerList()
{
	ImGui::SetNextWindowSize(ImVec2(300, 500), ImGuiSetCond_FirstUseEver);
	if (ImGui::Begin(("Player list"), &g_Options.Players.Playerlist, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders))
	{
		static int currentPlayer = -1;

		if (!Interfaces.pEngine->IsInGame())
			currentPlayer = -1;

		ImGui::ListBoxHeader(("##PLAYERS"), ImVec2(-1, (ImGui::GetWindowSize().y - 135)));
		{
			if (Interfaces.pEngine->IsInGame())
			{
				for (int i = 1; i < 65; i++)
				{

					if (i == Interfaces.pEngine->GetLocalPlayer())
						continue;

					CBaseEntity* Target = Interfaces.pEntList->GetClientEntity(i);
					if (!Target)
						continue;
					if (Target->GetClientClass()->m_ClassID != 35)
						continue;

					if (Target->GetTeam() == G::LocalPlayer->GetTeam())
						continue;

					player_info_t entityInformation;		
					if(!Interfaces.pEngine->GetPlayerInfo(i, &entityInformation))
						continue;

					if (entityInformation.name == "GOTV" && !Target->GetActiveBaseCombatWeapon())
						continue;

					

	

					ImGui::Separator();
					char buf[255]; sprintf_s(buf, u8"%s", entityInformation.name);
					if (ImGui::Selectable(buf, i == currentPlayer, ImGuiSelectableFlags_SpanAllColumns))
						currentPlayer = i;
				}
			}
		}
		ImGui::ListBoxFooter();

	

		if (currentPlayer != -1)
		{
			player_info_t entityInformation;
			Interfaces.pEngine->GetPlayerInfo(currentPlayer, &entityInformation);

			ImVec2 siz = ImVec2(200, 625 - ImGui::GetCursorPosY() - 40);
			ImVec2 size = ImVec2(200, 625 - ImGui::GetCursorPosY() - 40);
			if (ImGui::BeginChild(("##PLISTFIX-CHILD"), siz, false))
			{

				bool shouldResolve = std::find(CPlayerList::Players.begin(), CPlayerList::Players.end(), entityInformation.userid) != CPlayerList::Players.end();
				if (ImGui::Checkbox(("Resolver Whitelist"), &shouldResolve))
				{
					if (shouldResolve)
						CPlayerList::Players.push_back(entityInformation.userid);
					else
						CPlayerList::Players.erase(std::find(CPlayerList::Players.begin(), CPlayerList::Players.end(), entityInformation.userid));
				}

				ImGui::Combo(("PitchFix"), &g_Options.Players.AAA[currentPlayer].PAngle, ("Auto\0\rDown\0\rUp\0\rZero\0\rEmotion\0\0"), -1);
					
			} ImGui::EndChild(); ImGui::SameLine();
			if (ImGui::BeginChild(("##CLEARS-CHILD"), size, false))
			{
				if (ImGui::Button(("Clear NoResolve"), ImVec2(93.f, 20.f)))
					CPlayerList::Players.clear();
				if (ImGui::Button(("Clear Fixes"), ImVec2(93.f, 20.f))) {
					if (Interfaces.pEngine->IsInGame())
					{
						for (int i = 1; i < 65; i++)
						{
							g_Options.Players.AAA[i].PAngle = 0;
						}
					}
				}
			} ImGui::EndChild(); ImGui::NewLine();
		}
	}
	ImGui::End();
}

namespace MenuUI
{
	/*void SkinChangerWindow(IDirect3DDevice9* pDevice, IDirect3DTexture9 *TittleBar)
	{

		static bool notFull = true;
		static bool notFull1 = true;
		static bool notFull2 = true;
		static int XMenu = 1;
		static int YMenu = 80;


		if (!g_Options.Menu.Opened || !g_Options.Menu.SkinChangerWindow)
		{
			notFull = true;
			notFull1 = true;
			notFull2 = true;
			XMenu = 1;
			YMenu = 80;
		}
		if (g_Options.Menu.Opened && g_Options.Menu.SkinChangerWindow)
		{
	
			int pX, pY;
			Interfaces.g_pInputSystem->GetCursorPosition(&pX, &pY);
			ImGuiIO& io = ImGui::GetIO();
			io.MousePos.x = (float)(pX);
			io.MousePos.y = (float)(pY);
			//VMProtectBeginMutation("MENU");
			//	char nameChar[128];
			//	sprintf(nameChar, "Project Z");

			int windowWidth3 = 500;
			int windowHeight3 = 380;



			if (windowWidth3 <= XMenu) {
				notFull1 = false;
			}
			if (windowHeight3 <= YMenu) {
				notFull2 = false;
			}
			ImGui::SetNextWindowSize(ImVec2(XMenu, YMenu));

			if (notFull1)
			{
				if (g_Options.Menu.Animations)
					XMenu += 32;
				else
					XMenu = windowWidth3;
			}
			if (notFull2 && !notFull1)
			{
				if (g_Options.Menu.Animations)
					YMenu += 20;
				else
					YMenu = windowHeight3;
			}


			if (ImGui::Begin(("SkinChanger"), &g_Options.Menu.SkinChangerWindow, ImVec2(XMenu, YMenu), 0.0F, (notFull1 || notFull2 ? ImGuiWindowFlags_NoMove : 0) | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar))
			{

				ImGui::PushFont(GlobalFont);
				





				//if (notFull) return;	ImVec2 lPos = ImGui::GetCursorPos();
				ImGuiContext* io = ImGui::GetCurrentContext();
				ImGuiStyle& style = ImGui::GetStyle();


				ImDrawList* windowDrawList = ImGui::GetWindowDrawList();
				windowDrawList->AddRectFilledMultiColor(ImVec2(ImGui::GetWindowPos().x - 5, ImGui::GetWindowPos().y), ImVec2(ImGui::GetWindowPos().x + windowWidth3 + 10, ImGui::GetWindowPos().y + 95),
					ImColor(0.f, 0.f, 0.f, 0.f),//Upleft
					ImColor(0.f, 0.f, 0.f, 0.f),//UpRight
					ImColor(XMenu / 5500.f, XMenu / 5500.f, XMenu / 5500.f, 0.65f),//downleft

					ImColor(XMenu / 5500.f, XMenu / 5500.f, XMenu / 5500.f, 0.65f));//downright


				

				//	if (LegitTabImg == nullptr)D3DXCreateTextureFromFileInMemoryEx(pDevice
				//		, &NameLegitArray, sizeof(NameLegitArray),
				//		1000, 1000, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &LegitTabImg);





				if (!LegitTabImg)
					D3DXCreateTextureFromFileInMemoryEx(pDevice, &NameLegitArray, sizeof(NameLegitArray), 1000, 1000, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &LegitTabImg);


				ImVec2 curWindowPos = ImGui::GetWindowPos();
				windowDrawList->AddImage(TittleBar, ImVec2(curWindowPos.x + 500 / 2.3f, curWindowPos.y), ImVec2(curWindowPos.x + 500 / 2.3f + 95, curWindowPos.y + 95));

				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.05f, 1.0f, 0.05f, 0.f));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.05f, 1.0f, 0.05f, 0.f));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.05f, 1.0f, 0.05f, 0.f));
				ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.05f, 1.0f, 0.05f, 0.f));
				ImGui::PushStyleColor(ImGuiCol_BorderShadow, ImVec4(0.05f, 1.0f, 0.05f, 0.f));

				ImGui::Text(("                                         "));
				ImGui::Text(("                                         "));
				ImGui::Text(("                                         "));

				ImGui::Text(("                                         "));
				ImGui::Text(("                                         "));


				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
				ImGui::PopStyleColor();





				ImGui::BeginChild(("SkinChangerTabs"), ImVec2(ImGui::GetWindowWidth() - 17, 0), true, notFull1 || notFull2 ? ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar : ImGuiWindowFlags_NoResize | ImGuiWindowFlags_ShowBorders);
				{
					
					ImGui::Separator();

					if (ImGui::Checkbox(("enable Changer"), &g_Options.Skinchanger.EnabledChanger))g_Skinchanger->ForceItemUpdates();
					ImGui::SameLine(); if (ImGui::Button(("update"), ImVec2(100.f, 20.f)))g_Skinchanger->ForceItemUpdates();
					if (ImGui::Combo(("knife Changer"), &g_Options.Skinchanger.knifemodel, ("none\0\rkerambit\0\rbayonet\0\rm9 bayonet\0\rhuntsman\0\rgut\0\rfalchion\0\rdaggers\0\rbutterfly\0\rflip\0\rbowie\0\0"), -1, ImVec2(130, 0)))g_Skinchanger->ForceItemUpdates();
					if (ImGui::Combo(("glove Model"), &g_Options.Skinchanger.glovemodel, ("none\0\rbloodhound\0\rsport\0\rdriver\0\rhand wraps\0\rmotorcycle\0\rspecialst\0\rhydra\0\0"), -1, ImVec2(130, 0)))g_Skinchanger->ForceItemUpdates();


					const char* gstr;
					if (g_Options.Skinchanger.glovemodel == 1)
					{
						gstr = "charred\0\rsnakebite\0\rbronzed\0\rguerilla\0\0";
					}
					else if (g_Options.Skinchanger.glovemodel == 2)
					{
						gstr = "hedge maze\0\randoras box\0\rsuperconductor\0\rarid\0\rvice\0\romega\0\ramphibious\0\rbronze morph\0\0";
					}
					else if (g_Options.Skinchanger.glovemodel == 3)
					{
						gstr = "lunar weave\0\rconvoy\0\rcrimson weave\0\rdiamondback\0\rovertake\0\rracing green\0\rking snake\0\rimperial plaid\0\0";
					}
					else if (g_Options.Skinchanger.glovemodel == 4)
					{
						gstr = "leather\0\rspruce ddpat\0\rslaughter\0\rbadlands\0\rcobalt skulls\0\roverprint\0\rduct tape\0\rarboreal\0\0";
					}
					else if (g_Options.Skinchanger.glovemodel == 5)
					{
						gstr = "eclipse\0\rspearmint\0\rboom!\0\rcool mint\0\rturtle\0\rtransport\0\rpolygon\0\rpow!\0\0";
					}
					else if (g_Options.Skinchanger.glovemodel == 6)
					{
						gstr = "forest ddpat\0\rcrimson kimono\0\remerald web\0\rfoundation\0\rcrimson web\0\rbuckshot\0\rfade\0\rmogul\0\0";
					}
					else if (g_Options.Skinchanger.glovemodel == 7)
					{
						gstr = "emerald\0\rmangrove\0\rrattler\0\rcase hardened\0\0";
					}
					else
					{
						gstr = "";
					}

					if (ImGui::Combo(("glove skin"), &g_Options.Skinchanger.gloveskin, gstr, -1, ImVec2(130, 0)))g_Skinchanger->ForceItemUpdates();

					std::string skinName = GetWeaponNameById(g_Options.wpn);
					if (g_Options.wpn <= 0)
						//ImGui::Text(("Parser not Found Skin For This Weapon | Try Later"));
						ImGui::InputInt((u8"skin"), &g_Options.Skinchanger.SkinMaster[g_Options.wpn].PaintKit);
					else
					{
						std::string skinStr = "";
						int curItem = -1;
						int s = 0;
						for (auto skin : weaponSkins[skinName])
						{
							int pk = skinMap[skin].paintkit;
							if (pk == g_Options.Skinchanger.SkinMaster[g_Options.wpn].PaintKit)
								curItem = s;

							skinStr += skinNames[skinMap[skin].tagName].c_str();
							skinStr.push_back('\0');
							s++;
						}
						skinStr.push_back('\0');
						if (ImGui::Combo((u8"skin"), &curItem, skinStr.c_str()))
						{
							int pk = 0;
							int c = 0;
							for (auto skin : weaponSkins[skinName])
							{
								if (curItem == c)
								{
									pk = skinMap[skin].paintkit;
									break;
								}

								c++;
							}
							g_Options.Skinchanger.SkinMaster[g_Options.wpn].PaintKit = pk;
							if (g_Options.Skinchanger.EnabledChanger) g_Skinchanger->ForceItemUpdates();
						}
					}


					if (ImGui::InputInt(("seed"), &g_Options.Skinchanger.SkinMaster[g_Options.wpn].Seed))g_Skinchanger->ForceItemUpdates();
					if (ImGui::Checkbox(("stattrak"), &g_Options.Skinchanger.SkinMaster[g_Options.wpn].Stattrak))g_Skinchanger->ForceItemUpdates();
					if (g_Options.Skinchanger.SkinMaster[g_Options.wpn].Stattrak)
					{
						if (ImGui::InputInt(("stattrak value"), &g_Options.Skinchanger.SkinMaster[g_Options.wpn].StattrakValue))g_Skinchanger->ForceItemUpdates();
					}
					ImGui::PushItemWidth(140);
					if (ImGui::SliderFloat(("wear procent"), &g_Options.Skinchanger.SkinMaster[g_Options.wpn].Wear, 0, 100))g_Skinchanger->ForceItemUpdates();
					ImGui::PopItemWidth();


					ImGui::Separator();

					if (!IsKnifeForMenu(g_Options.wpn) && g_Options.wpn != 0)
					{
						if (ImGui::Checkbox("sticker Changer", &g_Options.Skinchanger.SkinMaster[g_Options.wpn].StickersEnabled)) if (g_Options.Skinchanger.EnabledChanger) g_Skinchanger->ForceItemUpdates();
						static int iSlot = 0;
						ImGui::Combo("slot", &iSlot, "1 slot\0\r2 slot\0\r3 slot\0\r4 slot\0\0",-1,ImVec2(120,20));
						if (ImGui::SliderFloat("wear ", &g_Options.Skinchanger.SkinMaster[g_Options.wpn].Stickers[iSlot].flWear, 0.f, 1.f))g_Skinchanger->ForceItemUpdates();
						if (ImGui::SliderFloat("scale", &g_Options.Skinchanger.SkinMaster[g_Options.wpn].Stickers[iSlot].flScale, 0.f, 1.f)) g_Skinchanger->ForceItemUpdates();
						if (ImGui::SliderInt("rotation", &g_Options.Skinchanger.SkinMaster[g_Options.wpn].Stickers[iSlot].iRotation, 0, 360))g_Skinchanger->ForceItemUpdates();
						if (ImGui::InputInt("id", &g_Options.Skinchanger.SkinMaster[g_Options.wpn].Stickers[iSlot].iID))g_Skinchanger->ForceItemUpdates();
					}


				}ImGui::EndChild();
				
				ImGui::PopFont();

			}
			ImGui::End();





		}
	}*/


	void Render(IDirect3DDevice9* pDevice)
	{
		if (!pDevice)
			return;

		ImGui::GetIO().MouseDrawCursor = g_Options.Menu.Opened;

		ImGui_ImplDX9_NewFrame();

		if (g_Options.Menu.Opened)
		{

			
			//if (TittleBar == nullptr)D3DXCreateTextureFromFileInMemoryEx(pDevice
				//, &NameArry, sizeof(NameArry),
				//1000, 1000, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &TittleBar);
			
		}
		//SkinChangerWindow(pDevice, TittleBar);
		


		if (g_Options.Visuals.Panels.Monitor)
			RenderMonitor();

		if (g_Options.Visuals.Panels.Radar.ExternalRadar)
			RenderRadar();

		if (g_Options.Misc.SpectatorList)
		{
			ImGuiStyle& style = ImGui::GetStyle();
			style.ChildWindowRounding = 4.0f;
			style.WindowRounding = 4.0f;

			if (ImGui::Begin(("spectators"), &g_Options.Misc.SpectatorList, ImVec2(300, 100), 0.5f, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize))
			{
				ImGui::Text(("spectator list"));

				int max = 65;

				for (int i = 1; i < max; i++)
				{
					CBaseEntity *entity = Interfaces.pEntList->GetClientEntity(i);

					if (NULL == entity) continue;
					if (entity->IsDormant()) continue;

					if (entity->GetClientClass()->m_ClassID != _CCSPlayer) continue;

					CBaseHandle sh = entity->GetObserverTarget();

					if (sh == 0xFFFFFFFF) continue;

					CBaseEntity *spectating = Interfaces.pEntList->GetClientEntityFromHandle(sh);

					if (spectating != NULL && spectating == G::LocalPlayer)
					{
						player_info_t info;
						if (Interfaces.pEngine->GetPlayerInfo(entity->GetIndex(), &info))
						{
							std::string tmp = SanitizeName(info.name);

							ImGui::Text(u8"%s", tmp.c_str());
						}
					}
				}

				ImGui::End();
			}
			style.ChildWindowRounding = 0.0f;
			style.WindowRounding = 0.0f;

		}

		static bool notFull = true;
		static bool notFull1 = true;
		static bool notFull2 = true;
		static int XMenu = 1;
		static int YMenu = 80;

		if (!g_Options.Menu.Opened)
		{
			notFull = true;
			notFull1 = true;
			notFull2 = true;
			XMenu = 1;
			YMenu = 65;
		}
		if (g_Options.Menu.Opened)
		{

			if (g_Options.Players.Playerlist)
				PlayerList();

			int pX, pY;
			Interfaces.g_pInputSystem->GetCursorPosition(&pX, &pY);
			ImGuiIO& io = ImGui::GetIO();
			io.MousePos.x = (float)(pX);
			io.MousePos.y = (float)(pY);
			//VMProtectBeginMutation("MENU");
			//	char nameChar[128];
			//	sprintf(nameChar, "Project Z");

			int windowWidth3 = 750;
			int windowHeight3 = 430;



			if (windowWidth3 <= XMenu) {
				notFull1 = false;
			}
			if (windowHeight3 <= YMenu) {
				notFull2 = false;
			}
			ImGui::SetNextWindowSize(ImVec2(XMenu, YMenu));

			if (notFull1)
			{
				if (g_Options.Menu.Animations)
					XMenu += 32;
				else
					XMenu = windowWidth3;
			}
			if (notFull2 && !notFull1)
			{
				if (g_Options.Menu.Animations)
					YMenu += 20;
				else
					YMenu = windowHeight3;
			}

			if (ImGui::Begin(("Lion"), &g_Options.Menu.Opened, ImVec2(XMenu, YMenu), 0.0F, (notFull1 || notFull2 ? ImGuiWindowFlags_NoMove : 0) | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar))
			{
				

				ImGui::PushFont(GlobalFont);
			

				static bool legitTab = true; 
				static bool skinsTab = false;
				static bool visualsTab = false;
				static bool changer = false;
				static bool rageTab = false;
				static bool configTab = false;
				static bool miscTab = false;
				static bool testTab = false;




				//if (notFull) return;	ImVec2 lPos = ImGui::GetCursorPos();
				ImGuiContext* io = ImGui::GetCurrentContext();
				ImGuiStyle& style = ImGui::GetStyle();


				ImDrawList* windowDrawList = ImGui::GetWindowDrawList();
				windowDrawList->AddRectFilledMultiColor(ImVec2(ImGui::GetWindowPos().x - 5, ImGui::GetWindowPos().y), ImVec2(ImGui::GetWindowPos().x + windowWidth3 + 10, ImGui::GetWindowPos().y + 90),
					ImColor(0.f, 0.f, 0.f, 0.f),//Upleft
					ImColor(0.f, 0.f, 0.f, 0.f),//UpRight
					ImColor(XMenu / 5500.f, XMenu / 5500.f, XMenu / 5500.f, 0.65f),//downleft

					ImColor(XMenu / 5500.f, XMenu / 5500.f, XMenu / 5500.f, 0.65f));//downright

				

				if (!TextureImage)
					D3DXCreateTextureFromFileExA(pDevice, pszPic, 50, 50, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &TextureImage);


				if (!LegitTabImg)
					D3DXCreateTextureFromFileInMemoryEx(pDevice, &NameLegitArray, sizeof(NameLegitArray), 1000, 1000, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &LegitTabImg);

				if (RageTabImg == nullptr)
					D3DXCreateTextureFromFileInMemoryEx(pDevice, &NameRageArray, sizeof(NameRageArray),1000, 1000, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &RageTabImg);

				if (VisualsTabImg == nullptr)D3DXCreateTextureFromFileInMemoryEx(pDevice
					, &NameVisualsArray, sizeof(NameVisualsArray),
					1000, 1000, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &VisualsTabImg);


				if (MiscTabImg == nullptr)D3DXCreateTextureFromFileInMemoryEx(pDevice
					, &NameMiscArray, sizeof(NameMiscArray),
					1000, 1000, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &MiscTabImg);
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.05f, 1.0f, 0.05f, 0.f));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.05f, 1.0f, 0.05f, 0.f));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.05f, 1.0f, 0.05f, 0.f));
				ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.05f, 1.0f, 0.05f, 0.f));
				ImGui::PushStyleColor(ImGuiCol_BorderShadow, ImVec4(0.05f, 1.0f, 0.05f, 0.f));
				
				
				ImVec2 curWindowPos = ImGui::GetWindowPos();
				//windowDrawList->AddImage(TittleBar, ImVec2(curWindowPos.x + 750 / 2.5f + 30, curWindowPos.y), ImVec2(curWindowPos.x + 750 / 2.5f + 125, curWindowPos.y + 95));

				//ImGui::Text(("                                                                     "));
				//ImGui::SameLine();
				//ImGui::Image(TittleBar, ImVec2(150, 75));

				//ImGui::Text(("        "));
				//ImGui::Text(("        "));
				//ImGui::Text(("        "));
				//ImGui::Text(("        "));

				//ImGui::Text(("         "));
				//ImGui::SameLine();
				 
			
				ImGui::Image(RageTabImg, ImVec2(50, 50), ImVec2(0, 0), ImVec2(1, 1));
				ImGui::SameLine();
				//if (ImGui::ImageButton(LegitTabImg, ImVec2(105, 105))) 
				if(ImGui::Button("Legit", ImVec2(125, 50)))
				{
					rageTab = false;
					legitTab = true;
					visualsTab = false;
					changer = false;
					configTab = false;
					miscTab = false;
					skinsTab = false;
				}
				//ImGui::SameLine();
				//ImGui::Text(("       "));
				ImGui::SameLine();
				//if (ImGui::ImageButton(RageTabImg, ImVec2(105, 105))) 
				if (ImGui::Button("Rage", ImVec2(125, 50)))
				{
					rageTab = true;
					legitTab = false;
					visualsTab = false;
					changer = false;
					configTab = false;
					miscTab = false;
					skinsTab = false;
				}
				ImGui::SameLine();
				//ImGui::Text(("       "));
				//ImGui::SameLine();
				//if (ImGui::ImageButton(VisualsTabImg, ImVec2(105, 105))) 
				if (ImGui::Button("Visual", ImVec2(125, 50)))
				{
					rageTab = false;
					legitTab = false;
					visualsTab = true;
					changer = false;
					configTab = false;
					miscTab = false;
					skinsTab = false;
				}
				ImGui::SameLine();
				//ImGui::Text(("       "));
				//ImGui::SameLine();
				//if (ImGui::ImageButton(MiscTabImg, ImVec2(105, 105))) 
				if (ImGui::Button("Misc", ImVec2(125, 50)))
				{
					rageTab = false;
					legitTab = false;
					visualsTab = false;
					miscTab = true;
					skinsTab = false;
				}
				ImGui::SameLine();
				if (ImGui::Button("Skins", ImVec2(125, 50))) {

					rageTab = false;
					legitTab = false;
					visualsTab = false;
					changer = false;
					configTab = false;
					miscTab = false;
					skinsTab = true;

				}

				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
				ImGui::PopStyleColor();


				if (skinsTab)
					DrawskinschildMeme(notFull1 || notFull2);
				if (rageTab)
					DrawRagechildMeme(notFull1 || notFull2);
				if (visualsTab)
					DrawVisualschildMeme(notFull1 || notFull2);
				if (miscTab)
					DrawMiscchildMeme(notFull1 || notFull2);
				if(legitTab)
					DrawlegitchildMeme(notFull1 || notFull2);
		

			}
			ImGui::End();


			ImGui::PopFont();


		}

		ImGui::Render();
	}


}