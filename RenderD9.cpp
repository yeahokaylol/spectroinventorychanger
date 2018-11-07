#include "stdafx.h"
#include "Global.h"
#include "RenderD9.h"
#include "NameSpace.h"
#include "imgui\dx9\imgui_dx9.h"

Render *render = new Render();

Render::Render()
{
	pDevice = nullptr;

	setupComplete = false;
	resourcesCreated = false;
	locked = false;

	line = NULL;
	fntVerdana9 = NULL;
	fntVerdana10 = NULL;
	fntVerdana11 = NULL;
	fntVerdana12 = NULL;
	fntWeaponIcon = NULL;
}

Render::~Render()
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	ImGui_ImplDX9_Shutdown();

	g_Options.Visuals.Enabled = false;

	SAFE_RELEASE(line);
	SAFE_RELEASE(fntVerdana12);
	SAFE_RELEASE(fntVerdana11);
	SAFE_RELEASE(fntVerdana10);
	SAFE_RELEASE(fntVerdana9);
	SAFE_RELEASE(fntWeaponIcon);

	resourcesCreated = false;
	locked = true;


	if (INIT::OldWindow)
	{
		SetWindowLongPtr(render->window, GWLP_WNDPROC, (LONG_PTR)INIT::OldWindow);
	}
}

bool getFont(const std::string& name, std::string& path) {
	char buffer[MAX_PATH];
	HKEY registryKey;

	GetWindowsDirectoryA(buffer, MAX_PATH);
	std::string fontsFolder = buffer + std::string("\\Fonts\\");

	if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows NT\\CurrentVersion\\Fonts", 0, KEY_READ, &registryKey)) {
		return false;
	}

	uint32_t valueIndex = 0;
	char valueName[MAX_PATH];
	uint8_t valueData[MAX_PATH];
	std::wstring wsFontFile;

	do {
		uint32_t valueNameSize = MAX_PATH;
		uint32_t valueDataSize = MAX_PATH;
		uint32_t valueType;

		auto error = RegEnumValueA(
			registryKey,
			valueIndex,
			valueName,
			reinterpret_cast<DWORD*>(&valueNameSize),
			0,
			reinterpret_cast<DWORD*>(&valueType),
			valueData,
			reinterpret_cast<DWORD*>(&valueDataSize));

		valueIndex++;

		if (error == ERROR_NO_MORE_ITEMS) {
			RegCloseKey(registryKey);
			return false;
		}

		if (error || valueType != REG_SZ) {
			continue;
		}

		if (_strnicmp(name.data(), valueName, name.size()) == 0) {
			path = fontsFolder + std::string((char*)valueData, valueDataSize);
			RegCloseKey(registryKey);
			return true;
		}
	} while (true);

	return false;
}

