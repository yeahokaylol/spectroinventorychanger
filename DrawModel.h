typedef void(__thiscall* DrawModel_t)(void*, void* results, DrawModelInfo_t&, matrix3x4*, float*, float*, Vector&, int);
extern DrawModel_t oDrawModel;

extern void __fastcall DrawModel(void* _this, void* edx, void* results, DrawModelInfo_t& info, matrix3x4* pBoneToWorld, float* pFlexDelayedWeights, float* pFlexWeights, Vector& origin, int drawFlags);
