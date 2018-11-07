#include "stdafx.h"
#include "DrawModel.h"
#include "Chamz.h"


DrawModel_t oDrawModel = NULL;

void __fastcall DrawModel(void* _this, void* edx, void* results, DrawModelInfo_t& info, matrix3x4* pBoneToWorld, float* pFlexWeights, float* pFlexDelayedWeights, Vector& origin, int drawFlags)
{
	if (!Interfaces.pEngine->IsConnected() || !Interfaces.pEngine->IsInGame() || !G::LocalPlayer || !G::LocalPlayer->isAlive() || !g_Options.Visuals.Visuals_Chams)
		return oDrawModel(_this, results, info, pBoneToWorld, pFlexWeights, pFlexDelayedWeights, origin, drawFlags);


	if (Chams::DrawModel(oDrawModel, _this, results, info, pBoneToWorld, pFlexWeights, pFlexDelayedWeights, origin, drawFlags))
	{
		Interfaces.g_pModelRender->ForcedMaterialOverride(NULL);
		return;
	}

	return oDrawModel(_this, results, info, pBoneToWorld, pFlexWeights, pFlexDelayedWeights, origin, drawFlags);
}