ImFont* Default;
ImFont* GlobalFont = nullptr;
void color()
{
	auto bColor = g_Options.g_fBColor;
	auto mColor = g_Options.g_fMColor;
	auto tColor = g_Options.g_fTColor;

	ImColor mainColor = ImColor(0, 102, 255);//ImColor(MenuColor[0], MenuColor[1], MenuColor[2], 1.f);
	ImColor bodyColor = ImColor(24, 24, 24, 239);
	ImColor fontColor = ImColor(150, 150, 150, 255);

	ImGuiStyle& style = ImGui::GetStyle();
	//std::string font_path; ImFontConfig config;
	ImGuiIO& io = ImGui::GetIO();

	//if (getFont("Verdana", font_path))
	//	io.Fonts->AddFontFromFileTTF(font_path.data(), 15.0f, &config, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
	Default = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Verdana.ttf", 14.0f);
	GlobalFont = io.Fonts->AddFontFromMemoryCompressedBase85TTF(Pharamcy, 13.0f, NULL, io.Fonts->GetGlyphRangesCyrillic());

	//io.Fonts->AddFontDefault();

	ImVec4 mainColorHovered = ImVec4(mainColor.Value.x + 0.1f, mainColor.Value.y + 0.1f, mainColor.Value.z + 0.1f, mainColor.Value.w);
	ImVec4 mainColorActive = ImVec4(mainColor.Value.x + 0.2f, mainColor.Value.y + 0.2f, mainColor.Value.z + 0.2f, mainColor.Value.w);
	ImVec4 menubarColor = ImVec4(bodyColor.Value.x, bodyColor.Value.y, bodyColor.Value.z, bodyColor.Value.w - 0.8f);
	ImVec4 frameBgColor = ImVec4(bodyColor.Value.x, bodyColor.Value.y, bodyColor.Value.z, bodyColor.Value.w + .1f);
	ImVec4 tooltipBgColor = ImVec4(bodyColor.Value.x, bodyColor.Value.y, bodyColor.Value.z, bodyColor.Value.w + .05f);

	style.Alpha = 1.0f;
	style.WindowPadding = ImVec2(8, 8);
	style.WindowMinSize = ImVec2(32, 32);
	style.WindowRounding = 0.0f;
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.ChildWindowRounding = 3.0f;
	style.FramePadding = ImVec2(4, 1);
	style.FrameRounding = 0.0f;
	style.ItemSpacing = ImVec2(9, 9);
	style.ItemInnerSpacing = ImVec2(4, 4);
	style.TouchExtraPadding = ImVec2(0, 0);
	style.IndentSpacing = 21.0f;
	style.ColumnsMinSpacing = 3.0f;
	style.ScrollbarSize = 12.0f;
	style.ScrollbarRounding = 0.0f;
	style.GrabMinSize = 0.1f;
	style.GrabRounding = 16.0f;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.DisplayWindowPadding = ImVec2(22, 22);
	style.DisplaySafeAreaPadding = ImVec2(4, 4);
	style.AntiAliasedLines = true;
	style.AntiAliasedShapes = true;
	style.CurveTessellationTol = 1.25f;


	float MenuColor[3] = { 0.f, 1.f, 0.f };

	ImGuiStyle& styled = ImGui::GetStyle();

	styled.Colors[ImGuiCol_Text] = ImVec4(0.86f, 0.93f, 0.89f, 0.78f);
	styled.Colors[ImGuiCol_TextDisabled] = ImVec4(0.86f, 0.93f, 0.89f, 0.78f);
	styled.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.13f, 0.13f, 1.f);
	styled.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.14f, 0.14f, 0.14f, 0.6f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.27f, 0.27f, 0.27f, 0.2f);
	styled.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	styled.Colors[ImGuiCol_FrameBg] = ImVec4(0.22f, 0.22f, 0.22f, 1.f);
	styled.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.22f, 0.22f, 0.22f, 1.f);
	styled.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.22f, 0.22f, 0.22f, 1.f);
	styled.Colors[ImGuiCol_TitleBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.f);
	styled.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.1f, 0.1f, 0.1f, 1.f);
	styled.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.1f, 0.1f, 0.1f, 1.f);
	styled.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
	styled.Colors[ImGuiCol_ScrollbarBg] = ImVec4(frameBgColor.x + .1f, frameBgColor.y + .1f, frameBgColor.z + .1f, frameBgColor.w);
	styled.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.40f, 0.40f, 0.40f, 1.f);
	styled.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 1.f);
	styled.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.40f, 0.40f, 0.40f, 1.f);
	styled.Colors[ImGuiCol_ComboBg] = frameBgColor;
	styled.Colors[ImGuiCol_CheckMark] = ImColor(255, 255, 255);
	styled.Colors[ImGuiCol_SliderGrab] = ImColor(0, 102, 255);
	styled.Colors[ImGuiCol_SliderGrabActive] = ImColor(0, 102, 255);
	styled.Colors[ImGuiCol_Button] = ImVec4(0.1f, 0.1f, 0.1f, 0.95f);
	styled.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.1f, 0.1f, 0.1f, 0.95f);
	styled.Colors[ImGuiCol_ButtonActive] = ImVec4(0.1f, 0.1f, 0.1f, 0.95f);
	styled.Colors[ImGuiCol_Header] = mainColor;
	styled.Colors[ImGuiCol_HeaderHovered] = mainColorHovered;
	styled.Colors[ImGuiCol_HeaderActive] = mainColorActive;

	styled.Colors[ImGuiCol_Column] = ImVec4(.30f, .30f, .30f, 1.f);
	styled.Colors[ImGuiCol_ColumnHovered] = mainColorHovered;
	styled.Colors[ImGuiCol_ColumnActive] = mainColorActive;
}
void GUI_Init(IDirect3DDevice9* pDevice)
{


	ImGui_ImplDX9_Init(render->window, render->pDevice);

	color();

	G::d3dinit = true;
}
void Render::Setup(LPDIRECT3DDEVICE9 pDevice)
{
	if (locked) return;

	this->pDevice = pDevice;

	if (window)
	{
		if (GetCursorPos(&mouse))
			ScreenToClient(window, &mouse);
	}

	// misc
	D3DDEVICE_CREATION_PARAMETERS cp;

	pDevice->GetCreationParameters(&cp);
	pDevice->GetViewport(&viewPort);

	window = cp.hFocusWindow;

	if (setupComplete)
		return;


	if (!INIT::OldWindow)
	{
		INIT::OldWindow = (WNDPROC)SetWindowLongPtr(render->window, GWLP_WNDPROC, (LONG_PTR)Hooked_WndProc);
	}



	if (!G::d3dinit)
		GUI_Init(pDevice);

	// resources
	if (!resourcesCreated)
	{
		D3DXCreateLine(pDevice, &line);
		D3DXCreateFont(pDevice, 9, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DRAFT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, ("Verdana"), &fntVerdana9);
		D3DXCreateFont(pDevice, 10, 5, FW_NORMAL, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, ("Verdana"), &fntVerdana10);
		D3DXCreateFont(pDevice, 11, 5, FW_NORMAL, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, ("Verdana"), &fntVerdana11);
		D3DXCreateFont(pDevice, 12, 5, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, ("Verdana"), &fntVerdana12);
		D3DXCreateFont(pDevice, 11, 0, FW_NORMAL, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, ("csgo_icons"), &fntWeaponIcon);
		resourcesCreated = true;
	}

	setupComplete = true;
}

