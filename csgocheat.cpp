//#include "stdafx.h"
#include "Tools/Hacks/Misc.h"

#include "NetVars.h"
#include "Offsets.h"
#include "SkinChanger-KentMeister.h"
#include "ResolveFULLRecode.h"
#include "Parser.h"




void HookProxies()
{
	ClientClass *pClass = Interfaces.pClient->GetAllClasses();
	while (pClass)
	{
		const char *pszName = pClass->m_pRecvTable->m_pNetTableName;
		if (!strcmp(pszName, ("DT_BaseViewModel")))
		{
			for (int i = 0; i < pClass->m_pRecvTable->m_nProps; i++)
			{
				RecvProp *pProp = &(pClass->m_pRecvTable->m_pProps[i]);

				if (!strcmp(pProp->m_pVarName, ("m_nModelIndex")))
				{

					//oModelIndexProxy = (RecvVarProxyFn)pProp->m_ProxyFn;
					oRecvnModelIndex = (RecvVarProxyFn)pProp->m_ProxyFn;
					pProp->m_ProxyFn = ViewModel_Index_Proxy;
					
				}
				if (!strcmp(pProp->m_pVarName, ("m_nSequence")))
				{
					oRecvProxySequence = (RecvVarProxyFn)pProp->m_ProxyFn;
					pProp->m_ProxyFn = RecvProxy_Sequence;
				}
			}
		}
		
		pClass = pClass->m_pNext;
	}
}



#include "RenderD9.h"
bool ExitCheat(int stage)
{
	if( !INIT::Exit && stage != 1)
		return false;

	Hacks.UnHook();
	Sleep( 200 );

	SetWindowLongPtr( render->window, GWL_WNDPROC, reinterpret_cast< LONG_PTR >( INIT::OldWindow ) );
	Sleep( 200 );

	FreeLibraryAndExitThread( INIT::Dll, 0 );
}


void SetupOffsets()
{
	NetVarManager->Initialize();
	Offsets::GrabOffsets();
}






DWORD WINAPI CheatMain( LPVOID lpThreadParameter )
{
	Interfaces.CreateInterfaces();

	SetupOffsets();

	Hacks.Hook();
	HookProxies();
	ParseSkins();
	G::LineToSmoke = (LineGoesThroughSmokeFn)Utils.FindPatternIDA(("client_panorama.dll"), ("55 8B EC 83 EC 08 8B 15 ? ? ? ? 0F 57 C0"));



	while (INIT::Exit == false)
	{
		
	}

	ExitCheat(0);

	if (!::FreeLibrary(INIT::Dll))
	::UnmapViewOfFile(INIT::Dll);

	return 0;
}
