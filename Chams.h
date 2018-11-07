
struct DrawModelInfo_t;

typedef void(__thiscall* DrawModel_t)(void*, void* results, DrawModelInfo_t&, matrix3x4*, float*, float*, Vector&, int);


namespace Chams
{

	extern bool clean;
	extern bool materialsCreated;
	extern bool enablePlayersDraw;



	extern float colorHiddenEnemy[3], colorHiddenTeam[3], colorShowingEnemy[3], colorShowingTeam[3], colorShowingLocalPlayer[3];
	extern float colorWhite[3], colorDoctor[3], colorBlack[3], colorGlow[3];

	bool DrawModel(DrawModel_t oDrawModel, void* _this, void* results, DrawModelInfo_t& info, matrix3x4* pBoneToWorld, float* pFlexWeights, float* pFlexDelayedWeights, Vector& origin, int drawFlags);
	extern IMaterial* CreateMaterialChamsNew(bool shouldIgnoreZ, bool isLit, bool isWireframe, std::string matdata = "");

	extern bool execute;
	extern bool dmeClean;
	extern bool frsClean;

	struct DrawModelParams {
		DrawModel_t oDrawModel;
		DWORD* _this;
		DWORD* results;
		DrawModelInfo_t& info;
		matrix3x4* pBoneToWorld;
		float* pFlexWeights;
		float* pFlexDelayedWeights;
		Vector& origin;
		int drawFlags;
	};

//	void DrawColoredModel(DrawModelParams p, IMaterial *pMaterialHidden, IMaterial *pMaterialShowing, CColor colorHidden, CColor colorShowing);
}; 