void Render::OnLostDevice()
{
	if (line)
		line->OnLostDevice();

	if (fntVerdana9)
		fntVerdana9->OnLostDevice();

	if (fntVerdana10)
		fntVerdana10->OnLostDevice();

	if (fntVerdana11)
		fntVerdana11->OnLostDevice();

	if (fntVerdana12)
		fntVerdana12->OnLostDevice();

	if (fntWeaponIcon)
		fntWeaponIcon->OnLostDevice();

	ImGui_ImplDX9_InvalidateDeviceObjects();

}

void Render::OnResetDevice()
{
	if (line)
		line->OnResetDevice();

	if (fntVerdana10)
		fntVerdana10->OnResetDevice();

	if (fntVerdana11)
		fntVerdana11->OnResetDevice();

	if(fntVerdana12)
		fntVerdana12->OnResetDevice();

	if (fntVerdana9)
		fntVerdana9->OnResetDevice();


	if (fntWeaponIcon)
		fntWeaponIcon->OnResetDevice();
	ImGui_ImplDX9_CreateDeviceObjects();
}
#include "D9Visuals.h"

IDirect3DStateBlock9* pixel_state = NULL; IDirect3DVertexDeclaration9* vertDec; IDirect3DVertexShader9* vertShader;
DWORD dwOld_D3DRS_COLORWRITEENABLE;

void SaveState(IDirect3DDevice9 * pDevice)
{
	pDevice->GetRenderState(D3DRS_COLORWRITEENABLE, &dwOld_D3DRS_COLORWRITEENABLE);
	//	pDevice->CreateStateBlock(D3DSBT_PIXELSTATE, &pixel_state); // This seam not to be needed anymore because valve fixed their shit
	pDevice->GetVertexDeclaration(&vertDec);
	pDevice->GetVertexShader(&vertShader);
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);
	pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, false);
	pDevice->SetSamplerState(NULL, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(NULL, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(NULL, D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(NULL, D3DSAMP_SRGBTEXTURE, NULL);
}

void RestoreState(IDirect3DDevice9 * pDevice) // not restoring everything. Because its not needed.
{
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, dwOld_D3DRS_COLORWRITEENABLE);
	pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, true);
	//pixel_state->Apply(); 
	//pixel_state->Release();
	pDevice->SetVertexDeclaration(vertDec);
	pDevice->SetVertexShader(vertShader);
}

