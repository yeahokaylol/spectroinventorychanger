#include "ResolveFULLRecode.h"


namespace ResolverV3
{


	RecvVarProxyFn oRecvLowerBodyYawTarget = NULL;
	RecvVarProxyFn oRecvEyeAnglesX = NULL;
	RecvVarProxyFn oRecvEyeAnglesY = NULL;
	RecvVarProxyFn oRecvEyeAnglesZ = NULL;





	bool Filter(CBaseEntity *entity)
	{
		if (!entity) return true;
		if (entity == G::LocalPlayer) return true;
		if (entity->isAlive() == false) return true;
		if (entity->GetTeam() != 2 && entity->GetTeam() != 3) return true;
		if (entity->GetClientClass()->m_ClassID != _CCSPlayer) return true; // !CCSPlayer
		if (entity->IsDormant()) return true;
		if (entity->GetIndex() >= 64) return true;
		if (entity->GetIndex() < 0) return true;


		return false;
	}

	

	void RecvLowerBodyYawTarget(const CRecvProxyData *pData, CBaseEntity *entity, void *pOut)
	{
		if (entity)
		{
			float value = pData->m_Value.m_Float;

			*(float*)pOut = value;
		}

		oRecvLowerBodyYawTarget(pData, entity, pOut);
	}

	void RecvEyeAnglesX(const CRecvProxyData *pData, CBaseEntity *entity, void *pOut)
	{
		if (g_Options.Ragebot.Ragebot_Resolver && g_Options.Ragebot.Ragebot_AimbotEnabled)
		{
			if (entity)
			{
				
					float value = pData->m_Value.m_Float;

					*(float*)pOut = value;
				
			}
		}

		oRecvEyeAnglesX(pData, entity, pOut);
	}

	void RecvEyeAnglesY(const CRecvProxyData *pData, CBaseEntity *entity, void *pOut)
	{
		if (g_Options.Ragebot.Ragebot_Resolver && g_Options.Ragebot.Ragebot_AimbotEnabled)
		{
			if (entity && !Filter(entity))
			{
					float value = pData->m_Value.m_Float;

					
					*(float*)pOut = value;
			}
		}

		oRecvEyeAnglesY(pData, entity, pOut);
	}

	void RecvEyeAnglesZ(const CRecvProxyData *pData, CBaseEntity *entity, void *pOut)
	{
		if (g_Options.Ragebot.Ragebot_Resolver && g_Options.Ragebot.Ragebot_AimbotEnabled)
		{
			if (entity && !Filter(entity))
			{
			
					float value = pData->m_Value.m_Float;

					
					*(float*)pOut = value;
			}
		}

		oRecvEyeAnglesZ(pData, entity, pOut);
	}

};
