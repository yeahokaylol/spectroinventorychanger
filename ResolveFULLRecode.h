#pragma once

#include "stdafx.h"

namespace ResolverV3
{

	void RecvLowerBodyYawTarget(const CRecvProxyData *pData, CBaseEntity *entity, void *pOut);
	void RecvEyeAnglesX(const CRecvProxyData *pData, CBaseEntity *entity, void *pOut);
	void RecvEyeAnglesY(const CRecvProxyData *pData, CBaseEntity *entity, void *pOut);
	void RecvEyeAnglesZ(const CRecvProxyData *pData, CBaseEntity *entity, void *pOut);
	bool Filter(CBaseEntity *entity);
	extern RecvVarProxyFn oRecvLowerBodyYawTarget;
	extern RecvVarProxyFn oRecvEyeAnglesX;
	extern RecvVarProxyFn oRecvEyeAnglesY;
	extern RecvVarProxyFn oRecvEyeAnglesZ;
};