int Render::FrameRate() {
	static int iFps, iLastFps;
	static float flLastTickCount, flTickCount;
	flTickCount = clock() * 0.001f;
	iFps++;
	if ((flTickCount - flLastTickCount) >= 1.0f) {
		flLastTickCount = flTickCount;
		iLastFps = iFps;
		iFps = 0;
	}
	return iLastFps;
} 

void Render::Present(LPDIRECT3DDEVICE9 pDevice)
{
	if (!render->setupComplete)
		return;
	if (!render->pDevice)
		return;
	if (!pDevice)
		return;

	DrawFilledRectangle(viewPort.Width - 160, 3, 17, 155, D3DCOLOR_ARGB(230,15,15,15));

	static char cTitle[256];
	sprintf_s(cTitle, "FPS: %i", FrameRate());


	//DrawStringWithFont(fntVerdana11, viewPort.Width - 159, 5, D3D_COLOR_BLACK(240), " LORE-CHEATS.COM | %s", cTitle);
	DrawStringWithFont(fntVerdana10, viewPort.Width - 160, 6, D3D_COLOR_WHITE(240), " LORE-CHEATS.COM | %s", cTitle);

	//DrawStringWithFont(fntVerdana11, viewPort.Width - 159, 5, D3D_COLOR_BLACK(240), " LORE-CHEATS.COM | %s", cTitle);
	//DrawStringWithFont(fntVerdana10, viewPort.Width - 160, 6, D3D_COLOR_WHITE(240), " LORE-CHEATS.COM | %s", cTitle);


	if (g_Options.Visuals.Enabled)
	{

		D9Visuals::Render();

	}
	
	SaveState(pDevice);

	//Menu();
	MenuUI::Render(pDevice);

	RestoreState(pDevice);
}


// Misc
void Render::SetFont(LPD3DXFONT font)
{
	this->fntVerdana10 = font;
}



bool Render::WorldToScreen(Vector vOrigin, Vector &vScreen)
{


	float w = G::viewMatrix[3][0] * vOrigin.x + G::viewMatrix[3][1] * vOrigin.y + G::viewMatrix[3][2] * vOrigin.z + G::viewMatrix[3][3];

	float ScreenWidth = (float)viewPort.Width;
	float ScreenHeight = (float)viewPort.Height;

	if (w > 0.01f)
	{
		float inverseWidth = 1.f / w;
		vScreen.x = (float)((ScreenWidth / 2) + (0.5 * ((G::viewMatrix[0][0] * vOrigin.x + G::viewMatrix[0][1] * vOrigin.y + G::viewMatrix[0][2] * vOrigin.z + G::viewMatrix[0][3]) * inverseWidth) * ScreenWidth + 0.5));
		vScreen.y = (float)((ScreenHeight / 2) - (0.5 * ((G::viewMatrix[1][0] * vOrigin.x + G::viewMatrix[1][1] * vOrigin.y + G::viewMatrix[1][2] * vOrigin.z + G::viewMatrix[1][3]) * inverseWidth) * ScreenHeight + 0.5));
		return true;
	}

	return false;
}



// Rendering
void Render::DrawLine(float x1, float y1, float x2, float y2, float size, bool antiAlias, D3DCOLOR COLOR)
{
	D3DXVECTOR2 dLine[2];

	line->SetWidth(size);

	dLine[1] = { x1, y1 };
	dLine[0] = { x2, y2 };

	if (antiAlias)
		line->SetAntialias(1);
	else
		line->SetAntialias(0);

	line->Begin();
	line->Draw(dLine, 2, COLOR);
	line->End();
}

void Render::DrawLineFast(float x1, float y1, float x2, float y2, D3DCOLOR COLOR)
{
	D3DTLVERTEX qV[2] = {
		{ x1, y1, 0.0f, 1.0f, COLOR },
	{ x2, y2, 0.0f, 1.0f, COLOR },
	};

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); //pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCALPHA); // neon mode
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_FOGENABLE, false);

	DWORD oldFVF;

	pDevice->GetFVF(&oldFVF);
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	pDevice->SetTexture(0, 0);
	pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, qV, sizeof(D3DTLVERTEX));
	pDevice->SetFVF(oldFVF);
}

