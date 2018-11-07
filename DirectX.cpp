#include "stdafx.h"
#include "Global.h"
#include "RenderD9.h"




Reset_t Reset = nullptr;
Present_t Present = nullptr;
EndScene_t EndScene = nullptr;

VMT *hookDirectX = nullptr;

bool reseting = false;

void DirectXX::ApplyHook()
{
	static IDirect3DDevice9* d3d9_device = **reinterpret_cast<IDirect3DDevice9***>(Utils.FindPatternIDA("shaderapidx9.dll", "A1 ? ? ? ? 50 8B 08 FF 51 0C") + 1);

	hookDirectX = new VMT(d3d9_device);

	hookDirectX->HookVM(&PresentHook, 17);
	Present = hookDirectX->GetOriginalMethod<Present_t>(17);

	hookDirectX->HookVM(&ResetHook, 16);
	Reset = hookDirectX->GetOriginalMethod<Reset_t>(16);
	hookDirectX->HookVM(&EndSceneHook, 42);
	EndScene = hookDirectX->GetOriginalMethod<EndScene_t>(42);

	hookDirectX->ApplyVMT();
}

void DirectXX::ReleaseHook()
{
	hookDirectX->ReleaseVMT();

	delete hookDirectX;
	hookDirectX = nullptr;
}


HRESULT WINAPI PresentHook(LPDIRECT3DDEVICE9 pDevice, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion)
{
	if (!render || INIT::Exit || reseting) return Present(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);


	// backup render states
	static const D3DRENDERSTATETYPE backupStates[] = { D3DRS_COLORWRITEENABLE, D3DRS_ALPHABLENDENABLE, D3DRS_SRCBLEND, D3DRS_DESTBLEND, D3DRS_BLENDOP, D3DRS_FOGENABLE };
	static const int size = sizeof(backupStates) / sizeof(DWORD);

	DWORD oldStates[size] = { 0 };

	for (int i = 0; i < size; i++)
		pDevice->GetRenderState(backupStates[i], &oldStates[i]);

	////////////////////////////////////////////////////////////////////
	// no draw fix
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xFFFFFFFF);

	render->Setup(pDevice);
	render->Present(pDevice);
	////////////////////////////////////////////////////////////////////

	// restore render states	
	for (int i = 0; i < size; i++)
		pDevice->SetRenderState(backupStates[i], oldStates[i]);

	// restore hook vmt
	/*static int elapsedFrames = 0;
	elapsedFrames++;
	if (elapsedFrames > 600)
	{
	hookDirectX->ApplyVMT();
	}*/

	return Present(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}


HRESULT WINAPI EndSceneHook(LPDIRECT3DDEVICE9 pDevice)
{
	if (!render || INIT::Exit || reseting) return EndScene(pDevice);

	return EndScene(pDevice);
}

HRESULT WINAPI ResetHook(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS *pPresentationParameters)
{
	if (!render || INIT::Exit) return Reset(pDevice, pPresentationParameters);

	DirectXX::Get().ReleaseHook();

	reseting = true;
	render->OnLostDevice();

	HRESULT ret = Reset(pDevice, pPresentationParameters);

	DirectXX::Get().ApplyHook();

//	if (ret == D3D_OK)
//	{
		reseting = false;
		render->OnResetDevice();
		render->Setup(pDevice);
//	}

	return ret;
}
