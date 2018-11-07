#pragma once

typedef void(__thiscall* DrawModelExecute_t)(void* ths, void*, void*, ModelRenderInfo_t&, matrix3x4*);
typedef void(__thiscall* DrawModel_t)(void*, void* results, DrawModelInfo_t&, matrix3x4*, float*, float*, Vector&, int);

namespace Chams
{
	extern bool clean;
	extern bool materialsCreated;

	extern bool execute;
	extern bool dmeClean;
	extern bool frsClean;

	extern IMaterial* ignorezLit;
	extern IMaterial* ignorezLitWireframe;
	extern IMaterial* lit;
	extern IMaterial* litWireframe;
	extern IMaterial* flat;
	extern IMaterial* ignorezFlat;
	extern IMaterial* cubeMap;
	extern IMaterial* cubeMapRed;

	extern IMaterial* matShowingEnemy;
	extern IMaterial* matHiddenEnemy;
	extern IMaterial* matShowingTeam;
	extern IMaterial* matHiddenTeam;
	extern IMaterial* matWeapon;
	extern IMaterial* matBlack;
	extern IMaterial* matWhite;

	void CreateMaterials();

	
	bool DrawModel(DrawModel_t oDrawModel, void* _this, void* results, DrawModelInfo_t& info, matrix3x4* pBoneToWorld, float* pFlexWeights, float* pFlexDelayedWeights, Vector& origin, int drawFlags);
	IMaterial* CreateMaterialChamsNew(bool shouldIgnoreZ, bool isLit, bool isWireframe, std::string matdata = "");


	extern bool enablePlayersDraw;

	struct DrawModelParams {
		DrawModel_t oDrawModel;
		DWORD* _this;
		DWORD* results;
		DrawModelInfo_t& info;
		matrix3x4_t* pBoneToWorld;
		float* pFlexWeights;
		float* pFlexDelayedWeights;
		Vector& origin;
		int drawFlags;
	};

};