void Render::DrawString(float x, float y, D3DCOLOR color, char *format, ...)
{
	char buffer[256];
	RECT fontRect = { (int)x, (int)y, (int)x, (int)y };

	va_list va_argList;

	va_start(va_argList, format);
	wvsprintf(buffer, format, va_argList);
	va_end(va_argList);

	fntVerdana10->DrawText(NULL, buffer, strlen(buffer), &fontRect, DT_NOCLIP, color);
}

void Render::DrawStringW(float x, float y, D3DCOLOR color, WCHAR *format, ...)
{
	wchar_t buffer[256];
	RECT fontRect = { (int)x, (int)y, (int)x, (int)y };

	va_list va_argList;

	va_start(va_argList, format);
	wvsprintfW(buffer, format, va_argList);
	va_end(va_argList);

	fntVerdana10->DrawTextW(NULL, buffer, -1, &fontRect, DT_NOCLIP, color);
}

void Render::DrawStringWithFont(LPD3DXFONT fnt, float x, float y, D3DCOLOR color, char *format, ...)
{
	char buffer[256];
	RECT fontRect = { (int)x, (int)y, (int)x, (int)y };

	va_list va_argList;

	va_start(va_argList, format);
	wvsprintf(buffer, format, va_argList);
	va_end(va_argList);

	fnt->DrawText(NULL, buffer, strlen(buffer), &fontRect, DT_NOCLIP, color);
}

void Render::DrawStringWithFontW(LPD3DXFONT fnt, float x, float y, D3DCOLOR color, wchar_t *format, ...)
{
	wchar_t buffer[256];
	RECT fontRect = { (int)x, (int)y, (int)x, (int)y };

	va_list va_argList;

	va_start(va_argList, format);
	wvsprintfW(buffer, format, va_argList);
	va_end(va_argList);

	fnt->DrawTextW(NULL, buffer, -1, &fontRect, DT_NOCLIP, color);
}

float Render::GetTextWitdh(char *text, LPD3DXFONT fnt)
{
	RECT fontRect = { 0,0,0,0 };

	fnt->DrawText(NULL, text, strlen(text), &fontRect, DT_CALCRECT, D3DCOLOR_XRGB(0, 0, 0));

	return fontRect.right - fontRect.left;
}

void Render::TexturedPolygon(int n, std::vector<FontVertex_tForCrosshair> vertice, CColor color)
{
	static int texture_id = Interfaces.pSurface->CreateNewTextureID(true); // 
	static unsigned char buf[4] = { 255, 255, 255, 255 };
	Interfaces.pSurface->DrawSetTextureRGBA(texture_id, buf, 1, 1); //
	Interfaces.pSurface->DrawSetColor1(color); //
	Interfaces.pSurface->DrawSetTexture(texture_id); //
	Interfaces.pSurface->DrawTexturedPolygon(n, vertice.data()); //
}

int Render::GetTextWitdhW(wchar_t *text, LPD3DXFONT fnt)
{
	RECT fontRect = { 0,0,0,0 };

	fnt->DrawTextW(NULL, text, -1, &fontRect, DT_CALCRECT, D3DCOLOR_XRGB(0, 0, 0));

	return fontRect.right - fontRect.left;
}

#define M_PI		3.14159265358979323846f

void Render::DrawFilledCircle1(Vector2D center, CColor color, float radius, float points) {
	std::vector<FontVertex_tForCrosshair> vertices;
	float step = (float)M_PI * 2.0f / points;

	for (float a = 0; a < (M_PI * 2.0f); a += step)
		vertices.push_back(FontVertex_tForCrosshair(Vector2DForCrosshair(radius * cosf(a) + center.x, radius * sinf(a) + center.y)));

	render->TexturedPolygon((int)points, vertices, color);
}

void Render::DrawCircle(float x, float y, int radius, int numSides, float size, D3DCOLOR color)
{
	float step = (float)(D3DX_PI * 2.0 / numSides);

	if (step <= 0)
		return;

	for (float a = 0; a < D3DX_PI*2.0; a += step)
	{
		float X1 = radius * cosf(a) + x;
		float Y1 = radius * sinf(a) + y;
		float X2 = radius * cosf(a + step) + x;
		float Y2 = radius * sinf(a + step) + y;

		DrawLine(X1, Y1, X2, Y2, size, true, color);
	}
}


