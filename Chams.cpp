#include "stdafx.h"
#include "Chams.h"




/*
enum LightType_t
{
	MATERIAL_LIGHT_DISABLE = 0,
	MATERIAL_LIGHT_POINT,
	MATERIAL_LIGHT_DIRECTIONAL,
	MATERIAL_LIGHT_SPOT,
};
struct LightDesc_t
{
	LightType_t m_Type;										//< MATERIAL_LIGHT_xxx
	Vector m_Color;											//< color+intensity 
	Vector m_Position;										//< light source center position
	Vector m_Direction;										//< for SPOT, direction it is pointing
	float  m_Range;											//< distance range for light.0=infinite
	float m_Falloff;										//< angular falloff exponent for spot lights
	float m_Attenuation0;									//< constant distance falloff term
	float m_Attenuation1;									//< linear term of falloff
	float m_Attenuation2;									//< quadatic term of falloff
	float m_Theta;											//< inner cone angle. no angular falloff 
															//< within this cone
	float m_Phi;											//< outer cone angle

															// the values below are derived from the above settings for optimizations
															// These aren't used by DX8. . used for software lighting.
	float m_ThetaDot;
	float m_PhiDot;
	unsigned int m_Flags;
protected:
	float OneOver_ThetaDot_Minus_PhiDot;
	float m_RangeSquared;
public:
};*/
/*
struct DrawModelInfo_t
{
	studiohdr_t		*m_pStudioHdr;
	void	*m_pHardwareData;
	void* m_Decals;
	int				m_Skin;
	int				m_Body;
	int				m_HitboxSet;
	DWORD			*m_pClientEntity;
	int				m_Lod;
	void	*m_pColorMeshes;
	bool			m_bStaticLighting;
	Vector			m_vecAmbientCube[6];		// ambient, and lights that aren't in locallight[]
	int				m_nLocalLightCount;
	LightDesc_t		m_LocalLightDescs[4];
};
*/







bool autsimv3 = false;

namespace Chams
{
	bool clean = true;
	bool materialsCreated = false;
	bool enablePlayersDraw = true;


	float colorHiddenEnemy[3], colorHiddenTeam[3], colorShowingEnemy[3], colorShowingTeam[3], colorShowingLocalPlayer[3];
	float colorWhite[3], colorDoctor[3], colorBlack[3], colorGlow[3];

	bool execute = true;
	bool dmeClean = true;
	bool frsClean = true;





	bool DrawModel(DrawModel_t oDrawModel, void *_this, void* results, DrawModelInfo_t& info, matrix3x4* pBoneToWorld, float* pFlexWeights, float* pFlexDelayedWeights, Vector& origin, int drawFlags)
	{
		DrawModelParams p = DrawModelParams{ oDrawModel, (DWORD*)_this, (DWORD*)results, info, pBoneToWorld, pFlexWeights, pFlexDelayedWeights, origin, drawFlags };

		static IMaterial* Covered_Lit;
		if (!autsimv3)
		{
			Covered_Lit = G::CreateMaterial(false, false);
			autsimv3 = true;
		}
		CBaseEntity *entity = (CBaseEntity*)((DWORD)info.m_pClientEntity - 4);
		CBaseEntity *pLocal = Hacks.LocalPlayer;
		studiohdr_t* hdr = info.m_pStudioHdr;

		if (!entity || !hdr || !pLocal)
			return false;

		string modelName = hdr->name;

		if (modelName.find(XorStr("shadow")) != -1)
			return false;

		if (modelName.find(XorStr("player")) != -1 && entity->GetClientClass()->m_ClassID == _CCSPlayer)
		{
			if (entity == pLocal)
			{
				if (Interfaces.pInput->m_fCameraInThirdPerson && pLocal->isAlive())
				{

					if (Settings.GetSetting(Tab_Visuals,Visuals_GhostAngle))
					{
						Interfaces.g_pModelRender->ForcedMaterialOverride(Covered_Lit);
						Covered_Lit->AlphaModulate(1);
						Covered_Lit->ColorModulate(1, 1, 1);
						p.oDrawModel(p._this, p.results, p.info, G::localPlayerLbyBones, p.pFlexWeights, p.pFlexDelayedWeights, p.origin, p.drawFlags);
					}

					return Settings.GetSetting(Tab_Visuals, Visuals_GhostAngle);
				}
			}
		}


		return false;
	}
}