void Render::DrawCircleFast(float x, float y, int radius, int numSides, D3DCOLOR color)
{
	float step = (float)(D3DX_PI * 2.0 / numSides);

	if (step <= 0)
		return;

	for (float a = 0; a < D3DX_PI*2.0; a += step)
	{
		float X1 = radius * cosf(a) + x;
		float Y1 = radius * sinf(a) + y;
		float X2 = radius * cosf(a + step) + x;
		float Y2 = radius * sinf(a + step) + y;

		DrawLineFast(X1, Y1, X2, Y2, color);
	}
}
struct SD3DVertex {
	float x, y, z, rhw;
	DWORD colour;
};
void Render::DrawFilledCircleFast(float x, float y, int radius, int numSides, D3DCOLOR color)
{
	SD3DVertex* pVertex = new SD3DVertex[numSides + 1];
	for (int i = 0; i <= numSides; i++) pVertex[i] = { x + radius * cos(D3DX_PI * (i / (numSides / 2.0f))), y + radius * sin(D3DX_PI * (i / (numSides / 2.0f))), 0.0f, 1.0f, color };
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, numSides, pVertex, sizeof(SD3DVertex));
	delete[] pVertex;
}




void Render::DrawCornierBoxFastAlpha(float x, float y, float height, float width, D3DCOLOR COLOR, float alpha)
{
	D3DXVECTOR2 points[4][3];



	switch (g_Options.Visuals.Visuals_BoxType)
	{
	case 0: 
	{
		points[0][0] = D3DXVECTOR2(x, y);
		points[0][1] = D3DXVECTOR2(x + (width)* alpha, y);
		points[0][2] = D3DXVECTOR2(x, y + (height)* alpha);

		points[1][0] = D3DXVECTOR2(x + width, y);
		points[1][1] = D3DXVECTOR2(x + width - (width)* alpha, y);
		points[1][2] = D3DXVECTOR2(x + width, y + (height)* alpha);


		points[2][0] = D3DXVECTOR2(x, y + height);
		points[2][1] = D3DXVECTOR2(x + (width)* alpha, y + height);
		points[2][2] = D3DXVECTOR2(x, y + height - (height)* alpha);

		points[3][0] = D3DXVECTOR2(x + width, y + height);
		points[3][1] = D3DXVECTOR2(x + width - (width)* alpha, y + height);
		points[3][2] = D3DXVECTOR2(x + width, y + height - (height)* alpha);
	}break;
	case 1:
	{
		points[0][0] = D3DXVECTOR2(x, y);
		points[0][1] = D3DXVECTOR2(x + (width / 4.5f)* alpha, y);
		points[0][2] = D3DXVECTOR2(x, y + (height / 5.f)* alpha);

		points[1][0] = D3DXVECTOR2(x + width, y);
		points[1][1] = D3DXVECTOR2(x + width - (width / 4.5f)* alpha, y);
		points[1][2] = D3DXVECTOR2(x + width, y + (height / 5.f)* alpha);


		points[2][0] = D3DXVECTOR2(x, y + height);
		points[2][1] = D3DXVECTOR2(x + (width / 4.5f)* alpha, y + height);
		points[2][2] = D3DXVECTOR2(x, y + height - (height / 5.f)* alpha);

		points[3][0] = D3DXVECTOR2(x + width, y + height);
		points[3][1] = D3DXVECTOR2(x + width - (width / 4.5f)* alpha, y + height);
		points[3][2] = D3DXVECTOR2(x + width, y + height - (height / 5.f)* alpha);
	}break;
	default: break;
	}
		


	

	DrawLineFast(points[0][0].x, points[0][0].y, points[0][1].x, points[0][1].y, COLOR);
	DrawLineFast(points[0][0].x, points[0][0].y, points[0][2].x, points[0][2].y, COLOR);

	DrawLineFast(points[1][0].x, points[1][0].y, points[1][1].x, points[1][1].y, COLOR);
	DrawLineFast(points[1][0].x, points[1][0].y, points[1][2].x, points[1][2].y, COLOR);
	
	DrawLineFast(points[2][0].x, points[2][0].y, points[2][1].x, points[2][1].y, COLOR);
	DrawLineFast(points[2][0].x, points[2][0].y, points[2][2].x, points[2][2].y, COLOR);

	DrawLineFast(points[3][0].x, points[3][0].y, points[3][1].x, points[3][1].y, COLOR);
	DrawLineFast(points[3][0].x, points[3][0].y, points[3][2].x, points[3][2].y, COLOR);
}

void Render::DrawBox(float x, float y, float height, float width, float size, D3DCOLOR COLOR)
{
	D3DXVECTOR2 points[5];

	points[0] = D3DXVECTOR2(x, y);
	points[1] = D3DXVECTOR2(x + width, y);
	points[2] = D3DXVECTOR2(x + width, y + height);
	points[3] = D3DXVECTOR2(x, y + height);
	points[4] = D3DXVECTOR2(x, y);

	line->SetWidth(size);
	line->SetAntialias(1);
	line->Begin();
	line->Draw(points, 5, COLOR);
	line->End();
}

void Render::DrawBoxFast(float x, float y, float height, float width, D3DCOLOR COLOR)
{
	D3DXVECTOR2 points[5];

	points[0] = D3DXVECTOR2(x, y);
	points[1] = D3DXVECTOR2(x + width, y);
	points[2] = D3DXVECTOR2(x + width, y + height);
	points[3] = D3DXVECTOR2(x, y + height);
	points[4] = D3DXVECTOR2(x, y);

	DrawLineFast(points[0].x, points[0].y, points[1].x, points[1].y, COLOR);
	DrawLineFast(points[1].x, points[1].y, points[2].x, points[2].y, COLOR);
	DrawLineFast(points[2].x, points[2].y, points[3].x, points[3].y, COLOR);
	DrawLineFast(points[3].x, points[3].y, points[4].x, points[4].y, COLOR);
}
void Render::DrawBoxFastAlpha(float x, float y, float height, float width, D3DCOLOR COLOR, float alpha)
{
	D3DXVECTOR2 points[5];

	/*points[0] = D3DXVECTOR2(x, y);
	points[1] = D3DXVECTOR2(x + width * alpha, y);
	points[2] = D3DXVECTOR2(x + width * alpha, y + height * alpha );
	points[3] = D3DXVECTOR2(x, y + height * alpha);
	points[4] = D3DXVECTOR2(x, y);*/



	points[0] = D3DXVECTOR2(x, y);
	points[1] = D3DXVECTOR2(x + width * alpha, y);
	points[2] = D3DXVECTOR2(x + width, y + height * alpha);
	points[3] = D3DXVECTOR2(x, y + height * alpha);
	points[4] = D3DXVECTOR2(x, y);


	DrawLineFast(points[0].x, points[0].y, points[1].x, points[1].y, COLOR);
	DrawLineFast(points[1].x, points[1].y, points[2].x, points[2].y, COLOR);
	DrawLineFast(points[2].x, points[2].y, points[3].x, points[3].y, COLOR);
	DrawLineFast(points[3].x, points[3].y, points[4].x, points[4].y, COLOR);
}

void Render::DrawFilledRectangle(float x, float y, float height, float width, D3DCOLOR COLOR)
{
	D3DXVECTOR2 points[5];

	/*
	x	y
	h	w
	*/

	D3DTLVERTEX t1[3] = {
		{ x, y, 0.0f, 1.0f, COLOR },
	{ x + width, y, 0.0f, 1.0f, COLOR },
	{ x + width, y + height, 0.0f, 1.0f, COLOR },
	};

	D3DTLVERTEX t2[3] = {
		{ x , y, 0.0f, 1.0f, COLOR },
	{ x + width , y + height, 0.0f, 1.0f, COLOR },
	{ x, y + height, 0.0f, 1.0f, COLOR },
	};

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); //pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCALPHA); // neon mode
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_FOGENABLE, false);

	DWORD oldFVF;

	pDevice->GetFVF(&oldFVF);
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	pDevice->SetTexture(0, 0);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 1, t1, sizeof(D3DTLVERTEX));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 1, t2, sizeof(D3DTLVERTEX));
	pDevice->SetFVF(oldFVF);
}